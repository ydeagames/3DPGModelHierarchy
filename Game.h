//
// Game.h
//

#pragma once

#include "DeviceResources.h"
#include "StepTimer.h"
#include "CommonStates.h"
#include "SimpleMath.h"
#include "Mouse.h"
#include "Keyboard.h"

class DebugCamera;
class GridFloor;

// A basic game implementation that creates a D3D11 device and
// provides a game loop.
class Game : public DX::IDeviceNotify
{
public:

	Game() noexcept(false);
	~Game();

	// Initialization and management
	void Initialize(HWND window, int width, int height);

	// Basic game loop
	void Tick();

	// IDeviceNotify
	virtual void OnDeviceLost() override;
	virtual void OnDeviceRestored() override;

	// Messages
	void OnActivated();
	void OnDeactivated();
	void OnSuspending();
	void OnResuming();
	void OnWindowMoved();
	void OnWindowSizeChanged(int width, int height);

	// Properties
	void GetDefaultSize(int& width, int& height) const;

private:

	void Update(DX::StepTimer const& timer);
	void Render();

	void Clear();

	void CreateDeviceDependentResources();
	void CreateWindowSizeDependentResources();

	// Device resources.
	std::unique_ptr<DX::DeviceResources>    m_deviceResources;

	// Rendering loop timer.
	DX::StepTimer                           m_timer;

	// 射影行列
	DirectX::SimpleMath::Matrix				m_projection;

	// マウス
	std::unique_ptr<DirectX::Mouse>			m_pMouse;

	// デバッグカメラ
	DebugCamera*							m_pDebugCamera;
	// グリッド床
	GridFloor*								m_pGridFloor;
	// コモンステート
	std::unique_ptr<DirectX::CommonStates>	m_pState;
};