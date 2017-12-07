#ifndef RESOURCEIDENTIFIERS_H_
#define RESOURCEIDENTIFIERS_H_

// Forward declaration of SFML classes
namespace sf
{
	class Texture;
}

namespace Textures
{
enum class ID {
	Landscape = 0,
	Vulture,
	Raptor,
	Missile
};
}

template <typename Resource, typename Identifier>
class ResourceHolder;

typedef ResourceHolder<sf::Texture, Textures::ID> TextureHolder;

#endif
