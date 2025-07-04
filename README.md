# Vibetastic - Single Key Keyboard

[![Vibetastic Demo](https://img.youtube.com/vi/SV0bM1FkdLY/maxresdefault.jpg)](https://youtu.be/SV0bM1FkdLY)

*Click the image above to watch the demo video*

## Overview

A very silly but functional single-key keyboard - perfect for vibe coding! This project combines interesting hardware design choices with AI-assisted firmware development.

## Key Features

- **Dual Power Management**: Uses TPS2117 for clean switching between battery and USB power with controlled slew rate
- **Versatile Switch Compatibility**: Custom PCB footprint supports both low-profile and full-height Cherry MX switches
- **Stabilizer Support**: Full-height keycaps can use stabilizers for improved feel and reduced wobble
- **AI-Coded Firmware**: The entire codebase was developed through AI collaboration without manual code review

## Hardware Highlights

The PCB incorporates several thoughtful design decisions:
- TPS2117 power switch controller enables high capacitance loads without violating USB specifications
- Hybrid Cherry MX footprint accommodates both switch types (though stabilizers only work with full-height switches)
- Clean power management replaces traditional MOSFET/diode circuits

## Project Structure

- `/firmware/` - PlatformIO-based embedded firmware
- `/hardware/` - KiCad PCB design files and component libraries
