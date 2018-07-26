#ifndef GAUSSIANKERNEL_H
#define GAUSSIANKERNEL_H
#include <vector>

typedef std::vector<double> kernel_row;
typedef std::vector<kernel_row> kernel_type;

class GaussianKernel
{
    static double GaussianFunc(double x, double sigma);
public:
    GaussianKernel();
    static kernel_type CalculateGaussian2DKernel(int kernel_radius);
};

#endif // GAUSSIANKERNEL_H
