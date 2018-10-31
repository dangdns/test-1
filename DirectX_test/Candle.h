#pragma once
#include "GameObject.h"

#define CANDLE_BBOX_WIDTH  8
#define CANDLE_BBOX_HEIGHT 11

#define BIGCANDLE_BBOX_WIDTH  16
#define BIGCANDLE_BBOX_HEIGHT 17

#define CANDLE_STATE_ACTIVE 100
#define CANDLE_STATE_DIE 200
class CCandle : public CGameObject
{
public:
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void SetState(int state);
};
