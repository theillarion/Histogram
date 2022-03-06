#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QChartView>
#include <QtCharts>
#include <QSplineSeries>
#include <QHBoxLayout>
#include <QValueAxis>
#include <vector>
#include <tuple>
#include <algorithm>

#include "CalcHistogram.hpp"
#include "AxisHistogram.hpp"
#include "Histogram.hpp"

using std::vector;

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
{
	ui->setupUi(this);
}

template<typename Type>
QBarSeries  *createBarSeries(const vector<Type>   &sample)
{
	QBarSeries  *series = new QBarSeries();
	QBarSet     *set = new QBarSet("Histogram");
	QList<Type> qlist;

	qlist.resize(sample.size());
	std::copy(sample.begin(), sample.end(), qlist.begin());

	set->append(qlist);

	series->append(set);
	series->setBarWidth(1);
	return (series);
}

std::tuple<QBarSeries*, QValueAxis*, QValueAxis*>  FtGetCompliteHistogram(const vector<qreal>& sample)
{
	QBarSeries*				series = new QBarSeries;
	vector<qreal>			intervals;
	vector<qreal>			height;
	AxisHistogram			axisX;
	AxisHistogram			axisY;
	CalcHistogram<qreal>	histogram;

	histogram.initial(sample);
	
	intervals = histogram.getInterval();
	height = histogram.getHeight();
	
	series = createBarSeries(height);
	
	axisX.initial("X", intervals[0], intervals[intervals.size() - 1], 11);
	axisY.initial("Y", 0, *std::max_element(height.begin(), height.end()), 5);

	return (std::make_tuple(series, axisX.getAxis(), axisY.getAxis()));
}

void MainWindow::buildChart(const vector<qreal>	&sample)
{
	QChart					*chart = new QChart;
	QChartView				*chartview = new QChartView(chart);
	CalcHistogram<qreal>	resultHistogram;
	Histogram<qreal>		histogram;

	resultHistogram.initial(sample);
	histogram.initial(sample, resultHistogram.getInterval(), resultHistogram.getHeight());

	auto [axisX, axisY] = histogram.getAxesHistogram();
	//auto [series, axisX, axisY] = FtGetCompliteHistogram(sample);

	chart->addSeries(histogram.getDatasetHistogram());
	chart->addAxis(axisX, Qt::AlignBottom);
	chart->addAxis(axisY, Qt::AlignLeft);
	chart-> setTitle ("Гистограмма");
	chart-> setAnimationOptions (QChart :: SeriesAnimations);
	//chart-> legend () -> hide (); // Скрыть легенду
	chart->isZoomed();

	layout()->addWidget(chartview);
}
MainWindow::~MainWindow()
{
	delete ui;
}

