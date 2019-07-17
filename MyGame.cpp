#include "pch.h"
#include "MyGame.h"
#include "GameCamera.h"
#include "GameContext.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

void MyGame::Initialize(GameContext& context)
{
	// �f�o�b�O�J�����쐬
	m_pDebugCamera = std::make_unique<DebugCamera>();
	// �O���b�h���쐬
	m_pGridFloor = std::make_unique<GridFloor>(context.GetDR().GetD3DDevice(), context.GetDR().GetD3DDeviceContext(), &context.GetStates(), 10.0f, 10);

	// �J����
	context.GetCamera().view = Matrix::CreateLookAt(Vector3(0, 0, 5), Vector3::Zero, Vector3::Up);

	// �G�t�F�N�g�̐���
	m_basicEffect = std::make_unique<DirectX::BasicEffect>(context.GetDR().GetD3DDevice());
	// ���_�J���[(�L��)
	m_basicEffect->SetVertexColorEnabled(true);
	// �v���~�e�B�u�I�u�W�F�N�g����
	m_primitiveBatch = std::make_unique<DirectX::PrimitiveBatch<DirectX::VertexPositionColor>>(context.GetDR().GetD3DDeviceContext());
	// �C���v�b�g���C�A�E�g����
	void const* shaderByteCode;
	size_t byteCodeLength;
	m_basicEffect->GetVertexShaderBytecode(&shaderByteCode, &byteCodeLength);
	context.GetDR().GetD3DDevice()->CreateInputLayout(DirectX::VertexPositionColor::InputElements,
		DirectX::VertexPositionColor::InputElementCount,
		shaderByteCode, byteCodeLength,
		m_inputLayout.GetAddressOf());
}

void MyGame::Update(GameContext& context)
{
	// �f�o�b�O�J�����X�V
	m_pDebugCamera->update();
	context.GetCamera().view = m_pDebugCamera->getViewMatrix();
}

void MyGame::Render(GameContext& context)
{
	auto ctx = context.GetDR().GetD3DDeviceContext();

	// �O���b�h���`��
	//m_pGridFloor->draw(context.GetDR().GetD3DDeviceContext(), context.GetCamera().view, context.GetCamera().projection);

	ctx->OMSetBlendState(context.GetStates().Opaque(), nullptr, 0xFFFFFFFF);
	ctx->OMSetDepthStencilState(context.GetStates().DepthDefault(), 0);

	m_basicEffect->SetWorld(Matrix::Identity);
	m_basicEffect->SetView(context.GetCamera().view);
	m_basicEffect->SetProjection(context.GetCamera().projection);

	m_basicEffect->Apply(ctx);
	ctx->IASetInputLayout(m_inputLayout.Get());

	// �`��
	m_primitiveBatch->Begin();
	m_primitiveBatch->DrawTriangle(
		VertexPositionColor(Vector3::Transform(Vector3::Up, Matrix::CreateRotationZ(-XM_2PI / 3 * 0)), Colors::White),
		VertexPositionColor(Vector3::Transform(Vector3::Up, Matrix::CreateRotationZ(-XM_2PI / 3 * 1)), Colors::White),
		VertexPositionColor(Vector3::Transform(Vector3::Up, Matrix::CreateRotationZ(-XM_2PI / 3 * 2)), Colors::White));
	m_primitiveBatch->End();
}

void MyGame::Finalize(GameContext& context)
{

}
