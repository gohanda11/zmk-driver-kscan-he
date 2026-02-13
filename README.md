# ZMK Hall Effect Kscan Driver Module

This is a [ZMK module](https://zmk.dev/docs/features/modules) providing a custom `kscan` driver for Hall Effect magnetic switches. It supports multiplexing via MUX (e.g., SN74LV4051A) and ADC-based distance sensing with EMA filtering and automatic calibration.

## Features

- **ADC-based sensing**: High-resolution distance measurement for magnetic switches.
- **Multiplexer Support**: Efficiently scan many keys using fewer ADC pins.
- **EMA Filtering**: Smooths out ADC noise for stable readings.
- **Auto-Calibration**: Measures "rest" values on boot to handle environmental magnetic variance.
- **Configurable Thresholds**: Set press/release points individually per board.

## Installation

To use this driver in your ZMK configuration, add this module to your `config/west.yml`:

```yaml
manifest:
  remotes:
    - name: zmkfirmware
      url-base: https://github.com/zmkfirmware
    - name: gohanda11
      url-base: https://github.com/gohanda11
  projects:
    - name: zmk
      remote: zmkfirmware
      revision: main
      import: app/west.yml
    - name: zmk-driver-kscan-he
      remote: gohanda11
      revision: main
  self:
    path: config
```

## Usage

In your shield's `.overlay` or `.dtsi` file, define the `kscan` node as follows:

```dts
/ {
    kscan_he: kscan_he {
        compatible = "zmk,kscan-adc-mux";
        
        /* GPIOs for MUX selection */
        select-gpios = <&xiao_d 0 GPIO_ACTIVE_HIGH>, 
                       <&xiao_d 4 GPIO_ACTIVE_HIGH>, 
                       <&xiao_d 5 GPIO_ACTIVE_HIGH>;
                       
        /* ADC channels (one for each MUX output) */
        io-channels = <&adc 1>, <&adc 4>, <&adc 5>;

        num-keys = <22>;
        scan-period-ms = <1>;
        settle-us = <20>;
        invert-adc;
        press-threshold = <60>;
        release-threshold = <50>;
        calibration-duration-ms = <500>;

        /* Map MUX address/channel to key index */
        mux-map = <
             7   12   21     /* addr0: ADC0, ADC1, ADC2 */
             6   11   18     /* addr1 */
             ...
        >;
    };
};
```

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
