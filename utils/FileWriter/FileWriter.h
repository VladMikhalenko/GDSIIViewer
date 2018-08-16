#ifndef FILEWRITER_H
#define FILEWRITER_H
#include <fstream>

constexpr std::string DEFAULT_PATH = "default_file_name.txt";

class FileWriter
{
    std::fstream _file;
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
    void WriteStringToFile(const std::string &filePath = DEFAULT_PATH, const std::string &data);
};

#endif // FILEWRITER_H
