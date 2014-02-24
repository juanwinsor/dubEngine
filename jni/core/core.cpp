
#include "hardware/DeviceInfo.h"
#include "../game/Game.h"
#include "graphics/Renderer.h"
#include "core.h"


core::~core()
{
	delete m_Game;
}


void core::initialize(DeviceInfo* deviceInfo)
{
	m_DeviceInfo = deviceInfo;

	//-- initialize the renderer
	Renderer2D::instance()->initialize(m_DeviceInfo);

	//-- initialize game
	m_Game = new Game();
	m_Game->initialize();
}

void core::update(GameTime* gameTime)
{
	//-- game update
	m_Game->update(gameTime);




}

void core::fixedUpdate(GameTime* gameTime)
{

}

void core::preDraw()
{
	//-- clear the buffer
	Renderer2D::instance()->clear();
}

void core::draw()
{
	//-- draw renderables
	Renderer2D::instance()->draw();

	//-- game draw
	m_Game->draw();
}
