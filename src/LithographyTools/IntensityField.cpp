#include "inc/LithographyTools/IntensityField.h"

IntensityField::IntensityField(std::size_t rows, std::size_t cols):
    _field(rows,fieldRow(cols)),
    _Min(0),
    _Max(0)
{}

fieldMatrix IntensityField::GetMatrix() const
{
    return _field;
}

fieldRow& IntensityField::operator [](std::size_t index)
{
    if(_field.size()>0 && index<_field.size())
        return _field[index];
    else throw ErrorIndexOutOfRangeException();
}

fieldRow IntensityField::operator [](std::size_t index) const
{
    if(_field.size()>0 && index<_field.size())
        return _field[index];
    else throw ErrorIndexOutOfRangeException();
}

std::size_t IntensityField::GetRows() const
{
    return _field.size();
}

std::size_t IntensityField::GetCols() const
{
    return _field[0].size();
}

double IntensityField::GetMax() const
{
    return _Max;
}
double IntensityField::GetMin() const
{
    return _Min;
}

void IntensityField::SetMax(double value)
{
    _Max=value;
}
void IntensityField::SetMin(double value)
{
    _Min=value;
}
