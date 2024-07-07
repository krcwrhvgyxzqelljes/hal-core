#include "draw_clothoids.h"

draw_clothoids::draw_clothoids(){ }

int draw_clothoids::draw_2d_clothoid_3arc_G2_xy(gp_Pnt p0, gp_Pnt p1, double theta0, double theta1, double kappa0, double kappa1, std::vector<gp_Pnt> &pvec, double &ltot){

    //std::vector<gp_Pnt> pvec;
    G2lib::G2solve3arc g2solve3arc;

    g2solve3arc.setTolerance(1e-6);
    g2solve3arc.setMaxIter(10);

    G2lib::real_type x0  = p0.X();
    G2lib::real_type y0  = p0.Y();
    G2lib::real_type th0 = theta0;
    G2lib::real_type k0  = kappa0;
    G2lib::real_type x1  = p1.X();
    G2lib::real_type y1  = p1.Y();
    G2lib::real_type th1 = theta1;
    G2lib::real_type k1  = kappa1;

    int iter = g2solve3arc.build( x0, y0, th0, k0, x1, y1, th1, k1 );
    if(iter==-1){
        std::cout<<"clothoid terminated."<<std::endl;
        return 0;
    }

    G2lib::ClothoidCurve const & S0 = g2solve3arc.getS0();
    G2lib::ClothoidCurve const & S1 = g2solve3arc.getS1();
    G2lib::ClothoidCurve const & SM = g2solve3arc.getSM();

    ltot= g2solve3arc.totalLength();
    // std::cout<<"ltot"<<ltot<<" iter:"<<iter<<std::endl;
    int segments=20;

    if(ltot==0){
        return 0;
    }

    int cycles = segments+1;
    double increment = ltot / segments;

    for (int cycle = 0; cycle < cycles; ++cycle) {
        double i = cycle * increment;
        pvec.push_back({g2solve3arc.X(i), g2solve3arc.Y(i), 0});
    }
    return 1;
}

int draw_clothoids::draw_2d_clothoid_3arc_G2_xz(gp_Pnt p0, gp_Pnt p1, double theta0, double theta1, double kappa0, double kappa1, std::vector<gp_Pnt> &pvec, double &ltot){

    //std::vector<gp_Pnt> pvec;
    G2lib::G2solve3arc g2solve3arc;

    g2solve3arc.setTolerance(1e-6);
    g2solve3arc.setMaxIter(10);

    G2lib::real_type x0  = p0.X();
    G2lib::real_type z0  = p0.Z();
    G2lib::real_type th0 = theta0;
    G2lib::real_type k0  = kappa0;
    G2lib::real_type x1  = p1.X();
    G2lib::real_type z1  = p1.Z();
    G2lib::real_type th1 = theta1;
    G2lib::real_type k1  = kappa1;

    int iter = g2solve3arc.build( x0, z0, th0, k0, x1, z1, th1, k1 );
    if(iter==-1){
        std::cout<<"clothoid terminated."<<std::endl;
        return 0;
    }

    G2lib::ClothoidCurve const & S0 = g2solve3arc.getS0();
    G2lib::ClothoidCurve const & S1 = g2solve3arc.getS1();
    G2lib::ClothoidCurve const & SM = g2solve3arc.getSM();

    ltot= g2solve3arc.totalLength();
    // std::cout<<"ltot"<<ltot<<" iter:"<<iter<<std::endl;
    int segments=20;

    if(ltot==0){
        return 0;
    }

    int cycles = segments+1;
    double increment = ltot / segments;

    for (int cycle = 0; cycle < cycles; ++cycle) {
        double i = cycle * increment;
        pvec.push_back({g2solve3arc.X(i), 0, g2solve3arc.Y(i)});
    }
    return 1;
}


int draw_clothoids::interpolate_2d_clothoid_3arc_G2_xy(gp_Pnt p0, gp_Pnt p1, double theta0, double theta1, double kappa0, double kappa1, double progress, gp_Pnt &pi){

    //std::vector<gp_Pnt> pvec;
    G2lib::G2solve3arc g2solve3arc;

    g2solve3arc.setTolerance(1e-6);
    g2solve3arc.setMaxIter(10);

    G2lib::real_type x0  = p0.X();
    G2lib::real_type y0  = p0.Y();
    G2lib::real_type th0 = theta0;
    G2lib::real_type k0  = kappa0;
    G2lib::real_type x1  = p1.X();
    G2lib::real_type y1  = p1.Y();
    G2lib::real_type th1 = theta1;
    G2lib::real_type k1  = kappa1;

    int iter = g2solve3arc.build( x0, y0, th0, k0, x1, y1, th1, k1 );
    if(iter==-1){
        std::cout<<"clothoid terminated."<<std::endl;
        return 0;
    }

    G2lib::ClothoidCurve const & S0 = g2solve3arc.getS0();
    G2lib::ClothoidCurve const & S1 = g2solve3arc.getS1();
    G2lib::ClothoidCurve const & SM = g2solve3arc.getSM();

    double ltot= g2solve3arc.totalLength();

    if(ltot==0){
        return 0;
    }

    double i=progress*ltot;
    pi={g2solve3arc.X(i), g2solve3arc.Y(i), 0};

    return 1;
}

int draw_clothoids::interpolate_2d_clothoid_3arc_G2_xz(gp_Pnt p0, gp_Pnt p1, double theta0, double theta1, double kappa0, double kappa1, double progress, gp_Pnt &pi){

    //std::vector<gp_Pnt> pvec;
    G2lib::G2solve3arc g2solve3arc;

    g2solve3arc.setTolerance(1e-6);
    g2solve3arc.setMaxIter(10);

    G2lib::real_type x0  = p0.X();
    G2lib::real_type z0  = p0.Z();
    G2lib::real_type th0 = theta0;
    G2lib::real_type k0  = kappa0;
    G2lib::real_type x1  = p1.X();
    G2lib::real_type z1  = p1.Z();
    G2lib::real_type th1 = theta1;
    G2lib::real_type k1  = kappa1;

    int iter = g2solve3arc.build( x0, z0, th0, k0, x1, z1, th1, k1 );
    if(iter==-1){
        std::cout<<"clothoid terminated."<<std::endl;
        return 0;
    }

    G2lib::ClothoidCurve const & S0 = g2solve3arc.getS0();
    G2lib::ClothoidCurve const & S1 = g2solve3arc.getS1();
    G2lib::ClothoidCurve const & SM = g2solve3arc.getSM();

    double ltot= g2solve3arc.totalLength();

    if(ltot==0){
        return 0;
    }

    double i=progress*ltot;
    pi={g2solve3arc.X(i), 0, g2solve3arc.Y(i)};

    return 1;
}

int draw_clothoids::draw_inbetween_2d_clothoid_3arc_G2_xy(gp_Pnt p0, gp_Pnt p1, gp_Pnt p2, gp_Pnt p3, gp_Pnt p4, gp_Pnt p5, std::vector<gp_Pnt> &pvec, double &ltot){

    int type0=draw_primitives::get_shape_type(p0,p1,p2);
    int type1=draw_primitives::get_shape_type(p3,p4,p5);

    // std::cout<<"shapetype0:"<<type0<<std::endl;
    // std::cout<<"shapetype1:"<<type1<<std::endl;

    if(type0==draw_primitives::point || type0==draw_primitives::circle || type0==draw_primitives::unknown){
        return 0;
    }
    if(type1==draw_primitives::point || type1==draw_primitives::circle || type1==draw_primitives::unknown){
        return 0;
    }

    double theta0=0, theta1=0, dir0=0, dir1=0, kappa0=0, kappa1=0;

    // Shape0
    if(type0==draw_primitives::line){ // Line.
        theta0=draw_primitives::get_2d_line_angle_xy(p0, p2);
        kappa0=0;
    }
    if(type0==draw_primitives::arc){ // Arc.
        theta0=draw_primitives::get_2d_arc_end_angle_xy(p0, p1, p2);
        dir0=draw_primitives::get_2d_arc_direction_xy(p0,p1,p2);
        if(dir0==-1){ // cw.
            theta0+=0.5*M_PI;
        }
        if(dir0==1){ // ccw.
            theta0-=0.5*M_PI;
        }
        kappa0=1/draw_primitives::get_2d_arc_radius_xy(p0,p1,p2);
    }

    // Shape1
    if(type1==draw_primitives::line){ // Line.
        theta1=draw_primitives::get_2d_line_angle_xy(p3, p5);
        kappa1=0;
    }
    if(type1==draw_primitives::arc){ // Arc.
        theta1=draw_primitives::get_2d_arc_start_angle_xy(p3, p4, p5);
        dir1=draw_primitives::get_2d_arc_direction_xy(p3,p4,p5);
        if(dir1==-1){ // cw.
            theta1-=0.5*M_PI;
        }
        if(dir1==1){ // ccw.
            theta1+=0.5*M_PI;
        }
        kappa1=1/draw_primitives::get_2d_arc_radius_xy(p3,p4,p5);
    }

    // Construct the tri-clothoid.
    int r=draw_2d_clothoid_3arc_G2_xy(p2, p3, theta0, theta1,  kappa0, kappa1, pvec, ltot);
    return r;
}

int draw_clothoids::interpolate_inbetween_2d_clothoid_3arc_G2_xy(gp_Pnt p0, gp_Pnt p1, gp_Pnt p2, gp_Pnt p3, gp_Pnt p4, gp_Pnt p5, double progress, gp_Pnt &pi){

    int type0=draw_primitives::get_shape_type(p0,p1,p2);
    int type1=draw_primitives::get_shape_type(p3,p4,p5);

    // std::cout<<"shapetype0:"<<type0<<std::endl;
    // std::cout<<"shapetype1:"<<type1<<std::endl;

    if(type0==draw_primitives::point || type0==draw_primitives::circle || type0==draw_primitives::unknown){
        return 0;
    }
    if(type1==draw_primitives::point || type1==draw_primitives::circle || type1==draw_primitives::unknown){
        return 0;
    }

    double theta0=0, theta1=0, dir0=0, dir1=0, kappa0=0, kappa1=0;

    // Shape0
    if(type0==draw_primitives::line){ // Line.
        theta0=draw_primitives::get_2d_line_angle_xy(p0, p2);
        kappa0=0;
    }
    if(type0==draw_primitives::arc){ // Arc.
        theta0=draw_primitives::get_2d_arc_end_angle_xy(p0, p1, p2);
        dir0=draw_primitives::get_2d_arc_direction_xy(p0,p1,p2);
        if(dir0==-1){ // cw.
            theta0+=0.5*M_PI;
        }
        if(dir0==1){ // ccw.
            theta0-=0.5*M_PI;
        }
        kappa0=1/draw_primitives::get_2d_arc_radius_xy(p0,p1,p2);
    }

    // Shape1
    if(type1==draw_primitives::line){ // Line.
        theta1=draw_primitives::get_2d_line_angle_xy(p3, p5);
        kappa1=0;
    }
    if(type1==draw_primitives::arc){ // Arc.
        theta1=draw_primitives::get_2d_arc_start_angle_xy(p3, p4, p5);
        dir1=draw_primitives::get_2d_arc_direction_xy(p3,p4,p5);
        if(dir1==-1){ // cw.
            theta1-=0.5*M_PI;
        }
        if(dir1==1){ // ccw.
            theta1+=0.5*M_PI;
        }
        kappa1=1/draw_primitives::get_2d_arc_radius_xy(p3,p4,p5);
    }

    // Construct the tri-clothoid.
    int r=interpolate_2d_clothoid_3arc_G2_xy(p2, p3, theta0, theta1,  kappa0, kappa1,progress,pi);
    // int r=draw_2d_clothoid_3arc_G2_xy(p2, p3, theta0, theta1,  kappa0, kappa1, pvec, ltot);
    return r;
}


int draw_clothoids::draw_inbetween_2d_clothoid_3arc_G2_xz(gp_Pnt p0, gp_Pnt p1, gp_Pnt p2, gp_Pnt p3, gp_Pnt p4, gp_Pnt p5, std::vector<gp_Pnt> &pvec, double &ltot){

    int type0=draw_primitives::get_shape_type(p0,p1,p2);
    int type1=draw_primitives::get_shape_type(p3,p4,p5);

    // std::cout<<"shapetype0:"<<type0<<std::endl;
    // std::cout<<"shapetype1:"<<type1<<std::endl;

    if(type0==draw_primitives::point || type0==draw_primitives::circle || type0==draw_primitives::unknown){
        return 0;
    }
    if(type1==draw_primitives::point || type1==draw_primitives::circle || type1==draw_primitives::unknown){
        return 0;
    }

    double theta0=0, theta1=0, dir0=0, dir1=0, kappa0=0, kappa1=0;

    // Shape0
    if(type0==draw_primitives::line){ // Line.
        theta0=draw_primitives::get_2d_line_angle_xz(p0, p2);
        kappa0=0;
    }
    if(type0==draw_primitives::arc){ // Arc.
        theta0=draw_primitives::get_2d_arc_end_angle_xz(p0, p1, p2);
        dir0=draw_primitives::get_2d_arc_direction_xz(p0,p1,p2);
        if(dir0==-1){ // cw.
            theta0+=0.5*M_PI;
        }
        if(dir0==1){ // ccw.
            theta0-=0.5*M_PI;
        }
        kappa0=1/draw_primitives::get_2d_arc_radius_xz(p0,p1,p2);
    }

    // Shape1
    if(type1==draw_primitives::line){ // Line.
        theta1=draw_primitives::get_2d_line_angle_xz(p3, p5);
        kappa1=0;
    }
    if(type1==draw_primitives::arc){ // Arc.
        theta1=draw_primitives::get_2d_arc_start_angle_xz(p3, p4, p5);
        dir1=draw_primitives::get_2d_arc_direction_xz(p3,p4,p5);
        if(dir1==-1){ // cw.
            theta1-=0.5*M_PI;
        }
        if(dir1==1){ // ccw.
            theta1+=0.5*M_PI;
        }
        kappa1=1/draw_primitives::get_2d_arc_radius_xz(p3,p4,p5);
    }

    // Construct the tri-clothoid.
    int r=draw_2d_clothoid_3arc_G2_xz(p2, p3, theta0, theta1,  kappa0, kappa1, pvec, ltot);
    return r;
}

int draw_clothoids::interpolate_inbetween_2d_clothoid_3arc_G2_xz(gp_Pnt p0, gp_Pnt p1, gp_Pnt p2, gp_Pnt p3, gp_Pnt p4, gp_Pnt p5, double progress, gp_Pnt &pi){

    int type0=draw_primitives::get_shape_type(p0,p1,p2);
    int type1=draw_primitives::get_shape_type(p3,p4,p5);

    // std::cout<<"shapetype0:"<<type0<<std::endl;
    // std::cout<<"shapetype1:"<<type1<<std::endl;

    if(type0==draw_primitives::point || type0==draw_primitives::circle || type0==draw_primitives::unknown){
        return 0;
    }
    if(type1==draw_primitives::point || type1==draw_primitives::circle || type1==draw_primitives::unknown){
        return 0;
    }

    double theta0=0, theta1=0, dir0=0, dir1=0, kappa0=0, kappa1=0;

    // Shape0
    if(type0==draw_primitives::line){ // Line.
        theta0=draw_primitives::get_2d_line_angle_xz(p0, p2);
        kappa0=0;
    }
    if(type0==draw_primitives::arc){ // Arc.
        theta0=draw_primitives::get_2d_arc_end_angle_xz(p0, p1, p2);
        dir0=draw_primitives::get_2d_arc_direction_xz(p0,p1,p2);
        if(dir0==-1){ // cw.
            theta0+=0.5*M_PI;
        }
        if(dir0==1){ // ccw.
            theta0-=0.5*M_PI;
        }
        kappa0=1/draw_primitives::get_2d_arc_radius_xz(p0,p1,p2);
    }

    // Shape1
    if(type1==draw_primitives::line){ // Line.
        theta1=draw_primitives::get_2d_line_angle_xz(p3, p5);
        kappa1=0;
    }
    if(type1==draw_primitives::arc){ // Arc.
        theta1=draw_primitives::get_2d_arc_start_angle_xz(p3, p4, p5);
        dir1=draw_primitives::get_2d_arc_direction_xz(p3,p4,p5);
        if(dir1==-1){ // cw.
            theta1-=0.5*M_PI;
        }
        if(dir1==1){ // ccw.
            theta1+=0.5*M_PI;
        }
        kappa1=1/draw_primitives::get_2d_arc_radius_xz(p3,p4,p5);
    }

    // Construct the tri-clothoid.
    int r=interpolate_2d_clothoid_3arc_G2_xz(p2, p3, theta0, theta1,  kappa0, kappa1, progress, pi);
    // int r=draw_2d_clothoid_3arc_G2_xz(p2, p3, theta0, theta1,  kappa0, kappa1, pvec, ltot);
    return r;
}
int draw_clothoids::draw_inbetween_3d_clothoid_3arc_G2(gp_Pnt &p0, gp_Pnt &p1, gp_Pnt &p2,  gp_Pnt &p3, gp_Pnt &p4, gp_Pnt &p5, std::vector<gp_Pnt> &pvec){

    int type0=draw_primitives::get_shape_type(p0,p1,p2);
    int type1=draw_primitives::get_shape_type(p3,p4,p5);

    // std::cout<<"shapetype0:"<<type0<<std::endl;
    // std::cout<<"shapetype1:"<<type1<<std::endl;

    if(type0==draw_primitives::point || type0==draw_primitives::circle || type0==draw_primitives::unknown){
        return 0;
    }
    if(type1==draw_primitives::point || type1==draw_primitives::circle || type1==draw_primitives::unknown){
        return 0;
    }

    gp_Pln plane3d;
    if(!draw_primitives::create_3d_plane(p0,p2,p4,plane3d)){
        pvec={p2,p3};
        return 1;
    }
    gp_Pln plane2d=draw_primitives::align_plane_to_origin(plane3d);

    draw_primitives::port_point_between_planes(plane3d,plane2d,p0);
    draw_primitives::port_point_between_planes(plane3d,plane2d,p1);
    draw_primitives::port_point_between_planes(plane3d,plane2d,p2);
    draw_primitives::port_point_between_planes(plane3d,plane2d,p3);
    draw_primitives::port_point_between_planes(plane3d,plane2d,p4);
    draw_primitives::port_point_between_planes(plane3d,plane2d,p5);

    double ltot;
    int r=draw_inbetween_2d_clothoid_3arc_G2_xy(p0,p1,p2,p3,p4,p5,pvec,ltot);
    draw_primitives::port_points_between_planes(plane2d,plane3d,pvec);

    return r;
}

int draw_clothoids::draw_inbetween_3d_clothoid_3arc_G2_non_planar(
    gp_Pnt &p0, gp_Pnt &p1, gp_Pnt &p2, gp_Pnt &p3, gp_Pnt &p4, gp_Pnt &p5,
    std::vector<gp_Pnt> &pvec0, std::vector<gp_Pnt> &pvec1, std::vector<gp_Pnt> &pvec2) {

    // Create 2 clothoids, one on xy plane, one on xz plane.
    double ltot0, ltot1;
    gp_Pnt pi0, pi1;

    // Generate first clothoid on xy plane.
    int r = draw_inbetween_2d_clothoid_3arc_G2_xy(p0, p1, p2, p3, p4, p5, pvec0, ltot0);
    if (r == 0) {
        return 0; // Early return if generation failed.
    }

    // Check which direction has the most length, x or y, for the first clothoid.
    double xdiff = 0, ydiff = 0;

    if (!pvec0.empty()) {
        double x0 = pvec0.front().X();
        double x1 = pvec0.back().X();
        xdiff = fabs(x1 - x0);

        double y0 = pvec0.front().Y();
        double y1 = pvec0.back().Y();
        ydiff = fabs(y1 - y0);
    }

    // Generate second clothoid on xz plane.
    r = draw_inbetween_2d_clothoid_3arc_G2_xz(p0, p1, p2, p3, p4, p5, pvec1, ltot1);
    if (r == 0) {
        return 0; // Early return if generation failed.
    }

    // Number of segments for interpolation.
    const int segments = 50;
    const int cycles = 1000;

    for (int i = 0; i <= segments; i++) {
        double progress0 = static_cast<double>(i) / segments;

        interpolate_inbetween_2d_clothoid_3arc_G2_xy(p0, p1, p2, p3, p4, p5, progress0, pi0);

        if (xdiff > ydiff) {
            double x = pi0.X();
            // Find nearest x in xz plane clothoid.
            for (int j = 0; j <= cycles; j++) {
                double progress1 = static_cast<double>(j) / cycles;
                interpolate_inbetween_2d_clothoid_3arc_G2_xz(p0, p1, p2, p3, p4, p5, progress1, pi1);
                if (pi1.X() >= x) {
                    break;
                }
            }
            pvec2.push_back(gp_Pnt(pi0.X(), pi0.Y(), pi1.Z()));
        } else {
            double y = pi0.Y();
            // Find nearest y in xz plane clothoid.
            for (int j = 0; j <= cycles; j++) {
                double progress1 = static_cast<double>(j) / cycles;
                interpolate_inbetween_2d_clothoid_3arc_G2_xz(p0, p1, p2, p3, p4, p5, progress1, pi1);
                if (pi1.Y() >= y) {
                    break;
                }
            }
            pvec2.push_back(gp_Pnt(pi0.X(), pi0.Y(), pi1.Z()));
        }
    }

    return 1; // Assuming 1 means success in this context.
}































