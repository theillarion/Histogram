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

#define ALPHA		0.05

#define NEWLINE			"\n"
#define TAB				"\t"
#define N_LOWER			"\u2099"
#define CHAR_SQRT		"\u221a"
#define CHAR_ALPHA		"\u03b1"
#define CHAR_MU			"\u03bc"
#define CHAR_DELTA		"\u03b4\u00b2"
#define CHARS_D_N		"D\u2099"
#define CHARS_KOLM_R	"Kolm\u207B\u00B9(1 - \u03b1)"
#define FORMULA_D_N		"sup|F\u2099(x) - G(x)|"

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

	qreal	alpha;
	qreal	mean;
	qreal	shifted_variance;

	QPen	getSettingsPen(QPen	oldPen);
	void	getResult();

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