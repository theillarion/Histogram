#include "MainWindow.hpp"
#include "ui_mainwindow.h"

using std::vector;

double	kolm_reverse(double	alpha)
{
	alpha = 1 - alpha;
	return (sqrt(-0.5 * log(alpha / 2)));
}

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
	QMenu* file;
	QAction*	result;
	QAction*	quit;

	ui->setupUi(this);
	layout = new QHBoxLayout;
	chart = new QChart;
	chartview = new QChartView(chart);
	chartview->chart()->setTheme(QChart::ChartThemeBlueCerulean);
	chartview->setRenderHint(QPainter::Antialiasing);

	result = new QAction(tr("&Результат"), this);
	quit = new QAction(tr("&Выход"), this);
	
	file = menuBar()->addMenu(tr("&Файл"));
	file->addAction(result);
	file->addAction(quit);

	connect(quit, &QAction::triggered, qApp, QApplication::quit);
	connect(result, &QAction::triggered, this, &MainWindow::getResult);
}

void	MainWindow::getResult()
{
	double	max;
	QString	result;
	size_t	current_size;
	size_t	sample_size;
	bool	hypothesis_accepted;
	qreal	kolm_alpha;

	max = 0;
	hypothesis_accepted = true;
	kolm_alpha = kolm_reverse(alpha);
	sample_size = sample.size();
	current_size = resultNormal.size();

	for (size_t i = 0; i < current_size; i++)
		if (abs(resultEmpirical[i + 1] - resultNormal[i]) > max)
			max = abs(resultEmpirical[i + 1] - resultNormal[i]);

	if (max * sqrt(sample_size) > kolm_alpha)
		hypothesis_accepted = false;

	result = "Дано: ";
	result += NEWLINE + QString("n = ") + QString::number(sample.size());
	result += NEWLINE + QString::fromUtf8(CHAR_ALPHA) + " = " + QString::number(alpha);
	result += NEWLINE + QString::fromUtf8(CHAR_MU) + " = " + QString::number(mean) + TAB + QString::fromUtf8(CHAR_DELTA) + " = " + QString::number(shifted_variance);
	result += NEWLINE + QString::fromUtf8(CHARS_KOLM_R) + " = " + QString::number(kolm_alpha);
	result += NEWLINE + QString::fromUtf8(CHARS_D_N) + " = " + QString::fromUtf8(FORMULA_D_N) + " = " + QString::number(max);
	result += NEWLINE + QString::fromUtf8(CHAR_SQRT) + "n * " + QString::fromUtf8(CHARS_D_N) + " = " + QString::number(max * sqrt(sample_size));
	result += NEWLINE + QString(NEWLINE) + QString::fromUtf8(CHAR_SQRT) + "n * " + QString::fromUtf8(CHARS_D_N) + QString((hypothesis_accepted) ? (" <= ") : (" > ")) + QString::fromUtf8(CHARS_KOLM_R);
	result += " => " + QString("Гипотеза ") + QString((hypothesis_accepted) ? ("принята") : ("отвергнута"));
	/*result += NEWLINE + QString::number(max * sqrt(sample_size)) + " (" + QString::fromUtf8(CHAR_SQRT) + QString::fromUtf8("n * ") + QString::fromUtf8(CHARS_D_N) + ") ";
	result += (hypothesis_accepted) ? ("<=") : (">");
	result += " " + QString::number(kolm_reverse(0.05)) + "(" + QString::fromUtf8(CHARS_KOLM_R) + ")";*/

	QMessageBox::information(this, "Результат", result);
}

void MainWindow::initial(const std::vector<qreal>& sample, qreal alpha, qreal mean, qreal shifted_variance)
{
	this->alpha = alpha;
	this->mean = mean;
	this->shifted_variance = shifted_variance;
	this->sample.resize(sample.size());

	std::copy(sample.begin(), sample.end(), this->sample.begin());
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

QPen	MainWindow::getSettingsPen(QPen	oldPen = QPen())
{
	QPen	newPen;

	newPen = oldPen;

	newPen.setWidth(2);
	newPen.setCapStyle(Qt::FlatCap);

	return (newPen);
}

void	MainWindow::buildEmpiricalFunction()
{
	Axis			axisX;
	Axis			axisY;
	QValueAxis		*axisXX = new QValueAxis;
	QValueAxis		*axisYY = new QValueAxis;;
	QSplineSeries*	series = new QSplineSeries;
	QLineSeries*	lines = new QLineSeries;

	std::tie(interval, resultEmpirical) = calcEmpiricalFunction(sample);
	std::tie(std::ignore, resultNormal) = calcNormalfunction(sample);

	axisX.initial("X", interval[0], interval[interval.size() - 1], 20);
	axisY.initial("F(X)", 0, 1, 11);

	axisXX = axisX.getAxis();
	axisYY = axisY.getAxis();

	lines->append(interval.front(), resultEmpirical.front());
	for (int i = 0; i < interval.size() - 1; i++)
	{
		lines->append(interval[i], resultEmpirical[i + 1]);
		lines->append(interval[i + 1], resultEmpirical[i + 1]);
	}
	lines->append(interval.back(), resultEmpirical.back());
	lines->setColor(QColor::fromRgba(qRgb(255, 255, 0)));
	lines->setName("Эмпирическая функция распределения");

	chart->addSeries(lines);

	lines->setPen(getSettingsPen(lines->pen()));
	
	chart->setAxisX(axisXX, lines);
	chart->setAxisY(axisYY, lines);

	for (int i = 0; i < interval.size(); i++)
		series->append(interval[i], resultNormal[i]);

	series->setPen(getSettingsPen(series->pen()));
	series->setColor(QColor::fromRgba(qRgb(255, 0, 0)));
	series->setName("Функция нормального распределения (" + QString::fromUtf8(CHAR_MU) + " = 0, " + QString::fromUtf8(CHAR_DELTA) + " = 1)");

	chart->addSeries(series);
	chart->setAxisX(axisXX, series);
	chart->setAxisY(axisYY, series);

	chart->setAnimationOptions(QChart::SeriesAnimations);
	chart->setTitle("Эмпирическая функция распределения с наложением нормальной функции распределения");
	//chart->legend()->hide();
	
	layout->addWidget(chartview);
	ui->centralwidget->setLayout(layout);
}

MainWindow::~MainWindow()
{
	delete ui;
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

