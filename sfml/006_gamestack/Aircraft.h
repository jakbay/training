#ifndef AIRCRAFT_H
#define AIRCRAFT_H

#include <SFML/Graphics/Sprite.hpp>

#include "Entity.h"
#include "ResourceIdentifiers.h"

class Aircraft : public Entity
{
public:
	enum Type {
		Vulture,
		Raptor,
	};

public:
	Aircraft(Type type, const TextureHolder& textures);
	virtual unsigned int getCategory() const;

private:
	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	Type mType;
	sf::Sprite mSprite;
};

#endif
