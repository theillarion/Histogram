#include "MainWindow.hpp"
#include "ui_mainwindow.h"

using std::vector;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
	QMenu*		file;
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
	connect(result, &QAction::triggered, this, &MainWindow::ouputResult);
}

MainWindow::Data_result	MainWindow::calcResult()
{
	Data_result	result;
	size_t		current_size;

	result.is_accepted = true;
	result.supreme = 0;
	result.n = sample.size();
	result.alpha_critical = kolm_reverse<qreal>(alpha);
	current_size = resultNormal.size();
	
	for (size_t i = 0; i < current_size; i++)
		if (abs(resultEmpirical[i + 1] - resultNormal[i]) > result.supreme)
			result.supreme = abs(resultEmpirical[i + 1] - resultNormal[i]);

	result.stat = result.supreme * sqrt(result.n);

	if (result.stat > result.alpha_critical)
		result.is_accepted = false;

	result.interval_critical = QString("Критическая область (правосторонняя): A = {%1 : T(%1) > %2}").arg(QString::fromUtf8(CHARS_SAMPLE)).arg("C крит");
		

	return (result);
}

void	MainWindow::ouputResult()
{
	Data_result	data;
	QString		result;

	data = calcResult();

	#define UTF8(arg) QString::fromUtf8(arg)

	result = QString("Дано: \n");
	result += QString("n = %1 \n").arg(data.n);
	result += QString("%1 = %2 \n").arg(UTF8(CHAR_ALPHA)).arg(alpha);
	result += QString("%1 = %2\t%3 = %4 \n\n").arg(UTF8(CHAR_MU)).arg(mean).arg(UTF8(CHAR_DELTA)).arg(shifted_variance);
	result += QString("Вычислено: \n");
	result += QString("%1 = %2 \n").arg(UTF8(CHARS_KOLM_R)).arg(data.alpha_critical);
	result += QString("%1 = %2 = %3 \n").arg(UTF8(CHARS_D_N)).arg(UTF8(FORMULA_D_N)).arg(data.supreme);
	result += QString("T = %1 * %2 = %3 \n").arg(UTF8(CHAR_SQRT) + 'n').arg(UTF8(CHARS_D_N)).arg(data.stat);
	result += QString("Критическая точка = %1 \n").arg(data.alpha_critical);
	result += QString("%1 \n\n").arg(data.interval_critical);
	result += QString("Вывод: \n");
	result += QString("%1%2 %3 %4 => Гипотеза %5\n").arg(UTF8(CHAR_SQRT) + 'n').arg(UTF8(CHARS_D_N)).arg(data.is_accepted ? "<=" : ">")
		.arg(UTF8(CHARS_KOLM_R)).arg(data.is_accepted ? "принята" : "отвергнута");

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
	QValueAxis		*axisX;
	QValueAxis		*axisY;
	QSplineSeries*	series = new QSplineSeries;
	QLineSeries*	lines = new QLineSeries;

	std::tie(interval, resultEmpirical) = calcEmpiricalFunction(sample);
	std::tie(std::ignore, resultNormal) = calcNormalfunction(sample, mean, shifted_variance);

	axisX = makeAxis("X", interval[0], interval[interval.size() - 1], 20);
	axisY = makeAxis("F(X)", 0, 1, 11);

	lines->append(interval.front(), resultEmpirical.front());
	for (int i = 0; i < interval.size() - 1; i++)
	{
		lines->append(interval[i], resultEmpirical[i + 1]);
		lines->append(interval[i + 1], resultEmpirical[i + 1]);
	}
	lines->append(interval.back(), resultEmpirical.back());

	for (int i = 0; i < interval.size(); i++)
		series->append(interval[i], resultNormal[i]);

	lines->setName("Эмпирическая функция распределения");
	series->setName(QString("Функция нормального распределения (%1 = %2, %3 = %4)")
		.arg(QString::fromUtf8(CHAR_MU)).arg(mean).arg(QString::fromUtf8(CHAR_DELTA)).arg(shifted_variance));

	lines->setColor(QColor::fromRgba(qRgb(255, 255, 0)));
	series->setColor(QColor::fromRgba(qRgb(255, 0, 0)));

	chart->addSeries(lines);
	chart->addSeries(series);

	lines->setPen(getSettingsPen(lines->pen()));
	series->setPen(getSettingsPen(series->pen()));

	chart->setAxisX(axisX, lines);
	chart->setAxisY(axisY, lines);
	chart->setAxisX(axisX, series);
	chart->setAxisY(axisY, series);

	chart->setAnimationOptions(QChart::SeriesAnimations);
	chart->setTitle("Эмпирическая функция распределения с наложением нормальной функции распределения");
	
	layout->addWidget(chartview);
	ui->centralwidget->setLayout(layout);
}

MainWindow::~MainWindow()
{
	delete ui;
}