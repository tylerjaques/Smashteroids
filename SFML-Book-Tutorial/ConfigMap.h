#ifndef __CONFIG_MAP_H__
#define __CONFIG_MAP_H__
#include <map>
#include <string>
#include <exception>
#include <sstream>

using namespace std;

class ConfigMap : public map<string, string>  {

public:
	ConfigMap();
	ConfigMap(string filepath);
	void LoadFromFile(string filepath);

	template<typename T>
	float getAs(std::string name) {
		std::stringstream ss;
			
		ss << at(name);

		T ret;
		ss >> ret;
		return ret;
	}

	template<typename T>
	float getAs(std::string name) const {
		std::stringstream ss;
			
		ss << at(name);

		T ret;
		ss >> ret;
		return ret;
	}

};
#endif