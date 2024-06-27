#pragma once
#include <string>

class ManagerBase {
public:
	virtual void StartUp() = 0;
	virtual void Update() {}
	virtual void ShutDown() = 0;
protected:
	ManagerBase() = default;
	virtual ~ManagerBase() = default;

	//Reports the name of the manager that started initialization.
	void ReportStartUp(const std::string& name);

	//Reports the name of the manager that started deinitialization.
	void ReportShutDown(const std::string& name);
};
