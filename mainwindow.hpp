#pragma once

#include <QMainWindow>
#include <QChartView>
#include <QtCharts>
#include <QSplineSeries>
#include <QHBoxLayout>
#include <QValueAxis>
#include <vector>
#include <tuple>

#include "CalcHistogram.hpp"
#include "Histogram.hpp"
#include "CalcFunctions.hpp"
#include "DefineSymbols.hpp"

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

	std::vector<qreal>	sample;
	std::vector<qreal>	interval;
	std::vector<qreal>	resultEmpirical;
	std::vector<qreal>	resultNormal;

	struct Data_result
	{
		size_t	n;
		qreal	supreme;
		qreal	stat;
		qreal	alpha_critical;
		qreal	p_value;
		QString	interval_critical;
		bool	is_accepted;
	};

	qreal		alpha;
	qreal		mean;
	qreal		shifted_variance;

	QPen		getSettingsPen(QPen	oldPen);
	void		ouputResult();
	Data_result	calcResult();

	Ui::MainWindow* ui;
public:
	MainWindow(QWidget *parent = nullptr);
	~MainWindow();

	void	initial(const std::vector<qreal>& sample, qreal alpha, qreal mean, qreal shifted_variance);
	void	buildChart(const std::vector<qreal>	&sample);
	void	buildEmpiricalFunction();
};


//void buildGraph(const std::vector<qreal>	&sample);

//QList<QPointF>	createXY(const qreal start, const qreal end, const qreal step, qreal(*fun)(qreal));

//void	buildSin();
//void	buildGraphic(std::vector<qreal>& sample);