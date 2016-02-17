#include "hexaedra.h"

Hexaedra::Hexaedra(){}

Hexaedra::Hexaedra(int i1, int i2, int i3, int i4, int i5, int i6, int i7, int i8)
 : i1(i1), i2(i2), i3(i3), i4(i4), i5(i5), i6(i6), i7(i7), i8(i8){

}

QString Hexaedra::format() const
{
    QString res;
    QTextStream stream(&res);
    stream << i1 + 1 << " "
           << i2 + 1 << " "
           << i3 + 1 << " "
           << i4 + 1 << " "
           << i5 + 1 << " "
           << i6 + 1 << " "
           << i7 + 1 << " "
           << i8 + 1 << " 0";
    return res;
}
