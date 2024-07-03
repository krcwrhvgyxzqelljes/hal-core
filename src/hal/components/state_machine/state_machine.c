#include "rtapi.h"
#include "rtapi_ctype.h"
#include "rtapi_app.h"
#include "rtapi_string.h"
#include "rtapi_errno.h"
#include "rtapi_math64.h"
#include <rtapi_io.h>
#include "hal.h"

/* module information */
MODULE_AUTHOR("Skynet");
MODULE_DESCRIPTION("Halmodule");
MODULE_LICENSE("GPL");

static int comp_idx;

typedef struct {
    bool ok;
} skynet_t;
skynet_t *skynet;

typedef struct {
    hal_float_t *Pin;
} float_data_t;
float_data_t *x_axis_0;
float_data_t *x_axis_1;
float_data_t *y_axis;
float_data_t *z_axis;

//! Pins
typedef struct {
    hal_bit_t *Pin;
} bit_data_t;
bit_data_t *enable;

typedef struct {
    hal_s32_t *Pin;
} s32_data_t;

typedef struct {
    hal_u32_t *Pin;
} u32_data_t;

typedef struct {
    hal_port_t *Pin;
} port_data_t;
port_data_t *port;

//! Params
typedef struct {
    hal_float_t Pin;
} param_float_data_t;

typedef struct {
    hal_bit_t Pin;
} param_bit_data_t;

struct state_machine_shm *ptr; // Pointer to vector c++ class.
extern struct state_machine_shm* shm_init_ptr();
extern void shm_detach(struct state_machine_shm *ptr);
extern void shm_update(struct state_machine_shm *ptr);
extern void shm_update_pos(struct state_machine_shm *ptr, double* pos);

static int comp_idx; /* component ID */

static void the_function();
static int setup_pins();

int rtapi_app_main(void) {

    int r = 0;
    comp_idx = hal_init("state_machine");
    if(comp_idx < 0) return comp_idx;
    r = hal_export_funct("state_machine.update", the_function, &skynet,0,0,comp_idx);

    r+=setup_pins();

    if(r) {
        hal_exit(comp_idx);
    } else {
        hal_ready(comp_idx);
    }

    ptr=shm_init_ptr();

    return 0;
}

void rtapi_app_exit(void){
    shm_detach(ptr);
    hal_exit(comp_idx);
}

//! Perforn's every ms.
static void the_function(){

    shm_update(ptr); // Get the status from the gui.

    double pos[9];
    shm_update_pos(ptr, pos);

    *x_axis_0->Pin=pos[0]; // Dual motors for x.
    *x_axis_1->Pin=pos[0];
    *y_axis->Pin=pos[1];
    *z_axis->Pin=pos[2]; // And so on for abc uvw.

    if(*enable->Pin==1){

    }
}

static int setup_pins(){
    int r=0;

    //! Input pins, type bit.
    enable = (bit_data_t*)hal_malloc(sizeof(bit_data_t));
    r+=hal_pin_bit_new("state_machine.enable",HAL_IN,&(enable->Pin),comp_idx);

    x_axis_0 = (float_data_t*)hal_malloc(sizeof(float_data_t));
    r+=hal_pin_float_new("state_machine.x_axis_0",HAL_OUT,&(x_axis_0->Pin),comp_idx);

    x_axis_1 = (float_data_t*)hal_malloc(sizeof(float_data_t));
    r+=hal_pin_float_new("state_machine.x_axis_1",HAL_OUT,&(x_axis_1->Pin),comp_idx);

    y_axis = (float_data_t*)hal_malloc(sizeof(float_data_t));
    r+=hal_pin_float_new("state_machine.y_axis",HAL_OUT,&(y_axis->Pin),comp_idx);

    z_axis = (float_data_t*)hal_malloc(sizeof(float_data_t));
    r+=hal_pin_float_new("state_machine.z_axis",HAL_OUT,&(z_axis->Pin),comp_idx);



    return r;
}





































