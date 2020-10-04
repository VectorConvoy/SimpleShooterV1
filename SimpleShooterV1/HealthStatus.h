#pragma once
#define _HEALTHSTATUS_H

class HealthStatus
{
public:
	
	bool GetHealthLow() { return healthLow; }
	int GetHealth() { return health; }

private:
	int health;
	bool healthLow;
};