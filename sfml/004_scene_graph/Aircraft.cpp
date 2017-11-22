#include "Aircraft.h"

Textures::ID toTextureID(Aircraft::Type type)
{
	Textures::ID texture = Textures::ID::Vulture;
	switch (type)
	{
	case Aircraft::Type::Vulture:
		texture = Textures::ID::Vulture;
		break;
	case Aircraft::Type::Raptor:
		texture = Textures::ID::Raptor;
		break;
	default:
		break;
	}
	return texture;
}

Aircraft::Aircraft(Type type, const TextureHolder& textures): mType(type), mSprite(textures.get(toTextureID(type)))
{
	sf::FloatRect bounds = mSprite.getLocalBounds();
	mSprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
}

void Aircraft::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(mSprite, states);
}
