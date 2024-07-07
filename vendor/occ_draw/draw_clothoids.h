#ifndef DRAW_CLOTHOIDS_H
#define DRAW_CLOTHOIDS_H

#include "draw_primitives.h"
#include "Clothoids.hh"

class draw_clothoids
{
public:
    draw_clothoids();

    struct clothoid {
        gp_Pnt p1,p2;
        double theta0,theta1,kappa0,kappa1;
        double lenght;
    };

    // 2d
    static int draw_2d_clothoid_3arc_G2_xy(gp_Pnt p0, gp_Pnt p1, double theta0, double theta1, double kappa0, double kappa1, std::vector<gp_Pnt> &pvec, double &ltot);
    static int draw_2d_clothoid_3arc_G2_xz(gp_Pnt p0, gp_Pnt p1, double theta0, double theta1, double kappa0, double kappa1,std::vector<gp_Pnt> &pvec, double &ltot);

    static int interpolate_2d_clothoid_3arc_G2_xy(gp_Pnt p0, gp_Pnt p1, double theta0, double theta1, double kappa0, double kappa1, double progress, gp_Pnt &pi);
    static int interpolate_2d_clothoid_3arc_G2_xz(gp_Pnt p0, gp_Pnt p1, double theta0, double theta1, double kappa0, double kappa1, double progress, gp_Pnt &pi);

    // 2d
    static int draw_inbetween_2d_clothoid_3arc_G2_xy(gp_Pnt p0, gp_Pnt p1, gp_Pnt p2, gp_Pnt p3, gp_Pnt p4, gp_Pnt p5, std::vector<gp_Pnt> &pvec, double &ltot);
    static int draw_inbetween_2d_clothoid_3arc_G2_xz(gp_Pnt p0, gp_Pnt p1, gp_Pnt p2, gp_Pnt p3, gp_Pnt p4, gp_Pnt p5, std::vector<gp_Pnt> &pvec, double &ltot);

    static int interpolate_inbetween_2d_clothoid_3arc_G2_xy(gp_Pnt p0, gp_Pnt p1, gp_Pnt p2, gp_Pnt p3, gp_Pnt p4, gp_Pnt p5, double progress, gp_Pnt &pi);
    static int interpolate_inbetween_2d_clothoid_3arc_G2_xz(gp_Pnt p0, gp_Pnt p1, gp_Pnt p2, gp_Pnt p3, gp_Pnt p4, gp_Pnt p5, double progress, gp_Pnt &pi);

    // 3d on a plane
    static int draw_inbetween_3d_clothoid_3arc_G2(gp_Pnt &p0, gp_Pnt &p1, gp_Pnt &p2, gp_Pnt &p3, gp_Pnt &p4, gp_Pnt &p5, std::vector<gp_Pnt> &pvec);

    //3d out of plane. Designed by skynet cyberdyne.
    static int draw_inbetween_3d_clothoid_3arc_G2_non_planar(gp_Pnt &p0, gp_Pnt &p1, gp_Pnt &p2, gp_Pnt &p3, gp_Pnt &p4, gp_Pnt &p5,
                                                             std::vector<gp_Pnt> &pvec0, std::vector<gp_Pnt> &pvec1, std::vector<gp_Pnt> &pvec2);
};

#endif // DRAW_CLOTHOIDS_H




















