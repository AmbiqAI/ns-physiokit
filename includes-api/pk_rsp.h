/**
 * @file pk_rsp.h
 * @author Adam Page (adam.page@ambiq.com)
 * @brief PhysioKit: RSP
 * @version 1.0
 * @date 2023-12-13
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef __PK_RSP_H
#define __PK_RSP_H

#ifdef __cplusplus
extern "C" {
#endif

#include "arm_math.h"

typedef struct
{
    float32_t peakWin; // Peak window length in sec (0.5)
    float32_t breathWin; // Breath window length in sec (2.0)
    float32_t breathOffset; // Breath offset in sec (0.05)
    float32_t peakDelayWin; // Successive breah delay in sec (0.3)
    uint32_t sampleRate; // Sample rate in Hz
    float32_t *state; // Internal state requires 4*rspLen
    uint32_t *peaks; // Array of peak indices
} rsp_peak_f32_t;

/**
 * @brief Find peaks in RSP signal
 *
 * @param ctx RSP context
 * @param rsp RSP signal
 * @param rspLen Length of RSP signal
 * @param peaks Array of peak indices
 * @return uint32_t
 */
uint32_t
pk_rsp_find_peaks_f32(rsp_peak_f32_t* ctx, float32_t *rsp, uint32_t rspLen, uint32_t *peaks);

/**
 * @brief Compute RR intervals from peak indices
 *
 * @param peaks Array of peak indices
 * @param numPeaks Number of peaks
 * @param rrIntervals Array of RR intervals
 * @return uint32_t
 */
uint32_t
pk_rsp_compute_rr_intervals(uint32_t *peaks, uint32_t numPeaks, uint32_t *rrIntervals);

/**
 * @brief Filter out RR intervals that are outside of the min and max range
 *
 * @param rrIntervals Array of RR intervals
 * @param numPeaks Number of peaks
 * @param mask Filter mask (1 = outside of range, 0 = inside of range)
 * @param sampleRate Sample rate in Hz
 * @param minRR Minimum RR interval in seconds
 * @param maxRR Maximum RR interval in seconds
 * @param minDelta Minimum delta between RR intervals
 * @return uint32_t
 */
uint32_t
pk_rsp_filter_rr_intervals(uint32_t *rrIntervals, uint32_t numPeaks, uint8_t *mask, uint32_t sampleRate, float32_t minRR, float32_t maxRR, float32_t minDelta);

/**
 * @brief Compute respiratory rate from RR intervals
 *
 * @param rrIntervals Array of RR intervals
 * @param mask Filter mask (1 = outside of range, 0 = inside of range)
 * @param numPeaks Number of peaks
 * @param sampleRate Sample rate in Hz
 * @return float32_t
 */
float32_t
pk_rsp_compute_respiratory_rate_from_rr_intervals(uint32_t *rrIntervals, uint32_t *mask, uint32_t numPeaks, uint32_t sampleRate);

#ifdef __cplusplus
}
#endif

#endif // __PK_RSP_H
