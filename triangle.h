#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <QtCore>

class Triangle
{
public:
    Triangle();
    Triangle(int index1, int index2, int index3);
    int getIndex1() const;
    void setIndex1(int value);

    int getIndex2() const;
    void setIndex2(int value);

    int getIndex3() const;
    void setIndex3(int value);

    bool hasIndex(int index);

    QString format() const;

private:
    int index1;
    int index2;
    int index3;
};

#endif // TRIANGLE_H
