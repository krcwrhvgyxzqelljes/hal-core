#ifndef HAL_COMMON_H
#define HAL_COMMON_H

#include "hal.h"


typedef struct {
    hal_float_t *Pin;
} float_data_t;
// float_data_t *hal_usage_example;

//! Pins
typedef struct {
    hal_bit_t *Pin;
} bit_data_t;

typedef struct { //! Int.
    hal_s32_t *Pin;
} s32_data_t;

typedef struct { //! Param int.
    hal_s32_t Pin;
} param_s32_data_t;

typedef struct { //! Uint.
    hal_u32_t *Pin;
} u32_data_t;

typedef struct { //! Param Uint.
    hal_u32_t Pin;
} param_u32_data_t;

typedef struct {
    hal_port_t *Pin;
} port_data_t;

//! Params
typedef struct {
    hal_float_t Pin;
} param_float_data_t;

typedef struct {
    hal_bit_t Pin;
} param_bit_data_t;

#endif // HAL_COMMON_H
