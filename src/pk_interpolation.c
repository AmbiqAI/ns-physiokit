/**
 * @file pk_interpolation.c
 * @author Adam Page (adam.page@ambiq.com)
 * @brief PhysioKit: Interpolation
 * @version 0.1
 * @date 2024-10-01
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "arm_math.h"

#include "pk_sort.h"
#include "pk_interpolation.h"


void
pk_inter1d_f32(float32_t *x, float32_t *y, uint32_t xLen, float32_t *xNew, float32_t *yNew, uint32_t xNewLen)
{
    for (size_t i = 0; i < xNewLen; i++)
    {
        // Find the two known x values using binary search.
        size_t j = pk_binary_search_f32(x, xLen, xNew[i]);

        // Handle edge cases.
        j = (j == 0) ? 1 : (j == xLen) ? xLen - 1 : j;

        // Use these two known x values to interpolate the new y value.
        float32_t slope = (y[j] - y[j - 1]) / (x[j] - x[j - 1]);
        yNew[i] = y[j - 1] + slope * (xNew[i] - x[j - 1]);
    }

}
