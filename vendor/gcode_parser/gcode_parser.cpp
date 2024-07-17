#include "gcode_parser.h"
#include <iostream>
#include <sstream>
#include <string>
#include <iomanip> // For std::fixed and std::setprecision
#include "draw_primitives.h"

#define mm_to_inch 0.03937008;
#define inch_to_mm 25.4;

gcode_parser::gcode_parser(){ }

// Function to split a token like "G64" into a pair ('G', 64)
std::pair<std::string, double> gcode_parser::split_token(std::string token) {
    std::string letter(1, token[0]);  // Create a string with the first character
    double value = std::stod(token.substr(1));
    return std::make_pair(letter, value);
}

int gcode_parser::tokenize(const std::string &filename, std::vector<gcode_line> &gcode_vec, const int &debug) {
    gcode_vec.clear();  // Clear the vector to ensure it's empty before starting

    std::string gcode = std_functions().read_file_to_string(filename);
    gcode = std_functions().string_to_lower(gcode);
    gcode = std_functions().remove_spaces(gcode);

    std::vector<std::pair<std::string, double>> pairvec = std_functions().parse_string_to_key_and_value(gcode, debug);

    gcode_line gc;
    for(auto pair:pairvec){

        if(pair.first=="newline"){
            gcode_vec.push_back(gc);
            gc.gvec.clear();
            gc.pvec.clear();
        }
        if(pair.first=="n"){
            gc.n=pair.second;
        }
        if(pair.first=="g"){
            gc.g=pair.second;
            gc.gvec.push_back(gc.g);
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
            gc.x=pair.second; // Keep track of the last coordinates.
            gc.pvec.push_back({'x',gc.x}); // Multiple spline input points
        }
        if(pair.first=="y"){
            gc.y=pair.second;
            gc.pvec.push_back({'y',gc.y});
        }
        if(pair.first=="z"){
            gc.z=pair.second;
            gc.pvec.push_back({'z',gc.z});
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
    gcode_vec.push_back(gc);

    return 1;
}

int gcode_parser::tokens_to_shapes(std::vector<gcode_line> &gcvec, std::vector<gcode_shape> &svec, const int &debug) {
    gp_Pnt p = {0, 0, 0};
    gp_Abc abc = {0, 0, 0};
    gp_Uvw uvw = {0, 0, 0};
    std::vector<gp_Pnt> pvec;

    gcode_shape shape;
    int plane = 0;
    int turns = 0; // For spirals, they use the P word for number of turns.
    int to_inches = 0;
    double deviation = 0;
    double tolerance = 0;
    int offset_side = 0;
    int line = 1;
    int gid = -1;

    for (size_t i = 0; i < gcvec.size(); i++) {
        // Convert the multi input for gcode line x, y, z into gp_Pnt vec.
        pvec.clear();
        pvec.push_back(p);
        double x = p.X(), y = p.Y(), z = p.Z();
        for (size_t j = 0; j < gcvec[i].pvec.size(); j++) { // std::vector<std::pair<char, double>> pvec
            if (gcvec[i].pvec[j].first == 'x') {
                x = gcvec[i].pvec[j].second;
            }
            if (gcvec[i].pvec[j].first == 'y') {
                y = gcvec[i].pvec[j].second;
            }
            if (gcvec[i].pvec[j].first == 'z') {
                z = gcvec[i].pvec[j].second;
            }

            if (j < gcvec[i].pvec.size() - 1) {
                // Create groups.
                if ((gcvec[i].pvec[j].first == 'x' && gcvec[i].pvec[j + 1].first == 'x') ||
                    (gcvec[i].pvec[j].first == 'y' && gcvec[i].pvec[j + 1].first == 'y') ||
                    (gcvec[i].pvec[j].first == 'y' && gcvec[i].pvec[j + 1].first == 'x') ||
                    (gcvec[i].pvec[j].first == 'z' && gcvec[i].pvec[j + 1].first == 'x') ||
                    (gcvec[i].pvec[j].first == 'z' && gcvec[i].pvec[j + 1].first == 'y') ||
                    (gcvec[i].pvec[j].first == 'z' && gcvec[i].pvec[j + 1].first == 'z')) {
                    pvec.push_back({x, y, z});
                }
            }

            if (j == gcvec[i].pvec.size() - 1) {
                pvec.push_back({x, y, z});
            }
        }

        // If no G-code identifier in the current line, use the previous one
        if (gcvec[i].gvec.empty() && gid != -1) {
            gcvec[i].gvec.push_back(gid);
        }

        // Update active G-codes
        for (size_t j = 0; j < gcvec[i].gvec.size(); j++) {
            int current_gcode = gcvec[i].gvec[j];
            if (current_gcode == 20) { // G20 - to use inches for length units.
                to_inches = 1;
            }
            if (current_gcode == 21) { // G21 - to use millimeters for length units.
                to_inches = 0;
            }
            if (current_gcode == 40) { // Tool compensation off.
                offset_side = 0;
            }
            if (current_gcode == 41) { // Tool offset left of programmed path.
                offset_side = 1;
            }
            if (current_gcode == 42) { // Tool offset right of programmed path.
                offset_side = 2;
            }
            if (current_gcode == 17) { // G17 (Z-axis, XY-plane)
                plane = 0;
            }
            if (current_gcode == 18) { // G18 (Y-axis, XZ-plane)
                plane = 1;
            }
            if (current_gcode == 19) { // G19 (X-axis, YZ-plane)
                plane = 2;
            }
            if (current_gcode == 2 || current_gcode == 3) { // Spiral turns.
                turns = gcvec[i].p;
            }
            if (current_gcode == 64) { // G64
                deviation = gcvec[i].p; // Path max deviation, tolerance.
                tolerance = gcvec[i].q; // Naive cam tolerance. Filter out tiny segments.
            }
            if (current_gcode == 0 || current_gcode == 1 || current_gcode == 2 || current_gcode == 3 || current_gcode == 5 || current_gcode == 9) { // New shape found.
                shape.p0 = p;
                shape.p1 = {gcvec[i].x, gcvec[i].y, gcvec[i].z};
                shape.pvec.clear();
                shape.pvec = pvec;
                shape.abc0 = abc;
                shape.abc1 = {gcvec[i].a, gcvec[i].b, gcvec[i].c};
                shape.uvw0 = uvw;
                shape.uvw1 = {gcvec[i].u, gcvec[i].v, gcvec[i].w};
                shape.ijk = {gcvec[i].i, gcvec[i].j, gcvec[i].k};
                shape.plane = plane;
                shape.deviation = deviation;
                shape.tolerance = tolerance;
                shape.offset_side = offset_side;
                shape.turns = turns;
                shape.to_inches = to_inches;
                shape.gcode_line = line;
                shape.g_id = current_gcode;
                shape.shape_type = gcode_shape_type::general;

                if (current_gcode == 0) { // G0 - rapid positioning
                    shape.shape_type = gcode_shape_type::line;
                    shape.aShape = draw_primitives::draw_3d_line(p, shape.p1, shape.length);
                }
                if (current_gcode == 1) { // G1 - linear interpolation
                    shape.shape_type = gcode_shape_type::line;
                    shape.aShape = draw_primitives::draw_3d_line(p, shape.p1, shape.length);
                }
                if (current_gcode == 2 || current_gcode == 3) { // G2, G3 - circular interpolation
                    shape.shape_type = gcode_shape_type( draw_primitives::get_arc_shape_type(current_gcode, p, shape.p1) );
                    shape.aShape = draw_primitives::draw_3d_gcode_arc_circle_helix(p, shape.p1, current_gcode, plane, shape.ijk.X(), shape.ijk.Y(), shape.ijk.Z(), turns, 0, shape.pw, shape.length);
                }
                if (current_gcode == 5) { // G5 - spline interpolation
                    shape.shape_type = gcode_shape_type::spline;
                    shape.aShape = draw_primitives::draw_3d_spline_degree_3(shape.pvec, shape.length);
                }

                shape.aShape=draw_primitives::colorize(shape.aShape, Quantity_NOC_ANTIQUEWHITE, 0);
                svec.push_back(shape);

                p = shape.p1;
                abc = shape.abc1;
                uvw = shape.uvw1;
                line++;
            }
        }

        if (!gcvec[i].gvec.empty()) {
            gid = gcvec[i].gvec.back();
        }
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

int gcode_parser::optimize_tooldir_path(std::vector<gcode_shape> &svec, double fillet, std::vector<Handle(AIS_Shape)> &aisvec){

    if(fillet==0){
        return 0;
    }

    int first=0, last=0;
    for(uint i=0; i<svec.size(); i++){
        if ( (svec[i].g_id == 0 || svec[i].g_id == 1 || svec[i].g_id == 2 || svec[i].g_id == 3 || svec[i].g_id == 5 ) && svec[i].length>0 ) {
            last=i;
        }
    }

    // Record tooldir path, trim tooldir path.
    int count=0;
    for (auto& i : svec) {
        // mainWindow->occ->add_shapevec(i.aShape);
        aisvec.push_back( i.aShape_tooldir_1);

        // Recorded tooldir path preview.
        if ( (i.g_id == 0 || i.g_id == 1) && i.length>0 ) {
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
        else if ( (i.g_id == 2 || i.g_id == 3) && i.length>0 ) {
            std::vector<gp_Pnt> pvec;
            if(i.shape_type==gcode_shape_type::arc){
                pvec = draw_primitives::record_tooldir_path_arc(i.p0, i.pw, i.p1, i.abc0, i.abc1, 15);
            }
            if(i.shape_type==gcode_shape_type::circle){
                pvec = draw_primitives::record_tooldir_path_circle(i.p0, i.pc, i.plane, i.g_id, i.abc0, i.abc1, 15);
            }
            if(i.shape_type==gcode_shape_type::helix){

            }
            i.pvec_tooldir_path = draw_primitives::trim_recorded_tooldir_path_line_both_sides( pvec, fillet);
            if(!first){
                i.pvec_tooldir_path[0]=i.p0;
                first=1;
            }
            if(count==last){
                i.pvec_tooldir_path.back()=i.ta1;
            }
        }  else if (i.g_id == 5 && i.length>0 ) {
            std::vector<gp_Pnt> pvec = draw_primitives::record_tooldir_path_spline_degree_3(i.pvec, i.abc0, i.abc1, 15);
            i.pvec_tooldir_path = draw_primitives::trim_recorded_tooldir_path_line_both_sides( pvec, fillet);
            if(!first){
                i.pvec_tooldir_path[0]=i.pvec.front();
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
        if(svec[i].length>0){
            for (j = i+1; j < svec.size(); j++) {
                if(svec[j].length>0){

                    // Generate spline waypoints.
                    gp_Pnt p0 = svec[i].pvec_tooldir_path[svec[i].pvec_tooldir_path.size() - 2];
                    gp_Pnt p1 = svec[i].pvec_tooldir_path[svec[i].pvec_tooldir_path.size() - 1];
                    gp_Pnt p2;
                    double dist0=p0.Distance(p1);

                    int c=3; // In some cases a line was drawn, spline fillet failed. This had to do with p0 to p1 dist was zero.
                    while (dist0 == 0 && c <= svec[i].pvec_tooldir_path.size()) {
                        p0 = svec[i].pvec_tooldir_path[svec[i].pvec_tooldir_path.size() - c];
                        dist0 = p0.Distance(p1);
                        c++;
                    }

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

int gcode_parser::optimize_tcp_path(std::vector<gcode_shape> &svec, double fillet, std::vector<Handle(AIS_Shape)> &aisvec){

    // First get the shape type.
    // Line G0-G1, Arc G2-G3, Spline G.. , Helix G2-G3 + Zdiff, Clothoid G9.



}


















