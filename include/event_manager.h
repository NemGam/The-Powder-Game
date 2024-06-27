#pragma once
#include <iostream>
#include "manager_base.h"
class EventManager : ManagerBase {
public:

	void StartUp() override;
	void Update() override;
	void ShutDown() override;

private:
};