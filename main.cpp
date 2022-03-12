#include "MainWindow.hpp"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication        a(argc, argv);
    MainWindow          w;
    QRect               screenGeometry;
    std::vector<qreal>  sample;

    screenGeometry = QGuiApplication::primaryScreen()->geometry();

    w.setWindowTitle("GGWP");
    w.setGeometry(QRect(300, 200, screenGeometry.width() - 600, screenGeometry.height() - 400));
   
    sample = ft_read_file("C:\\Users\\pro10\\OneDrive\\Документы\\matstat\\all\\10\\r2z2.csv");
    srand(time(NULL));
    //for (int i = 0; i < 10000; i++)
    //    sample.push_back(1 + rand() % 10);
    //sample = { 1, 2 };
    //w.buildChart(sample);
    w.buildEmpiricalFunction(sample);
    //w.buildGraphic(sample);
   // w.buildSin();
    //w.buildCos();
    w.show();

    return (a.exec());
}
