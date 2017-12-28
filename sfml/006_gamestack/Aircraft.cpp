#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

#include "Aircraft.h"
#include "ResourceHolder.h"
#include "Utility.h"

Textures::ID toTextureID(Aircraft::Type type)
{
	Textures::ID ret = Textures::Vulture;
	switch (type) {
	case Aircraft::Vulture:
		ret = Textures::Vulture;
		break;
	case Aircraft::Raptor:
		ret = Textures::Raptor;
		break;
	default:
		break;
	}
	return ret;
}

Aircraft::Aircraft(Type type, const TextureHolder& textures)
: mType(type)
, mSprite(textures.get(toTextureID(type)))
{
	centerOrigin(mSprite);
}

void Aircraft::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(mSprite, states);
}

unsigned int Aircraft::getCategory() const
{
	switch (mType) {
		case Vulture:
			return Category::PlayerAircraft;

		default:
			return Category::EnemyAircraft;
	}
}
