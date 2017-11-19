#pragma once
#include <directxmath.h>
#include <d3d11.h>
using namespace DirectX;

class ModelClass;

class GameObject
{
public:
	GameObject();
	~GameObject();

	void SetPos(XMFLOAT3 _pos);
	void SetPos(float x, float y, float z);

	void SetRot(float _rot);
	void SetYaw(float _yaw);
	void SetPitch(float _pitch);
	void SetRoll(float _roll);

	XMFLOAT3 GetPos();
	float GetRot();
	float GetYaw();
	float GetPitch();
	float GetRoll();


	void SetModel(ModelClass&);
	ModelClass* GetModel();


	virtual void Tick();
	virtual void Render(ID3D11DeviceContext*);
private:
	XMFLOAT3 m_pos;
	ModelClass* model;
	float m_yaw, m_pitch, m_roll, m_rot;
	bool m_alive;

};