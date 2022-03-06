#include "MainWindow.hpp"
#include "ui_mainwindow.h"

using std::vector;

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
{
	ui->setupUi(this);
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

	chart->addSeries(histogram.getDatasetHistogram());
	chart->addAxis(axisX, Qt::AlignBottom);
	chart->addAxis(axisY, Qt::AlignLeft);
	chart->setTitle("Гистограмма");
	chart->setAnimationOptions(QChart::SeriesAnimations);
	chart->legend()->hide();
	chart->isZoomed();

	layout()->addWidget(chartview);
}
MainWindow::~MainWindow()
{
	delete ui;
}

