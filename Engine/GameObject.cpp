#include "GameObject.h"
#include "modelclass.h"

GameObject::GameObject()
{
	//model = 0;

	m_worldMat = XMMatrixIdentity();
	m_fudge = XMMatrixIdentity();

	m_scale = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_pos = XMFLOAT3(0.0f, 0.0f, 0.0f);

	maxForce = 0.3f;
	minForce = 0.0f;
	maxSpeed = 0.5f;
	minSpeed = 0.0f;
	neighbourDistance = 20.0f;
	seperation = 5.0f;
	alignmentMultiplier = 1.0f;
	separationMultiplier = 1.0f;
	cohesionMultiplier = 1.0f;

	m_size = 300;
	float angle = 0.1 + (rand() % (int)(359 - 0.1 + 1));
	m_pos = XMFLOAT3((float)(rand() % (int)m_size), (float)(rand() % (int)m_size), 0);
//	m_vel = XMFLOAT3(cos(angle), sin(angle), 0.0f);
	m_acc = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_ownSize = 1.0f;

}

GameObject::~GameObject()
{
	/*if (model)
	{
		delete model;
		model = 0;
	}*/

	for (int i = 0; i < m_boids.size(); i++)
	{
		m_boids[i] = nullptr;
	}


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

XMMATRIX GameObject::getWorldMat()
{
	return m_worldMat;
}

XMFLOAT3 GameObject::getPos()
{
	return m_pos;
}

XMFLOAT3 GameObject::getVel()
{
	return m_vel;
}

float GameObject::getOwnSize()
{
	return m_ownSize;
}

void GameObject::SetTargetPos(XMFLOAT3  targetPos)
{
	_targetPos = targetPos;
}

XMFLOAT3 GameObject::Seperation()
{
	return XMFLOAT3();
}

XMFLOAT3 GameObject::Alignment()
{
	XMFLOAT3 sum = XMFLOAT3(0.0f, 0.0f, 0.0f);
	

	int count = 0;


	for (int i = 0; i < m_boids.size(); i++)
	{
		float d = distance(m_pos, m_boids[i]->getPos());

		if ((d > 0) && (d < neighbourDistance))
		{
			sum = XMFLOAT3(sum.x += m_boids[i]->getVel().x, sum.y += m_boids[i]->getVel().y, sum.z += m_boids[i]->getVel().z);
			count++;
		}
	}




	if (count > 0)
	{
		sum = XMFLOAT3(sum.x /= (float)count, sum.y /= (float)count, sum.z /= (float)count);
		XMVECTOR v1 = XMLoadFloat3(&sum);
		XMVECTOR X = XMVector3Normalize(v1);
		XMStoreFloat3(&sum, X);

		XMFLOAT3 steer= XMFLOAT3(sum.x - m_vel.x, sum.y - m_vel.y, sum.z - m_vel.z);
		
		if (steer.x > maxForce)
		{
			steer.x = maxForce;
		}
		if (steer.y > maxForce)
		{
			steer.y = maxForce;
		}
		if (steer.z > maxForce)
		{
			steer.z = maxForce;
		}

		if (steer.x < minForce)
		{
			steer.x = minForce;
		}
		if (steer.y < minForce)
		{
			steer.y = minForce;
		}
		if (steer.z < minForce)
		{
			steer.z = minForce;
		}
		return steer;
	}
	else
	{
		return XMFLOAT3(0.0f, 0.0f, 0.0f);
	}
}

XMFLOAT3 GameObject::Cohesion()
{
	return XMFLOAT3();



	//for (int i = 0; i < m_boids.size(); i++)
	//{
	//	float d = 
	//}


}

void GameObject::applyForce(XMFLOAT3 _force)
{
	m_acc.x += _force.x;
	m_acc.y += _force.y;
	m_acc.z += _force.z;

	XMVECTOR v1 = XMLoadFloat3(&m_acc);
	XMVECTOR X = XMVector3ClampLength(v1, minSpeed, maxSpeed);
	XMStoreFloat3(&m_acc, X);

}

void GameObject::flock()
{

	XMFLOAT3 sep = Seperation();
	XMFLOAT3 ali = Alignment();
	XMFLOAT3 coh = Cohesion();


	//applyForce(sep);
	applyForce(ali);
	//applyForce(coh);
}

void GameObject::Box()
{
	if (m_pos.x < 0)
	{
		m_pos.x += m_size;
	}
	else if (m_pos.x > m_size)
	{
		m_pos.x -= m_size;
	}

	if (m_pos.y < 0)
	{
		m_pos.y += m_size;
	}
	else if (m_pos.y > m_size)
	{
		m_pos.y -= m_size;
	}


}

void GameObject::setBoids(std::vector<GameObject*> _boids)
{
	m_boids = _boids;
}

float GameObject::distance(XMFLOAT3 _pos, XMFLOAT3 _otherPos)
{
	float z_difference = _pos.z - _otherPos.z;
	float y_difference = _pos.y - _otherPos.y;
	float x_difference = _pos.x - _otherPos.x;
	return sqrt((z_difference* z_difference) + (y_difference * y_difference) + (x_difference*x_difference));
}



void GameObject::Tick(float* deltaTime)
{

	//flock();

	//m_acc.x *= *deltaTime;
	//m_acc.y *= *deltaTime;
	//m_acc.z *= *deltaTime;

	m_vel.x += m_acc.x * *deltaTime;
	m_vel.y += m_acc.y * *deltaTime;
	//m_vel.z += m_acc.z * *deltaTime;

		XMVECTOR v1 = XMLoadFloat3(&m_vel);
		XMVECTOR X = XMVector3ClampLength(v1, minSpeed, maxSpeed);
		XMStoreFloat3(&m_vel, X);

	m_pos.x += m_vel.x;
	m_pos.y += m_vel.y;
	//m_pos.z += m_vel.z;





	m_acc = XMFLOAT3(0.0f, 0.0f, 0.0f);
	Box();


}

void GameObject::Render(ID3D11DeviceContext* _deviceContext, ID3D11Device* _device)
{
	if (m_alive)
	{
		//model->InitializeBuffers(_device, m_pos);
		//model->Render(_deviceContext);
	}
}


