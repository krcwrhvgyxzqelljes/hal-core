#ifndef HAL_FUNCTIONS_H
#define HAL_FUNCTIONS_H

#include "hal.h"
#include "iostream"

class hal_functions
{
public:
    hal_functions();

    void update();
    void exit();

    void run(int state);
    void pause(int state);

    void maxvel(double value);
    void maxacc(double value);
    void maxjerk(double value);
    void feed_override(double value);
    void rapid_override(double value);

    void mode_manual();
    void mode_auto();
    void mode_mdi();

private:

    //! Pins
    typedef struct {
        hal_bit_t *Pin;
    } bit_data_t;
    bit_data_t *h_on, *h_run, *h_pause;
    bit_data_t *h_motion_finished;



    int comp_id=0;



};

#endif // HAL_FUNCTIONS_H
