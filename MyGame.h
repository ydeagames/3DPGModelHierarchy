#pragma once
#include "DebugCamera.h"
#include "GridFloor.h"

class GameContext;

class MyGame
{
	// �f�o�b�O�J����
	std::unique_ptr<DebugCamera>			m_pDebugCamera;
	// �O���b�h��
	std::unique_ptr<GridFloor>				m_pGridFloor;

	// �G�t�F�N�g
	std::unique_ptr<DirectX::BasicEffect> m_basicEffect;
	// �v���~�e�B�u�o�b�`
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColor>>	m_primitiveBatch;
	// �C���v�b�g���C�A�E�g
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;

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

