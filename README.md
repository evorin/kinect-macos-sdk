# Kinect macOS SDK

macOS project for Kinect integration with libfreenect SDK and custom algorithm interface

## Overview

This project provides a complete framework for working with Microsoft Kinect on macOS. It includes:
- Integration with libfreenect (open-source Kinect driver)
- Basic project structure for Kinect data processing
- Interface for plugging in custom user algorithms
- Dependency management setup

## Requirements

- macOS 10.15 or later
- Xcode 12.0 or later
- CMake 3.15 or later
- Homebrew (for dependency installation)
- Microsoft Kinect sensor

## Installation

### 1. Install Dependencies

```bash
# Install Homebrew if not already installed
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"

# Install required packages
brew install libfreenect
brew install cmake
brew install pkg-config
```

### 2. Clone Repository

```bash
git clone https://github.com/evorin/kinect-macos-sdk.git
cd kinect-macos-sdk
```

### 3. Build Project

```bash
mkdir build
cd build
cmake ..
make
```

## Project Structure

```
kinect-macos-sdk/
├── src/
│   ├── kinect_interface.h      # Main Kinect interface
│   ├── kinect_interface.cpp    # Kinect implementation
│   ├── algorithm_interface.h   # Custom algorithm interface
│   └── main.cpp                # Application entry point
├── include/
│   └── custom_algorithm.h      # User algorithm template
├── examples/
│   └── example_algorithm.cpp   # Example implementation
├── CMakeLists.txt              # Build configuration
└── README.md                   # This file
```

## Usage

### Basic Kinect Connection

```cpp
#include "kinect_interface.h"

int main() {
    KinectInterface kinect;
    if (kinect.initialize()) {
        kinect.startCapture();
        // Process data...
        kinect.stopCapture();
    }
    return 0;
}
```

### Implementing Custom Algorithm

Create your custom algorithm by implementing the `AlgorithmInterface`:

```cpp
#include "algorithm_interface.h"

class MyCustomAlgorithm : public AlgorithmInterface {
public:
    void processDepthData(const uint16_t* depth, int width, int height) override {
        // Your depth processing logic here
    }
    
    void processRGBData(const uint8_t* rgb, int width, int height) override {
        // Your RGB processing logic here
    }
};
```

## API Reference

### KinectInterface

- `bool initialize()` - Initialize Kinect device
- `void startCapture()` - Begin data capture
- `void stopCapture()` - Stop data capture
- `void setAlgorithm(AlgorithmInterface* algo)` - Attach custom algorithm
- `const uint16_t* getDepthData()` - Get latest depth frame
- `const uint8_t* getRGBData()` - Get latest RGB frame

### AlgorithmInterface

- `virtual void processDepthData(const uint16_t*, int, int)` - Process depth data
- `virtual void processRGBData(const uint8_t*, int, int)` - Process RGB data
- `virtual void onInitialize()` - Called when algorithm is initialized
- `virtual void onShutdown()` - Called before algorithm shutdown

## Features

- ✅ Cross-platform macOS support
- ✅ Real-time depth and RGB data streaming
- ✅ Modular algorithm interface
- ✅ CMake build system
- ✅ Example implementations included
- ✅ Automatic dependency management

## Troubleshooting

### Kinect Not Detected

```bash
# Check if Kinect is recognized
system_profiler SPUSBDataType | grep Kinect

# Try resetting USB device
sudo kextunload -b com.apple.driver.usb.AppleUSBEHCI
sudo kextload -b com.apple.driver.usb.AppleUSBEHCI
```

### Build Errors

Make sure all dependencies are installed:
```bash
brew list libfreenect
brew list cmake
```

## Contributing

Contributions are welcome! Please feel free to submit a Pull Request.

## License

MIT License - see LICENSE file for details

## Resources

- [libfreenect Documentation](https://openkinect.org/wiki/Main_Page)
- [Kinect Hardware Specifications](https://docs.microsoft.com/en-us/previous-versions/windows/kinect/)
- [CMake Documentation](https://cmake.org/documentation/)

## Support

For issues and questions, please use the [GitHub Issues](https://github.com/evorin/kinect-macos-sdk/issues) page.
