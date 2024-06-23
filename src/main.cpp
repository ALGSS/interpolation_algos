//
// Created by weng on 6/22/24.
//
#include <algorithm>
#include "input_reader.h"
#include "inverse_dist.h"
#include "kriging.h"
#include "data/3DData.h"

#include "../thirdparty/svpng/svpng.inc"


static unsigned char Colors[11][3] = {{127, 127, 127}, {0,   0,   127}, {0,   0,   255}, {0,   127, 127}, {0,   255, 0},
                                      {127, 127, 0}, {255, 255, 0}, {0,   255, 255}, {255, 0,   255}, {255, 127, 0},
                                      {255, 0,   0}};


void WriteData2Img(std::string &img_file_info, vector<double> &vecZs, int nDiameter, double m_dThickMin, double m_dThickMax, int m_nNumOfLevels = 11) {

    double interval = (m_dThickMax - m_dThickMin) / (m_nNumOfLevels - 1);
    unsigned char *p_img = nullptr, *p_img_start = nullptr;
    unsigned x, y;

    FILE *fp = fopen(("interpolated_result_" + img_file_info + ".png").c_str(), "wb");
    int img_data_pixels = nDiameter * nDiameter;
    p_img_start = new unsigned char[img_data_pixels * 3];
    p_img = p_img_start;

    // create an image.  of width nDiameter, height nDiameter.
    for (int i = 0; i < img_data_pixels; i++) {
        double z = vecZs[i];
        int index = (int) ((z - m_dThickMin) / interval);

        *p_img++ = Colors[index][0];        // R
        *p_img++ = Colors[index][1];        // G
        *p_img++ = Colors[index][2];        // B
    }
    svpng(fp, nDiameter, nDiameter, p_img_start, 0);


    // finally
    std::cout << "write interpolation result done! " << std::endl;
    fclose(fp);
    delete p_img_start;
}


void ViewIn3D(vector<double> &vecZs, int nDiameter, double m_dThickMin, double m_dThickMax) {
    // These 3 lines are for determining thickness range. Typical thickness range 4000~7000 is too big
    // compared to x, y range of 200 so I had to reduce it.
    double MinMaxDiff = m_dThickMax - m_dThickMin;
    double widthRatio = nDiameter;
    double ratio = MinMaxDiff / widthRatio * 4;

    int dataSize = (nDiameter + 1) * (nDiameter + 1);
    C3DData *pdata = C3DData::GetInstance();
    pdata->SetSize(dataSize);

    int ii = 0;
    for (int j = 0; j <= nDiameter; j++) {
        for (int i = 0; i <= nDiameter; i++) {
            pdata->SetAt(ii, i, j, (vecZs[ii] - m_dThickMin) / ratio);
            ++ii;
        }
    }

    // GetGrapher().Add3DData(pdata);
    // GetGrapher().SetAxisRange(nDiameter + 1, (m_dThickMax-m_dThickMin)/ratio, nDiameter);
    // GetGrapher().SetMinValue(0);
    // GetGrapher().SetTitles("", "Y", "Thickness(mm)", "X");
    // GetGrapher().SetCullFace(false);
    //
    // CGLSurfaceView::OnInitialUpdate();
    //
    //
    // // GetGrapher().SetLegend(!GetGrapher().IsLegend());
    // GetGrapher().SetWall(!GetGrapher().IsWall());
    // GetGrapher().SetBoundary(!GetGrapher().IsBoundary());
    // GetGrapher().SetCullFace(!GetGrapher().IsCullFace());
    // GetGrapher().SetShadeModel(C3DGrapher::SMOOTH);
    // GetGrapher().SetShadeModel(C3DGrapher::FLAT);
    // GetGrapher().SetBkGndColor(dlg.GetColor());
}


int main(int argc, char **argv) {
    InputReader m_ir;
    std::string data_file_test_path;
    int interpolater_mode;
    double m_dThickMin;
    double m_dThickMax;
    int nDiameter = 300;
    std::string img_name;

    // para parse
    if (argc != 3) {
        std::cout << "not a valid number of parameters. please check it out." << std::endl;
        exit(-1);
    }
    data_file_test_path = argv[1];
    interpolater_mode = std::stoi(argv[2]);

    // data read
    m_ir.Read(data_file_test_path);

    // interplot
    auto &input = const_cast<vector<Point3D> &>(m_ir.Get3DPoints());
    Interpolater *pInterpolater;
    if (interpolater_mode == 0)
    {
        pInterpolater = new InverseDist(200, 4);
        img_name =  "inverse_dist";
    }
    else if (interpolater_mode == 1) {
        pInterpolater = new Kriging(input.begin(), input.end(), 4);
        img_name =  "kriging";
    }
    else {
        std::cout << "wrong interplot mode." << std::endl;
        exit(-2);
    }

    vector<double> vecZs;

    for (int row_y = 0; row_y < nDiameter; row_y++) {
        for (int col_x = 0; col_x < nDiameter; col_x++) {
            double z = pInterpolater->GetInterpolatedZ(row_y - nDiameter / 2, col_x - 0.5 * nDiameter, input.begin(), input.end());
            vecZs.push_back(z);
        }
    }
    delete pInterpolater;


    // for visual output
    vector<double>::iterator iter2;
    iter2 = max_element(vecZs.begin(), vecZs.end());
    m_dThickMax = *iter2;
    iter2 = min_element(vecZs.begin(), vecZs.end());
    m_dThickMin = *iter2;


    WriteData2Img(img_name, vecZs, nDiameter, m_dThickMax, m_dThickMin);
    if (interpolater_mode == 1)
        ViewIn3D(vecZs, nDiameter, m_dThickMax, m_dThickMin);


    return 0;
}

