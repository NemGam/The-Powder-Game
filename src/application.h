#ifndef APPLICATION_H
#define APPLICATION_H

class Application {
public:
	static void Start();
	static void Quit();
	static bool IsRunning();

private:
	static bool is_running_;
};
#endif // APPLICATION_H
