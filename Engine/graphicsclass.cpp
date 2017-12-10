#include "graphicsclass.h"
#include "GameObject.h"
#include "Tile.h"
#include "textureclass.h"

GraphicsClass::GraphicsClass()
{
	m_Direct3D = 0;
	m_Camera = 0;
	m_Model = 0;
	m_ColorShader = 0;
	m_TextureShader = 0;
	m_LightShader = 0;
	m_Light = 0;
}


GraphicsClass::GraphicsClass(const GraphicsClass& other)
{

}


GraphicsClass::~GraphicsClass()
{


}


bool GraphicsClass::Initialize(int screenWidth, int screenHeight, HWND hwnd)
{
	bool result;


	// Create the Direct3D object.
	m_Direct3D = new D3DClass;
	if (!m_Direct3D)
	{
		return false;
	}

	// Initialize the Direct3D object.
	result = m_Direct3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize Direct3D", L"Error", MB_OK);
		return false;
	}

	// Create the camera object.
	m_Camera = new CameraClass;
	if (!m_Camera)
	{
		return false;
	}

	// Set the initial position of the camera.
	m_Camera->SetPosition(147.3f, 147.3f, -372.0f);
	

	m_texture = new TextureClass();
	m_texture->Initialize(m_Direct3D->GetDevice(), m_Direct3D->GetDeviceContext(), "../Engine/Textures/kerrigan.tga");

	// Create the model object.
	m_Model = new ModelClass();
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	result = m_Model->Initialize(m_Direct3D->GetDevice());
	m_Model->SetTexture(m_texture);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	GameObject* objMass = 0;
	int posX = 0;
	int posY = 0;

	int row = 100;
	int col = 100;


	for (int r = 0; r < row; r++)
	{
		for (int c = 0; c < col; c++)
		{
			objMass = new GameObject();
			//objMass->Initialize(m_Direct3D->GetDevice(), m_Direct3D->GetDeviceContext(), "../Engine/Textures/stone01.tga");
	//		objMass->SetPos(posX, posY, 0.0f);
			objMass->SetTargetPos(m_Camera->GetPosition());
			//objMass->GetModel()->SetTexture(m_texture);
			m_gameObjects.push_back(objMass);
			posY += 1;
			
		}
		posY = 0;
		posX += 1;
	}



	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->setBoids(m_gameObjects);
	}

	m_Model->InitializeBuffers(m_Direct3D->GetDevice(), row, col, XMFLOAT3(0.0f, 0.0f, 0.0f));

	tileWidth = 30;
	tileHeight = 30;
	posX = 0;
	posY = 0;



	Tile* newTile = 0;

	for (int r = 0; r < tileHeight; r++)
	{
		for (int c = 0; c < tileWidth; c++)
		{
			newTile = new Tile(posX, posY);

			if (r + c * tileHeight == 13)
			{
				newTile->setTarget(true);
			}


			m_tiles.push_back(newTile);
			posX += 10;






		}
		posX = 0;
		posY += 10;
	}

	setVectors();

	// Create the light shader object.
	m_LightShader = new LightShaderClass;
	if (!m_LightShader)
	{
		return false;
	}

	// Initialize the light shader object.
	result = m_LightShader->Initialize(m_Direct3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the light shader object.", L"Error", MB_OK);
		return false;
	}

	// Create the light object.
	m_Light = new LightClass;
	if (!m_Light)
	{
		return false;
	}

	// Initialize the light object.
	m_Light->SetDiffuseColor(1.0f, 0.0f, 1.0f, 1.0f);
	m_Light->SetDirection(0.0f, 0.0f, 1.0f);

	// Create the texture shader object.
	m_TextureShader = new TextureShaderClass;
	if (!m_TextureShader)
	{
		return false;
	}

	// Initialize the color shader object.
	result = m_TextureShader->Initialize(m_Direct3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the color shader object.", L"Error", MB_OK);
		return false;
	}


	return true;
}


void GraphicsClass::Shutdown()
{
	// Release the color shader object.
	// Release the texture shader object.
	// Release the light object.
	if (m_Light)
	{
		delete m_Light;
		m_Light = 0;
	}

	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		//m_gameObjects[i]->GetModel()->Shutdown();
		delete m_gameObjects[i];
		m_gameObjects[i] = 0;
	}


	if (m_texture)
	{
		delete m_texture;
		m_texture = 0;
	}
	// Release the light shader object.
	if (m_LightShader)
	{
		m_LightShader->Shutdown();
		delete m_LightShader;
		m_LightShader = 0;
	}
	if (m_TextureShader)
	{
		m_TextureShader->Shutdown();
		delete m_TextureShader;
		m_TextureShader = 0;
	}
	if (m_ColorShader)
	{
		m_ColorShader->Shutdown();
		delete m_ColorShader;
		m_ColorShader = 0;
	}

	// Release the model object.

	// Release the camera object.
	if (m_Camera)
	{
		delete m_Camera;
		m_Camera = 0;
	}
	// Release the Direct3D object.
	if (m_Direct3D)
	{
		m_Direct3D->Shutdown();
		delete m_Direct3D;
		m_Direct3D = 0;
	}

	return;
}


bool GraphicsClass::Frame(float* deltaTime)
{
	bool result;
	static float rotation = 0.0f;

	Tick(deltaTime);


	// Update the rotation variable each frame.
	rotation += (float)XM_PI * 0.01f;
	if (rotation > 360.0f)
	{
		rotation -= 360.0f;
	}

	// Render the graphics scene.
	result = Render(rotation);
	if (!result)
	{
		return false;
	}

	return true;
}

void GraphicsClass::Tick(float* deltaTime)
{

	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		for (int t = 0; t < m_tiles.size(); t++)
		{
			if (checkColliding(m_gameObjects[i], m_tiles[t]))
			{
				m_gameObjects[i]->applyForce(m_tiles[t]->getDirection());
			}
		}





		m_gameObjects[i]->Tick(deltaTime);

		m_gameObjects[i]->SetTargetPos(m_Camera->GetPosition());
	}





	m_Model->updatePositions(m_Direct3D->GetDeviceContext(), m_gameObjects);
}

void GraphicsClass::moveCamera(float x, float y, float z)
{
	m_Camera->move(x, y, z);
}

bool GraphicsClass::checkColliding(GameObject * _gameObj, Tile * _tile)
{
	if ((_gameObj->getPos().x + _gameObj->getOwnSize()) >= _tile->getPos().x
		&& _gameObj->getPos().x <= (_tile->getPos().x + _tile->getOwnSize()))
	{
		//check both objects Y positions and size
		if ((_gameObj->getPos().y + _gameObj->getOwnSize()) >= _tile->getPos().y
			&& _gameObj->getPos().y <= (_tile->getPos().y + _tile->getOwnSize()))
		{
			return true;
		}
	}
	return false;
}

void GraphicsClass::setVectors()
{
	bool complete = false;
	int targetTile;
	int tilechecker = 0;
	for (int i = 0; i < m_tiles.size(); i++)
	{
		m_tiles[i]->setStamp(0);
	}


	for (int i = 0; i < m_tiles.size(); i++)
	{
		if (m_tiles[i]->isTarget())
		{
			targetTile = i;

			m_tiles[i + 1]->setStamp(1);
			m_tiles[i - 1]->setStamp(1);
			m_tiles[i + tileHeight]->setStamp(1);
			m_tiles[i - tileHeight]->setStamp(1);
		}
		
	}

	while (tilechecker != tileWidth * tileHeight)
	{


		for (int i = 0; i < m_tiles.size(); i++)
		{

				if (m_tiles[i + 1])
				{
					if (i + 1 != targetTile && m_tiles[i + 1]->getStamp() < m_tiles[i]->getStamp())
					{
						m_tiles[i + 1]->setStamp(m_tiles[i]->getStamp() + 1);
					}
				}

				if (m_tiles[i - 1])
				{
					if (i - 1 != targetTile && m_tiles[i - 1]->getStamp() < m_tiles[i]->getStamp())
					{
						m_tiles[i - 1]->setStamp(m_tiles[i]->getStamp() + 1);
					}
				}

				if (m_tiles[i + tileWidth])
				{
					if (i + tileWidth != targetTile && m_tiles[i + tileWidth]->getStamp() < m_tiles[i]->getStamp())
					{
						m_tiles[i + tileWidth]->setStamp(m_tiles[i]->getStamp() + 1);
					}
				}

				if (m_tiles[i - tileWidth])
				{
					if (i - tileWidth != targetTile && m_tiles[i - tileWidth]->getStamp() < m_tiles[i]->getStamp())
					{
						m_tiles[i - tileWidth]->setStamp(m_tiles[i]->getStamp() + 1);
					}
				}
		}



		for (int i = 0; i < m_tiles.size(); i++)
		{
			if (!m_tiles[i]->isTarget() && m_tiles[i]->getStamp() != 0)
			{
				tilechecker++;
			}
			else
			{
				tilechecker = 0;
			}
		}

		if (tilechecker == tileWidth * tileHeight -1)
		{
			complete = true;
		}

	}


	for (int i = 0; i < m_tiles.size(); i++)
	{

		if (m_tiles[i + 1])
		{
			if (m_tiles[i + 1]->getStamp() < m_tiles[i]->getStamp())
			{
				m_tiles[i]->setDirection(XMFLOAT3(1.0f, 0.0f, 0.0f));
			}

		}

		if (m_tiles[i - 1])
		{
			if (m_tiles[i - 1]->getStamp() < m_tiles[i]->getStamp())
			{
				m_tiles[i]->setDirection(XMFLOAT3(-1.0f, 0.0f, 0.0f));
			}

		}

		if (m_tiles[i + tileWidth])
		{
			if (m_tiles[i + tileWidth]->getStamp() < m_tiles[i]->getStamp())
			{
				m_tiles[i]->setDirection(XMFLOAT3(0.0f, 1.0f, 0.0f));
			}

		}

		if (m_tiles[i - tileWidth])
		{

			if (m_tiles[i - tileWidth]->getStamp() < m_tiles[i]->getStamp());
			{
				m_tiles[i]->setDirection(XMFLOAT3(0.0f, -1.0f, 0.0f));
			}


		}


	}









}


bool GraphicsClass::Render(float rotation)
{
	XMMATRIX worldMatrix, viewMatrix, projectionMatrix;
	bool result;


	// Clear the buffers to begin the scene.
	m_Direct3D->BeginScene(0.0f, 0.0f, 1.0f, 1.0f);

	// Generate the view matrix based on the camera's position.
	m_Camera->Render();

	// Get the world, view, and projection matrices from the camera and d3d objects.
	m_Direct3D->GetWorldMatrix(worldMatrix);
	m_Camera->GetViewMatrix(viewMatrix);
	m_Direct3D->GetProjectionMatrix(projectionMatrix);

	// Rotate the world matrix by the rotation value so that the triangle will spin.
	XMMatrixRotationY(rotation);
	m_Model->Render(m_Direct3D->GetDeviceContext());


	//for (auto& Tile : m_tiles)
	//{
	//	worldMatrix *= Tile->getWorldMat();
	//}
	// Render the model using the texture shader.
	result = m_TextureShader->Render(m_Direct3D->GetDeviceContext(), m_Model->GetVertexCount(), m_Model->GetInstanceCount(), worldMatrix, viewMatrix,
		projectionMatrix, m_Model->GetTexture());

	//for (int i = 0; i < m_gameObjects.size(); i++)
	//{
	//	m_gameObjects[i]->Render(m_Direct3D->GetDeviceContext(), m_Direct3D->GetDevice());
	//	result = m_LightShader->Render(m_Direct3D->GetDeviceContext(), m_gameObjects[i]->GetModel()->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
	//		m_gameObjects[i]->GetModel()->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
	//	if (!result)
	//	{
	//		return false;
	//	}

	//	result = m_TextureShader->Render(m_Direct3D->GetDeviceContext(), m_gameObjects[i]->GetModel()->GetIndexCount(), m_gameObjects[i]->GetModel()->GetInstanceCount(), worldMatrix, viewMatrix, projectionMatrix, m_gameObjects[i]->GetModel()->GetTexture());
	//	if (!result)
	//	{
	//		return false;
	//	}
	//}

	// Present the rendered scene to the screen.
	m_Direct3D->EndScene();


	return true;
}