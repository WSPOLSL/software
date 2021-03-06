#ifndef bullet_hpp
#define bullet_hpp

#include <SFML/Graphics.hpp>
#include <math.h>
#define PI 3.1415926

#define SPEED 500
#define gun_length 25

class Bullet : public sf::CircleShape {
private:
	float dx, dy;
	sf::Vector2f bullet_v;
	sf::Vector2f current_position;
	sf::Vector2f up_point;
	sf::Vector2f down_point;
	sf::Vector2f right_point;
	sf::Vector2f left_point;


	bool horizontal_collision = false;
	bool vertical_collsion = false;
public:
	bool is_exist = false;

public:

	Bullet(sf::Vector2f position, float angle) {
		this->setRadius(5);
		this->setFillColor(sf::Color::Green);
		sf::Vector2f position_bullet;
		float angle_hudu;
		angle_hudu = angle*PI / 180;
		position_bullet.x = position.x + gun_length * sin(angle_hudu);
		position_bullet.y = position.y - gun_length * cos(angle_hudu);

		this->setPosition(position_bullet);
		bullet_v.x = SPEED*sin(angle_hudu);
		bullet_v.y = -SPEED*cos(angle_hudu);
	}
	void horizontal_collide();
	void vertical_collide();
	void reset_collision();

	void update(sf::Time elapsed);



	void collsion_check(sf::Image image);
	void bullet_collision_check(Bullet *bullet);

	void Draw_Bullet(sf::RenderWindow &window);
	//bullet_shape.setRadius(5);
	//void Get_Next_Position(int x,int y,int vx,int vy,int t);
	void Run_Bullet();
	//void Put_Bullet(int x,int y,int vx,int vy);

	//    void Get_Next_Position();
};

#endif /* bullet_hpp */
