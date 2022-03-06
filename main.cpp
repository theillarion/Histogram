#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication        a(argc, argv);
    MainWindow          w;
    std::vector<qreal>  sample;

    sample = ft_read_file("C:\\Users\\pro10\\mygitrepo\\matstat00\\r1z1.csv");

    w.buildChart(sample);
    w.show();

    return (a.exec());
}
