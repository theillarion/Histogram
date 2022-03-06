#include "AxisHistogram.hpp"

void    AxisHistogram::initial(const QString &name_axis, const qreal       min,  const qreal       max,  const int count = 5)
{
    this->name_axis = name_axis;
    this->min = min;
    this->max = max;
    this->count = count;
}
QValueAxis  * AxisHistogram::getAxis()
{
    auto    *axis = new QValueAxis;

    axis->setTitleText(name_axis);
    axis->setRange(min, max);
    axis->setTickCount(count);

    return (axis);
}
