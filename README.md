# (Inofficial) LocalBytes™ LocalDeck Custom ESPHome Configuration

This repository contains custom ESPHome configuration files for the LocalBytes™ LocalDeck device.
The configuration is derived off of the official LocalBytes™ firmware (which can be found here: https://github.com/LocalBytes/localdeck-config/blob/main/packages/localdeck-codegen/esphome-localdeck.yaml) but includes additional features,
enhancements, and optimizations.

## Changelog

### New Features

- Blip animation enhancements
  - Blip is overlaid ontop of the current color of the button instead of replacing it
- Additional configuration entities
  - Blip duration in milliseconds
  - Individual Blip brightness control (independent of overall brightness)

### Bug Fixes

- Blip animations don't overlap each other, preventing animation glitches
- Fix latency issues and missed button events caused by ESPHome state change debouncing, see: https://github.com/LocalBytes/localdeck-config/issues/57

### Removed Components

- Web server component has been removed to free up resources and reduce complexity
- Improv WiFi component has been removed, as I deploy using my own method.

### Other noteworthy Changes

- disabled WiFi power save mode to reduce light flickering, see: https://github.com/esphome/esphome/issues/10335
- added "Last Boot Timestamp" sensor, to be able to insantly update the device when it comes online

# Affiliation Note

The content of this repository is not officially affiliated with or endorsed by LocalBytes™.
The configuration files provided here are community-created custom firmware setups for LocalBytes™ LocalDeck,
which is based on the official configuration, but modified to include additional features and enhancements.
If possible and desirable, these changes and enhancements may be proposed for inclusion in the official LocalBytes™ firmware.

