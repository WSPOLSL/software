#include "buff.h"
#include <stdlib.h>
using namespace std;
#define BUFF_TANK_DISTANCE 50
#define RAND_MAX_X  700
#define RAND_MIN_X 50
#define RAND_MAX_Y  600
#define RAND_MIN_Y 50
#define TYPE_MAX 2
#define TYPE_MIN 1
Buff::Buff(int type) :RectangleShape(sf::Vector2f(BUFF_WIDTH, BUFF_HEIGHT)){
	//int type;
	sf::Vector2f buff_position;
	buff_position.x = (rand() % (RAND_MAX_X - RAND_MIN_X)) + RAND_MIN_X;
	buff_position.y = (rand() % (RAND_MAX_Y - RAND_MIN_Y)) + RAND_MIN_Y;
	//type=(rand() % (TYPE_MAX - TYPE_MIN + 1)) + TYPE_MIN;
	if (type == 1)
	{
		this->buff_texture.loadFromFile("buff1.png");
		this->type = type;
	}
	if (type == 2)
	{
		this->buff_texture.loadFromFile("buff2.png");
		this->type = type;
	}
	this->setPosition(buff_position.x, buff_position.y);
	this->setOrigin(BUFF_WIDTH / 2, BUFF_HEIGHT / 2);
}
int Buff::tank_buff_collision(Tank *tank){
	sf::Vector2f tank_position;
	sf::Vector2f buff_position;
	sf::Vector2f position_distance;
	float distance;
	tank_position = tank->getPosition();
	buff_position = this->getPosition();
	position_distance.x = tank_position.x-buff_position.x;
	position_distance.y = tank_position.y - buff_position.y;
	distance = (sqrt(pow(position_distance.x, 2) + pow(position_distance.y, 2)));
	if (distance < BUFF_TANK_DISTANCE){
		int temp_type=this->type;
		this->type = 0;
		return temp_type;
	}
	return 0;
}
void Buff::buff_collision_handle_one(){

}
