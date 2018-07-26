#include "Record23_Presentation.h"

Record23_Presentation::Record23_Presentation() {
    IGDSIISource* source=SourceFactory::GetSource();
    _presentation = BinDataTypeReader::_BitArray(source->GetBytes(2),2);
    recordID = PRESENTATION;
}

Record23_Presentation::Record23_Presentation(const Record23_Presentation& orig) {
    this->_presentation = orig._presentation;
    recordID = PRESENTATION;
}

Record23_Presentation::~Record23_Presentation() {

}

void Record23_Presentation::Show() {
    std::cout << "Record23_Presentation..." << std::endl;
    std::cout << GetFont() << std::endl;
    std::cout << GetVerticalPresentation() << std::endl;
    std::cout << GetHorizontalPresentation() << std::endl;
    std::cout << "...Record23_Presentation" << std::endl;
}

short Record23_Presentation::GetFont() {
    return _presentation[5] * 2 + _presentation[4];
}

short Record23_Presentation::GetVerticalPresentation() {
    return _presentation[3] * 2 + _presentation[2];
}

short Record23_Presentation::GetHorizontalPresentation() {
    return _presentation[1] * 2 + _presentation[0];
}
