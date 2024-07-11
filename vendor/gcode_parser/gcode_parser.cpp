#include "gcode_parser.h"
#include <iostream>
#include <sstream>
#include <string>
#include <iomanip> // For std::fixed and std::setprecision
#include "draw_primitives.h"

gcode_parser::gcode_parser(){ }

// Function to split a token like "G64" into a pair ('G', 64)
std::pair<std::string, double> gcode_parser::split_token(std::string token) {
    std::string letter(1, token[0]);  // Create a string with the first character
    double value = std::stod(token.substr(1));
    return std::make_pair(letter, value);
}

void gcode_parser::tokenize(const std::string &filename, std::vector<gcode_line> &gvec, int debug) {
    gvec.clear();  // Clear the vector to ensure it's empty before starting

    std::string gcode = std_functions().read_file_to_string(filename);
    gcode = std_functions().string_to_lower(gcode);
    gcode = std_functions().remove_spaces(gcode);


    std::vector<std::pair<std::string, double>> pairvec = std_functions().parse_string_to_key_and_value(gcode, 0);

    gcode_line gc;
    for(auto pair:pairvec){

        if(pair.first=="newline"){
            gvec.push_back(gc);
            gc.i=0;
            gc.j=0;
            gc.k=0;
        }
        if(pair.first=="n"){
            gc.n=pair.second;
        }
        if(pair.first=="g"){
            gc.g=pair.second;

            if(gc.g==17 || gc.g==18 || gc.g==19 || gc.g==20 || gc.g==21){
                // gvec.push_back(gc);
            }

            if(gc.g==64){

            }
        }
        if(pair.first=="p"){ // Used for spirals nr of turns. Used for G64 P..
            gc.p=pair.second;
        }
        if(pair.first=="q"){ // Used for G64 P.. Q..
            gc.q=pair.second;
        }
        if(pair.first=="l"){ // Used for spirals enables g2_continuity mode.
            gc.l=pair.second;
        }
        if(pair.first=="x"){
            gc.x=pair.second;
        }
        if(pair.first=="y"){
            gc.y=pair.second;
        }
        if(pair.first=="z"){
            gc.z=pair.second;
        }

        if(pair.first=="i"){
            gc.i=pair.second;
        }
        if(pair.first=="j"){
            gc.j=pair.second;
        }
        if(pair.first=="k"){
            gc.k=pair.second;
        }

        if(pair.first=="a"){
            gc.a=pair.second;
        }
        if(pair.first=="b"){
            gc.b=pair.second;
        }
        if(pair.first=="c"){
            gc.c=pair.second;
        }


        if(pair.first=="u"){
            gc.u=pair.second;
        }
        if(pair.first=="v"){
            gc.v=pair.second;
        }
        if(pair.first=="w"){
            gc.w=pair.second;
        }
    }
    gvec.push_back(gc);

    if(debug){
        for(auto line:gvec){
            std::cout<<"n:"<<line.n<<" g:"<<line.g
                    <<" x: "<<line.x<<" y:"<<line.y<<" z:"<<line.z
                   <<" a: "<<line.a<<" b:"<<line.b<<" c:"<<line.c
                  <<" i:"<<line.i<<" j:"<<line.j<<" k:"<<line.k
                 <<std::endl;
        }
    }
}

void gcode_parser::tokens_to_shapes(const std::vector<gcode_line> &gvec, std::vector<shape> &svec){

    gp_Pnt p={0,0,0};
    gp_Abc abc={0,0,0};
    gp_Uvw uvw={0,0,0};

    shape sha;

#define mm_to_inch 0.03937008;
#define inch_to_mm 25.4;
    int plane=0;
    int turns=0; // For spirals, they use the P word for nr of turns.
    int to_inches=0;
    double g64_p=0;
    double g64_q=0;

    int line=1;
    for(auto g:gvec){

        if(g.g==20){ // G20 - to use inches for length units.
            to_inches=1;
        }
        if(g.g==21){ // G21 - to use millimeters for length units.
            to_inches=0;
        }

        if(g.g==17){ // G17 (Z-axis, XY-plane)
            plane=0;
        }
        if(g.g==18){ // G18 (Y-axis, XZ-plane)
            plane=1;
        }
        if(g.g==19){ // G19 (X-axis, YZ-plane)
            plane=2;
        }

        if(g.g==64){ // G64
            g64_p=g.p; // Path max deviation, tollerance.
            g64_q=g.q; // Naive cam tollerance. Filter out tiny segments.
        }

        if(to_inches){
            g.x=g.x*inch_to_mm;
            g.y=g.y*inch_to_mm;
            g.z=g.z*inch_to_mm;
            g.a=g.a*inch_to_mm;
            g.b=g.b*inch_to_mm;
            g.c=g.c*inch_to_mm;
            g.u=g.u*inch_to_mm;
            g.v=g.v*inch_to_mm;
            g.w=g.w*inch_to_mm;
            g.i=g.i*inch_to_mm;
            g.j=g.j*inch_to_mm;
            g.k=g.k*inch_to_mm;
        }

        if(g.g==0 || g.g==1 || g.g==2 || g.g==3 || g.g==9){ // New shape found.
            svec.push_back(sha);
            svec.back().gcode_line=line;
            svec.back().g_id=g.g;
        }
        if(g.e>0){
            svec.back().e_id=g.e;
        }

        if(svec.back().g_id==0){
            svec.back().feed=INFINITY;
        }
        if(svec.back().g_id==1){
            svec.back().feed=g.f;
        }

        if(svec.back().g_id==0 || svec.back().g_id==1){ // Draw rapid or line feed.
            svec.back().p0=p;
            svec.back().p1={g.x,g.y,g.z};
            svec.back().abc0=abc;
            svec.back().abc1={g.a,g.b,g.c};
            svec.back().uvw0=uvw;
            svec.back().uvw1={g.u,g.v,g.w};

            svec.back().aShape=draw_primitives::draw_3d_gcode_line(svec.back().p0, svec.back().p1, svec.back().g_id, svec.back().pw);


            svec.back().aShape_tooldir_0=draw_primitives::draw_3d_line_vector(svec.back().p0,15,svec.back().abc0.X(),svec.back().abc0.Y(),svec.back().abc0.Z(),svec.back().ta0);
            svec.back().aShape_tooldir_1=draw_primitives::draw_3d_line_vector(svec.back().p1,15,svec.back().abc1.X(),svec.back().abc1.Y(),svec.back().abc1.Z(),svec.back().ta1);
            svec.back().aShape_tooldir_1=draw_primitives::colorize( svec.back().aShape_tooldir_1, Quantity_NOC_AQUAMARINE2, 0.8);

            //svec.back().aShape_tooldir_connect= draw_primitives::colorize( draw_primitives::draw_3d_line(svec.back().ta0,svec.back().ta1), Quantity_NOC_GREEN, 0.8);

            //std::vector<gp_Pnt> pvec=draw_primitives::record_tooldir_path_line(svec.back().p0,svec.back().p1,svec.back().abc0,svec.back().abc1,15);
            //svec.back().aShape_tooldir_connect=draw_primitives::draw_3d_line_wire_low_memory_usage(pvec);

            svec.back().lenght=svec.back().p0.Distance(svec.back().p1);
            svec.back().g64_p=g64_p;
            svec.back().g64_q=g64_q;
        }

        // Arc, circle or helix.
        if(svec.back().g_id==2 || svec.back().g_id==3){ // Draw arc G2 or G3. Draw spiral G2 or G3
            svec.back().p0=p;
            svec.back().p1={g.x,g.y,g.z};
            svec.back().abc0=abc;
            svec.back().abc1={g.a,g.b,g.c};
            svec.back().uvw0=uvw;
            svec.back().uvw1={g.u,g.v,g.w};
            svec.back().turns=g.p; // Set helix turns.
            svec.back().g2_continuity=g.l; // Set helix G2 continuity model.
            svec.back().aShape=draw_primitives::draw_3d_gcode_arc_circle_helix(svec.back().p0, svec.back().p1, plane, svec.back().g_id, g.i, g.j, g.k,
                                                                               svec.back().turns, svec.back().g2_continuity, svec.back().pw);

            svec.back().aShape_tooldir_0=draw_primitives::draw_3d_line_vector(svec.back().p0,15,svec.back().abc0.X(),svec.back().abc0.Y(),svec.back().abc0.Z(),svec.back().ta0);
            svec.back().aShape_tooldir_1=draw_primitives::draw_3d_line_vector(svec.back().p1,15,svec.back().abc1.X(),svec.back().abc1.Y(),svec.back().abc1.Z(),svec.back().ta1);
            svec.back().aShape_tooldir_1=draw_primitives::colorize( svec.back().aShape_tooldir_1, Quantity_NOC_AQUAMARINE2, 0.8);

            //svec.back().aShape_tooldir_connect= draw_primitives::colorize( draw_primitives::draw_3d_line(svec.back().ta0,svec.back().ta1), Quantity_NOC_GREEN, 0.8);

            //std::vector<gp_Pnt> pvec=draw_primitives::record_tooldir_path_arc(svec.back().p0,svec.back().pw,svec.back().p1,svec.back().abc0,svec.back().abc1,15);
            //svec.back().aShape_tooldir_connect=draw_primitives::draw_3d_line_wire_low_memory_usage(pvec);

            // Todo calculate helix lenght.
            svec.back().lenght=draw_primitives::get_3d_arc_lenght(svec.back().p0,svec.back().pw,svec.back().p1);
            svec.back().g64_p=g64_p;
            svec.back().g64_q=g64_q;
        }
        p=svec.back().p1;
        abc=svec.back().abc1;
        uvw=svec.back().uvw1;
        line++;
    }
}

void gcode_parser::process_limits(const std::vector<gcode_line> &gvec, gcode_limits &limits){

    for(auto i:gvec){
        if(limits.xmin>i.x){
            limits.xmin=i.x;
        }
        if(limits.xmax<i.x){
            limits.xmax=i.x;
        }

        if(limits.ymin>i.y){
            limits.ymin=i.y;
        }
        if(limits.ymax<i.y){
            limits.ymax=i.y;
        }

        if(limits.zmin>i.z){
            limits.zmin=i.z;
        }
        if(limits.zmax<i.z){
            limits.zmax=i.z;
        }
    }
}

void gcode_parser::optimize_tooldir_path(std::vector<shape> &svec, double fillet){

    int first=0, last=0;
    for(uint i=0; i<svec.size(); i++){
        if ( (svec[i].g_id == 0 || svec[i].g_id == 1 || svec[i].g_id == 2 || svec[i].g_id == 3) && svec[i].lenght>0 ) {
            last=i;
        }
    }

    // Record tooldir path, trim tooldir path.
    int count=0;
    for (auto& i : svec) {
        // mainWindow->occ->add_shapevec(i.aShape);
        // mainWindow->occ->add_shapevec(i.aShape_tooldir_1);

        // Recorded tooldir path preview.
        if ( (i.g_id == 0 || i.g_id == 1) && i.lenght>0 ) {
            std::vector<gp_Pnt> pvec = draw_primitives::record_tooldir_path_line(i.p0, i.p1, i.abc0, i.abc1, 15);
            i.pvec_tooldir_path = draw_primitives::trim_recorded_tooldir_path_line_both_sides( pvec, fillet);
            if(!first){
                i.pvec_tooldir_path[0]=i.p0; // Don't trim the first gcode segment.
                first=1;
            }
            if(count==last){
                i.pvec_tooldir_path.back()=i.ta1; // Don't trim the last gcode segment.
            }
        }
        else if ( (i.g_id == 2 || i.g_id == 3) && i.lenght>0 ) {
            std::vector<gp_Pnt> pvec = draw_primitives::record_tooldir_path_arc(i.p0, i.pw, i.p1, i.abc0, i.abc1, 15);
            i.pvec_tooldir_path = draw_primitives::trim_recorded_tooldir_path_line_both_sides( pvec, fillet);
            if(!first){
                i.pvec_tooldir_path[0]=i.p0;
                first=1;
            }
            if(count==last){
                i.pvec_tooldir_path.back()=i.ta1;
            }
        }
        if(i.pvec_tooldir_path.size()>0){ // Draw result.
            // mainWindow->occ->add_shapevec(draw_primitives::draw_3d_line_wire_low_memory_usage( i.pvec_tooldir_path) );
        }
        count++;
    }

    // Draw tooldir path fillets.
    int i=0, j=0;
    for (i = 0; i < svec.size() - 1; i++) {
        if(svec[i].lenght>0){
            for (j = i+1; j < svec.size(); j++) {
                if(svec[j].lenght>0){

                    // Generate spline waypoints.
                    gp_Pnt p0 = svec[i].pvec_tooldir_path[svec[i].pvec_tooldir_path.size() - 2];
                    gp_Pnt p1 = svec[i].pvec_tooldir_path[svec[i].pvec_tooldir_path.size() - 1];
                    gp_Pnt p2;
                    double dist0=p0.Distance(p1);
                    draw_primitives::offset_3d_point_on_line(p0,p1,dist0+0.001,p2);

                    gp_Pnt p3 = svec[j].pvec_tooldir_path[0];
                    gp_Pnt p4 = svec[j].pvec_tooldir_path[1];
                    gp_Pnt p5;
                    double dist1=p3.Distance(p4);
                    draw_primitives::offset_3d_point_on_line(p4,p3,dist1+0.001,p5);

                    if(p1.Distance(p2)>0 && p5.Distance(p3)>0){
                        // For the spline fillets, store fist set of points in this gcode line, store second set of points in upfollowing gcode line.
                        int numPoints = 20;
                        for (int ii = 0; ii < numPoints; ++ii) {
                            // Calculate parameter corresponding to current point
                            double progress = static_cast<double>(ii) / (2 * (numPoints - 1));  // Adjusted for 0 to 0.5
                            // std::cout << "progress: " << progress << std::endl;
                            gp_Pnt pi;
                            draw_primitives::interpolate_point_on_spline_degree_3({p1, p2, p5, p3}, progress, pi);
                            svec[i].pvec_back_tooldir_path.push_back(pi);
                        }
                        for (int ii = 0; ii < numPoints; ++ii) {
                            // Calculate parameter corresponding to current point
                            double progress = 0.5 + static_cast<double>(ii) / (2 * (numPoints - 1));  // Adjusted for 0.5 to 1.0
                            // std::cout << "progress: " << progress << std::endl;
                            gp_Pnt pi;
                            draw_primitives::interpolate_point_on_spline_degree_3({p1, p2, p5, p3}, progress, pi);
                            svec[j].pvec_front_tooldir_path.push_back(pi);
                        }

                        //mainWindow->occ->add_shapevec( draw_primitives::colorize( draw_primitives::draw_3d_line_wire_low_memory_usage(svec[i].pvec_back_tooldir_path), Quantity_NOC_AZURE,0 ) );
                        //mainWindow->occ->add_shapevec( draw_primitives::colorize( draw_primitives::draw_3d_line_wire_low_memory_usage(svec[j].pvec_front_tooldir_path), Quantity_NOC_CYAN,0 ) );

                        gp_Pnt pi;
                        draw_primitives::interpolate_point_on_spline_degree_3({p1,p2,p5,p3},0.5,pi);

                        svec[i].aShape_tooldir_1=draw_primitives::draw_3d_line(pi,svec[i].p1);
                        svec[i].aShape_tooldir_1=draw_primitives::colorize( svec[i].aShape_tooldir_1, Quantity_NOC_DODGERBLUE1,0 );
                        // mainWindow->occ->add_shapevec(svec[i].aShape_tooldir_1);

                    } else { // If spline fails, draw a line.
                        gp_Pnt p2=draw_primitives::get_line_midpoint(p1,p3);
                        svec[i].pvec_back_tooldir_path={p1,p2};
                        svec[j].pvec_front_tooldir_path={p2,p3};

                        // mainWindow->occ->add_shapevec( draw_primitives::colorize( draw_primitives::draw_3d_line_wire_low_memory_usage(svec[i].pvec_back_tooldir_path), Quantity_NOC_AZURE,0 ) );
                        // mainWindow->occ->add_shapevec( draw_primitives::colorize( draw_primitives::draw_3d_line_wire_low_memory_usage(svec[j].pvec_front_tooldir_path), Quantity_NOC_CYAN,0 ) );

                        svec[i].aShape_tooldir_1=draw_primitives::draw_3d_line( p2 ,svec[i].p1);
                        svec[i].aShape_tooldir_1=draw_primitives::colorize( svec[i].aShape_tooldir_1, Quantity_NOC_DODGERBLUE1,0 );
                        // mainWindow->occ->add_shapevec(svec[i].aShape_tooldir_1);
                    }
                    break;
                }
            }
        }
    }

    // Tooldir at program start.
    svec[0].aShape_tooldir_0=draw_primitives::draw_3d_line( svec[0].ta0 ,svec[0].p0);
    svec[0].aShape_tooldir_0=draw_primitives::colorize( svec[0].aShape_tooldir_0, Quantity_NOC_DODGERBLUE1,0 );
    // mainWindow->occ->add_shapevec(svec[0].aShape_tooldir_0);

    // Tooldir at program end.
    svec[svec.size()-1].aShape_tooldir_1=draw_primitives::draw_3d_line( svec[svec.size()-1].ta1 ,svec[svec.size()-1].p1);
    svec[svec.size()-1].aShape_tooldir_1=draw_primitives::colorize( svec[svec.size()-1].aShape_tooldir_1, Quantity_NOC_DODGERBLUE1,0 );
    // mainWindow->occ->add_shapevec(svec[svec.size()-1].aShape_tooldir_1);

    // Group final tooldir path to every gcode line. Also cleanup memory.
    for (uint i=0; i<svec.size(); i++) {
        svec[i].pvec_final_tooldir_path.clear();
        for (uint j=0; j<svec[i].pvec_front_tooldir_path.size(); j++) {
            svec[i].pvec_final_tooldir_path.push_back(svec[i].pvec_front_tooldir_path[j]);
        }
        for (uint j=0; j<svec[i].pvec_tooldir_path.size(); j++) {
            svec[i].pvec_final_tooldir_path.push_back(svec[i].pvec_tooldir_path[j]);
        }
        for (uint j=0; j<svec[i].pvec_back_tooldir_path.size(); j++) {
            svec[i].pvec_final_tooldir_path.push_back(svec[i].pvec_back_tooldir_path[j]);
        }

        svec[i].pvec_front_tooldir_path.clear();
        svec[i].pvec_tooldir_path.clear();
        svec[i].pvec_back_tooldir_path.clear();

        // Check if ii is even or odd. Show difference in color output to verify content.
        if (i % 2 == 0) {
            // mainWindow->occ->add_shapevec( draw_primitives::colorize( draw_primitives::draw_3d_line_wire_low_memory_usage(svec[i].pvec_final_tooldir_path), Quantity_NOC_DARKORCHID2,0) );
        } else {
            // mainWindow->occ->add_shapevec( draw_primitives::colorize( draw_primitives::draw_3d_line_wire_low_memory_usage(svec[i].pvec_final_tooldir_path), Quantity_NOC_CORAL3,0) );
        }
    }

    // Calculate total lenghts for tooldir path.
    for (uint i=0; i<svec.size(); i++) {
        svec[i].tooldir_final_lenght=0; // Reset.

        if(svec[i].pvec_final_tooldir_path.size()>1){
            for (uint j=0; j<svec[i].pvec_final_tooldir_path.size()-1; j++) {
                double l=svec[i].pvec_final_tooldir_path[j].Distance(svec[i].pvec_final_tooldir_path[j+1]);
                svec[i].tooldir_final_lenght+=l;
            }
        }
    }
}


















