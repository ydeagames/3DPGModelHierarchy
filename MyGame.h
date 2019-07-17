#pragma once
#include "DebugCamera.h"
#include "GridFloor.h"

class GameContext;

class MyGame
{
	// デバッグカメラ
	std::unique_ptr<DebugCamera>			m_pDebugCamera;
	// グリッド床
	std::unique_ptr<GridFloor>				m_pGridFloor;

	// エフェクト
	std::unique_ptr<DirectX::BasicEffect> m_basicEffect;
	// プリミティブバッチ
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColor>>	m_primitiveBatch;
	// インプットレイアウト
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;

public:
	// 生成
	void Initialize(GameContext& context);
	// 更新
	void Update(GameContext& context);
	// 描画
	void Render(GameContext& context);
	// 破棄
	void Finalize(GameContext& context);
};

