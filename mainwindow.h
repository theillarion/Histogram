#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>
#include "axishistrogram.h"

std::vector<double>	ft_read_file(const std::string path);
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void buildChart(const std::vector<qreal>& sample);

private:
    Ui::MainWindow *ui;
};

#endif
