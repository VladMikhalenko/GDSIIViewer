#ifndef BINDATATYPEREADER_H
#define BINDATATYPEREADER_H

#include <bitset>
//using namespace std;

//typedef BitArray std::bitset<16>;

class BinDataTypeReader
{
  public:
    //BinDataTypeReader();
    static std::bitset<16>  _BitArray(unsigned char* buff, int buff_size);
    static short            _2ByteInteger(unsigned char* buff,int buff_size);
    static int              _4ByteInteger(unsigned char* buff,int buff_size);
    static double           _8ByteReal(unsigned char* buff,int buff_size);
    static std::string      _ASCIIString(unsigned char* buff, int buff_size);
};
#endif /* BINDATATYPEREADER_H */


