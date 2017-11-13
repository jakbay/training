#include <map>
#include <memory>
#include <string>

#include <SFML/Graphics.hpp>

namespace Textures
{
enum class ID {
	Landscape = 0,
	Airplane,
	Missile };
}

class TextureHolder
{
public:
	void load(Textures::ID id, const std::string& filename);
	sf::Texture& get(Textures::ID id);
	const sf::Texture& get(Textures::ID id) const;

private:
std::map<Textures::ID,
std::unique_ptr<sf::Texture>> mTextureMap;
};
