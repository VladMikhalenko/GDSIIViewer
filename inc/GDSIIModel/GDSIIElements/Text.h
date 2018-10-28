#ifndef TEXT_H
#define TEXT_H

#include "GDSIIElement.h"

class Text:public GDSIIElement
{
    //textbody
    short TEXTTYPE;
    std::bitset<16> PRESENTATION;
    short PATHTYPE;
    int WIDTH;
    bool presentFlag;
    bool pathTypeFlag;
    bool widthFlag;

    //strans part
    double MAG;
    double ANGLE;
    bool magFlag;
    bool angleFlag;

    std::string STRING;

public:
    Text();
    ~Text();
    void Show();

    void SetPoints(const std::vector<GDSIIPoint> &source, int amount);

    void SetTextType(short t_type);
    short GetTextType();

    void SetPresentation(std::bitset<16> bits);
    std::bitset<16> GetPresentation();

    void SetPathType(short p_type);
    short GetPathType();

    void SetWidth(int width);
    int GetWidth();

    void SetMag(double mag);
    double GetMag();

    void SetAngle(double angle);
    double GetAngle();

    void SetString(std::string str);
    std::string GetString();

    bool HasPathType();
    bool HasWidth();
    bool HasMag();
    bool HasAngle();
    bool HasPresentation();


};

#endif // TEXT_H
