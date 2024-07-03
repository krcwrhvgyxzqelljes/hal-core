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
scurve_data sctp;           // Scurve trajectory planner.
double svec_nr=0;           // Current gcode line in the vector.
gp_Pnt pi;

inline void load_gcode_from_line(shared_mem_data &shm,int start_line) {
    svec.clear();
    std::string file_name(shm.file_name);
    std::vector<gcode_line> gvec;
    gcode_parser parser;
    parser.tokenize(file_name, gvec, 0);
    parser.tokens_to_shapes(gvec, svec);

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

    // Insert rapid moves from the current position to the program start position
    shape s0;
    s0.g_id = 0;
    s0.p0 = {shm.scd[0].guipos, shm.scd[1].guipos, shm.scd[2].guipos};
    s0.p1 = {shm.scd[0].guipos, shm.scd[1].guipos, p_start.Z() + 5};
    s0.lenght = s0.p0.Distance(s0.p1);

    shape s1;
    s1.g_id = 0;
    s1.p0 = s0.p1;
    s1.p1 = {p_start.X(), p_start.Y(), p_start.Z() + 5};
    s1.lenght = s1.p0.Distance(s1.p1);

    shape s2;
    s2.g_id = 0;
    s2.p0 = s1.p1;
    s2.p1 = p_start;
    s2.lenght = s2.p0.Distance(s2.p1);

    // Insert the shapes at the front of the shape vector
    svec.insert(svec.begin(), s2); // Insert s2 at the front
    svec.insert(svec.begin(), s1); // Insert s1 at the front
    svec.insert(svec.begin(), s0); // Insert s0 at the front

    // Calculate trajectory lengths for the vector
    svec[0].lenght_end = 0;
    double stot = 0;
    for (uint i = 0; i < svec.size(); i++) {
        stot += svec[i].lenght;
        svec[i].lenght_end = stot;
        svec[i].lenght_begin = svec[i].lenght_end - svec[i].lenght;
        // std::cout << "svec i:" << i << " length end:" << stot << std::endl;
    }

    // Reset the current position and shape vector number
    sctp.guipos = 0;
    svec_nr = 0;

    // Copy the file name for further reference
    copy_file_name(old_file_name, shm.file_name);
    // std::cout << "svec size:" << svec.size() << std::endl;
    std::cout << "-- gcode ready --" << std::endl << std::endl;
}

inline void load_gcode(shared_mem_data &shm) {
    svec.clear();
    std::string file_name(shm.file_name);
    std::vector<gcode_line> gvec;
    gcode_parser().tokenize(file_name,gvec,0);
    gcode_parser().tokens_to_shapes(gvec, svec);

    // Insert rapids from current pos to program startpos.
    shape s0;
    s0.g_id=0;
    s0.p0={shm.scd[0].guipos, shm.scd[1].guipos, shm.scd[2].guipos};
    s0.p1={shm.scd[0].guipos, shm.scd[1].guipos, svec[0].p0.Z()+5};
    s0.lenght=s0.p0.Distance(s0.p1);

    shape s1;
    s1.g_id=0;
    s1.p0=s0.p1;
    s1.p1={svec[0].p0.X(),svec[0].p0.Y(),svec[0].p0.Z()+5};
    s1.lenght=s1.p0.Distance(s1.p1);

    shape s2;
    s2.g_id=0;
    s2.p0=s1.p1;
    s2.p1=svec[0].p0;
    s2.lenght=s2.p0.Distance(s2.p1);

    // Insert the shapes at the front of svec
    svec.insert(svec.begin(), s2); // Insert s3 at the front
    svec.insert(svec.begin(), s1); // Insert s1 at the front
    svec.insert(svec.begin(), s0); // Insert s0 at the front

    // Calculate trajectory lenghts for the vector.
    svec[0].lenght_end=0;
    double stot;
    for(uint i=0; i<svec.size(); i++){
        stot+=svec[i].lenght;
        svec[i].lenght_end=stot;
        svec[i].lenght_begin=svec[i].lenght_end-svec[i].lenght;
        // std::cout<<"svec i:"<<i<<" lenght end:"<<stot<<std::endl;
    }

    sctp.guipos=0;
    svec_nr=0;
    copy_file_name(old_file_name,shm.file_name);
    // std::cout<<"svec size:"<<svec.size()<<std::endl;
    std::cout<<"-- gcode ready --"<<std::endl<<std::endl;
}

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

        // For the trajectory speed i now take the lowest of x, y axis.
        sctp.maxvel=shm.scd[0].maxvel*(fabs(shm.auto_speed_procent/100));
        sctp.maxacc=shm.scd[1].maxacc;
        sctp.jermax=shm.scd[0].jermax;
        sctp.intval=0.001;

        if(shm.run_mode==RUN &&  shm.auto_speed_procent>=0){
            scurve_engine::jog(sctp,svec[svec_nr].lenght_end);
            if((sctp.guipos > svec[svec_nr].lenght_end - 1e-6) && svec_nr<svec.size()-1){
                svec_nr++;
            }
        }
        if(shm.run_mode==RUN && shm.auto_speed_procent<0){
            scurve_engine::jog(sctp,svec[svec_nr].lenght_begin);
            if((sctp.guipos < svec[svec_nr].lenght_begin + 1e-6)  && svec_nr>0){
                svec_nr--;
            }
        }

        if(shm.run_mode==STOP || shm.run_mode==PAUSE){
            scurve_engine::jog_stop(sctp);
        }

        gp_Pnt p0=svec[svec_nr].p0;
        gp_Pnt pw=svec[svec_nr].pw;
        gp_Pnt p1=svec[svec_nr].p1;

        double progress=(sctp.guipos-svec[svec_nr].lenght_begin) /*lenght done*/ / svec[svec_nr].lenght;

        if(svec[svec_nr].lenght==0){ // Avoid NAN when svec lenght=0.
            progress=1;
        }
        std::cout<<"progress:"<<progress<<std::endl;

        if(svec[svec_nr].g_id==0 || svec[svec_nr].g_id==1 ){
            draw_primitives::interpolate_point_on_line(p0,p1,progress,pi);
        }
        if(svec[svec_nr].g_id==2 || svec[svec_nr].g_id==3 ){
            draw_primitives::interpolate_point_on_arc(p0,pw,p1,progress,pi);
        }

        shm.pos[0]=pi.X();
        shm.pos[1]=pi.Y();
        shm.pos[2]=pi.Z();

        shm.scd[0].guipos=pi.X();
        shm.scd[1].guipos=pi.Y();
        shm.scd[2].guipos=pi.Z();

        shm.curvel=sctp.guivel;
        shm.curacc=sctp.guiacc;
        shm.curpos=sctp.guipos;
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





























