#pragma once
#ifndef game_hpp
#define game_hpp

#include <SFML/Graphics.hpp>
#include <stdio.h>
#include "bullet.h"
#include "tank.h"
#include "shield.h"
#include <stdlib.h>
#include"buff.h"

#define WIDTH 800
#define HEIGHT 600

class Game {
public:
	Game();
private:
	Bullet *bullets[10];
	Tank *tanks[5];
	Buff *buffs[2];

public:
	void is_exit(sf::Event &event, sf::RenderWindow &window);
	void Draw_Tank(Tank &tank, sf::Time elapsed, sf::RenderWindow &window);
	void init_array(Bullet **bullets, Tank **tanks,Buff **buffs);

	//////////////////////////////////////////////////////////////////////¡ıÀ…¡÷ÃÌº”
	void buff_clear_allbullets(Bullet **bullets);
	//////////////////////////////////////////////////////////////
};




#endif /* game_hpp */
