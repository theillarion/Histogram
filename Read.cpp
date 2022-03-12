#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using std::ios;
using std::string;
using std::ifstream;
using std::vector;
using std::cout;
using std::endl;

static bool	ft_validation(const	string	str) noexcept
{
	size_t	i = 0;

	if (str.length() == 0)
		return (false);
	while (str[i])
	{
		if (!isdigit(str[i]) && str[i] != '.' && str[i] != '-' && str[i] != 'e')
			return (false);
		++i;
	}
	return (true);
}

vector<double>	ft_read_file(const string path)
{
	ifstream		file(path);
	vector<double>	numbers;
	string			buff;

	if (!file.is_open())
	{
		cout << "Error: file isn't open" << std::endl;
		std::exit(EXIT_FAILURE);
	}
	while (!file.eof())
	{
		std::getline(file, buff);
		if (ft_validation(buff))
			numbers.push_back(std::stod(buff));
	}
	file.close();
	return (numbers);
}
