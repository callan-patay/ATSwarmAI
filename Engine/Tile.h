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







private:
	XMFLOAT2 size;
	XMFLOAT3 direction;





};