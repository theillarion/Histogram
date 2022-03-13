#include "MainWindow.hpp"
#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication        a(argc, argv);
	MainWindow          w;
	std::vector<qreal>  sample;
	QRect               screenGeometry;
   
	screenGeometry = QGuiApplication::primaryScreen()->geometry();
	sample = ft_read_file("C:\\Users\\pro10\\OneDrive\\Документы\\matstat\\all\\10\\r2z2.csv");

	w.initial(sample, 0.05, 0, 1);
	w.setWindowTitle("GGWP");
	w.setGeometry(QRect(300, 200, screenGeometry.width() - 600, screenGeometry.height() - 400));

	w.buildEmpiricalFunction();
	w.show();

	return (a.exec());
}

//srand(time(NULL));
   //for (int i = 0; i < 10000; i++)
   //    sample.push_back(1 + rand() % 10);
   //sample = { 1, 1, 2, 2, 2, 3, 4, 4, 4, 4, 4, 4};