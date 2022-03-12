#include "MainWindow.hpp"
#include "ui_mainwindow.h"
#include <numbers>
#include <boost/math/distributions/normal.hpp>

using std::vector;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	layout = new QHBoxLayout;
	chart = new QChart;
	chartview = new QChartView(chart);
	chartview->chart()->setTheme(QChart::ChartThemeBlueCerulean);
	chartview->setRenderHint(QPainter::Antialiasing);
}

void MainWindow::buildChart(const vector<qreal>	&sample)
{
	CalcHistogram<qreal>	resultHistogram;
	Histogram<qreal>		histogram;

	resultHistogram.initial(sample);
	histogram.initial(sample, resultHistogram.getInterval(), resultHistogram.getHeight());

	auto [axisX, axisY] = histogram.getAxesHistogram();
	chart->addSeries(histogram.getDatasetHistogram());
	chart->addAxis(axisX, Qt::AlignBottom);
	chart->addAxis(axisY, Qt::AlignLeft);
	chart->setTitle("Гистограмма");
	chart->setAnimationOptions(QChart::SeriesAnimations);
	chart->legend()->hide();
	chart->isZoomed();

	layout->addWidget(chartview);
	ui->centralwidget->setLayout(layout);
}

double fff(double	x)
{
	double one_chart = 1 / sqrt(2 * std::numbers::pi);
	return (one_chart * pow(std::numbers::e, -0.5 * pow(x, 2)));
}

QPen	MainWindow::getSettingsPen(QPen	oldPen = QPen())
{
	QPen	newPen;

	newPen = oldPen;

	newPen.setWidth(2);
	newPen.setCapStyle(Qt::FlatCap);

	return (newPen);
}

void	analysis(vector<qreal>	x, vector<qreal>	y_empirical, vector<qreal>	y_normal)
{

}

void	MainWindow::buildEmpiricalFunction(vector<qreal>	&sample)
{
	Axis			axisX;
	Axis			axisY;
	QValueAxis		*axisXX = new QValueAxis;
	QValueAxis		*axisYY = new QValueAxis;;
	QSplineSeries*	series = new QSplineSeries;
	QLineSeries*	lines = new QLineSeries;
	vector<qreal>	interval;
	vector<qreal>	resultEmpirical;
	vector<qreal>	resultNormal;
	
	std::tie(interval, resultEmpirical) = calcEmpiricalFunction(sample);
	std::tie(std::ignore, resultNormal) = calcNormalfunction(sample);

	axisX.initial("X", interval[0], interval[interval.size() - 1], 20);
	axisY.initial("F(X)", 0, 1, 11);

	axisXX = axisX.getAxis();
	axisYY = axisY.getAxis();

	for (int i = 0; i < interval.size() - 1; i++)
	{
		lines->append(interval[i], resultEmpirical[i]);
		lines->append(interval[i + 1], resultEmpirical[i]);
	}

	lines->setColor(QColor::fromRgba(qRgb(255, 255, 0)));
	lines->setName("Эмпирическая функция распределения");

	chart->addSeries(lines);

	lines->setPen(getSettingsPen(lines->pen()));
	
	chart->setAxisX(axisXX, lines);
	chart->setAxisY(axisYY, lines);

	for (int i = 0; i < sample.size(); i++)
		series->append(interval[i], resultNormal[i]);

	series->setPen(getSettingsPen(series->pen()));
	series->setColor(QColor::fromRgba(qRgb(255, 0, 0)));
	series->setName("Функция нормального распределения (среднее = 0, выборочная дисперсия = 1)");

	//analysis(interval, frequency, y);

	chart->addSeries(series);
	chart->setAxisX(axisXX, series);
	chart->setAxisY(axisYY, series);

	chart->setAnimationOptions(QChart::SeriesAnimations);
	chart->setTitle("Эмпирическая функция распределения с наложением нормальной функции распределения");
	//chart->legend()->hide();
	
	layout->addWidget(chartview);
	ui->centralwidget->setLayout(layout);
}

/*QList<QPointF>	MainWindow::createXY(const qreal start, const qreal end, const qreal step, qreal(*fun)(qreal))
{
	QList<QPointF>	result;

	for (qreal i = start; i <= end; i += step)
	{
		result.push_back(QPointF(i, (*fun)(i)));
	}
	return (result);
}

void MainWindow::buildSin()
{
	Axis			axisX;
	Axis			axisY;
	QValueAxis		*axisXX;
	QValueAxis		*axisYY;
	QSplineSeries	*series;
	QSplineSeries	*series2;
	QSplineSeries	*series3;

	axisXX = new QValueAxis;
	axisYY = new QValueAxis;
	series = new QSplineSeries;
	series2 = new QSplineSeries;
	series3 = new QSplineSeries;

	vector<double>	y;

	for (int i = -20; i <= 20; i++)
		y.push_back(tan(i));

	axisX.initial("X", -20, 20, 11);
	axisY.initial("Y", *std::min_element(y.begin(), y.end()), *std::max_element(y.begin(), y.end()), 5);
	axisXX = axisX.getAxis();
	axisYY = axisY.getAxis();
	
	series->append(createXY(-20, 20, 1, sin));
	series->setName("Sin");
	chart->addSeries(series);
	chart->setAxisX(axisXX, series);
	chart->setAxisY(axisYY, series);

	series2->append(createXY(-20, 20, 1, cos));
	series2->setName("Cos");
	chart->addSeries(series2);
	chart->setAxisX(axisXX, series2);
	chart->setAxisY(axisYY, series2);
	auto t = createXY(-10, 10, 1, tan);

	series3->append(createXY(-20, 20, 1, tan));
	series3->setName("Tan");
	chart->addSeries(series3);
	chart->setAxisX(axisXX, series3);
	chart->setAxisY(axisYY, series3);

	chart->setAnimationOptions(QChart::SeriesAnimations);
	//chart->legend()->hide();
	chart->setTitle("Синусоида и косинусоида");
	layout->addWidget(chartview);
	ui->centralwidget->setLayout(layout);
}


void MainWindow::buildGraphic(vector<qreal>& sample)
{
	Axis			axisX;
	Axis			axisY;
	QValueAxis*		axisXX;
	QValueAxis*		axisYY;
	QSplineSeries*	series;
	vector<qreal>	y;

	axisXX = new QValueAxis;
	axisYY = new QValueAxis;
	series = new QSplineSeries;

	std::sort(sample.begin(), sample.end());
	for (const auto& x : sample)
		y.push_back(fff(x));


	axisX.initial("X", sample.front(), sample.back(), 11);
	axisY.initial("Y", *std::min_element(y.begin(), y.end()), *std::max_element(y.begin(), y.end()), 5);
	axisXX = axisX.getAxis();
	axisYY = axisY.getAxis();

	for (int i = 0; i < sample.size(); i++)
	{
		series->append(sample[i], y[i]);
	}
	series->setName("F(x)");
	chart->addSeries(series);
	chart->setAxisX(axisXX, series);
	chart->setAxisY(axisYY, series);

	chart->setAnimationOptions(QChart::SeriesAnimations);
	//chart->legend()->hide();
	chart->setTitle("Синусоида и косинусоида");
	layout->addWidget(chartview);
	ui->centralwidget->setLayout(layout);
}*/


MainWindow::~MainWindow()
{
	delete ui;
}
