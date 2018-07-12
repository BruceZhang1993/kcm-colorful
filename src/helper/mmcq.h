#ifndef MMCQ_H
#define MMCQ_H

#include <QImage>
#include <QtCore>
#include <unordered_map>
#include <vector>

class VBox
{
public:
    VBox();
    explicit VBox(int r1, int g1, int b1, int r2, int g2, int b2);
    ~VBox();

    int r1, g1, b1, r2, g2, b2;
};


class MMCQ
{
public:
    explicit MMCQ(QString file);
    ~MMCQ();

private:
    int sigbits = 5;
    int rshift = 8 - sigbits;
    QImage *img;
    std::unordered_map<int, int> histo;

    int get_color_index(int r, int g, int b);
    void calc_histo();
    VBox gen_vbox();
    std::vector<VBox> do_median_cut(VBox v);

};




#endif
