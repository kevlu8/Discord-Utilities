#include "network.hpp"

namespace network {
	//Send POST request to given URL with given headers
	std::string postRequest(std::string url, std::list<std::string> headers) {
		std::stringstream response;
		try {
			//Create a request
			curlpp::Cleanup myCleanup;
			curlpp::Easy myRequest;
			myRequest.setOpt(new curlpp::options::Url(url));
			myRequest.setOpt(new curlpp::options::HttpHeader(headers));
			myRequest.setOpt(new curlpp::options::PostFieldSize(0));
			myRequest.setOpt(new curlpp::options::WriteStream(&response));
			myRequest.perform();
		}
		catch (curlpp::LogicError& e) {
			std::cout << "Logic error: " << e.what() << std::endl;
		}
		catch (curlpp::RuntimeError& e) {
			std::cout << "Runtime error: " << e.what() << std::endl;
		}
		catch (std::exception& e) {
			std::cout << "General error: " << e.what() << std::endl;
		}
		return response.str();
	}

	//Send GET request to given URL
	std::string getRequest(std::string url, std::list<std::string> headers) {
		cpr::Response res = cpr::Get(cpr::Url{url})
	}

	void sendWebHookMsg(std::string msg, const char* WEBHOOK) {
		CURL* curl;
		CURLcode res;
		curl_global_init(CURL_GLOBAL_ALL);
		curl = curl_easy_init();
		if (curl) {
			std::string combine = "content=";
			combine += msg;
			const char* postContent = combine.c_str();
			curl_easy_setopt(curl, CURLOPT_URL, WEBHOOK);
			curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postContent);

			res = curl_easy_perform(curl);

			if (res != CURLE_OK) {
				fprintf(stderr, "cURL failed to perform POST, are you connected to the internet? Error: %s\n", curl_easy_strerror(res));
			}

			curl_easy_cleanup(curl);
		}
		curl_global_cleanup();
	}
}