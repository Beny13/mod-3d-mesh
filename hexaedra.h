#ifndef HEXAEDRA_H
#define HEXAEDRA_H

#include <QtCore>

class Hexaedra
{
public:
    Hexaedra();
    Hexaedra(int i1, int i2, int i3, int i4, int i5, int i6, int i7, int i8);
    QString format() const;
private:
    int i1, i2, i3, i4, i5, i6, i7, i8;
};

#endif // HEXAEDRA_H
