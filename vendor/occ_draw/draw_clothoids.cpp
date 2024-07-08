#include "draw_clothoids.h"

draw_clothoids::draw_clothoids(){ }

int draw_clothoids::draw_2d_clothoid_3arc_G2_xy(const gp_Pnt &p0, const gp_Pnt &p1, const  double &theta0, const double &theta1, const double &kappa0, const double &kappa1,
                                                const int &segments, std::vector<gp_Pnt> &pvec, double &ltot){

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

int draw_clothoids::draw_2d_clothoid_3arc_G2_xz(const gp_Pnt &p0, const gp_Pnt &p1, const double &theta0, const double &theta1, const double &kappa0, const double &kappa1,
                                                const int &segments, std::vector<gp_Pnt> &pvec, double &ltot){

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

int draw_clothoids::draw_2d_clothoid_3arc_G2_yz(const gp_Pnt &p0, const gp_Pnt &p1, const double &theta0, const double &theta1, const double &kappa0, const double &kappa1,
                                                const int &segments, std::vector<gp_Pnt> &pvec, double &ltot){

    //std::vector<gp_Pnt> pvec;
    G2lib::G2solve3arc g2solve3arc;

    g2solve3arc.setTolerance(1e-6);
    g2solve3arc.setMaxIter(10);

    G2lib::real_type y0  = p0.Y();
    G2lib::real_type z0  = p0.Z();
    G2lib::real_type th0 = theta0;
    G2lib::real_type k0  = kappa0;
    G2lib::real_type y1  = p1.Y();
    G2lib::real_type z1  = p1.Z();
    G2lib::real_type th1 = theta1;
    G2lib::real_type k1  = kappa1;

    int iter = g2solve3arc.build( y0, z0, th0, k0, y1, z1, th1, k1 );
    if(iter==-1){
        std::cout<<"clothoid terminated."<<std::endl;
        return 0;
    }

    G2lib::ClothoidCurve const & S0 = g2solve3arc.getS0();
    G2lib::ClothoidCurve const & S1 = g2solve3arc.getS1();
    G2lib::ClothoidCurve const & SM = g2solve3arc.getSM();

    ltot= g2solve3arc.totalLength();

    if(ltot==0){
        return 0;
    }

    int cycles = segments+1;
    double increment = ltot / segments;

    for (int cycle = 0; cycle < cycles; ++cycle) {
        double i = cycle * increment;
        pvec.push_back({0, g2solve3arc.X(i), g2solve3arc.Y(i)});
    }
    return 1;
}

int draw_clothoids::interpolate_2d_clothoid_3arc_G2_xy(const gp_Pnt &p0, const gp_Pnt &p1, const double &theta0, const double &theta1, const double &kappa0, const double &kappa1,
                                                       const double &progress, gp_Pnt &pi){

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

int draw_clothoids::interpolate_2d_clothoid_3arc_G2_xz(const gp_Pnt &p0, const gp_Pnt &p1, const double &theta0, const double &theta1, const double &kappa0, const double &kappa1,
                                                       const double &progress, gp_Pnt &pi){

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

int draw_clothoids::interpolate_2d_clothoid_3arc_G2_yz(const gp_Pnt &p0, const gp_Pnt &p1, const double &theta0, const double &theta1, const double &kappa0, const double &kappa1,
                                                       const double &progress, gp_Pnt &pi){

    //std::vector<gp_Pnt> pvec;
    G2lib::G2solve3arc g2solve3arc;

    g2solve3arc.setTolerance(1e-6);
    g2solve3arc.setMaxIter(10);

    G2lib::real_type y0  = p0.Y();
    G2lib::real_type z0  = p0.Z();
    G2lib::real_type th0 = theta0;
    G2lib::real_type k0  = kappa0;
    G2lib::real_type y1  = p1.Y();
    G2lib::real_type z1  = p1.Z();
    G2lib::real_type th1 = theta1;
    G2lib::real_type k1  = kappa1;

    int iter = g2solve3arc.build( y0, z0, th0, k0, y1, z1, th1, k1 );
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
    pi={0, g2solve3arc.X(i), g2solve3arc.Y(i)};

    return 1;
}

int draw_clothoids::draw_inbetween_2d_clothoid_3arc_G2_xy(const gp_Pnt &p0, const gp_Pnt &p1, const gp_Pnt &p2, const gp_Pnt &p3, const gp_Pnt &p4, const gp_Pnt &p5,
                                                          const int &segments, std::vector<gp_Pnt> &pvec, double &ltot){

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
    int r=draw_2d_clothoid_3arc_G2_xy(p2, p3, theta0, theta1,  kappa0, kappa1, segments, pvec, ltot);
    return r;
}

int draw_clothoids::interpolate_inbetween_2d_clothoid_3arc_G2_xy(const gp_Pnt &p0, const gp_Pnt &p1, const gp_Pnt &p2, const gp_Pnt &p3, const gp_Pnt &p4, const gp_Pnt &p5, const double &progress, gp_Pnt &pi){

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
    int r=interpolate_2d_clothoid_3arc_G2_xy(p2, p3, theta0, theta1, kappa0, kappa1,progress,pi);
    // int r=draw_2d_clothoid_3arc_G2_xy(p2, p3, theta0, theta1,  kappa0, kappa1, pvec, ltot);
    return r;
}

int draw_clothoids::draw_inbetween_2d_clothoid_3arc_G2_xz(const gp_Pnt &p0, const gp_Pnt &p1, const gp_Pnt &p2, const gp_Pnt &p3, const gp_Pnt &p4, const gp_Pnt &p5,
                                                          const int &segments, std::vector<gp_Pnt> &pvec, double &ltot){

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
    int r=draw_2d_clothoid_3arc_G2_xz(p2, p3, theta0, theta1,  kappa0, kappa1, segments, pvec, ltot);
    return r;
}

int draw_clothoids::interpolate_inbetween_2d_clothoid_3arc_G2_xz(const gp_Pnt &p0, const gp_Pnt &p1, const gp_Pnt &p2, const gp_Pnt &p3, const gp_Pnt &p4, const gp_Pnt &p5, const double &progress, gp_Pnt &pi){

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

int draw_clothoids::draw_inbetween_2d_clothoid_3arc_G2_yz(const gp_Pnt &p0, const gp_Pnt &p1, const gp_Pnt &p2, const gp_Pnt &p3, const gp_Pnt &p4, const gp_Pnt &p5,
                                                          const int &segments, std::vector<gp_Pnt> &pvec, double &ltot){

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
        theta0=draw_primitives::get_2d_line_angle_yz(p0, p2);
        kappa0=0;
    }
    if(type0==draw_primitives::arc){ // Arc.
        theta0=draw_primitives::get_2d_arc_end_angle_yz(p0, p1, p2);
        dir0=draw_primitives::get_2d_arc_direction_yz(p0,p1,p2);
        if(dir0==-1){ // cw.
            theta0+=0.5*M_PI;
        }
        if(dir0==1){ // ccw.
            theta0-=0.5*M_PI;
        }
        kappa0=1/draw_primitives::get_2d_arc_radius_yz(p0,p1,p2);
    }

    // Shape1
    if(type1==draw_primitives::line){ // Line.
        theta1=draw_primitives::get_2d_line_angle_yz(p3, p5);
        kappa1=0;
    }
    if(type1==draw_primitives::arc){ // Arc.
        theta1=draw_primitives::get_2d_arc_start_angle_yz(p3, p4, p5);
        dir1=draw_primitives::get_2d_arc_direction_yz(p3,p4,p5);
        if(dir1==-1){ // cw.
            theta1-=0.5*M_PI;
        }
        if(dir1==1){ // ccw.
            theta1+=0.5*M_PI;
        }
        kappa1=1/draw_primitives::get_2d_arc_radius_yz(p3,p4,p5);
    }

    // Construct the tri-clothoid.
    int r=draw_2d_clothoid_3arc_G2_yz(p2, p3, theta0, theta1,  kappa0, kappa1, segments, pvec, ltot);
    return r;
}

int draw_clothoids::interpolate_inbetween_2d_clothoid_3arc_G2_yz(const gp_Pnt &p0, const gp_Pnt &p1, const gp_Pnt &p2, const gp_Pnt &p3, const gp_Pnt &p4, const gp_Pnt &p5, const double &progress, gp_Pnt &pi){

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
        theta0=draw_primitives::get_2d_line_angle_yz(p0, p2);
        kappa0=0;
    }
    if(type0==draw_primitives::arc){ // Arc.
        theta0=draw_primitives::get_2d_arc_end_angle_yz(p0, p1, p2);
        dir0=draw_primitives::get_2d_arc_direction_yz(p0,p1,p2);
        if(dir0==-1){ // cw.
            theta0+=0.5*M_PI;
        }
        if(dir0==1){ // ccw.
            theta0-=0.5*M_PI;
        }
        kappa0=1/draw_primitives::get_2d_arc_radius_yz(p0,p1,p2);
    }

    // Shape1
    if(type1==draw_primitives::line){ // Line.
        theta1=draw_primitives::get_2d_line_angle_yz(p3, p5);
        kappa1=0;
    }
    if(type1==draw_primitives::arc){ // Arc.
        theta1=draw_primitives::get_2d_arc_start_angle_yz(p3, p4, p5);
        dir1=draw_primitives::get_2d_arc_direction_yz(p3,p4,p5);
        if(dir1==-1){ // cw.
            theta1-=0.5*M_PI;
        }
        if(dir1==1){ // ccw.
            theta1+=0.5*M_PI;
        }
        kappa1=1/draw_primitives::get_2d_arc_radius_yz(p3,p4,p5);
    }

    // Construct the tri-clothoid.
    int r=interpolate_2d_clothoid_3arc_G2_yz(p2, p3, theta0, theta1,  kappa0, kappa1, progress, pi);
    // int r=draw_2d_clothoid_3arc_G2_xz(p2, p3, theta0, theta1,  kappa0, kappa1, pvec, ltot);
    return r;
}

int draw_clothoids::draw_inbetween_3d_clothoid_3arc_G2(const gp_Pnt &p0, const gp_Pnt &p1, const gp_Pnt &p2,  const gp_Pnt &p3, const gp_Pnt &p4, const gp_Pnt &p5,
                                                       const int &segments, std::vector<gp_Pnt> &pvec){

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

    gp_Pnt p0_=p0; // To non const.
    gp_Pnt p1_=p1;
    gp_Pnt p2_=p2;
    gp_Pnt p3_=p3;
    gp_Pnt p4_=p4;
    gp_Pnt p5_=p5;

    draw_primitives::port_point_between_planes(plane3d,plane2d,p0_);
    draw_primitives::port_point_between_planes(plane3d,plane2d,p1_);
    draw_primitives::port_point_between_planes(plane3d,plane2d,p2_);
    draw_primitives::port_point_between_planes(plane3d,plane2d,p3_);
    draw_primitives::port_point_between_planes(plane3d,plane2d,p4_);
    draw_primitives::port_point_between_planes(plane3d,plane2d,p5_);

    double ltot;
    int r=draw_inbetween_2d_clothoid_3arc_G2_xy(p0_,p1_,p2_,p3_,p4_,p5_,segments,pvec,ltot);
    draw_primitives::port_points_between_planes(plane2d,plane3d,pvec);

    return r;
}


/* Example usage :

    // Draw first line.
    gp_Pnt p0={50,50,50};
    gp_Pnt p2={75,75,60};
    gp_Pnt p1=draw_primitives::get_line_midpoint(p0,p2);
    occ->add_shapevec( draw_primitives::colorize( draw_primitives::draw_3d_line(p0,p2),Quantity_NOC_ALICEBLUE,0));

    // Draw second line.
    gp_Pnt p3={100,100,60};
    gp_Pnt p5={120,80,40};
    gp_Pnt p4=draw_primitives::get_line_midpoint(p3,p5);
    occ->add_shapevec( draw_primitives::colorize( draw_primitives::draw_3d_line(p3,p5),Quantity_NOC_ALICEBLUE,0));

    // Construct 3d clothoid.
    // pvec0 = projection on xy plane.
    // pvec1 = projection on xz plane.
    // pvec2 = projection 3d.
    int segments=50;
    std::vector<gp_Pnt> pvec0,pvec1,pvec2;
    draw_clothoids::draw_inbetween_3d_clothoid_3arc_G2_non_planar(p0,p1,p2,p3,p4,p5,segments,pvec0,pvec1,pvec2);
    occ->add_shapevec(draw_primitives::draw_3d_line_wire_low_memory_usage(pvec0));
    occ->add_shapevec(draw_primitives::draw_3d_line_wire_low_memory_usage(pvec1));
    occ->add_shapevec(draw_primitives::draw_3d_line_wire_low_memory_usage(pvec2));
*/

 #include <GeomAPI_ExtremaCurveCurve.hxx>
#include <GeomAPI_PointsToBSpline.hxx>
#include <Geom_BSplineCurve.hxx>
#include <TColgp_Array1OfPnt.hxx>
#include <Precision.hxx>
#include <iostream>

int draw_clothoids::draw_inbetween_3d_clothoid_3arc_G2_non_planar(
        const gp_Pnt &p0, const gp_Pnt &p1, const gp_Pnt &p2, const gp_Pnt &p3, const gp_Pnt &p4, const gp_Pnt &p5, const int &segments,
        std::vector<gp_Pnt> &pvec0, std::vector<gp_Pnt> &pvec1, std::vector<gp_Pnt> &pvec2, std::vector<gp_Pnt> &pvec3) {

    // Generate first clothoid on XY plane.
    double ltot0, ltot1, ltot2;
    draw_inbetween_2d_clothoid_3arc_G2_xy(p0, p1, p2, p3, p4, p5, segments, pvec0, ltot0);

    // Generate second clothoid on XZ plane.
    draw_inbetween_2d_clothoid_3arc_G2_xz(p0, p1, p2, p3, p4, p5, segments, pvec1, ltot1);

    // Generate third clothoid on YZ plane.
    draw_inbetween_2d_clothoid_3arc_G2_yz(p0, p1, p2, p3, p4, p5, segments, pvec2, ltot2);

    // Convert std::vector to TColgp_Array1OfPnt for pvec0
    TColgp_Array1OfPnt array3D_XY(1, static_cast<Standard_Integer>(pvec0.size()));
    for (Standard_Integer i = 0; i < pvec0.size(); ++i) {
        array3D_XY.SetValue(i + 1, pvec0[i]);
    }

    // Convert std::vector to TColgp_Array1OfPnt for pvec1
    TColgp_Array1OfPnt array3D_XZ(1, static_cast<Standard_Integer>(pvec1.size()));
    for (Standard_Integer i = 0; i < pvec1.size(); ++i) {
        array3D_XZ.SetValue(i + 1, pvec1[i]);
    }

    // Print the contents of the arrays to confirm values
    std::cout << "Points in array3D_XY:" << std::endl;
    for (Standard_Integer i = 1; i <= array3D_XY.Length(); ++i) {
        gp_Pnt p = array3D_XY.Value(i);
        std::cout << "Point " << i << ": (" << p.X() << ", " << p.Y() << ", " << p.Z() << ")" << std::endl;
    }

    std::cout << "Points in array3D_XZ:" << std::endl;
    for (Standard_Integer i = 1; i <= array3D_XZ.Length(); ++i) {
        gp_Pnt p = array3D_XZ.Value(i);
        std::cout << "Point " << i << ": (" << p.X() << ", " << p.Y() << ", " << p.Z() << ")" << std::endl;
    }

    // Convert the points to B-Spline curves
    Handle(Geom_BSplineCurve) curve3D_XY = GeomAPI_PointsToBSpline(array3D_XY).Curve();
    Handle(Geom_BSplineCurve) curve3D_XZ = GeomAPI_PointsToBSpline(array3D_XZ).Curve();

    if (curve3D_XY.IsNull() || curve3D_XZ.IsNull()) {
        std::cerr << "Failed to create B-Spline curves." << std::endl;
        return 0;
    }

    // Evaluate points on the B-Spline curves and store in pvec3
    Standard_Real firstParamXY = curve3D_XY->FirstParameter();
    Standard_Real lastParamXY = curve3D_XY->LastParameter();
    Standard_Real firstParamXZ = curve3D_XZ->FirstParameter();
    Standard_Real lastParamXZ = curve3D_XZ->LastParameter();

    Standard_Integer numPoints = 100; // Number of points to evaluate on the curve
    for (Standard_Integer i = 0; i <= numPoints; ++i) {
        Standard_Real paramXY = firstParamXY + (lastParamXY - firstParamXY) * (static_cast<Standard_Real>(i) / numPoints);
        Standard_Real paramXZ = firstParamXZ + (lastParamXZ - firstParamXZ) * (static_cast<Standard_Real>(i) / numPoints);

        gp_Pnt pointXY, pointXZ;
        curve3D_XY->D0(paramXY, pointXY);
        curve3D_XZ->D0(paramXZ, pointXZ);

        // Store the evaluated points in pvec3
        pvec3.push_back(gp_Pnt(pointXY.X(), pointXY.Y(), pointXZ.Z()));
    }

    // Print the evaluated points in pvec3
    std::cout << "Evaluated points in pvec3:" << std::endl;
    for (const auto &p : pvec3) {
        std::cout << "Point: (" << p.X() << ", " << p.Y() << ", " << p.Z() << ")" << std::endl;
    }

    return 1; // Success
}

/* Example usage:

    gp_Pnt p0={50,50,50};
    gp_Pnt p2={75,75,60};
    gp_Pnt p1=draw_primitives::get_line_midpoint(p0,p2);
    occ->add_shapevec( draw_primitives::colorize( draw_primitives::draw_3d_line(p0,p2),Quantity_NOC_ALICEBLUE,0));

    gp_Pnt p3={100,100,60};
    gp_Pnt p5={120,80,40};
    gp_Pnt p4=draw_primitives::get_line_midpoint(p3,p5);
    occ->add_shapevec( draw_primitives::colorize( draw_primitives::draw_3d_line(p3,p5),Quantity_NOC_ALICEBLUE,0));

    std::vector<gp_Pnt> pvec;
    draw_clothoids::draw_inbetween_3d_clothoid_3arc_G2_non_planar(p0,p1,p2,p3,p4,p5,100,pvec);
    occ->add_shapevec(draw_primitives::draw_3d_line_wire_low_memory_usage(pvec));

*/
int draw_clothoids::draw_inbetween_3d_clothoid_3arc_G2_non_planar(
        const gp_Pnt &p0, const gp_Pnt &p1, const gp_Pnt &p2, const gp_Pnt &p3, const gp_Pnt &p4, const gp_Pnt &p5,
        const int &segments, std::vector<gp_Pnt> &pvec) {

    // Create 2 clothoids, one on xy plane, one on xz plane.
    double ltot0, ltot1;
    std::vector<gp_Pnt> pvec0,pvec1;

    // Generate first clothoid on xy plane.
    int r = draw_inbetween_2d_clothoid_3arc_G2_xy(p0, p1, p2, p3, p4, p5, segments, pvec0, ltot0);
    if (r == 0) {
        return 0; // Early return if generation failed.
    }

    // Generate second clothoid on xz plane.
    r = draw_inbetween_2d_clothoid_3arc_G2_xz(p0, p1, p2, p3, p4, p5, segments, pvec1, ltot1);
    if (r == 0) {
        return 0; // Early return if generation failed.
    }

    for (int i=0; i<pvec0.size(); i++) {
        pvec.push_back({pvec0[i].X(), pvec0[i].Y(), pvec1[i].Z()});
    }
    return 1; // Assuming 1 means success in this context.
}

























