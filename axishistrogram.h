#ifndef AXISHISTROGRAM_H
#define AXISHISTROGRAM_H

#include <QString>
#include <QValueAxis>

class CreateAxesHistogram
{
private:
	QString		name_axis;
	qreal		min;
	qreal		max;
	int			count;
public:
	CreateAxesHistogram();
	CreateAxesHistogram(const QString &name_axis, const qreal       min,  const qreal       max,  const int count);
	void		fill(const QString &name_axis, const qreal       min,  const qreal       max,  const int count);
	QValueAxis	*getAxis();
};

/*
struct CreateAxesHistogram
{
	QString     name_axis;
	qreal       min;
	qreal       max;
	int         count;
	CreateAxesHistogram(void);
	CreateAxesHistogram(const QString &name_axis, const qreal       min,  const qreal       max,  const int count = 5) : name_axis{name_axis}, min{min}, max{max}, count{count} {}
	void    initial(const QString &name_axis, const qreal       min,  const qreal       max,  const int count = 5)
	{
		this->name_axis = name_axis;
		this->min = min;
		this->max = max;
		this->count = count;
	}
	QValueAxis  *getAxis()
	{
		auto    *axis = new QValueAxis;

		axis->setTitleText(name_axis);
		axis->setRange(min, max);
		axis->setTickCount(count);

		return (axis);
	}
};
*/

#endif // AXISHISTROGRAM_H
