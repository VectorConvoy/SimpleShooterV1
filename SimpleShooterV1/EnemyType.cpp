#include "EnemyType.h"
#include "BehaviorTree.h"
#include "Enemy.h"

EnemyType::EnemyType()
{
	speed = DEFAULT_SPEED;
	health = DEFAULT_HEALTH;
	maxBullets = DEFAULT_NUM_BULLETS;
	bulletSpeed = DEFAULT_BULLET_SPEED;

	ShipFileName = SHIP_NAME;
	DeathAnimationName = DEATH_ANIMATION;

	sLoggerInstance = Logger::Instance();
	XMLDocumentName = "TestBehaviorInputs.xml";

	LoadXML();

}

EnemyType::~EnemyType()
{
	//Not sure if necessary to delete 
	delete enemyOwner;
	enemyOwner = nullptr;

	delete decisionTree;
	decisionTree = nullptr;
}

void EnemyType::ConstructBehaviorTree()
{
	if (decisionTree != NULL)
	{
		delete decisionTree;
		decisionTree = NULL;
	}

	decisionTree = new BehaviorTree(enemyOwner);

	//debug
	//decisionTree->CreateBehaviorTree(BehaviorTree::BEHAVIOR_TYPES::sniper);

	

	decisionTree->ParseRoot(xmlDoc.child("Enemy"));

}

BehaviorTree* EnemyType::GetDecisionTree()
{
	return decisionTree;
}

void EnemyType::SetEnemyOwner(Enemy* enemyOwn)
{
	enemyOwner = enemyOwn;
}

Enemy* EnemyType::GetEnemyOwner()
{
	return enemyOwner;
}

void EnemyType::SetSpeed(float newSpeed)
{
	speed = newSpeed;
}

float EnemyType::GetSpeed()
{
	return speed;
}

void EnemyType::SetHealth(int newHealthVal)
{
	health = newHealthVal;
}

int EnemyType::GetHealth()
{
	return health;
}

void EnemyType::SetMaxBullets(int newMaxBullets)
{
	maxBullets = newMaxBullets;
}

int EnemyType::GetMaxBullets()
{
	return maxBullets;
}

void EnemyType::SetBulletSpeed(float newBulletSpeed)
{
	bulletSpeed = newBulletSpeed;
}

float EnemyType::GetBulletSpeed()
{
	return bulletSpeed;
}

void EnemyType::SetShipFile(std::string newName)
{
	ShipFileName = newName;
}

std::string EnemyType::GetShipFile()
{
	return ShipFileName;
}

void EnemyType::SetDeathAnimationName(std::string newName)
{
	DeathAnimationName = newName;
}

std::string EnemyType::GetDeathAnimationName()
{
	return DeathAnimationName;
}

void EnemyType::LoadXML()
{
	pugi::xml_parse_result parseResults = xmlDoc.load_file(XMLDocumentName.c_str());

	if (parseResults)
	{
		//Success, parse XML

		pugi::xml_node root = xmlDoc.child("Enemy");

		ShipFileName = root.child_value("ShipFile");
		speed = (float) atof(root.child_value("Speed"));
		bulletSpeed = (float) atof(root.child_value("BulletSpeed"));
		maxBullets = atoi(root.child_value("MaxBullets"));
	}
	else
	{
		//Failure
		sLoggerInstance->Log("FAILED TO LOAD XML\n");
	}

}
