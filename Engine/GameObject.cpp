#include "GameObject.h"
#include "modelclass.h"

GameObject::GameObject()
{
	model = 0;



	m_pos = XMFLOAT3(2.0f, 3.0f, 0.0f);
}

GameObject::~GameObject()
{
	if (model)
	{
		delete model;
		model = 0;
	}
}

void GameObject::SetPos(XMFLOAT3 _pos)
{
	m_pos = _pos;
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

XMFLOAT3 GameObject::GetPos()
{
	return m_pos;
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
	m_pos.x += 0.01;
}

void GameObject::Render(ID3D11DeviceContext* deviceContext)
{
	if (m_alive)
	{
		model->Render(deviceContext);
	}
}


