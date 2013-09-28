#include "ConfigMap.h"
#include <string>
#include <fstream>

//Default Constructor
Config::ConfigMap::ConfigMap() { }

//Auto load constructor
Config::ConfigMap::ConfigMap(string filepath) {
	LoadFromFile(filepath);
}

//Manual Loader
void Config::ConfigMap::LoadFromFile(string filepath) {

	ifstream inFile(filepath);
	string line = "";

	if(!inFile.is_open())
		throw exception("File failed to open.");

	while(getline(inFile, line)) {

		size_t split = line.find(':');

		string name = line.substr(0, split);

		string value = line.substr(split + 1, line.length() - split);

		insert(std::pair<string, string>(name, value));
	}
}