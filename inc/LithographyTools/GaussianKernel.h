#ifndef GAUSSIANKERNEL_H
#define GAUSSIANKERNEL_H
#include <vector>

typedef std::vector<double> kernel_row;
typedef std::vector<kernel_row> kernel_type;

class GaussianKernel
{
    static double GaussianFunc(double x, double sigma, double alpha=1.0, double mu=0);
public:
    GaussianKernel();
    static kernel_type CalculateGaussian2DKernel(int kernel_size, double sigma, double alpha);
};

#endif // GAUSSIANKERNEL_H
