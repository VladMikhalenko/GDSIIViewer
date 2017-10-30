#include "Record34_Generations.h"

Record34_Generations::Record34_Generations() {
    IGDSIISource* source=SourceFactory::GetSource();
    _Count = BinDataTypeReader::_2ByteInteger(source->GetBytes(2),2);
    recordID = GENERATIONS;
}

Record34_Generations::Record34_Generations(const Record34_Generations& orig) {
}

Record34_Generations::~Record34_Generations() {
}

void Record34_Generations::Show() {
    std::cout<<"<Record14_Datatype..."<<std::endl;
    std::cout<<"Count: "<<_Count<<std::endl;
    std::cout<<"...Record14_Datatype>"<<std::endl;
}

short Record34_Generations::GetCount() {
    return _Count;
}
