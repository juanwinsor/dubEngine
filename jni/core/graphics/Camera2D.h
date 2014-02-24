#ifndef __CAMERA2D_H
#define __CAMERA2D_H

class Camera2D
{
public:
	Camera2D(int screenWidth, int screenHeight);

protected:
	glm::mat4 m_Projection;
	glm::mat4 m_Transform;
};

#endif
