/**
 * @file pk_ecg.h
 * @author Adam Page (adam.page@ambiq.com)
 * @brief PhysioKit: ECG
 * @version 1.0
 * @date 2023-12-13
 *
 * @copyright Copyright (c) 2023
 *
 */
#ifndef __PK_ECG_H
#define __PK_ECG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "arm_math.h"

typedef struct
{
    float32_t qrsWin; // QRS window length in secs (0.1)
    float32_t avgWin; // Average window length in secs (1.0)
    float32_t qrsPromWeight; // QRS prominent weight (1.5)
    float32_t qrsMinLenWeight; // QRS minimum length in secs (0.4)
    float32_t qrsDelayWin; // Minimum delay between successive QRS peaks in secs (0.3)
    uint32_t sampleRate; // Sample rate in Hz
    float32_t *state; // Interal state requires 4*ecgLen
} ecg_peak_f32_t;


/**
 * @brief Filter out RR intervals that are outside of the min and max range
 *
 * @param rrIntervals Array of RR intervals
 * @param numPeaks Number of peaks
 * @param mask Filter mask (1 = outside of range, 0 = inside of range)
 * @param sampleRate Sample rate in Hz
 * @param minRR Minimum RR interval in seconds
 * @param maxRR Maximum RR interval in seconds
 * @return uint32_t
 */
uint32_t
pk_ecg_square_filter_mask(uint32_t *rrIntervals, uint32_t numPeaks, uint8_t *mask, uint32_t sampleRate, float32_t minRR, float32_t maxRR);

/**
 * @brief Find r peaks in ECG signal
 *
 * @param ctx Context
 * @param ecg ECG signal
 * @param ecgLen Length of ECG signal
 * @param peaks Array of peak indices
 * @param mask Segmentation mask (QRS region)
 * @return uint32_t
 */
uint32_t
pk_ecg_find_peaks_f32(ecg_peak_f32_t *ctx, float32_t *ecg, uint32_t ecgLen, uint32_t *peaks, uint16_t *mask);

/**
 * @brief Compute RR intervals from peak indices
 *
 * @param peaks Array of peak indices
 * @param numPeaks Number of peaks
 * @param rrIntervals Array of RR intervals
 * @return uint32_t Result code
 */
uint32_t
pk_ecg_compute_rr_intervals(uint32_t *peaks, uint32_t numPeaks, uint32_t *rrIntervals);

/**
 * @brief Filter RR intervals using square filter and quotient filter
 *
 * @param rrIntervals Array of RR intervals
 * @param numPeaks Number of peaks
 * @param mask Filter mask
 * @param sampleRate Sample rate in Hz
 * @param minRR Minimum RR interval in seconds
 * @param maxRR Maximum RR interval in seconds
 * @param minDelta Minimum quotient delta
 * @return uint32_t
 */
uint32_t
pk_ecg_filter_rr_intervals(uint32_t *rrIntervals, uint32_t numPeaks, uint8_t *mask, uint32_t sampleRate, float32_t minRR, float32_t maxRR, float32_t minDelta);

/**
 * @brief Compute heart rate from RR intervals
 *
 * @param rrIntervals Array of RR intervals
 * @param mask Filter mask
 * @param numPeaks Number of peaks
 * @param sampleRate Sample rate in Hz
 * @return float32_t Heart rate in BPM
 */
float32_t
pk_ecg_compute_heart_rate_from_rr_intervals(uint32_t *rrIntervals, uint32_t *mask, uint32_t numPeaks, uint32_t sampleRate);

/**
 * @brief Derive respiratory rate from ECG signal
 *
 * @param peaks Array of peak indices
 * @param rrIntervals Array of RR intervals
 * @param numPeaks Number of peaks
 * @param sampleRate Sample rate in Hz
 * @param respRate Respiratory rate in BPM
 * @return uint32_t Result code
 */
uint32_t
pk_ecg_derive_respiratory_rate(uint32_t *peaks, uint32_t *rrIntervals, uint32_t numPeaks, uint32_t sampleRate, float32_t *respRate);

#ifdef __cplusplus
}
#endif

#endif // __PK_ECG_H
