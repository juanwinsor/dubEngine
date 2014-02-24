#include "Camera2D.h"


Camera2D::Camera2D(int screenWidth, int screenHeight)
{
	//-- initialize projection to orthographic
	m_Projection = glm::ortho(0, screenWidth, 0, screenHeight);

	//-- initialize transform to identity plus z offset
	m_Transform = glm::mat4();
	m_Transform = glm::translate(m_Transform, glm::vec3(0, 0, -1.0f));

}
