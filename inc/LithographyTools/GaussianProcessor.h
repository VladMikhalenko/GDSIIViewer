#ifndef GAUSSIANPROCESSOR_H
#define GAUSSIANPROCESSOR_H

#include "inc/LithographyTools/GaussianKernel.h"
#include "inc/LithographyTools/IntensityField.h"
#include "inc/GUI/GDSIILineContainer.h"
class GaussianProcessor
{
    kernel_type _gaussKernel;
    int _kernel_size;
    double _curveHeight;
    double _bellWidth;
    unsigned _rayStep;
public:
    explicit GaussianProcessor(int kSize,double cHeight, double bWidth, unsigned rayStep);
    void ProcessLineContainer(IntensityField& field, const GDSIILineContainer& container);
    double getCurveHeight();
    void   setCurveHeight(double value);
    double getBellWidth();
    void   setBellWidth(double value);
    unsigned getRayStep();
    void     setRayStep(unsigned value);
};

#endif // GAUSSIANPROCESSOR_H
