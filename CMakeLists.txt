# SPDX-License-Identifier: MIT

if(CONFIG_ZMK_KSCAN_ADC_MUX)
  zephyr_library_named(kscan_adc_mux)
  zephyr_include_directories(include)
  zephyr_library_sources(src/kscan_adc_mux.c)
endif()
