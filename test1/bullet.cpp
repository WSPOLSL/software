#include "bullet.h"
#include <iostream>
#define lift_side 5
#define right_side 795
#define up_side 5
#define down_side 595
#define t 0.0005
#define bullet_r 5
/*void bullet::Put_Bullet(int x, int y, int vx, int vy){
bullet bullet;
CircleShape bullet_shape(5);
bullet_shape.setFillColor(Color::Green);
bullet.x = x;
bullet.y = y;
bullet.vx = vx;
bullet.vy = vy;
bullet_shape.setPosition(x, y);

}*/

void Bullet::horizontal_collide(){
	horizontal_collision = true;
}
void Bullet::vertical_collide(){
	vertical_collsion = true;
}
void Bullet::reset_collision(){
	horizontal_collision = false;
	vertical_collsion = false;
}

void Bullet::update(sf::Time elapsed)
{
	//  float elapsed_time = elapsed.asSeconds();
	//update position

	//stay in window
	float elapsed_time = elapsed.asSeconds();
	//printf("%f\n", elapsed_time);
	dx = bullet_v.x*elapsed_time;
	dy = bullet_v.y*elapsed_time;
	//printf("%f     %f\n", dx, dy);
	current_position = this->getPosition();
	sf::Vector2f next_position;
	next_position.x = current_position.x + dx;
	next_position.y = current_position.y + dy;
	if (next_position.x <= lift_side || next_position.x >= right_side){
		bullet_v.x = -bullet_v.x;
		dx = -dx;
	}
	if (next_position.y >= down_side || next_position.y <= up_side){
		bullet_v.y = -bullet_v.y;
		dy = -dy;
	}


	if (horizontal_collision)
	{
		bullet_v.y = -bullet_v.y;
	}
	if (vertical_collsion)
	{
		bullet_v.x = -bullet_v.x;
	}

	//collsion_check(image);
	
	this->move(dx, dy);





}


void Bullet::collsion_check(sf::Image image){

	float r = this->getRadius();

	sf::Vector2f p = this->getPosition();
	/*
	// ��

	up_point.x=p.x;
	up_point.y=p.y-r;

	//��

	down_point.x=p.x;
	down_point.y=p.y+r;
	//��

	left_point.x=p.x-r;
	left_point.y=p.y;



	//��
	right_point.x=p.x+r;
	right_point.y=p.y;
	*/

	if (image.getPixel(p.x, p.y).toInteger() == 4278190335) {
		if (dy>0) {
			dy = -dy;
		}
	}

	if (image.getPixel(p.x, p.y).toInteger() == 4261413119) {
		if (dy<0) {
			dy = -dy;
		}

	}

	if (image.getPixel(p.x, p.y).toInteger() == 4244635903) {
		if (dx<0) {
			dx = -dx;
		}

	}

	if (image.getPixel(p.x, p.y).toInteger() == 4227858687) {
		if (dx>0) {
			dx = -dx;
		}

	}


}

void Bullet::bullet_collision_check(Bullet *bullet){
	sf::Vector2f this_position = this->getPosition();
	sf::Vector2f other_position = bullet->getPosition();
	sf::Vector2f position_vector;
	position_vector.x = this_position.x - other_position.x;
	position_vector.y = this_position.y - other_position.y;
	float distance;
	distance = (sqrt(pow(position_vector.x, 2) + pow(position_vector.y, 2)));
	if (distance < bullet_r){
		this->is_exist = false;
		bullet->is_exist = false;
	}

}


void Bullet::Draw_Bullet(sf::RenderWindow &window){
	//    Get_Next_Position();
	//   this->setPosition(x, y);

}
void Bullet::Run_Bullet(){
	CircleShape bullet_shape;
	bullet_shape.setRadius(5);
	bullet_shape.setFillColor(sf::Color::Green);
	sf::RenderWindow window(sf::VideoMode(800, 600), "bullet!");
	sf::Clock clock;
	sf::Time run_time = sf::seconds(t);
	while (window.isOpen())
	{
		if (clock.getElapsedTime() >= run_time){
			//           bullet_shape.setPosition(x, y);
			window.clear();
			window.draw(bullet_shape);
			window.display();
			//bullet.Get_Next_Position(bullet.x, bullet.y, bullet.vx, bullet.vy);
			//	printf("%d,%d,%d,%d,%f\n", bullet.x, bullet.y, bullet.vx, bullet.vy, t);
			clock.restart();
		}

	}
}