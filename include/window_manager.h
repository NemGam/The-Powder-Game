#pragma once
#include "manager_base.h"
#include "window.h"

constexpr int kWindowWidth = 800;
constexpr int kWindowHeight = 600;

class WindowManager : ManagerBase {
public:

private:
	
public:
	void ShutDown() override;
	void Update() override;
	void StartUp() override;
	const Window& GetCurrentWindow();
	void DestroyWindow();
private:

	Window* current_window_ = nullptr;
};
