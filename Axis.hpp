#pragma once

#include <QString>
#include <QValueAxis>

QValueAxis* makeAxis(const QString& name_axis, const qreal       min, const qreal       max, const int count);

class Axis
{
private:
	QValueAxis*	axis;
public:
	Axis() : axis(new QValueAxis) {}
	Axis(const QString name_axis, const qreal min, const qreal max, const int count = 5);
	
	void		initial(const QString& name_axis, const qreal       min, const qreal       max, const int count);
	QValueAxis* getAxis() const;
};
