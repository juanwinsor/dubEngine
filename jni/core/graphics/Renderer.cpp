#define LOGW(...) ((void)__android_log_print(ANDROID_LOG_WARN, "native-activity", __VA_ARGS__))

#include <android/log.h>

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#include "core/hardware/DeviceInfo.h"

#include "Renderer.h"

Renderer2D* Renderer2D::m_Instance = NULL;

Renderer2D* Renderer2D::instance()
{
	if(m_Instance == NULL)
	{
		m_Instance = new Renderer2D();
	}

	return m_Instance;
}

Renderer2D::Renderer2D()
: m_DeviceInfo ( NULL )
{
	//m_SpriteShader = NULL;
}

void Renderer2D::initialize(DeviceInfo* deviceInfo)
{
	m_DeviceInfo = deviceInfo;

	//m_SpriteShader = new Shader("Content/Shaders/vs.glsl", "Content/Shaders/fs.glsl");
	//glUniform4f(m_SpriteShader->vsColorHandle(), 1, 1, 1, 1);

	//m_CamerMatrix = glm::ortho(0.0f, 640.0f, 480.0f, 0.0f, -1.0f, 1.0f);
	m_CamerMatrix = glm::ortho<float>(0, 640, 0, 480);

	//-- set initial GL state
	glClearDepthf(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	//-- cornflower blue
	setClearColor(0.39f, 0.584f, 0.929f, 1.0f);

	LOGW("RENDERER INITIALIZE");
}

void Renderer2D::draw()
{
	//-- swap buffer to the screen
	eglSwapBuffers(m_DeviceInfo->Display.display, m_DeviceInfo->Display.surface);
}

void Renderer2D::clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//LOGW("RENDERER CLEAR");

}

void Renderer2D::setClearColor(float r, float g, float b, float a)
{
	//--m_ClearColor = glm::vec4(r, g, b, a);
	//--glClearColor(m_ClearColor.x, m_ClearColor.y, m_ClearColor.z, m_ClearColor.w);

	glClearColor(r, g, b, a);

}

void Renderer2D::uninitialize()
{
}
