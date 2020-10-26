#include "Node.h"

Node::Node()
{
}

Node::Node(Blackboard* enemyBoard) : super(enemyBoard)
{
	
}

Node::~Node()
{
}

void Node::CreateController()
{
	controller = new TaskController(this);
}
