#include "include.hpp"
#include "network.hpp"
#include "utilities.hpp"
#include "codes.hpp"

int main(int argc, char* argv[]) {
	std::string fileName;
	std::ifstream lic("license.dat");
	if (argc == 2 && strcmp(argv[1], "--startup") == 0) {
		std::string user;
		std::string line; 
		std::ifstream settings("settings");
		if (settings.is_open()) {
			while (getline(settings, line)) {
				user = line;
			}
		}
		else {
			slowType("You haven't ran [8] yet, or you have corrupted something!\n");
			goto exit; //Pls no kill for bad practice
		}
		codes::generateWhileCheck(true, user);
	}
	SetConsoleTitle(L"kevlu8's Discord Utilities");
	SetPriorityClass(GetCurrentProcess(), HIGH_PRIORITY_CLASS);
	//options
	int sel;
	changeColor(7);
	slowType("The source code of this program is available at https://www.github.com/kevlu8/Discord-Utilities.\n");
	if (lic.is_open()) { lic.close(); } //worst license checking EVER!!!
	else {
		if (MessageBoxW(NULL, L"Do you agree to the license agreement that can be found on GitHub?", L"License", MB_ICONQUESTION | MB_YESNO | MB_DEFBUTTON1) == IDNO) return 0;
		else { std::ofstream licensefile("license.dat"); licensefile << "true"; licensefile.close(); }
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
	slowType("WARNING: [4] is still in development.\n");
	changeColor(7);
	slowType("---------------------------------------\n");
	std::cout << "Enter option: ";
	std::cin >> sel;

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
		codes::checkCode(fileName);
		break;
	case 3:
		codes::generateWhileCheck();
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
		std::cout << "This function is an infinite loop. Once you feel that you have generated enough, press control+C to stop the program.";
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
		std::ofstream settings("settings");
		settings << user << std::endl;
		settings.close();
		ShellExecute(NULL, L"open", L"StartupUtil.exe", NULL, NULL, 0);
		codes::generateWhileCheck(true, user);
		break;
	}
	default:
		slowType("That isn't an option!\n");
	}
	goto exit; //Horrible practice, i know...
	exit:
	slowType("Program is complete. Press enter to terminate.\n");
	while (!_kbhit()) {
		Sleep(100);
	}
	return 0;
}