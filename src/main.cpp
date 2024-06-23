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
                                      {127, 127, 0}, {255, 255, 0}, {0,   255, 255}, {255, 0,   255}, {255, 127, 0}, {255, 0,   0}};

const int FLAT_HEIGHT = 600;
const int LEGEND_WIDTH = 200;


/*
void CSurfer::BuildDataList() const throw()
{
    BEGIN_GL
    C3DData* pdata;
    double xPos, yPos, thickness;
    double x, y, z;

    // We'll have only one C3DData*
    pdata = m_listData.front();

    ::glNewList(DATA_LIST, GL_COMPILE);
    double i;
    for(double j=0; j<m_dZrange-1; j+=1) {
        ::glBegin(GL_TRIANGLE_STRIP);
        i = 0;
        xPos = i;
        yPos = j;
        thickness = pdata->GetZdata((int}(i + m_dXrange*j});
        x = -m_dXrange/2+xPos;
        y = -m_dYrange/2+thickness;
        z = -m_dZrange/2+yPos;
        SetDataColor(thickness);
        ::glVertex3f(x, y, z);
        for(i=0; i<m_dXrange; i+=1) {
            xPos = i;
            yPos = j+1;
            thickness = pdata->GetZdata((int)(i + m_dXrange*(j+1)));
            x = -m_dXrange/2+xPos;
            y = -m_dYrange/2+thickness;
            z = -m_dZrange/2+yPos;
            SetDataColor(thickness);
            ::glVertex3f(x, y, z);

            xPos = i+1;
            yPos = j;
            thickness = pdata->GetZdata((int)(i + 1 + m_dXrange*j));
            x = -m_dXrange/2+xPos;
            y = -m_dYrange/2+thickness;
            z = -m_dZrange/2+yPos;
            SetDataColor(thickness);
            ::glVertex3f(x, y, z);
        }
        ::glEnd();
    }
    ::glEndList();
    END_GL
}*/


void D2View(vector<double> &vecZs, int nDiameter, double m_dThickMin, double m_dThickMax, int m_nNumOfLevels = 11) {

    double interval = (m_dThickMax - m_dThickMin) / (m_nNumOfLevels - 1);
    unsigned char * p_img = nullptr, *p_img_start= nullptr;
    unsigned x, y;

    FILE *fp = fopen("rgb_1.png", "wb");
    int img_data_pixels = nDiameter * nDiameter;
    p_img_start  = new unsigned char[ img_data_pixels * 3];
    p_img = p_img_start;

    // create an image.  of width nDiameter, height nDiameter.
    for (int i = 0; i < img_data_pixels; i++) {
        double z = vecZs[i];
        int index = (int) ((z - m_dThickMin) / interval);

        *(p_img++) = Colors[index][0];    /* R */
        *p_img++ =  Colors[index][1];    /* G */
        *p_img++ = Colors[index][2];    /* B */
    }

    svpng(fp, nDiameter, nDiameter, p_img_start, 0);
    fclose(fp);
    delete p_img_start;
}


void D3View(vector<double> &vecZs, int nDiameter, double m_dThickMin, double m_dThickMax) {
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


// https://www.cnblogs.com/arxive/p/5119632.html
int main() {
    InputReader m_ir;
    std::string test_data;
    int interpolaterMode = 0;
    double m_dThickMin;
    double m_dThickMax;
    int nDiameter = 300;

    // data read
    test_data = "/home/weng/DEV/pros/prod/algoui/test/test_kriging_weng/data/testdata.txt";
    m_ir.Read(test_data);

    // interplot
    auto &input = const_cast<vector<Point3D> &>(m_ir.Get3DPoints());
    Interpolater *pInterpolater = nullptr;
    if (interpolaterMode == 0)
        pInterpolater = new InverseDist(200, 4);
    else if (interpolaterMode == 1)
        pInterpolater = new Kriging(input.begin(), input.end(), 4);

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


    D2View(vecZs, nDiameter, m_dThickMax, m_dThickMin);
    // D3View(vecZs, nDiameter, m_dThickMax, m_dThickMin);


    return 0;
}

