#pragma once
#include "DebugCamera.h"
#include "GridFloor.h"
#include "Transform.h"

class GameContext;

class MyGame
{
	// �f�o�b�O�J����
	std::unique_ptr<DebugCamera>			m_pDebugCamera;
	// �O���b�h��
	std::unique_ptr<GridFloor>				m_pGridFloor;

	// �G�t�F�N�g
	//std::unique_ptr<DirectX::BasicEffect>	m_basicEffect;
	// �v���~�e�B�u�o�b�`
	std::unique_ptr<DirectX::Model>			m_model;
	// �C���v�b�g���C�A�E�g
	//Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;
	// Transform
	std::vector<std::shared_ptr<Transform>>	m_transform;

public:
	// ����
	void Initialize(GameContext& context);
	// �X�V
	void Update(GameContext& context);
	// �`��
	void Render(GameContext& context);
	// �j��
	void Finalize(GameContext& context);
};

