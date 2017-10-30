#include "GDSIIBinSource.h"
#include "GlobalOptions.h"
#include <iostream>

GDSIIBinSource::GDSIIBinSource()
{
    OpenFile();
}
unsigned char* GDSIIBinSource::GetBytes(int byteCount)
{
    if(FileStream.peek()!=EOF)
    {
        unsigned char* buffer=new unsigned char[byteCount];
        char* curByte=new char();
        int buff_pos=0;
        while(buff_pos<byteCount && FileStream.peek()!=EOF)
        {
            FileStream.read(curByte,1);//получаем байт из файла
            int charAsInt=static_cast<int>(*curByte);//(int)strtol(s.c_str(),0,16);
            //printf("Convert: %x\n",charAsInt);
            buffer[buff_pos++]=(unsigned char)charAsInt;//добавляем вычисленный байт массив
        }
        delete curByte;
        if(FileStream.peek()==EOF)
        {
            FileStream.close();
        }
        return buffer;
    }
    std::cout<<"Source has no bytes to read"<<std::endl;
    return 0;
}

GDSIIBinSource* GDSIIBinSource::GetInstance()
{
    if(!instance)
        instance=new GDSIIBinSource();
    return instance;
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

GDSIIBinSource* GDSIIBinSource::instance=0;
