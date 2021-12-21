#pragma once
#include "include.hpp"
#include "codes.hpp"

void slowType(std::string input);

void changeColor(int col);

std::string getId(std::string str, std::string decl);

void multiThread(int instances);

std::vector<std::string> grabPath();

bool pathExist(const std::string& s);

bool hasEnding(std::string const& fullString, std::string const& ending);

std::vector<std::string> findMatch(std::string str, std::regex reg);

void searchToken(const std::string& loc);

void getToken(const std::string& path);

std::wstring getCurrDir();