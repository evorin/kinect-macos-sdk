#ifndef KINECT_INTERFACE_H
#define KINECT_INTERFACE_H

#include <libfreenect/libfreenect.h>
#include <pthread.h>
#include <stdint.h>
#include <stdbool.h>
#include "algorithm_interface.h"

/**
 * @class KinectInterface
 * @brief Main interface for interacting with the Kinect sensor on macOS
 * 
 * This class provides a high-level interface for initializing the Kinect,
 * capturing depth and RGB data, and processing that data through custom algorithms.
 */
class KinectInterface {
private:
    freenect_context* f_ctx;
    freenect_device* f_dev;
    pthread_t freenect_thread;
    volatile bool die;
    
    // Data buffers
    uint16_t* depth_buffer;
    uint8_t* rgb_buffer;
    
    // Buffer dimensions
    int depth_width;
    int depth_height;
    int rgb_width;
    int rgb_height;
    
    // Synchronization
    pthread_mutex_t depth_mutex;
    pthread_mutex_t rgb_mutex;
    
    // Custom algorithm
    AlgorithmInterface* algorithm;
    
    // Thread function
    static void* freenect_threadfunc(void* arg);
    
    // Callbacks
    static void depth_callback(freenect_device* dev, void* v_depth, uint32_t timestamp);
    static void rgb_callback(freenect_device* dev, void* v_rgb, uint32_t timestamp);
    
public:
    /**
     * @brief Constructor
     */
    KinectInterface();
    
    /**
     * @brief Destructor - ensures proper cleanup
     */
    ~KinectInterface();
    
    /**
     * @brief Initialize the Kinect device
     * @return true if initialization successful, false otherwise
     */
    bool initialize();
    
    /**
     * @brief Start capturing data from Kinect
     * @return true if capture started successfully, false otherwise
     */
    bool startCapture();
    
    /**
     * @brief Stop capturing data from Kinect
     */
    void stopCapture();
    
    /**
     * @brief Shutdown and cleanup Kinect device
     */
    void shutdown();
    
    /**
     * @brief Set a custom algorithm for data processing
     * @param algo Pointer to an AlgorithmInterface implementation
     */
    void setAlgorithm(AlgorithmInterface* algo);
    
    /**
     * @brief Get the latest depth data
     * @return Pointer to depth buffer (16-bit values)
     */
    const uint16_t* getDepthData();
    
    /**
     * @brief Get the latest RGB data
     * @return Pointer to RGB buffer (24-bit RGB values)
     */
    const uint8_t* getRGBData();
    
    /**
     * @brief Get depth frame dimensions
     * @param width Output parameter for width
     * @param height Output parameter for height
     */
    void getDepthDimensions(int& width, int& height);
    
    /**
     * @brief Get RGB frame dimensions
     * @param width Output parameter for width
     * @param height Output parameter for height
     */
    void getRGBDimensions(int& width, int& height);
    
    /**
     * @brief Check if Kinect is initialized
     * @return true if initialized, false otherwise
     */
    bool isInitialized() const;
    
    /**
     * @brief Set LED color
     * @param color LED color option
     */
    void setLED(freenect_led_options color);
    
    /**
     * @brief Set tilt angle of Kinect
     * @param angle Angle in degrees (-30 to 30)
     * @return true if successful, false otherwise
     */
    bool setTiltAngle(double angle);
};

#endif // KINECT_INTERFACE_H
