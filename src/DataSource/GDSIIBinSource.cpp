#include "inc/DataSource/GDSIIBinSource.h"
#include "inc/Global/GlobalOptions.h"
#include <iostream>
#include <vector>


GDSIIBinSource::GDSIIBinSource()
{
    OpenFile();
}
unsigned char *GDSIIBinSource::GetBytes(int byteCount)
{
    if(!FileStream.is_open())
        return nullptr;
    if(FileStream.peek()!=EOF)
    {
        //unsigned char* buffer=new unsigned char[byteCount];
        unsigned char* buffer=new unsigned char[byteCount];
        char* curByte=new char();
        int buff_pos=0;
        while(buff_pos<byteCount && FileStream.peek()!=EOF)
        {
            FileStream.read(curByte,1);//получаем байт из файла
            int charAsInt=static_cast<int>(*curByte);//(int)strtol(s.c_str(),0,16);
            //printf("Convert: %x\n",charAsInt);
            unsigned char ch=(unsigned char)charAsInt;
            buffer[buff_pos++]=ch;//добавляем вычисленный байт массив
        }
        delete curByte;
        if(FileStream.peek()==EOF)
        {
            FileStream.close();
        }
        return buffer;
    }
    std::cout<<"Source has no bytes to read"<<std::endl;
    return nullptr;
}

GDSIIBinSource *GDSIIBinSource::GetInstance()
{
    static GDSIIBinSource _instance;
    return &_instance;
}

void GDSIIBinSource::OpenFile()
{
    if(FileStream.is_open())
        FileStream.close();

    if(GlobalOptions::GetFileName().length()!=0)
    {
        try
        {
            FileStream.open(GlobalOptions::GetFileName(),std::ios_base::binary|std::ios_base::in);
            if(FileStream.is_open())
                std::cout<<"OPENED!!"<<std::endl;
        }
        catch(int code)
        {
            std::cout<<"Error occured with code"<<code<<std::endl;
        }

        //if(FileStream.is_open())
        //    std::cout<<"OPENED!!"<<std::endl;
    }
    else
    {
        //throw AnError();
    }
}
