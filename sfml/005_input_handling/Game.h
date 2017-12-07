#ifndef GAME_H
#define GAME_H

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "World.h"
#include "Player.h"

class Game
{
public:
	Game();
	void run();

private:
	void processInput();
	void update(const sf::Time &deltaTime);
	void render();
	void updateStatistics(sf::Time elapsedTime);

	sf::RenderWindow mWindow;
	World mWorld;
	Player mPlayer;
  	sf::Font mFont;
	sf::Text mStatisticsText;
	sf::Time mStatisticsUpdateTime;
	std::size_t	mStatisticsNumFrames;
};
#endif
