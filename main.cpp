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
   
    sample = ft_read_file("C:\\Users\\pro10\\mygitrepo\\matstat00\\r1z1.csv");

    //w.buildChart(sample);
    w.buildEmpiricalFunction(sample);
    w.show();

    return (a.exec());
}
