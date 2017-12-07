#ifndef WORLD_H
#define WORLD_H

#include <array>

#include <SFML/Graphics.hpp>

#include "Aircraft.h"
#include "ResourceHolder.h"
#include "SceneNode.h"
#include "CommandQueue.h"

class World : private sf::NonCopyable
{
	public:
		explicit World(sf::RenderWindow& window);

		void update(sf::Time dt);
		void draw();

		CommandQueue& getCommandQueue();

	private:
		void loadTextures();
		void buildScene();
		void adaptPlayerPosition();
		void adaptPlayerVelocity();

	private:
		enum Layer {
			Background = 0,
			Foreground,
			LayerCount
		};

	private:
		sf::RenderWindow& mWindow;
		sf::View mWorldView;
		TextureHolder mTextures;

		SceneNode mSceneGraph;
		std::array<SceneNode*, LayerCount>	mSceneLayers;
		CommandQueue mCommandQueue;

		sf::FloatRect mWorldBounds;
		sf::Vector2f mSpawnPosition;
		float mScrollSpeed;
		Aircraft* mPlayerAircraft;
};

#endif
