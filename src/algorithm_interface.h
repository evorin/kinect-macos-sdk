#ifndef ALGORITHM_INTERFACE_H
#define ALGORITHM_INTERFACE_H

#include <stdint.h>

/**
 * @class AlgorithmInterface
 * @brief Abstract interface for custom Kinect data processing algorithms
 * 
 * This interface allows users to plug in their own custom algorithms
 * for processing depth and RGB data from the Kinect sensor.
 * 
 * Users should inherit from this class and implement the virtual methods
 * to define their custom processing logic.
 */
class AlgorithmInterface {
public:
    /**
     * @brief Virtual destructor
     */
    virtual ~AlgorithmInterface() {}
    
    /**
     * @brief Called when the algorithm is first initialized
     * 
     * Use this method to perform any setup or initialization
     * your algorithm requires (e.g., allocating buffers, loading models)
     */
    virtual void onInitialize() {
        // Default implementation - override if needed
    }
    
    /**
     * @brief Called before the algorithm is shut down
     * 
     * Use this method to perform cleanup (e.g., releasing resources)
     */
    virtual void onShutdown() {
        // Default implementation - override if needed
    }
    
    /**
     * @brief Process depth data from Kinect
     * 
     * This method is called whenever new depth data is available
     * 
     * @param depth Pointer to depth buffer (16-bit values, in millimeters)
     * @param width Width of the depth frame
     * @param height Height of the depth frame
     */
    virtual void processDepthData(const uint16_t* depth, int width, int height) = 0;
    
    /**
     * @brief Process RGB data from Kinect
     * 
     * This method is called whenever new RGB data is available
     * 
     * @param rgb Pointer to RGB buffer (24-bit RGB values)
     * @param width Width of the RGB frame
     * @param height Height of the RGB frame
     */
    virtual void processRGBData(const uint8_t* rgb, int width, int height) = 0;
    
    /**
     * @brief Optional: Process synchronized depth and RGB data
     * 
     * Override this method if you need to process depth and RGB data together
     * 
     * @param depth Pointer to depth buffer (16-bit values, in millimeters)
     * @param rgb Pointer to RGB buffer (24-bit RGB values)
     * @param width Width of the frames (assumed same for both)
     * @param height Height of the frames (assumed same for both)
     */
    virtual void processSynchronizedData(
        const uint16_t* depth,
        const uint8_t* rgb,
        int width,
        int height) {
        // Default implementation calls individual processors
        processDepthData(depth, width, height);
        processRGBData(rgb, width, height);
    }
    
    /**
     * @brief Get algorithm name
     * @return Name of the algorithm implementation
     */
    virtual const char* getAlgorithmName() const {
        return "BaseAlgorithm";
    }
    
    /**
     * @brief Get algorithm version
     * @return Version string of the algorithm
     */
    virtual const char* getVersion() const {
        return "1.0.0";
    }
};

#endif // ALGORITHM_INTERFACE_H
