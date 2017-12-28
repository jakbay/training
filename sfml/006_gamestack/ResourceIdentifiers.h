#ifndef RESOURCEIDENTIFIERS_H
#define RESOURCEIDENTIFIERS_H

namespace sf
{
class Texture;
class Font;
}

namespace Textures
{
enum ID {
	Vulture,
	Raptor,
	Desert,
	TitleScreen,
};
}

namespace Fonts
{
enum ID {
	Main,
};
}

template <typename Resource, typename Identifier>
class ResourceHolder;

typedef ResourceHolder<sf::Texture, Textures::ID> TextureHolder;
typedef ResourceHolder<sf::Font, Fonts::ID> FontHolder;

#endif
