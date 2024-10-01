/**
 * @file pk_sort.c
 * @author Adam Page (adam.page@ambiq.com)
 * @brief PhysioKit: Sort
 * @version 0.1
 * @date 2024-10-01
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "arm_math.h"
#include "pk_sort.h"

size_t
pk_binary_search_f32(float32_t *x, size_t xLen, float32_t xNew)
{
    // Binary search for the index of the x value that is closest to the new x value.
    // Return the index of the x value that is closest to the new x value.
    size_t low = 0;
    size_t high = xLen - 1;
    while (low < high)
    {
        size_t mid = low + (high - low) / 2;
        if (x[mid] < xNew)
        {
            low = mid + 1;
        }
        else
        {
            high = mid;
        }
    }
    return low;
}
