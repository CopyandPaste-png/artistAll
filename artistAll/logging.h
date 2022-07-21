#pragma once
#include <fstream>
#include <string>

inline void logToFile(std::string message) noexcept {
	std::ofstream file("logs.txt", std::ios_base::app);

	if (file) {
		file << message << "\n";
	}
	file.close();
}