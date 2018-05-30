#include "mainwindow.cpp"

void MainWindow::on_pathCat_adm_clicked() {
    dir1 = QFileDialog::getExistingDirectory(
                         this, tr("Open Directory"),
                         "/home", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

    QDir dirName(dir1);
    dirName.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
    dirName.setSorting(QDir::Name);

    dirList = dirName.entryInfoList();
    ui -> linePath_adm -> setText(dir1);
}

void MainWindow::on_start_adm_clicked() {

    std::ofstream fout_classes("/Users/kirill/Desktop/class.txt", std::ios_base::app);

    while(ui->nameClass_adm->text().isEmpty() ||
          ui->nameClass_adm->text() == "Введите название класса!!!") {
        ui->nameClass_adm->setText("Введите название класса!!!");
        return;
    }

    std::ofstream fout("/Users/kirill/Desktop/" + ui->nameClass_adm->text().toStdString() +".txt");

    class_name = ui->nameClass_adm->text();

    for (QFileInfoList::iterator it = dirList.begin() + 1; it != dirList.end(); ++it) {
        int fileNum = 0;

        std::vector<std::vector<int> > brightness_MPS(255, std::vector<int>(255, 0));

        QFileInfo fileInfo(*it);
        QString name = fileInfo.fileName();

        MoM = 0;
        blackArea   = 0;
        cellPer     = 0;

        blueComp.clear();
        MomOfInertion.clear();

        pathLine_adm = dir1 + '/' + name;

        scene1 = new QGraphicsScene();
        pix1 = new QGraphicsPixmapItem(pathLine_adm);
        pix1->setPos(0, 0);
        scene1->addItem(pix1);

        QImage image(scene1->width(), scene1->height(), QImage::Format_ARGB32_Premultiplied);
        image1 = image;
        image1.fill(NULL);
        QPainter painter1(&image1);
        scene1->render(&painter1);

        imgHeight = image1.height();
        imgWidth = image1.width();
        imgArea = imgHeight * imgWidth;

        for(int height = 0; height < imgHeight; ++height) {
            for(int width = 0; width < imgWidth; ++width) {
                if(image1.pixel(width, height) == qRgb(0, 0, 0) ||
                   image1.pixel(width, height) == qRgb(255, 255, 255)) {           //ищем все черные пикселы - не относящиеся к клетке
                    ++blackArea;
                }
                else {
                    if((width  > 0 || height > 0) &&
                       (width < imgWidth - 1 || height < imgHeight - 1)) {
                        if((image1.pixel(width - 1, height) == qRgb(0, 0, 0) || image1.pixel(width - 1, height) == qRgb(255, 255, 255)) ||
                           (image1.pixel(width, height - 1) == qRgb(0, 0, 0) || image1.pixel(width, height - 1) == qRgb(255, 255, 255)) ||
                           (image1.pixel(width + 1, height) == qRgb(0, 0, 0) || image1.pixel(width + 1, height) == qRgb(255, 255, 255)) ||
                           (image1.pixel(width, height + 1) == qRgb(0, 0, 0) || image1.pixel(width, height + 1) == qRgb(255, 255, 255))) {
                            ++cellPer;
                        }
                    }

                    blueComp.push_back((double) image1.pixelColor(width, height).blue());    //получаем синюю компоненту

                    int red = image1.pixelColor(width, height).red();
                    int red_Next = image1.pixelColor(width + 1, height).red();
                    int green = image1.pixelColor(width, height).green();
                    int green_Next = image1.pixelColor(width + 1, height).green();
                    int blue = image1.pixelColor(width, height).blue();
                    int blue_Next = image1.pixelColor(width + 1, height).blue();

                    int brightness = (int) (red + green + blue) / 3;
                    int brightness_Next = (int) (red_Next + green_Next + blue_Next) / 3;

                    ++brightness_MPS[brightness][brightness_Next];                  //заполняем МПС
                }
            }
        }

        for(int i = 0; i < 255; ++i) {
            for(int j = 0; j < 255; ++j) {
                MoM += sqrt(std::pow(i - j, 2) * brightness_MPS[i][j]);
            }
        }

        blueComp.shrink_to_fit();
        MomOfInertion.shrink_to_fit();

        blueComp_AVRG = getAverage(blueComp);
        cellPer *= sqrt(2);
        cellArea = imgArea - blackArea;
        koefForm = std::pow(cellPer, 2) /(4 * 3.14 * cellArea);

        signs_of_cell.push_back(std::make_tuple(koefForm, blueComp_AVRG, MoM));

        fout << fileNum
             << ";" << std::get<0>(signs_of_cell[fileNum])
//             << "\tPerimetr:" << cellPer
//             << "\tArea:" << cellArea
             << ";" << std::get<1>(signs_of_cell[fileNum])
             << ";" << std::get<2>(signs_of_cell[fileNum])
             << '\n';
        ++fileNum;
    }

    signs_of_cell.shrink_to_fit();

    radius_blue.reserve(signs_of_cell.size());
    radius_form.reserve(signs_of_cell.size());
    radius_MoM.reserve(signs_of_cell.size());
    radius_blue_AVRG.reserve(signs_of_cell.size());
    radius_form_AVRG.reserve(signs_of_cell.size());
    radius_MoM_AVRG.reserve(signs_of_cell.size());

    radius_blue_AVRG.clear();
    radius_form_AVRG.clear();
    radius_MoM_AVRG.clear();

    for(int i = 0; i < signs_of_cell.size(); ++i) {
        radius_blue.clear();
        radius_form.clear();
        radius_MoM.clear();

        for(int j = 0; j < signs_of_cell.size(); ++j) {
            if(i == j) {
                continue;
            }
            else if(i != j) {
                double distance_koeff = sqrt(std::pow(std::get<0>(signs_of_cell[i]) - std::get<0>(signs_of_cell[j]), 2));
                radius_form.push_back(distance_koeff);

                double distance_blue =  sqrt(std::pow(std::get<1>(signs_of_cell[i]) - std::get<1>(signs_of_cell[j]), 2));
                radius_blue.push_back(distance_blue);

                double distance_MoM =  sqrt(std::pow(std::get<2>(signs_of_cell[i]) - std::get<2>(signs_of_cell[j]), 2));
                radius_MoM.push_back(distance_MoM);
            }
        }
        radius_form_AVRG.push_back(getAverage(radius_form));
        radius_blue_AVRG.push_back(getAverage(radius_blue));
        radius_MoM_AVRG.push_back(getAverage(radius_MoM));
    }

    double rad_koeff = getAverage(radius_form_AVRG);
    double rad_blue = getAverage(radius_blue_AVRG);
    double rad_MoM = getAverage(radius_MoM_AVRG);


//    получение коордиат центра
    double result = 0;

    for(int i = 0; i < signs_of_cell.size(); ++i) {
        result += std::get<0>(signs_of_cell[i]);
    }

    result /= signs_of_cell.size();

    fout_classes << ui->nameClass_adm->text().toStdString()
         << ":" << result;
    result = 0;

    for(int i = 0; i < signs_of_cell.size(); ++i) {
        result += std::get<1>(signs_of_cell[i]);
    }

    result /= signs_of_cell.size();

    fout_classes << ":" << result;
    result = 0;

    for(int i = 0; i < signs_of_cell.size(); ++i) {
        result += std::get<2>(signs_of_cell[i]);
    }

    result /= signs_of_cell.size();

    fout_classes << ":" << result;

    fout_classes << ":" << rad_koeff
                 << ":" << rad_blue
                 << ":" << rad_MoM << std::endl;
}
