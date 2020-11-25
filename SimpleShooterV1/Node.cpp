/*
* A class that represents a node within a behavior tree
* 
* 
* A main component of the behavior tree that represents the objects 
* that contain tasks
*/

#include "Node.h"

Node::Node()
{
}

//Node::Node(Blackboard* enemyBoard) : super(enemyBoard)
//{
//	CreateController();
//}

Node::Node(Blackboard* enemyBoard, std::string aName) : super(enemyBoard, aName)
{
	CreateController();
}

Node::~Node()
{
}

void Node::CreateController()
{
	controller = new TaskController(this);
}

TaskController* Node::GetControl()
{
	return this->controller;
}
