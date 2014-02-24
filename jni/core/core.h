#ifndef __CORE_H
#define __CORE_H

class DeviceInfo;
class Game;


struct GameTime
{
	GameTime()
	{
		deltaTime = 0;
		totalTime = 0;
		fixedStep = 1.0f / 60.0f;
	}

	float deltaTime;
	float totalTime;
	float fixedStep;
};

class core
{
public:
	~core();

	void initialize(DeviceInfo* deviceInfo);
	void update(GameTime* gameTime);
	void fixedUpdate(GameTime* gameTime);
	void preDraw();
	void draw();
protected:

	DeviceInfo* m_DeviceInfo;
	Game* m_Game;

};




#endif
