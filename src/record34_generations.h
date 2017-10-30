#ifndef RECORD34_GENERATIONS_H
#define RECORD34_GENERATIONS_H
#include "GDSIIRecord.h"

class Record34_Generations:public GDSIIRecord
{
public:
    Record34_Generations();
    Record34_Generations(const Record34_Generations& orig);
    virtual ~Record34_Generations();

    void Show();
    short GetCount();
private:
    short _Count;
};
#endif // RECORD34_GENERATIONS_H
