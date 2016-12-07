#include "game.h"
//LSL
#include <stdlib.h>
#include <SFML/Audio.hpp>
#define TYPE_MAX 2
#define TYPE_MIN 1
#define BUFF_TIME 1000
using namespace std;
//
void Game::is_exit(sf::Event &event, sf::RenderWindow &window)
{
	//≈–∂œ «∑Òµ„°¡
	bool close = (event.type == sf::Event::Closed);
	//≈–∂œ «∑Ò∞¥ESC
	bool escape = (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape);
	if (close || escape)
		window.close();
}
void Game::Draw_Tank(Tank &tank, sf::Time elapsed, sf::RenderWindow &window)
{
	tank.update(elapsed, window);
	window.draw(tank);
	window.draw(tank.gun);
}
void Game::init_array(Bullet **bullets, Tank **tanks,Buff **buffs){
	int i;
	for (i = 0; i < 10; i++){
		bullets[i] = NULL;
	}
	for (i = 0; i < 5; i++){
		tanks[i] = NULL;
		
	}
	//////////////////////////////////////////////////////////////////////////////////////////
	for (i = 0; i < 2; i++){
		buffs[i] = NULL;
	}
	//////////////////////////////////////////////////////
}
//////////////////////////////////////////////////////////////////////////////////////////////////刘松林添加
void Game::buff_clear_allbullets(Bullet **bullets){
	int i;
	for (i = 0; i < 10; i++){
		//bullets[i]->is_exist = false;
		free(bullets[i]);
		bullets[i] = NULL;
	}
}
///////////////////////////////////////////////////////////////////////////////
Game::Game() {
	this->init_array(bullets, tanks,buffs);
	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "TANK");
	sf::Clock clock;
	sf::Clock clock1;
	tanks[0] = new Tank();
	Tank enemy_tank;
	enemy_tank.setPosition(350, 450);
	enemy_tank.gun.setPosition(350, 450);
	int temp = 0;///////////////////////////////////////////////////////////////////////////
	sf::Vector2f buff_position;
	//buff_position.x = 100;//
	//buff_position.y = 50;//

	sf::Event event;
	////////////////////////////////////////////////////////////////LSL music
	sf::SoundBuffer shotbuffer;
	shotbuffer.loadFromFile("shot.wav");
	sf::Sound shotsound;
	shotsound.setBuffer(shotbuffer);
	sf::SoundBuffer gameoverbuffer;
	bool x=gameoverbuffer.loadFromFile("gameover.wav");
	sf::Sound gameoversound;
	gameoversound.setBuffer(gameoverbuffer);
	////////////////////////////////////////////////////////////////////////////////

	sf::Texture startgame_texture;
	if (!startgame_texture.loadFromFile("gamestart.jpg")) {
		return;
	}
	sf::Sprite startgame_sprite(startgame_texture);



	window.draw(startgame_sprite);
	window.display();

	bool flag = true;

	while (window.isOpen() && flag){
		while (window.pollEvent(event))
		{
			is_exit(event, window);


			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					flag = false;
					break;
				}
			}
		}

	}




	Shield shield_a(SHIELD_A);
	/*SYSTEMTIME sys;
	GetLocalTime(&sys);
	int fire_time = sys.wSecond;*/
	sf::Time fire_time = clock1.restart();
	
	while (window.isOpen())
	{
		
		while (window.pollEvent(event))
		{
			is_exit(event, window);

			tanks[0]->move_tank(event);

			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					for (int i = 0; i < 10; i++) {
						if (bullets[i] == NULL) {
							bullets[i] = new Bullet(tanks[0]->fire(window));
							shotsound.play();/////////////////////////////////////////////////////////////music
							break;
						}
					}

				}
			}
		}
		sf::Time fire_gap = clock1.getElapsedTime();
		sf::Vector2f vector = tanks[0]->getPosition() - enemy_tank.getPosition();
		float distance = (sqrt(vector.x*vector.x + vector.y*vector.y));
		if (distance<150)
		{
			float angle = enemy_tank.enemy_fire_angle(vector);
			enemy_tank.gun.setRotation(angle);
			if (fire_gap.asSeconds() > 1)
			{
				for (int i = 0; i < 10; i++) {
					if (bullets[i] == NULL) {
						bullets[i] = new Bullet(enemy_tank.enemy_fire2tank(*tanks[0]));
						break;
					}
				}
				fire_time = clock1.restart();
			}
		}
		enemy_tank.enemy_move();
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////LSL
		temp++;
		if (temp == BUFF_TIME){
			//printf("%d\n", temp);
			for (int i = 0; i < 2; i++){
				if (buffs[i] == NULL){
					int type = (rand() % (TYPE_MAX - TYPE_MIN + 1)) + TYPE_MIN;
					//Buff buff(type);
					//buffs[i] = &buff;
					buffs[i] = new Buff(type);
					//printf("%d\n", buffs[i]->type);
					break;
				}
			}
			temp = 0;
		}
		for (int i = 0; i < 2; i++){
			if (buffs[i] != NULL){
				int buff_type = buffs[i]->tank_buff_collision(tanks[0]);
				if (buff_type == 1){
					this->buff_clear_allbullets(bullets);
					free(buffs[i]);
					buffs[i] = NULL;
				}
				if (buff_type == 2){
					//tanks[0].
					tanks[0]->reset_tank_texture();
					free(buffs[i]);
					buffs[i] = NULL;
				}
			}
		}
		//////////////////////////////////////////////////////////////////////////////////////////////////////
		window.clear(sf::Color(225, 225, 225));

		window.draw(shield_a);
		///////////////////////////////////////////////////////////////////////////////////////LSL
		for (int i = 0; i < 2; i++){
			if (buffs[i]!=NULL&&buffs[i]->type != 0){
				window.draw(*buffs[i]);
			}
		}//////////////////////////////////////////////////////////////////////////////////////////////////
		/*if (enemy_tank.is_exist == true)
		{
		window.draw(enemy_tank);
		window.draw(enemy_tank.gun);
		}*/
		window.draw(enemy_tank);
		window.draw(enemy_tank.gun);

		sf::Time elapsed = clock.restart();
		Draw_Tank(*tanks[0], elapsed, window);
		tanks[0]->tank_collison(enemy_tank);//坦克碰撞
		enemy_tank.enemy_update(elapsed, window);
		//check_collsion
		for (int i = 0; i<10; i++) {
			if (bullets[i] != NULL) {
				shield_a.A_check_collsion_with_bullet(*bullets[i]);
				tanks[0]->bullet_collision(*bullets[i]);

				enemy_tank.bullet_collision(*bullets[i]);

				for (int j = i + 1; j<10; j++) {
					if (bullets[j] != NULL) {
						bullets[i]->bullet_collision_check(bullets[j]);
					}

				}

			}
			
		}
		/////////////////////////////////////////////////////////////////////////////////////////lsl music
		if (tanks[0]->is_exist == false){
			
			gameoversound.play();
		}
		///////////////////////////////////////////////////////////////////////////////

		shield_a.A_check_collsion_with_tank(*tanks[0]);
		shield_a.A_check_collsion_with_tank(enemy_tank);
		//check_exit

		for (int i = 0; i<10; i++) {
			if (bullets[i] != NULL && bullets[i]->is_exist == false) {
				delete bullets[i];
				bullets[i] = NULL;
			}
		}

		for (int i = 0; i<10; i++) {
			if (bullets[i] && bullets[i]->is_exist == true)
			{
				bullets[i]->update(elapsed);
				window.draw(*bullets[i]);

			}
		}


		window.display();
	}

}

