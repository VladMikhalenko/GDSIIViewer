#include "GDSIISourceTXT.h"
#include "GlobalOptions.h"
#include <iostream>

GDSIISourceTXT::GDSIISourceTXT()
{
    OpenFile();
}
unsigned char* GDSIISourceTXT::GetBytes(int byteCount)
{
    if(FileStream.peek()!=EOF)
    {
        unsigned char* buffer=new unsigned char[byteCount];
        char* curByte=new char();
        int value=0,buff_pos=0;
        bool metLeft=false;
        while(buff_pos<byteCount && FileStream.peek()!=EOF)
        {
            FileStream.read(curByte,1);//получаем байт из файла
            //printf("Read: %c\n",*curByte);
            if(isxdigit(*curByte))//если это '0' '1' '2' '3' '4' ... 'D' 'E' 'F'
            {
                std::string s(1,*curByte);
                int charAsInt=(int)strtol(s.c_str(),0,16);//конвертируем символ в целое
                if(!metLeft)//если текущий байт является "левой" частью hex значения
                {
                    value=charAsInt<<4;// то в value помещаем этот байт со сдвигом на 4 позиции влево
                    metLeft=true;//это флаг левой и правой частей hex
                }
                else
                {
                    value+=charAsInt; // если правая часть hex
                    metLeft=false;
                    buffer[buff_pos++]=(unsigned char)value;//добавляем вычисленный байт массив
                }
            }
        }
        delete curByte;
        return buffer;
    }
    //AnError();
    std::cout<<"Source has no bytes to read"<<std::endl;
    return 0;
}

GDSIISourceTXT* GDSIISourceTXT::GetInstance()
{
    if(!instance)
        instance=new GDSIISourceTXT();
    return instance;
}

void GDSIISourceTXT::OpenFile()
{
    if(FileStream.is_open())
        FileStream.close();

    if(GlobalOptions::GetFileName().length()!=0)
    {
        FileStream.open(GlobalOptions::GetFileName());
        //if(FileStream.is_open())
        //    std::cout<<"OPENED!!"<<std::endl;
    }
    else
    {
        //throw AnError();
    }
}

GDSIISourceTXT* GDSIISourceTXT::instance=0;
