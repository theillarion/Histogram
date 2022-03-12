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

#include "CalcFunctions.hpp"

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

	QPen	getSettingsPen(QPen	oldPen);
public:
	MainWindow(QWidget *parent = nullptr);
	~MainWindow();
   
	void	buildChart(const std::vector<qreal>	&sample);
	void	buildEmpiricalFunction(std::vector<qreal>& sample);
	//void buildGraph(const std::vector<qreal>	&sample);

	//QList<QPointF>	createXY(const qreal start, const qreal end, const qreal step, qreal(*fun)(qreal));

	//void	buildSin();
	//void	buildGraphic(std::vector<qreal>& sample);
private:
	Ui::MainWindow *ui;
};
