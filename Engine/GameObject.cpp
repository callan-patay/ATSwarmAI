#include "GameObject.h"
#include "modelclass.h"

GameObject::GameObject()
{
	model = 0;



	positionX = 0;
	positionY = 0;
	positionZ = 0;
}

GameObject::~GameObject()
{
	if (model)
	{
		delete model;
		model = 0;
	}


}

bool GameObject::Initialize(ID3D11Device * _device, ID3D11DeviceContext* deviceContext, char* textureFilename)
{
	bool result;


	model = new ModelClass();
	if (!model)
	{
		return false;
	}

	result = model->Initialize(_device, deviceContext, "../Engine/Textures/stone01.tga");
	return true;


}


void GameObject::SetPos(float x, float y, float z)
{
	positionX = x;
	positionY = y;
	positionZ = z;

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
	return positionX;
}

float GameObject::getPosY()
{
	return positionY;
}

float GameObject::getPosZ()
{
	return positionZ;
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

void GameObject::SetTargetPos(XMFLOAT3  targetPos)
{
	_targetPos = targetPos;
}

void GameObject::SetModel(ModelClass &_model)
{
	model = &_model;
}

ModelClass* GameObject::GetModel()
{
	return model;
}

void GameObject::Tick()
{










	if (_targetPos.x >= m_pos.x)
	{
		m_pos.x += 0.1;
	}
	else if (_targetPos.x <= m_pos.x)
	{
		m_pos.x -= 0.1;
	}


	if (_targetPos.x >= m_pos.y)
	{
		m_pos.y += 0.1;
	}
	else if (_targetPos.y <= m_pos.y)
	{
		m_pos.y -= 0.1;
	}






}

void GameObject::Render(ID3D11DeviceContext* _deviceContext, ID3D11Device* _device)
{
	if (m_alive)
	{
		model->InitializeBuffers(_device, m_pos);
		model->Render(_deviceContext);
	}
}


