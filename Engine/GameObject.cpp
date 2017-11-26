#include "GameObject.h"
#include "modelclass.h"

GameObject::GameObject()
{
	//model = 0;

	m_worldMat = XMMatrixIdentity();
	m_fudge = XMMatrixIdentity();

	m_scale = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_pos = XMFLOAT3(0.0f, 0.0f, 0.0f);
}

GameObject::~GameObject()
{
	/*if (model)
	{
		delete model;
		model = 0;
	}*/


}

bool GameObject::Initialize(ID3D11Device * _device, ID3D11DeviceContext* deviceContext, char* textureFilename)
{
	bool result;


//	model = new ModelClass();
	/*if (!model)
	{
		return false;
	}
*/
//	result = model->Initialize(_device);
	return true;


}


void GameObject::SetPos(float x, float y, float z)
{

	m_pos = XMFLOAT3(x, y, z);
}

void GameObject::SetRot(float _rot)
{
	m_rot = _rot;
}


void GameObject::SetYaw(float _yaw)
{
	m_yaw = _yaw;
}

void GameObject::SetPitch(float _pitch)
{
	m_pitch = _pitch;
}

void GameObject::SetRoll(float _roll)
{
	m_roll = _roll;
}

float GameObject::getPosX()
{
	return m_pos.x;
}

float GameObject::getPosY()
{
	return m_pos.y;
}

float GameObject::getPosZ()
{
	return m_pos.z;
}


float GameObject::GetRot()
{
	return m_rot;
}

float GameObject::GetYaw()
{
	return m_yaw;
}

float GameObject::GetPitch()
{
	return m_pitch;
}

float GameObject::GetRoll()
{
	return m_roll;
}

XMFLOAT3 GameObject::getPos()
{
	return m_pos;
}

void GameObject::SetTargetPos(XMFLOAT3  targetPos)
{
	_targetPos = targetPos;
}



void GameObject::Tick(float* deltaTime)
{



	//XMMATRIX scaleMat = XMMatrixScalingFromVector(m_scale);
	m_rotMat = XMMatrixRotationRollPitchYaw(m_yaw, m_pitch, m_roll);




	if (_targetPos.x >= m_pos.x)
	{
		m_pos.x += 2* *deltaTime;
	}
	if (_targetPos.x <= m_pos.x)
	{
		m_pos.x -= 2 * *deltaTime;
	}


	if (_targetPos.x >= m_pos.y)
	{
		m_pos.y += 2 * *deltaTime;
	}
	 if (_targetPos.y <= m_pos.y)
	{
		m_pos.y -= 2 * *deltaTime;
	}


	//m_pos.x += 0.2;



}

void GameObject::Render(ID3D11DeviceContext* _deviceContext, ID3D11Device* _device)
{
	if (m_alive)
	{
		//model->InitializeBuffers(_device, m_pos);
		//model->Render(_deviceContext);
	}
}


