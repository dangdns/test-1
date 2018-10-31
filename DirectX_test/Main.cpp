#include "GameObject.h"
#include "Texture.h"
#include "Game.h"

#include "Simon.h"
#include "Candle.h"
#include "Whip.h"

#define WINDOW_CLASS_NAME L"SampleWindow"
#define MAIN_WINDOW_TITLE L"02 - Sprite animation"

#define BACKGROUND_COLOR D3DCOLOR_XRGB(200, 200, 255)
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240

#define MAX_FRAME_RATE 90

#define ID_TEX_SIMON 0
#define ID_TEX_ENEMY 10
#define ID_TEX_OBJ 20

CGame *game;
CSimon *simon;
CCandle *candle;

 int atkTick = 20, isAtk=0;
 vector<LPGAMEOBJECT> objects;

class CSample03KeyHander : public CKeyEventHandler
{
	virtual void KeyState(BYTE *states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
};

CSample03KeyHander * keyHandler;

void CSample03KeyHander::OnKeyDown(int KeyCode)
{
	/*DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);*/
	if (simon->GetState() != SIMON_STATE_JUMP)
		switch (KeyCode)
		{
		case DIK_SPACE:
			simon->SetState(SIMON_STATE_JUMP);
			break;
		/*case 90:
			simon->SetState(SIMON_STATE_ATTACK);
			break;*/
		/*case 29:
			mario->SetLevel(mario->GetLevel(), 1);*/
		}
}

void CSample03KeyHander::OnKeyUp(int KeyCode)
{
	/*DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);*/
}

void CSample03KeyHander::KeyState(BYTE *states)

{
	atkTick -= isAtk;
	if (atkTick==5)
	{
		Whip *whip = new Whip();

		whip->SetPosition(simon->GetX(), simon->GetY());
		whip->nx = simon->nx;
		objects.push_back(whip);
	}
	if (atkTick == 1)
	{
		objects.pop_back();
	}
	if ((atkTick == 20 || atkTick <= 0))
	{
		isAtk = 0;
		if (atkTick <= 0) atkTick = 20;

		//for (UINT i = 0; i < objects.size(); i++)
		//{
		//	LPGAMEOBJECT e = objects[i];

		//	if (dynamic_cast<CCandle *>(e))
		//	{
		//		//xoa whip di
		//	}
		//}
	}

	if (isAtk)return;
	if (game->IsKeyDown(DIK_RIGHT))
	{
		simon->SetState(SIMON_STATE_WALKING_RIGHT);
		OutputDebugString(L"down");
	}
	else if (game->IsKeyDown(DIK_LEFT))
		simon->SetState(SIMON_STATE_WALKING_LEFT);
	else /*if (simon->GetState() != SIMON_STATE_ATTACK)*/
	
		if (game->IsKeyDown(DIK_CAPSLOCK))
		{
			isAtk = 1;
			simon->SetState(SIMON_STATE_ATTACK);
		}
	
	else
		if (isAtk==0)
		{
			simon->SetState(SIMON_STATE_IDLE);
		}
	
	
		
}

LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

/*
Load all game resources
In this example: load textures, sprites, animations and mario object
*/
void LoadResources()
{
	CTextures * textures = CTextures::GetInstance();

	textures->Add(ID_TEX_SIMON, L"textures\\Simonx.png", D3DCOLOR_XRGB(0, 128, 128));
	textures->Add(ID_TEX_OBJ, L"textures\\Objects.png", D3DCOLOR_XRGB(34, 177, 76));

	CSprites * sprites = CSprites::GetInstance();
	CAnimations * animations = CAnimations::GetInstance();

	LPDIRECT3DTEXTURE9 texSimon = textures->Get(ID_TEX_SIMON);
	LPDIRECT3DTEXTURE9 texObj = textures->Get(ID_TEX_OBJ);

	sprites->Add(10001, 314, 4, 336, 40, texSimon);

	sprites->Add(10002, 290, 4, 304, 40, texSimon);
	sprites->Add(10003, 263, 4, 283, 40, texSimon);

	sprites->Add(10011, 494, 4, 514, 40, texSimon);

	sprites->Add(10012, 522, 4, 538, 40, texSimon);
	sprites->Add(10013, 548, 4, 569, 40, texSimon);

	sprites->Add(10021, 233, 11, 253, 40, texSimon);//jump right
	sprites->Add(10022, 577, 11, 596, 40, texSimon);//jump left

	sprites->Add(10031, 343, 89, 381, 123, texSimon); // atack right - stand
	sprites->Add(10032, 294, 89, 334, 123, texSimon);
	sprites->Add(10033, 230-14, 89, 283, 123, texSimon);

	sprites->Add(10034, 450, 89, 484, 123, texSimon); // atack left - stand
	sprites->Add(10035, 499, 89, 532, 123, texSimon);
	sprites->Add(10036, 549, 89, 595, 123, texSimon);


	LPANIMATION ani;

	ani = new CAnimation(100);
	ani->Add(10001);
	animations->Add(400, ani);

	ani = new CAnimation(100);
	ani->Add(10011);
	animations->Add(401, ani);

	//ani = new CAnimation(100);		//fire idle
	//ani->Add(20001);
	//animations->Add(700, ani);


	ani = new CAnimation(100);
	ani->Add(10001);
	ani->Add(10002);
	ani->Add(10003);
	animations->Add(500, ani);

	ani = new CAnimation(100);
	ani->Add(10011);
	ani->Add(10012);
	ani->Add(10013);
	animations->Add(501, ani);

	ani = new CAnimation(100);
	ani->Add(10021);
	animations->Add(601, ani);

	ani = new CAnimation(100);
	ani->Add(10022);
	animations->Add(602, ani);

	ani = new CAnimation(100);
	ani->Add(10031);
	ani->Add(10032);
	ani->Add(10033);
	animations->Add(701, ani);

	ani = new CAnimation(100);
	ani->Add(10034);
	ani->Add(10035);
	ani->Add(10036);
	animations->Add(702, ani);

	sprites->Add(20001, 16, 30, 25, 47, texObj);//candle 1
	sprites->Add(20002, 30, 30, 39, 47, texObj);//candle 2

	sprites->Add(20003, 47, 25, 64, 56, texObj);//candle big 1 (hien h tam thoi xai sprite nay vao code cua small candle de bao cao)
	sprites->Add(20004, 74, 23, 91, 56, texObj);//candle big 2

	ani = new CAnimation(100);
	ani->Add(20001);
	ani->Add(20002);
	animations->Add(2001, ani); // ani candle

	ani = new CAnimation(100);
	ani->Add(20003);
	ani->Add(20004);
	animations->Add(2002, ani); // ani candle big

	simon = new CSimon();
	simon->AddAnimation(400);		// idle right
	simon->AddAnimation(401);		// idle left
	simon->AddAnimation(500);		// walk right
	simon->AddAnimation(501);		// walk left
	simon->AddAnimation(601);		// jump right
	simon->AddAnimation(602);		// jump left
	simon->AddAnimation(701);		// attack right
	simon->AddAnimation(702);		// attack left
	objects.push_back(simon);




	for (int i = 1; i < 6; i++)
	{
		candle = new CCandle();
		candle->AddAnimation(2002);//xai tam (nt)
		candle->SetPosition(i*100.0f,100.0f);
		candle->SetState(CANDLE_STATE_ACTIVE);
		objects.push_back(candle);	

	

		///*candle = new CCandle();
		//candle->AddAnimation(601);
		//candle->SetPosition(100 + i*48.0f, 90);
		//objects.push_back(candle);

	//	candle = new CCandle();
	//	candle->AddAnimation(601);
	//	candle->SetPosition(84 + i*48.0f, 90);
	//	objects.push_back(candle);*/
	}

	simon->SetPosition(0.0f, 100.0f);
}

/*
Update world status for this frame
dt: time period between beginning of last frame and beginning of this frame
*/
void Update(DWORD dt)
{
	vector<LPGAMEOBJECT> coObjects;
	for (int i = 1; i < objects.size(); i++)
	{
		coObjects.push_back(objects[i]);
	}

	for (int i = 0; i < objects.size(); i++)
	{
		objects[i]->Update(dt, &coObjects);
	}
}

/*
Render a frame
*/
void Render()
{
	LPDIRECT3DDEVICE9 d3ddv = game->GetDirect3DDevice();
	LPDIRECT3DSURFACE9 bb = game->GetBackBuffer();
	LPD3DXSPRITE spriteHandler = game->GetSpriteHandler();

	if (d3ddv->BeginScene())
	{
		// Clear back buffer with a color
		d3ddv->ColorFill(bb, NULL, BACKGROUND_COLOR);

		spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);

		for (int i = 0; i < objects.size(); i++)
			objects[i]->Render();

		spriteHandler->End();
		d3ddv->EndScene();
	}

	// Display back buffer content to the screen
	d3ddv->Present(NULL, NULL, NULL, NULL);
}

HWND CreateGameWindow(HINSTANCE hInstance, int nCmdShow, int ScreenWidth, int ScreenHeight)
{
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hInstance = hInstance;

	wc.lpfnWndProc = (WNDPROC)WinProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hIcon = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = WINDOW_CLASS_NAME;
	wc.hIconSm = NULL;

	RegisterClassEx(&wc);

	HWND hWnd =
		CreateWindow(
			WINDOW_CLASS_NAME,
			MAIN_WINDOW_TITLE,
			WS_OVERLAPPEDWINDOW, // WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			ScreenWidth,
			ScreenHeight,
			NULL,
			NULL,
			hInstance,
			NULL);

	if (!hWnd)
	{
		OutputDebugString(L"[ERROR] CreateWindow failed");
		DWORD ErrCode = GetLastError();
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return hWnd;
}

int Run()
{
	MSG msg;
	int done = 0;
	DWORD frameStart = GetTickCount();
	DWORD tickPerFrame = 1000 / MAX_FRAME_RATE;

	while (!done)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) done = 1;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		DWORD now = GetTickCount();

		// dt: the time between (beginning of last frame) and now
		// this frame: the frame we are about to render
		DWORD dt = now - frameStart;

		if (dt >= tickPerFrame)
		{
			frameStart = now;

			game->ProcessKeyboard();

			Update(dt);
			Render();
		}
		else
			Sleep(tickPerFrame - dt);
	}

	return 1;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	HWND hWnd = CreateGameWindow(hInstance, nCmdShow, SCREEN_WIDTH, SCREEN_HEIGHT);

	game = CGame::GetInstance();
	game->Init(hWnd);

	keyHandler = new CSample03KeyHander();
	game->InitKeyboard(keyHandler);


	LoadResources();
	Run();

	return 0;
}