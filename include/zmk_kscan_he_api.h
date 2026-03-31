/*
 * SPDX-License-Identifier: MIT
 *
 * Public API for the HE kscan driver.
 * Provides runtime access to per-key thresholds, ADC/calibration data,
 * and NVS persistence via Zephyr settings subsystem.
 */

#pragma once

#include <zephyr/device.h>
#include <stdint.h>

#include "he_key_state.h"

/**
 * Internal vtable used by the driver to register per-instance operations.
 * External consumers should use the zmk_kscan_he_* functions below.
 */
struct he_kscan_api_vtable {
    uint8_t  num_keys;
    uint8_t  default_press;
    uint8_t  default_release;
    uint8_t  *press_thresholds;
    uint8_t  *release_thresholds;
    struct he_key_state *keys;
    int (*save_settings)(const struct device *dev);
    int (*reset_defaults)(const struct device *dev);
    int (*recalibrate)(const struct device *dev);
};

/**
 * Register the HE kscan device for use with the public API.
 * Called internally by the driver during init.
 */
void zmk_kscan_he_register_device(const struct device *dev,
                                   struct he_kscan_api_vtable *vtable);

/**
 * Get per-key thresholds.
 * @param dev       HE kscan device
 * @param key_idx   0-based local key index
 * @param press_out pointer to receive press threshold
 * @param release_out pointer to receive release threshold
 * @return 0 on success, -EINVAL if arguments are invalid
 */
int zmk_kscan_he_get_threshold(const struct device *dev, uint8_t key_idx,
                                uint8_t *press_out, uint8_t *release_out);

/**
 * Set per-key thresholds at runtime.
 * press must be > release (e.g., press=60, release=30).
 * @return 0 on success, -EINVAL if arguments are invalid
 */
int zmk_kscan_he_set_threshold(const struct device *dev, uint8_t key_idx,
                                uint8_t press, uint8_t release);

/** Get current ADC filtered value and distance for a key */
int zmk_kscan_he_get_adc_raw(const struct device *dev, uint8_t key_idx,
                              uint16_t *adc_out, uint8_t *distance_out);

/** Get calibration baseline values (rest and bottom-out ADC) */
int zmk_kscan_he_get_calibration(const struct device *dev, uint8_t key_idx,
                                  uint16_t *rest_out, uint16_t *bottom_out);

/** Get number of keys managed by this device */
int zmk_kscan_he_get_num_keys(const struct device *dev, uint8_t *num_keys_out);

/** Persist current thresholds to NVS (Zephyr settings) */
int zmk_kscan_he_save_settings(const struct device *dev);

/** Reset all thresholds to devicetree defaults and persist */
int zmk_kscan_he_reset_defaults(const struct device *dev);

/**
 * Re-run calibration (blocking ~500ms).
 * IMPORTANT: Caller must ensure scan is stopped (disable_callback) before
 * calling, and re-enable after. Keys must be fully released during calibration.
 */
int zmk_kscan_he_recalibrate(const struct device *dev);
