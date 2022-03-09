#include "MainWindow.hpp"
#include "ui_mainwindow.h"

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

void	MainWindow::buildEmpiricalFunction(const vector<qreal>	&sample)
{
	AxisHistogram	axisX;
	AxisHistogram	axisY;
	QValueAxis		*axisXX;
	QValueAxis		*axisYY;

	axisYY = new QValueAxis;
	axisXX = new QValueAxis;

	auto [interval, frequency] = calcEmpiricalFunction(sample);

	axisX.initial("X", interval[0], interval[interval.size() - 1], 20);
	axisY.initial("F(X)", 0, 1, 11);

	axisXX = axisX.getAxis();
	axisYY = axisY.getAxis();

	for (int i = 0; i < interval.size() - 1; i++)
	{
		QLineSeries* line = new QLineSeries;

		line->append(interval[i], frequency[i + 1]);
		line->append(interval[i + 1], frequency[i + 1]);
		
		chart->addSeries(line);
		chart->setAxisX(axisXX, line);
		chart->setAxisY(axisYY, line);
	}

	chart->setAnimationOptions(QChart::SeriesAnimations);
	chart->legend()->hide();
	chart->setTitle("Эмпирическая функция распределения");
	layout->addWidget(chartview);
	ui->centralwidget->setLayout(layout);
}

MainWindow::~MainWindow()
{
	delete ui;
}
