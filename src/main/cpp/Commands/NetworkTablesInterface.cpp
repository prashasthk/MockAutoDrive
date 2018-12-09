
#include "NetworkTablesInterface.h"
#include "NetworkTables/NetworkTableInstance.h"

bool NetworkTablesInterface::crossFound() {
	return nt::NetworkTableInstance::GetDefault().GetEntry("Entry Key").GetBoolean(false);
}
double NetworkTablesInterface::crossAzi() {
	return nt::NetworkTableInstance::GetDefault().GetEntry("Entry Key").GetDouble(-1);
}
bool NetworkTablesInterface::rectFound() {
	return nt::NetworkTableInstance::GetDefault().GetEntry("Entry Key").GetBoolean(false);
}
double NetworkTablesInterface::rectAzi() {
	return nt::NetworkTableInstance::GetDefault().GetEntry("Entry Key").GetDouble(-1);
}

