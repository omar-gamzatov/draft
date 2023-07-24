#pragma once
#include <iostream>
#include <sstream>
#include <map>
#include <vector>

class Shitposter
{
	std::string text;
	std::map<std::string, std::vector<std::string>> dict;
	std::vector<std::string> starters;

public:
	Shitposter(std::string t);
	~Shitposter();
	void generate() const;

private:
	void parse();
};
