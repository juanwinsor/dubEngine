#ifndef __GAME_H
#define __GAME_H

class GameTime;

class Game
{
public:
	void initialize();
	void update(GameTime* gameTime);
	void draw();
	void unload();
protected:

};

#endif
