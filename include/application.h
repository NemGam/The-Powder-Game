#pragma once

class Application {
public:
	static void Start();
	static void Quit();
	static bool IsRunning();

private:
	static bool is_running_;
};
