#pragma once
#define _FACEPLAYERTASK_H

#include "Node.h"

class FacePlayerTask : public Node
{
public:
	typedef Node super;

	FacePlayerTask();
	FacePlayerTask(Blackboard* blackboard, std::string aName);
	~FacePlayerTask();

	bool CheckConditions();

	void DoAction();

	void Start();
	void End();
};