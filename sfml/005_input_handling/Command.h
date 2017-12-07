#ifndef COMMAND_H_
#define COMMAND_H_

#include <SFML/System/Time.hpp>

#include <functional>
#include <cassert>

#include "Category.h"

class SceneNode;

struct Command
{
	Command();

	std::function<void(SceneNode&, sf::Time)> action;
	Category::Type category;
};

template <typename GameObject, typename Function>
std::function<void(SceneNode&, sf::Time)> derivedAction(Function fn)
{
	return [=] (SceneNode& node, sf::Time dt) {
		assert(dynamic_cast<GameObject*>(&node) != nullptr);
		fn(static_cast<GameObject&>(node), dt);
	};
}

#endif
