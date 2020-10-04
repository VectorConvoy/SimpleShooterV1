#pragma once
#define _COMPOSITENODE_H

#include "Node.h"
#include <list>

class CompositeNode : public Node
{
public:
	const std::list<Node*>& GetChildren();
	
	void AddChild(Node* child) { children.emplace_back(child); };
private:
	std::list<Node*> children;
};