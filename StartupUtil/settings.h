#pragma once
#include <vector>
#include <stdlib.h>
#include <Windows.h>
namespace Settings {
	std::vector<int> pauseTimes = { 5, 10, 30, 60, 120, 180, 300, 360 };
	uint32_t pauseSelection = 0;
	int pauseTime;

	int Exit() {
		exit(0);
		return 0;
	}
	void Pause() {
		Sleep(pauseTime);
	}
}