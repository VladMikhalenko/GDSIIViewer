#include "PythonModule.h"

PythonModule::PythonModule(std::string name):
    _name(name)
{
    pModule = PythonHelper::tryImportModule(name);
}
PythonModule::~PythonModule()
{
    PythonHelper::destroyPyObject(pModule);
}

PyObject* PythonModule::GetModulePointer()
{
    return pModule;
}

std::string PythonModule::GetModuleName()
{
    return _name;
}
