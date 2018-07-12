#include <QImage>
#include <QRgb>
#include <algorithm>
#include "mmcq.h"


MMCQ::MMCQ(QString file)
{
    QImage i(file);
    img = new QImage(i.convertToFormat(QImage::Format_RGBA8888));
}

MMCQ::~MMCQ()
{
    delete img;
}

int MMCQ::get_color_index(int r, int g, int b)
{
    return (r << (2 * sigbits)) + (g << sigbits) + b;
}

void MMCQ::calc_histo()
{
    int index = 0;
    for (int i = 0; i < img->colorCount(); i++) {
        index = get_color_index(qRed(img->color(i)) >> rshift, qGreen(img->color(i)) >> rshift, qBlue(img->color(i)) >> rshift);
        histo[index]++;
    }
}

VBox MMCQ::gen_vbox()
{
    int rval, gval, bval;
    int rmin = 1000000;
    int rmax = 0;
    int gmin = 1000000;
    int gmax = 0;
    int bmin = 1000000;
    int bmax = 0;
    for (int i = 0; i < img->colorCount(); i++) {
        rval = qRed(img->color(i)) >> rshift;
        gval = qGreen(img->color(i)) >> rshift;
        bval = qBlue(img->color(i)) >> rshift;

        rmin = std::min(rval, rmin);
        rmax = std::max(rval, rmax);
        gmin = std::min(gval, gmin);
        gmax = std::max(gval, gmax);
        bmin = std::min(bval, bmin);
        bmax = std::max(bval, bmax);
    }

    VBox vbox(rmin, rmax, gmin, gmax, bmin, bmax);
    return vbox;
}

std::vector<VBox> MMCQ::do_median_cut(VBox v)
{

}

VBox::VBox()
{
    r1 = 0;
    g1 = 0;
    b1 = 0;
    r2 = 0;
    g2 = 0;
    b2 = 0;
}

VBox::VBox(int r1, int g1, int b1, int r2, int g2, int b2)
{
    this->r1 = r1;
    this->g1 = g1;
    this->b1 = b1;
    this->r2 = r2;
    this->g2 = g2;
    this->b2 = b2;
}
