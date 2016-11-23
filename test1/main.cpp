using namespace std;
//using namespace sf;
#include <SFML/Graphics.hpp>
//#include "Graphics.h"
#include "tank.h"
#include "bullet.h"
#define WIDTH 800
#define HEIGHT 600
#define bullet_max 50
void is_exit(sf::Event &event, sf::RenderWindow &window)
{
	//判断是否点×
	bool close = (event.type == sf::Event::Closed);
	//判断是否按ESC
	bool escape = (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape);
	if (close || escape)
		window.close();
}
void Draw_Tank(Tank &tank, sf::Time elapsed, sf::RenderWindow &window)
{
	tank.update(elapsed, window);
	window.draw(tank);
	window.draw(tank.gun);
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "TANK");
	sf::Clock clock;
	Tank tank;
	Bullet *bullet = NULL;
	//	Bullet bullet_array[50];
	Bullet *bullet_array[bullet_max];

	//bool bullet_array_bool[bullet_max];
	int i, j;
	for (i = 0; i < bullet_max; i++){
		bullet_array[i] = NULL;
	}
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			is_exit(event, window);
			tank.move_tank(event);
			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					for (i = 0; i < bullet_max&&bullet_array[i] != NULL; i++){}//找到空位放子弹
					if (i >= bullet_max){ printf("too many bullets"); }
					else{
						bullet_array[i] = new Bullet(tank.fire(window));

					}
				}
			}
		}
		sf::Time elapsed = clock.restart();
		window.clear(sf::Color(255, 255, 255));
		Draw_Tank(tank, elapsed, window);
		for (i = 0; i < bullet_max; i++){//检测子弹碰撞
			if (bullet_array[i] != NULL){
				for (j = i + 1; j < bullet_max; j++){
					if (bullet_array[j] != NULL){
						bullet_array[i]->bullet_collision_check(bullet_array[j]);
					}
				}
			}
		}
		for (i = 0; i < bullet_max; i++){//释放消失子弹内存
			if (bullet_array[i] != NULL){
				if (bullet_array[i]->is_exist == false){
					free(bullet_array[i]);
					bullet_array[i] = NULL;
				}
			}
		}
		for (i = 0; i < bullet_max; i++){//画子弹
			if (bullet_array[i] != NULL)
			{
				window.draw(*bullet_array[i]);
				bullet_array[i]->update(elapsed);
				//printf("%d:", i);
			}
		}
		window.display();
	}

}