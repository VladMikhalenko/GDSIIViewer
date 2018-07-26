#include "GlobalOptions.h"

GlobalOptions::GlobalOptions(){

}

std::string GlobalOptions::GetFileName(){
    return fileName;
}

SourceType GlobalOptions::GetSourceType(){
    return sourceType;
}

void GlobalOptions::SetSourceType(SourceType type){
    sourceType=type;
}

void GlobalOptions::SetFileName(std::string name){
    fileName=name;
}

SourceType GlobalOptions::sourceType=UNDEFINED;

std::string GlobalOptions::fileName="";
