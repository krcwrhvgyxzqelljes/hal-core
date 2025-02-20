#ifndef SCURVE_STRUCT_H
#define SCURVE_STRUCT_H

//! Struct used to save scurve periodic data.
struct scurve_period {
    double accbeg, accend;
    double velini, velbeg, velend;
    double disbeg, disend;
    double timbeg, timend;
    double jermax, accinf;
};

struct position_data {
    double stopdist;
    double stoptime;
    double overshoot;
    double dist_remove_a_cycle;
    int stopinit;
    int btn_fwd;
    int btn_rev;
    int cycles;
    int cycle_count;
};

enum jog_mode {
    POSITION_SC,
    VELOCITY_SC
};

enum jog_direction {
    FORWARD_SC,
    REVERSE_SC
};

struct jog_input {
    int enable;                 // No enable will behave as pause.
    enum jog_direction dir;     // Direction of motion.
    enum jog_mode mode;         // Position or velocity control mode.
};

//! Struct used to store forward or stop scurve data.
struct scurve_data {

    struct scurve_period c0,c1,c2,c3,c4;   // Periods to contruct a forward or stop scurve.
    double intval;              // Cycletime.
    double jermax;              // Jerk max.
    double curtim;              // Time current.
    double endacc;              // Acceleration end.
    double endvel;              // Velocity end.
    double maxvel;              // Velocity max.
    double maxacc;              // Acceleration max.
    double guipos;              // Guipos has no reverse pos.
    double guivel;
    double guiacc;
    double maxpos;              // Limit for jogging +
    double minpos;              // Limit for jogging -
    int finish;                 // Curve has no velocity.

    double incpos;              // Increment position for each cycle. Includes reverse motion.
    double oldpos;              // Previous displacements.

    int jog_btn_dir, jog_stop_first;

    double tarpos;              // Tarpos forward move.

    double vr, ar, sr;          // Results for "vr" velocity, "ar" acceleration, "sr" displacement.

    int revers;                 // Reverse motion active.
    int modpos;                 // Mode position.
    struct position_data pd;    // Position data.
    struct jog_input jog;       // Inputs for jogging.

    int rcode;                  // Master position function return code.
};

#endif // SCURVE_STRUCT_H
