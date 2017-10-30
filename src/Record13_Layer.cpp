#include "Record13_Layer.h"

Record13_Layer::Record13_Layer() {
    IGDSIISource* source=SourceFactory::GetSource();
    _layer = BinDataTypeReader::_2ByteInteger(source->GetBytes(2),2);
    recordID = LAYER;
}

Record13_Layer::Record13_Layer(const Record13_Layer& orig) {
    this -> _layer = orig._layer;
    recordID = LAYER;
}

Record13_Layer::~Record13_Layer() {

}

void Record13_Layer::Show() {
    std::cout << "Record13_Layer..." << std::endl;
    std::cout << GetLayer() << std::endl;
    std::cout << "...Record13_Layer" << std::endl;
}

short Record13_Layer::GetLayer() {
    return _layer;
}
