
#include "shield.h"






Shield::Shield(unsigned int category) {
	switch (category) {
	case SHIELD_A:
		//            ConvexShape(6);
		create_map_A();
		break;
	case SHIELD_B:
		//            ConvexShape(8);
		setshape_B();
		break;
		/*
		case SHIELD_Cup:
		setshape_Cup();
		break;
		case SHIELD_Cdown:
		setshape_Cdown();
		break;
		case SHIELD_Cleft:
		setshape_Cleft();
		break;
		case SHIELD_Cright:
		setshape_Cright();
		break;
		*/

	default:
		break;
	}
}

void Shield::check_collsion_with_bullet(Bullet &bullet, float position_x, float position_y) {
	sf::Vector2f centre_A, bullet_position;
	centre_A.x = position_x + 20;
	centre_A.y = position_y + 20;

	bullet_position = bullet.getPosition();

	float x = bullet_position.x - centre_A.x;
	float y = bullet_position.y - centre_A.y;

	if (x<35 && x>-35 && y<35 && y>-35) {
		if (y>x && y>-x) {
			bullet.reverse_dy_up();
		}
		else if (y<x && y<-x) {
			bullet.reverse_dy_down();
		}
		else if (y<x && y>-x) {
			bullet.reverse_dx_right();
		}
		else { bullet.reverse_dx_left(); }
	}
}
void Shield::check_collsion_with_tank(Tank &tank, float position_x, float position_y) {
	sf::Vector2f centre_A, bullet_position, tank_position;
	centre_A.x = position_x + 25;
	centre_A.y = position_y + 25;

	tank_position = tank.getPosition();

	float x = tank_position.x - centre_A.x;
	float y = tank_position.y - centre_A.y;

	if (sqrt(x*x + y*y)<(50 * 1.414)) {

		sf::Vector2f left_up_point, right_down_point, right_up_point, left_down_point;
		float l = sqrt(TANK_WIDTH*TANK_WIDTH + TANK_HEIGHT*TANK_HEIGHT)*0.5;
		sf::Vector2f p = tank.getPosition();
		// ◊Û…œ
		float angle = 3.1416*0.25 - tank.getRotation() TO_RADIAN;

		left_up_point.x = p.x - l*sin(angle);
		left_up_point.y = p.y - l*cos(angle);

		//”“œ¬

		right_down_point.x = p.x + l*sin(angle);
		right_down_point.y = p.y + l*cos(angle);
		//”“…œ
		angle = 3.1415926535*0.25 + tank.getRotation() TO_RADIAN;
		right_up_point.x = p.x + l*sin(angle);
		right_up_point.y = p.y - l*cos(angle);



		//◊Ûœ¬
		left_down_point.x = p.x - l*sin(angle);
		left_down_point.y = p.y + l*cos(angle);


		//«∞√Ê»°10∏ˆµ„
		float k = (right_up_point.y - left_up_point.y) / (right_up_point.x - left_up_point.x);
		float dx = (right_up_point.x - left_up_point.x) / 9;
		//        float x,y;


		for (int i = 0; i<10; i++) {
			x = left_up_point.x + dx*i;
			y = k*(x - left_up_point.x) + left_up_point.y;

			x = x - centre_A.x;
			y = y - centre_A.y;

			if (x<27 && x>-27 && y<27 && y>-27) {
				tank.setPosition(tank.previous_position.x, tank.previous_position.y);
				tank.setRotation(tank.previous_rotation);
				break;
			}

		}



		//∫Û√Ê»°10∏ˆµ„
		k = (right_down_point.y - left_down_point.y) / (right_down_point.x - left_down_point.x);
		dx = (right_down_point.x - left_down_point.x) / 9;
		//        float x,y;


		for (int i = 0; i<10; i++) {
			x = left_down_point.x + dx*i;
			y = k*(x - left_down_point.x) + left_down_point.y;

			x = x - centre_A.x;
			y = y - centre_A.y;

			if (x<27 && x>-27 && y<27 && y>-27) {
				tank.setPosition(tank.previous_position.x, tank.previous_position.y);
				tank.setRotation(tank.previous_rotation);
				break;
			}

		}





	}

}
void Shield::init_shield(){
	//float shield_position_array[17][2] = { { 16, 16 }, { 100, 100 }, { 100, 150 }, { 150, 150 }, { 200, 150 }, { 600, 100 },
	//{ 650, 100 }, { 650, 150 }, { 100, 350 }, { 150, 350 },
	//{ 150, 400 }, { 150, 450 }, { 100, 450 }, { 550, 450 }, { 600, 400 }, { 600, 450 }, { 650, 450 } };
	//float shield_position_array[5][2] = { { 4, 4 }, { 0, 0 }, { 0, 50 }, { 50, 50 }, { 100, 50 } };
	shield_position_array[0][0] = 16;
	shield_position_array[0][1] = 16;

	shield_position_array[1][0] = 100;
	shield_position_array[1][1] = 100;

	shield_position_array[2][0] = 100;
	shield_position_array[2][1] = 150;

	shield_position_array[3][0] = 150;
	shield_position_array[3][1] = 150;

	shield_position_array[4][0] = 200;
	shield_position_array[4][1] = 150;

	shield_position_array[5][0] = 600;
	shield_position_array[5][1] = 100;

	shield_position_array[6][0] = 650;
	shield_position_array[6][1] = 100;

	shield_position_array[7][0] = 650;
	shield_position_array[7][1] = 150;
	//{ 100, 350 }, { 150, 350 },
	shield_position_array[8][0] = 100;
	shield_position_array[8][1] = 350;

	shield_position_array[9][0] = 150;
	shield_position_array[9][1] = 350;
	//{ 150, 400 }, { 150, 450 }, { 100, 450 }, { 550, 450 }, { 600, 400 }, { 600, 450 }, { 650, 450 } };
	shield_position_array[10][0] = 150;
	shield_position_array[10][1] = 400;

	shield_position_array[11][0] = 150;
	shield_position_array[11][1] = 450;

	shield_position_array[12][0] = 100;
	shield_position_array[12][1] = 450;

	shield_position_array[13][0] = 550;
	shield_position_array[13][1] = 450;

	shield_position_array[14][0] = 600;
	shield_position_array[14][1] = 400;

	shield_position_array[15][0] = 600;
	shield_position_array[15][1] = 450;

	shield_position_array[16][0] = 650;
	shield_position_array[16][1] = 450;
};
void Shield::create_map_A(){}

void Shield::setshape_B() {

	//*
	//**
	//*


	//  set_block_counts(get_block_counts()+4);
	/*

	add_centre(sf::Vector2f(200+25,200+25));
	add_centre(sf::Vector2f(200+25,200+75));
	add_centre(sf::Vector2f(200+25,200+125));
	add_centre(sf::Vector2f(200+75,200+75));
	*/

}

