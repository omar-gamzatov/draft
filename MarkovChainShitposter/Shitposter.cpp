#include "Shitposter.h"

Shitposter::Shitposter(std::string t)
	: text(t)
{
	parse();
}

Shitposter::~Shitposter() = default;

void Shitposter::generate() const
{
	std::srand(std::time(NULL));
	int seq_num = rand() % starters.size();
	std::string str = starters[seq_num];
	while (dict.at(str).size() != 0)
	{
		std::cout << str << " ";
		int num = rand() % dict.at(str).size();
		str = dict.at(str).at(num);
	}
	std::cout << str << std::endl;
}

void Shitposter::parse()
{
	std::stringstream ss(text);
	std::string start;
	std::string key;
	std::string value;

	ss >> start;

	starters.push_back(start);

	key = start;
	while (ss >> value)
	{
		if (value[value.size() - 1] != '.')
		{
			dict[key].push_back(value);
			key = value;
		}
		else
		{
			dict[key].push_back(value);
			dict[value] = std::vector<std::string>{};
			ss >> key;
			starters.push_back(key);
		}
	}
}
