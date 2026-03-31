/*
 * SPDX-License-Identifier: MIT
 *
 * Private header for the HE kscan driver.
 * Contains the vtable struct and device registration API used internally
 * by the driver implementation. Not for external consumers.
 */

#pragma once

#include <zephyr/device.h>
#include <stdint.h>

#include "he_key_state.h"

/**
 * Internal vtable used by the driver to register per-instance operations.
 * External consumers should use the zmk_kscan_he_* functions from the
 * public header (zmk_kscan_he_api.h).
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
