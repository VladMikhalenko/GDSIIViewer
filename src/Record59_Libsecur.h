#pragma once
#ifndef RECORD59_LIBSECUR_H
#define RECORD59_LIBSECUR_H

#include "ACL.h"
#include "GDSIIRecord.h"

class Record59_Libsecur :public  GDSIIRecord
{
  public:
    Record59_Libsecur(int count);
    Record59_Libsecur(const Record59_Libsecur& orig);
    virtual ~Record59_Libsecur();
    void Show();
    ACL* GetACL();
    int GetACLAmount();
  private:
    ACL* _ACL;
    int _ACLAmount;
};

#endif // RECORD59_LIBSECUR_H
