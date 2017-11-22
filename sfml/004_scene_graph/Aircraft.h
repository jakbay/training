#ifndef AIRCRAFT_H
#define AIRCRAFT_H

#include "Entity.h"
#include "ResourceHolder.h"

class Aircraft : public Entity
{
public:
	enum class Type {
		Vulture = 0,
		Raptor
	};

public:
	explicit Aircraft(Type type, const TextureHolder& textures);
	virtual ~Aircraft() {};

	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	Type mType;
	sf::Sprite mSprite;
};

#endif
