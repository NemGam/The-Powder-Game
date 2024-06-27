#include "application.h"
#include <iostream>

bool Application::is_running_;

void Application::Start() {
	is_running_ = true;
}

bool Application::IsRunning() {
	return is_running_;
}


void Application::Quit() {
	std::cout << "Quitting\n";
	is_running_ = false;
}
