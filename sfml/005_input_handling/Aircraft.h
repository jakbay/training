#ifndef AIRCRAFT_H
#define AIRCRAFT_H

#include "Entity.h"
#include "ResourceHolder.h"
#include "ResourceIdentifiers.h"
#include "Category.h"

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

	virtual Category::Type getCategory() const;

	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	Type mType;
	sf::Sprite mSprite;
};

#endif
