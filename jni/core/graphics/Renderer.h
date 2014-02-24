#ifndef _RENDERER2D_H
#define _RENDERER2D_H

//#include "Shader.h"

class DeviceInfo;

class Renderer2D
{
public:


	static Renderer2D* instance();

	void addRenderable();
	void removeRenderable();

	void initialize(DeviceInfo* deviceInfo);
	void draw();
	void clear();
	void setClearColor(float r, float g, float b, float a);
	void uninitialize();

protected:
	Renderer2D();
	~Renderer2D(){}

	static Renderer2D* m_Instance;

	DeviceInfo* m_DeviceInfo;

	glm::mat4 m_CamerMatrix;

	//vec4 m_WindowRect;
	//vec4 m_ClearColor;

	//Shader* m_SpriteShader;
};

#endif
