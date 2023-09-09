#include<queue>
#include<random>
#include<map>
#include<iostream>
#include<string>
#include<filesystem>
#include<vector>
#include<regex>
#include<chrono>

namespace fs = std::filesystem;

void PicturePrint(std::string PicturePath);

int main() {
	using std::string;
	std::vector<string> imageFiles;
	std::queue<string> order;
	std::map<string, short>visit;
	fs::path currentDir = fs::current_path() / "picture";
	std::regex pattern(".*\\.(jpg|jpeg|png)$");
	auto currentTime = std::chrono::high_resolution_clock::now();
	auto seed = currentTime.time_since_epoch().count();
	string tempName;
	std::mt19937 generator(seed);
	for (const auto& entry : std::filesystem::directory_iterator(currentDir)) {
		if (std::regex_match(entry.path().filename().string(), pattern)) {
			imageFiles.push_back(entry.path().filename().string());
		}
	}
	while (true) {
		std::uniform_int_distribution<short> distribution(0, imageFiles.size());
		short random = distribution(generator);
		fs::path temp = currentDir / imageFiles[random];
		if (visit.contains(imageFiles[random]) && visit[imageFiles[random]] == true) continue;
		visit[imageFiles[random]] = 1;
		order.push(imageFiles[random]);
		PicturePrint(temp.string());
		if (order.size() >= 20) {
			tempName = order.front();
			visit[tempName] = false;
			order.pop();
		}
	}
	return 0;
}