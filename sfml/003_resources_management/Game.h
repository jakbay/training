#include <SFML/Graphics.hpp>

#include "ResourceHolder.h"

class Game
{
public:
	Game();
	void run();

private:
	void processEvents();
	void update(const sf::Time &deltaTime);
	void render();

	void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);

	sf::RenderWindow mWindow;
	ResourceHolder<sf::Texture, Textures::ID> mTextures;
	sf::Sprite mBackground;
	sf::Sprite mPlayer;
	bool mIsMovingUp;
	bool mIsMovingDown;
	bool mIsMovingLeft;
	bool mIsMovingRight;
	const float PlayerSpeed = 480.f;
	const sf::Time TimePerFrame = sf::seconds(1.f / 60.f);
};
