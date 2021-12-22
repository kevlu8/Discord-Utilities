#pragma once
#include "include.hpp"
#include "utilities.hpp"
#include "network.hpp"

namespace codes {
	void generateCodes(std::string filename = "NitroCodes.txt");

	void threadFriendlyGenerateCodes(std::string filename = "NitroCodes.txt");

	void checkCode(std::string filename = "NitroCodes.txt");

	void checkOneCode(std::string code, std::string user, bool webhook = true);

	void generateWhileCheck(bool sendWebhook = false, std::string user = "anonymous");
}