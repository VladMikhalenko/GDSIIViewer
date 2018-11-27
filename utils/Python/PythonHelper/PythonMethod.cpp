#include "PythonMethod.h"

PythonMethod::PythonMethod(PythonModule &owner, std::string name):
    _name("")
  , _owner(NULL)
{
    pMethod = PythonHelper::trySelectMethod(owner.GetModulePointer(),name);
    if(pMethod)
    {
        _name = name;
        _owner = &owner;
    }
}
PythonMethod::~PythonMethod()
{
    PythonHelper::destroyPyObject(pMethod);
}

PythonModule* PythonMethod::GetOwner()
{
    return _owner;
}

std::string PythonMethod::GetName()
{
    return _name;
}

PyObject* PythonMethod::GetMethodPointer()
{
    return pMethod;
}

PyObject* PythonMethod::Execute(PyObject *arg)
{
    return PythonHelper::tryCallMethod(pMethod,arg);
}
