#pragma once
#define HEADER_FILE
#include "include.hpp"
#include "utilities.hpp"

namespace codes {
	void generateCodes(std::string filename = "NitroCodes.txt");

	void threadFriendlyGenerateCodes(std::string filename = "NitroCodes.txt");
}