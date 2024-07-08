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
    static int draw_2d_clothoid_3arc_G2_xy(const gp_Pnt &p0, const gp_Pnt &p1, const double &theta0, const double &theta1, const double &kappa0, const double &kappa1,
                                           const int &segments, std::vector<gp_Pnt> &pvec, double &ltot);
    static int draw_2d_clothoid_3arc_G2_xz(const gp_Pnt &p0, const gp_Pnt &p1, const double &theta0, const double &theta1, const double &kappa0, const double &kappa1,
                                           const int &segments, std::vector<gp_Pnt> &pvec, double &ltot);
    static int draw_2d_clothoid_3arc_G2_yz(const gp_Pnt &p0, const gp_Pnt &p1, const double &theta0, const double &theta1, const double &kappa0, const double &kappa1,
                                           const int &segments, std::vector<gp_Pnt> &pvec, double &ltot);

    static int interpolate_2d_clothoid_3arc_G2_xy(const gp_Pnt &p0, const gp_Pnt &p1, const double &theta0, const double &theta1, const double &kappa0, const double &kappa1,
                                                  const double &progress, gp_Pnt &pi);
    static int interpolate_2d_clothoid_3arc_G2_xz(const gp_Pnt &p0, const gp_Pnt &p1, const double &theta0, const double &theta1, const double &kappa0, const double &kappa1,
                                                  const double &progress, gp_Pnt &pi);
    static int interpolate_2d_clothoid_3arc_G2_yz(const gp_Pnt &p0, const gp_Pnt &p1, const double &theta0, const double &theta1, const double &kappa0, const double &kappa1,
                                                  const double &progress, gp_Pnt &pi);

    // 2d
    static int draw_inbetween_2d_clothoid_3arc_G2_xy(const gp_Pnt &p0, const gp_Pnt &p1, const gp_Pnt &p2, const gp_Pnt &p3, const gp_Pnt &p4, const gp_Pnt &p5,
                                                     const int &segments,
                                                     std::vector<gp_Pnt> &pvec, double &ltot);
    static int draw_inbetween_2d_clothoid_3arc_G2_xz(const gp_Pnt &p0, const gp_Pnt &p1, const gp_Pnt &p2, const gp_Pnt &p3, const gp_Pnt &p4, const gp_Pnt &p5,
                                                     const int &segments,
                                                     std::vector<gp_Pnt> &pvec, double &ltot);
    static int draw_inbetween_2d_clothoid_3arc_G2_yz(const gp_Pnt &p0, const gp_Pnt &p1, const gp_Pnt &p2, const gp_Pnt &p3, const gp_Pnt &p4, const gp_Pnt &p5,
                                                     const int &segments,
                                                     std::vector<gp_Pnt> &pvec, double &ltot);

    static int interpolate_inbetween_2d_clothoid_3arc_G2_xy(const gp_Pnt &p0, const gp_Pnt &p1, const gp_Pnt &p2, const gp_Pnt &p3, const gp_Pnt &p4, const gp_Pnt &p5,
                                                            const double &progress, gp_Pnt &pi);
    static int interpolate_inbetween_2d_clothoid_3arc_G2_xz(const gp_Pnt &p0, const gp_Pnt &p1, const gp_Pnt &p2, const gp_Pnt &p3, const gp_Pnt &p4, const gp_Pnt &p5,
                                                            const double &progress, gp_Pnt &pi);
    static int interpolate_inbetween_2d_clothoid_3arc_G2_yz(const gp_Pnt &p0, const gp_Pnt &p1, const gp_Pnt &p2, const gp_Pnt &p3, const gp_Pnt &p4, const gp_Pnt &p5,
                                                            const double &progress, gp_Pnt &pi);

    // 3d on a plane
    static int draw_inbetween_3d_clothoid_3arc_G2(const gp_Pnt &p0, const gp_Pnt &p1, const gp_Pnt &p2, const gp_Pnt &p3, const gp_Pnt &p4, const gp_Pnt &p5,
                                                  const int &segments,
                                                  std::vector<gp_Pnt> &pvec);

    // Original design function, 3d non-planar. Designed by skynet cyberdyne.
    static int draw_inbetween_3d_clothoid_3arc_G2_non_planar(const gp_Pnt &p0, const gp_Pnt &p1, const gp_Pnt &p2, const gp_Pnt &p3, const gp_Pnt &p4, const gp_Pnt &p5,
                                                             const int &segments,
                                                             std::vector<gp_Pnt> &pvec0, std::vector<gp_Pnt> &pvec1, std::vector<gp_Pnt> &pvec2, std::vector<gp_Pnt> &pvec3);

    // 3d non planar. Designed & optimized by skynet cyberdyne.
    static int draw_inbetween_3d_clothoid_3arc_G2_non_planar(
            const gp_Pnt &p0, const gp_Pnt &p1, const gp_Pnt &p2, const gp_Pnt &p3, const gp_Pnt &p4, const gp_Pnt &p5,
            const int &segments, std::vector<gp_Pnt> &pvec);

};

#endif // DRAW_CLOTHOIDS_H




















