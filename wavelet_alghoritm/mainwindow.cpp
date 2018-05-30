#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mathematic.cpp"
#include "coder.cpp"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    CL.reserve(4);
    CH.reserve(4);

    coeff0 = (1 + sqrt(3)) / (4 * sqrt(2));
    coeff1 = (3 + sqrt(3)) / (4 * sqrt(2));
    coeff2 = (3 - sqrt(3)) / (4 * sqrt(2));
    coeff3 = (1 - sqrt(3)) / (4 * sqrt(2));

    ui -> textBrowser-> insertPlainText(" Program starts method Dobeshi D4 \n**************************************\n"
                                        "1 coeff:" + QString::number(coeff0) + "\n" +
                                        "2 coeff:" + QString::number(coeff1) + "\n" +
                                        "3 coeff:" + QString::number(coeff2) + "\n" +
                                        "4 coeff:" + QString::number(coeff3) + "\n");

    CL = {coeff0, coeff1, coeff2, coeff3};          //фильтр низких частот для D4
    CH = {coeff3, -coeff2, coeff1, -coeff0};        //фильтр высоких частот для D4

    iCoeffs(CL, CH);                                //коэффициенты транспонированной матрицы

//    CL = {0.5, 0.5};
//    CH = {0.5, -0.5};        //фильтры для метода Хаара

    outputStringPixels.reserve(4);
    promej.reserve(4);

//    promej = pairConv(initialStringPixels, CL, CH);
//    outputStringPixels = pairConv(promej, iCL, iCH, CL.size() - 2);
}

void MainWindow::on_pathButton_clicked() {
    dir1 = QFileDialog::getOpenFileName(this,
                                       tr("Open Image"), "/home", tr("Image Files (*.png *.jpg *.bmp)"));

    QDir dirName(dir1);
    dirName.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
    dirName.setSorting(QDir::Name);

    pathImage1 = dir1;
    ui -> pathLine -> setText(dir1);

    scene1 = new QGraphicsScene();
    ui -> initialImage -> setScene(scene1);

    scene2 = new QGraphicsScene();
    ui -> compressedImage -> setScene(scene2);

    pix1 = new QGraphicsPixmapItem(pathImage1);
    pix1->setPos(0, 0);

    scene1->addItem(pix1);

    QImage image(scene1->width(), scene1->height(), QImage::Format_ARGB32);
    image1 = image;
    QPainter painter1(&image1);
    scene1->render(&painter1);

    imgHeight = image1.height();
    imgWidth = image1.width();

    vectorImage.resize(imgWidth);                     //создание вектора изображения
    redComponent.resize(imgWidth);
    greenComponent.resize(imgWidth);
    blueComponent.resize(imgWidth);

    for(int i = 0; i < vectorImage.size(); ++i) {
        vectorImage[i].resize(imgHeight);
        redComponent[i].resize(imgHeight);
        greenComponent[i].resize(imgHeight);
        blueComponent[i].resize(imgHeight);
    }

    ui->textBrowser->insertPlainText(QString::number(image1.pixel(255, 255)));
}

void MainWindow::on_compressed_clicked() {
    getColorComponent();
}

MainWindow::~MainWindow()
{
    delete ui;
}
