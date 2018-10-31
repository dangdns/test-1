#include "Simon.h"
#include <algorithm>
#include "debug.h"
#include "Game.h"

void CSimon::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	CGameObject::Update(dt);

	// simple JUMP

	vy += SIMON_GRAVITY;
	if (y > 100)
	{
		vy = 0; y = 100.0f;
	}
	x += vx;
	y += vy;

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	////// turn off collision when die 
	////if (state != SIMON_STATE_DIE)
	//	CalcPotentialCollisions(coObjects, coEvents);

	////// reset untouchable timer if untouchable time has passed
	////if (GetTickCount() - untouchable_start > SIMON_UNTOUCHABLE_TIME)
	////{
	////	untouchable_start = 0;
	////	untouchable = 0;
	////}

	//// No collision occured, proceed normally
	//if (coEvents.size() == 0)
	//{
	//	/*x += dx;
	//	y += dy;*/
	//	x += vx;
	//	y += vy;
	//}
	//else
	//{
	//	float min_tx, min_ty, nx = 0, ny;

	//	FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

	//	// block 
	//	x += min_tx*vx + nx*0.1f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
	//	y += min_ty*vy + ny*0.1f;

	//	if (nx != 0) vx = 0;
	//	if (ny != 0) vy = 0;


	//}

	//// clean up collision events
	//for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];

	 /*simple screen edge collision!!!*/
	if (vx > 0 && x > 280) x = 280;
	if (vx < 0 && x < 0) x = 0;
}

void CSimon::Render()
{
	int ani;
	if (this->GetState() == SIMON_STATE_ATTACK)
	{
		if (nx > 0)
			ani = SIMON_ANI_ATTACK_RIGHT;
		else ani = SIMON_ANI_ATTACK_LEFT;
	}
		
	else
	if (y != 100) {
		if (nx > 0) ani = SIMON_ANI_JUMPING_RIGHT;
		else ani = SIMON_ANI_JUMPING_LEFT;
	}
	else
		if (vx == 0)
		{	
				if (nx > 0) ani = SIMON_ANI_IDLE_RIGHT;
				else ani = SIMON_ANI_IDLE_LEFT;
			
		}
		else
			if (nx >0)
				ani = SIMON_ANI_WALKING_RIGHT;
			else ani = SIMON_ANI_WALKING_LEFT;

			if (this->GetState() == SIMON_STATE_ATTACK)
			{
				if (nx > 0)
					animations[ani]->Render(x - 14, y);
				else animations[ani]->Render(x, y);
			}
			else
			{
				animations[ani]->Render(x, y);
			}
			/*this->animations.at(3)->*/
}

void CSimon::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case SIMON_STATE_WALKING_RIGHT:
		vx = SIMON_WALKING_SPEED;
		nx = 1;
		break;
	case SIMON_STATE_WALKING_LEFT:
		vx = -SIMON_WALKING_SPEED;
		nx = -1;
		break;
	case SIMON_STATE_JUMP:
		vy = -SIMON_JUMP_SPEED_Y;

	case SIMON_STATE_IDLE:
	case SIMON_STATE_ATTACK:
		vx = 0;
		break;
	}
}
void CSimon::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y;

	if (stand)
	{
		right = x + SIMON_STAND_BBOX_WIDTH;
		bottom = y + SIMON_STAND_BBOX_HEIGHT;
	}
	else
	{
		right = x + SIMON_CROUCH_BBOX_WIDTH;
		bottom = y + SIMON_CROUCH_BBOX_HEIGHT;
	}
}
void CSimon::SetLevel(int level, int effect)
{
}
