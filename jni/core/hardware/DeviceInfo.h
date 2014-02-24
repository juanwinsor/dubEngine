#ifndef __DEVICE_INFO_H
#define __DEVICE_INFO_H

#include <android_native_app_glue.h>
#include <EGL/egl.h>
#include <android/sensor.h>

class DisplayInfo
{
public:
	EGLDisplay display;
	EGLSurface surface;
	EGLContext context;
	int32_t width;
	int32_t height;
};

class DeviceInfo
{
public:
	struct android_app* app;

    ASensorManager* sensorManager;
    const ASensor* accelerometerSensor;
    ASensorEventQueue* sensorEventQueue;

    DisplayInfo Display;
};




#endif
