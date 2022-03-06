#pragma once

#include <QString>
#include <QValueAxis>

class AxisHistogram
{
private:
	QString		name_axis;
	qreal		min;
	qreal		max;
	int			count;
public:
	AxisHistogram() : name_axis{ "Axis" }, min{ 0 }, max{ 0 }, count{ 0 } {}
	AxisHistogram(const QString& name_axis, const qreal       min, const qreal       max, const int count) : name_axis{ name_axis }, min{ min }, max{ max }, count{ count } {}
	void		initial(const QString& name_axis, const qreal       min, const qreal       max, const int count);
	QValueAxis* getAxis();
};
