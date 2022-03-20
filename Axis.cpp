#include "Axis.hpp"

Axis::Axis(const QString name_axis, const qreal min, const qreal max, const int count) : axis(new QValueAxis)
{
    axis->setTitleText(name_axis);
    axis->setRange(min, max);
    if (count != 5)
        axis->setTickCount(count);
}

void    Axis::initial(const QString &name_axis, const qreal       min,  const qreal       max,  const int count = 5)
{
    axis->setTitleText(name_axis);
    axis->setRange(min, max);
    if (count != 5)
        axis->setTickCount(count);
}
QValueAxis  * Axis::getAxis() const
{
    return (axis);
}

QValueAxis* makeAxis(const QString& name_axis, const qreal       min, const qreal       max, const int count = 5)
{
    QValueAxis* axis;

    axis = new QValueAxis;

    axis->setTitleText(name_axis);
    axis->setRange(min, max);
    if (count != 5)
        axis->setTickCount(count);

    return (axis);
}