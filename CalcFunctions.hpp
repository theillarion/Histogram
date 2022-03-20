#pragma once

#include <vector>
#include <tuple>
#include <algorithm>
#include <boost/math/distributions/normal.hpp>

using boost::math::cdf;
using boost::math::normal;

template <typename Type>
std::tuple<std::vector<Type>, std::vector<Type>>	calcEmpiricalFunction(const std::vector<Type>& sample)
{
	std::vector<Type>	interval;
	std::vector<Type>	frequency;
	std::vector<Type>	countRepeat;
	size_t				countFinally;
	Type				sum;

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

	sum = 0;
	countFinally = sample.size();
	for (const auto& elem : countRepeat)
	{
		frequency.push_back(sum / countFinally);
		sum += elem;
	}
	frequency.push_back(sum / countFinally);
	// complete <frequency>

	return (std::make_tuple(interval, frequency));
}

template<typename Type>
std::tuple<std::vector<Type>, std::vector<Type>>	calcNormalfunction(std::vector<Type>& sample, Type mean, Type shifted_variance)
{
	std::vector<Type>	valuesX;
	std::vector<Type>	valuesY;

	valuesX.resize(sample.size());
	std::copy(sample.begin(), sample.end(), valuesX.begin());

	std::sort(valuesX.begin(), valuesX.end());

	valuesX.erase(std::unique(valuesX.begin(), valuesX.end()), valuesX.end());

	for (const auto& elem : valuesX)
		valuesY.push_back(cdf(normal(mean, shifted_variance), elem));

	return (std::make_tuple(valuesX, valuesY));
}

template<typename Type>
Type	kolm_reverse(Type alpha)
{
	return (sqrt(-0.5 * log(alpha / 2)));
}
