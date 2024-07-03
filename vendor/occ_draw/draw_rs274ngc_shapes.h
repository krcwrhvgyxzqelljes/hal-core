#ifndef DRAW_RS274NGC_SHAPES_H
#define DRAW_RS274NGC_SHAPES_H

#include "../vendor/rs274ngc/rs274ngc_data.h"
#include "draw_primitives.h"

class draw_rs274ngc_shapes
{
public:
    draw_rs274ngc_shapes();
    void get_shapes(std::vector<rs274ngc_data> &datavec, std::vector<Handle(AIS_Shape)> &shapevec);
};

#endif // DRAW_RS274NGC_SHAPES_H
