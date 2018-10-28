#ifndef FILEWRITER_H
#define FILEWRITER_H
#include <fstream>

const std::string DEFAULT_PATH = "default_file_name.txt";

class FileWriter
{
    std::ofstream _file;
    FileWriter();
    ~FileWriter();
    FileWriter(const FileWriter&);
    FileWriter& operator =(const FileWriter&);
public:
    static FileWriter& GetInstance()
    {
        static FileWriter _instance;
        return _instance;
    }
    void WriteStringToFile(const std::string &data,const std::string &filePath = DEFAULT_PATH);
};

#endif // FILEWRITER_H
