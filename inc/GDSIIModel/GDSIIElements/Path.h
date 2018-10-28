#ifndef PATH_H
#define PATH_H

#include "GDSIIElement.h"
class Path:public GDSIIElement
{
    short DATATYPE;//????
    short PATHTYPE;
    int BGNEXTN;
    int ENDEXTN;
    int WIDTH;

    bool pathTypeFlag;
    bool bgnExtnFlag;
    bool endExtnFlag;
    bool widthFlag;

public:
    Path();
    ~Path();
    void Show();

    void SetPoints(const std::vector<GDSIIPoint> &source, int amount);

    void SetPathType(short p_type);
    short GetPathType();

    void SetBgnExtn(int b_extn);
    int GetBgnExtn();

    void SetEndExtn(int e_extn);
    int GetEndExtn();

    void SetWidth(int width);
    int GetWidth();

    void SetDataType(short data_t);
    short GetDataType();

    bool HasWidth();
    bool HasPathType();
    bool HasBgnExtn();
    bool HasEndExtn();

};

#endif // PATH_H
