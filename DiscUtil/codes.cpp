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
			char code[] = "https://www.discord.gift/";
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
			char code[] = "https://www.discord.gift/";
			for (int j = 0; j < 16; j++) {
				int random = rand() % 62;
				code[25 + j] = chars[random];
			}
			codes << code << std::endl;
		}
		codes.close();
	}
}