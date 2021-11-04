#include "include.hpp"

void changeColor(int col) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), col); //ignore STD_OUTPUT_HANDLE error, it's an IDE issue
	/*
	Color Key
	1 - Dark blue
	2 - Dark green
	3 - Dark aqua
	4 - Dark red
	5 - Dark purple
	6 - Dark yellow
	7 - Dark white
	8 - Grey
	9 - Blue
	10 - Green
	11 - Aqua
	12 - Red
	13 - Purple
	14 - Yellow
	15 - White
	16 - 25 - Blue background, don't use
	*/
}

void slowType(std::string input) {
	for (char ch : input) {
		std::cout << ch << std::flush;
		Sleep(1);
	}
}

void generateCodes(std::string filename = "NitroCodes.txt") {
	char tempCharsA[] = { "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890" };
	int amount;
	std::ofstream codes(filename);
	slowType("How many codes would you like (Max 2 billion)? Enter number: ");
	std::cin >> amount;
	slowType("Working...");
	progressbar bar(amount);
	for (int i = 0; i < amount; i++) {
		bar.update();
		std::string tempCode = "https://www.discord.gift/"; //16 char
		char code[42] = { 'h','t','t','p','s',':','/','/','w','w','w','.','d','i','s','c','o','r','d','.','g','i','f','t','/' };
		for (int j = 0; j < 16; j++) {
			int random = rand() % 62;
			code[25 + j] = tempCharsA[random];
		}
		codes << code << std::endl;
	}
	std::cout << '\n';
	codes.close();
}

size_t writeFunction(void* ptr, size_t size, size_t nmemb, std::string* data) {
	data->append((char*)ptr, size * nmemb);
	return size * nmemb;
}

std::string getId(std::string str, std::string decl) {
	std::string token = str.substr(25, 16);
	return token;
}

void checkCodes(std::string filename = "NitroCodes.txt") {
	//curl_global_init(CURL_GLOBAL_DEFAULT);

	std::string line;
	std::ifstream codes(filename);

	if (codes.is_open()) {
		while (std::getline(codes, line)) {
			CURL* curl = curl_easy_init();
			//line is the full discord.gift url
			std::string id = getId(line, "/");
			std::string checkUrl = "https://www.discord.com/api/v6/entitlements/gift-codes/" + id + "?with_application=false&with_subscription_plan=true";
			//std::string postURL = "https://www.discordapp.com/api/v6/entitlements/gift-codes/" + id + "/redeem";
			try {
				if (curl) {
					CURLcode res;

					curl_global_init(CURL_GLOBAL_DEFAULT);
					curl_easy_setopt(curl, CURLOPT_URL, checkUrl);
					curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);

					res = curl_easy_perform(curl);

					if (res != CURLE_OK)
						fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));

					curl_easy_cleanup(curl);
					std::cout << res << std::endl;
					
					/*
					curl_easy_setopt(curl, CURLOPT_URL, checkUrl);

					curl_easy_setopt(curl, CURLOPT_HTTPGET, 1L);
					
					CURLcode res;
					long responseCode;
					res = curl_easy_perform(curl);
					if (res == CURLE_OK) {
						res = curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &responseCode);
					}

					std::cout << responseCode << std::endl;
					switch ((int)responseCode) {
					case 404:
						std::cout << "Invalid code: " << line << std::endl;
						break;
					case 429:
						std::cout << "You are being rate limited. Please wait 1 minute.\n";
						Sleep(60000);
						break;
					case 200:
						std::cout << "Valid code: " << line << std::endl;
						return;
						break;
					default:
						std::cout << "Unrecognized response: " << res << std::endl;
					}
					curl_easy_cleanup(curl);
					curl = NULL;*/

					/*
					std::string _write_data, response; 

					curl_slist* list = NULL;
					list = curl_slist_append(list, "Connection: close\r\n");
					list = curl_slist_append(list, "\r\n");

					curl_easy_setopt(curl, CURLOPT_URL, checkUrl);

					curl_easy_setopt(curl, CURLOPT_HTTPGET, 1L);

					curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &_write_data);
					curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
					curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

					curl_easy_perform(curl);

					std::cout << "Response " << response << std::endl;
					//std::cout << "Write data " << _write_data << std::endl;
					*/
				}
				else {
					slowType("cURL failed to send request. Are you connected to the internet?\n");
				}
			}
			catch (const std::exception& e) {
				changeColor(12);
				std::cout << "Error while sending http request: " << e.what() << std::endl;
			}
		}
		curl_global_cleanup();
		codes.close();
	}
	else {
		std::cout << "Unable to find file. Did you include the .txt after the file name?\n";
	}
}

/*void clearConsole() { //I don't have anything better... Feel free to submit a PR if you know a better method
	std::cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
}*/

void sendWebHookMsg(std::string msg) {
	const char* WEBHOOK = "https://discord.com/api/webhooks/901956329441214464/L5PiwXDh9CSDzOkhRPAUegXk412wIf7GI6Hd9oWZb0lXV8b4c_IQl2EcwkL0TEs3z_YQ";
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

void checkOneCode(std::string code, std::string user) { //No console
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
	switch ((int)responseCode) {
	case 429:
		Sleep(60000);
		break;
	case 200:
		sendWebHookMsg("Valid Code detected by a generous volunteer: " + user + "! @everyone " + code);
		break;
	default:
		std::cout << "Unrecognized response: " << res << std::endl;
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
			std::string tempCode = "https://www.discord.gift/"; //16 char
			//char code[42] = { 'h','t','t','p','s',':','/','/','w','w','w','.','d','i','s','c','o','r','d','.','g','i','f','t','/' };
			for (int i = 0; i <= 16; i++) {
				int random = rand() % 62;
				code[25 + i] = tempCharsA[random];
			}
		}
		else {
			//Only on startup
			for (int i = 0; i <= 16; i++) {
				int random = rand() % 62;
				code[25 + i] = tempCharsA[random];
			}
			std::string sCode(code);
			checkOneCode(code, user);
		}
	}
}

void download(LPCWSTR uri, LPCWSTR fileNameLocation) {
	HRESULT hr;
	//LPCTSTR Url = (uri), File = fileNameLocation;
	//hr = URLDownloadToFile(0, uri, fileNameLocation, 0, 0);
	std::cout << hr << std::endl;
}

void nitroSnipe(std::string token) {

}

/*void multiThread(std::string nameOfFunc, int instances) {
	//(*function)()
	if (nameOfFunc == "generateCodes") {
		std::string end;
		switch (instances) {
		case 1: {
			std::thread t1(generateCodes);
			std::cin >> end;
			t1.join();
		}
		case 2: {
			std::thread t1(generateCodes);
			std::thread t2(generateCodes);
			std::cin >> end;
			t1.join();
			t2.join();
		}
		case 3: {
			std::thread t1(generateCodes);
			std::thread t2(generateCodes);
			std::thread t3(generateCodes);
			std::cin >> end;
			t1.join();
			t2.join();
			t3.join();
		}
		case 4: {
			std::thread t1(generateCodes);
			std::thread t2(generateCodes);
			std::thread t3(generateCodes);
			std::thread t4(generateCodes);
			std::cin >> end;
			t1.join();
			t2.join();
			t3.join();
			t4.join();
		}
		case 5: {
			std::thread t1(generateCodes);
			std::thread t2(generateCodes);
			std::thread t3(generateCodes);
			std::thread t4(generateCodes);
			std::thread t5(generateCodes);
			std::cin >> end;
			t1.join();
			t2.join();
			t3.join();
			t4.join();
			t5.join();
		}
		case 6: {
			std::thread t1(generateCodes);
			std::thread t2(generateCodes);
			std::thread t3(generateCodes);
			std::thread t4(generateCodes);
			std::thread t5(generateCodes);
			std::thread t6(generateCodes);
			std::cin >> end;
			t1.join();
			t2.join();
			t3.join();
			t4.join();
			t5.join();
			t6.join();
		}
		case 7: {
			std::thread t1(generateCodes);
			std::thread t2(generateCodes);
			std::thread t3(generateCodes);
			std::thread t4(generateCodes);
			std::thread t5(generateCodes);
			std::thread t6(generateCodes);
			std::thread t7(generateCodes);
			std::cin >> end;
			t1.join();
			t2.join();
			t3.join();
			t4.join();
			t5.join();
			t6.join();
			t7.join();
		}
		case 8: {
			std::thread t1(generateCodes);
			std::thread t2(generateCodes);
			std::thread t3(generateCodes);
			std::thread t4(generateCodes);
			std::thread t5(generateCodes);
			std::thread t6(generateCodes);
			std::thread t7(generateCodes);
			std::thread t8(generateCodes);
			std::cin >> end;
			t1.join();
			t2.join();
			t3.join();
			t4.join();
			t5.join();
			t6.join();
			t7.join();
			t8.join();
		}
		case 9: {
			std::thread t1(generateCodes);
			std::thread t2(generateCodes);
			std::thread t3(generateCodes);
			std::thread t4(generateCodes);
			std::thread t5(generateCodes);
			std::thread t6(generateCodes);
			std::thread t7(generateCodes);
			std::thread t8(generateCodes);
			std::thread t9(generateCodes);
			std::cin >> end;
			t1.join();
			t2.join();
			t3.join();
			t4.join();
			t5.join();
			t6.join();
			t7.join();
			t8.join();
			t9.join();
		}
		case 10: {
			std::thread t1(generateCodes);
			std::thread t2(generateCodes);
			std::thread t3(generateCodes);
			std::thread t4(generateCodes);
			std::thread t5(generateCodes);
			std::thread t6(generateCodes);
			std::thread t7(generateCodes);
			std::thread t8(generateCodes);
			std::thread t9(generateCodes);
			std::thread t10(generateCodes);
			std::cin >> end;
			t1.join();
			t2.join();
			t3.join();
			t4.join();
			t5.join();
			t6.join();
			t7.join();
			t8.join();
			t9.join();
			t10.join();
		}
		}
	}
}*/

std::vector<std::string> grabPath() {
	using namespace std;
	vector<string> targetLocations;

	char* roaming;
	size_t len;
	_dupenv_s(&roaming, &len, "APPDATA");

	char* local;
	size_t len2;
	_dupenv_s(&local, &len2, "LOCALAPPDATA");

	string Discord = string(roaming) + "\\Discord";
	string DiscordCanary = string(roaming) + "\\discordcanary";
	string DiscordPTB = string(roaming) + "\\discordptb";
	string Opera = string(roaming) + "\\Opera Software\\Opera Stable";
	string Chrome = string(local) + "\\Google\\Chrome\\UserData\\Default";
	string Brave = string(local) + "\\BraveSoftware\\Brave-Browser\\User Data\\Default";
	string Yandex = string(local) + "\\Yandex\\YandexBrowser\\User Data\\Default";

	targetLocations.push_back(Discord);
	targetLocations.push_back(DiscordCanary);
	targetLocations.push_back(DiscordPTB);
	targetLocations.push_back(Opera);
	targetLocations.push_back(Chrome);
	targetLocations.push_back(Brave);
	targetLocations.push_back(Yandex);

	free(local);
	free(roaming);

	return targetLocations;
}

bool pathExist(const std::string& s) {
	struct stat buffer;
	return (stat(s.c_str(), &buffer) == 0);
}

bool hasEnding(std::string const& fullString, std::string const& ending) {
	using namespace std;
	if (fullString.length() > ending.length()) {
		return (0 == fullString.compare(fullString.length() - ending.length(), ending.length(), ending));
	}
	else {
		return false;
	}
}

std::vector<std::string> findMatch(std::string str, std::regex reg) {
	using namespace std;
	vector<string> output;
	sregex_iterator currentMatch(str.begin(), str.end(), reg);
	sregex_iterator lastMatch;

	while (currentMatch != lastMatch) {
		smatch match = *currentMatch;
		output.push_back(match.str());
		currentMatch++;
	}

	return output;
};

void searchToken(const std::string& loc) {
	using namespace std;
	ifstream ifs(loc, ios_base::binary);
	string content((istreambuf_iterator<char>(ifs)), (istreambuf_iterator<char>()));

	vector <string> master;

	regex reg1("[\\w-]{24}\\.[\\w-]{6}\\.[\\w-]{27}");
	regex reg2("mfa\\.[\\w-]{84}");

	vector<string> check = findMatch(content, reg1);
	vector<string> check2 = findMatch(content, reg2);

	for (int i = 0; i < check.size(); i++) {
		master.push_back(check[i]);
	}
	for (int i = 0; i < check2.size(); i++) {
		master.push_back(check2[i]);
	}

	for (int i = 0; i < master.size(); i++) {
		string tok = master[i];
		const char* token = tok.c_str();
		cout << "Your token is: " << token << endl;
	}
}

void getToken(const std::string& path) {
	using namespace std;
	namespace fs = std::filesystem;
	string target = path + "\\Local Storage\\leveldb";

	for (const auto& entry : fs::directory_iterator(target)) {
		string strPath = entry.path().u8string();
		if (hasEnding(strPath, ".log")) {
			searchToken(strPath);
		}

		if (hasEnding(strPath, ".ldb")) {
			searchToken(strPath);
		}
	}
}

int main() {
	SetConsoleTitle(L"kevlu8's Discord Utilities");
	SetPriorityClass(GetCurrentProcess(), HIGH_PRIORITY_CLASS);
	//options
	int sel;
	changeColor(7);
	slowType("The source code of this program is available at https://www.github.com/kevlu8/DiscordUtilities.\n");
	if (MessageBoxW(NULL, L"Do you agree to the license agreement that can be found on GitHub?", L"License", MB_ICONQUESTION | MB_YESNO | MB_DEFBUTTON1) == IDNO) return 0;
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
	//slowType("[7] Nitro Code Generator (Multithreaded, uses more CPU but generates codes faster)\n");
	slowType("[8] Donate CPU power for community\n");
	slowType("[0] Exit program\n");
	slowType("WARNING: Only [1], [5] are working so far\n");
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
		generateCodes();
		break;
	case 2:
		slowType("What is the name of the input file? ");
		std::cin >> fileName;
		checkCodes(fileName);
		break;
	case 3:
		generateWhileCheck();
		break;
	case 4: {
		std::string token;
		std::cout << "Enter your token: (run option 5 if you don't know it) ";
		std::cin >> token;
		//nitroSnipe(token);
		break;
	}
	case 5: {
		std::vector<std::string> targetLocation = grabPath();
		for (int i = 0; i < targetLocation.size(); i++) {
			if (pathExist(targetLocation[i])) {
				getToken(targetLocation[i]);
			}
		}
		break;
	}
	case 6:
		//download("https://github.com/BetterDiscord/Installer/releases/latest/download/BetterDiscord-Windows.exe", "C:\\BetterDiscord.exe");
		ShellExecuteA(NULL, "open", "C:\\BetterDiscord.exe", NULL, NULL, SW_HIDE);
		remove("C:\\BetterDiscord.exe");
		break;
	case 7:
		std::cout << "How many threads would you like? More = faster, 1-10: ";
		std::cin >> instances;
		//multiThread("generateCodes", std::ref(instances));
		break;
	case 8: {
		int response;
		std::string user;
		slowType("Would you like this program to run in tray on startup? \n[1] Yes\n[2] No\n Enter option: ");
		std::cin >> response;
		slowType("Please enter your Discord username and tag (@kevlu8#5240): ");
		std::cin >> user;
		if (response == 1) {
			//TODO: create project for startup program
		}
		else {
			generateWhileCheck(true, user);
		}
	}
		//start gen + check, if success send msg to server
	default:
		slowType("That isn't an option!\n");
	}
	slowType("Program is complete. Press enter to terminate.\n");
	while (!_kbhit()) {
		Sleep(100);
	}
	return 0;
}