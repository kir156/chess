#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QImage>
#include <QFileDialog>
#include <QGraphicsItem>
#include <QGraphicsView>
#include <iostream>
#include <QtMath>
#include <fstream>
#include <tuple>
#include <QSqlDatabase>
//#include <QFileDialog>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    std::vector<std::tuple<double, double, double> >    signs_of_cell;
    std::vector<double>                                 blueComp;
    std::vector<long double>                            MomOfInertion;

    std::vector<double>                                 radius_blue;
    std::vector<double>                                 radius_form;
    std::vector<double>                                 radius_MoM;
    std::vector<double>                                 radius_blue_AVRG;
    std::vector<double>                                 radius_form_AVRG;
    std::vector<double>                                 radius_MoM_AVRG;

    int imgHeight, imgWidth, imgArea, blackArea, cellArea, cellPer;
    double blueComp_AVRG, MoI_AVRG, koefForm, MoM;

    QString pathLine_adm, pathLine, className, dir1, class_name;

    QImage          image1;
    QGraphicsItem   *pix1;
    QGraphicsScene  *scene1;
    QFileInfoList   dirList;

    QSqlDatabase db;

private slots:
    void on_pathCat_adm_clicked();
    void on_start_adm_clicked();
//    void on_pathCat_clicked();
//    void on_start_clicked();
};

#endif // MAINWINDOW_H
