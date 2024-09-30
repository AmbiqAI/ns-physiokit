/**
 * @file pk_imu.h
 * @author Adam Page (adam.page@ambiq.com)
 * @brief PhysioKit: IMU
 * @version 1.0
 * @date 2023-12-13
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef __PK_IMU_H
#define __PK_IMU_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "arm_math.h"

/**
 * @brief Compute ENMO from accelerometer data
 *
 * @param x X-axis accelerometer data
 * @param y Y-axis accelerometer data
 * @param z Z-axis accelerometer data
 * @param enmo Output ENMO data
 * @param blockSize Number of samples
 * @return uint32_t
 */
uint32_t
pk_imu_compute_enmo_f32(float32_t *x, float32_t *y, float32_t *z, float32_t *enmo, uint32_t blockSize);

/**
 * @brief Compute tilt angles from accelerometer data
 *
 * @param x X-axis accelerometer data
 * @param y Y-axis accelerometer data
 * @param z Z-axis accelerometer data
 * @param xAngle Output X-axis tilt angle
 * @param yAngle Output Y-axis tilt angle
 * @param zAngle Output Z-axis tilt angle
 * @param blockSize Number of samples
 * @return uint32_t
 */
uint32_t
pk_imu_compute_tilt_angles_f32(float32_t *x, float32_t *y, float32_t *z, float32_t *xAngle, float32_t* yAngle, float32_t *zAngle, uint32_t blockSize);

/**
 * @brief Compute pitch, and roll from accelerometer data
 *
 * @param x X-axis accelerometer data
 * @param y Y-axis accelerometer data
 * @param z Z-axis accelerometer data
 * @param pitch Output pitch angle
 * @param roll Output roll angle
 * @param blockSize Number of samples
 * @return uint32_t
 */
uint32_t
pk_imu_compute_pitch_roll_f32(float32_t *x, float32_t *y, float32_t *z, float32_t *pitch, float32_t *roll, uint32_t blockSize);

#ifdef __cplusplus
}
#endif

#endif // __PK_IMU_H
