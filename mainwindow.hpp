#pragma once

#include <QMainWindow>
#include <QChartView>
#include <QtCharts>
#include <QSplineSeries>
#include <QHBoxLayout>
#include <QValueAxis>
#include <vector>
#include <tuple>
#include <vector>
#include "CalcHistogram.hpp"
#include "Histogram.hpp"
#include <tuple>

#include "CalcEmpiricalFunction.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

std::vector<double>	ft_read_file(const std::string path);

class MainWindow : public QMainWindow
{
	Q_OBJECT
	QHBoxLayout	*layout;
	QChart		*chart;
	QChartView	*chartview;
public:
	MainWindow(QWidget *parent = nullptr);
	~MainWindow();
   
	void buildChart(const std::vector<qreal>	&sample);
	void buildGraph(const std::vector<qreal>	&sample);

	void	buildEmpiricalFunction(const std::vector<qreal>& sample);
private:
	Ui::MainWindow *ui;
};
