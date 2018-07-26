#include "GaussianKernel.h"
#include <math.h>
#include <iostream>
#include <iomanip>
GaussianKernel::GaussianKernel()
{

}
double GaussianKernel::GaussianFunc(double x, double sigma)
{
    /* alpha - is curve height
     * mu - is position of center of the curve peak
     * sigma is "bell" width
     *
    */
    //double ALPHA=1/(sigma*sqrt(2*M_PI));
    const double ALPHA=0.5;//0.45;
    const double MU=0.0;
    return exp(-(((x-MU)/sigma)*((x-MU)/sigma))/2.0)*ALPHA;
}

kernel_type GaussianKernel::CalculateGaussian2DKernel(int radius)
{
    const int KERNEL_SIZE=1199;//*radius+1;//1201;
    const double SIGMA=radius/2.5;//bell width    WAS 8 BEFORE BEGAN TO TEST BLACK
    const int HALF_SIZE=KERNEL_SIZE/2;

    kernel_type kernel2d(KERNEL_SIZE,kernel_row(KERNEL_SIZE));

    double sum=0.0;//accumulation for normalization
    for(unsigned row=0;row<kernel2d.size();row++)
        for(unsigned col=0;col<kernel2d[row].size();col++)
        {
            double gx=GaussianFunc(static_cast<int>(row-HALF_SIZE),SIGMA);
            double gy=GaussianFunc(static_cast<int>(col-HALF_SIZE),SIGMA);
            double val=gx*gy;
            kernel2d[row][col]=val;
            sum+=val;
        }
    //normalize
//    std::cout<<std::setprecision(5)<<std::fixed;
//    for(int row=0;row<kernel2d.size();row++)
//    {
//        for(int col=0;col<kernel2d[row].size();col++)
//        {
//            //kernel2d[row][col]/=sum;
//            std::cout<<kernel2d[row][col]<<' ';
//        }
//        std::cout<<std::endl;
//    }

    return kernel2d;
}
