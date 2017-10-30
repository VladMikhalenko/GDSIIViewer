#ifndef RECORD39_ELKEY_H
#define RECORD39_ELKEY_H

#include "GDSIIRecord.h"
class Record39_Elkey :public  GDSIIRecord
{
  public:
    Record39_Elkey();
    Record39_Elkey(const Record39_Elkey& orig);
    virtual ~Record39_Elkey();
    void Show();
    int GetElkey();
  private:
    int _elkey;
};


#endif // RECORD39_ELKEY_H
