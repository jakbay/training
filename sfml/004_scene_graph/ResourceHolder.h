#ifndef RESOURCEHOLDER_H
#define RESOURCEHOLDER_H

#include <map>
#include <memory>
#include <string>

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
class ResourceHolder
{
public:
	void load(Identifier id, const std::string& filename);

	template <typename Parameter>
	void load(Identifier id, const std::string& filename,
	const Parameter& secondParam);

	Resource& get(Identifier id);
	const Resource& get(Identifier id) const;

private:
std::map<Identifier,
std::unique_ptr<Resource>> mResourceMap;
};

#include "ResourceHolder.inl"

typedef ResourceHolder<sf::Texture, Textures::ID> TextureHolder;

#endif
