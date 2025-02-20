#include "draw_primitives.h"
#include "BRepPrimAPI_MakeBox.hxx"
#include <BRepLib.hxx>
#include <BRepOffsetAPI_ThruSections.hxx>
#include <BRepBuilderAPI_MakeWire.hxx>
#include <BRepBuilderAPI_Transform.hxx>
#include <BRepBuilderAPI_MakeFace.hxx>
#include <BRepBuilderAPI_MakeEdge.hxx>
#include <BRepPrimAPI_MakePrism.hxx>
#include <BRepPrimAPI_MakeSphere.hxx>
#include <BRepPrimAPI_MakeCone.hxx>
#include <BRepPrimAPI_MakeTorus.hxx>
#include <BRepPrimAPI_MakeBox.hxx>
#include <BRepFilletAPI_MakeFillet.hxx>
#include <BRepOffsetAPI_MakeThickSolid.hxx>
#include <BRepPrimAPI_MakeCylinder.hxx>
#include <BRepAlgoAPI_Fuse.hxx>
#include <BRepTools_ReShape.hxx>
#include <BRepTools.hxx>
#include <BRepBuilderAPI_MakeVertex.hxx>
#include <algorithm>
#include <stdio.h>
#include "ElCLib.hxx"
#include <BRepPrimAPI_MakeSphere.hxx>
#include <BRepAlgoAPI_Section.hxx>
#include <GeomAPI_ProjectPointOnCurve.hxx>

// Make conversion's easy:
#define toRadians M_PI/180.0
#define toDegrees (180.0/M_PI)

draw_primitives::draw_primitives(){ }

// Draw 3d solids
Handle(AIS_Shape) draw_primitives::draw_3d_cone(gp_Pnt centerpoint, double bottomdiameter, double topdiameter, double height){
    gp_Dir axis=gp::DZ();
    gp_Ax2 aplace(centerpoint,axis);
    TopoDS_Shape t_topo_cone = BRepPrimAPI_MakeCone(aplace,bottomdiameter,topdiameter,height).Shape();
    return new AIS_Shape(t_topo_cone);
}

Handle(AIS_Shape) draw_primitives::draw_3d_tcp_cone(gp_Pnt centerpoint, double bottomdiameter, double topdiameter, double height){
    gp_Dir axis=-gp::DX();
    gp_Ax2 aplace(centerpoint,axis);
    TopoDS_Shape t_topo_cone = BRepPrimAPI_MakeCone(aplace,bottomdiameter,topdiameter,height).Shape();
    return new AIS_Shape(t_topo_cone);
}

Handle(AIS_Shape) draw_primitives::draw_3d_cilinder(double radius, double height){
    TopoDS_Shape t_topo_cylinder = BRepPrimAPI_MakeCylinder(radius , height).Shape();
    return new AIS_Shape(t_topo_cylinder);
}

Handle(AIS_Shape) draw_primitives::draw_3d_sphere(double radius, gp_Pnt center){
    TopoDS_Shape t_topo_sphere = BRepPrimAPI_MakeSphere(center,radius).Shape();
    return new AIS_Shape(t_topo_sphere);
}

Handle(AIS_Shape) draw_primitives::draw_3d_box(double dx, double dy, double dz){
    // Create workframe box.
    if(dx==0){
        std::cout<<"draw 3d box, invalid input"<<std::endl;
        return draw_3d_point({0,0,0});
    }
    if(dy==0){
        std::cout<<"draw 3d box, invalid input"<<std::endl;
        return draw_3d_point({0,0,0});
    }
    if(dz==0){
        std::cout<<"draw 3d box, invalid input"<<std::endl;
        return draw_3d_point({0,0,0});
    }

    TopoDS_Shape t_topo_box = BRepPrimAPI_MakeBox(dx,dy,dz).Shape();
    Handle(AIS_Shape) t_ais_box = new AIS_Shape(t_topo_box);
    return t_ais_box;
}

// Draw 2d primitives:
Handle(AIS_Shape) draw_primitives::draw_2d_circle(gp_Pnt center,double radius){
    gp_Dir dir(0,0,1);
    gp_Circ circle(gp_Ax2( center, dir),radius);
    BRepBuilderAPI_MakeEdge makeEdge(circle);
    Handle(AIS_Shape) gcode_shape = new AIS_Shape(TopoDS_Edge());
    gcode_shape ->Set(makeEdge.Edge());
    return gcode_shape;
}

Handle(AIS_Shape) draw_primitives::draw_cp_2d_arc(gp_Pnt center, gp_Pnt point1, gp_Pnt point2){

    double radius=center.Distance(point2);
    gp_Dir dir(0,0,1); // you can change this
    gp_Circ circle(gp_Ax2( center, dir),radius);
    Handle(Geom_TrimmedCurve) aArcOfCircle = GC_MakeArcOfCircle(circle,point1,point2,0);
    TopoDS_Edge aEdge2 = BRepBuilderAPI_MakeEdge(aArcOfCircle);
    return new AIS_Shape(aEdge2);
}

//double calculate_2d_angle_rad(double x1, double y1, double x2, double y2, double x3, double y3) {
//    // Vectors AB and BC
//    double ABx = x1 - x2;
//    double ABy = y1 - y2;
//    double BCx = x3 - x2;
//    double BCy = y3 - y2;

//    // Dot product of AB and BC
//    double dot_product = ABx * BCx + ABy * BCy;

//    // Magnitudes of AB and BC
//    double magnitude_AB = sqrt(ABx * ABx + ABy * ABy);
//    double magnitude_BC = sqrt(BCx * BCx + BCy * BCy);

//    // Calculate the angle in radians
//    double angle_rad = acos(dot_product / (magnitude_AB * magnitude_BC));

//    // Convert angle from radians to degrees
//    return angle_rad;
//}


void makeHelix(void)
{
    Handle_Geom_CylindricalSurface aCylinder = new Geom_CylindricalSurface(gp::XOY(), 6.0);

    gp_Lin2d aLine2d(gp_Pnt2d(0.0, 0.0), gp_Dir2d(1.0, 1.0));

    Handle_Geom2d_TrimmedCurve aSegment = GCE2d_MakeSegment(aLine2d, 0.0, M_PI * 2.0);

    TopoDS_Edge aHelixEdge = BRepBuilderAPI_MakeEdge(aSegment, aCylinder, 0.0, 6.0 * M_PI).Edge();


}

/*
    Given 2 points, we can check the shape type for arc.
*/
int draw_primitives::get_arc_shape_type(const int &plane, const gp_Pnt &p0, const gp_Pnt &p1){

    if(p0.Distance(p1)==0){
        //  std::cout<<"Error, spiral is circle"<<std::endl;
        return 3; // Circle.
    }

    if(plane==0 && p0.Z()==p1.Z()){
        // std::cout<<"Error, spiral needs z diff value in xy plane."<<std::endl;
        return 2; // Arc.
    }
    if(plane==1 && p0.Y()==p1.Y()){
        // std::cout<<"Error, spiral needs y diff value in xz plane."<<std::endl;
        return 2; // Arc.
    }
    if(plane==2 && p0.X()==p1.X()){
        // std::cout<<"Error, spiral needs x diff value in yz plane."<<std::endl;
        return 2; // Arc.
    }

    return 4; // Is a helix.
}

/*
Sample gcode tested for spiral, helix:

    x1 y1(start xy circle)
    g17 g02 i.5 j.5 // xy plane

    x1 z1(start xz circle)
    g18 g02 i.5 k.5 // xz plane

    y1 z1 (start yz circle)
    g19 g02 j.5 k.5 // yz plane

p0 = starpoint of arc.
p1 = endpoint of arc.

plane:
    0=xy plane ,G17
    1=xz plane ,G18
    2=yz plane ,G19

gcode:
    2=gcode G2, clockwise arc, cw.
    3=gcode G3, counter clockwise arc, ccw.

gcode arc center:
    i=gcode I, center offset for x, seen from arc startpoint.
    j=gcode J, center offset for y, seen from arc startpoint.
    k=gcode K, center offset for z, seen from arc startpoint.

turns =
    how many revolutions the spiral may have.
    Gcode P0=no revolutions, gcode P1= one revolution etc.


    Linuxcnc is also able to draw multiturn spirals
    G2 or G3 <X- Y- Z- I- J- P-> where P is the number of turns

    Full circle or spiral programming is possible without axis words
    G2 Z- I- J- P-

*/
Handle(AIS_Shape) draw_primitives::draw_2d_gcode_G2_helix(const gp_Pnt& p0, const gp_Pnt& p1, const int& plane,
                                                          const double& i, const double& j, const double& k ,
                                                          const int& turns, const int& g2_continuity, double &lenght) {

    // Validate
    if(plane==0 && p0.Z()==p1.Z()){
        std::cout<<"Error, spiral needs z diff value in xy plane."<<std::endl;
        return draw_3d_point(p0);
    }
    if(plane==1 && p0.Y()==p1.Y()){
        std::cout<<"Error, spiral needs y diff value in xz plane."<<std::endl;
        return draw_3d_point(p0);
    }
    if(plane==2 && p0.X()==p1.X()){
        std::cout<<"Error, spiral needs x diff value in yz plane."<<std::endl;
        return draw_3d_point(p0);
    }

    if(p0.Distance(p1)==0){
        std::cout<<"Error, spiral is circle"<<std::endl;
        return draw_3d_point(p0);
    }

    gp_Pnt pc;
    std::vector<gp_Pnt> pvec;
    double angle0=0, angle1=0, radius=0, delta_angle=0, delta_pitch=0, full_pitch=0, angle_step=0;
    int num_points=0;

    if(plane==0){
        pc={p0.X()+i, p0.Y()+j, p0.Z()};
        angle0 = atan2(p0.Y()-pc.Y(),p0.X()-pc.X());
        angle1 = atan2(p1.Y()-pc.Y(),p1.X()-pc.X());
    }
    if(plane==1){
        pc={p0.X()+i, p0.Y(), p0.Z()+k};
        angle0 = atan2(p0.Z()-pc.Z(),p0.X()-pc.X());
        angle1 = atan2(p1.Z()-pc.Z(),p1.X()-pc.X());
    }
    if(plane==2){
        pc={p0.X(), p0.Y()+j, p0.Z()+k};
        angle0 = atan2(p0.Z()-pc.Z(),p0.Y()-pc.Y());
        angle1 = atan2(p1.Z()-pc.Z(),p1.Y()-pc.Y());
    }

    radius =        p0.Distance(pc);
    delta_angle =   angle0 - angle1;

    // std::cout<<"center x:"<<pc.X()<<" y:"<<pc.Y()<<" z:"<<pc.Z()<<std::endl;
    // std::cout<<"angle0:"<<angle0<<" angle1:"<<angle1<<std::endl;
    // std::cout<<"radius:"<<radius<<std::endl;

    // Calculate the difference in Z-coordinates
    if(plane==0){
        delta_pitch = p0.Z() - p1.Z();
    }
    if(plane==1){
        delta_pitch = p0.Y() - p1.Y();
    }
    if(plane==2){
        delta_pitch = p0.X() - p1.X();
    }

    // Check for zero angular difference which could mean a full revolution
    if (delta_angle == 0) {
        if (delta_pitch != 0) {
            // Assume one full revolution
            delta_angle = 2 * M_PI;
        } else {
            // Both delta_angle and delta_z are zero, meaning the points are the same
        }
    }

    // Multi turn
    delta_angle+=turns*2*M_PI;

    // Calculate the pitch for a full revolution (2*pi)
    full_pitch = (delta_pitch / delta_angle) * (2 * M_PI);

    // Calculate step size
    num_points = fmax(turns,1)  *50;
    angle_step = delta_angle / (num_points - 1);

    if(plane==0){
        // Generate points along the helix
        for (int idx = 0; idx < num_points; ++idx) {
            double angle = angle0 - idx * angle_step;
            double x = pc.X() + radius * cos(angle);
            double y = pc.Y() + radius * sin(angle);
            double z=0;

            if(!g2_continuity){
                z = p0.Z() + ((angle0 - angle) / (2 * M_PI)) * -full_pitch;
            } else {
                // Calculate Z using a sinusoidal function for variable pitch
                double t = static_cast<double>(idx) / (num_points - 1); // Normalized parameter [0, 1]
                double sinusoidal_factor = 0.5 * (1 - cos(M_PI * t)); // Sinusoidal factor to vary pitch
                z = p0.Z() - sinusoidal_factor * delta_pitch;
            }

            pvec.push_back({x,y,z});
        }
    }
    if(plane==1){
        // Generate points along the helix
        for (int idx = 0; idx < num_points; ++idx) {
            double angle = angle0 - idx * angle_step;
            double x = pc.X() + radius * cos(angle);
            double z = pc.Z() + radius * sin(angle);
            double y = 0;

            if(!g2_continuity){
                y = p0.Y() + ((angle0 - angle) / (2 * M_PI)) * -full_pitch;
            } else {
                // Calculate Z using a sinusoidal function for variable pitch
                double t = static_cast<double>(idx) / (num_points - 1); // Normalized parameter [0, 1]
                double sinusoidal_factor = 0.5 * (1 - cos(M_PI * t)); // Sinusoidal factor to vary pitch
                y = p0.Y() - sinusoidal_factor * delta_pitch;
            }
            pvec.push_back({x,y,z});
        }
    }
    if(plane==2){
        // Generate points along the helix
        for (int idx = 0; idx < num_points; ++idx) {
            double angle = angle0 - idx * angle_step;
            double y = pc.Y() + radius * cos(angle);
            double z = pc.Z() + radius * sin(angle);
            double x = 0;

            if(!g2_continuity){
                x = p0.X() + ((angle0 - angle) / (2 * M_PI)) * -full_pitch;
            } else {
                // Calculate Z using a sinusoidal function for variable pitch
                double t = static_cast<double>(idx) / (num_points - 1); // Normalized parameter [0, 1]
                double sinusoidal_factor = 0.5 * (1 - cos(M_PI * t)); // Sinusoidal factor to vary pitch
                x = p0.X() - sinusoidal_factor * delta_pitch;
            }
            pvec.push_back({x, y, z});
        }
    }

    lenght=get_3d_pvec_lenght(pvec);

    return draw_3d_line_wire(pvec);
}

// For info see G2 helix.
Handle(AIS_Shape) draw_primitives::draw_2d_gcode_G3_helix(const gp_Pnt& p0, const gp_Pnt& p1, const int& plane,
                                                          const double& i, const double& j, const double& k,
                                                          const int& turns, const int& g2_continuity, double &lenght){

    // Validate
    if(plane==0 && p0.Z()==p1.Z()){
        std::cout<<"Error, spiral needs z diff value in xy plane."<<std::endl;
        return draw_3d_point(p0);
    }
    if(plane==1 && p0.Y()==p1.Y()){
        std::cout<<"Error, spiral needs y diff value in xz plane."<<std::endl;
        return draw_3d_point(p0);
    }
    if(plane==2 && p0.X()==p1.X()){
        std::cout<<"Error, spiral needs x diff value in yz plane."<<std::endl;
        return draw_3d_point(p0);
    }

    if(p0.Distance(p1)==0){
        std::cout<<"Error, spiral is circle"<<std::endl;
        return draw_3d_point(p0);
    }

    gp_Pnt pc;
    std::vector<gp_Pnt> pvec;
    double angle0 = 0, angle1 = 0, radius = 0, delta_angle = 0, delta_pitch = 0, full_pitch = 0, angle_step = 0;
    int num_points = 0;

    if (plane == 0) {
        pc = {p0.X() + i, p0.Y() + j, p0.Z()};
        angle0 = atan2(p0.Y() - pc.Y(), p0.X() - pc.X());
        angle1 = atan2(p1.Y() - pc.Y(), p1.X() - pc.X());
    }
    else if (plane == 1) {
        pc = {p0.X() + i, p0.Y(), p0.Z() + k};
        angle0 = atan2(p0.Z() - pc.Z(), p0.X() - pc.X());
        angle1 = atan2(p1.Z() - pc.Z(), p1.X() - pc.X());
    }
    else if (plane == 2) {
        pc = {p0.X(), p0.Y() + j, p0.Z() + k};
        angle0 = atan2(p0.Z() - pc.Z(), p0.Y() - pc.Y());
        angle1 = atan2(p1.Z() - pc.Z(), p1.Y() - pc.Y());
    }

    // Adjust angle0 if needed for CCW arc
    if (angle0 >= angle1) {
        angle0 -= 2 * M_PI;
    }

    radius = p0.Distance(pc);
    delta_angle = angle1 - angle0; // Change in angle direction for G3 CCW

    // Calculate the difference in Z-coordinates
    if (plane == 0) {
        delta_pitch = p0.Z() - p1.Z();
    }
    else if (plane == 1) {
        delta_pitch = p0.Y() - p1.Y();
    }
    else if (plane == 2) {
        delta_pitch = p0.X() - p1.X();
    }

    // Check for zero angular difference which could mean a full revolution
    if (delta_angle == 0) {
        if (delta_pitch != 0) {
            // Assume one full revolution
            delta_angle = 2 * M_PI;
        } else {
            // Both delta_angle and delta_z are zero, meaning the points are the same
        }
    }

    // Multi turn
    delta_angle += turns * 2 * M_PI;

    // Calculate the pitch for a full revolution (2*pi)
    full_pitch = (delta_pitch / delta_angle) * (2 * M_PI);

    // Calculate step size
    num_points = fmax(turns, 1) * 50;
    angle_step = delta_angle / (num_points - 1);

    // Generate points along the helix
    for (int idx = 0; idx < num_points; ++idx) {
        double angle = angle0 + idx * angle_step; // Increase angle for counterclockwise direction (G3 CCW)
        double x=0, y=0, z=0;

        if (plane == 0) {
            x = pc.X() + radius * cos(angle);
            y = pc.Y() + radius * sin(angle);

            if(!g2_continuity){
                z = p0.Z() + ((angle - angle0) / (2 * M_PI)) * -full_pitch; // Adjust Z using pitch
            } else {
                // Calculate Z using a sinusoidal function for variable pitch
                double t = static_cast<double>(idx) / (num_points - 1); // Normalized parameter [0, 1]
                double sinusoidal_factor = 0.5 * (1 - cos(M_PI * t)); // Sinusoidal factor to vary pitch
                z = p0.Z() - sinusoidal_factor * delta_pitch;
            }
        } else if (plane == 1) {
            x = pc.X() + radius * cos(angle);
            z = pc.Z() + radius * sin(angle);
            if(!g2_continuity){
                y = p0.Y() + ((angle - angle0) / (2 * M_PI)) * -full_pitch; // Adjust Y using pitch
            } else {
                // Calculate Z using a sinusoidal function for variable pitch
                double t = static_cast<double>(idx) / (num_points - 1); // Normalized parameter [0, 1]
                double sinusoidal_factor = 0.5 * (1 - cos(M_PI * t)); // Sinusoidal factor to vary pitch
                y = p0.Y() - sinusoidal_factor * delta_pitch;
            }
        } else if (plane == 2) {
            y = pc.Y() + radius * cos(angle);
            z = pc.Z() + radius * sin(angle);
            if(!g2_continuity){
                x = p0.X() + ((angle - angle0) / (2 * M_PI)) * -full_pitch; // Adjust X using pitch
            } else {
                // Calculate Z using a sinusoidal function for variable pitch
                double t = static_cast<double>(idx) / (num_points - 1); // Normalized parameter [0, 1]
                double sinusoidal_factor = 0.5 * (1 - cos(M_PI * t)); // Sinusoidal factor to vary pitch
                x = p0.X() - sinusoidal_factor * delta_pitch;
            }
        }
        pvec.push_back({x, y, z});
    }

    lenght=get_3d_pvec_lenght(pvec);

    return draw_3d_line_wire(pvec);
}

Handle(AIS_Shape) draw_primitives::draw_2d_gcode_G2_G3_helix(const gp_Pnt& p0, const gp_Pnt& p1, const int& plane,const int& gcode,
                                                             const double& i, const double& j, const double& k,
                                                             const int& turns, const int& g2_continuity, double &lenght){

    std::cout<<"helix g2_continuity status:"<<g2_continuity<<std::endl;

    if(gcode==2){
        return draw_2d_gcode_G2_helix(p0,p1,plane,i,j,k,turns,g2_continuity,lenght);
    }
    if(gcode==3){
        return draw_2d_gcode_G3_helix(p0,p1,plane,i,j,k,turns,g2_continuity,lenght);
    }
    std::cout<<"Error, helix has wrong gcode id."<<std::endl;
    return draw_3d_point(p0);
}

double draw_primitives::calculate_2d_angle_rad(const double &x0, const double &y0, const double &x1, const double &y1) {
    double angle = atan2(y0 - y1, x0 - x1);
    return angle;
}

// Sample function.
Handle(AIS_Shape) draw_primitives::draw_2d_gcode_G2_xy_helix(const gp_Pnt& p0, const gp_Pnt& p1, const gp_Pnt& pc, const int& turns) {

    // Calculate radius
    double radius = p0.Distance(pc);
    // Calculate initial and final angles
    double angle0 = calculate_2d_angle_rad(p0.X(), p0.Y(), pc.X(), pc.Y());
    double angle1 = calculate_2d_angle_rad(p1.X(), p1.Y(), pc.X(), pc.Y());

    // Normalize angles to be in range [0, 2*PI)
    if (angle0 < 0) {
        angle0 += 2 * M_PI;
    }
    if (angle1 < 0) {
        angle1 += 2 * M_PI;
    }
    // Ensure angle0 > angle1 for CW direction
    if (angle0 <= angle1) {
        angle0 += 2 * M_PI;
    }

    //std::cout << "angle0: " << angle0 << " angle1: " << angle1 << std::endl;

    // Calculate the difference in angles
    double delta_angle = angle0 - angle1;

    // Calculate the difference in Z-coordinates
    double delta_z = p0.Z() - p1.Z();

    // Check for zero angular difference which could mean a full revolution
    if (delta_angle == 0) {
        if (delta_z != 0) {
            // Assume one full revolution
            delta_angle = 2 * M_PI;
        } else {
            // Both delta_angle and delta_z are zero, meaning the points are the same
        }
    }

    // Multi turn
    delta_angle+=turns*2*M_PI;

    // Calculate the pitch for a full revolution (2*pi)
    double full_pitch = -(delta_z / delta_angle) * (2 * M_PI); // Inverse pitch for clockwise direction

    // Calculate step size
    int num_points = fmax(turns,1)  *50;
    double angle_step = delta_angle / (num_points - 1);
    std::vector<gp_Pnt> pvec;

    // Generate points along the helix
    for (int i = 0; i < num_points; ++i) {
        double angle = angle0 - i * angle_step; // Decrease angle for clockwise direction
        double x = pc.X() + radius * cos(angle);
        double y = pc.Y() + radius * sin(angle);
        double z = p0.Z() + ((angle0 - angle) / (2 * M_PI)) * full_pitch; // Adjust Z using pitch

        pvec.push_back({x,y,z});
    }

    return draw_3d_line_wire(pvec);
}

Handle(AIS_Shape) draw_primitives::draw_2d_gcode_G2_xy_helix_g2_continuity_test(const gp_Pnt& p0, const gp_Pnt& p1,
                                                                                const gp_Pnt& pc, const int& turns) {

    // Calculate radius
    double radius = p0.Distance(pc);
    // Calculate initial and final angles
    double angle0 = calculate_2d_angle_rad(p0.X(), p0.Y(), pc.X(), pc.Y());
    double angle1 = calculate_2d_angle_rad(p1.X(), p1.Y(), pc.X(), pc.Y());

    // Normalize angles to be in range [0, 2*PI)
    if (angle0 < 0) {
        angle0 += 2 * M_PI;
    }
    if (angle1 < 0) {
        angle1 += 2 * M_PI;
    }
    // Ensure angle0 > angle1 for CW direction
    if (angle0 <= angle1) {
        angle0 += 2 * M_PI;
    }

    //std::cout << "angle0: " << angle0 << " angle1: " << angle1 << std::endl;

    // Calculate the difference in angles
    double delta_angle = angle0 - angle1;

    // Calculate the difference in Z-coordinates
    double delta_z = p0.Z() - p1.Z();

    // Check for zero angular difference which could mean a full revolution
    if (delta_angle == 0) {
        if (delta_z != 0) {
            // Assume one full revolution
            delta_angle = 2 * M_PI;
        } else {
            // Both delta_angle and delta_z are zero, meaning the points are the same
        }
    }

    // Multi turn
    delta_angle += turns * 2 * M_PI;

    // Calculate the total number of points
    int num_points = fmax(turns, 1) * 50;
    double angle_step = delta_angle / (num_points - 1);
    std::vector<gp_Pnt> pvec;

    // Generate points along the helix with variable pitch
    for (int i = 0; i < num_points; ++i) {
        double angle = angle0 - i * angle_step; // Decrease angle for clockwise direction
        double x = pc.X() + radius * cos(angle);
        double y = pc.Y() + radius * sin(angle);

        // Calculate Z using a sinusoidal function for variable pitch
        double t = static_cast<double>(i) / (num_points - 1); // Normalized parameter [0, 1]
        double sinusoidal_factor = 0.5 * (1 - cos(M_PI * t)); // Sinusoidal factor to vary pitch
        double z = p0.Z() - sinusoidal_factor * delta_z;

        pvec.push_back({x, y, z});
    }

    return draw_3d_line_wire(pvec);
}


Handle(AIS_Shape) draw_primitives::draw_2d_gcode_G3_xy_helix(const gp_Pnt& p0, const gp_Pnt& p1, const gp_Pnt& pc, const int& turns) {
    // Calculate radius
    double radius = p0.Distance(pc);
    // Calculate initial and final angles
    double angle0 = calculate_2d_angle_rad(p0.X(), p0.Y(), pc.X(), pc.Y());
    double angle1 = calculate_2d_angle_rad(p1.X(), p1.Y(), pc.X(), pc.Y());

    // Normalize angles to be in range [0, 2*PI)
    if (angle0 < 0) {
        angle0 += 2 * M_PI;
    }
    if (angle1 < 0) {
        angle1 += 2 * M_PI;
    }
    // Ensure angle0 < angle1 for CCW direction
    if (angle0 >= angle1) {
        angle1 += 2 * M_PI;
    }

    // Calculate the difference in angles
    double delta_angle = angle1 - angle0;

    // Calculate the difference in Z-coordinates
    double delta_z = p1.Z() - p0.Z();

    // Check for zero angular difference which could mean a full revolution
    if (delta_angle == 0) {
        if (delta_z != 0) {
            // Assume one full revolution
            delta_angle = 2 * M_PI;
        } else {
            // Both delta_angle and delta_z are zero, meaning the points are the same
        }
    }

    // Multi turn
    delta_angle += turns * 2 * M_PI;

    // Calculate the pitch for a full revolution (2*pi)
    double full_pitch = (delta_z / delta_angle) * (2 * M_PI); // Positive pitch for counter-clockwise direction

    // Calculate step size
    int num_points = std::max(turns, 1) * 50;
    double angle_step = delta_angle / (num_points - 1);
    std::vector<gp_Pnt> pvec;

    // Generate points along the helix
    for (int i = 0; i < num_points; ++i) {
        double angle = angle0 + i * angle_step; // Increase angle for counter-clockwise direction
        double x = pc.X() + radius * cos(angle);
        double y = pc.Y() + radius * sin(angle);
        double z = p0.Z() + ((angle - angle0) / (2 * M_PI)) * full_pitch; // Adjust Z using pitch

        pvec.push_back({x, y, z});
    }

    return draw_3d_line_wire(pvec);
}

Handle(AIS_Shape) draw_primitives::draw_2d_acad_arc(gp_Pnt center, double radius, const Standard_Real alpha1, const Standard_Real alpha2){
    gp_Dir dir(0,0,1); // you can change this
    gp_Circ circle(gp_Ax2( center, dir),radius);
    Handle(Geom_TrimmedCurve) aArcOfCircle = GC_MakeArcOfCircle(circle,alpha1,alpha2,0);
    TopoDS_Edge aEdge = BRepBuilderAPI_MakeEdge(aArcOfCircle);
    return new AIS_Shape(aEdge);
}

Handle(AIS_Shape) draw_primitives::draw_3d_acad_arc(gp_Pnt center, double radius, double alpha1, double alpha2, gp_Dir dir){
    //gp_Dir dir(0,0,1); // you can change this
    gp_Circ circle(gp_Ax2( center, dir),radius);
    Handle(Geom_TrimmedCurve) aArcOfCircle = GC_MakeArcOfCircle(circle,alpha1,alpha2,0);
    TopoDS_Edge aEdge = BRepBuilderAPI_MakeEdge(aArcOfCircle);
    return new AIS_Shape(aEdge);
}

Handle(AIS_Shape) draw_primitives::draw_2d_ellipse(gp_Pnt center, gp_Pnt secpoint, double alpha_start, double alpha_end, double ratio){

    //https://github.com/grotius-cnc/QT_CadCam_rev0/blob/master/display/display.h
    // Acad's ellipse nr's, https://github.com/grotius-cnc/cadcam/blob/master/dxf/read_ellipse_AC1027.cpp
    // x,y,z centerpoint    10,20,30
    // x,y,z endpoint mayor 11,21,31 ( coordinates relative to ellipse centerpoint..)
    // ratio                40
    // start angle          41
    // end angle            42

    //Standard_Real alpha1=alpha_start;
    //Standard_Real alpha2=alpha_end;

    //center point to endpoint mayor axis..
    double MayorRadius = sqrt(pow(secpoint.X()-center.X(),2) + pow(secpoint.Y()-center.Y(),2) + pow(secpoint.Z()-center.Z(),2));
    //ratio minor axis to mayor axis..
    double MinorRadius = ratio*MayorRadius ;

    gp_Dir xDirection(secpoint.X()-center.X(),secpoint.Y()-center.Y(),secpoint.Z()-center.Z()); // Direction is auto normalized by occ.
    gp_Dir normalDirection(0,0,1);
    gp_Ax2 axis(center,normalDirection,xDirection);

    gp_Elips ellipse(axis,MayorRadius,MinorRadius);
    Handle(Geom_TrimmedCurve) aArcOfEllipse = GC_MakeArcOfEllipse(ellipse,alpha_start,alpha_end,0);
    TopoDS_Edge aEdge = BRepBuilderAPI_MakeEdge(aArcOfEllipse);

    return new AIS_Shape(aEdge);
}

// Draw 3d tools:
Handle(AIS_Shape) draw_primitives::draw_3d_origin(gp_Pnt origin, double linelenght){

    double x=origin.X();
    double y=origin.Y();
    double z=origin.Z();

    TopoDS_Shape t_topo_sphere = BRepPrimAPI_MakeSphere(origin,2).Shape();
    Handle(AIS_Shape) aisbody_tcp_sphere = new AIS_Shape(t_topo_sphere);
    aisbody_tcp_sphere->SetColor(Quantity_NOC_YELLOW);
    aisbody_tcp_sphere->SetTransparency(0.75);

    TopoDS_Edge edge = BRepBuilderAPI_MakeEdge(origin,{x+linelenght,y,z});
    Handle(AIS_Shape) aisbody_tcp_xaxis = new AIS_Shape(edge);
    aisbody_tcp_xaxis->SetColor(Quantity_NOC_RED);

    edge= BRepBuilderAPI_MakeEdge(origin,{x,y+linelenght,z});
    Handle(AIS_Shape) aisbody_tcp_yaxis = new AIS_Shape(edge);
    aisbody_tcp_yaxis->SetColor(Quantity_NOC_GREEN);

    edge= BRepBuilderAPI_MakeEdge(origin,{x,y,z+linelenght});
    Handle(AIS_Shape) aisbody_tcp_zaxis = new AIS_Shape(edge);
    aisbody_tcp_zaxis->SetColor(Quantity_NOC_BLUE);

    aisbody_tcp_sphere->AddChild(aisbody_tcp_xaxis);
    aisbody_tcp_sphere->AddChild(aisbody_tcp_yaxis);
    aisbody_tcp_sphere->AddChild(aisbody_tcp_zaxis);

    return aisbody_tcp_sphere;
}

// Euler angles in radians.
Handle(AIS_Shape) draw_primitives::rotate_3d(Handle(AIS_Shape) shape, gp_Pnt center, double euler_z, double euler_y, double euler_x){

    gp_Trsf trsf1,trsf2,trsf3;
    trsf1.SetRotation(gp_Ax1(center,
                             gp_Dir(0,
                                    0,
                                    1)), euler_z);

    trsf2.SetRotation(gp_Ax1(center,
                             gp_Dir(0,
                                    1,
                                    0)), euler_y);

    trsf3.SetRotation(gp_Ax1(center,
                             gp_Dir(1,
                                    0,
                                    0)), euler_x);

    trsf1.Multiply(trsf2);
    trsf1.Multiply(trsf3);
    shape->SetLocalTransformation(trsf1);
    return shape;
}

// For euler angles you have to follow the euler sequence of rotation. First around z, then around y, then around x.
// Otherwise you will get wrong solutions.
Handle(AIS_Shape) draw_primitives::rotate_translate_3d_quaternion(Handle(AIS_Shape) shape, gp_Pnt translation, double euler_z, double euler_y, double euler_x){

    gp_Trsf trsf;
    gp_Quaternion aQuat;

    aQuat.SetEulerAngles (gp_YawPitchRoll, euler_z, euler_y, euler_x);
    trsf.SetRotation(aQuat);

    gp_Trsf trsf1;
    trsf1.SetTranslation({0,0,0},translation);

    trsf1.Multiply(trsf);

    shape->SetLocalTransformation(trsf1);
    return shape;
}

// Function to rotate an AIS_Shape around the x, y, and z axes at the origin and then move to tcp
Handle(AIS_Shape) draw_primitives::rotate_translate_3d(Handle(AIS_Shape) shape, gp_Pnt tcp, double a, double b, double c) {
    // Create transformation objects for each axis
    gp_Trsf trsf_x, trsf_y, trsf_z;

    // Set rotation for x-axis
    trsf_x.SetRotation(gp_Ax1(tcp, gp_Dir(1, 0, 0)), a);

    // Set rotation for y-axis
    trsf_y.SetRotation(gp_Ax1(tcp, gp_Dir(0, 1, 0)), b);

    // Set rotation for z-axis
    trsf_z.SetRotation(gp_Ax1(tcp, gp_Dir(0, 0, 1)), c);

    // Initialize the final transformation
    gp_Trsf trsf;

    // Apply rotations in the correct order: a, b, c
    trsf.Multiply(trsf_x);
    trsf.Multiply(trsf_y);
    trsf.Multiply(trsf_z);

    // Create a translation transformation to move to tcp
    gp_Trsf move;
    move.SetTranslation(gp_Vec(gp_Pnt(0, 0, 0), tcp));

    // Apply the translation after the rotations
    trsf.Multiply(move);

    // Apply the transformation to the shape
    shape->SetLocalTransformation(trsf);

    return shape;
}

Handle(AIS_Shape) draw_primitives::translate_3d(Handle(AIS_Shape) shape, gp_Pnt current, gp_Pnt target){
    gp_Trsf trsf;
    trsf.SetTranslation(current,target);
    shape->SetLocalTransformation(trsf);
    return shape;
}

Handle(AIS_Shape) draw_primitives::colorize(Handle(AIS_Shape) shape, Quantity_Color color, double transparancy){

    if(shape.IsNull()){
        return nullptr;
    }

    shape->SetTransparency(transparancy); // 0.0 - 1.0
    shape->SetColor(color);
    shape->SetMaterial(Graphic3d_NOM_PLASTIC);
    return shape;
}

Handle(AIS_Shape) draw_primitives::show_boundary(Handle(AIS_Shape) aShape, int status){
    aShape->Attributes()->SetFaceBoundaryDraw(status);
    aShape->Attributes()->SetFaceBoundaryAspect(new Prs3d_LineAspect(Quantity_NOC_BLACK, Aspect_TOL_SOLID, 1.));
    return aShape;
}

// Draw 3d primitives:
Handle(AIS_Shape) draw_primitives::draw_3d_point(gp_Pnt point){
    TopoDS_Vertex vertex = BRepBuilderAPI_MakeVertex(point);
    return new AIS_Shape(vertex);
}

Handle(AIS_Shape) draw_primitives::draw_3d_line(const gp_Pnt &p0, const gp_Pnt &p1){

    if(p0.Distance(p1)<1e-12){
        return draw_3d_point(p0);
    }
    TopoDS_Edge edge = BRepBuilderAPI_MakeEdge(p0,p1);
    return new AIS_Shape(edge);
}

Handle(AIS_Shape) draw_primitives::draw_3d_line(const gp_Pnt &p0, const gp_Pnt &p1, double &lenght){

    lenght=p0.Distance(p1);
    if(lenght<1e-12){
        return draw_3d_point(p0);
    }

    TopoDS_Edge edge = BRepBuilderAPI_MakeEdge(p0,p1);
    return new AIS_Shape(edge);
}

Handle(AIS_Shape) draw_primitives::draw_3d_line_vector(const gp_Pnt &p0, const double &length, const double &a, const double &b, const double &c, gp_Pnt &pi) {
    // Create rotation transformations around x and y axes
    //    gp_Trsf trsfX, trsfY;
    //    trsfX.SetRotation(gp_Ax1(gp_Pnt(0, 0, 0), gp_Dir(1, 0, 0)), a);
    //    trsfY.SetRotation(gp_Ax1(gp_Pnt(0, 0, 0), gp_Dir(0, 1, 0)), b);

    //    // Define direction vector in global coordinate system
    //    gp_Vec direction(0, 0, length);  // Line direction along Z-axis initially

    //    // Rotate direction vector using trsfX (around x-axis)
    //    direction.Transform(trsfX);

    //    // Rotate direction vector using trsfY (around y-axis)
    //    direction.Transform(trsfY);

    //    // Compute endpoint p1
    //    pi = p0.Translated(direction);

    //    // Create a geometric line from p0 to p1
    //    gp_Ax1 axis(p0, gp_Dir(direction));  // Axis of the line from p0 in direction of p1
    //    Handle(Geom_Line) lineGeom = new Geom_Line(axis);

    //    // Create an edge (line segment) from p0 to p1
    //    BRepBuilderAPI_MakeEdge edgeMaker(lineGeom, p0, pi);
    //    TopoDS_Edge edge = edgeMaker.Edge();

    //    // Create AIS_Shape for visualization
    //    Handle(AIS_Shape) shape = new AIS_Shape(edge);

    Handle(AIS_Shape) aShape=draw_3d_line({0,0,0},{0,0,length});
    aShape=rotate_translate_3d(aShape,p0,a,b,c);

    gp_Pnt p;
    get_transformed_line_points(aShape,p,pi);

    return aShape;
}

Handle(AIS_Shape) draw_primitives::draw_3d_line_wire(std::vector<gp_Pnt> pvec){

    if(pvec.size()==0){
        return draw_3d_point({0,0,0});
    }

    // std::cout<<"drawing line wire pvec size:"<<pvec.size()<<std::endl;
    if(pvec.size()==1){
        return draw_3d_point(pvec[0]);
    }
    if(pvec.size()==2){
        return draw_3d_line(pvec[0],pvec[1]);
    }

    BRepBuilderAPI_MakeWire wire;
    TopoDS_Edge edge;
    for(unsigned int i=0; i<pvec.size()-1; i++){
        if(pvec[i].Distance(pvec[i+1])>0){ // Don't use zero lenght.
            edge = BRepBuilderAPI_MakeEdge(pvec[i],pvec[i+1]);
            wire.Add(edge);
        }
    }

    return new AIS_Shape(wire);
}

Handle(AIS_Shape) draw_primitives::draw_3p_3d_arc(const gp_Pnt &p0, const gp_Pnt &pw, const gp_Pnt &p1) {

    int r=get_3d_arc_lenght(p0,pw,p1); // Good indicator is arc is valid.
    if(!r){
        return draw_3d_line(p0, p1);
    }

    // Attempt to create the arc of a circle
    try {
        // std::cout << "Creating arc with points:" << std::endl;
        // std::cout << "  p0: (" << p0.X() << ", " << p0.Y() << ", " << p0.Z() << ")" << std::endl;
        // std::cout << "  pw: (" << pw.X() << ", " << pw.Y() << ", " << pw.Z() << ")" << std::endl;
        // std::cout << "  p1: (" << p1.X() << ", " << p1.Y() << ", " << p1.Z() << ")" << std::endl;

        Handle(Geom_TrimmedCurve) aArcOfCircle = GC_MakeArcOfCircle(p0, pw, p1);
        if (aArcOfCircle.IsNull()) {
            // std::cerr << "Error: GC_MakeArcOfCircle returned a null curve." << std::endl;
            // Additional debug information
            // std::cerr << "Failed to create an arc with the provided points. Ensure the points form a valid arc." << std::endl;
            return draw_3d_line(p0, p1);
        }

        TopoDS_Edge aEdge = BRepBuilderAPI_MakeEdge(aArcOfCircle);
        if (aEdge.IsNull()) {
            // std::cerr << "Error: BRepBuilderAPI_MakeEdge returned a null edge." << std::endl;
            return draw_3d_line(p0, p1);
        }

        // std::cout << "Returning arc shape." << std::endl;
        return new AIS_Shape(aEdge);
    } catch (Standard_Failure &failure) {
        std::cerr << "Exception caught: " << failure.GetMessageString() << std::endl;
        return nullptr;
    } catch (...) {
        std::cerr << "Unknown exception caught." << std::endl;
        return nullptr;
    }
}

Handle(AIS_Shape) draw_primitives::draw_3d_pc_circle(gp_Pnt center, double dir_Xv, double dir_Yv, double dir_Zv, double radius){
    return draw_3d_pc_circle(center,{dir_Xv,dir_Yv,dir_Zv},radius);
}

Handle(AIS_Shape) draw_primitives::draw_3d_pc_circle(gp_Pnt center, gp_Dir dir, double radius){

    gp_Circ circle(gp_Ax2( center, dir),radius);
    Handle(Geom_TrimmedCurve) aArcOfCircle = GC_MakeArcOfCircle(circle,0,2*M_PI,0);
    TopoDS_Edge aEdge = BRepBuilderAPI_MakeEdge(aArcOfCircle);
    return new AIS_Shape(aEdge);
}

Handle(AIS_Shape) draw_primitives::draw_3d_surface(gp_Pnt p1, gp_Pnt p2, gp_Pnt p3, gp_Pnt p4){

    // Create edges using the points
    BRepBuilderAPI_MakeEdge edge1(p1, p2);
    BRepBuilderAPI_MakeEdge edge2(p2, p3);
    BRepBuilderAPI_MakeEdge edge3(p3, p4);
    BRepBuilderAPI_MakeEdge edge4(p4, p1);

    // Create a wire from the edges
    BRepBuilderAPI_MakeWire wire;
    wire.Add(edge1.Edge());
    wire.Add(edge2.Edge());
    wire.Add(edge3.Edge());
    wire.Add(edge4.Edge());

    gp_Pln plane;
    create_3d_plane(p1,p2,p3,plane);

    // Create a face from the wire
    BRepBuilderAPI_MakeFace makeFace(plane, wire.Wire(), Standard_True);

    // Get the resulting face
    TopoDS_Face face = makeFace.Face();

    // Create an AIS_Shape from the resulting face
    return new AIS_Shape(face);
}

Handle(AIS_Shape) draw_primitives::draw_3d_pc_arc_closest(gp_Pnt point1,gp_Pnt point2,gp_Pnt center,gp_Dir dir ,gp_Pnt closest){

    gp_Circ circle(gp_Ax2( center, dir), point1.Distance(center));
    Standard_Real first, last;

    //! Cww or cw
    Handle(Geom_TrimmedCurve) aArcOfCircle1 = GC_MakeArcOfCircle(circle,point1,point2,0);
    TopoDS_Edge aEdge1 = BRepBuilderAPI_MakeEdge(aArcOfCircle1);

    Handle(Geom_Curve) aCurve1 = BRep_Tool::Curve(aEdge1, first, last);
    gp_Pnt pw1= aCurve1->Value((first+last)/2); //! Arc waypoint is more robust for defining a plane.

    //! Other dir.
    Handle(Geom_TrimmedCurve) aArcOfCircle2 = GC_MakeArcOfCircle(circle,point2,point1,0);
    TopoDS_Edge aEdge2 = BRepBuilderAPI_MakeEdge(aArcOfCircle2);
    Handle(Geom_Curve) aCurve2 = BRep_Tool::Curve(aEdge2, first, last);
    gp_Pnt pw2= aCurve2->Value((first+last)/2); //! Arc waypoint is more robust for defining a plane.

    double dist1=pw1.Distance(closest);
    double dist2=pw2.Distance(closest);

    if(dist1<dist2){
        return new AIS_Shape(aEdge1);
    }

    return new AIS_Shape(aEdge2);
}

Handle(AIS_Shape) draw_primitives::draw_3d_gcode_line(gp_Pnt p0, gp_Pnt p1, int gcode, gp_Pnt &pw){

    pw=get_line_midpoint(p0,p1);
    if(gcode==0){
        return colorize( draw_primitives::draw_3d_line(p0,p1),Quantity_NOC_GRAY15,0);
    }
    if(gcode==1){
        return colorize( draw_primitives::draw_3d_line(p0,p1),Quantity_NOC_GRAY50,0);
    }

    std::cout<<"Error draw 3d gcode line. Draws point."<<std::endl;
    return draw_3d_point(p0);
}

/*
p0 = circumfence point of circle.

plane:
    0=xy plane ,G17
    1=xz plane ,G18
    2=yz plane ,G19

gcode arc center:
    i=gcode I, center offset for x, seen from arc startpoint.
    j=gcode J, center offset for y, seen from arc startpoint.
    k=gcode K, center offset for z, seen from arc startpoint.
*/
gp_Pnt draw_primitives::get_circle_center(const gp_Pnt& p0, const int& plane,
                                          const double& i, const double& j, const double& k, gp_Pnt &pc){

    if(plane==0){
        pc={p0.X()+i, p0.Y()+j, p0.Z()};
    }
    if(plane==1){
        pc={p0.X()+i, p0.Y(), p0.Z()+k};
    }
    if(plane==2){
        pc={p0.X(), p0.Y()+j, p0.Z()+k};
    }
}

/*
p0 = starpoint of arc.
p1 = endpoint of arc.
pw = arc waypoint.

plane:
    0=xy plane ,G17
    1=xz plane ,G18
    2=yz plane ,G19

gcode:
    2=gcode G2, clockwise arc, cw.
    3=gcode G3, counter clockwise arc, ccw.

gcode arc center:
    i=gcode I, center offset for x, seen from arc startpoint.
    j=gcode J, center offset for y, seen from arc startpoint.
    k=gcode K, center offset for z, seen from arc startpoint.

turns:
    P=gcode P, nr of turns, rotations. Normally use zero.

*/
Handle(AIS_Shape) draw_primitives::draw_3d_gcode_arc_circle_helix(const gp_Pnt& p0, const gp_Pnt& p1, const int& plane, const int& gcode,
                                                                  const double& i, const double& j, const double& k,
                                                                  const int& turns, const int& g2_continuity, gp_Pnt &pw, double &lenght){

    pw={0,0,0}; // Init to zero.
    gp_Pnt pc;
    get_circle_center(p0,plane,i,j,k,pc);

    // Draw full circle.
    if(p0.Distance(p1)==0 && p0.Distance(pc)>0){
        lenght=get_3d_circle_lenght(p0,pc);
        pw=p0;
        if(plane==0){
            return colorize( draw_3d_pc_circle(pc,0,0,1,p1.Distance(pc)),Quantity_NOC_GRAY50,0);
        }
        if(plane==1){
            return colorize( draw_3d_pc_circle(pc,0,1,0,p1.Distance(pc)),Quantity_NOC_GRAY50,0);
        }
        if(plane==2){
            return colorize( draw_3d_pc_circle(pc,1,0,0,p1.Distance(pc)),Quantity_NOC_GRAY50,0);
        }
    }

    // Draw helix, spiral.
    if( (plane==0 && p0.Z()!=p1.Z()) || (plane==1 && p0.Y()!=p1.Y()) || (plane==2 && p0.X()!=p1.X()) ){
        return draw_2d_gcode_G2_G3_helix(p0,p1,plane,gcode,i,j,k,turns,g2_continuity,lenght);
    }

    // G2 arc plane 0
    if(gcode==2 && plane==0 && p0.Distance(p1)>0 && p0.Distance(pc)>0){
        Handle(AIS_Shape) aShape=colorize( draw_3d_pc_arc(p1,p0,pc,0,0,1,pw),Quantity_NOC_GRAY50,0);
        lenght=get_3d_arc_lenght(p0,pw,p1);
        return aShape;
    }
    // G2 arc plane 1
    if(gcode==2 && plane==1 && p0.Distance(p1)>0 && p0.Distance(pc)>0){
        Handle(AIS_Shape) aShape=colorize( draw_3d_pc_arc(p1,p0,pc,0,1,0,pw),Quantity_NOC_GRAY50,0);
        lenght=get_3d_arc_lenght(p0,pw,p1);
        return aShape;
    }
    // G2 arc plane 2
    if(gcode==2 && plane==2 && p0.Distance(p1)>0 && p0.Distance(pc)>0){
        Handle(AIS_Shape) aShape=colorize( draw_3d_pc_arc(p1,p0,pc,1,0,0,pw),Quantity_NOC_GRAY50,0);
        lenght=get_3d_arc_lenght(p0,pw,p1);
        return aShape;
    }

    // G3 arc plane 0
    if(gcode==3 && plane==0 && p0.Distance(p1)>0 && p0.Distance(pc)>0){
        Handle(AIS_Shape) aShape=colorize( draw_3d_pc_arc(p0,p1,pc,0,0,1,pw),Quantity_NOC_GRAY50,0);
        lenght=get_3d_arc_lenght(p0,pw,p1);
        return aShape;
    }
    // G3 arc plane 1
    if(gcode==3 && plane==1 && p0.Distance(p1)>0 && p0.Distance(pc)>0){
        Handle(AIS_Shape) aShape=colorize( draw_3d_pc_arc(p0,p1,pc,0,1,0,pw),Quantity_NOC_GRAY50,0);
        lenght=get_3d_arc_lenght(p0,pw,p1);
        return aShape;
    }
    // G3 arc plane 2
    if(gcode==3 && plane==2 && p0.Distance(p1)>0 && p0.Distance(pc)>0){
        Handle(AIS_Shape) aShape= colorize( draw_3d_pc_arc(p0,p1,pc,1,0,0,pw),Quantity_NOC_GRAY50,0);
        lenght=get_3d_arc_lenght(p0,pw,p1);
        return aShape;
    }

    std::cout<<"Error draw 3d gcode arc, circle. Draws point."<<std::endl;
    lenght=0;
    return draw_3d_point(p0);
}

Handle(AIS_Shape) draw_primitives::draw_3d_pc_arc(gp_Pnt point1,gp_Pnt point2,gp_Pnt center, double dir_Xv, double dir_Yv, double dir_Zv){

    gp_Pnt pw;
    return draw_3d_pc_arc(point1,point2,center,dir_Xv,dir_Yv,dir_Zv,pw);
}

Handle(AIS_Shape) draw_primitives::draw_3d_pc_arc(gp_Pnt point1,gp_Pnt point2,gp_Pnt center, double dir_Xv, double dir_Yv, double dir_Zv, gp_Pnt &pw){

    double radius=center.Distance(point1);
    gp_Dir dir(dir_Xv,dir_Yv,dir_Zv);
    gp_Circ circle(gp_Ax2( center, dir),radius);

    Handle(Geom_TrimmedCurve) aArcOfCircle;
    if(point1.Distance(point2)==0){
        aArcOfCircle = GC_MakeArcOfCircle(circle,0,2*M_PI,0);
    } else {
        aArcOfCircle = GC_MakeArcOfCircle(circle,point1,point2,0);
    }

    TopoDS_Edge aEdge = BRepBuilderAPI_MakeEdge(aArcOfCircle);

    Standard_Real first, last;
    Handle(Geom_Curve) aCurve1 = BRep_Tool::Curve(aEdge, first, last);
    pw=aCurve1->Value((first+last)/2); //! Arc waypoint.

    TopoDS_Edge aEdge2 = BRepBuilderAPI_MakeEdge(aArcOfCircle);
    return new AIS_Shape(aEdge2);
}

Handle(AIS_Shape) draw_primitives::draw_3p_3d_circle(gp_Pnt point1,gp_Pnt point2,gp_Pnt point3){
    Handle(Geom_Circle) aCircle = GC_MakeCircle(point1,point2,point3);
    TopoDS_Edge aEdge2 = BRepBuilderAPI_MakeEdge(aCircle);
    return new AIS_Shape(aEdge2);
}

Handle(AIS_Shape) draw_primitives::draw_2d_text(std::string str, int textheight, gp_Pnt point, double rot_deg){ //https://www.youtube.com/watch?v=31SXQLpdNyE

    const char *chartext=str.c_str();

    if(textheight==0 || textheight<0){textheight=1;}

    Font_BRepFont aBrepFont("/usr/share/fonts/truetype/dejavu/DejaVuSans-Bold.ttf", textheight);
    Font_BRepTextBuilder aTextBuilder;
    TopoDS_Shape a_text_shape = aTextBuilder.Perform(aBrepFont, NCollection_String(chartext));

    Handle(AIS_Shape) ais_shape_text = new AIS_Shape(a_text_shape);

    gp_Trsf MyTrsf_rot;
    MyTrsf_rot.SetRotation(gp_Ax1(gp_Pnt(
                                      0,
                                      0,
                                      0), gp_Dir(
                                      0,                         //rotation flag x
                                      0,                         //rotation flag y
                                      1)), rot_deg * M_PI /180);
    gp_Trsf MyTrsf_trans;
    MyTrsf_trans.SetTranslation(gp_Pnt(0,0,0),point);
    ais_shape_text->SetLocalTransformation(MyTrsf_trans*MyTrsf_rot);
    return ais_shape_text;
}

Handle(AIS_Shape) draw_primitives::draw_3d_point_origin_cone(gp_Pnt point, gp_Pnt euler){

    Handle(AIS_Shape) Ais_shape=draw_3d_point(point);
    Ais_shape=colorize(Ais_shape,Quantity_NOC_BLUE,0);

    // Draw the origin
    Handle(AIS_Shape) Ais_child=draw_3d_origin({0,0,0},25);
    Ais_child=rotate_translate_3d_quaternion(Ais_child,point,
                                             euler.Z(),
                                             euler.Y(),
                                             euler.X());
    Ais_shape->AddChild(Ais_child);

    // Draw the cone
    Ais_child=draw_3d_tcp_cone({0,0,0},0,5,25);
    Ais_child=rotate_translate_3d_quaternion(Ais_child,point,
                                             euler.Z(),
                                             euler.Y(),
                                             euler.X());

    Ais_child=colorize(Ais_child,Quantity_NOC_RED,0.5);
    Ais_shape->AddChild(Ais_child);

    return Ais_shape;
}

Handle(AIS_Shape) draw_primitives::draw_3d_point_origin_cone_text(gp_Pnt point, gp_Pnt euler, std::string text, int textheight, int textrotation){

    Handle(AIS_Shape) Ais_shape=draw_3d_point_origin_cone(point, euler);
    Ais_shape=colorize(Ais_shape,Quantity_NOC_RED,0);
    Handle(AIS_Shape) Ais_text=draw_2d_text(text, textheight, point, textrotation);
    Ais_text=colorize(Ais_text,Quantity_NOC_BLACK,0.5);
    Ais_shape->AddChild(Ais_text);
    return Ais_shape;
}

Handle(AIS_Shape) draw_primitives::draw_3d_line_origin_cone_text(gp_Pnt point1, gp_Pnt point2, gp_Pnt euler1, gp_Pnt euler2, std::string text, int textheight){

    // Draw the line
    Handle(AIS_Shape) Ais_shape=draw_3d_line(point1,point2);
    Ais_shape=draw_primitives().colorize(Ais_shape,Quantity_NOC_BLUE,0);

    // Draw the first origin
    Handle(AIS_Shape) Ais_child=draw_primitives().draw_3d_origin({0,0,0},25);
    Ais_child=rotate_translate_3d_quaternion(Ais_child,point1,
                                             euler1.Z(),
                                             euler1.Y(),
                                             euler1.X());
    Ais_shape->AddChild(Ais_child);

    // Draw the second origin
    Ais_child=draw_primitives().draw_3d_origin({0,0,0},50);
    Ais_child=rotate_translate_3d_quaternion(Ais_child,point2,
                                             euler2.Z(),
                                             euler2.Y(),
                                             euler2.X());
    Ais_shape->AddChild(Ais_child);

    // Draw the first cone
    Ais_child=draw_primitives().draw_3d_tcp_cone({0,0,0},0,5,25);
    Ais_child=draw_primitives().colorize(Ais_child,Quantity_NOC_GREEN,0.5);
    Ais_child=draw_primitives().rotate_translate_3d_quaternion(Ais_child,point1,
                                                               euler1.Z(),
                                                               euler1.Y(),
                                                               euler1.X());
    Ais_shape->AddChild(Ais_child);

    // Draw the second cone
    Ais_child=draw_primitives().draw_3d_tcp_cone({0,0,0},0,5,25);
    Ais_child=draw_primitives().colorize(Ais_child,Quantity_NOC_BLACK,0.5);
    Ais_child=draw_primitives().rotate_translate_3d_quaternion(Ais_child,point2,
                                                               euler2.Z(),
                                                               euler2.Y(),
                                                               euler2.X());
    Ais_shape->AddChild(Ais_child);

    // Draw the text id.
    Handle(AIS_Shape) Ais_text=draw_2d_text(text, textheight, get_line_midpoint(point1,point2), 0);
    Ais_text=colorize(Ais_text,Quantity_NOC_BLACK,0.5);
    Ais_shape->AddChild(Ais_text);

    return Ais_shape;
}

Handle(AIS_Shape) draw_primitives::draw_3d_wire_origin_cone_text(std::vector<gp_Pnt> points, std::vector<gp_Pnt> euler, std::string text, int textheight){
    BRepBuilderAPI_MakeWire wire;
    for(unsigned int i=0; i<points.size()-1; i++){
        TopoDS_Edge edge = BRepBuilderAPI_MakeEdge(points.at(i),points.at(i+1));
        wire.Add(edge);
    }
    Handle(AIS_Shape) Ais_shape=new AIS_Shape(wire);
    Ais_shape=colorize(Ais_shape,Quantity_NOC_BLUE,0);

    for(unsigned int i=0; i<points.size(); i++){
        // Draw the origin
        Handle(AIS_Shape) Ais_child=draw_3d_origin({0,0,0},25);
        Ais_child=rotate_translate_3d_quaternion(Ais_child,points.at(i),
                                                 euler.at(i).Z(),
                                                 euler.at(i).Y(),
                                                 euler.at(i).X());
        Ais_shape->AddChild(Ais_child);

        // Draw the cone
        Ais_child=draw_3d_tcp_cone({0,0,0},0,5,25);
        Ais_child=rotate_translate_3d_quaternion(Ais_child,points.at(i),
                                                 euler.at(i).Z(),
                                                 euler.at(i).Y(),
                                                 euler.at(i).X());
        if(i==0){
            Ais_child=colorize(Ais_child,Quantity_NOC_GREEN,0.5);
        } else if(i==points.size()-1){
            Ais_child=colorize(Ais_child,Quantity_NOC_BLACK,0.5);
        } else {
            Ais_child=colorize(Ais_child,Quantity_NOC_BLUE,0.5);
        }

        Ais_shape->AddChild(Ais_child);
    }

    // Draw the text id.
    for(unsigned int i=0; i<points.size()-1; i++){
        std::string subidtext=text+"."+std::to_string(i);
        Handle(AIS_Shape) Ais_text=draw_2d_text(subidtext, textheight, get_line_midpoint(points.at(i),points.at(i+1)), 0);
        Ais_text=colorize(Ais_text,Quantity_NOC_BLACK,0.5);
        Ais_shape->AddChild(Ais_text);
    }

    return Ais_shape;
}

Handle(AIS_Shape) draw_primitives::draw_3d_arc_origin_cone_text(std::vector<gp_Pnt> points, std::vector<gp_Pnt> euler, std::string text, int textheight){

    Handle(AIS_Shape) Ais_shape=draw_3p_3d_arc(points.at(0),points.at(1),points.at(2));
    Ais_shape=colorize(Ais_shape,Quantity_NOC_BLUE,0);

    for(unsigned int i=0; i<points.size(); i++){
        // Draw the origin
        Handle(AIS_Shape) Ais_child=draw_3d_origin({0,0,0},25);
        Ais_child=rotate_translate_3d_quaternion(Ais_child,points.at(i),
                                                 euler.at(i).Z(),
                                                 euler.at(i).Y(),
                                                 euler.at(i).X());
        Ais_shape->AddChild(Ais_child);

        // Draw the cone
        Ais_child=draw_3d_tcp_cone({0,0,0},0,5,25);
        Ais_child=rotate_translate_3d_quaternion(Ais_child,points.at(i),
                                                 euler.at(i).Z(),
                                                 euler.at(i).Y(),
                                                 euler.at(i).X());
        if(i==0){
            Ais_child=colorize(Ais_child,Quantity_NOC_GREEN,0.5);
        } else if(i==points.size()-1){
            Ais_child=colorize(Ais_child,Quantity_NOC_BLACK,0.5);
        } else {
            Ais_child=colorize(Ais_child,Quantity_NOC_BLUE,0.5);
        }

        Ais_shape->AddChild(Ais_child);
    }

    // Draw the text id.
    Handle(AIS_Shape) Ais_text=draw_2d_text(text, textheight, points.at(1) /*midpoint*/, 0);
    Ais_text=colorize(Ais_text,Quantity_NOC_BLACK,0.5);
    Ais_shape->AddChild(Ais_text);

    return Ais_shape;
}

Handle(AIS_Shape) draw_primitives::draw_3d_circle_origin_cone_text(std::vector<gp_Pnt> points, std::vector<gp_Pnt> euler, std::string text, int textheight){

    Handle(AIS_Shape) Ais_shape=draw_3p_3d_circle(points.at(0),points.at(1),points.at(2));
    Ais_shape=colorize(Ais_shape,Quantity_NOC_BLUE,0);

    for(unsigned int i=0; i<points.size(); i++){
        // Draw the origin
        Handle(AIS_Shape) Ais_child=draw_3d_origin({0,0,0},25);
        Ais_child=rotate_translate_3d_quaternion(Ais_child,points.at(i),
                                                 euler.at(i).Z(),
                                                 euler.at(i).Y(),
                                                 euler.at(i).X());
        Ais_shape->AddChild(Ais_child);

        // Draw the cone
        Ais_child=draw_3d_tcp_cone({0,0,0},0,5,25);
        Ais_child=rotate_translate_3d_quaternion(Ais_child,points.at(i),
                                                 euler.at(i).Z(),
                                                 euler.at(i).Y(),
                                                 euler.at(i).X());
        if(i==0){
            Ais_child=colorize(Ais_child,Quantity_NOC_GREEN,0.5);
        } else if(i==points.size()-1){
            Ais_child=colorize(Ais_child,Quantity_NOC_BLACK,0.5);
        } else {
            Ais_child=colorize(Ais_child,Quantity_NOC_BLUE,0.5);
        }

        Ais_shape->AddChild(Ais_child);
    }

    // Draw the text id.
    Handle(AIS_Shape) Ais_text=draw_2d_text(text, textheight, points.at(1) /*midpoint*/, 0);
    Ais_text=colorize(Ais_text,Quantity_NOC_BLACK,0.5);
    Ais_shape->AddChild(Ais_text);

    return Ais_shape;
}

gp_Pnt draw_primitives::get_line_midpoint(gp_Pnt point1, gp_Pnt point2){
    gp_Pnt midpoint;
    midpoint.SetX((point1.X()+point2.X())/2);
    midpoint.SetY((point1.Y()+point2.Y())/2);
    midpoint.SetZ((point1.Z()+point2.Z())/2);
    return midpoint;
}

double draw_primitives::get_line_lenght(gp_Pnt p1, gp_Pnt p2){
    // Calculate the differences in each coordinate
    double dx = p2.X() - p1.X();
    double dy = p2.Y() - p1.Y();
    double dz = p2.Z() - p1.Z();

    // Use the Euclidean distance formula
    return std::sqrt(dx*dx + dy*dy + dz*dz);
}

double draw_primitives::waypoint_to_bulge(gp_Pnt p1, gp_Pnt pw, gp_Pnt p2) {
    // Calculate the vectors from p1 to p2 and from p1 to pw
    gp_Vec vec_p1p2(p2.X() - p1.X(), p2.Y() - p1.Y(), 0); // Assuming 2D, so Z-coordinate is 0
    gp_Vec vec_p1pw(pw.X() - p1.X(), pw.Y() - p1.Y(), 0); // Assuming 2D, so Z-coordinate is 0

    // Calculate the dot product of the vectors to determine the cosine of the angle between them
    double dot_product = vec_p1p2.Dot(vec_p1pw);

    // Calculate the lengths of the vectors
    double length_p1p2 = vec_p1p2.Magnitude();
    double length_p1pw = vec_p1pw.Magnitude();

    // Calculate the angle between the vectors using the dot product
    double cos_angle = dot_product / (length_p1p2 * length_p1pw);
    double angle = acos(cos_angle);

    // Use the atan2 function to determine the direction of rotation
    double sign = atan2(vec_p1p2.X() * vec_p1pw.Y() - vec_p1p2.Y() * vec_p1pw.X(), dot_product) > 0 ? 1.0 : -1.0;

    sign*=-1; // This is a bug fix.

    // Check if p1 equals p2
    if (p1.IsEqual(p2, Precision::Confusion())) {
        // std::cout << "The arc is full circle." << sign << std::endl;
        return sign;  // Return ±1 for full circle based on direction
    }

    // Calculate the midpoint between p1 and p2
    gp_Pnt pm = draw_primitives().get_line_midpoint(p1, p2);

    // Calculate the distance from the midpoint to pw
    double d1 = draw_primitives().get_line_lenght(pm, pw);

    // Calculate the length of the line segment from p1 to p2
    double l = draw_primitives().get_line_lenght(p1, p2);

    // Bulge factor calculation
    double bulge = sign * d1 / (l / 2);

    // Debugging output to indicate direction
    if (bulge > 0) {
        // std::cout << "The arc is curving counter-clockwise (CCW)." << bulge << std::endl;
    } else {
        // std::cout << "The arc is curving clockwise (CW)." << bulge << std::endl;
    }

    return bulge;
}

std::vector<Handle(AIS_Shape)> draw_primitives::draw_3d_arc_lenght(gp_Pnt point1,gp_Pnt point2,gp_Pnt point3){

    std::vector<Handle(AIS_Shape)> shapevec;

    Handle(Geom_TrimmedCurve) aArcOfCircle = GC_MakeArcOfCircle(point1,point2,point3);

    TopoDS_Edge aEdge2 = BRepBuilderAPI_MakeEdge(aArcOfCircle);

    GeomAdaptor_Curve acrv(aArcOfCircle);
    TColgp_Array1OfPnt pkte(0, 10);
    GCPnts_UniformAbscissa algo(acrv, 10);
    if(algo.IsDone() && algo.NbPoints() > 0)
    {
        int n = algo.NbPoints();
        // std::cout<<"total points:"<<n<<std::endl;
        // std::cout<<"abscissa dist:"<<algo.Abscissa()<<std::endl; // Distance between the points. Totalcurvelenght = (points-1)*abscissa dist.

        for(int i=1; i<algo.NbPoints()+1; i++){
            double param = algo.Parameter(i);
            gp_Pnt p = aArcOfCircle->Value(param);
            // std::cout<<"Px:"<<p.X()<< " Py:" << p.Y() << " Pz:" << p.Z() <<std::endl;

            Handle(AIS_Shape) Ais_shape=draw_3d_sphere(5,p);
            Ais_shape=colorize(Ais_shape,Quantity_NOC_BLUE,0);
            shapevec.push_back(Ais_shape);
        }

        double curvelenght=0;
        curvelenght=(algo.NbPoints()-1)*algo.Abscissa();
        // std::cout<<"curvelenght:"<<curvelenght<<std::endl;
    }
    return shapevec;
}

// Function to calculate the radius and center of an arc given three points
void draw_primitives::get_3d_arc_radius_and_center(const gp_Pnt& p0, const gp_Pnt& pw, const gp_Pnt& p1, double& radius, gp_Pnt& center) {
    // Convert points to Eigen vectors
    gp_Vec pa(p0.X(), p0.Y(), p0.Z());
    gp_Vec pb(pw.X(), pw.Y(), pw.Z());
    gp_Vec pc(p1.X(), p1.Y(), p1.Z());

    // Calculate vectors
    gp_Vec v1 = pb - pa;
    gp_Vec v2 = pc - pa;

    // Calculate dot products
    double v1v1 = v1.Dot(v1);
    double v2v2 = v2.Dot(v2);
    double v1v2 = v1.Dot(v2);

    // Calculate coefficients
    double base = 0.5 / (v1v1 * v2v2 - v1v2 * v1v2);
    double k1 = base * v2v2 * (v1v1 - v1v2);
    double k2 = base * v1v1 * (v2v2 - v1v2);

    // Calculate center of the arc
    gp_Vec pcenter = pa + v1 * k1 + v2 * k2;

    // Calculate radius
    radius = (pcenter - pa).Magnitude();

    // Convert center back to gp_Pnt
    center = gp_Pnt(pcenter.X(), pcenter.Y(), pcenter.Z());
}

void draw_primitives::get_3d_arc_angle_radians(const gp_Pnt& p0, const gp_Pnt& pw, const gp_Pnt& p1, double &theta) {
    // Calculate vectors
    gp_Vec vec1(p0, pw);
    gp_Vec vec2(p1, pw);

    // Calculate the dot product of the vectors
    double dot = vec1.Dot(vec2);

    // Calculate the magnitudes of the vectors
    double mag1 = vec1.Magnitude();
    double mag2 = vec2.Magnitude();

    // Calculate the cosine of the angle
    double cosTheta = dot / (mag1 * mag2);

    // Ensure the cosine value is within the valid range [-1, 1] to avoid domain errors in acos
    if (cosTheta > 1.0) cosTheta = 1.0;
    if (cosTheta < -1.0) cosTheta = -1.0;

    // Calculate the angle in radians
    theta = std::acos(cosTheta);
}

// Line p0,p1
gp_Pnt draw_primitives::rotate_point_around_line(const gp_Pnt& p_to_rotate, double theta, const gp_Pnt& p0, const gp_Pnt& p1) {

    double costheta, sintheta;
    gp_Pnt r(p1.X() - p0.X(), p1.Y() - p0.Y(), p1.Z() - p0.Z());
    gp_Pnt pointVec(p_to_rotate.X() - p0.X(), p_to_rotate.Y() - p0.Y(), p_to_rotate.Z() - p0.Z());

    // Normalize r
    double rLength = sqrt(r.X() * r.X() + r.Y() * r.Y() + r.Z() * r.Z());
    r.SetX(r.X() / rLength);
    r.SetY(r.Y() / rLength);
    r.SetZ(r.Z() / rLength);

    costheta = cos(theta);
    sintheta = sin(theta);

    // Calculate the rotated coordinates
    double qx = (costheta + (1 - costheta) * r.X() * r.X()) * pointVec.X();
    qx += ((1 - costheta) * r.X() * r.Y() - r.Z() * sintheta) * pointVec.Y();
    qx += ((1 - costheta) * r.X() * r.Z() + r.Y() * sintheta) * pointVec.Z();

    double qy = ((1 - costheta) * r.X() * r.Y() + r.Z() * sintheta) * pointVec.X();
    qy += (costheta + (1 - costheta) * r.Y() * r.Y()) * pointVec.Y();
    qy += ((1 - costheta) * r.Y() * r.Z() - r.X() * sintheta) * pointVec.Z();

    double qz = ((1 - costheta) * r.X() * r.Z() - r.Y() * sintheta) * pointVec.X();
    qz += ((1 - costheta) * r.Y() * r.Z() + r.X() * sintheta) * pointVec.Y();
    qz += (costheta + (1 - costheta) * r.Z() * r.Z()) * pointVec.Z();

    // Set the rotated coordinates to the resulting point
    gp_Pnt q;
    q.SetX(qx + p0.X());
    q.SetY(qy + p0.Y());
    q.SetZ(qz + p0.Z());
    return q;
}

int draw_primitives::get_3d_arc_angle_rad_center(const gp_Pnt &p0, const gp_Pnt &pw, const gp_Pnt &p1, double &angle_rad, gp_Pnt &pc) {

    // Check if p0 and p1 are the same point
    if (p0.X() == p1.X() && p0.Y() == p1.Y() && p0.Z() == p1.Z()) {
        // std::cout << "error, is circle, use circle interpolation function." << std::endl;
        return 0;
    }

    // Convert points to Eigen vectors
    Eigen::Vector3d p00(p0.X(), p0.Y(), p0.Z());
    Eigen::Vector3d pww(pw.X(), pw.Y(), pw.Z());
    Eigen::Vector3d p11(p1.X(), p1.Y(), p1.Z());

    // Calculate vectors from p0 to pw and p0 to p1
    Eigen::Vector3d v1 = pww - p00;
    Eigen::Vector3d v2 = p11 - p00;

    // Calculate dot products
    double v1v1 = v1.dot(v1);
    double v2v2 = v2.dot(v2);
    double v1v2 = v1.dot(v2);

    // Base calculation for coefficients
    double denom = v1v1 * v2v2 - v1v2 * v1v2;
    if (std::abs(denom) < 1e-12) { // Check for small denominator
        // std::cout << "error, points are too close or collinear." << std::endl;
        return 0;
    }
    double base = 0.5 / denom;
    double k1 = base * v2v2 * (v1v1 - v1v2);
    double k2 = base * v1v1 * (v2v2 - v1v2);

    // Calculate the center of the arc
    Eigen::Vector3d pc_vec = p00 + v1 * k1 + v2 * k2;
    pc = { pc_vec.x(), pc_vec.y(), pc_vec.z() };

    // Calculate normalized vectors for arc angle
    Eigen::Vector3d va = (p00 - pc_vec).normalized();
    Eigen::Vector3d vb = (p11 - pc_vec).normalized();

    // Arc direction, in arc plane between p1, p3 or v1, v2
    Eigen::Vector3d n = v1.cross(v2);
    double nl = n.norm();
    if (nl < 1e-12) { // Check for small norm
        // std::cout << "error, vectors are collinear." << std::endl;
        return 0;
    }
    Eigen::Vector3d axis = n / nl;
    Eigen::Vector3d an = axis.normalized();

    // Calculate arc angle using dot product, clamp the dot product to [-1, 1] to avoid NaN
    double dot_product = va.dot(vb);
    dot_product = std::max(-1.0, std::min(1.0, dot_product));
    angle_rad = acos(dot_product);

    // Check the sign of the angle
    Eigen::Vector3d vab = va.cross(vb);
    if (vab.dot(an) < 0) {
        angle_rad = 2 * M_PI - angle_rad;
    }
    return 1;
}

// Validated on xy plane fwd & rev ok. Left for info.
double draw_primitives::get_3d_arc_lenght(const gp_Pnt &p0, const gp_Pnt &pw, const gp_Pnt &p1){

    gp_Pnt pc;
    double angle_rad;
    int r=get_3d_arc_angle_rad_center(p0,pw,p1,angle_rad,pc);
    if(r==0){
        // std::cout<<"arc lenght error."<<std::endl;
        return 0;
    }

    // std::cout<<"angle rad:"<<angle_rad<<std::endl;
    double radius=p0.Distance(pc);
    // std::cout<<"radius:"<<radius<<std::endl;
    return angle_rad*radius;
}

double draw_primitives::get_3d_circle_lenght(const gp_Pnt &p0, const gp_Pnt &pc){
    double radius = pc.Distance(p0);
    double circumference = 2 * M_PI * radius;
    return circumference;
}

double draw_primitives::get_3d_pvec_lenght(const std::vector<gp_Pnt> &pvec){

    double ltot;
    for(uint i=0; i<pvec.size()-1; i++){
        double l=pvec[i].Distance(pvec[i+1]);
        ltot+=l;
    }
    return ltot;
}

// Validated on xy plane fwd & rev ok. Left for info.
void draw_primitives::interpolate_point_on_arc(const gp_Pnt &p0, const gp_Pnt &pw, const gp_Pnt &p1, const double &progress, gp_Pnt &pi){

    if(p0.X()==p1.X() && p0.Y()==p1.Y() && p0.Z()==p1.Z()){
        // std::cout<<"error, is circle, use circle interpolation function."<<std::endl;
        return;
    }

    gp_Pnt pc;
    double radius;
    get_3d_arc_radius_and_center(p0,pw,p1,radius,pc);

    Eigen::Vector3d p00(p0.X(),p0.Y(),p0.Z());
    Eigen::Vector3d pww(pw.X(),pw.Y(),pw.Z());
    Eigen::Vector3d p11(p1.X(),p1.Y(),p1.Z());

    Eigen::Vector3d v1 = pww-p00;
    Eigen::Vector3d v2 = p11-p00;
    double v1v1, v2v2, v1v2;
    v1v1 = v1.dot(v1);
    v2v2 = v2.dot(v2);
    v1v2 = v1.dot(v2);

    double base = 0.5/(v1v1*v2v2-v1v2*v1v2);
    double k1 = base*v2v2*(v1v1-v1v2);
    double k2 = base*v1v1*(v2v2-v1v2);

    //! Center of arc.
    Eigen::Vector3d pc_vec = p00 + v1*k1 + v2*k2;

    //! Arc angle.
    Eigen::Vector3d va=(p00-pc_vec).normalized();
    Eigen::Vector3d vb=(p11-pc_vec).normalized();

    //! Arc direction, in arc plane between p1,p3 or v1,v2, doesn't really matter.
    Eigen::Vector3d n=v1.cross(v2);
    double nl=n.norm();
    Eigen::Vector3d axis=n/sqrt(nl);
    Eigen::Vector3d an=axis.normalized();
    double angle=acos(va.dot(vb));

    Eigen::Vector3d vab=va.cross(vb);
    double dot=vab.dot(an);
    if(dot<0){
        double diff=M_PI-angle;
        angle=M_PI+diff;
    }

    pi=rotate_point_around_line(p0,progress*angle,pc,{pc.X()+an.x(),pc.Y()+an.y(),pc.Z()+an.z()});
}

void draw_primitives::interpolate_point_on_circle(const gp_Pnt &p0, const gp_Pnt &pc, const int &plane, const int &gcode, const double &progress, gp_Pnt &pi){

    gp_Dir dir;
    if (plane == 0) {
        dir = gp_Dir(0, 0, 1);
    } else if (plane == 1) {
        dir = gp_Dir(0, 1, 0);
    } else if (plane == 2) {
        dir = gp_Dir(1, 0, 0);
    } else {
        throw std::invalid_argument("Invalid plane value. Expected 0, 1, or 2.");
    }

    double angle;
    if (gcode == 2) { // Interpolate clockwise
        angle = -progress * 2 * M_PI;
    } else if (gcode == 3) { // Interpolate counter-clockwise
        angle = progress * 2 * M_PI;
    } else {
        throw std::invalid_argument("Invalid gcode value. Expected 2 or 3.");
    }

    // Calculate the interpolated point on the circle
    gp_Trsf rotation;
    rotation.SetRotation(gp_Ax1(pc, dir), angle);
    pi = p0.Transformed(rotation);
}

void draw_primitives::print_gp_Pnt(gp_Pnt pnt){
    std::cout<<"pnt x:"<<pnt.X()<<" y:"<<pnt.Y()<<" z:"<<pnt.Z()<<std::endl;
}

void draw_primitives::print_gp_Pnt(std::string text, gp_Pnt pnt){
    std::cout<<text<<" pnt x:"<<pnt.X()<<" y:"<<pnt.Y()<<" z:"<<pnt.Z()<<std::endl;
}

gp_Pnt draw_primitives::get_point(Handle(AIS_Shape) shape){
    gp_Pnt p1(0,0,0);
    TopExp_Explorer explorer(shape->Shape(), TopAbs_VERTEX);
    if (explorer.More()) {
        explorer.Next();
        if (!explorer.More()) {

            TopoDS_Vertex aVertex = TopoDS::Vertex(explorer.Current());
            p1 = BRep_Tool::Pnt(aVertex);
            // std::cout << "The shape is a point." << std::endl;

        }
    }
    return p1;
}

// Tested ok.
bool draw_primitives::intersect_3d_sphere_sphere(gp_Pnt pc1, double radius1, gp_Pnt pc2, double radius2, gp_Pnt &pi)
{

    // Create the first sphere
    TopoDS_Shape sphere1 = BRepPrimAPI_MakeSphere(pc1, radius1);

    // Create the second sphere
    TopoDS_Shape sphere2 = BRepPrimAPI_MakeSphere(pc2, radius2);

    // Find the intersection between the two spheres
    BRepAlgoAPI_Section section(sphere1, sphere2);
    section.Build();
    if (section.IsDone()) {
        // Get the intersection result
        TopoDS_Shape intersectionShape = section.Shape();

        // Display the intersection points
        for (TopExp_Explorer explorer(intersectionShape, TopAbs_VERTEX); explorer.More(); explorer.Next()) {
            TopoDS_Vertex vertex = TopoDS::Vertex(explorer.Current());
            pi = BRep_Tool::Pnt(vertex);

        }
    } else {
        // std::cout << "No intersection found between the spheres." << std::endl;
        return 0;
    }
    return 1;
}

void draw_primitives::get_closest_point_to_line(gp_Pnt point, Handle(AIS_Shape) shape, gp_Pnt &intersection){

    gp_Pnt p1,p2;
    get_line_points(shape,p1,p2);
    get_closest_point_to_line(point,p1,p2,intersection);
}

// This finds a intersection point on a given line, where the given point is in space somewhere.
// The intersection point is the closest line between space point & given line.
void draw_primitives::get_closest_point_to_line( gp_Pnt point, gp_Pnt line_start, gp_Pnt line_end, gp_Pnt &intersection )
{
    double U;
    double LineMag = line_end.Distance(line_start);

    U = ( ( ( point.X() - line_start.X() ) * ( line_end.X() - line_start.X() ) ) +
          ( ( point.Y() - line_start.Y() ) * ( line_end.Y() - line_start.Y() ) ) +
          ( ( point.Z() - line_start.Z() ) * ( line_end.Z() - line_start.Z() ) ) ) /
            ( LineMag * LineMag );

    //if( U < 0.0f || U > 1.0f ) //! If you need it valid if on the line.
    // return 0;   // closest point does not fall within the line segment

    intersection.SetX( line_start.X() + U * ( line_end.X() - line_start.X() ) );
    intersection.SetY( line_start.Y() + U * ( line_end.Y() - line_start.Y() ) );
    intersection.SetZ( line_start.Z() + U * ( line_end.Z() - line_start.Z() ) );
}

void draw_primitives::offset_3d_point_on_line(gp_Pnt A, gp_Pnt B, double offset_a, gp_Pnt &C){

    //    A-----------B------------C
    // (Xa,Ya)     (Xb,Yb)      (Xc,Yc)

    C.SetX( A.X() + (offset_a * (B.X() - A.X()) / (A.Distance(B)) ) );
    C.SetY( A.Y() + (offset_a * (B.Y() - A.Y()) / (A.Distance(B)) ) );
    C.SetZ( A.Z() + (offset_a * (B.Z() - A.Z()) / (A.Distance(B)) ) );

    if(A.Distance(B)==0){
        C=A;
    }
}

//! This only returns 0 or 2 solutions.
bool draw_primitives::intersect_3d_line_sphere(gp_Pnt cp, gp_Pnt p0, gp_Pnt p1, double radius, gp_Pnt &pi){

    double cx = cp.X();
    double cy = cp.Y();
    double cz = cp.Z();

    double px = p0.X();
    double py = p0.Y();
    double pz = p0.Z();

    double vx = p1.X() - px;
    double vy = p1.Y() - py;
    double vz = p1.Z() - pz;

    double A = vx * vx + vy * vy + vz * vz;
    double B = 2.0 * (px * vx + py * vy + pz * vz - vx * cx - vy * cy - vz * cz);
    double C = px * px - 2 * px * cx + cx * cx + py * py - 2 * py * cy + cy * cy +
            pz * pz - 2 * pz * cz + cz * cz - radius * radius;

    //! discriminant
    double D = B * B - 4 * A * C;
    // std::cout<<"D:"<<D<<std::endl;

    if(D<0){
        // std::cout<<"3d_line_sphere, no intersections found in general."<<std::endl;
        return 0;
    }

    double t1 = (-B - Sqrt(D)) / (2.0 * A);
    // std::cout<<"T1:"<<t1<<std::endl;

    gp_Pnt solution1, solution2;

    solution1.SetX(p0.X() * (1 - t1) + t1 * p1.X());
    solution1.SetY(p0.Y() * (1 - t1) + t1 * p1.Y());
    solution1.SetZ(p0.Z() * (1 - t1) + t1 * p1.Z());

    double t2 = (-B + Sqrt(D)) / (2.0 * A);
    // std::cout<<"T2:"<<t2<<std::endl;

    solution2.SetX(p0.X() * (1 - t2) + t2 * p1.X());
    solution2.SetY(p0.Y() * (1 - t2) + t2 * p1.Y());
    solution2.SetZ(p0.Z() * (1 - t2) + t2 * p1.Z());

    if(is_point_on_line(p0,p1,solution2)){
        pi=solution2;
        return 1;
    }
    if(is_point_on_line(p0,p1,solution1)){
        pi=solution1;
        return 1;
    }

    return 0;
}

bool draw_primitives::intersect_line_arc_sphere(Handle(AIS_Shape) lineShape, Handle(AIS_Shape) arcShape, gp_Pnt sphere_pc, double sphere_radius){

    gp_Pnt p1,p2,pi1;
    get_line_points(lineShape,p1,p2);

    gp_Pnt p3,p4,pw,pc,pi2;
    get_arc_points(arcShape,p3,p4,pw,pc);
    double r=get_arc_radius(arcShape);

    //! Intersect lineShape with sphere.
    if(intersect_3d_line_sphere(sphere_pc,p1,p2,sphere_radius,pi1)){
        // one intersect ok.
    } else {
        return 0;
    }

    //! Intersect arcShape with sphere.
    if(intersect_3d_sphere_sphere(sphere_pc,sphere_radius,pc,r,pi2)){
        // one intersect ok.
    } else {
        return 0;
    }

    //! Are intersection points on the curve?
    if(is_point_on_line(lineShape,pi1)==1 && is_point_on_arc(arcShape,pi2)==1){
        return 1;
    }

    return 0;
}

bool draw_primitives::create_3d_plane(gp_Pnt p_origin, gp_Pnt p2, gp_Pnt p3, gp_Pln &plane) {
    // Define vectors using gp_Vec (Open CASCADE vectors)
    gp_Vec v1(p2, p_origin);
    gp_Vec v2(p3, p_origin);

    // Check if vectors are valid (not zero length)
    if (v1.Magnitude() == 0 || v2.Magnitude() == 0) {
        // std::cout << "One of the vectors is zero length" << std::endl;
        return false;
    }

    // Normalize vectors
    v1.Normalize();
    v2.Normalize();

    // Calculate angle between vectors
    double angle = v1.Angle(v2);

    // Check if vectors are collinear (angle is 0 or 180 degrees)
    if (std::abs(angle * toDegrees - 180.0) < 1e-6 || std::abs(angle * toDegrees) < 1e-6) {
        // std::cout << "Inputs are collinear" << std::endl;
        return false;
    }

    // Calculate normal vector for the plane
    gp_Vec n = v1.Crossed(v2);

    // Check if the cross product is a valid vector (not zero length)
    if (n.Magnitude() == 0) {
        // std::cout << "Cross product resulted in zero vector, inputs may be collinear" << std::endl;
        return false;
    }

    // Normalize the normal vector
    n.Normalize();

    // Create the direction for the plane's normal
    gp_Dir dir(n.X(), n.Y(), n.Z());

    // Create the plane passing through p_origin with direction dir
    gp_Pln p(p_origin, dir);
    plane = p;

    return true;
}

//! This function finds the common intersection point. Opencascade has no logic about arc start, arc endpoints.
//! The result is a intersection set at line_p1 to arc_p0
void draw_primitives::organize_line_arc_points(gp_Pnt &line_p0, gp_Pnt &line_p1, gp_Pnt &arc_p0, gp_Pnt &arc_p1){

    gp_Pnt p0=line_p0;
    gp_Pnt p1=line_p1;
    gp_Pnt a0=arc_p0;
    gp_Pnt a1=arc_p1;

    //! Find if line_p0 with arc_p0 match intersect.
    if(line_p0.Distance(arc_p0)<line_p0.Distance(arc_p1) && line_p0.Distance(arc_p0)<line_p1.Distance(arc_p0) ){
        line_p0=p1;
        line_p1=p0;
        arc_p0=a0;
        arc_p1=a1;
        return;
    }
    //! Find if line_p0 with arc_p1 match intersect.
    if(line_p0.Distance(arc_p1)<line_p0.Distance(arc_p0) && line_p0.Distance(arc_p1)<line_p1.Distance(arc_p1) ){
        line_p0=p1;
        line_p1=p0;
        arc_p0=a1;
        arc_p1=a0;
        return;
    }
    //! Find if line_p1 with arc_p0 match intersect.
    if(line_p1.Distance(arc_p0)<line_p1.Distance(arc_p1) && line_p1.Distance(arc_p0)<line_p0.Distance(arc_p0) ){
        line_p0=p0;
        line_p1=p1;
        arc_p0=a0;
        arc_p1=a1;
        return;
    }
    //! Find if line_p1 with arc_p1 match intersect.
    if(line_p1.Distance(arc_p1)<line_p1.Distance(arc_p0) && line_p1.Distance(arc_p1)<line_p0.Distance(arc_p1) ){
        line_p0=p0;
        line_p1=p1;
        arc_p0=a1;
        arc_p1=a0;
        return;
    }
}

//! This function creates a transformation matrix, where x axis is p0-p1, given a third point on a plane.
gp_Trsf draw_primitives::create_transformation_matrix(gp_Pnt p0, gp_Pnt p1, gp_Pnt point_on_plane){

    // Calculate vectors
    gp_Vec x_axis(p0, p1);
    x_axis.Normalize();
    gp_Vec v2(p0,point_on_plane);

    // Calculate the normal vector using cross product
    gp_Vec z_axis = x_axis.Crossed(v2).Normalized();
    z_axis.Normalize();

    gp_Vec y_axis = z_axis.Crossed(x_axis);
    y_axis.Normalize();

    // Create the transformation matrix using the calculated axes
    gp_Trsf transformation;
    transformation.SetValues(x_axis.X(), y_axis.X(), z_axis.X(), 0,
                             x_axis.Y(), y_axis.Y(), z_axis.Y(), 0,
                             x_axis.Z(), y_axis.Z(), z_axis.Z(), 0);

    return transformation;
}

gp_Dir draw_primitives::create_normal_from_3_points_on_plane(gp_Pnt p1, gp_Pnt p2, gp_Pnt p3){

    // Calculate vectors
    gp_Vec x_axis(p1, p2);
    x_axis.Normalize();
    gp_Vec v2(p1,p3);

    // Calculate the normal vector using cross product
    gp_Vec z_axis = x_axis.Crossed(v2).Normalized();
    z_axis.Normalize();

    gp_Vec y_axis = z_axis.Crossed(x_axis);
    y_axis.Normalize();

    return z_axis;
}


void draw_primitives::offset_line_on_a_plane(gp_Pnt line_p0, gp_Pnt line_p1, gp_Pnt plane_p0, double offset, gp_Pnt &offset_line_p0, gp_Pnt &offset_line_p1){

    gp_Trsf transformation=create_transformation_matrix(line_p0,line_p1,plane_p0);

    // Create the point (0, 5, 0) in the original coordinate system
    gp_Pnt originalPoint(0, offset, 0);

    // Apply the transformation to move the point to the new coordinate system
    gp_Pnt transformedPoint = originalPoint.Transformed(transformation);

    offset_line_p0.SetXYZ({transformedPoint.X()+line_p0.X(),
                           transformedPoint.Y()+line_p0.Y(),
                           transformedPoint.Z()+line_p0.Z()});
    offset_line_p1.SetXYZ({((line_p1.X()-line_p0.X()+transformedPoint.X())+line_p0.X()),
                           ((line_p1.Y()-line_p0.Y())+transformedPoint.Y())+line_p0.Y(),
                           ((line_p1.Z()-line_p0.Z())+transformedPoint.Z())+line_p0.Z()
                          });
}

gp_Pnt draw_primitives::get_arc_centerpoint(Handle(AIS_Shape) shapeArc){

    const TopoDS_Edge& edgeA = TopoDS::Edge(shapeArc->Shape());
    Standard_Real first, last;
    Handle(Geom_Curve) aCurve = BRep_Tool::Curve(edgeA, first, last);

    Handle(Geom_Circle) circle = Handle(Geom_Circle)::DownCast(aCurve);
    return circle->Location();
}

void draw_primitives::get_arc_points(Handle(AIS_Shape) shapeArc, gp_Pnt &p1, gp_Pnt &p2, gp_Pnt &pw ,gp_Pnt &pc){

    const TopoDS_Edge& edgeB = TopoDS::Edge(shapeArc->Shape());
    Standard_Real first, last;
    Handle(Geom_Curve) aCurve = BRep_Tool::Curve(edgeB, first, last);

    //! Arc start-, endpoint.
    p1= aCurve->Value(first);
    p2= aCurve->Value(last);
    pw= aCurve->Value((first+last)/2);

    Handle(Geom_Circle) circle = Handle(Geom_Circle)::DownCast(aCurve);
    pc=circle->Location();
}

double draw_primitives::get_arc_radius(Handle(AIS_Shape) shapeArc){

    const TopoDS_Edge& edgeA = TopoDS::Edge(shapeArc->Shape());
    Standard_Real first, last;
    Handle(Geom_Curve) aCurve = BRep_Tool::Curve(edgeA, first, last);

    Handle(Geom_Circle) circle = Handle(Geom_Circle)::DownCast(aCurve);
    return circle->Radius();
}

void draw_primitives::get_line_points(Handle(AIS_Shape) shapeLine, gp_Pnt &p1, gp_Pnt &p2){
    const TopoDS_Edge& edgeA = TopoDS::Edge(shapeLine->Shape());
    TopoDS_Vertex vp1,vp2;
    TopExp::Vertices(edgeA,vp1,vp2);
    p1= BRep_Tool::Pnt(vp1);
    p2= BRep_Tool::Pnt(vp2);
}

bool draw_primitives::is_point_on_line(Handle(AIS_Shape) shapeLine, gp_Pnt pi){
    const TopoDS_Edge& edgeA = TopoDS::Edge(shapeLine->Shape());
    TopoDS_Vertex vp1,vp2;
    TopExp::Vertices(edgeA,vp1,vp2);
    gp_Pnt p1= BRep_Tool::Pnt(vp1);
    gp_Pnt p2= BRep_Tool::Pnt(vp2);

    return is_point_on_line(p1,p2,pi);
}

bool draw_primitives::is_point_on_line(gp_Pnt p1, gp_Pnt p2, gp_Pnt pi) {
    double tolerance = 1e-12;

    double d1 = pi.Distance(p1);
    double d2 = pi.Distance(p2);
    double d12 = p1.Distance(p2);

    // Check if the sum of distances from pi to p1 and p2 is approximately equal to the distance between p1 and p2
    if (std::abs((d1 + d2) - d12) < tolerance) {
        return true;
    }
    return false;
}

//! Is pi on plane p1,p2,p3?
bool draw_primitives::is_point_on_plane(gp_Pnt p1, gp_Pnt p2, gp_Pnt p3, gp_Pnt pi){
    double a1 = p2.X() - p1.X();
    double b1 = p2.Y() - p1.Y();
    double c1 = p2.Z() - p1.Z();
    double a2 = p3.X() - p1.X();
    double b2 = p3.Y() - p1.Y();
    double c2 = p3.Z() - p1.Z();
    double a = b1 * c2 - b2 * c1 ;
    double b = a2 * c1 - a1 * c2 ;
    double c = a1 * b2 - b1 * a2 ;
    double d = (- a * p1.X() - b * p1.Y() - c * p1.Z()) ;

    //! equation of plane is: a*x + b*y + c*z = 0 #

    //! checking if the 4th point satisfies
    //! the above equation
    if(a * pi.X() + b * pi.Y() + c * pi.Z() + d ==0){
        // std::cout<<"Coplanar (on plane)"<<std::endl;
        return 1;
    }
    return 0;
}

bool draw_primitives::is_point_on_arc(Handle(AIS_Shape) shapeArc, gp_Pnt pi){

    const TopoDS_Edge& edgeA = TopoDS::Edge(shapeArc->Shape());
    double first, last;
    double tol=1e-6;
    Handle(Geom_Curve) aCurve = BRep_Tool::Curve(edgeA, first, last);
    // gp_Pnt p1= aCurve->Value(first);

    Handle(Geom_Circle) aCircle = Handle(Geom_Circle)::DownCast(aCurve);

    // std::cout<<"first:"<<first<<std::endl;
    // std::cout<<"last:"<<last<<std::endl;

    if(aCurve->IsKind(STANDARD_TYPE (Geom_Circle))){

        // Create a projector to find the parameter on the arc for the test point
        GeomAPI_ProjectPointOnCurve projector(pi, aCurve);

        // Get the parameter value on the curve for the projected point
        double parameter = projector.LowerDistanceParameter();
        // std::cout<<"parameter:"<<parameter<<std::endl;

        // Get the point on the curve corresponding to the calculated parameter
        // gp_Pnt projectedPoint = aCurve->Value(parameter);
        // print_gp_Pnt("projected point:",projectedPoint);

        //! Check radius.
        if(aCircle->Location().Distance(pi)<aCircle->Radius()+tol &&  aCircle->Location().Distance(pi)>aCircle->Radius()-tol){

        } else {
            // std::cout<<"point is outside of arc radius."<<std::endl;
            return 0;
        }

        if(parameter>=first && parameter<=last){
            // std::cout<<"point is on arc segment."<<std::endl;
            return 1;
        }
        if(parameter<first || parameter>last){
            //! Try adding 2*M_PI, if the range by opencascade given 2*M_PI ahead.
            if((parameter+M_PI+M_PI)>first && (parameter+M_PI+M_PI)<last ){
                // std::cout<<"point is on arc segment."<<std::endl;
                return 1;
            } else {
                // std::cout<<"point is not on arc segment."<<std::endl;
                return 0;
            }
        }
        // std::cout<<""<<std::endl;
    }
    return 0;
}

std::vector<Handle(AIS_Shape)> draw_primitives::create_line_arc_intersections(Handle(AIS_Shape) shapeLine, Handle(AIS_Shape) shapeArc, double offset){

    std::vector<Handle(AIS_Shape)> Vec;

    gp_Pnt p1,p2;
    get_line_points(shapeLine,p1,p2);
    gp_Pnt p3,p4,pc,pw;
    get_arc_points(shapeArc,p3,p4,pw,pc);
    organize_line_arc_points(p1,p2,p3,p4);

    // print_gp_Pnt("shape arc-line intersect at",p2);

    double r=get_arc_radius(shapeArc);

    // 1. Create offset lines on both sides of the shapeLine with the shapeArc's plane's waypoint to set the plane.
    gp_Pnt po1,po2,po3,po4;
    create_3d_line_arc_offset_lines(shapeLine,shapeArc,offset,po1,po2,po3,po4);
    // Vec.push_back(draw_3d_line(po1,po2));
    // Vec.push_back(draw_3d_line(po3,po4));

    // 2. Create normal.
    gp_Dir normal=create_normal_from_3_points_on_plane(po1,po2,po3);

    // 3. Create offset arcs.
    // Vec.push_back(draw_3d_pc_circle(pc,normal,r+offset));
    // Vec.push_back( colorize(draw_3d_sphere(r+offset,pc),Quantity_NOC_BEET,0.9) );
    if(r-offset>0){
        // Vec.push_back(draw_3d_pc_circle(pc,normal,r-offset));
        // Vec.push_back( colorize(draw_3d_sphere(r-offset,pc),Quantity_NOC_BEET,0.9) );
    }

    // 4. Create the 2 intersection points with the inside offset shapeArc.
    gp_Pnt pc_offset_sphere;
    gp_Pnt pi_arc_contour;
    gp_Pnt pi_line_contour;

    if(r-offset>0){
        if(intersect_3d_line_sphere(pc,po1,po2,r-offset,pc_offset_sphere)){ //! Centerpoint offset sphere.
            if(intersect_3d_sphere_sphere(pc_offset_sphere,offset,pc,r,pi_arc_contour)){ //! Intersect contour arc with offset spehe.
                if(is_point_on_arc(shapeArc,pi_arc_contour)){
                    //! Draw intersecton points.
                    // Vec.push_back(draw_3d_point(pi_arc_contour));
                    get_closest_point_to_line(pc_offset_sphere,p1,p2,pi_line_contour);
                    // Vec.push_back(draw_3d_point(pi_line_contour));
                    //! Draw intersection sphere.
                    // Vec.push_back( colorize(draw_3d_sphere(offset,pc_offset_sphere),Quantity_NOC_GREEN,0.9) );
                    if(pi_arc_contour.Distance(pi_line_contour)>1e-6 && pi_arc_contour.Distance(pc_offset_sphere)>1e-6){ //! Check for valid arc construct.
                        //! Draw 3p arc.
                        Vec.push_back( colorize(draw_3d_pc_arc_closest(pi_line_contour,pi_arc_contour,pc_offset_sphere,normal,p2),Quantity_NOC_RED,0.9) );
                    }
                }
            }
        }

        if(intersect_3d_line_sphere(pc,po3,po4,r-offset,pc_offset_sphere)){ //! Centerpoint offset sphere.
            if(intersect_3d_sphere_sphere(pc_offset_sphere,offset,pc,r,pi_arc_contour)){ //! Intersect 1.
                if(is_point_on_arc(shapeArc,pi_arc_contour)){
                    // Vec.push_back(draw_3d_point(pi_arc_contour));
                    get_closest_point_to_line(pc_offset_sphere,p1,p2,pi_line_contour);
                    // Vec.push_back(draw_3d_point(pi_line_contour));
                    // Vec.push_back( colorize(draw_3d_sphere(offset,pc_offset_sphere),Quantity_NOC_GREEN,0.9) );
                    if(pi_arc_contour.Distance(pi_line_contour)>1e-6 && pi_arc_contour.Distance(pc_offset_sphere)>1e-6){ //! Check for valid arc construct.
                        //! Draw 3p arc.
                        Vec.push_back( colorize(draw_3d_pc_arc_closest(pi_line_contour,pi_arc_contour,pc_offset_sphere,normal,p2),Quantity_NOC_RED,0.9) );
                    }
                }
            }
        }
    }

    if(intersect_3d_line_sphere(pc,po1,po2,r+offset,pc_offset_sphere)){ //! Centerpoint offset sphere.

        if(intersect_3d_sphere_sphere(pc_offset_sphere,offset,pc,r,pi_arc_contour)){ //! Intersect 1.
            if(is_point_on_arc(shapeArc,pi_arc_contour)){
                // Vec.push_back(draw_3d_point(pi_arc_contour));
                get_closest_point_to_line(pc_offset_sphere,p1,p2,pi_line_contour);
                // Vec.push_back(draw_3d_point(pi_line_contour));
                // Vec.push_back( colorize(draw_3d_sphere(offset,pc_offset_sphere),Quantity_NOC_GREEN,0.9) );
                if(pi_arc_contour.Distance(pi_line_contour)>1e-6 && pi_arc_contour.Distance(pc_offset_sphere)>1e-6){ //! Check for valid arc construct.
                    //! Draw 3p arc.
                    Vec.push_back( colorize(draw_3d_pc_arc_closest(pi_line_contour,pi_arc_contour,pc_offset_sphere,normal,p2),Quantity_NOC_RED,0.9) );
                }
            }
        }
    }

    if(intersect_3d_line_sphere(pc,po3,po4,r+offset,pc_offset_sphere)){ //! Centerpoint offset sphere.
        if(intersect_3d_sphere_sphere(pc_offset_sphere,offset,pc,r,pi_arc_contour)){ //! Intersect 1.
            if(is_point_on_arc(shapeArc,pi_arc_contour)){
                // Vec.push_back(draw_3d_point(pi_arc_contour));
                get_closest_point_to_line(pc_offset_sphere,p1,p2,pi_line_contour);
                // Vec.push_back(draw_3d_point(pi_line_contour));
                // Vec.push_back( colorize(draw_3d_sphere(offset,pc_offset_sphere),Quantity_NOC_GREEN,0.9) );
                if(pi_arc_contour.Distance(pi_line_contour)>1e-6 && pi_arc_contour.Distance(pc_offset_sphere)>1e-6){ //! Check for valid arc construct.
                    //! Draw 3p arc.
                    Vec.push_back( colorize(draw_3d_pc_arc_closest(pi_line_contour,pi_arc_contour,pc_offset_sphere,normal,p2),Quantity_NOC_RED,0.9) );
                    //Vec.push_back( colorize(draw_3d_pc_arc(pi_line_contour,pi_arc_contour,pc_offset_sphere,normal.X(),normal.Y(),normal.Z()),Quantity_NOC_RED,0.9) );
                }
            }
        }
    }

    return Vec;
}

void draw_primitives::create_3d_line_arc_offset_lines(Handle(AIS_Shape) shapeLine, Handle(AIS_Shape) shapeArc, double offset, gp_Pnt &po1, gp_Pnt &po2, gp_Pnt &po3, gp_Pnt &po4){

    const TopoDS_Edge& edgeA = TopoDS::Edge(shapeLine->Shape());
    TopoDS_Vertex vp1,vp2;
    TopExp::Vertices(edgeA,vp1,vp2);
    //! Line point start, end.
    gp_Pnt p1= BRep_Tool::Pnt(vp1);
    gp_Pnt p2= BRep_Tool::Pnt(vp2);

    const TopoDS_Edge& edgeB = TopoDS::Edge(shapeArc->Shape());
    Standard_Real first, last;
    Handle(Geom_Curve) aCurve = BRep_Tool::Curve(edgeB, first, last);

    //! Arc start-, endpoint.
    gp_Pnt p3= aCurve->Value(first);
    gp_Pnt p4= aCurve->Value(last);
    gp_Pnt pw= aCurve->Value((first+last)/2); //! Arc waypoint is more robust for defining a plane.

    //! Ensure correct point flow.
    organize_line_arc_points(p1,p2,p3,p4);

    //! Create both line offset lines. Leftside offset + rightside offset.
    offset_line_on_a_plane(p1,p2,pw,offset,po1,po2);
    offset_line_on_a_plane(p1,p2,pw,-offset,po3,po4);
}

bool draw_primitives::draw_3d_line_arc_offset_lines( Handle(AIS_Shape) shapeLine, Handle(AIS_Shape) shapeArc, double offset, Handle(AIS_Shape) &shapeA, Handle(AIS_Shape) &shapeB){

    gp_Pnt po1,po2,po3,po4;
    create_3d_line_arc_offset_lines(shapeLine,shapeArc,offset,po1,po2,po3,po4);

    shapeA=draw_3d_line(po1,po2);
    shapeA=colorize(shapeA,Quantity_NOC_BLUE,0);
    shapeB=draw_3d_line(po3,po4);
    shapeB=colorize(shapeB,Quantity_NOC_RED,0);

    return 1;
}

void draw_primitives::filter_out_duplicate_points(std::vector<gp_Pnt>& pvec, double tolerance){
    if (pvec.empty()) {
        return;
    }

    // Result vector to store unique points
    std::vector<gp_Pnt> uniquePoints;
    uniquePoints.reserve(pvec.size());

    // Iterate over the input points
    for (const auto& point : pvec) {
        bool isDuplicate = false;
        for (const auto& uniquePoint : uniquePoints) {
            if (point.Distance(uniquePoint) <= tolerance) {
                isDuplicate = true;
                break;
            }
        }
        if (!isDuplicate) {
            uniquePoints.push_back(point);
        }
    }

    // Replace the original vector with the filtered one
    pvec = std::move(uniquePoints);
}

//bool draw_primitives::draw_3d_arc_line_fillet_conventional(Handle(AIS_Shape) shapeArc, Handle(AIS_Shape) shapeLine, double radius, Handle(AIS_Shape) &shape){

//    //! Or use:
//    const TopoDS_Edge& edgeA = TopoDS::Edge(shapeArc->Shape());
//    const TopoDS_Edge& edgeB = TopoDS::Edge(shapeLine->Shape());

//    TopoDS_Vertex vp1,vp2;
//    TopExp::Vertices(edgeB,vp1,vp2);
//    //! Line point start, end.
//    gp_Pnt p1= BRep_Tool::Pnt(vp1);
//    gp_Pnt p2= BRep_Tool::Pnt(vp2);

//    Standard_Real first, last;
//    Handle(Geom_Curve) aCurve = BRep_Tool::Curve(edgeA, first, last);
//    gp_Pnt p3= aCurve->Value(first);
//    gp_Pnt p4= aCurve->Value(last);
//    gp_Pnt pw= aCurve->Value((first+last)/2); //! Arc waypoint.

//    gp_Pln plane;
//    create_3d_plane(p2,pw,p1,plane);

//    //! Create 2d fillets on a plane.
//    ChFi2d_FilletAlgo api;
//    api.Init(edgeA,edgeB,plane);

//    if(!api.Perform(radius)){
//        std::cout<<"error in perform api arc-line."<<std::endl;
//        return 0;
//    }
//    TopoDS_Edge theEdge1,theEdge2;
//    TopoDS_Edge edge1=api.Result(gp_Pnt(0,0,0),theEdge1,theEdge2,-1);

//    shape=new AIS_Shape(edge1);
//    shape=colorize(shape,Quantity_NOC_RED,0);
//    return 1;
//}

// Function to project a point onto a plane
gp_Pnt draw_primitives::projectPointOnPlane(gp_Pnt point, gp_Pnt planeOrigin, gp_Vec planeNormal) {
    gp_Vec pointToPlane(planeOrigin, point);
    Standard_Real dotProduct = pointToPlane.Dot(planeNormal);
    Standard_Real distance = planeNormal.Magnitude();

    Standard_Real projectionFactor = dotProduct / distance;
    gp_Vec projectedVector = planeNormal.Multiplied(projectionFactor);

    gp_Pnt projectedPoint = point.Translated(-projectedVector);
    return projectedPoint;
}

void draw_primitives::Visit(const TDF_Label& theLabel)
{
    //! theLabel.EntryDump(std::cout);
    Quantity_Color aColor;
    TopoDS_Shape aShape;
    Handle(TDataStd_Name) aName;
    if (theLabel.FindAttribute(TDataStd_Name::GetID(), aName)){
        //! std::cout << "  Name: " << aName->Get() << std::endl;
    }
    bool skip=0;
    if (aShapeTool->IsShape(theLabel))
    {
        //! if a shape can be made from the current label, look for the color of that label:
        if(aShapeTool->GetShape(theLabel, aShape)){
            if(aColorTool->GetColor(aShape,XCAFDoc_ColorSurf,aColor)){
                skip=0;
            } else { skip=1;}
        }
        if(skip==0){
            Ais_ShapeVec.push_back(new AIS_Shape(aShape));
            Ais_ShapeVec.back()->SetColor(aColor);
            Ais_ShapeVec.back()->SetDisplayMode(AIS_Shaded);
            Ais_ShapeVec.back()->Attributes()->SetFaceBoundaryDraw(true);
            Ais_ShapeVec.back()->Attributes()->SetFaceBoundaryAspect(
                        new Prs3d_LineAspect(Quantity_NOC_BLACK, Aspect_TOL_SOLID, 1.));
            Ais_ShapeVec.back()->Attributes()->SetIsoOnTriangulation(true);
            //! Temporairy stepfile preview:
            //! m_context->Display(Ais_ShapeVec.back(),Standard_False);
        }
    }
    /*! Repeat the visit function for each childmember. */
    for (TDF_ChildIterator c(theLabel); c.More(); c.Next())
    {
        Visit(c.Value());
    }
}

std::vector<Handle(AIS_Shape)> draw_primitives::load_stepfile(std::string filename)
{
    //! Empty temponairy bucket, the visit function will fill up the bucket for one stepfile.
    Ais_ShapeVec.clear();

    STEPCAFControl_Controller::Init();

    Handle(TDocStd_Document) aDoc;
    Handle(XCAFApp_Application) anApp = XCAFApp_Application::GetApplication();
    anApp->NewDocument("MDTV-XCAF", aDoc);

    STEPCAFControl_Reader aStepReader;
    aStepReader.SetColorMode(true);
    aStepReader.SetNameMode(true);
    aStepReader.SetLayerMode(true);
    aStepReader.SetPropsMode(true);

    aStepReader.ReadFile (filename.c_str());
    aStepReader.Transfer (aDoc);

    TDF_Label aRootLabel = aDoc->Main();

    aShapeTool = XCAFDoc_DocumentTool::ShapeTool(aRootLabel);
    aColorTool = XCAFDoc_DocumentTool::ColorTool(aRootLabel);

    Visit(aRootLabel);

    return Ais_ShapeVec;
}

bool draw_primitives::snap_to_closest_endpoint(std::vector<Handle(AIS_Shape)> shapevec, gp_Pnt mousepos, double dist, gp_Pnt &snappos){

    for(uint i=0; i<shapevec.size(); i++){

        TopExp_Explorer explorer(shapevec.at(i)->Shape(), TopAbs_VERTEX);
        if (explorer.More()) {
            explorer.Next();
            if (!explorer.More()) {

                TopoDS_Vertex aVertex = TopoDS::Vertex(explorer.Current());
                gp_Pnt p1 = BRep_Tool::Pnt(aVertex);

                // std::cout << "The shape represents a single point." << std::endl;
                if(mousepos.Distance(p1)<dist){
                    snappos=p1;
                    // print_gp_Pnt("snap to",p1);
                    return 1;
                }

            } else {
                // std::cout << "The shape does not represent a single point." << std::endl;

                Handle(AIS_Shape) gcode_shape=shapevec.at(i);
                const TopoDS_Edge& edge = TopoDS::Edge(gcode_shape->Shape());
                Standard_Real first, last;
                Handle(Geom_Curve) curve = BRep_Tool::Curve(edge, first, last);

                if(curve->IsKind(STANDARD_TYPE(Geom_Line))){
                    gp_Pnt p1,p2;
                    p1= curve->Value(first);
                    p2= curve->Value(last);

                    if(mousepos.Distance(p1)<dist){
                        snappos=p1;
                        // print_gp_Pnt("snap to",p1);
                        return 1;
                    }
                    if(mousepos.Distance(p2)<dist){
                        snappos=p2;
                        // print_gp_Pnt("snap to",p2);
                        return 1;
                    }

                }
            }
        }

    }

    snappos=mousepos;
    return 0;
}

bool draw_primitives::snap_to_closest_midpoint(std::vector<Handle(AIS_Shape)> shapevec, gp_Pnt mousepos, double dist, gp_Pnt &snappos){

    for(uint i=0; i<shapevec.size(); i++){

        Handle(AIS_Shape) gcode_shape=shapevec.at(i);
        const TopoDS_Edge& edge = TopoDS::Edge(gcode_shape->Shape());
        Standard_Real first, last;
        Handle(Geom_Curve) curve = BRep_Tool::Curve(edge, first, last);
        gp_Pnt p1= curve->Value((first+last)/2);

        if(mousepos.Distance(p1)<dist){
            snappos=p1;
            return 1;
        }
    }
    snappos=mousepos;
    return 0;
}

Handle(AIS_Shape) draw_primitives::downcast(Handle(AIS_InteractiveObject) interactiveObject){
    return  Handle(AIS_Shape)::DownCast(interactiveObject);
}

// Function to calculate the angle of a vector with respect to the x-axis
double draw_primitives::get_2d_arc_end_angle_xy(const gp_Pnt& p0, const gp_Pnt& pw, const gp_Pnt& p1) {
    // Calculate the arc center (pc)
    double x0 = p0.X(), y0 = p0.Y();
    double xw = pw.X(), yw = pw.Y();
    double x1 = p1.X(), y1 = p1.Y();

    double A1 = xw - x0, B1 = yw - y0, C1 = (xw*xw + yw*yw - x0*x0 - y0*y0) / 2.0;
    double A2 = x1 - xw, B2 = y1 - yw, C2 = (x1*x1 + y1*y1 - xw*xw - yw*yw) / 2.0;

    double pc_x = (C1*B2 - C2*B1) / (A1*B2 - A2*B1);
    double pc_y = (A1*C2 - A2*C1) / (A1*B2 - A2*B1);

    // Calculate the angle of the direction vector with respect to the x-axis
    return atan2(pc_y - p1.Y(), pc_x - p1.X());
}

// Function to calculate the angle of a vector with respect to the x-axis
double draw_primitives::get_2d_arc_end_angle_xz(const gp_Pnt& p0, const gp_Pnt& pw, const gp_Pnt& p1) {
    // Calculate the arc center (pc)
    double x0 = p0.X(), z0 = p0.Z();
    double xw = pw.X(), zw = pw.Z();
    double x1 = p1.X(), z1 = p1.Z();

    double A1 = xw - x0, B1 = zw - z0, C1 = (xw*xw + zw*zw - x0*x0 - z0*z0) / 2.0;
    double A2 = x1 - xw, B2 = z1 - zw, C2 = (x1*x1 + z1*z1 - xw*xw - zw*zw) / 2.0;

    double pc_x = (C1*B2 - C2*B1) / (A1*B2 - A2*B1);
    double pc_z = (A1*C2 - A2*C1) / (A1*B2 - A2*B1);

    // Calculate the angle of the direction vector with respect to the x-axis
    return atan2(pc_z - p1.Z(), pc_x - p1.X());
}

// Function to calculate the angle of a vector with respect to the x-axis
double draw_primitives::get_2d_arc_end_angle_yz(const gp_Pnt& p0, const gp_Pnt& pw, const gp_Pnt& p1) {
    // Calculate the arc center (pc)
    double y0 = p0.Y(), z0 = p0.Z();
    double yw = pw.Y(), zw = pw.Z();
    double y1 = p1.Y(), z1 = p1.Z();

    double A1 = yw - y0, B1 = zw - z0, C1 = (yw*yw + zw*zw - y0*y0 - z0*z0) / 2.0;
    double A2 = y1 - yw, B2 = z1 - zw, C2 = (y1*y1 + z1*z1 - yw*yw - zw*zw) / 2.0;

    double pc_y = (C1*B2 - C2*B1) / (A1*B2 - A2*B1);
    double pc_z = (A1*C2 - A2*C1) / (A1*B2 - A2*B1);

    // Calculate the angle of the direction vector with respect to the x-axis
    return atan2(pc_z - p1.Z(), pc_y - p1.Y());
}

// Function to calculate the angle of the arc's circumference at the start
double draw_primitives::get_2d_arc_start_angle_xy(const gp_Pnt& p0, const gp_Pnt& pw, const gp_Pnt& p1) {
    // Calculate the arc center (pc)
    double x0 = p0.X(), y0 = p0.Y();
    double xw = pw.X(), yw = pw.Y();
    double x1 = p1.X(), y1 = p1.Y();

    double A1 = xw - x0, B1 = yw - y0, C1 = (xw*xw + yw*yw - x0*x0 - y0*y0) / 2.0;
    double A2 = x1 - xw, B2 = y1 - yw, C2 = (x1*x1 + y1*y1 - xw*xw - yw*yw) / 2.0;

    double pc_x = (C1*B2 - C2*B1) / (A1*B2 - A2*B1);
    double pc_y = (A1*C2 - A2*C1) / (A1*B2 - A2*B1);

    // Calculate the angle of the direction vector with respect to the x-axis
    return atan2(p0.Y() - pc_y, p0.X() - pc_x);
}

// Function to calculate the angle of the arc's circumference at the start
double draw_primitives::get_2d_arc_start_angle_xz(const gp_Pnt& p0, const gp_Pnt& pw, const gp_Pnt& p1) {
    // Calculate the arc center (pc)
    double x0 = p0.X(), z0 = p0.Z();
    double xw = pw.X(), zw = pw.Z();
    double x1 = p1.X(), z1 = p1.Z();

    double A1 = xw - x0, B1 = zw - z0, C1 = (xw*xw + zw*zw - x0*x0 - z0*z0) / 2.0;
    double A2 = x1 - xw, B2 = z1 - zw, C2 = (x1*x1 + z1*z1 - xw*xw - zw*zw) / 2.0;

    double pc_x = (C1*B2 - C2*B1) / (A1*B2 - A2*B1);
    double pc_z = (A1*C2 - A2*C1) / (A1*B2 - A2*B1);

    // Calculate the angle of the direction vector with respect to the x-axis
    return atan2(p0.Z() - pc_z, p0.X() - pc_x);
}

// Function to calculate the angle of the arc's circumference at the start
double draw_primitives::get_2d_arc_start_angle_yz(const gp_Pnt& p0, const gp_Pnt& pw, const gp_Pnt& p1) {
    // Calculate the arc center (pc)
    double y0 = p0.Y(), z0 = p0.Z();
    double yw = pw.Y(), zw = pw.Z();
    double y1 = p1.Y(), z1 = p1.Z();

    double A1 = yw - y0, B1 = zw - z0, C1 = (yw*yw + zw*zw - y0*y0 - z0*z0) / 2.0;
    double A2 = y1 - yw, B2 = z1 - zw, C2 = (y1*y1 + z1*z1 - yw*yw - zw*zw) / 2.0;

    double pc_y = (C1*B2 - C2*B1) / (A1*B2 - A2*B1);
    double pc_z = (A1*C2 - A2*C1) / (A1*B2 - A2*B1);

    // Calculate the angle of the direction vector with respect to the x-axis
    return atan2(p0.Z() - pc_z, p0.Y() - pc_y);
}

// Function to determine if an arc is clockwise (CW) or counterclockwise (CCW)
int draw_primitives::get_2d_arc_direction_xy(const gp_Pnt& p0, const gp_Pnt& pw, const gp_Pnt& p1) {
    // Calculate vectors from p0 to pw and from p0 to p1
    double vector1_x = pw.X() - p0.X();
    double vector1_y = pw.Y() - p0.Y();
    double vector2_x = p1.X() - p0.X();
    double vector2_y = p1.Y() - p0.Y();

    // Calculate the cross product of the vectors
    double crossProduct = vector1_x * vector2_y - vector1_y * vector2_x;

    // Determine the direction based on the sign of the cross product
    if (crossProduct > 0) {
        return 1; // Counterclockwise (CCW)
    } else if (crossProduct < 0) {
        return -1; // Clockwise (CW)
    } else {
        return 0; // The points are collinear
    }
}

// Function to determine if an arc is clockwise (CW) or counterclockwise (CCW)
int draw_primitives::get_2d_arc_direction_xz(const gp_Pnt& p0, const gp_Pnt& pw, const gp_Pnt& p1) {
    // Calculate vectors from p0 to pw and from p0 to p1
    double vector1_x = pw.X() - p0.X();
    double vector1_z = pw.Z() - p0.Z();
    double vector2_x = p1.X() - p0.X();
    double vector2_z = p1.Z() - p0.Z();

    // Calculate the cross product of the vectors
    double crossProduct = vector1_x * vector2_z - vector1_z * vector2_x;

    // Determine the direction based on the sign of the cross product
    if (crossProduct > 0) {
        return 1; // Counterclockwise (CCW)
    } else if (crossProduct < 0) {
        return -1; // Clockwise (CW)
    } else {
        return 0; // The points are collinear
    }
}

// Function to determine if an arc is clockwise (CW) or counterclockwise (CCW)
int draw_primitives::get_2d_arc_direction_yz(const gp_Pnt& p0, const gp_Pnt& pw, const gp_Pnt& p1) {
    // Calculate vectors from p0 to pw and from p0 to p1
    double vector1_y = pw.Y() - p0.Y();
    double vector1_z = pw.Z() - p0.Z();
    double vector2_y = p1.Y() - p0.Y();
    double vector2_z = p1.Z() - p0.Z();

    // Calculate the cross product of the vectors
    double crossProduct = vector1_y * vector2_z - vector1_z * vector2_y;

    // Determine the direction based on the sign of the cross product
    if (crossProduct > 0) {
        return 1; // Counterclockwise (CCW)
    } else if (crossProduct < 0) {
        return -1; // Clockwise (CW)
    } else {
        return 0; // The points are collinear
    }
}

// Function to calculate the angle of a direction vector
double draw_primitives::get_2d_line_angle_xy(const gp_Pnt& p1, const gp_Pnt& p2) {
    double dx = p2.X() - p1.X();
    double dy = p2.Y() - p1.Y();
    return atan2(dy, dx);
}

// Function to calculate the angle of a direction vector
double draw_primitives::get_2d_line_angle_xz(const gp_Pnt& p1, const gp_Pnt& p2) {
    double dx = p2.X() - p1.X();
    double dz = p2.Z() - p1.Z();
    return atan2(dz, dx);
}

// Function to calculate the angle of a direction vector
double draw_primitives::get_2d_line_angle_yz(const gp_Pnt& p1, const gp_Pnt& p2) {
    double dy = p2.Y() - p1.Y();
    double dz = p2.Z() - p1.Z();
    return atan2(dz, dy);
}
// Function to calculate the angle of the arc's circumference at the start
double draw_primitives::get_2d_arc_radius_xy(const gp_Pnt& p0, const gp_Pnt& pw, const gp_Pnt& p1) {
    // Calculate the arc center (pc)
    double x0 = p0.X(), y0 = p0.Y();
    double xw = pw.X(), yw = pw.Y();
    double x1 = p1.X(), y1 = p1.Y();

    double A1 = xw - x0, B1 = yw - y0, C1 = (xw*xw + yw*yw - x0*x0 - y0*y0) / 2.0;
    double A2 = x1 - xw, B2 = y1 - yw, C2 = (x1*x1 + y1*y1 - xw*xw - yw*yw) / 2.0;

    double pc_x = (C1*B2 - C2*B1) / (A1*B2 - A2*B1);
    double pc_y = (A1*C2 - A2*C1) / (A1*B2 - A2*B1);

    gp_Pnt pc={pc_x,pc_y,0};
    return draw_primitives().get_line_lenght(p0,pc);
}

// Function to calculate the angle of the arc's circumference at the start
double draw_primitives::get_2d_arc_radius_xz(const gp_Pnt& p0, const gp_Pnt& pw, const gp_Pnt& p1) {
    // Calculate the arc center (pc)
    double x0 = p0.X(), z0 = p0.Z();
    double xw = pw.X(), zw = pw.Z();
    double x1 = p1.X(), z1 = p1.Z();

    double A1 = xw - x0, B1 = zw - z0, C1 = (xw*xw + zw*zw - x0*x0 - z0*z0) / 2.0;
    double A2 = x1 - xw, B2 = z1 - zw, C2 = (x1*x1 + z1*z1 - xw*xw - zw*zw) / 2.0;

    double pc_x = (C1*B2 - C2*B1) / (A1*B2 - A2*B1);
    double pc_z = (A1*C2 - A2*C1) / (A1*B2 - A2*B1);

    gp_Pnt pc={pc_x,0,pc_z};
    return draw_primitives().get_line_lenght(p0,pc);
}

// Function to calculate the angle of the arc's circumference at the start
double draw_primitives::get_2d_arc_radius_yz(const gp_Pnt& p0, const gp_Pnt& pw, const gp_Pnt& p1) {
    // Calculate the arc center (pc)
    double y0 = p0.Y(), z0 = p0.Z();
    double yw = pw.Y(), zw = pw.Z();
    double y1 = p1.Y(), z1 = p1.Z();

    double A1 = yw - y0, B1 = zw - z0, C1 = (yw*yw + zw*zw - y0*y0 - z0*z0) / 2.0;
    double A2 = y1 - yw, B2 = z1 - zw, C2 = (y1*y1 + z1*z1 - yw*yw - zw*zw) / 2.0;

    double pc_y = (C1*B2 - C2*B1) / (A1*B2 - A2*B1);
    double pc_z = (A1*C2 - A2*C1) / (A1*B2 - A2*B1);

    gp_Pnt pc={0,pc_y,pc_z};
    return draw_primitives().get_line_lenght(p0,pc);
}

int draw_primitives::get_shape_type(const Handle(AIS_Shape)& shape) {
    // Extract the underlying TopoDS_Shape from the AIS_Shape
    TopoDS_Shape underlyingShape = shape->Shape();

    // Check if the shape is a vertex
    if (underlyingShape.ShapeType() == TopAbs_VERTEX) {
        // Return 1 if the shape is a vertex
        return point;
    }

    // Check if the shape is an edge
    if (underlyingShape.ShapeType() == TopAbs_EDGE) {
        // Cast the underlying shape to a TopoDS_Edge
        const TopoDS_Edge& edge = TopoDS::Edge(underlyingShape);
        Standard_Real first, last;

        // Retrieve the geometric curve associated with the edge
        Handle(Geom_Curve) curve = BRep_Tool::Curve(edge, first, last);

        // Check if the curve is a line
        if (curve->IsKind(STANDARD_TYPE(Geom_Line))) {
            // Return 2 if the shape is a line
            return line;
        }

        // Check if the curve is a circle
        if (curve->IsKind(STANDARD_TYPE(Geom_Circle))) {
            // Downcast the curve to a Geom_Circle
            Handle(Geom_Circle) circle_ = Handle(Geom_Circle)::DownCast(curve);

            // Check if the circle parameters indicate a full circle
            if (circle_->FirstParameter() ==  circle_->LastParameter()) {
                // Return 3 if the shape is a full circle
                return circle;
            } else {
                // Return 4 if the shape is an arc
                return arc;
            }
        }
    }

    // Return 0 if the shape type is unknown
    return unknown;
}

int draw_primitives::get_shape_type(const gp_Pnt p0, const gp_Pnt p1, const gp_Pnt p2) {

    // Check if the shape is a vertex
    if (p0.Distance(p1)==0 && p0.Distance(p2)==0) {
        // Return 1 if the shape is a vertex
        return point;
    }

    // Check if the curve is a line
    if (is_point_on_line(p0,p2,p1) && p0.Distance(p2)>0) {
        return line;
    }

    return arc;
}

gp_Pln draw_primitives::create_top_view_plane(){
    // Define the origin point
    gp_Pnt origin(0, 0, 0);

    // Define the normal direction for the top view (Z-axis)
    gp_Dir normal(0, 0, 1);

    // Define the X-direction for the plane's local coordinate system (X-axis)
    gp_Dir xDirection(1, 0, 0);

    // Create a coordinate system aligned with the global XYZ axes at the origin
    gp_Ax3 coordinateSystem(origin, normal, xDirection);

    // Create a plane with the defined coordinate system
    gp_Pln topViewPlane(coordinateSystem);

    return topViewPlane;
}

// Function to port points from one plane to another
void draw_primitives::port_points_between_planes(const gp_Pln& sourcePlane, const gp_Pln& targetPlane, std::vector<gp_Pnt>& pvec) {
    // Get the transformation from sourcePlane to targetPlane
    gp_Trsf transformation;
    transformation.SetTransformation(sourcePlane.Position(), targetPlane.Position());

    for(auto& point : pvec) {
        point.Transform(transformation);
    }
}

// Function to port points from one plane to another
void draw_primitives::port_point_between_planes(const gp_Pln& sourcePlane, const gp_Pln& targetPlane, gp_Pnt &p){
    // Get the transformation from sourcePlane to targetPlane
    gp_Trsf transformation;
    transformation.SetTransformation(sourcePlane.Position(), targetPlane.Position());
    p.Transform(transformation);
}

gp_Trsf draw_primitives::get_transformation_2_planes(gp_Pln a, gp_Pln b){
    gp_Trsf transformation;
    transformation.SetTransformation(a.Position(), b.Position());
    return transformation;
}

// Function to create a new plane aligned with global XYZ axes and positioned at the origin
gp_Pln draw_primitives::align_plane_to_origin(const gp_Pln& originalPlane) {
    // Get the coordinate system of the original plane
    gp_Ax3 axis = originalPlane.Position();

    // Create a new coordinate system aligned with the global XYZ axes at the origin
    gp_Ax3 globalAxes(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1), gp_Dir(1, 0, 0));

    // Create a transformation to align the plane with the global axes
    gp_Trsf transformation;
    transformation.SetTransformation(axis, globalAxes);

    // Apply the transformation to the original plane
    gp_Pln alignedPlane = originalPlane;
    alignedPlane.Transform(transformation);

    return alignedPlane;
}

// Progress 0-1.
void draw_primitives::interpolate_point_on_line(const gp_Pnt& p0, const gp_Pnt& p1, const double &progress, gp_Pnt& pi) {
    // Ensure progress is within the range [0, 1]
    double pro=progress;
    if (pro < 0.0) pro = 0.0;
    if (pro > 1.0) pro = 1.0;

    // Calculate the interpolated point
    double x = p0.X() + (p1.X() - p0.X()) * pro;
    double y = p0.Y() + (p1.Y() - p0.Y()) * pro;
    double z = p0.Z() + (p1.Z() - p0.Z()) * pro;
    pi.SetCoord(x, y, z);
}

bool draw_primitives::is_valid_point(const gp_Pnt &p) {
    return !std::isnan(p.X()) && !std::isnan(p.Y()) && !std::isnan(p.Z());
}

Handle(AIS_Shape) draw_primitives::draw_universal_3d_shape(gp_Pnt p0, gp_Pnt p1, gp_Pnt p2){

    // Check for valid input points
    if (!is_valid_point(p0)) {
        std::cerr << "Invalid point p0: (" << p0.X() << ", " << p0.Y() << ", " << p0.Z() << ")" << std::endl;
        return draw_3d_point(p0);
    }
    if (!is_valid_point(p1)) {
        std::cerr << "Invalid point pw: (" << p1.X() << ", " << p1.Y() << ", " << p1.Z() << ")" << std::endl;
        return draw_3d_point(p0);
    }
    if (!is_valid_point(p1)) {
        std::cerr << "Invalid point p1: (" << p1.X() << ", " << p1.Y() << ", " << p1.Z() << ")" << std::endl;
        return draw_3d_point(p0);
    }

    // Check for degenerate case where all points are the same
    if (p0.Distance(p1) == 1e-6 && p0.Distance(p2) == 1e-6) {
        std::cout << "All points are the same. Returning point shape." << std::endl;
        return draw_3d_point(p0);
    }

    // Check if the points are collinear and distinct
    if (is_point_on_line(p0, p2, p1) && p0.Distance(p2) > 0) {
        std::cout << "Points are collinear. Returning line shape." << std::endl;
        return draw_3d_line(p0, p2);
    }

    // Attempt to create the arc of a circle
    try {
        std::cout << "Creating arc with points:" << std::endl;
        std::cout << "  p0: (" << p0.X() << ", " << p0.Y() << ", " << p0.Z() << ")" << std::endl;
        std::cout << "  pw: (" << p1.X() << ", " << p1.Y() << ", " << p1.Z() << ")" << std::endl;
        std::cout << "  p1: (" << p2.X() << ", " << p2.Y() << ", " << p2.Z() << ")" << std::endl;

        Handle(Geom_TrimmedCurve) aArcOfCircle = GC_MakeArcOfCircle(p0, p1, p2);
        if (aArcOfCircle.IsNull()) {
            std::cerr << "Error: GC_MakeArcOfCircle returned a null curve." << std::endl;
            // Additional debug information
            std::cerr << "Failed to create an arc with the provided points. Ensure the points form a valid arc, can create a 3d plane." << std::endl;
            return draw_3d_point(p0);
        }

        TopoDS_Edge aEdge = BRepBuilderAPI_MakeEdge(aArcOfCircle);
        if (aEdge.IsNull()) {
            std::cerr << "Error: BRepBuilderAPI_MakeEdge returned a null edge." << std::endl;
            return draw_3d_point(p0);
        }

        std::cout << "Returning arc shape." << std::endl;
        return new AIS_Shape(aEdge);
    } catch (Standard_Failure &failure) {
        std::cerr << "Exception caught: " << failure.GetMessageString() << std::endl;
        return nullptr;
    } catch (...) {
        std::cerr << "Unknown exception caught." << std::endl;
        return nullptr;
    }
}

int draw_primitives::get_3d_fillet_start_end_point(const gp_Pnt &p0, gp_Pnt &p1, gp_Pnt &p2, gp_Pnt &p3, gp_Pnt &p4, const gp_Pnt &p5, double offset){

    if(offset<=0){
        return 0;
    }

    int type0=get_shape_type(p0,p1,p2);
    int type1=get_shape_type(p3,p4,p5);

    double s0,s1,offset0,offset1;
    offset0=offset;
    offset1=offset;

    // Get lenghts. Limit offset to lenght.
    if(type0==line){
        s0=p0.Distance(p2);
        // std::cout<<"line0 s:"<<s0<<std::endl;
    }
    if(type0==arc){
        s0=get_3d_arc_lenght(p0,p1,p2);
        // std::cout<<"arc0 s:"<<s0<<std::endl;
    }
    if(offset0>s0){
        offset0=s0;
        // std::cout<<"offset0:"<<offset0<<std::endl;
    }

    if(type1==line){
        s1=p3.Distance(p5);
        // std::cout<<"line1 s:"<<s1<<std::endl;
    }
    if(type1==arc){
        s1=get_3d_arc_lenght(p3,p4,p5);
        // std::cout<<"arc1 s:"<<s1<<std::endl;
    }
    if(offset1>s1){
        offset1=s1;
        // std::cout<<"offset1:"<<offset0<<std::endl;
    }

    gp_Pnt pi0,pi1,pw0,pw1;
    double progress0=offset0/s0;
    double progress1=offset1/s1;

    progress0=fmin(0.5,progress0);
    progress1=fmin(0.5,progress1);

    // std::cout<<"progress0:"<<progress0<<std::endl;
    // std::cout<<"progress1:"<<progress1<<std::endl;

    // Set new points.
    if(type0==line){
        interpolate_point_on_line(p2,p0,progress0,pi0);
        p2=pi0;
        p1=get_line_midpoint(p0,p2);
    }
    if(type0==arc){
        interpolate_point_on_arc(p2,p1,p0,progress0,pi0);
        interpolate_point_on_arc(p2,p1,p0,((1-progress0)*0.5)+progress0,pw0);
        p2=pi0;
        p1=pw0;
    }

    if(type1==line){
        interpolate_point_on_line(p3,p5,progress1,pi1);
        p3=pi1;
        p4=get_line_midpoint(p3,p5);
    }
    if(type1==arc){
        interpolate_point_on_arc(p3,p4,p5,progress1,pi1);
        interpolate_point_on_arc(p3,p4,p5,((1-progress1)*0.5)+progress1,pw1);
        p3=pi1;
        p4=pw1;
    }
    return 1;
}

Handle(AIS_Shape) draw_primitives::draw_3d_line_wire_low_memory_usage(const std::vector<gp_Pnt>& pvec){
    // Check if the input vector is empty
    if (pvec.empty()) {
        std::cerr << "Error: The input vector is empty." << std::endl;
        return draw_3d_point({0,0,0});
    }

    // Create an array of points from the input vector
    TColgp_Array1OfPnt array(1, static_cast<Standard_Integer>(pvec.size()));
    for (Standard_Integer i = 1; i <= pvec.size(); ++i) {
        array.SetValue(i, pvec[i - 1]);
    }

    // Create a polygon from the array of points
    Handle(Poly_Polygon3D) aPolygon = new Poly_Polygon3D(array);

    // Create a new shape with the updated polygon
    TopoDS_Shape resultShape;
    BRep_Builder brepBuilder;
    TopoDS_Edge edge;
    brepBuilder.MakeEdge(edge, aPolygon);
    resultShape = edge;

    // Create an AIS_Shape to visualize the result
    Handle(AIS_Shape) aShape = new AIS_Shape(resultShape);

    return aShape;
}

Handle(AIS_Shape) draw_primitives::draw_3d_line_wire_low_memory_usage(const std::vector<gp_Pnt>& pvec, Handle(AIS_Shape) existingShape) {
    if (pvec.empty()) {
        std::cerr << "Error: The input vector is empty." << std::endl;
        return draw_3d_point({0,0,0});
    }

    TColgp_Array1OfPnt array(1, static_cast<Standard_Integer>(pvec.size()));
    for (Standard_Integer i = 1; i <= pvec.size(); ++i) {
        array.SetValue(i, pvec[i - 1]);
    }

    Handle(Poly_Polygon3D) aPolygon = new Poly_Polygon3D(array);

    TopoDS_Shape resultShape;
    BRep_Builder brepBuilder;
    TopoDS_Edge edge;
    if (existingShape.IsNull()) {
        brepBuilder.MakeEdge(edge, aPolygon);
        resultShape = edge;
    } else {
        TopoDS_Edge existingEdge = TopoDS::Edge(existingShape->Shape());
        brepBuilder.UpdateEdge(existingEdge, aPolygon);
        resultShape = existingEdge;
    }

    if (existingShape.IsNull()) {
        return new AIS_Shape(resultShape);
    } else {
        existingShape->Set(resultShape);
        return existingShape;
    }
}

Handle(AIS_Shape) draw_primitives::draw_3d_spline_degree_3(std::vector<gp_Pnt> &pvec, double &length){

    filter_out_duplicate_points(pvec);

    if(pvec.size()==2){
        return draw_3d_line(pvec.front(),pvec.back());
    }
    if(pvec.size()<2){
        return draw_3d_point(pvec.front());
    }
    if(pvec.size()==0){
        std::cout<<"spline error, no points given."<<std::endl;
        return draw_3d_point({0,0,0});
    }

    bool periodicFlag=false;
    double tolerance=Precision::Approximation();

    // Create handle to array of points
    Handle(TColgp_HArray1OfPnt) arrayPoints = new TColgp_HArray1OfPnt(1, static_cast<Standard_Integer>(pvec.size()));
    for (size_t i = 0; i < pvec.size(); ++i) {
        arrayPoints->SetValue(i + 1, pvec[i]);
    }

    // Create GeomAPI_Interpolate object
    GeomAPI_Interpolate interpolator(arrayPoints, periodicFlag, tolerance);

    // Perform interpolation
    interpolator.Perform();

    // Check if interpolation was successful
    if (!interpolator.IsDone()) {
        std::cerr << "Failed to interpolate points." << std::endl;
        return nullptr;
    }

    // Retrieve the interpolated B-spline curve
    Handle(Geom_BSplineCurve) spline = interpolator.Curve();

    // Compute the length of the B-spline curve
    GeomAdaptor_Curve adaptorCurve(spline);
    GCPnts_AbscissaPoint lengthCalculator;
    length = lengthCalculator.Length(adaptorCurve);

    // Create an edge from the B-spline curve
    BRepBuilderAPI_MakeEdge edgeMaker(spline);
    TopoDS_Edge edge = edgeMaker.Edge();

    // Create an AIS_Shape for the edge
    return new AIS_Shape(edge);
}

double draw_primitives::get_3d_spline_lenght_degree_3(std::vector<gp_Pnt> pvec){
    // Filter out duplicate points
    filter_out_duplicate_points(pvec);

    // Handle special cases
    if (pvec.size() == 2) {
        return pvec.front().Distance(pvec.back());
    }
    if (pvec.size() < 2) {
        std::cerr << "spline error, not enough points given." << std::endl;
        return 0.0;
    }
    if (pvec.size() == 0) {
        std::cerr << "spline error, no points given." << std::endl;
        return 0.0;
    }

    bool periodicFlag = false;
    double tolerance = Precision::Approximation();

    // Create handle to array of points
    Handle(TColgp_HArray1OfPnt) arrayPoints = new TColgp_HArray1OfPnt(1, static_cast<Standard_Integer>(pvec.size()));
    for (size_t i = 0; i < pvec.size(); ++i) {
        arrayPoints->SetValue(static_cast<Standard_Integer>(i) + 1, pvec[i]);
    }

    // Create GeomAPI_Interpolate object
    GeomAPI_Interpolate interpolator(arrayPoints, periodicFlag, tolerance);

    // Perform interpolation
    interpolator.Perform();

    // Check if interpolation was successful
    if (!interpolator.IsDone()) {
        std::cerr << "Failed to interpolate points." << std::endl;
        return 0.0;
    }

    // Retrieve the interpolated B-spline curve
    Handle(Geom_BSplineCurve) spline = interpolator.Curve();

    // Compute the length of the B-spline curve
    GeomAdaptor_Curve adaptorCurve(spline);
    GCPnts_AbscissaPoint lengthCalculator;
    Standard_Real length = lengthCalculator.Length(adaptorCurve);

    return length;
}

void draw_primitives::interpolate_point_on_spline_degree_3(const std::vector<gp_Pnt>& pvec, const double &progress, gp_Pnt &pi) {
    // Clamp progress between 0 and 1
    double pro=progress;
    pro= std::max(0.0, std::min(1.0, pro));

    // Check if there are enough points for interpolation
    if (pvec.size() < 2) {
        std::cerr << "Spline has invalid input parameters." << std::endl;
        pi = gp_Pnt(0, 0, 0); // Default point if input is invalid
        return;
    }

    bool periodicFlag = false;
    double tolerance = Precision::Approximation();

    // Create handle to array of points
    Handle(TColgp_HArray1OfPnt) arrayPoints = new TColgp_HArray1OfPnt(1, static_cast<Standard_Integer>(pvec.size()));
    for (size_t i = 0; i < pvec.size(); ++i) {
        arrayPoints->SetValue(i + 1, pvec[i]);
    }

    // Create GeomAPI_Interpolate object
    GeomAPI_Interpolate interpolator(arrayPoints, periodicFlag, tolerance);

    // Perform interpolation
    interpolator.Perform();

    // Check if interpolation was successful
    if (!interpolator.IsDone()) {
        std::cerr << "Spline failed to interpolate points." << std::endl;
        pi = gp_Pnt(0, 0, 0); // Default point if interpolation fails
        return;
    }

    // Retrieve the interpolated B-spline curve
    Handle(Geom_BSplineCurve) spline = interpolator.Curve();

    // Get the parameter range of the curve
    Standard_Real first = spline->FirstParameter();
    Standard_Real last = spline->LastParameter();

    // Calculate the parameter value corresponding to the progress
    Standard_Real parameter = first + pro * (last - first);

    // Evaluate the point on the curve at the calculated parameter value
    spline->D0(parameter, pi);
}

void draw_primitives::get_transformed_line_points(Handle(AIS_Shape) aShape, gp_Pnt &p0, gp_Pnt &p1){

    // Get the shape from AIS_Shape
    TopoDS_Shape gcode_shape = aShape->Shape();

    // Get the edge and its geometry
    TopoDS_Edge edge = TopoDS::Edge(gcode_shape);

    // Get the local transformation of the edge
    gp_Trsf localTransformation = aShape->LocalTransformation();

    // Retrieve the geometry of the edge after applying the local transformation
    Standard_Real first, last;
    Handle(Geom_Curve) curve = BRep_Tool::Curve(edge, first, last);

    // Get the transformed endpoints of the curve
    p0 = curve->Value(first).Transformed(localTransformation);
    p1 = curve->Value(last).Transformed(localTransformation);
}

std::vector<gp_Pnt> draw_primitives::record_tooldir_path_line(gp_Pnt p0, gp_Pnt p1,
                                                              gp_Pnt abc0, gp_Pnt abc1,
                                                              double tp_height) {

    std::vector<gp_Pnt> pvec;
    gp_Pnt pi, abci, p, ta;

    const int num_cycles = 100;  // Number of interpolation cycles
    const double min_distance = 0.1;  // Minimum distance between points to be added to the vector

    for (int i = 0; i <= num_cycles; ++i) {
        double t = static_cast<double>(i) / num_cycles;

        // Interpolate points on the line and along the auxiliary line
        interpolate_point_on_line(p0, p1, t, pi);
        interpolate_point_on_line(abc0, abc1, t, abci);

        // Create a shape and transform it
        Handle(AIS_Shape) aShape = draw_3d_line({0, 0, 0}, {0, 0, tp_height});
        aShape = rotate_translate_3d(aShape, pi, abci.X(), abci.Y(), abci.Z());
        get_transformed_line_points(aShape, p, ta);

        // Always add the first point
        if (pvec.empty()) {
            pvec.push_back(ta);
        } else {
            // Add points to the vector if the distance condition is met
            if (pvec.back().Distance(ta) > min_distance) {
                pvec.push_back(ta);
            }
        }
    }

    // Ensure the last point is added
    if (!pvec.empty()) {
        pvec.push_back(ta);  // Add the last generated point to pvec
    }

    return pvec;
}

std::vector<gp_Pnt> draw_primitives::record_tooldir_path_arc(const gp_Pnt &p0, const gp_Pnt &pw, const gp_Pnt &p1,
                                                             const gp_Pnt &abc0, const gp_Pnt &abc1,
                                                             const double tp_height) {
    std::vector<gp_Pnt> pvec;
    gp_Pnt pi, abci, p, ta;

    const int num_cycles = 100;  // Number of interpolation cycles
    const double min_distance = 0.5;  // Minimum distance between points to be added to the vector

    for (int i = 0; i <= num_cycles; ++i) {
        double t = static_cast<double>(i) / num_cycles;

        // Interpolate points on the arc and line
        interpolate_point_on_arc(p0, pw, p1, t, pi);
        interpolate_point_on_line(abc0, abc1, t, abci);

        // Create a shape and transform it
        Handle(AIS_Shape) aShape = draw_3d_line({0, 0, 0}, {0, 0, tp_height});
        aShape = rotate_translate_3d(aShape, pi, abci.X(), abci.Y(), abci.Z());

        // Get transformed points
        get_transformed_line_points(aShape, p, ta);

        // Always add the first point
        if (pvec.empty()) {
            pvec.push_back(ta);
        } else {
            // Add points to the vector if the distance condition is met
            if (pvec.back().Distance(ta) > min_distance) {
                pvec.push_back(ta);
            }
        }
    }

    // Ensure the last point is added
    if (!pvec.empty()) {
        pvec.push_back(ta);  // Add the last generated point to pvec
    }

    return pvec;
}

std::vector<gp_Pnt> draw_primitives::record_tooldir_path_circle(const gp_Pnt &p0, const gp_Pnt &pc, const int &plane, const int &gcode,
                                                                const gp_Pnt &abc0, const gp_Pnt &abc1,
                                                                const double tp_height) {
    std::vector<gp_Pnt> pvec;
    gp_Pnt pi, abci, p, ta;

    const int num_cycles = 100;  // Number of interpolation cycles
    const double min_distance = 0.5;  // Minimum distance between points to be added to the vector

    for (int i = 0; i <= num_cycles; ++i) {
        double t = static_cast<double>(i) / num_cycles;

        // Interpolate points on the arc and line
        interpolate_point_on_circle(p0, pc, plane, gcode, t, pi);
        interpolate_point_on_line(abc0, abc1, t, abci);

        // Create a shape and transform it
        Handle(AIS_Shape) aShape = draw_3d_line({0, 0, 0}, {0, 0, tp_height});
        aShape = rotate_translate_3d(aShape, pi, abci.X(), abci.Y(), abci.Z());

        // Get transformed points
        get_transformed_line_points(aShape, p, ta);

        // Always add the first point
        if (pvec.empty()) {
            pvec.push_back(ta);
        } else {
            // Add points to the vector if the distance condition is met
            if (pvec.back().Distance(ta) > min_distance) {
                pvec.push_back(ta);
            }
        }
    }

    // Ensure the last point is added
    if (!pvec.empty()) {
        pvec.push_back(ta);  // Add the last generated point to pvec
    }

    return pvec;
}

std::vector<gp_Pnt> draw_primitives::record_tooldir_path_spline_degree_3(const std::vector<gp_Pnt> pwvec,
                                                                         const gp_Pnt &abc0, const gp_Pnt &abc1,
                                                                         const double tp_height) {
    std::vector<gp_Pnt> pvec;
    gp_Pnt pi, abci, p, ta;

    const int num_cycles = 100;  // Number of interpolation cycles
    const double min_distance = 0.5;  // Minimum distance between points to be added to the vector

    for (int i = 0; i <= num_cycles; ++i) {
        double t = static_cast<double>(i) / num_cycles;

        // Interpolate points on the spline and line
        interpolate_point_on_spline_degree_3(pwvec,t,pi);
        interpolate_point_on_line(abc0, abc1, t, abci);

        // Create a shape and transform it
        Handle(AIS_Shape) aShape = draw_3d_line({0, 0, 0}, {0, 0, tp_height});
        aShape = rotate_translate_3d(aShape, pi, abci.X(), abci.Y(), abci.Z());

        // Get transformed points
        get_transformed_line_points(aShape, p, ta);

        // Always add the first point
        if (pvec.empty()) {
            pvec.push_back(ta);
        } else {
            // Add points to the vector if the distance condition is met
            if (pvec.back().Distance(ta) > min_distance) {
                pvec.push_back(ta);
            }
        }
    }

    // Ensure the last point is added
    if (!pvec.empty()) {
        pvec.push_back(ta);  // Add the last generated point to pvec
    }

    return pvec;
}

std::vector<gp_Pnt> draw_primitives::trim_recorded_tooldir_path_line_both_sides(const std::vector<gp_Pnt>& pvec, double trim_dist) {
    // Calculate total length of the curve
    double totalLength = 0.0;
    std::vector<gp_Pnt> trimmedPath;

    for (size_t i = 0; i < pvec.size() - 1; ++i) {
        totalLength += pvec[i].Distance(pvec[i + 1]);
    }

    if ((2 * trim_dist + 1) > totalLength) {
        trim_dist = (totalLength - 1) / 2;
    }

    double accumulatedLength = 0.0;
    bool startFound = false;

    for (size_t i = 0; i < pvec.size() - 1; ++i) {
        double segmentLength = pvec[i].Distance(pvec[i + 1]);
        double previousLength = accumulatedLength;
        accumulatedLength += segmentLength;

        if (accumulatedLength > trim_dist && !startFound) {
            double remainingLength = trim_dist - previousLength;
            double progress = remainingLength / segmentLength;
            gp_Pnt startPoint;
            interpolate_point_on_line(pvec[i], pvec[i + 1], progress, startPoint);
            trimmedPath.push_back(startPoint);
            startFound = true;
        }

        if (accumulatedLength <= (totalLength - trim_dist) && startFound) {
            trimmedPath.push_back(pvec[i + 1]);
        } else if (accumulatedLength > (totalLength - trim_dist) && startFound) {
            double remainingLength = (totalLength - trim_dist) - previousLength;
            double progress = remainingLength / segmentLength;
            gp_Pnt endPoint;
            interpolate_point_on_line(pvec[i], pvec[i + 1], progress, endPoint);
            trimmedPath.push_back(endPoint);
            break;
        }
    }
    return trimmedPath;
}

void draw_primitives::interpolate_point_on_pvec_path(const std::vector<gp_Pnt>& pvec, const double& pathlength, double progress, gp_Pnt& pi) {
    // Clamp progress between 0 and 1
    progress = std::max(0.0, std::min(1.0, progress));

    double li = progress * pathlength;
    pi = gp_Pnt(0, 0, 0); // Reset.

    double ls = 0, le = 0;
    for (size_t i = 0; i < pvec.size() - 1; ++i) {
        double l = pvec[i].Distance(pvec[i + 1]);
        ls = le;
        le += l;

        if (le > li) {
            double local_progress = (li - ls) / l;
            interpolate_point_on_line(pvec[i], pvec[i + 1], local_progress, pi);
            return;
        }
    }

    // If progress equals or exceeds the path length, return the last point
    pi = pvec.back();
}

/*
// Create B-spline curve from points
        gp_Pnt pt(x, y, z);
        points.SetValue(i + 1, pt);
  TColgp_Array1OfPnt points(1, num_points); // Use TColgp_Array1OfPnt for B-spline points
GeomAPI_PointsToBSpline spline(points, 3, 8, GeomAbs_C2); // Degree 3, max segments 8, C2 continuity
Handle(Geom_BSplineCurve) bspline = spline.Curve();

// Create shape from B-spline curve
TopoDS_Edge edge = BRepBuilderAPI_MakeEdge(bspline);
TopoDS_Wire wire = BRepBuilderAPI_MakeWire(edge);
Handle(AIS_Shape) ais_shape = new AIS_Shape(wire);
*/































