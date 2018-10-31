#pragma once
#include "GameObject.h"

#define SIMON_WALKING_SPEED 0.5f
#define SIMON_JUMP_SPEED_X	1.0f
#define SIMON_JUMP_SPEED_Y	0.7f
#define SIMON_GRAVITY		0.1f
#define SIMON_JUMP_DEFLECT_SPEED 0.2f


#define SIMON_STATE_IDLE			0
#define SIMON_STATE_WALKING_RIGHT	100
#define SIMON_STATE_WALKING_LEFT	200
#define SIMON_STATE_JUMP			300
#define SIMON_STATE_ATTACK			400
#define SIMON_STATE_DIE			500

#define SIMON_ANI_IDLE_RIGHT	0
#define SIMON_ANI_IDLE_LEFT		1
#define SIMON_ANI_WALKING_RIGHT		2
#define SIMON_ANI_WALKING_LEFT		3
#define SIMON_ANI_JUMPING_RIGHT		4
#define SIMON_ANI_JUMPING_LEFT		5
#define SIMON_ANI_ATTACK_RIGHT		6
#define SIMON_ANI_ATTACK_LEFT		7


#define SIMON_STAND_BBOX_WIDTH  16
#define SIMON_STAND_BBOX_HEIGHT 31

#define SIMON_CROUCH_BBOX_WIDTH  16
#define SIMON_CROUCH_BBOX_HEIGHT 24

#define SIMON_UNTOUCHABLE_TIME 5000

class CSimon : public CGameObject
{
	int level;
	int untouchable;//
	DWORD untouchable_start;//
	int stand = 1;
public:
	CSimon() : CGameObject()//
	{
		level = 1;
		untouchable = 0;
	}
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL);
	void Render();
	int GetLevel() { return level; }

	void SetState(int state);
	void SetLevel(int level, int effect);
	float GetY() { return this->y; };
	float GetX() { return this->x; };
	float GetVY()
	{
		return this->vy;
	}

	int GetState()
	{
		return this->state;
	}
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount(); }//

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);//
};