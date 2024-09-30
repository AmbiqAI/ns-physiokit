/**
 * @file pk_filter.h
 * @author Adam Page (adam.page@ambiq.com)
 * @brief PhysioKit: Filtering
 * @version 1.0
 * @date 2023-12-13
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef __PK_FILTER_H
#define __PK_FILTER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "arm_math.h"

typedef struct
{
    arm_biquad_casd_df1_inst_f32 *inst;
    uint8_t numSecs;
    const float32_t *sos;
    float32_t *state;
} biquad_filt_f32_t;

/**
 * @brief Resample signal by upsampling followed by downsamping
 *
 * @param pSrc Source signal
 * @param pResult Result signal
 * @param blockSize Block size
 * @param upSample Upsample factor
 * @param downSample Downsample factor
 * @return uint32_t
 */
uint32_t
pk_resample_signal_f32(float32_t *pSrc, float32_t *pResult, uint32_t blockSize, uint32_t upSample, uint32_t downSample);

/**
 * @brief Resample categorical signal by upsampling followed by downsamping
 *
 * @param pSrc Source signal
 * @param pResult Result signal
 * @param blockSize Block size
 * @param upSample Upsample factor
 * @param downSample Downsample factor
 * @return uint32_t
 */
uint32_t
pk_resample_categorical_u32(uint32_t *pSrc, uint32_t *pResult, uint32_t blockSize, uint32_t upSample, uint32_t downSample);

/**
 * @brief Basic downsampling using linear interpolation
 *
 * @param pSrc Source signal
 * @param srcSize Source size
 * @param srcFs Source sample rate
 * @param pRst Result signal
 * @param rstSize Result size
 * @param rstFs Result sample rate
 * @return uint32_t
 */
uint32_t
pk_linear_downsample_f32(float32_t *pSrc, uint32_t srcSize, uint32_t srcFs, float32_t *pRst, uint32_t rstSize, uint32_t rstFs);

/**
 * @brief Initialize biqaud filter
 *
 * @param ctx Filter context
 * @return uint32_t
 */
uint32_t
pk_init_biquad_filter_f32(arm_biquad_casd_df1_inst_f32 *ctx);

/**
 * @brief Apply biqaud filter to signal
 *
 * @param ctx Filter context
 * @param pSrc Source signal
 * @param pResult Result signal
 * @param blockSize Length of signal
 * @return uint32_t
 */
uint32_t
pk_apply_biquad_filter_f32(arm_biquad_casd_df1_inst_f32 *ctx, float32_t *pSrc, float32_t *pResult, uint32_t blockSize);

/**
 * @brief Apply biqaud filter to signal forwards and backwards
 *
 * @param ctx Filter context
 * @param pSrc Source signal
 * @param pResult Result signal
 * @param blockSize Length of signal
 * @param state Internal state (blockSize)
 * @return uint32_t Result code
 */
uint32_t
pk_apply_biquad_filtfilt_f32(arm_biquad_casd_df1_inst_f32 *ctx, float32_t *pSrc, float32_t *pResult, uint32_t blockSize, float32_t *state);

/**
 * @brief Apply quotient filter to signal
 *
 * @param data Input signal
 * @param mask Output mask
 * @param dataLen Length of input signal
 * @param iterations Number of iterations
 * @param lowcut Quotient lowcut
 * @param highcut Quotient highcut
 * @return uint32_t Result code
 */
uint32_t
pk_quotient_filter_mask_u32(uint32_t *data, uint8_t *mask, uint32_t dataLen, uint32_t iterations, float32_t lowcut, float32_t highcut);

/**
 * @brief Smooth signal using moving average
 *
 * @param pSrc Source signal
 * @param pResult Result signal
 * @param blockSize Length of signal
 * @param wBuffer Window buffer
 * @param windowSize Window size
 * @return uint32_t Result code
 */
uint32_t
pk_smooth_signal_f32(float32_t *pSrc, float32_t *pResult, uint32_t blockSize, float32_t *wBuffer, uint32_t windowSize);

/**
 * @brief Standardize signal: y = (x - mu) / std.
 * Provides safegaurd against small st devs
 *
 * @param pSrc Source signal
 * @param pResult Result signal
 * @param blockSize Length of signal
 * @param epsilon Epsilon value
 * @return uint32_t Result code
 */
uint32_t
pk_standardize_f32(float32_t *pSrc, float32_t *pResult, uint32_t blockSize, float32_t epsilon);

/**
 * @brief Generate Blackman window coefficients
 *
 * @param window Array of window coefficients
 * @param len Length of window
 * @return uint32_t
 */
uint32_t pk_blackman_window_f32(float32_t *window, size_t len);

/**
 * @brief Compute frequency bins for FFT
 *
 * @param freqBins Array of frequency bins
 * @param sampleRate Sample rate in Hz
 * @param fftLen Length of FFT
 * @return uint32_t Result code
 */
uint32_t pk_compute_frequency_bins(float32_t *freqBins, float32_t sampleRate, size_t fftLen);

#ifdef __cplusplus
}
#endif

#endif // __PK_FILTER_H
