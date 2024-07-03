#include "draw_rs274ngc_shapes.h"

draw_rs274ngc_shapes::draw_rs274ngc_shapes()
{

}

/*
struct rs274ngc_data {
    int type;           // G0,G1,G2,G3,G9
    gp_Pnt p0,p1;       // Line start, end = p0 to p1.
    gp_Pnt pc;          // Arc center, relative to startpoint? z=p1.z
    gp_Pnt abc0, abc1, uvw0, uvw1;
    double feed;
    int line_nr;
};*/

// Todo if arc begin z is not arc end z, then its a spiral. Draw it as a spiral.
void draw_rs274ngc_shapes::get_shapes(std::vector<rs274ngc_data> &datavec,
                                      std::vector<Handle(AIS_Shape)> &shapevec){

    for(auto d:datavec){

        // G0 rapid.
        if(d.type==0){
            shapevec.push_back(draw_primitives::colorize( draw_primitives::draw_3d_line(d.p0,d.p1),Quantity_NOC_GRAY15,0) );
        }
        // G1 linear.
        if(d.type==1){
            shapevec.push_back(draw_primitives::colorize( draw_primitives::draw_3d_line(d.p0,d.p1),Quantity_NOC_GRAY50,0) );
        }

        // G2 cw arc.
        if(d.type==2
                && d.p0.Distance(d.p1)>0    // Start, end differs.
                && d.p0.Distance(d.pc)>0    // Has radius.
                ){ // Validate arc.
            if(d.plane==1){ // XY
                shapevec.push_back(draw_primitives::colorize( draw_primitives::draw_3d_pc_arc(d.p0,d.p1,d.pc,0,0,1,d.pw),Quantity_NOC_GRAY50,0) );
            }
            if(d.plane==2){ // YZ
                shapevec.push_back(draw_primitives::colorize( draw_primitives::draw_3d_pc_arc(d.p0,d.p1,d.pc,1,0,0,d.pw),Quantity_NOC_GRAY50,0) );
            }
            if(d.plane==3){ // XZ
                shapevec.push_back(draw_primitives::colorize( draw_primitives::draw_3d_pc_arc(d.p0,d.p1,d.pc,0,1,0,d.pw),Quantity_NOC_GRAY50,0) );
            }
        }

        // G3 ccw arc.
        if(d.type==3
                && d.p0.Distance(d.p1)>0    // Start, end differs.
                && d.p0.Distance(d.pc)>0    // Has radius.
                ){
            if(d.plane==1){ // XY
                shapevec.push_back(draw_primitives::colorize( draw_primitives::draw_3d_pc_arc(d.p1,d.p0,d.pc,0,0,1,d.pw),Quantity_NOC_GRAY50,0) );
            }
            if(d.plane==2){ // YZ
                shapevec.push_back(draw_primitives::colorize( draw_primitives::draw_3d_pc_arc(d.p1,d.p0,d.pc,1,0,0,d.pw),Quantity_NOC_GRAY50,0) );
            }
            if(d.plane==3){ // XZ
                shapevec.push_back(draw_primitives::colorize( draw_primitives::draw_3d_pc_arc(d.p1,d.p0,d.pc,0,1,0,d.pw),Quantity_NOC_GRAY50,0) );
            }
        }

        // G2 G3 full circle.
        if( (d.type==2 || d.type==3)
                && d.p0.Distance(d.p1)==0   // Start = end.
                && d.p0.Distance(d.pc)>0    // Has radius.
                ){ // Validate full circle.
            if(d.plane==1){ // XY
                shapevec.push_back(draw_primitives::colorize( draw_primitives::draw_3d_pc_circle(d.pc,0,0,1,d.p1.Distance(d.pc)),Quantity_NOC_GRAY50,0) );
            }
            if(d.plane==2){ // YZ
                shapevec.push_back(draw_primitives::colorize( draw_primitives::draw_3d_pc_circle(d.pc,1,0,0,d.p1.Distance(d.pc)),Quantity_NOC_GRAY50,0) );
            }
            if(d.plane==3){ // XZ
                shapevec.push_back(draw_primitives::colorize( draw_primitives::draw_3d_pc_circle(d.pc,0,1,0,d.p1.Distance(d.pc)),Quantity_NOC_GRAY50,0) );
            }
        }

        if(d.type==9){ // Draw general.

        }
    }
}



