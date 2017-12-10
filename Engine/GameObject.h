#pragma once
#include <directxmath.h>
#include <d3d11.h>
#include <vector>
using namespace DirectX;


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
	XMMATRIX getWorldMat();
	XMFLOAT3 getPos();
	XMFLOAT3 getVel();
	float getOwnSize();

	void SetTargetPos(XMFLOAT3);

	XMFLOAT3 Seperation();
	XMFLOAT3 Alignment();
	XMFLOAT3 Cohesion();
	void applyForce(XMFLOAT3 _force);
	void flock();
	void Box();
	void setBoids(std::vector<GameObject*> _boids);
	float distance(XMFLOAT3 _pos, XMFLOAT3 _otherPos);
	//void SetModel(ModelClass&);
	//ModelClass* GetModel();


	virtual void Tick(float* deltaTime);
	virtual void Render(ID3D11DeviceContext*, ID3D11Device*);
protected:
	XMFLOAT3 m_pos, m_scale, m_vel, m_acc, m_drag;
	//ModelClass* model;
	float m_yaw, m_pitch, m_roll, m_rot;
	float m_size;
	float m_ownSize;
	bool m_alive;
	XMFLOAT3 _targetPos;
	float maxForce, minForce, maxSpeed, minSpeed;
	float neighbourDistance, seperation;
	float cohesionMultiplier, separationMultiplier, alignmentMultiplier;
	XMMATRIX m_worldMat, m_rotMat, m_fudge;

	std::vector<GameObject*> m_boids;
};