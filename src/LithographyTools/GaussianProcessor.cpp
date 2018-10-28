#include "inc/LithographyTools/GaussianProcessor.h"
#include "inc/LithographyTools/LithographicRay.h"
GaussianProcessor::GaussianProcessor(int kSize, double cHeight, double bWidth, unsigned rayStep):
    _gaussKernel(),
    _kernel_size(kSize),
    _curveHeight(cHeight),
    _bellWidth(bWidth),
    _rayStep(rayStep)
{
    _gaussKernel = GaussianKernel::CalculateGaussian2DKernel(_kernel_size,_bellWidth,_curveHeight);
}

void GaussianProcessor::ProcessLineContainer(IntensityField& field, const GDSIILineContainer &container)
{
    int bottomX = container.GetBottomX();
    int bottomY = container.GetBottomY();
    size_t areaWidth = static_cast<size_t>(container.GetAreaWidth());
    size_t areaHeight = static_cast<size_t>(container.GetAreaHeight());
    field = IntensityField(areaHeight,areaWidth);
    for(auto it = container.Begin(); it!=container.End();it++)
    {
        int x1 = it->GetP1().GetX();
        int y1 = it->GetP1().GetY();
        int x2 = it->GetP2().GetX();
        int y2 = it->GetP2().GetY();
        LithographicRay::ShootLine(field,
        GDSIILine(x1-bottomX,areaHeight - (y1-bottomY),
                  x2-bottomX,areaHeight - (y2-bottomY)),_gaussKernel,_rayStep);
    }
}

double GaussianProcessor::getCurveHeight()
{
    return _curveHeight;
}
double GaussianProcessor::getBellWidth()
{
    return _bellWidth;
}
void GaussianProcessor::setCurveHeight(double value)
{
    _curveHeight = value;
}
void GaussianProcessor::setBellWidth(double value)
{
    _bellWidth= value;
}

void GaussianProcessor::setRayStep(unsigned value)
{
    _rayStep = value;
}
unsigned GaussianProcessor::getRayStep()
{
    return _rayStep;
}
