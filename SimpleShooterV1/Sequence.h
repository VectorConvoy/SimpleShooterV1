#pragma once
#define _SEQUENCE_H

#include "CompositeNode.h"

class Sequence : public CompositeNode
{
public:
	virtual bool Run() override
	{
		for (Node* child : GetChildren())
		{
			if (!child->Run())
			{
				return false;
			}
		}

		return true;
	}
};