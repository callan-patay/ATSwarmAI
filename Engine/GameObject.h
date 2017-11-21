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


	bool Initialize(ID3D11Device*, ID3D11DeviceContext* deviceContext, char* textureFilename);
	void SetPos(float x, float y, float z);

	void SetRot(float _rot);
	void SetYaw(float _yaw);
	void SetPitch(float _pitch);
	void SetRoll(float _roll);

	float getPosX();
	float getPosY();
	float getPosZ();
	float GetRot();
	float GetYaw();
	float GetPitch();
	float GetRoll();


	void SetTargetPos(XMFLOAT3);


	//void SetModel(ModelClass&);
	//ModelClass* GetModel();


	virtual void Tick();
	virtual void Render(ID3D11DeviceContext*, ID3D11Device*);
private:
	float positionX, positionY, positionZ;
	XMFLOAT3 m_pos;
	//ModelClass* model;
	float m_yaw, m_pitch, m_roll, m_rot;
	bool m_alive;
	XMFLOAT3 _targetPos;
};