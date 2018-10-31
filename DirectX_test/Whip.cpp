#include "Whip.h"

#include <algorithm>
#include "debug.h"

#include "Simon.h"
#include "Game.h"
#include "Candle.h"
void Whip::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	float x, y;
	this->GetPosition(x, y);
	if (this->nx > 0)
	{
		if (this->type == VAMPIRE_KILLER)
		{
			l = x + 23;
			t = y + 5;
			r = l + 33;
			b = t + 10;
		}
		else if (type == CHAIN_WHIP)
		{
			l = x + 23;
			t = y + 5;
			r = l + 33;
			b = t + 8;
		}
		else if (type == MORNING_STAR)
		{
			l = x + 23;
			t = y + 5;
			r = l + 41;
			b = t + 8;
		}
	}
	else
	{
		if (this->type == VAMPIRE_KILLER)
		{
			l = x ;
			t = y + 5;
			r = l - 33;
			b = t + 10;
		}
		else if (type == CHAIN_WHIP)
		{
			l = x;
			t = y + 5;
			r = l - 33;
			b = t + 8;
		}
		else if (type == MORNING_STAR)
		{
			l = x;
			t = y + 5;
			r = l - 41;
			b = t + 8;
		}
	}

}

void Whip::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

	// Calculate dx, dy (khuc nay lua tinh thoi)
	this->dx = 0.0f;
	this->dy = this->y;
	this->y = 0;
	this->dt = dt;

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	CalcPotentialCollisions(coObjects, coEvents);
	if (coEvents.size() != 0)
	{
		float min_tx, min_ty, nx = 0, ny;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			if (dynamic_cast<CCandle *>(e->obj))
			{
				CCandle *candle = dynamic_cast<CCandle *>(e->obj);
				if (candle->state == CANDLE_STATE_ACTIVE)
				{
					OutputDebugString(L"hit");
					candle->SetState(CANDLE_STATE_DIE);
					candle->SetPosition(-100, -100);
				}
			/*	e->obj->SetPosition(0,0);*/

			}
		}
	}
}

Whip::Whip()
{
	this->type = VAMPIRE_KILLER;
}

Whip::~Whip()
{
}
