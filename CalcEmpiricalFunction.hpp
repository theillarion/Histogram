#pragma once

#include <vector>
#include <tuple>
#include <algorithm>

template <typename Type>
std::tuple<std::vector<Type>, std::vector<Type>>	calcEmpiricalFunction(const std::vector<Type>& sample)
{
	std::vector<Type>	interval;
	std::vector<Type>	frequency;
	std::vector<Type>	countRepeat;
	size_t			countFinally;
	Type			sum;

	interval.resize(sample.size());
	std::copy(sample.cbegin(), sample.cend(), interval.begin());

	std::sort(interval.begin(), interval.end());

	countRepeat.resize(interval.size());

	countFinally = 0;
	for (size_t i = 0; i < interval.size(); i++)
	{
		if (i != 0 && interval[i] == interval[i - 1])
			continue;
		for (size_t j = 0; j < interval.size(); j++)
			if (interval[i] == interval[j])
				++countRepeat[countFinally];
		countFinally++;
	}
	countRepeat.resize(countFinally);

	interval.erase(std::unique(interval.begin(), interval.end()), interval.end());
	// complete <interval>

	frequency.push_back((double)0);

	sum = 0;
	countFinally = sample.size();
	for (const auto& elem : countRepeat)
	{
		sum += elem;
		frequency.push_back(sum / countFinally);
	}
	// complete <frequency>

	return (std::make_tuple(interval, frequency));
}
