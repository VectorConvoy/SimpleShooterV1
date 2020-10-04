#pragma once
#define _SELECTOR_H

#include "CompositeNode.h"

class Selector : public CompositeNode
{
public:
	virtual bool Run() override
	{
		for (Node* child : GetChildren())
		{
			if (child->Run())
			{
				return true;
			}
		}
		return false;
	}
};