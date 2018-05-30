#include "mainwindow.h"

std::vector<float> MainWindow::pairConv(std::vector<float> &data,std::vector<float> &CL, std::vector<float> &CH, int delta) {
    if(CL.size() == CH.size()) {
        std::vector<float> out;

        int N = CL.size();
        int M = data.size();

        for(int i = 0; i != M; i += 2) {
            float sL = 0;
            float sH = 0;

            for(int k = 0; k < N; ++k) {
                sL += data[(i + k - delta) % M] * CL[k];
                sH += data[(i + k - delta) % M] * CH[k];
            }

            out.push_back(sL);
            out.push_back(sH);
        }

        return out;
    }
}

void MainWindow::iCoeffs(std::vector<float> &CL, std::vector<float> &CH) {
    if(CL.size() == CH.size()) {
        for(int k = 0; k < CL.size(); k += 2) {
            if(k == 0) {
                int i = CL.size() - 1;

                iCL.push_back(CL[i-1]);
                iCL.push_back(CH[i-1]);
                iCH.push_back(CL[i]);
                iCH.push_back(CH[i]);
            }
            else {
                iCL.push_back(CL[k-2]);
                iCL.push_back(CH[k-2]);
                iCH.push_back(CL[k-1]);
                iCH.push_back(CH[k-1]);
            }
        }
    }
}
