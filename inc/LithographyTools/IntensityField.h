#ifndef INTENSITYFIELD_H
#define INTENSITYFIELD_H
#include <vector>
typedef std::vector<double> fieldRow;
typedef std::vector<fieldRow> fieldMatrix;

class IntensityField
{
    class ErrorIndexOutOfRangeException{};
    fieldMatrix _field;
    double _Min;
    double _Max;
    public:
        IntensityField(std::size_t rows,std::size_t cols);
        fieldMatrix GetMatrix() const;
        fieldRow &operator [](std::size_t index);
        fieldRow operator [](std::size_t index) const;
        std::size_t GetRows() const;
        std::size_t GetCols() const;
        double GetMax() const;
        double GetMin() const;
        void SetMax(double value);
        void SetMin(double value);

};

#endif // INTENSITYFIELD_H
