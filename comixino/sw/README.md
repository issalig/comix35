# COMIXINO - COMX File Player/Recorder

## Overview

COMIXINO is an Arduino-based project that plays and records COMX files using High Speed Direct Connection (HDSC). It's designed to work with the COMX-35 computer system, allowing you to transfer programs and data between a modern SD card storage and the vintage computer.

## Hardware Requirements

- **Arduino Nano** (tested platform)
- **SD Card Module** with SPI interface
- **OLED Display** (128x64, SSD1306) - optional but recommended
- **Push Buttons** (7 total):
  - UP/DOWN: File navigation
  - PLAY: Start playback or pause
  - STOP: Stop playback/recording or go to root (short press) / Settings (long press)
  - ROOT: Return to SD card root directory
  - RECORD: Start recording mode
  - RESET: Resets COMX-35 when the jumper is installed
- **SD Card** formatted with FAT32 (**Max size 8Gb**)

## Pin Connections

```
Arduino Nano Pin Assignments:
- Pin 2:  BTN_PLAY (Play/Pause button)
- Pin 3:  BTN_UP (Navigate up in file list)
- Pin 4:  BTN_DOWN (Navigate down in file list)
- Pin 5:  BTN_ROOT (Return to root directory)
- Pin 6:  BTN_STOP (Stop/Settings button)
- Pin 7:  BTN_RECORD (Record button)
- Pin 10: SD_CS (SD card chip select)
- Pin 8:  SW_RX (Software serial RX - optional)
- Pin 9:  SW_TX (Software serial TX - optional)
- A4/A5: I2C for OLED display (SDA/SCL)
```

## Features

### File Management
- Browse files and directories on SD card
- Support for long filenames with scrolling display
- Directory navigation with visual indicators (`>` prefix for directories)
- File size display
- COMX file type detection and display

### COMX File Support
The system supports multiple COMX file formats:
- **Format 1**: Machine code programs
- **Format 2**: Old BASIC programs
- **Format 3**: F&M BASIC programs
- **Format 4**: Old data format (legacy)
- **Format 5**: Data files
- **Format 6**: BASIC programs (standard)

### Playback Features
- Serial transmission of COMX files to target computer
- Progress indication during playback
- Pause/resume functionality
- Buffer management for reliable transmission

### Recording Features
- Record incoming data from COMX computer
- Automatic filename generation (`cmx000.comx`, `cmx001.comx`, etc.)
- Timeout-based recording stop
- Data validation (first byte format checking)
- Manual stop capability

### User Interface
- OLED display showing:
  - File information (name, size, type)
  - Current operation status
  - Progress indicators
  - Error messages
- Button-based navigation and control
- Text scrolling for long filenames
- Settings mode access

## Operation Guide

### Basic Navigation
1. **Power on** - Device shows splash screen then "Ready"
2. **UP/DOWN buttons** - Navigate through files and directories
3. **PLAY button** - Enter directories or play COMX files
4. **ROOT button** - Return to SD card root directory

### Playing Files
1. Navigate to desired COMX file using UP/DOWN buttons
2. Press PLAY button to start transmission
3. Display shows progress percentage
4. Press PLAY again to pause/resume
5. Press STOP to terminate playback

### Recording Files
1. Press RECORD button to start recording mode
2. Device waits for incoming data (5-second timeout)
3. Automatically saves as `cmxXXX.comx` format
4. Recording stops on timeout (1.5s) or STOP button
5. Display shows bytes written count

### Settings Mode
1. **Long press STOP button** (>1.5 seconds) when not playing/recording
2. Settings menu appears with options:
   - PLAY: Output sample COMX program
   - STOP: Exit settings
3. Auto-timeout after 10 seconds of inactivity

## Technical Details

### Serial Communication
- Default baud rate: 9600 bps
- Optional software serial support for additional flexibility
- Hardware serial used for primary communication
- Buffer size: 32 bytes for playback, 256 bytes for recording

### Memory Management
- Program memory usage optimized for Arduino Nano
- PROGMEM used for constants and graphics
- Dynamic buffer allocation for file operations
- Warning: >80% memory usage may cause OLED library issues

### File System
- FAT32 SD card support via SdFat library **Use cards <= 8GB**
- 8.3 and long filename support
- Directory depth navigation
- File size up to 4GB theoretical limit

### Error Handling
- SD card detection and recovery
- File open/read error reporting
- Buffer overflow protection
- Invalid file format handling

## Sample Program

The device includes a built-in sample COMX BASIC program that outputs "COMIXINO" when transmitted. This is useful for testing communication with the target computer.

## Dependencies

Required Arduino libraries:
- **SdFat** version 1.1.4 - SD card file system
- **U8glib** version 1.19.1 - OLED display driver
- **SoftwareSerial** version 1.0 - Optional software serial

## Build Information

- Version: 1.0.0
- Target: Arduino Nano
- Memory requirements: <80% recommended
- I recommend to use PlatformIO. However it is possible to compile it under Arduino IDE.

## Troubleshooting

### Common Issues
1. **"No SD" message**: Check SD card insertion and formatting
2. **File won't play**: Ensure file is valid COMX format
3. **Recording issues**: Check serial connections and baud rate
4. **Display problems**: Verify I2C connections and power
5. **Recording**: Some bytes could be missed (not sure why)

### Memory Warnings
- **Keep program memory usage below 80%**
- Large file operations may require memory optimization
- OLED library is memory-intensive

## HDSC Protocol

COMIXINO implements the High Speed Direct Connection protocol used by COMX-35 computers. The Q output pin is used for data transmission, and /EF4 input is used for flow control (see HDSC project documentation for details).

## License and Acknowledgments

- Based on TZXDuino and HDSC projects. 
- Created by issalig, original date: 10/06/2005.
