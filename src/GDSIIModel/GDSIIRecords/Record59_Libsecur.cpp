#include "Record59_Libsecur.h"

Record59_Libsecur::Record59_Libsecur(int count)
{
    //count /= 6;
    IGDSIISource* source = SourceFactory::GetSource();
    _ACL = new ACL[count];
    _ACLAmount = count;
    ACL acl;
    for(int i = 0; i < count; i++)
    {
        acl._groupNumber = BinDataTypeReader::_2ByteInteger(source->GetBytes(2),2);
        acl._userNumber = BinDataTypeReader::_2ByteInteger(source->GetBytes(2),2);
        acl._accessRights = BinDataTypeReader::_2ByteInteger(source->GetBytes(2),2);
        _ACL[i] = acl;
    }
    recordID = LIBSECUR;
}

Record59_Libsecur::Record59_Libsecur(const Record59_Libsecur& orig) {
    this->_ACLAmount = orig._ACLAmount;
    this->_ACL = new ACL[orig._ACLAmount];
    for (int i = 0; i < orig._ACLAmount; i++) {
        this->_ACL[i] = orig._ACL[i];
    }
    recordID = LIBSECUR;
}

Record59_Libsecur::~Record59_Libsecur() {

}
void Record59_Libsecur::Show() {
    std::cout << "<Record59_Libsecur..." << std::endl;
    for(int i = 0; i < GetACLAmount(); i++) {
        std::cout << "{" << _ACL[i]._groupNumber << ", " << _ACL[i]._userNumber << ", " << _ACL[i]._accessRights << "}" << std::endl;
    }
    std::cout << "...Record59_Libsecur>" << std::endl;
}

ACL* Record59_Libsecur::GetACL()
{
    return _ACL;
}

int Record59_Libsecur::GetACLAmount()
{
    return _ACLAmount;
}
