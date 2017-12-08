#include "Tile.h"

Tile::Tile(int posx, int posy)
{

	m_pos.x = posx;
	m_pos.y = posy;

	m_worldMat = XMMatrixIdentity();
	m_worldMat = XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z);
	
	size = XMFLOAT2(10.0f, 10.0f);
	direction = XMFLOAT3(0.0f, 0.0f, 0.0f);
}

Tile::~Tile()
{
}

void Tile::init()
{




	
}
