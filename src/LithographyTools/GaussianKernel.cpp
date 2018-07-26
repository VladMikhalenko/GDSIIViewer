#include "inc/LithographyTools/GaussianKernel.h"
#include <math.h>
#include <iostream>
#include <iomanip>
GaussianKernel::GaussianKernel()
{

}
double GaussianKernel::GaussianFunc(double x, double sigma,double alpha,double mu)
{
    /* alpha - is curve height
     * mu - is position of center of the curve peak
     * sigma is "bell" width
     *
    */
    //double ALPHA=1/(sigma*sqrt(2*M_PI));
    //const double ALPHA=0.5;//0.45;
    //const double mu=0.0;
    return exp(-(((x-mu)/sigma)*((x-mu)/sigma))/2.0)*alpha;
}

kernel_type GaussianKernel::CalculateGaussian2DKernel(int radius,int kernel_size,double sigma,double alpha)
{
    //const int kernel_size=1199;//*radius+1;//1201;
    //const double sigma=radius/2.5;//bell width
    const int HALF_SIZE=kernel_size/2;

    kernel_type kernel2d(kernel_size,kernel_row(kernel_size));

    double sum=0.0;//accumulation for normalization
    for(unsigned row=0;row<kernel2d.size();row++)
        for(unsigned col=0;col<kernel2d[row].size();col++)
        {
            double gx=GaussianFunc(static_cast<int>(row-HALF_SIZE),sigma,alpha);
            double gy=GaussianFunc(static_cast<int>(col-HALF_SIZE),sigma,alpha);
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
