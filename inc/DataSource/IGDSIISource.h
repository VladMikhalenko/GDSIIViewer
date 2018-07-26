#ifndef IGDSIISOURCE_H
#define IGDSIISOURCE_H


class IGDSIISource
{
    public:
        virtual unsigned char* GetBytes(int byteCount)=0;
};

#endif // IGDSIISOURCE_H
