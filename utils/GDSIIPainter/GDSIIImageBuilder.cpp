#include "GDSIIImageBuilder.h"
#include <QPainter>
GDSIIImageBuilder::GDSIIImageBuilder()
{

}

void GDSIIImageBuilder::DrawLineContainerOnImage(QImage &image, const GDSIILineContainer &container)
{
    QPainter* paint=new QPainter();
    paint->setPen(QPen(Qt::white,10.0));
    paint->setBrush(QBrush(Qt::white));
    paint->setRenderHint(QPainter::Antialiasing,true);

    int bottomX = container.GetBottomX();
    int bottomY = container.GetBottomY();
    size_t areaWidth = static_cast<size_t>(container.GetAreaWidth());
    size_t areaHeight = static_cast<size_t>(container.GetAreaHeight());
    image = QImage(areaWidth,areaHeight,QImage::Format_ARGB32_Premultiplied);
    //image.fill(Qt::white);
    for(auto it = container.Begin(); it!=container.End();it++)
    {
        auto lineToDraw = QLine(QPoint(it->GetP1().GetX()-bottomX,areaHeight - (it->GetP1().GetY()-bottomY)),
                                QPoint(it->GetP2().GetX()-bottomX,areaHeight - (it->GetP2().GetY()-bottomY)));
        paint->begin(&image);
        paint->drawLine(lineToDraw);
        paint->end();
    }
//    QString fullName = QString::fromStdString(std::string("[ContainerJPGImage]"+imgName+".jpg"));
//    image.save(fullName,"JPG");
}

void GDSIIImageBuilder::SaveIntensityFieldAsJpg(const IntensityField &field, const std::string &name)
{
    QImage image = GDSIIConverter::GetInstance().Convert(field);
    image.save(QString::fromStdString(std::string("[Field]"+name+".jpg")),"JPG");
}
