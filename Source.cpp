#include "SFML/Graphics.hpp"
#include <time.h>
#include <iostream>
#include <string>

const int WindWidth = 800;
const int WindHeight = 600;
int speed = 5;
bool playingfield[WindWidth][WindHeight];
struct player {
	int x, y, dir;
	sf::Color color;
	player(sf::Color c) {
		x = rand() % WindWidth;
		y = rand() % WindHeight;
		color = c;
		dir = rand() % 4;
	}
	void tick() { 
		if (dir == 0) {
			y += 1;
		}
		if (dir == 1) {
			x -= 1;
		}
		if (dir == 2) {
			x += 1;
		}
		if (dir == 3) {
			y -= 1;
		}
		if (x >= WindWidth) {
			x = 0;
		}
		if (x < 0) {
			x = WindWidth - 1;
		}
		if (y >= WindHeight) {
			y = 0;
		}
		if (y<0){
			y = WindHeight - 1;
		}

	}
	sf::Vector3f getColor() {
		return sf::Vector3f(color.r, color.g, color.b);
	}
};

int main() {
	std::string timer;
	srand(time(0));
	sf::RenderWindow window(sf::VideoMode(WindWidth, WindHeight), "COP GUI/SFML project"); //The window
	window.setFramerateLimit(60); //locks the framerate as any more can cause issues
	sf::Clock clock;
	sf::Font font;
	if(!font.loadFromFile("Minecraft.ttf")){ //imported a font to display text when the game is over
		throw("Font did not load");
	}
	sf::Text text("GAME OVER\nTIME ALLOCATED:", font, 20);
	text.setPosition(WindWidth/3 - 50, 250);
	player player(sf::Color::Cyan);
	sf::Sprite s;
	sf:: RenderTexture t;
	t.create(WindWidth, WindHeight);
	t.setSmooth(true); // smooths out the texture so it reduces the impact it has on the GPU
	s.setTexture(t.getTexture());
	t.clear();
	bool Game = 1;
	while (window.isOpen()) { //will run until closed
		sf::Event e;
		while (window.pollEvent(e)) 
		{
			if (e.type == sf::Event::Closed) {
				window.close();
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) //Keyboard movement
		{
			if (player.dir != 2) {
				player.dir = 1;
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) 
		{
			if (player.dir != 1) {
				player.dir = 2;
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) 
		{
			if (player.dir != 0) {
				player.dir = 3;
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) 
		{
			if (player.dir != 3) {
				player.dir = 0;
			}
		}
		if (!Game) {
			continue; //game continues until game is not true anymore
		}
		for (int i = 0; i < speed; i++) {
			player.tick();
			if (playingfield[player.x][player.y] == 1) {
				Game = 0;
			}
			playingfield[player.x][player.y] = 1;
			sf::CircleShape c(3);
			c.setPosition(player.x, player.y);
			c.setFillColor(player.color);
			t.draw(c);
			t.display();
		}

		//updates constantly

		sf::Time elapsed = clock.getElapsedTime();
		std::cout << elapsed.asSeconds() << std::endl; //Timer that updates
		window.clear();
		window.draw(s);
		window.display();
		
		if (Game == 0) {
			std::cout << "Time: " << elapsed.asSeconds() << std::endl;
			timer =  std::to_string(elapsed.asSeconds()) + "s";
			sf::Text text1(timer, font, 40);
			text1.setPosition(WindWidth /2 +30, 250); //Displays the time you spent during that game
			window.draw(text);
			window.draw(text1);
			window.display();
		}
		
	}
	return 0;
}