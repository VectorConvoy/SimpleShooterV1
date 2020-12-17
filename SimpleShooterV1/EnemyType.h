/*
* Object to store constants and data
* to create a specific type of enemy
*/
#pragma once
#define _ENEMYTYPE_H

#include <string>
#include <vector>
#include <pugixml.hpp>
#include "Logger.h"

class Enemy;
class BehaviorTree;

class EnemyType
{
public:

	const std::vector<std::string> PossibleTypes = {"FleeEnemy.xml", "SeekEnemy.xml", "SeekFleeShootEnemy.xml", "SeekShootEnemy.xml" };
	//const std::vector<std::string> PossibleTypes = { "FleeEnemy.xml", "SeekEnemy.xml", "SeekFleeShootEnemy.xml"};

	EnemyType();
	~EnemyType();

	void ConstructBehaviorTree();
	BehaviorTree* GetDecisionTree();

	void SetEnemyOwner(Enemy* enemyOwn);
	Enemy* GetEnemyOwner();

	void SetSpeed(float newSpeed);
	float GetSpeed();

	void SetHealth(int newHealthVal);
	int GetHealth();

	void SetMaxBullets(int newMaxBullets);
	int GetMaxBullets();

	void SetBulletSpeed(float newBulletSpeed);
	float GetBulletSpeed();

	void SetShipFile(std::string newName);
	std::string GetShipFile();

	void SetDeathAnimationName(std::string newName);
	std::string GetDeathAnimationName();

	void LoadXML();
	

private:

	const float DEFAULT_SPEED = 50.0f;
	const int DEFAULT_HEALTH = 1;
	const int DEFAULT_NUM_BULLETS = 3;
	const float DEFAULT_BULLET_SPEED = 500.0f;
	const std::string DEFAULT_SHIP_FILE = "enemyship1.png";
	const std::string DEATH_ANIMATION = "ship_explosion.png";

	float speed;
	float bulletSpeed;
	int health;

	int maxBullets; 

	Logger* sLoggerInstance;

	Enemy* enemyOwner; //Enemy object that owns this object instance

	BehaviorTree* decisionTree;

	std::string XMLDocumentName;

	std::string ShipFileName;

	std::string DeathAnimationName;

	pugi::xml_document xmlDoc;


};