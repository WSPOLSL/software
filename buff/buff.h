#pragma once
#include <SFML/Graphics.hpp>
#include"tank.h"
#define BUFF_HEIGHT 50
#define BUFF_WIDTH 50
//using namespace std
class Buff : public sf::RectangleShape
{
public:
	Buff(int type);
	int tank_buff_collision(Tank *tank);
	void buff_collision_handle_one();

private:
	
	sf::Texture buff_texture;
	bool is_exist = 0;
public:
	int type = 0;
};