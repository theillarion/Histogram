#pragma once
#include <QValueAxis>
#include <QBarSeries>
#include "Axis.hpp"

template<typename Type>
class Histogram
{
private:
	QVector<Type>	sample;
	QVector<Type>	height;
	QVector<Type>	interval;
	QValueAxis*		axisX;
	QValueAxis*		axisY;
	void	copyVector(const std::vector<Type>& src, QVector<Type>& dst);
public:
	Histogram() : axisX(new QValueAxis) {}
	Histogram(const std::vector<Type>& sample, const std::vector<Type>& interval, const std::vector<Type>& height);
	
	void		initial(const std::vector<Type>& sample, const std::vector<Type>& interval, const std::vector<Type>& height);
	QBarSeries* getDatasetHistogram() const;
	std::tuple<QValueAxis*, QValueAxis*>	getAxesHistogram();
};

template<typename Type>
inline Histogram<Type>::Histogram(const std::vector<Type>& sample, const std::vector<Type>& interval, const std::vector<Type>& height)
{
	initial(sample, interval, height);
}

template<typename Type>
inline void Histogram<Type>::copyVector(const std::vector<Type>& src, QVector<Type>& dst)
{
	dst.resize(src.size());
	std::copy(src.begin(), src.end(), dst.begin());
}

template<typename Type>
inline void Histogram<Type>::initial(const std::vector<Type>& sample, const std::vector<Type>& interval, const std::vector<Type>& height)
{
	copyVector(sample, this->sample);
	copyVector(interval, this->interval);
	copyVector(height, this->height);

	axisX = makeAxis("Интервал", interval[0], interval[interval.size() - 1], interval.size());
	axisY = makeAxis("Вероятность", 0, *std::max_element(height.begin(), height.end()), 5);
}

template<typename Type>
inline QBarSeries* Histogram<Type>::getDatasetHistogram() const
{
	QBarSeries*	series;
	QBarSet*	set;
	QList<Type>	qlist;

	series = new QBarSeries();
	set = new QBarSet("Histogram");

	qlist.resize(height.size());
	std::copy(height.begin(), height.end(), qlist.begin());

	set->append(qlist);

	series->append(set);
	series->setBarWidth(1);

	return (series);
}

template<typename Type>
inline std::tuple<QValueAxis*, QValueAxis*> Histogram<Type>::getAxesHistogram()
{
	return (std::make_tuple(axisX, axisY));
}
