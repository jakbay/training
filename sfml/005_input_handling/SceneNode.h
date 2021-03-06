#ifndef SCENENODE_H
#define SCENENODE_H

#include <vector>
#include <memory>

#include <SFML/Graphics.hpp>

#include "Command.h"
#include "Category.h"

class SceneNode : public sf::Transformable, public sf::Drawable, private sf::NonCopyable
{
public:
	typedef std::unique_ptr<SceneNode> Ptr;

public:
	SceneNode();
	virtual ~SceneNode() {};

	void attachChild(Ptr child);
	Ptr detachChild(const SceneNode& node);

	void update(sf::Time dt);

	sf::Transform getWorldTransform() const;
	sf::Vector2f getWorldPosition() const;

	void onCommand(const Command& command, sf::Time dt);
	virtual Category::Type getCategory() const;

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const final;
	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
	void drawChildren(sf::RenderTarget& target, sf::RenderStates states) const;

	virtual void updateCurrent(sf::Time dt);
	void updateChildren(sf::Time dt);

private:
	std::vector<Ptr> mChildren;
	SceneNode* mParent;
};

#endif
