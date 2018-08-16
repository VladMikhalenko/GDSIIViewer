#include "FileWriter.h"

FileWriter::FileWriter()
{

}

FileWriter::~FileWriter()
{

}

void FileWriter::WriteStringToFile(const std::string &filePath, const std::string &data)
{
    std::fstream writer;
    writer.open(filePath,std::ios_base::out);
    if(writer.is_open())
    {
        writer.write(data.c_str(),data.size());
    }
    else
    {
        std::cout<<"FileWriter::WriteStringToFile() -> Failed to open/create file "<<filePath<<std::endl;
    }
    writer.close();
}
