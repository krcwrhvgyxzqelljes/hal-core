#ifndef RS274NGC_DATA_H
#define RS274NGC_DATA_H

#include "gp_Pnt.hxx"

/*
A total of 52 G-codes are implemented.

The groups are:
group  0 = {g4,g10,g28,g30,g53,g92,g92.1,g92.2,g92.3} - NON-MODAL
dwell, setup, return to ref1, return to ref2,
motion in machine coordinates, set and unset axis offsets
group  1 = {g0,g1,g2,g3,g38.2,g80,g81,g82,g83,g84,g85,g86,g87,g88,g89} - motion
group  2 = {g17,g18,g19}   - plane selection
group  3 = {g90,g91}       - distance mode
group  5 = {g93,g94}       - feed rate mode
group  6 = {g20,g21}       - units
group  7 = {g40,g41,g42}   - cutter diameter compensation
group  8 = {g43,g49}       - tool length offset
group 10 = {g98,g99}       - return mode in canned cycles
group 12 = {g54,g55,g56,g57,g58,g59,g59.1,g59.2,g59.3} - coordinate system
group 13 = {g61,g61.1,g64} - control mode
*/

struct rs274ngc_data {
    int type;           // G0,G1,G2,G3,G9
    gp_Pnt p0,p1;       // Line start, end = p0 to p1.
    gp_Pnt pc;          // Arc center, relative to startpoint? z=p1.z
    gp_Pnt pw;          // Arc waypoint, line waypoint.
    gp_Pnt abc0, abc1, uvw0, uvw1;
    double feed;
    int line_nr;
    int plane;
};

#endif // RS274NGC_DATA_H
