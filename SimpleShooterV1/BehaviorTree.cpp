/*
* A class to reprent a behavior tree
* 
* Mainly handles the AI's logic and 
* determines what it should do
*/

#include "BehaviorTree.h"
#include "ChanceDecorator.h"
#include "FleeBehavior.h"
#include "SeekBehavior.h"
#include "ShootBehavior.h"
#include "IdleBehavior.h"
#include "GetPlayerTask.h"
#include "IdleTask.h"
#include <algorithm>

BehaviorTree::BehaviorTree()
{
	AIBoard = new Blackboard();
	AISelector = new Selector(AIBoard, "DEFAULT BEHAVIOR TREE");

	sAIEngineInstance = AIEngine::Instance();
	
	SetBoardForBehaviors();

	CreateBehaviorTree();
}

BehaviorTree::BehaviorTree(Enemy* owner)
{
	AIBoard = new Blackboard();
	AIBoard->SetEnemy(owner);
	GetPlayer = new GetPlayerTask(AIBoard, "Get Player Task");
	AISelector = new Selector(AIBoard, "AI Selector");
	sAIEngineInstance = AIEngine::Instance();
	
	SetBoardForBehaviors();

}

BehaviorTree::~BehaviorTree()
{
	delete AIBoard;
	AIBoard = nullptr;

	delete AISelector;
	AISelector = nullptr;
}

/*
* BUG - FIX ISSUE WHERE THE BOARD IS ONLY BEING SET ON THE SURFACE
* MUST ASSIGN BOARD TO EVERY SINGLE TASK
*/

void BehaviorTree::SetBoardForBehaviors()
{
	for (std::shared_ptr<Behavior> aBehavior : sAIEngineInstance->GetAllBehaviors())
	{
		aBehavior.get()->SetBoard(AIBoard);
		//((ParentTask*)aBehavior.get()->behaviorSequence)->SetBoardForAllSubtasks(AIBoard);
	}
}

void BehaviorTree::CreateBehaviorTree(BEHAVIOR_TYPES behavior)
{

	//std::transform(behaviorType.begin(), behaviorType.end(), behaviorType.begin(), [](unsigned char c) {return std::tolower(c); });

	if (behavior == BEHAVIOR_TYPES::flee)
	{
		//this->sLoggerInstance->Log("ADDING FLEE BEHAVIOR");
		AddBehaviorToBehaviorTree(new FleeBehavior(AIBoard));

	}
	else if (behavior == BEHAVIOR_TYPES::chase)
	{
		//this->sLoggerInstance->Log("ADDING CHASE BEHAVIOR");
		AddBehaviorToBehaviorTree(new SeekBehavior(AIBoard));
	}
	else if (behavior == BEHAVIOR_TYPES::chase_shoot)
	{
		//this->sLoggerInstance->Log("ADDING CHASE & FIRE BEHAVIOR");
		SeekBehavior* temp = new SeekBehavior(AIBoard);
		temp->AddAdditionalSequence((new ShootBehavior(AIBoard))->behaviorSequence);
		AddBehaviorToBehaviorTree(temp);

		temp = nullptr;
	}
	else if (behavior == BEHAVIOR_TYPES::sentry)
	{
		AddBehaviorToBehaviorTree(new ShootBehavior(AIBoard));
	}
	else if (behavior == BEHAVIOR_TYPES::sniper)
	{
		SeekBehavior* seek = new SeekBehavior(AIBoard, 10.0f);
		CloseToPlayerDecorator* close = new CloseToPlayerDecorator(AIBoard, seek->behaviorSequence, 200.0f, "Seek Close To Player Decorator Sequence");

		FleeBehavior* flee = new FleeBehavior(AIBoard, 500.0f);
		ShootBehavior* shoot = new ShootBehavior(AIBoard, 5);

		AddTaskToBehaviorTree(close);

		//AddBehaviorToBehaviorTree(seek);
		AddBehaviorToBehaviorTree(flee);
		AddBehaviorToBehaviorTree(shoot);

		//AddBehaviorToBehaviorTree(new SeekBehavior(AIBoard));


	}

	//Add Idle Task so if AI does not pass any decorators simply have it idle at current position
	AddBehaviorToBehaviorTree(new IdleBehavior(AIBoard));
}

void BehaviorTree::ConstructTree(std::string xmlFile)
{
	LoadXML(xmlFile);
}

void BehaviorTree::LoadXML(std::string xmlFile)
{
	pugi::xml_parse_result parseResults = behaviorDoc.load_file(xmlFile.c_str());

	if (parseResults)
	{
		//Success
		//ParseRoot();
	}
	else
	{
		//Failure
		this->sLoggerInstance->Log("FAILED TO LOAD BEHAVIOR XML\n");
	}
}

void BehaviorTree::ParseRoot(pugi::xml_node root)
{
	for (pugi::xml_node xmlNode : root.children("Behavior"))
	{
		for (pugi::xml_node traitNode : xmlNode.children("Trait"))
		{
			ParseBehaviorXML(traitNode);
		}
	}
}

void BehaviorTree::ParseBehaviorXML(pugi::xml_node traitNode)
{
	Behavior* unalteredBehavior;
	std::string name;
	int priorityVal;
	float value;

	name = traitNode.child_value("Name");
	priorityVal = atoi(traitNode.child_value("Priority"));
	value = (float) atof(traitNode.child_value("Value"));

	unalteredBehavior = sAIEngineInstance->GetSpecificBehavior(name);

	if (unalteredBehavior != nullptr)
	{
		unalteredBehavior->SetPriorityID(priorityVal);
		unalteredBehavior->SetValue(value);

		CreateDecorator(unalteredBehavior, traitNode.child("Condition"));
	}

	
}

void BehaviorTree::CreateDecorator(Behavior* behavior, pugi::xml_node conditionNode)
{
	std::string name;
	float value;
	std::string decoName;
	Tasks* customBehaviorSeq;
	

	decoName = conditionNode.child_value("Decorator");
	name = conditionNode.child_value("Name");
	value = atof(conditionNode.child_value("Value"));

	if (decoName == "CloseToPlayer")
	{
		customBehaviorSeq = new CloseToPlayerDecorator(AIBoard, behavior->behaviorSequence, value, name);
	}
	else if(decoName == "Chance")
	{
		customBehaviorSeq = new ChanceDecorator(AIBoard, behavior->behaviorSequence, name, value);
	}
	else
	{
		customBehaviorSeq = behavior->behaviorSequence;
	}

	((ParentTaskController*)AISelector->GetControl())->AddTask(customBehaviorSeq);

}

void BehaviorTree::AddBehavior(std::string nameOfBehavior, int priority)
{
	if (nameOfBehavior == "flee")
	{
		
	}
	else if (nameOfBehavior == "seek")
	{

	}
	else if (nameOfBehavior == "shoot")
	{

	}
	else if (nameOfBehavior == "idle")
	{

	}
	else
	{
		//Ignore as behavior DNE or is invalid
	}
}

void BehaviorTree::AddToBehaviorTree(Sequence* seq)
{
	((ParentTaskController*)AISelector->GetControl())->AddTask(seq);
}

void BehaviorTree::AddTaskToBehaviorTree(Tasks* task)
{
	((ParentTaskController*)AISelector->GetControl())->AddTask(task);
}

void BehaviorTree::AddBehaviorToBehaviorTree(Behavior* behaviorSeq)
{
	Tasks* behaviorSequence;

	if (behaviorSeq->GetConditionType() == "distance")
	{
		behaviorSequence = new CloseToPlayerDecorator(AIBoard, behaviorSeq->behaviorSequence, behaviorSeq->GetValue(), "Close To Player Decorator Sequence");
	}
	else if (behaviorSeq->GetConditionType() == "chance")
	{
		behaviorSequence = new ChanceDecorator(AIBoard, behaviorSeq->behaviorSequence,  "Chance Decorator Sequence", behaviorSeq->GetValue());
	}
	else
	{
		behaviorSequence = behaviorSeq->behaviorSequence;
	}

	
	((ParentTaskController*)AISelector->GetControl())->AddTask(behaviorSequence);

}


/// <summary>
/// Function to start traversing down the behavior tree
/// </summary>
void BehaviorTree::StartBehavior()
{
	//this->sLoggerInstance->Log("STARTING BEHAVIOR");
	GetPlayer->DoAction(); //Run task to get the player
	if (!((ParentTaskController*)AISelector->GetControl())->Started())
	{
		ResetBehavior();
		((ParentTaskController*)AISelector->GetControl())->SafeStart();
	}

	Active = true;
}

void BehaviorTree::StopBehavior()
{
	((ParentTaskController*)AISelector->GetControl())->SafeEnd();
	((ParentTaskController*)AISelector->GetControl())->Reset();

	Active = false;

}

/// <summary>
/// Function to reset the behavior tree to the root
/// </summary>
void BehaviorTree::ResetBehavior()
{
	((ParentTaskController*)AISelector->GetControl())->Reset();
	
	Active = false;
}

/// <summary>
/// Function to perform the task in the current node
/// </summary>
void BehaviorTree::DoBehavior()
{
	if (Active)
	{
		AISelector->DoAction();
	}

	if (AISelector->controller->currentTask == NULL)
	{
		ResetBehavior();
	}


}

void BehaviorTree::SetActive(bool activity)
{
	Active = activity;
}

bool BehaviorTree::GetActive()
{
	return Active;
}

bool BehaviorTree::CheckStarted()
{
	return ((ParentTaskController*)AISelector->GetControl())->Started();
}

bool BehaviorTree::CheckFinished()
{
	return ((ParentTaskController*)AISelector->GetControl())->Finished();
}

bool BehaviorTree::CheckFinishWithSuccess()
{
	return ((ParentTaskController*)AISelector->GetControl())->Succeeded();
}

bool BehaviorTree::CheckForFailure()
{
	return ((ParentTaskController*)AISelector->GetControl())->currentTask == nullptr;
}


