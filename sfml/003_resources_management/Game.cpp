#include "Game.h"

Game::Game() :
mWindow(sf::VideoMode(1920, 1080), "SFML Application"),
mTextures(),
mBackground(),
mPlayer(),
mIsMovingUp(false),
mIsMovingDown(false),
mIsMovingLeft(false),
mIsMovingRight(false)
{
	mWindow.setVerticalSyncEnabled(true);
	mTextures.load(Textures::ID::Airplane, "resources/images/vulture.png");
	mTextures.load(Textures::ID::Landscape, "resources/images/desert.png");
	mTextures.load(Textures::ID::Missile, "resources/images/missile.png");
	mBackground.setTexture(mTextures.get(Textures::ID::Landscape));
	mBackground.setPosition(0.f, 0.f);
	mPlayer.setTexture(mTextures.get(Textures::ID::Airplane));
	mPlayer.setPosition(900.f, 800.f);
}

void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	while (mWindow.isOpen()) {
		processEvents();
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;
			processEvents();
			update(TimePerFrame);
		}
		render();
	}
}

void Game::processEvents()
{
	sf::Event event;
	while (mWindow.pollEvent(event))
	{
		switch (event.type) {
		case sf::Event::KeyPressed:
			handlePlayerInput(event.key.code, true);
			break;
		case sf::Event::KeyReleased:
			handlePlayerInput(event.key.code, false);
			break;
		case sf::Event::Closed:
			mWindow.close();
			break;
		default:
			break;
		}
	}
}

void Game::update(const sf::Time &deltaTime)
{
	sf::Vector2f movement(0.f, 0.f);
	if (mIsMovingUp) {
		movement.y -= PlayerSpeed;
	}
	if (mIsMovingDown) {
		movement.y += PlayerSpeed;
	}
	if (mIsMovingLeft) {
		movement.x -= PlayerSpeed;
	}
	if (mIsMovingRight) {
		movement.x += PlayerSpeed;
	}
	mPlayer.move(movement * deltaTime.asSeconds());
}

void Game::render()
{
	mWindow.clear();
	mWindow.draw(mBackground);
	mWindow.draw(mPlayer);
	mWindow.display();
}

void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{
	switch (key) {
	case sf::Keyboard::Z:
		mIsMovingUp = isPressed;
		break;
	case sf::Keyboard::S:
		mIsMovingDown = isPressed;
		break;
	case sf::Keyboard::Q:
		mIsMovingLeft = isPressed;
		break;
	case sf::Keyboard::D:
		mIsMovingRight = isPressed;
		break;
	default:
		break;
	}
}
