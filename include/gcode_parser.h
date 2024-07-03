#ifndef GCODE_PARSER_H
#define GCODE_PARSER_H

#include <vector>
#include "std_functions.h"


struct gcode_line {
    double a,b,c,d,e,f,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x,y,z;
    std::vector<std::pair<char,double>> g_nrs;
    std::vector<std::pair<char,double>> m_nrs;
    std::string comment;
};

class gcode_parser
{
public:
    gcode_parser();

    void parse(const std::string &file, std::vector<gcode_line> &gvec, int debug);

private:
    std::pair<char, double> split_token(const std::string& token);
    void tokenize(const std::string& file, std::vector<gcode_line> &gvec);
    void print_line(const gcode_line& line);
};

#endif // GCODE_PARSER_H
