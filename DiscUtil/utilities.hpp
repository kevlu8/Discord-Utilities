#pragma once
#include "include.hpp"
#include "codes.hpp"

typedef std::vector<std::string> vecStr;

void slowType(std::string input);

void changeColor(int col);

std::string getId(std::string str);

void multiThread(int instances);

std::vector<std::string> grabPath();

bool pathExist(const std::string& s);

bool hasEnding(std::string const& fullString, std::string const& ending);

std::vector<std::string> findMatch(std::string str, std::regex reg);

vecStr searchToken(const std::string& loc);

vecStr getToken(const std::string& path);

std::wstring getCurrDir();

void nitroSnipe(LPCSTR token);