#pragma once
#define _MOVECOMMAND_H

#include "Command.h"

class MoveCommand : public Command
{
public:
	bool Execute();

	bool Execute(Enemy* enemy);
};