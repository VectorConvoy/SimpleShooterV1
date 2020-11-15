#pragma once
#define _FACEAWAYPLAYERTASK_H

#include "Node.h"

class FaceAwayPlayerTask : public Node
{
public:
	typedef Node super;

	FaceAwayPlayerTask(Blackboard* board, std::string aName);
	~FaceAwayPlayerTask();

	bool CheckConditions();
	void Start();
	void End();
	void DoAction();
};