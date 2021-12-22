#pragma once
#include "include.hpp"

namespace network {
	std::string postRequest(std::string url, std::list<std::string> headers);

	int getRequest(std::string url);

	void sendWebHookMsg(std::string msg, const char* WEBHOOK);
}