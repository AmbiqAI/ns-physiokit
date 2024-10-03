/**
 * @file pk_interpolation.h
 * @author Adam Page (adam.page@ambiq.com)
 * @brief PhysioKit: Interpolation
 * @version 1.0
 * @date 2024-10-01
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef __PK_INTERPOLATION_H
#define __PK_INTERPOLATION_H

#ifdef __cplusplus
extern "C" {
#endif

#include "arm_math.h"

void
pk_inter1d_f32(float32_t *x, float32_t *y, uint32_t xLen, float32_t *xNew, float32_t *yNew, uint32_t xNewLen);

#ifdef __cplusplus
}
#endif

#endif // __PK_INTERPOLATION_H
