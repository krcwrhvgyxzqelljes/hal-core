#include "hal_functions.h"

hal_functions::hal_functions()
{
    std::system("./halcmd -R");

    int r=0;

    comp_id = hal_init("cnc");
    hal_comp_name(comp_id);
    hal_malloc(200);

    h_on = (bit_data_t*)hal_malloc(sizeof(bit_data_t));
    if(hal_pin_bit_new("cnc.on",HAL_OUT,&(h_on->Pin),comp_id)){ // If successful, the hal_pin_xxx_new() functions return 0.
        std::cout<<"hal pin new error."<<std::endl;
    }

    h_run = (bit_data_t*)hal_malloc(sizeof(bit_data_t));
    if(hal_pin_bit_new("cnc.run",HAL_OUT,&(h_run->Pin),comp_id)){
        std::cout<<"hal pin new error."<<std::endl;
    }

    h_pause = (bit_data_t*)hal_malloc(sizeof(bit_data_t));
    if(hal_pin_bit_new("cnc.pause",HAL_OUT,&(h_pause->Pin),comp_id)){
        std::cout<<"hal pin new error."<<std::endl;
    }

    h_motion_finished = (bit_data_t*)hal_malloc(sizeof(bit_data_t));
    if(hal_pin_bit_new("cnc.motion_finished",HAL_IN,&(h_motion_finished->Pin),comp_id)){
        std::cout<<"hal pin new error."<<std::endl;
    }

    hal_ready(comp_id);
    std::cout<<"hal ready. component id:"<<comp_id<<std::endl;

    *h_on->Pin=1;
}

void hal_functions::exit(){
    std::cout<<"hal exit."<<std::endl;
    hal_exit(comp_id);
}

void hal_functions::update(){
   // std::cout<<"hal update"<<std::endl;

   // std::cout<<"test component state:"<<*h_motion_finished->Pin<<std::endl;

}

void hal_functions::run(int state){
    if(state){
        *h_run->Pin=1;
    } else {
        *h_run->Pin=0;
    }
}

void hal_functions::pause(int state){
    if(state){
        *h_pause->Pin=1;
    } else {
        *h_pause->Pin=0;
    }
}






















