#include "pch.h"
#include "MyGame.h"
#include "GameCamera.h"
#include "GameContext.h"
#include "Input.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

void MyGame::Initialize(GameContext& context)
{
	// デバッグカメラ作成
	m_pDebugCamera = std::make_unique<DebugCamera>();
	// グリッド床作成
	m_pGridFloor = std::make_unique<GridFloor>(context.GetDR().GetD3DDevice(), context.GetDR().GetD3DDeviceContext(), &context.GetStates(), 10.0f, 10);

	// カメラ
	context.GetCamera().view = Matrix::CreateLookAt(Vector3(0, 0, 5), Vector3::Zero, Vector3::Up);

	auto fxFactory = EffectFactory(context.GetDR().GetD3DDevice());
	fxFactory.SetDirectory(L"Resources/Models");
	m_model = DirectX::Model::CreateFromCMO(context.GetDR().GetD3DDevice(), L"Resources/Models/bone.cmo", fxFactory);

	Transform* lastTransform = nullptr;
	{
		auto transform = std::make_shared<Transform>();
		transform->parent = (lastTransform);
		m_transform.push_back(transform);
		lastTransform = transform.get();
	}
	{
		auto transform = std::make_shared<Transform>();
		transform->parent = (lastTransform);
		transform->localPosition = Vector3::Up;
		m_transform.push_back(transform);
		lastTransform = transform.get();
	}
	{
		auto transform = std::make_shared<Transform>();
		transform->parent = (lastTransform);
		transform->localPosition = Vector3::Up;
		m_transform.push_back(transform);
		lastTransform = transform.get();
	}
}

void MyGame::Update(GameContext& context)
{
	// 入力更新
	Input::Update();
	// デバッグカメラ更新
	m_pDebugCamera->update();
	context.GetCamera().view = m_pDebugCamera->getViewMatrix();

	// 回転
	float speed = 5.f * float(context.GetTimer().GetElapsedSeconds()) * 60.f;

	{
		if (Input::GetKey(Keyboard::Keys::W))
			m_transform[0]->localRotation *= Quaternion::CreateFromAxisAngle(Vector3::UnitX, XMConvertToRadians(-speed));
		if (Input::GetKey(Keyboard::Keys::S))
			m_transform[0]->localRotation *= Quaternion::CreateFromAxisAngle(Vector3::UnitX, XMConvertToRadians(speed));
		if (Input::GetKey(Keyboard::Keys::D))
			m_transform[0]->localRotation *= Quaternion::CreateFromAxisAngle(Vector3::UnitZ, XMConvertToRadians(-speed));
		if (Input::GetKey(Keyboard::Keys::A))
			m_transform[0]->localRotation *= Quaternion::CreateFromAxisAngle(Vector3::UnitZ, XMConvertToRadians(speed));
	}
	{
		if (Input::GetKey(Keyboard::Keys::Up))
			m_transform[1]->localRotation *= Quaternion::CreateFromAxisAngle(Vector3::UnitX, XMConvertToRadians(-speed));
		if (Input::GetKey(Keyboard::Keys::Down))
			m_transform[1]->localRotation *= Quaternion::CreateFromAxisAngle(Vector3::UnitX, XMConvertToRadians(speed));
		if (Input::GetKey(Keyboard::Keys::Right))
			m_transform[1]->localRotation *= Quaternion::CreateFromAxisAngle(Vector3::UnitZ, XMConvertToRadians(-speed));
		if (Input::GetKey(Keyboard::Keys::Left))
			m_transform[1]->localRotation *= Quaternion::CreateFromAxisAngle(Vector3::UnitZ, XMConvertToRadians(speed));
	}
	{
		if (Input::GetKey(Keyboard::Keys::I))
			m_transform[2]->localRotation *= Quaternion::CreateFromAxisAngle(Vector3::UnitX, XMConvertToRadians(-speed));
		if (Input::GetKey(Keyboard::Keys::K))
			m_transform[2]->localRotation *= Quaternion::CreateFromAxisAngle(Vector3::UnitX, XMConvertToRadians(speed));
		if (Input::GetKey(Keyboard::Keys::L))
			m_transform[2]->localRotation *= Quaternion::CreateFromAxisAngle(Vector3::UnitZ, XMConvertToRadians(-speed));
		if (Input::GetKey(Keyboard::Keys::J))
			m_transform[2]->localRotation *= Quaternion::CreateFromAxisAngle(Vector3::UnitZ, XMConvertToRadians(speed));
	}
}

void MyGame::Render(GameContext& context)
{
	auto ctx = context.GetDR().GetD3DDeviceContext();

	// グリッド床描画
	m_pGridFloor->draw(context.GetDR().GetD3DDeviceContext(), context.GetCamera().view, context.GetCamera().projection);

	for (auto& transform : m_transform)
		m_model->Draw(context.GetDR().GetD3DDeviceContext(), context.GetStates(), transform->GetMatrix(), context.GetCamera().view, context.GetCamera().projection);
}

void MyGame::Finalize(GameContext& context)
{

}
