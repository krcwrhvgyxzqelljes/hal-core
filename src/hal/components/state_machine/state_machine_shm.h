#ifndef TP_STATE_MACHINE_H
#define TP_STATE_MACHINE_H

//! Author  : Skynet Cyberdyne
//! Licence : MIT
//! Date    : 2023

#ifdef __cplusplus

#include <vector>
#include <iostream>
#include <cmath>

// Define the key for shared memory
#define SHM_KEY 1234  // Example key value
#define INTERVAL_APP 0.050
#define INTERVAL_HAL 0.001

/*

Usage:

    shared_mem_data d;
    d.dvalue=2223333333;
    d.value=12;
    smv->write_to_shared_memory(d);

*/

#include "gcode_parser.h"
#include "../../../../vendor/scurve/scurve_engine/scurve_struct.h"

enum cnc_state_mode {
    MANUAL,
    MDI,
    AUTO
};

enum cnc_online_mode {
    ONLINE,
    OFFLINE
};

enum cnc_run_mode {
    RUN,
    PAUSE,
    STOP
};

struct shared_mem_data {

    cnc_state_mode state_mode;
    cnc_online_mode online_mode;
    cnc_run_mode run_mode;

    double maxvel[9];
    double maxacc[9];
    double maxjerk[9];
    double pos[9];
    double dtg[9];
    int homed[9];

    double curvel;

    int jog[9]; // -1 is negative jog, 0 is jog stop, 1 is jog positive.
    double jog_speed_procent;
    double jog_step_size;
    double jog_velocity;
    int jog_step_enable;

    std::vector<shape> svec;

    // For each scurve axis we store the data in here.
    scurve_data scurve_dvec[9];
};

class state_machine_shm
{
public:

    //! Constructor.
    state_machine_shm();
    ~state_machine_shm();

    // shared_mem_data sdata;

    void create_shared_memory();
    void write_to_shared_memory(shared_mem_data data); // Method to update shared memory

    void attach_shared_memory();
    void detach_shared_memory();

    shared_mem_data read_from_shared_memory(); // Getter method for accessing shm_ptr[0]

    shared_mem_data* shm_ptr; // Pointer to shared memory data

private:
    int shm_id;
};

//! Here it tells if this code is used in c, convert the class to a struct. This is handy!
#else
typedef struct state_machine_vector state_machine_vector;
#endif //! cplusplus

#endif



















