/*
 * SPDX-License-Identifier: MIT
 *
 * Per-key state and shared constants for the HE20 kscan-adc-mux driver.
 */

#pragma once

#include <stdint.h>
#include <stdbool.h>

/* EMA filter exponent: alpha = 1 / 2^EMA_ALPHA_EXP
 * Higher = smoother but slower response. 3 → alpha = 0.125 */
#define EMA_ALPHA_EXP 3

/* Minimum ADC change required to update calibration values.
 * Prevents noise from drifting rest/bottom-out values.
 * Increased from 5 to 20 to prevent false bottom updates from noise. */
#define CALIBRATION_EPSILON 20

/* Maximum ADC raw value for 12-bit SAADC */
#define ADC_MAX_VALUE 4095

/* Distance LUT entries (maps normalized ADC span → 0-255 distance) */
#define DISTANCE_LUT_SIZE 256

/* Per-key runtime state */
struct he_key_state {
    /* EMA-filtered ADC value */
    uint16_t adc_filtered;
    /* Previous EMA-filtered ADC value (for movement detection) */
    uint16_t adc_prev_filtered;
    /* ADC value when key is fully released (rest position) */
    uint16_t adc_rest;
    /* ADC value at maximum travel (bottom-out), updated during scan */
    uint16_t adc_bottom;
    /* Normalized travel distance 0-255 */
    uint8_t  distance;
    /* Current press state */
    bool     pressed;
};
