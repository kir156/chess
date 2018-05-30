#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QImage>
#include <QFileDialog>
#include <QGraphicsItem>
#include <QGraphicsView>
#include <QColor>
#include <QtMath>
#include <QMatrix>
#include <QVector>
#include <QException>
#include <iostream>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    std::vector<float> pairConv(std::vector<float> &data, std::vector<float> &CL, std::vector<float> &CH, int delta = 0);
    void iCoeffs(std::vector<float> &CL, std::vector<float> &CH);
    void getColorComponent();
    std::vector<std::vector<float> > colorCoder(std::vector<std::vector<float> > &vector);
    void deleteLittleValuesOfComponent(std::vector<std::vector<float> > &imgMatrix);

private:
    Ui::MainWindow *ui;

    std::vector<float> CL, iCL, CH, iCH /*initialStringPixels, outputStringPixels*/;
    std::vector< std::vector<QColor> > vectorImage;

    std::vector< std::vector<float> > vectorImageRed;
    std::vector< std::vector<float> > vectorImageGreen;
    std::vector< std::vector<float> > vectorImageBlue;

    std::vector< std::vector<float> > redComponent;
    std::vector< std::vector<float> > greenComponent;
    std::vector< std::vector<float> > blueComponent;

    std::vector<float> promej;
    std::vector<float> outputStringPixels;
    std::vector<float> initialStringPixels;

    QString pathImage1, pathImage2, dir1, dir2;
    QImage image1, image2;
    QGraphicsItem *pix1, *pix2;
    QGraphicsScene *scene1, *scene2;
    QColor newComponent;
    int imgHeight, imgWidth, alpha;
    float coeff0, coeff1, coeff2, coeff3;

private slots:
    void on_pathButton_clicked();
    void on_compressed_clicked();

};

#endif // MAINWINDOW_H
