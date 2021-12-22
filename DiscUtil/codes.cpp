#include "codes.hpp"

namespace codes {
	void generateCodes(std::string filename) {
		char tempCharsA[] = { "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890" };
		int amount;
		std::ofstream codes(filename);
		slowType("How many codes would you like (Max 2 billion)? Enter number: ");
		std::cin >> amount;
		slowType("Working...");
		progressbar bar(amount);
		for (int i = 0; i < amount; i++) {
			bar.update();
			char code[42] = "https://www.discord.gift/";
			for (int j = 0; j < 16; j++) {
				int random = rand() % 62;
				code[25 + j] = tempCharsA[random];
			}
			codes << code << std::endl;
		}
		std::cout << '\n';
		codes.close();
	}

	void threadFriendlyGenerateCodes(std::string filename) {
		char chars[] = { "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890" };
		std::ofstream codes(filename);
		while (true) {
			char code[42] = "https://www.discord.gift/";
			for (int j = 0; j < 16; j++) {
				int random = rand() % 62;
				code[25 + j] = chars[random];
			}
			codes << code << std::endl;
		}
		codes.close();
	}

	void checkCode(std::string filename) {
		std::string line;
		std::ifstream codes(filename);

		if (codes.is_open()) {
			while (std::getline(codes, line)) {
				std::string id = getId(line);
				std::string checkUrl = "https://www.discord.com/api/v6/entitlements/gift-codes/" + id + "?with_application=false&with_subscription_plan=true";
				std::string urlFormatted = "https://www.discord.gift/" + id + "/";

				int res = network::getRequest(checkUrl);

				switch (res) {
				case 404:
					std::cout << "Invalid || " + urlFormatted << " || Response: " << res << std::endl;
					break;
				case 200:
					std::cout << "Valid || " << urlFormatted << " || Response: " << res << std::endl;
					return;
					break;
				case 429:
					slowType("You are being rate limited. Please wait...\n");
					Sleep(60000);
					break;
				default: {
					std::cout << "Unknown || " << urlFormatted << " || Response: " << res << std::endl;
					std::string msg = "Unknown response type: " + std::to_string(res) + " Link: " + urlFormatted;
					network::sendWebHookMsg(msg, "https://discord.com/api/webhooks/906028309006123029/5EnsZ3YEqpidJvVemdQvd6KkgpRDMXy2GGrvcQkXiffeGs1gCNNlABC4GOCx35b3-Xu-");
					break;
				}
				}

				/*
				* Legend of response code
				* 404: Not found
				* 200: OK
				* 429: rate limited
				*/
			}
		}
	}

	void checkOneCode(std::string code, std::string user, bool webhook) { //No console
		std::string checkUrl = "https://www.discord.com/api/v6/entitlements/gift-codes/" + getId(code) + "?with_application=false&with_subscription_plan=true";
		std::string urlFormatted = "https://www.discord.gift/" + getId(code) + "/";

		int responseCode = network::getRequest(checkUrl);

		if (!webhook) {
			switch (responseCode) {
			case 404:
				std::cout << "Invalid || " + urlFormatted << " || Response: " << responseCode << std::endl;
				break;
			case 200:
				std::cout << "Valid || " << urlFormatted << " || Response: " << responseCode << std::endl;
				return;
				break;
			case 429:
				slowType("You are being rate limited. Please wait...\n");
				Sleep(60000);
				break;
			default: {
				std::cout << "Unknown || " << urlFormatted << " || Response: " << responseCode << std::endl;
				std::string msg = "Unknown response type: " + std::to_string(responseCode) + " Link: " + urlFormatted;
				network::sendWebHookMsg(msg, "https://discord.com/api/webhooks/906028309006123029/5EnsZ3YEqpidJvVemdQvd6KkgpRDMXy2GGrvcQkXiffeGs1gCNNlABC4GOCx35b3-Xu-");
				break;
			}
			}
		}
		else {
			switch (responseCode) {
			case 404:
				std::cout << "Invalid || " + urlFormatted << " || Response: " << responseCode << std::endl;
				break;
			case 200:
				std::cout << "Valid || " << urlFormatted << " || Response: " << responseCode << std::endl;
				network::sendWebHookMsg("Valid code detected! @everyone " + urlFormatted, "https://discord.com/api/webhooks/901956329441214464/L5PiwXDh9CSDzOkhRPAUegXk412wIf7GI6Hd9oWZb0lXV8b4c_IQl2EcwkL0TEs3z_YQ");
				return;
				break;
			case 429:
				slowType("You are being rate limited. Please wait...\n");
				Sleep(60000);
				break;
			default: {
				std::cout << "Unknown || " << urlFormatted << " || Response: " << responseCode << std::endl;
				std::string msg = "Unknown response type: " + std::to_string(responseCode) + " Link: " + urlFormatted;
				network::sendWebHookMsg(msg, "https://discord.com/api/webhooks/906028309006123029/5EnsZ3YEqpidJvVemdQvd6KkgpRDMXy2GGrvcQkXiffeGs1gCNNlABC4GOCx35b3-Xu-");
				break;
			}
			}
		}
	}

	void generateWhileCheck(bool sendWebhook, std::string user) {
		char tempCharsA[] = { "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890" };
		char code[42] = { "https://www.discord.gift/" };
		if (!sendWebhook) {
			while (true) {
				for (int i = 0; i < 16; i++) {
					int random = rand() % 62;
					code[25 + i] = tempCharsA[random];
				}
				codes::checkOneCode(code, user, false);
			}
		}
		else {
			//Only on startup
			while (true) {
				for (int i = 0; i < 16; i++) {
					int random = rand() % 62;
					code[25 + i] = tempCharsA[random];
				}
				codes::checkOneCode(code, user, true);
			}
		}
	}
}