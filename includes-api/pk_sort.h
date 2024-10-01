/**
 * @file pk_sort.h
 * @author Adam Page (adam.page@ambiq.com)
 * @brief PhysioKit: Sort
 * @version 0.1
 * @date 2024-10-01
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef __PK_SORT_H
#define __PK_SORT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "arm_math.h"

size_t
pk_binary_search_f32(float32_t *x, size_t xLen, float32_t xNew);

#ifdef __cplusplus
}
#endif
