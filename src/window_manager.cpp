#include "window_manager.h"
#include "application.h"

void WindowManager::StartUp() {
	ReportStartUp("Window Manager");
	current_window_ = Window::Create(*this, kWindowWidth, kWindowHeight);
}

const Window& WindowManager::GetCurrentWindow() {
	return *current_window_;
}

void WindowManager::ShutDown() {
	ReportShutDown("Window Manager");
}

void WindowManager::Update() {
	current_window_->Render();
}

void WindowManager::DestroyWindow() {
	delete current_window_;
	current_window_ = nullptr;
}