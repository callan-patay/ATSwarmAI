#pragma once
#include "GameObject.h"
#include <directxmath.h>
#include <d3d11.h>
using namespace DirectX;

class ModelClass;

class Tile : public GameObject
{
public:
	Tile(int posx, int posy);
	~Tile();



	void init();
	XMFLOAT3 getDirection();

	void setDirection(XMFLOAT3 _dir);
	void setTarget(bool _targ);
	void setObstacle(bool _obs);
	bool isTarget();
	bool isObstacle();
	int getStamp();
	void setStamp(int _stmp);



private:

	XMFLOAT3 direction;
	bool obstacle = false;
	bool target = false;
	int stamp = 0;


};