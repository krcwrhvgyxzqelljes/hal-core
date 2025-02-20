#ifndef SCURVE_CONSTRUCT_H
#define SCURVE_CONSTRUCT_H

#include "math.h"
#include "scurve_struct.h"

#ifdef __cplusplus

double ttot_period(scurve_period p);
double stot_period(scurve_period p);

double delvelocity(scurve_data d);
double ttot(scurve_data d);
double stot(scurve_data d);
double vel(scurve_data d);
double acc(scurve_data d);
double pos(scurve_data d);

//! Class to construct a forward or stop scurve using different functions.
class scurve_engine
{
public:
    scurve_engine();

    //! Set values for initialisation.
    static scurve_data set_init_values(double jerk_max,
                                       double acceleration_max,
                                       double maximum_velocity,
                                       double cycletime,
                                       scurve_data s);

    //! Tarpos input positive or negative.
    //! Enable is jog forward or reverse, else stop jog.
    static void jog_velocity(scurve_data &s, int enable, double endvel, double endacc, double tarpos);

    //! Tarpos input positive or negative.
    //! Enable is jog forward or reverse, else stop jog to velocity end, like a pause.
    //! Jog forward or jog reverse input to verify direction. This prevents a direction change "saw effect" depending on the
    //! current position and target position.
    static void jog_position_master(scurve_data &s, int enable, double endvel, double endacc, double tarpos, int jog_fwd, int jog_rev);

    //! Update curve cycle.
    static void jog_update(scurve_data &s);

    //! Results :
    static void jog_results(scurve_data s, double &velocity, double &acceleration, double &position, int &finished);

    static void forward_curve_build(scurve_data &s);

    // Test ve's
    static void jog_position_master_endve(scurve_data &s, int enable, double endvel, double endacc, double tarpos, int jog_fwd, int jog_rev);
    static int jog_position_fwd_endve(scurve_data &s, int enable, double tarpos);
    static int jog_position_rev_endve(scurve_data &s, int enable, double tarpos);
    static void jog_update_ve(scurve_data &s);

    static int jog_position_fwd(scurve_data &s, int enable, double tarpos);
    static int jog_position_rev(scurve_data &s, int enable, double tarpos);

    static void stop_curve_build(scurve_data &s);

    static void zero_period(scurve_period &p);
    static void stop_lenght(scurve_data &s, double &lenght, double &time);

    // Added for simplicity.
    static int jog(scurve_data &s, double tarpos);
    static int jog_stop(scurve_data &s);

private:

    static void t1_t2_t3_build(double jermax,
                               double accinf,
                               double curvel,
                               double endvel,
                               scurve_period &c1,
                               scurve_period &c2,
                               scurve_period &c3);

    static void t1_build(double jermax,
                         double curvel,
                         double curacc,
                         double endacc,
                         scurve_period &c1);

    static void t2_build(double curvel,
                         double endvel,
                         double accinf,
                         scurve_period &c2);

    static void t3_build(double jermax,
                         double accinf,
                         double curvel,
                         double curacc,
                         double endacc,
                         scurve_period &c3);

    static void t4_build(double curvel,
                         scurve_period &c4);

    static void t1_play(double at_time,
                        double accinf,
                        double jermax,
                        double timbeg,
                        double timend,
                        double velini,
                        double disbeg,
                        double &velend,
                        double &disend,
                        double &accend);

    static void t2_play(double attime,
                        double accinf,
                        double timsta,
                        double timend,
                        double velbeg,
                        double &velend,
                        double &disend,
                        double &accend);

    static void t3_play(double attime,
                        double accinf,
                        double jermax,
                        double timbeg,
                        double timend,
                        double velini,
                        double disbeg,
                        double &velend,
                        double &disend,
                        double &accend);

    static void t4_play(double attime,
                        double timsta,
                        double velbeg,
                        double &velend,
                        double &disend,
                        double &accend);

    // "dv"  Delta velocity, dv=vo-ve, derived from: t1=2*(ve-vo)/as;
    // A t1,t3 curve using as is excact dv. Then 0.5*dv is a t1 or a t3.
    static double delta_vel(double jm, double as);

    // When vo to ve < dv, use custom as.
    // This results in t1 with ace, t3 with acs.
    // Valid for curvel with zero acceleration, endvel with zero acceleration.
    static void t1_t3_custom_as(double jm, double curvel, double endvel, double &as);

    // The netto difference between two values.
    static double diff(double a, double b);

};

//! Here it tells if this code is used in c, convert the class to a struct. This is handy!
#else
typedef struct scurve_engine scurve_engine;
#endif //! cplusplus

#endif // SCURVE_CONSTRUCT_H












