#include "World.h"
#include "SpriteNode.h"

World::World(sf::RenderWindow& window)
: mWindow(window)
, mWorldView(window.getDefaultView())
, mTextures()
, mSceneGraph()
, mSceneLayers()
, mWorldBounds(0.f, 0.f, mWorldView.getSize().x, 200000.f)
, mSpawnPosition(mWorldView.getSize().x / 2.f, mWorldBounds.height - mWorldView.getSize().y / 2.f)
, mScrollSpeed(-50.f)
, mPlayerAircraft(nullptr)
{
	loadTextures();
	buildScene();

	mWorldView.setCenter(mSpawnPosition);
}

void World::loadTextures()
{
	mTextures.load(Textures::ID::Vulture, "resources/images/vulture.png");
	mTextures.load(Textures::ID::Raptor, "resources/images/raptor.png");
	mTextures.load(Textures::ID::Landscape, "resources/images/space.png");
	mTextures.load(Textures::ID::Missile, "resources/images/missile.png");
}

void World::buildScene()
{
	// Create all empty nodes
	for (std::size_t i = 0; i < LayerCount; ++i) {
		SceneNode::Ptr layer(new SceneNode());
		mSceneLayers[i] = layer.get();
		mSceneGraph.attachChild(std::move(layer));
	}

	// Initiate background
	sf::Texture& texture = mTextures.get(Textures::ID::Landscape);
	sf::IntRect textureRect(mWorldBounds);
	texture.setRepeated(true);

	// Add background to the background node
	std::unique_ptr<SpriteNode> backgroundSprite(new SpriteNode(texture, textureRect));
	backgroundSprite->setPosition(mWorldBounds.left, mWorldBounds.top);
	mSceneLayers[Layer::Background]->attachChild(std::move(backgroundSprite));

	// Create and add player
	std::unique_ptr<Aircraft> leader(new Aircraft(Aircraft::Type::Vulture, mTextures));
	mPlayerAircraft = leader.get();
	mPlayerAircraft->setPosition(mSpawnPosition);
	mPlayerAircraft->setVelocity(40.f, mScrollSpeed);
	mSceneLayers[Layer::Foreground]->attachChild(std::move(leader));

	// Add escort to the player
	std::unique_ptr<Aircraft> leftEscort(new Aircraft(Aircraft::Type::Vulture, mTextures));
	leftEscort->setPosition(-80.f, 50.f);
	mPlayerAircraft->attachChild(std::move(leftEscort));
	std::unique_ptr<Aircraft> rightEscort(new Aircraft(Aircraft::Type::Vulture, mTextures));
	rightEscort->setPosition(80.f, 50.f);
	mPlayerAircraft->attachChild(std::move(rightEscort));

}

void World::draw()
{
	mWindow.setView(mWorldView);
	mWindow.draw(mSceneGraph);
}

void World::update(sf::Time dt)
{
	mWorldView.move(0.f, mScrollSpeed * dt.asSeconds());
	sf::Vector2f position = mPlayerAircraft->getPosition();
	sf::Vector2f velocity = mPlayerAircraft->getVelocity();
	if (position.x <= mWorldBounds.left + 150 || position.x >= mWorldBounds.left + mWorldBounds.width - 150) {
		velocity.x = -velocity.x;
		mPlayerAircraft->setVelocity(velocity);
	}
	mSceneGraph.update(dt);
}

