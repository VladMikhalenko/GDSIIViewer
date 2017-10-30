
#ifndef BINGDSIIFILEREADER_H
#define BINGDSIIFILEREADER_H

#include "BinDataTypeReader.h"
#include "IGDSIISource.h"
#include "GDSIIRecord.h"
using namespace std;


class RecordSupplier {
public:
    GDSIIRecord* NextRecord();
    static RecordSupplier* GetInstance();

private:
    static RecordSupplier *instance;
    virtual ~RecordSupplier();
    RecordSupplier();
    RecordSupplier(const RecordSupplier& orig);
    RecordSupplier& operator=(RecordSupplier const&);
    IGDSIISource* source;
};

#endif /* BINGDSIIFILEREADER_H */
