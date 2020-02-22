//======================================================
// File Name	:Game.h
// Summary	: ゲーム
// Author		: Kyoya Sakamoto
//======================================================
#pragma once

#include <CommonStates.h>
#include <SimpleMath.h>
#include <SpriteBatch.h>
#include <Keyboard.h>
#include <Mouse.h>

#include "DeviceResources.h"
#include "StepTimer.h"
#include <Utils\Projection.h>


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
    void GetDefaultSize( int& width, int& height ) const;
	void ChangeFullscreen(BOOL flag);

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
	std::unique_ptr<Projection>             m_projection;
	// コモンステート
	std::unique_ptr<DirectX::CommonStates>	m_state;
	//スプライトバッチ
	std::unique_ptr<DirectX::SpriteBatch>   m_spriteBatch;
	// マウス
	std::unique_ptr<DirectX::Mouse>			m_mouse;
	//キーボード
	std::unique_ptr<DirectX::Keyboard>      m_keyboard;

};