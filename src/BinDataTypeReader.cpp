/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BinDataTypeReader.cpp
 * Author: Val
 * 
 * Created on 2 января 2017 г., 17:11
 */

#include "BinDataTypeReader.h"
#include "AnError.h"
#include <math.h>
#include <iostream>

std::bitset<16> BinDataTypeReader::_BitArray(unsigned char *buff, int buff_size)
{
    if (buff_size<3 && buff_size>0) {
        unsigned short bArr, temp;
        bArr = (unsigned short)buff[0];
        bArr = bArr << 8;
        temp = (unsigned short)buff[1];
        bArr = bArr | temp;
        std::bitset<16> _Bits(bArr);
        return _Bits;
    }
    throw AnError();
}
short BinDataTypeReader::_2ByteInteger(unsigned char* buff,int buff_size)
{
    if(buff_size<3 && buff_size>0 && buff!=0){
        short result=0;
        short shiftKey=buff_size-1;
        for(int i=0;i<buff_size;i++){
            result+=(short)buff[i];
            result<<=shiftKey--*8;
        }
        return result;
    }
    //throw AnError();
}
double BinDataTypeReader::_8ByteReal(unsigned char* buff,int buff_size){

    if(buff_size>1 && buff_size<9 && _msize(buff)>0){

        //определяем знак, и експоненту
        int sign=((buff[0]&128)==0 ? 1: -1);
        int exponent=buff[0]&127;
        int actualExp=exponent>0 ? exponent-64:0;


        double mantissa=0.0;
        unsigned char curByte=0;
        double expOfBit=0.5;

        //проходим по каждому байту мантисы
        for(int i=1;i<buff_size;i++){
            curByte=buff[i];
            int bitMask=128;

            //проходим по каждому биту текущего байта, если он = 1, то в мантису накапливаем значение этого бита
            //проходим слева на право
            for(int j=0;j<8;j++){
                mantissa+=((curByte&bitMask)>0?  expOfBit:0);
                bitMask>>=1;
                expOfBit*=0.5;
            }
        }
        //
        return sign*pow(16,actualExp)*mantissa;
    }
    else{
        //throw AnError();
    }


}
int BinDataTypeReader::_4ByteInteger(unsigned char* buff,int buff_size)
{
    if(buff_size<5 && buff_size>0){
        int result=0;
        int tmp=0;
        short shiftKey=buff_size-1;
        for(int i=0;i<buff_size;i++){
            tmp=(int)buff[i];
            tmp<<=(shiftKey--)*8;
            result+=tmp;
        }
        return result;
    }
    throw AnError();
}
std::string BinDataTypeReader::_ASCIIString(unsigned char *buff, int buff_size){
    std::string result = "";
    for(int i = 0; i < buff_size; i++) {
        result += buff[i];
    }
    return result;
}

