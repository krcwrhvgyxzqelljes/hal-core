#include "state_machine_shm.h"
#include <iostream>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <mutex>
#include "../../../../vendor/scurve/scurve_engine/scurve_engine.h"
#include "draw_primitives.h"

#ifdef __cplusplus

std::mutex mtx; // Declaration of std::mutex

state_machine_shm::state_machine_shm() {
    create_shared_memory();
}

// For c++.
state_machine_shm::~state_machine_shm()
{
    // Detach and remove shared memory when destroying the object
    if (shm_ptr) {
        if (shmdt(shm_ptr) == -1) {
            perror("shmdt");
        }
    }
    if (shmctl(shm_id, IPC_RMID, nullptr) == -1) {
        perror("shmctl");
    }
}

// For c.
void state_machine_shm::detach_shared_memory(){
    // Detach and remove shared memory when destroying the object
    if (shm_ptr) {
        if (shmdt(shm_ptr) == -1) {
            perror("shmdt");
        }
    }
    if (shmctl(shm_id, IPC_RMID, nullptr) == -1) {
        perror("shmctl");
    }
}

void state_machine_shm::create_shared_memory()
{
    // Create a shared memory segment
    shm_id = shmget(SHM_KEY, sizeof(shared_mem_data), IPC_CREAT | 0666);
    if (shm_id == -1) {
        perror("shmget");
        throw std::runtime_error("Failed to create shared memory segment.");
    }

    // Attach the shared memory segment
    attach_shared_memory();

    std::cout << "Created shared memory segment" << std::endl;
}

void state_machine_shm::attach_shared_memory()
{
    // Attach the shared memory segment
    shm_ptr = (shared_mem_data*) shmat(shm_id, nullptr, 0);
    if (shm_ptr == (shared_mem_data*) -1) {
        perror("shmat");
        throw std::runtime_error("Failed to attach shared memory segment.");
    }
}

void state_machine_shm::write_to_shared_memory(shared_mem_data data)
{
    // Acquire lock to ensure exclusive access
    std::lock_guard<std::mutex> lock(mtx);

    // Update shared memory with sdata
    *shm_ptr = data;
}

shared_mem_data state_machine_shm::read_from_shared_memory(){

    // Acquire lock to ensure exclusive access
    std::lock_guard<std::mutex> lock(mtx);

    // Return the value from shared memory
    return *shm_ptr;
}

#else // C code

// Implement C-compatible functions here if needed

#endif // __cplusplus

extern "C" struct state_machine_shm* shm_init_ptr(){
    return new state_machine_shm();
}

extern "C" void shm_detach(struct state_machine_shm *ptr){
    std::cout<<"removing shared memory from hal"<<std::endl;
    ptr->detach_shared_memory();
}

// Function to calculate the combined velocity for x,y,z axis.
double combined_velocity(double vx, double vy, double vz) {
    return std::sqrt(vx * vx + vy * vy + vz * vz);
}
void copy_file_name(char (&target)[256], const char (&source)[256])
{
    std::strncpy(target, source, sizeof(target) - 1);
    target[sizeof(target) - 1] = '\0'; // Ensure null-termination
}
bool are_file_names_different(const char (&file_name1)[256], const char (&file_name2)[256])
{
    return std::strcmp(file_name1, file_name2) != 0;
}
bool are_strings_different(const char (&str1)[256], const char (&str2)[256])
{
    return std::strcmp(str1, str2) != 0;
}

char old_file_name[256];    // Checks if a new file is given.

inline void handle_jog(shared_mem_data &shm){

    for(uint id=0; id<10; id++){

        if(!shm.jog_step_enable){
            shm.maxpos[id]=shm.scd[id].maxpos;
            shm.minpos[id]=shm.scd[id].minpos;
        }

        // Jog step trigger reset on button release.
        if(shm.jog_step_enable && shm.jog[id]==0){
            shm.jog_step_trigger[id]=0;
        }

        // Apply the jog stepsize if jog step is active, respect machine limits.
        if(shm.jog_step_enable && !shm.jog_step_trigger[id] && shm.jog[id]!=0){
            shm.maxpos[id]= fmin( shm.scd[id].maxpos, shm.scd[id].guipos+shm.jog_step_size );
            shm.minpos[id]= fmax( shm.scd[id].minpos, shm.scd[id].guipos-shm.jog_step_size );
            shm.jog_step_trigger[id]=1;
        }

        if(shm.jog_to_zero[id]){
            shm.jog[id]=1;      // Set to a state.
            shm.maxpos[id]=0;   // Target pos.
        }

        // Jog routine.
        if(shm.jog[id]==1){
            scurve_engine::jog(shm.scd[id],shm.maxpos[id]); // New scurve jog function.
        }
        if(shm.jog[id]==-1){
            scurve_engine::jog(shm.scd[id],shm.minpos[id]);
        }
        if(shm.jog[id]==0){
            scurve_engine::jog_stop(shm.scd[id]);
        }
        shm.pos[id]=shm.scd[id].guipos;
    }
    // Get the total velocity for xyz moves to display in the dro.
    shm.curvel=combined_velocity(shm.scd[0].guivel,shm.scd[1].guivel,shm.scd[2].guivel);
}

inline void handle_mdi(shared_mem_data &shm){

}

std::vector<shape> svec;    // Gcode file shapes.
scurve_data sctp_xyz;       // Scurve trajectory planner for xyz moves.
scurve_data sctp_abc;       // Scurve trajectory planner for abc moves.
double svec_nr=0;           // Current gcode line in the vector.
gp_Pnt pi;

inline void process_rapids_to_starpos(shared_mem_data &shm){

    for(auto i:svec){ // Check if current position is at first gcode position. Otherwise insert moves to first gcode position.
        if(i.lenght>0 && i.p0.Distance({shm.scd[0].guipos, shm.scd[1].guipos, shm.scd[2].guipos})!=0){

            // Insert rapids from current pos to program startpos.
            shape s0;
            s0.g_id=0;
            s0.p0={shm.scd[0].guipos, shm.scd[1].guipos, shm.scd[2].guipos};
            s0.p1={shm.scd[0].guipos, shm.scd[1].guipos, svec[0].p0.Z()+5};
            s0.pw=draw_primitives::get_line_midpoint(s0.p0,s0.p1);
            s0.lenght=s0.p0.Distance(s0.p1);

            s0.abc0={shm.scd[3].guipos, shm.scd[4].guipos, shm.scd[5].guipos};
            s0.abc1=s0.abc0;

            s0.uvw0={shm.scd[6].guipos, shm.scd[7].guipos, shm.scd[8].guipos};
            s0.uvw1=s0.uvw0;

            shape s1;
            s1.g_id=0;
            s1.p0=s0.p1;
            s1.p1={svec[0].p0.X(),svec[0].p0.Y(),s0.p1.Z()};
            s1.pw=draw_primitives::get_line_midpoint(s1.p0,s1.p1);
            s1.lenght=s1.p0.Distance(s1.p1);

            s1.abc0=s0.abc0;
            s1.abc1=s0.abc1;
            s1.uvw0=s0.uvw0;
            s1.uvw1=s1.uvw1;

            shape s2;
            s2.g_id=0;
            s2.p0=s1.p1;
            s2.p1=svec[0].p0;
            s2.pw=draw_primitives::get_line_midpoint(s2.p0,s2.p1);
            s2.lenght=s2.p0.Distance(s2.p1);

            s2.abc0=s1.abc1; // Todo add lenght, comparision master move.
            s2.abc1={svec[0].abc0.X(),svec[0].abc0.Y(),svec[0].abc0.Z()};

            s0.uvw0=s1.uvw1;
            s0.uvw1={svec[0].uvw0.X(),svec[0].uvw0.Y(),svec[0].uvw0.Z()};

            s0.abc1=svec[0].abc0;
            s0.uvw1=svec[0].uvw0;

            // Insert the shapes at the front of svec
            svec.insert(svec.begin(), s2); // Insert s3 at the front
            svec.insert(svec.begin(), s1); // Insert s1 at the front
            svec.insert(svec.begin(), s0); // Insert s0 at the front

            break;
        }
    }
}

inline void process_trajectory_lenghts(){
    // Calculate trajectory lengths for the vector
    svec[0].lenght_end = 0;
    double stot = 0;
    for (uint i = 0; i < svec.size(); i++) {
        stot += svec[i].lenght;
        svec[i].lenght_end = stot;
        svec[i].lenght_begin = svec[i].lenght_end - svec[i].lenght;
        // std::cout << "svec i:" << i << " length end:" << stot << std::endl;
    }
}

inline void load_gcode_from_line(shared_mem_data &shm,int start_line) {
    svec.clear();
    std::string file_name(shm.file_name);
    std::vector<gcode_line> gvec;
    gcode_parser parser;
    parser.tokenize(file_name, gvec, 0);
    parser.tokens_to_shapes(gvec, svec);
    parser.optimize_tooldir_path(svec,shm.tooldir_fillet);

    // Find the starting point in the shape vector
    int svec_start_nr = 0;
    gp_Pnt p_start;
    bool found_start_line = false;

    for (uint i = 0; i < svec.size(); i++) {
        if (svec[i].gcode_line > start_line) {
            p_start = svec[i].p0;
            svec_start_nr = i;
            found_start_line = true;
            break;
        }
    }

    // If the specified line number is not found, start from the beginning
    if (!found_start_line) {
        svec_start_nr = 0;
        p_start = svec[0].p0;
    }

    // Remove shapes before the specified starting G-code line
    if (found_start_line) {
        svec.erase(svec.begin(), svec.begin() + svec_start_nr);
    }

    process_rapids_to_starpos(shm);
    process_trajectory_lenghts();

    // Reset the current position and shape vector number
    sctp_xyz.guipos = 0;
    sctp_abc.guipos = 0;
    svec_nr = 0;

    copy_file_name(old_file_name, shm.file_name);

    std::cout << "-- gcode ready --" << std::endl << std::endl;
}

inline void load_gcode(shared_mem_data &shm) {
    svec.clear();
    std::string file_name(shm.file_name);
    std::vector<gcode_line> gvec;
    gcode_parser().tokenize(file_name,gvec,0);
    gcode_parser().tokens_to_shapes(gvec, svec);
   // gcode_parser().optimize_tooldir_path(svec,shm.tooldir_fillet);

    process_rapids_to_starpos(shm);
    process_trajectory_lenghts();

    sctp_xyz.guipos=0;
    sctp_abc.guipos=0;
    svec_nr=0;

    copy_file_name(old_file_name,shm.file_name);

    std::cout<<"-- gcode ready --"<<std::endl<<std::endl;
}

// Function to calculate rotation angles and translation vector
inline void calculate_rotation_angles(const gp_Pnt& p0, gp_Pnt p1, double &a, double &b, double &c) {

    if(p0.Distance(p1)==0){
        p1.SetZ(p0.Z()+1);
        std::cout<<"calculate rotation angle error, z value set to 1."<<std::endl;
    }

    // Create the vector from p0 to p1
    gp_Vec vec_to(p1.X() - p0.X(), p1.Y() - p0.Y(), p1.Z() - p0.Z());

    // Assuming initial vector along the Z-axis (0, 0, 1)
    gp_Vec vec_from(0, 0, 1);

    // Get the rotation quaternion from the vectors
    gp_Quaternion quaternion;
    quaternion.SetRotation(vec_from, vec_to);

    // Retrieve the Euler angles directly from the quaternion
    quaternion.GetEulerAngles(gp_Extrinsic_XYZ, a, b, c);
}

gp_Pnt abc_pi;
int interupt_rotate_abc=0;
inline void handle_auto(shared_mem_data &shm){

    if(shm.load_file){
        if(shm.run_from_line==0){
            load_gcode(shm);
        }
        if(shm.run_from_line>0){
            load_gcode_from_line(shm, shm.run_from_line);
        }
        shm.load_file=0;
    }


    if(svec.size()>0){

        // Todo take the lowest xyz values.
        sctp_xyz.maxvel=shm.scd[0].maxvel*(fabs(shm.auto_speed_procent/100));
        sctp_xyz.maxacc=shm.scd[0].maxacc;
        sctp_xyz.jermax=shm.scd[0].jermax;
        sctp_xyz.intval=0.001;

        if(shm.run_mode==RUN && shm.auto_speed_procent>=0){
            scurve_engine::jog(sctp_xyz,svec[svec_nr].lenght_end);

            // Move finished to end pos, increment gcode line.
            if((sctp_xyz.guipos > svec[svec_nr].lenght_end - 1e-6) && svec_nr<svec.size()-1){

                // If xyz move has had no lenght, but abc has lenght, interupt process to perform the abc move now.
                if(svec[svec_nr].lenght_begin==svec[svec_nr].lenght_end && !interupt_rotate_abc){
                    if(svec[svec_nr].abc0.Distance(svec[svec_nr].abc1)>0){ // Has diff in corner angles abc.
                        sctp_abc.guipos=0;
                        sctp_abc.tarpos=svec[svec_nr].abc0.Distance(svec[svec_nr].abc1);
                        interupt_rotate_abc=1;
                        std::cout<<"abc axis move fwd interupt without xyz move."<<std::endl;
                    }
                }

                if(!interupt_rotate_abc){
                    svec_nr++;
                }
            }
        }
        if(shm.run_mode==RUN && shm.auto_speed_procent<0){
            scurve_engine::jog(sctp_xyz,svec[svec_nr].lenght_begin);

            // Move finished to be at start pos, decrement gcode line.
            if((sctp_xyz.guipos < svec[svec_nr].lenght_begin + 1e-6)  && svec_nr>0){

                // If xyz move has had no lenght, but abc has lenght, interupt process to perform the abc move now.
                if(svec[svec_nr].lenght_begin==svec[svec_nr].lenght_end){
                    if(svec[svec_nr].abc0.Distance(svec[svec_nr].abc1)>0 && !interupt_rotate_abc){ // Has diff in corner angles abc.
                        sctp_abc.guipos=svec[svec_nr].abc0.Distance(svec[svec_nr].abc0);
                        sctp_abc.tarpos=0;
                        interupt_rotate_abc=1;
                        std::cout<<"abc axis move rev interupt without xyz move."<<std::endl;
                    }
                }

                if(!interupt_rotate_abc){
                    svec_nr--;
                }
            }
        }

        if(shm.run_mode==STOP || shm.run_mode==PAUSE){
            scurve_engine::jog_stop(sctp_xyz);
        }

        gp_Pnt p0=svec[svec_nr].p0;
        gp_Pnt pw=svec[svec_nr].pw;
        gp_Pnt p1=svec[svec_nr].p1;

        gp_Pnt abc0=svec[svec_nr].abc0;
        gp_Pnt abc1=svec[svec_nr].abc1;
        // gp_Pnt abc_pi;

        gp_Pnt uvw0=svec[svec_nr].uvw0;
        gp_Pnt uvw1=svec[svec_nr].uvw1;
        gp_Pnt uvw_pi;

        double progress=(sctp_xyz.guipos-svec[svec_nr].lenght_begin) /*lenght done*/ / svec[svec_nr].lenght;

        if(svec[svec_nr].lenght==0){ // Avoid NAN when svec lenght=0.
            progress=1;
        }
        // std::cout<<"progress:"<<progress<<std::endl;

        if(svec[svec_nr].g_id==0 || svec[svec_nr].g_id==1 ){
            draw_primitives::interpolate_point_on_line(p0,p1,progress,pi);
            draw_primitives::interpolate_point_on_line(abc0,abc1,progress,abc_pi);
            // std::cout<<"original angle a:"<<abc_pi.X()<<" b:"<<abc_pi.Y()<<" c:"<<abc_pi.X()<<std::endl;
            // std::cout<<"original x:"<<svec[svec_nr].ta1.X()<<" y:"<<svec[svec_nr].ta1.Y()<<" z:"<<svec[svec_nr].ta1.Z()<<std::endl;

            if(svec[svec_nr].pvec_final_tooldir_path.size()>0){
                gp_Pnt ta;
                draw_primitives::interpolate_point_on_pvec_path(svec[svec_nr].pvec_final_tooldir_path,svec[svec_nr].tooldir_final_lenght,progress,ta);
                double a,b,c;
                calculate_rotation_angles(pi,ta,a,b,c);

                //

                abc_pi={a,b,abc_pi.Z()};
                //std::cout<<"angle a:"<<a<<" b:"<<b<<" c:"<<c<<std::endl;
                shm.ta=ta;
                // std::cout<<"ta x:"<<ta.X()<<" y:"<<ta.Y()<<" z:"<<ta.Z()<<std::endl;
            }

            draw_primitives::interpolate_point_on_line(uvw0,uvw1,progress,uvw_pi);
        }
        if(svec[svec_nr].g_id==2 || svec[svec_nr].g_id==3 ){
            draw_primitives::interpolate_point_on_arc(p0,pw,p1,progress,pi);
            draw_primitives::interpolate_point_on_line(abc0,abc1,progress,abc_pi);
            // std::cout<<"original angle a:"<<abc_pi.X()<<" b:"<<abc_pi.Y()<<" c:"<<abc_pi.X()<<std::endl;
            // std::cout<<"original x:"<<svec[svec_nr].ta1.X()<<" y:"<<svec[svec_nr].ta1.Y()<<" z:"<<svec[svec_nr].ta1.Z()<<std::endl;

            if(svec[svec_nr].pvec_final_tooldir_path.size()>0){
                gp_Pnt ta;
                draw_primitives::interpolate_point_on_pvec_path(svec[svec_nr].pvec_final_tooldir_path,svec[svec_nr].tooldir_final_lenght,progress,ta);
                double a,b,c;
                calculate_rotation_angles(pi,ta,a,b,c);
                abc_pi={a,b,abc_pi.Z()};
                shm.ta=ta;
                // std::cout<<"angle a:"<<a<<" b:"<<b<<" c:"<<c<<std::endl;
                // std::cout<<"ta x:"<<ta.X()<<" y:"<<ta.Y()<<" z:"<<ta.Z()<<std::endl;
            }

            draw_primitives::interpolate_point_on_line(uvw0,uvw1,progress,uvw_pi);
        }


        if(interupt_rotate_abc){

            std::cout<<"abc interupt move active."<<std::endl;

            // Todo take the lowest abc values.
            sctp_abc.maxvel=shm.scd[3].maxvel*(fabs(shm.auto_speed_procent/100));
            sctp_abc.maxacc=shm.scd[3].maxacc;
            sctp_abc.jermax=shm.scd[3].jermax;
            sctp_abc.intval=0.001;

            scurve_engine::jog(sctp_abc,sctp_abc.tarpos);

            if(shm.run_mode==RUN && shm.auto_speed_procent>=0){
                // Move finished to end pos, increment gcode line.
                if(sctp_abc.guipos > sctp_abc.tarpos - 1e-6){
                    interupt_rotate_abc=0;
                    svec_nr++;
                    std::cout<<"abc interupt fwd move finished."<<std::endl;
                }
            }
            if(shm.run_mode==RUN && shm.auto_speed_procent<0){
                // Move finished to be at start pos, decrement gcode line.
                if(sctp_abc.guipos < sctp_abc.tarpos + 1e-6){
                    interupt_rotate_abc=0;
                    svec_nr--;
                    std::cout<<"abc interupt rev move finished."<<std::endl;
                }
            }

            double progress_=sctp_abc.guipos/sctp_abc.tarpos;
            draw_primitives::interpolate_point_on_line(abc0,abc1,progress_,abc_pi);
        }

        shm.pos[0]=pi.X();
        shm.pos[1]=pi.Y();
        shm.pos[2]=pi.Z();

        shm.pos[3]=abc_pi.X();
        shm.pos[4]=abc_pi.Y();
        shm.pos[5]=abc_pi.Z();

        shm.pos[6]=uvw_pi.X();
        shm.pos[7]=uvw_pi.Y();
        shm.pos[8]=uvw_pi.Z();


        // Update jog axis 0-9.
        shm.scd[0].guipos=pi.X();
        shm.scd[1].guipos=pi.Y();
        shm.scd[2].guipos=pi.Z();

        shm.scd[3].guipos=abc_pi.X();
        shm.scd[4].guipos=abc_pi.Y();
        shm.scd[5].guipos=abc_pi.Z();

        shm.scd[6].guipos=uvw_pi.X();
        shm.scd[7].guipos=uvw_pi.Y();
        shm.scd[8].guipos=uvw_pi.Z();

        shm.curvel=sctp_xyz.guivel;
        shm.curacc=sctp_xyz.guiacc;
        shm.curpos=sctp_xyz.guipos;
        shm.gcode_line=svec[svec_nr].gcode_line;
    }
}

extern "C" void shm_update(struct state_machine_shm *ptr){

    // Acquire lock to ensure exclusive access
    std::lock_guard<std::mutex> lock(mtx);

    shared_mem_data &shm=*ptr->shm_ptr; // Use shorter notation.

    shm.halruntime+=0.001;

    if(shm.online_mode==ONLINE){
        //std::cout<<"hal online."<<std::endl;
        if(shm.state_mode==MANUAL){
            handle_jog(shm);
        }
        if(shm.state_mode==AUTO){
            handle_auto(shm);
        }
        if(shm.state_mode==MDI){
            handle_mdi(shm);
        }
    }
}

extern "C" void shm_update_pos(struct state_machine_shm *ptr, double* pos){

    pos[0] = ptr->shm_ptr->pos[0]; // x
    pos[1] = ptr->shm_ptr->pos[1]; // y
    pos[2] = ptr->shm_ptr->pos[2]; // z

    pos[3] = ptr->shm_ptr->pos[3]; // a
    pos[4] = ptr->shm_ptr->pos[4]; // b
    pos[5] = ptr->shm_ptr->pos[5]; // c

    pos[6] = ptr->shm_ptr->pos[6]; // u
    pos[7] = ptr->shm_ptr->pos[7]; // v
    pos[8] = ptr->shm_ptr->pos[8]; // w
}





























