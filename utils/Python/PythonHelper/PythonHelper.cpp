#include "PythonHelper.h"

PythonHelper::PythonHelper()
{
    Py_Initialize();
}
PythonHelper::~PythonHelper()
{
    Py_Finalize();
}
PyObject* PythonHelper::tryImportModule(const std::string &modulName)
{
    return PyImport_ImportModule(modulName.c_str());
}
PyObject* PythonHelper::trySelectMethod(PyObject *pModule, std::string &methodName)
{
    PyObject* pMethod = NULL;
    if(pModule)
    {
        pMethod = PyObject_GetAttrString(pModule,methodName.c_str());
    }
    return pMethod;
}
PyObject* PythonHelper::tryCallMethod(PyObject *pMethod, PyObject *args)
{
    PyObject* pRes = NULL;
    if(pMethod && PyCallable_Check(pMethod))
    {
        pRes = PyObject_CallObject(pMethod,args);
        destroyPyObject(args);
    }
    return pRes;
}
void PythonHelper::PrintPyObject(PyObject *obj)
{
    PyRun_SimpleString("print('test print')");
}
void PythonHelper::destroyPyObject(PyObject *obj)
{
    if(obj)
    {
        Py_DECREF(obj);
    }
}
