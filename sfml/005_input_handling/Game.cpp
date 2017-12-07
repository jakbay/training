#include <string>

#include "Game.h"

const sf::Time TimePerFrame = sf::seconds(1.f / 60.f);

Game::Game() :
mWindow(sf::VideoMode(1920, 1080), "SFML Application"),
mWorld(mWindow),
mPlayer(),
mFont(),
mStatisticsText(),
mStatisticsUpdateTime(),
mStatisticsNumFrames(0)
{
	mWindow.setKeyRepeatEnabled(false);
	mWindow.setVerticalSyncEnabled(true);
	mFont.loadFromFile("resources/fonts/Sansation.ttf");
	mStatisticsText.setFont(mFont);
	mStatisticsText.setPosition(5.f, 5.f);
	mStatisticsText.setCharacterSize(10);
}

void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	sf::Time elapsedTime = sf::Time::Zero;
	while (mWindow.isOpen()) {
		elapsedTime = clock.restart();
		timeSinceLastUpdate += elapsedTime;
		while (timeSinceLastUpdate > TimePerFrame) {
			timeSinceLastUpdate -= TimePerFrame;
			processInput();
			update(TimePerFrame);
		}
		updateStatistics(elapsedTime);
		render();
	}
}

void Game::processInput()
{
	CommandQueue& commands = mWorld.getCommandQueue();
	sf::Event event;
	while (mWindow.pollEvent(event)) {
		mPlayer.handleEvent(event, commands);
		if (event.type == sf::Event::Closed) {
			mWindow.close();
		}
	}
	mPlayer.handleRealtimeInput(commands);
}

void Game::update(const sf::Time &deltaTime)
{
	mWorld.update(deltaTime);
}

void Game::render()
{
	mWindow.clear();
	mWorld.draw();

	mWindow.setView(mWindow.getDefaultView());
	mWindow.draw(mStatisticsText);
	mWindow.display();
}

void Game::updateStatistics(sf::Time elapsedTime)
{
	mStatisticsUpdateTime += elapsedTime;
	mStatisticsNumFrames += 1;

	if (mStatisticsUpdateTime >= sf::seconds(1.0f)) {
		mStatisticsText.setString("Frames / Second = " + std::to_string(mStatisticsNumFrames) + "\n" +
			"Time / Update = " + std::to_string(mStatisticsUpdateTime.asMicroseconds() / mStatisticsNumFrames) + "us");

		mStatisticsUpdateTime -= sf::seconds(1.0f);
		mStatisticsNumFrames = 0;
	}
}