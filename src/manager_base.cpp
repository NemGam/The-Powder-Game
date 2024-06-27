#include "manager_base.h"
#include <iostream>

void ManagerBase::ReportStartUp(const std::string& name) {
	std::cout << "Starting up " << name << "\n";
}

void ManagerBase::ReportShutDown(const std::string& name) {
	std::cout << "Shutting down " << name << "\n";
}

