#include "FileWriter.h"
#include <iostream>
FileWriter::FileWriter():
    _file()
{

}

FileWriter::~FileWriter()
{

}

void FileWriter::WriteStringToFile(const std::string &filePath, const std::string &data)
{
    if(_file.is_open())
    {
        _file.close();
    }
    _file.open(filePath,std::ios_base::binary|std::ios_base::out);
    if(_file.is_open())
    {
        _file.write(data.c_str(),data.size());
        _file.close();
    }
    else
    {
        std::cout<<"FileWriter::WriteStringToFile()->Error occurred!"<<std::endl;
    }
}
