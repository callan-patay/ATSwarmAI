#include "Tile.h"

Tile::Tile(int posx, int posy)
{

	m_pos.x = posx;
	m_pos.y = posy;

	m_worldMat = XMMatrixIdentity();
	m_worldMat = XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z);
	

	m_ownSize = 10;
	direction = XMFLOAT3(1.0f, -0.5f, 0.0f);
}

Tile::~Tile()
{
}

void Tile::init()
{




	
}

XMFLOAT3 Tile::getDirection()
{
	return direction;
}



void Tile::setDirection(XMFLOAT3 _dir)
{
	direction = _dir;
}

void Tile::setTarget(bool _targ)
{
	target = _targ;
}

void Tile::setObstacle(bool _obs)
{
	obstacle = _obs;
}

bool Tile::isTarget()
{
	return target;
}

bool Tile::isObstacle()
{
	return obstacle;
}

int Tile::getStamp()
{
	return stamp;
}

void Tile::setStamp(int _stmp)
{
	stamp = _stmp;
}
