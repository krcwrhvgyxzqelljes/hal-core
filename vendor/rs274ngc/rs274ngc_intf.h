#ifndef RS274NGC_INTF_H
#define RS274NGC_INTF_H

#include <string>
#include <vector>
#include "rs274ngc_data.h"

class rs274ngc_intf
{
public:
    rs274ngc_intf();

    int load_file(std::string file_in, std::string file_out, std::vector<rs274ngc_data> &datavec);
};

#endif // RS274NGC_INTF_H
