/**
 * @file pk_math.h
 * @author Adam Page (adam.page@ambiq.com)
 * @brief PhysioKit: Math
 * @version 1.0
 * @date 2023-12-13
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef __PK_MATH_H
#define __PK_MATH_H

#ifdef __cplusplus
extern "C" {
#endif

#include "arm_math.h"

/**
 * @brief Mean of a signal
 *
 * @param pSrc Source signal
 * @param pResult Result of mean
 * @param blockSize Block size
 * @return uint32_t result code
 */
uint32_t
pk_mean_f32(float32_t *pSrc, float32_t *pResult, uint32_t blockSize);

/**
 * @brief Standard deviation of a signal
 *
 * @param pSrc Source signal
 * @param pResult Result of standard deviation
 * @param blockSize Block size
 * @return uint32_t Result code
 */
uint32_t
pk_std_f32(float32_t *pSrc, float32_t *pResult, uint32_t blockSize);

/**
 * @brief Compute gradient of a signal
 *
 * @param pSrc Source signal
 * @param pResult Result of gradient
 * @param blockSize Block size
 * @return uint32_t Result code
 */
uint32_t
pk_gradient_f32(float32_t *pSrc, float32_t *pResult, uint32_t blockSize);

/**
 * @brief Compute root mean square of a signal
 *
 * @param pSrc Source signal
 * @param pResult Result of root mean square
 * @param blockSize Block size
 * @return uint32_t Result code
 */
uint32_t
pk_rms_f32(float32_t *pSrc, float32_t *pResult, uint32_t blockSize);

/**
 * @brief Compute next power of 2
 *
 * @param val Value to compute next power of 2
 * @return uint32_t
 */
uint32_t
pk_next_power_of_2(uint32_t val);

/**
 * @brief Compute cosine similarity
 *
 * @param ref Reference signal
 * @param sig Signal to compare
 * @param len Length of signals
 * @param result Result of comparison
 * @return uint32_t
 */
uint32_t
cosine_similarity_f32(float32_t *ref, float32_t *sig, size_t len, float32_t *result);

#ifdef __cplusplus
}
#endif

#endif // __PK_MATH_H
