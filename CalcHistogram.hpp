#pragma once

#include <vector>
#include <algorithm>

template<typename Type>
class CalcHistogram
{
private:
    std::vector<Type>   sort_sample;
    std::vector<Type>   interval;
    std::vector<Type>   height;
    void    calcInterval();
    void    calcHeight();
public:
    CalcHistogram() {}
    CalcHistogram(const std::vector<Type>& sample) { initial(sample); }
    void    initial(const std::vector<Type>& sample);
    std::vector<Type>	getInterval() const noexcept { return (interval); }
    std::vector<Type>	getHeight() const noexcept { return (height); }
    ~CalcHistogram() {}
};

template<typename Type>
inline void CalcHistogram<Type>::calcInterval()
{
    Type    temp;
    Type    step;

    temp = sort_sample[0];
    step = (sort_sample[sort_sample.size() - 1] - sort_sample[0]) / 10;

    for (int i = 0; i < 10; i++)
    {
        interval.push_back(temp);
        temp += step;
    }
    interval.push_back(sort_sample[sort_sample.size() - 1]);
}

template<typename Type>
inline void CalcHistogram<Type>::calcHeight()
{
    Type    count_sample;
    Type    count_interval;
    
    height.resize(interval.size() - 1);

    count_interval = interval.size();
    for (auto& elem : sort_sample)
    {
        int index = 0;
        for (int i = 0; i < count_interval - 1; i++)
        {
            if (interval[i] <= elem && elem <= interval[i + 1])
            {
                index = i;
                break;
            }
        }
        height[index] += 1;
    }
    count_sample = sort_sample.size();
    for (auto& elem : height)
        elem /= count_sample;
}

template<typename Type>
inline void CalcHistogram<Type>::initial(const std::vector<Type>& sample)
{
    if (sample.size() < 1)
        throw "sample is incorrect";

    sort_sample.resize(sample.size());
    std::copy(sample.begin(), sample.end(), sort_sample.begin());
    std::sort(sort_sample.begin(), sort_sample.end());

    calcInterval();
    calcHeight();
}
