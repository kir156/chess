#include "mainwindow.h"
#include "ui_mainwindow.h"

template <typename T>
double getAverage(std::vector<T> &vec);

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

template<typename T>
double getAverage(std::vector<T> &vec) {
    double result = 0;
        for(int i = 0; i < vec.size(); ++i) {
            result += vec[i];
        }
        result /= vec.size();

        return result;
}

MainWindow::~MainWindow()
{
    delete ui;
}
