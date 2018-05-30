#include "mainwindow.h"

#include <QDebug>

void MainWindow::getColorComponent() {
    QImage image(imgWidth, imgHeight, QImage::Format_ARGB32);
    image2 = image;
    QString saveFile = "/Users/kirill/Desktop/new.jpg";

    for(int _height = 0; _height != imgHeight; ++_height) {
        for(int _width = 0; _width != imgWidth; ++_width) {

            redComponent[_width][_height] = (float) image1.pixelColor(_width, _height).red();            // возвращает красную компоненту изображения  в виде int
            greenComponent[_width][_height] = (float) image1.pixelColor(_width, _height).green();
            blueComponent[_width][_height] = (float) image1.pixelColor(_width, _height).blue();
        }
    }

    vectorImageRed = colorCoder(redComponent);
    vectorImageGreen = colorCoder(greenComponent);
    vectorImageBlue = colorCoder(blueComponent);

    for(int height = 0; height < imgHeight; ++height) {
        for(int width = 0; width < imgWidth; ++width) {
            image.setPixel(width, height, qRgb(vectorImageRed[width][height],
                                                vectorImageGreen[width][height],
                                                vectorImageBlue[width][height]));
        }
    }

    QPixmap a = QPixmap::fromImage(image);
    a.save(saveFile);

    pix2 = new QGraphicsPixmapItem(saveFile);
    pix2->setPos(0, 0);

    scene2->addItem(pix2);
    QPainter painter2(&image2);
    scene2->render(&painter2);

    ui -> textBrowser-> insertPlainText("\nDone");

}

std::vector<std::vector<float> > MainWindow::colorCoder(std::vector<std::vector<float> > &vector) {
    std::vector<std::vector<float> > vector1;
    int size = vector.size();
    std::vector<std::vector<float> > final(size, std::vector<float>(vector.at(0).size(), 0));
    std::vector<float > vector2;
    std::vector<float > vector3;

    vector1.resize(imgWidth);

    for(int i = 0; i < vector1.size(); ++i) {
        vector1[i].resize(imgHeight);
    }

    for(int width = 0; width < imgWidth; ++width) {   //vector1 содержит матрицу высоких и низких частот
        vector1[width] = pairConv(vector[width], CL, CH);
    }

    for(int height = 0; height < imgHeight; ++height) {
        vector2.clear();

        for(int width = 0; width < imgWidth; ++width) {
            vector2.push_back(vector1[width][height]);
        }

        vector2.shrink_to_fit();
        vector2 = pairConv(vector2, CL, CH);


        for(int width = 0; width < imgWidth; ++width) {
            vector1[width][height] = vector2[width];
        }
    }

    ui -> textBrowser-> insertPlainText("\nDone");

    //********
    for(int h = 0; h < imgHeight; ++h) {
        std::vector<float > vector;       //вектор, принимающий строку
        vector2.clear();
        vector3.clear();

        vector.reserve(imgWidth);

        for(int i = 0; i < imgWidth; ++i) {
            vector.push_back(vector1[i][h]);              //заполнение кодированной строкой
        }

        for(int i = 0; i < imgWidth; ++i) {
                if(i % 2 == 0) {
                    vector2.push_back(vector[i]);
                }
                else if(i % 2 != 0) {
                    vector3.push_back(vector[i]);
                }
        }

        vector.clear();
        long int indx = 0;

        for(float i : vector2) {
            final[indx][h] = i;
            ++indx;
        }

        for(float j : vector3) {
            final[indx][h] = j;
            ++indx;
        }
    }

    vector1 = final;

    for(int w = 0; w < imgWidth; ++w){          //переупорядочивание столбцов
        std::vector<float > vector;
        vector2.clear();
        vector3.clear();

        vector = vector1[w];                    //получаем столбец кодированного изображения

        for(int i = 0; i < imgHeight; ++i) {
            if(i % 2 == 0) {
                vector2.push_back(vector[i]);
            }
            else if(i % 2 != 0) {
                vector3.push_back(vector[i]);
            }
        }

        vector.clear();
        long int indx = 0;

        for(float i : vector2) {
            final[w][indx] = i;
            ++indx;
        }

        for(float j : vector3) {
            final[w][indx] = j;
            ++indx;
        }
    }

    return final;
}

void MainWindow::deleteLittleValuesOfComponent(std::vector<std::vector<float> > &imgMatrix) {

}
