#include "GDSIISourceConsole.h"
#include <stdio.h>
#include <conio.h>
#include <iostream>

GDSIISourceConsole::GDSIISourceConsole(){ }


unsigned char* GDSIISourceConsole::GetBytes(int byteCount)
{
    unsigned char ch;
    unsigned char* buffer=new unsigned char[byteCount];

    int chAsInt,value=0,countChars=0,buff_pos=0,lineControl=0;
    cout<<"Enter hex data("<<byteCount<<" bytes):"<<endl;
    while(buff_pos<byteCount)
    {
        ch=getch();
        switch(ch){
            case '0':chAsInt=0;
                break;
            case '1':chAsInt=1;
                break;
            case '2':chAsInt=2;
                break;
            case '3':chAsInt=3;
                break;
            case '4':chAsInt=4;
                break;
            case '5':chAsInt=5;
                break;
            case '6':chAsInt=6;
                break;
            case '7':chAsInt=7;
                break;
            case '8':chAsInt=8;
                break;
            case '9':chAsInt=9;
                break;
            case 'A':chAsInt=10;
                break;
            case 'B':chAsInt=11;
                break;
            case 'C':chAsInt=12;
                break;
            case 'D':chAsInt=13;
                break;
            case 'E':chAsInt=14;
                break;
            case 'F':chAsInt=15;
                break;
            case 'a':chAsInt=10;
                break;
            case 'b':chAsInt=11;
                break;
            case 'c':chAsInt=12;
                break;
            case 'd':chAsInt=13;
                break;
            case 'e':chAsInt=14;
                break;
            case 'f':chAsInt=15;
                break;
            default:chAsInt=-1;
                break;
        }
        if(chAsInt!=-1){
            cout<<ch;
            if(countChars<1){
                value=chAsInt<<4;
                countChars++;
                lineControl++;
            }
            else{
                value+=chAsInt;
                countChars=0;
                lineControl++;
                buffer[buff_pos++]=(unsigned char)value;
            }
            if(lineControl%4==0){
                cout<<" ";
            }
            if(lineControl==16){
                lineControl=0;
                cout<<endl;
            }
        }
    }
    cout<<"\nEnd..."<<endl;
    return buffer;
}


GDSIISourceConsole* GDSIISourceConsole::GetInstance(){
    if(!instance){
        instance=new GDSIISourceConsole();
    }
    return instance;
}

GDSIISourceConsole* GDSIISourceConsole::instance=0;
