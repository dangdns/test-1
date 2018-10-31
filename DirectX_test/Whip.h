#pragma once
#include "GameObject.h"

#define VAMPIRE_KILLER	1
#define CHAIN_WHIP		2
#define MORNING_STAR	3

class Whip : public CGameObject
{
private:
	int type = VAMPIRE_KILLER;
	bool isActive;
	int vx = 0.01f;
	int vy = 0;

public:
	void Render() {};
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL);
	Whip();
	~Whip();
};
