#include <ctime>
#include <jni.h>
#include <android_native_app_glue.h>
#include <android/log.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <EGL/egl.h>
#include <GLES/gl.h>

#include "core/core.h"

#define LOGW(...) ((void)__android_log_print(ANDROID_LOG_WARN, "native-activity", __VA_ARGS__))

DeviceInfo _device;
core* _core = NULL;

//-- timer variables
GameTime _gameTime;
float lastTime = 0;
float timeAccumulator = 0;

void initializeWindow()
{
	const EGLint attribs[] =
	{
		EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
		EGL_BLUE_SIZE, 8,
		EGL_GREEN_SIZE, 8,
		EGL_RED_SIZE, 8,
		EGL_NONE
	};
	EGLint w, h, dummy, format;
	EGLint numConfigs;
	EGLConfig config;
	EGLSurface surface;
	EGLContext context;

	//-- get the display
	EGLDisplay display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
	eglInitialize(display, 0, 0);
	//-- choose config for the display
	eglChooseConfig(display, attribs, &config, 1, &numConfigs);
	//-- get format attributes to pass to the native window
	eglGetConfigAttrib(display, config, EGL_NATIVE_VISUAL_ID, &format);
	//-- set format for the native window
	ANativeWindow_setBuffersGeometry(_device.app->window, 0, 0, format);

	//-- create a surface and context to draw on
	surface = eglCreateWindowSurface(display, config, _device.app->window, NULL);
	context = eglCreateContext(display, config, NULL, NULL);

	//-- get the display dimensions
	eglQuerySurface(display, surface, EGL_WIDTH, &w);
	eglQuerySurface(display, surface, EGL_HEIGHT, &h);


	if (eglMakeCurrent(display, surface, surface, context) == EGL_FALSE) {
		//LOGW("Unable to eglMakeCurrent");
		//return -1;
	}

	_device.Display.display = display;
	_device.Display.context = context;
	_device.Display.surface = surface;
	_device.Display.width = w;
	_device.Display.height = h;
}

void unloadWindow()
{
	if (_device.Display.display != EGL_NO_DISPLAY)
	{
		eglMakeCurrent(_device.Display.display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
		if (_device.Display.context != EGL_NO_CONTEXT) {
			eglDestroyContext(_device.Display.display, _device.Display.context);
		}
		if (_device.Display.surface != EGL_NO_SURFACE) {
			eglDestroySurface(_device.Display.display, _device.Display.surface);
		}
		eglTerminate(_device.Display.display);
	}
	_device.Display.display = EGL_NO_DISPLAY;
	_device.Display.context = EGL_NO_CONTEXT;
	_device.Display.surface = EGL_NO_SURFACE;
}

static void android_handle_cmd(struct android_app* app, int cmd)
{
    switch (cmd)
    {
    case APP_CMD_INIT_WINDOW:
        {
        	//-- create a window to draw on
			initializeWindow();

			//-- initialize the engine
			_core = new core();
			_core->initialize(&_device);
        }
        break;

    case APP_CMD_DESTROY:
        {
        }
        break;

    case APP_CMD_TERM_WINDOW:
        {
        	delete _core;
        	unloadWindow();
        }
        break;

    case APP_CMD_RESUME:
        {
        }
        break;

    case APP_CMD_PAUSE:
        {
        }
        break;
    }
}



void android_main(struct android_app* state)
{
    app_dummy();

    //-- cache the android app
    _device.app = state;

    //-- set app command callback to handle lifecycle messages
    state->onAppCmd = android_handle_cmd;
    //-- set input handler callback
    //state->onInputEvent

    //-- initialize frame time
    timeval tv;
    gettimeofday(&tv, NULL);
    lastTime = (tv.tv_sec * 1000.0f) + (tv.tv_usec / 1000.0f);


    bool running = true;
    while(running)
    {
    	//-- calculate frame time
    	//LOGW("MAIN: CALCULATE TIME");
    	gettimeofday(&tv, NULL);
    	float t = (tv.tv_sec * 1000.0f) + (tv.tv_usec / 1000.0f);
    	float delta = (t - lastTime);
    	lastTime = t;
    	if(delta > 0.25f)
    	{
    		delta = 0.25f;
    	}
    	_gameTime.deltaTime = delta;
    	_gameTime.totalTime += delta;

    	//LOGW("MAIN: PROCESS EVENTS");
    	int events;
    	struct android_poll_source* pSource = NULL;
    	int ident = ALooper_pollAll(0, 0, &events, (void**)&pSource);
		if (ident >= 0)
		{
			if (pSource)
			{
				pSource->process(state, pSource);
			}

			if (state->destroyRequested)
			{
				running = false;
			}
		}

		//-- fixed timestep
		//LOGW("MAIN: CONSUME FIXED TIME STEP");
		timeAccumulator += delta;
		while(timeAccumulator >= _gameTime.fixedStep)
		{
			//-- update physics

			//-- update core on fixed step
			_core->fixedUpdate(&_gameTime);

			//-- decrement the accumulator in discrete chunks
			timeAccumulator -= _gameTime.fixedStep;
		}

		//-- the remainder to interpolate drawing by
		float alpha = timeAccumulator / _gameTime.fixedStep;


		//-- update & draw
		if (_device.Display.display != NULL)
		{
			//-- update the engine
			//LOGW("MAIN: UPDATE");
			_core->update(&_gameTime);

			//-- pre draw
			_core->preDraw();

			//-- draw
			//LOGW("MAIN: DRAW");
			_core->draw();
		}



    }
}



