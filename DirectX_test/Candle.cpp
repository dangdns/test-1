#include "Candle.h"

void CCandle::Render()
{
	/*int ani = */
	/*if (state == CANDLE_STATE_DIE)
		return;*/
	animations[0]->Render(x, y);
	//RenderBoundingBox();
}

void CCandle::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	/*l = x;
	t = y-6;
	r = x + CANDLE_BBOX_WIDTH;
	b = y + CANDLE_BBOX_HEIGHT;*/

	l = x;
	t = y - 15;
	r = x + BIGCANDLE_BBOX_WIDTH;
	b = y + BIGCANDLE_BBOX_HEIGHT;
}

void CCandle::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
}

void CCandle::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case CANDLE_STATE_ACTIVE:
		break;
	case CANDLE_STATE_DIE:
		break;
	
	}
}
