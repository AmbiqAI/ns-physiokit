/**
 * @file pk_ppg.h
 * @author Adam Page (adam.page@ambiq.com)
 * @brief PhysioKit: PPG
 * @version 1.0
 * @date 2023-12-13
 *
 * @copyright Copyright (c) 2023
 *
 */
#ifndef __PK_PPG_H
#define __PK_PPG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "arm_math.h"

typedef struct
{
    float32_t peakWin; // 0.111
    float32_t beatWin; // 0.667
    float32_t beatOffset; // 0.02
    float32_t peakDelayWin; // 0.3
    uint32_t sampleRate;
    // State requires 4*ppgLen
    float32_t *state;
    uint32_t *peaks;
} ppg_peak_f32_t;

/**
 * @brief Find peaks in PPG signal
 *
 * @param ctx PPG context
 * @param ppg PPG signal
 * @param ppgLen Length of PPG signal
 * @param peaks Array of peak indices
 * @return uint32_t
 */
uint32_t
pk_ppg_find_peaks_f32(ppg_peak_f32_t* ctx, float32_t *ppg, uint32_t ppgLen, uint32_t *peaks);

/**
 * @brief Compute RR intervals from peak indices
 *
 * @param peaks Array of peak indices
 * @param numPeaks Number of peaks
 * @param rrIntervals Array of RR intervals
 * @return uint32_t
 */
uint32_t
pk_ppg_compute_rr_intervals(uint32_t *peaks, uint32_t numPeaks, uint32_t *rrIntervals);

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
pk_ppg_filter_rr_intervals(uint32_t *rrIntervals, uint32_t numPeaks, uint8_t *mask, uint32_t sampleRate, float32_t minRR, float32_t maxRR, float32_t minDelta);

/**
 * @brief Compute heart rate from RR intervals
 *
 * @param rrIntervals Array of RR intervals
 * @param mask Filter mask (1 = outside of range, 0 = inside of range)
 * @param numPeaks Number of peaks
 * @param sampleRate Sample rate in Hz
 * @return float32_t
 */
float32_t
pk_ppg_compute_heart_rate_from_rr_intervals(uint32_t *rrIntervals, uint32_t *mask, uint32_t numPeaks, uint32_t sampleRate);

/**
 * @brief Compute SpO2 from perfusion values
 *
 * @param dc1 DC component of PPG1
 * @param ac1 AC component of PPG1
 * @param dc2 DC component of PPG2
 * @param ac2 AC component of PPG2
 * @param coefs Correlation coefficients
 * @return float32_t SpO2 value
 */
float32_t
pk_ppg_compute_spo2_from_perfusion_f32(float32_t dc1, float32_t ac1, float32_t dc2, float32_t ac2, float32_t* coefs);


/**
 * @brief Compute SpO2 from PPG signals
 *
 * @param ppg1 PPG1 signal
 * @param ppg2 PPG2 signal
 * @param ppg1Mean Mean of PPG1 signal
 * @param ppg2Mean Mean of PPG2 signal
 * @param blockSize Length of PPG signals
 * @param coefs Correlation coefficients
 * @param sampleRate Sample rate in Hz
 * @return float32_t SpO2 value
 */
float32_t
pk_ppg_compute_spo2_in_time_f32(float32_t *ppg1, float32_t *ppg2, float32_t ppg1Mean, float32_t ppg2Mean, uint32_t blockSize, float32_t *coefs, float32_t sampleRate);

#ifdef __cplusplus
}
#endif

#endif // __PK_PPG_H
