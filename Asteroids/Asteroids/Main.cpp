#include <iostream> // cout 
#include <math.h> // atan2
#include "Collision/Collision.h"
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 720
#define PI 3.14159265

float vectorAngle(Vector2f first, Vector2f second) {

	first -= second;
	return atan2(first.y, first.x) * (180 / PI);
}

class Player{
private:
	Texture texture;
	Sprite sprite;
	float speed;
public:
	Player(){
		speed = 0.1;
		if (!texture.loadFromFile("Images/ship.png")) {
			std:cout << "ERROR: load sprite for player" << std::endl;
			exit(EXIT_FAILURE);
		}
		sprite.setTexture(texture);
		sprite.setOrigin(50, 50);
		sprite.setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	}
	void move() {
		if (Keyboard::isKeyPressed(Keyboard::A)) 
			sprite.move(-speed, 0);
		if (Keyboard::isKeyPressed(Keyboard::D)) 
			sprite.move(speed, 0);
		if (Keyboard::isKeyPressed(Keyboard::W)) 
			sprite.move(0, -speed);
		if (Keyboard::isKeyPressed(Keyboard::S)) 
			sprite.move(0, speed);
	}

	void rorate(Window& window) {
		Vector2f position = sprite.getPosition();
		Vector2f mousePosition = (Vector2f) Mouse::getPosition(window);

		float rotation = vectorAngle(position, mousePosition);
		sprite.setRotation(rotation-90);
	}

	Sprite getSprite() {
		return sprite;
	}
};

int main()
{
	Player* player = new Player();
	RenderWindow window(VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Asteroids!");

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}

		window.clear();

		// Draw everything 
		player->rorate(window);
		player->move();
		window.draw(player ->getSprite());

		window.display();
	}
	delete player;

	return 0;
}