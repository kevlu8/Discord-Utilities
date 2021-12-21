#pragma once
#include "include.hpp"

namespace network {
	std::string postRequest(std::string url, std::list<std::string> headers);

	std::string getRequest(std::string url, std::list<std::string> headers);

	void sendWebHookMsg(std::string msg, const char* WEBHOOK);
}