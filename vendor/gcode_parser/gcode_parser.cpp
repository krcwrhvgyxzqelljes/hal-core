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

int gcode_parser::tokenize(const std::string &filename, std::vector<gcode_line> &gvec, int debug) {
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
    return 1;
}

int gcode_parser::tokens_to_shapes(const std::vector<gcode_line> &gvec, std::vector<shape> &svec){

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
    int path_offset_dir=0;

    int line=1;
    int spline_start=0;
    for(auto g:gvec){

        if(g.g==20){ // G20 - to use inches for length units.
            to_inches=1;
        }
        if(g.g==21){ // G21 - to use millimeters for length units.
            to_inches=0;
        }

        if(g.g==40){ // Tool compensation off, we can use this for tangential knife or plasma, to set the cut compensation on a,b axis.
            path_offset_dir=0;
        }
        if(g.g==41){ // Tool offset left of programmed path.
            path_offset_dir=1;
        }
        if(g.g==42){ // Tool offset right of programmed path.
            path_offset_dir=2;
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
            spline_start=0; // Reset flag.
        }
        if(g.g==5 && !spline_start){ // New shape found.
            svec.push_back(sha);
            svec.back().gcode_line=line;
            svec.back().g_id=g.g;
            spline_start=1; // Reset flag.
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

            // Here we calculate point ta0 & ta1. This is a tooldir point on the tooldir axis.
            draw_primitives::draw_3d_line_vector(svec.back().p0,15,svec.back().abc0.X(),svec.back().abc0.Y(),svec.back().abc0.Z(),svec.back().ta0);
            draw_primitives::draw_3d_line_vector(svec.back().p1,15,svec.back().abc1.X(),svec.back().abc1.Y(),svec.back().abc1.Z(),svec.back().ta1);

            svec.back().lenght=svec.back().p0.Distance(svec.back().p1);
            svec.back().g64_p=g64_p;
            svec.back().g64_q=g64_q;
            svec.back().path_offset_dir=path_offset_dir;
            svec.back().shape_type=gcode_shape_type::line;
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

            // Here we calculate point ta0 & ta1. This is a tooldir point on the tooldir axis.
            draw_primitives::draw_3d_line_vector(svec.back().p0,15,svec.back().abc0.X(),svec.back().abc0.Y(),svec.back().abc0.Z(),svec.back().ta0);
            draw_primitives::draw_3d_line_vector(svec.back().p1,15,svec.back().abc1.X(),svec.back().abc1.Y(),svec.back().abc1.Z(),svec.back().ta1);

            // Todo calculate helix lenght.
            svec.back().lenght=draw_primitives::get_3d_arc_lenght(svec.back().p0,svec.back().pw,svec.back().p1);
            svec.back().g64_p=g64_p;
            svec.back().g64_q=g64_q;
            svec.back().path_offset_dir=path_offset_dir;
            svec.back().shape_type=gcode_shape_type( draw_primitives::get_arc_shape_type(plane,svec.back().p0,svec.back().p1) );
        }

        // Clothoid.
        if(svec.back().g_id==9){
            svec.back().p0=p;
            svec.back().p1={g.x,g.y,g.z};
            svec.back().abc0=abc;
            svec.back().abc1={g.a,g.b,g.c};
            svec.back().uvw0=uvw;
            svec.back().uvw1={g.u,g.v,g.w};

            std::cout<<"gcode parser: no clothoid produced."<<std::endl;
        }

        // Spline.
        /*
            # Spline valid gcode:
            G5  x0 y0 z0 	# spline start point.
                x50 y50     # spline control point, newline
                ..          # more control points, newline.
                x100 y0     # spline end point, newline
         */
        if(spline_start==1){

            svec.back().p0=p;               // Unused.
            svec.back().p1={g.x,g.y,g.z};   // Unused.
            svec.back().abc0=abc;
            svec.back().abc1={g.a,g.b,g.c};
            svec.back().uvw0=uvw;
            svec.back().uvw1={g.u,g.v,g.w};

            svec.back().pwvec.push_back({g.x,g.y,g.z}); // Add spline points.
            draw_primitives::filter_out_duplicate_points(svec.back().pwvec);

            svec.back().aShape=draw_primitives::draw_3d_spline_degree_3(svec.back().pwvec);
            svec.back().aShape=draw_primitives::colorize( svec.back().aShape, Quantity_NOC_GRAY50, 0.8);
        }

        p=svec.back().p1;
        abc=svec.back().abc1;
        uvw=svec.back().uvw1;
        line++;
    }

    return 1;
}

int gcode_parser::process_limits(const std::vector<gcode_line> &gvec, gcode_limits &limits){

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

    // Ok when there is no diff in xmax, xmin a box can not be made results in domain error.
    if(limits.xmin==limits.xmax){
        limits.xmax+=0.1;
    }
    if(limits.ymin==limits.ymax){
        limits.ymax+=0.1;
    }
    if(limits.zmin==limits.zmax){
        limits.zmax+=0.1;
    }

    return 1;
}

int gcode_parser::optimize_tooldir_path(std::vector<shape> &svec, double fillet, std::vector<Handle(AIS_Shape)> &aisvec){

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
        aisvec.push_back( i.aShape_tooldir_1);

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
            aisvec.push_back( draw_primitives::colorize( draw_primitives::draw_3d_line_wire_low_memory_usage( i.pvec_tooldir_path) , Quantity_NOC_BLUE, 0) );
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

                        aisvec.push_back( draw_primitives::colorize( draw_primitives::draw_3d_line_wire_low_memory_usage(svec[i].pvec_back_tooldir_path), Quantity_NOC_AZURE,0 ) );
                        aisvec.push_back( draw_primitives::colorize( draw_primitives::draw_3d_line_wire_low_memory_usage(svec[j].pvec_front_tooldir_path), Quantity_NOC_CYAN,0 ) );

                        gp_Pnt pi;
                        draw_primitives::interpolate_point_on_spline_degree_3({p1,p2,p5,p3},0.5,pi);

                        svec[i].aShape_tooldir_1=draw_primitives::draw_3d_line(pi,svec[i].p1);
                        svec[i].aShape_tooldir_1=draw_primitives::colorize( svec[i].aShape_tooldir_1, Quantity_NOC_DODGERBLUE1,0 );
                        aisvec.push_back( svec[i].aShape_tooldir_1);

                    } else { // If spline fails, draw a line.
                        gp_Pnt p2=draw_primitives::get_line_midpoint(p1,p3);
                        svec[i].pvec_back_tooldir_path={p1,p2};
                        svec[j].pvec_front_tooldir_path={p2,p3};

                        aisvec.push_back( draw_primitives::colorize( draw_primitives::draw_3d_line_wire_low_memory_usage(svec[i].pvec_back_tooldir_path), Quantity_NOC_AZURE,0 ) );
                        aisvec.push_back( draw_primitives::colorize( draw_primitives::draw_3d_line_wire_low_memory_usage(svec[j].pvec_front_tooldir_path), Quantity_NOC_CYAN,0 ) );

                        svec[i].aShape_tooldir_1=draw_primitives::draw_3d_line( p2 ,svec[i].p1);
                        svec[i].aShape_tooldir_1=draw_primitives::colorize( svec[i].aShape_tooldir_1, Quantity_NOC_DODGERBLUE1,0 );
                        aisvec.push_back( svec[i].aShape_tooldir_1);
                    }
                    break;
                }
            }
        }
    }

    // Tooldir at program start.
    svec[0].aShape_tooldir_0=draw_primitives::draw_3d_line( svec[0].ta0 ,svec[0].p0);
    svec[0].aShape_tooldir_0=draw_primitives::colorize( svec[0].aShape_tooldir_0, Quantity_NOC_DODGERBLUE1,0 );
    aisvec.push_back( svec[0].aShape_tooldir_0);

    // Tooldir at program end.
    svec[svec.size()-1].aShape_tooldir_1=draw_primitives::draw_3d_line( svec[svec.size()-1].ta1 ,svec[svec.size()-1].p1);
    svec[svec.size()-1].aShape_tooldir_1=draw_primitives::colorize( svec[svec.size()-1].aShape_tooldir_1, Quantity_NOC_DODGERBLUE1,0 );
    aisvec.push_back( svec[svec.size()-1].aShape_tooldir_1);

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
        // This draw the final tooldir path, matching one gcode line.
        if (i % 2 == 0) {
            // aisvec.push_back( draw_primitives::colorize( draw_primitives::draw_3d_line_wire_low_memory_usage(svec[i].pvec_final_tooldir_path), Quantity_NOC_DARKORCHID2,0) );
        } else {
            // aisvec.push_back( draw_primitives::colorize( draw_primitives::draw_3d_line_wire_low_memory_usage(svec[i].pvec_final_tooldir_path), Quantity_NOC_CORAL3,0) );
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

    return 1;
}

int gcode_parser::optimize_tcp_path(std::vector<shape> &svec, double fillet, std::vector<Handle(AIS_Shape)> &aisvec){

    // First get the shape type.
    // Line G0-G1, Arc G2-G3, Spline G.. , Helix G2-G3 + Zdiff, Clothoid G9.



}


















