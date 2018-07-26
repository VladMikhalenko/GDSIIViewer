
#ifndef BINGDSIIFILEREADER_H
#define BINGDSIIFILEREADER_H

#include "BinDataTypeReader.h"
#include "inc/DataSource/IGDSIISource.h"
#include "inc/GDSIIModel/GDSIIRecords/GDSIIRecord.h"

#include <memory>

class RecordSupplier {
public:
    std::shared_ptr<GDSIIRecord> NextRecord();
    static RecordSupplier& GetInstance();

private:
    RecordSupplier();
    RecordSupplier(const RecordSupplier& orig);
    RecordSupplier& operator=(RecordSupplier const&);
    IGDSIISource* source;
};

#endif /* BINGDSIIFILEREADER_H */
