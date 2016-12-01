#pragma once

#ifndef shield_hpp
#define shield_hpp


#define SHIELD_A 1
#define SHIELD_B 2
#define SHIELD_C 3
#define SHIELD_Cup 4
#define SHIELD_Cdown 5
#define SHIELD_Cleft 6
#define SHIELD_Cright 7


#include <SFML/Graphics.hpp>
#include "bullet.h"
#include "tank.h"
#include <math.h>

class Shield : public sf::ConvexShape
{
public:
	Shield(unsigned int category);
private:
	int a_position_x = 400;
	int a_position_y = 300;
	int block_counts = 0;
	sf::Vector2f* centre = new sf::Vector2f[20];
	int centre_top = 0;

public:

	int get_centre_top() { return centre_top; }
	//   void add_centre(sf::Vector2f c){centre[centre_top]=c;centre_top++;}
	sf::Vector2f get_Nth_centre(int n) { return centre[n]; }
	void set_block_counts(int block_counts) { this->block_counts = block_counts; }
	int get_block_counts() { return  block_counts; }

public:
	void setshape_A();
	void setshape_B();
	void A_check_collsion_with_bullet(Bullet &bullet);
	void A_check_collsion_with_tank(Tank &tank); //   void setshape_C();
	//   void setshape_Cup();
	//   void setshape_Cdown();
	//   void setshape_Cleft();
	//   void setshape_Cright();


};


#endif /* shield_hpp */

