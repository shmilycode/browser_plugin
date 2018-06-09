///////////////////////////////////////////////////////////
//  File:            CVTPluginInterface.h
//  Brif:            Define some neccessary interface for NPAPI.
//  Created on:      2018.5.10 22:47:30
//  Original author: Walle <chenweiqi@cvte.com>
///////////////////////////////////////////////////////////
#ifndef __CVT_PLUGIN_INTERFACE_H__
#define __CVT_PLUGIN_INTERFACE_H__
#include <string>
#include "npapi.h"
#include "npruntime.h"

enum PluginResult
{
    RESULT_SUCCESS,
    RESULT_FAILED,
    RESULT_UNSUPPORT
};

class CVTPluginInterface: public NPObject
{
public:
    CVTPluginInterface(NPP npp, NPClass* npclass)
		: NPObject(), npp_(npp){_class = npclass;referenceCount=1;}
    virtual ~CVTPluginInterface(){};

    virtual bool IsPropertyExisted(const std::string& property) = 0;

    virtual bool IsMethodNameExisted(const std::string& medthod_name) = 0;

    virtual PluginResult GetProperty(const std::string& property, NPVariant* result) = 0;

    virtual PluginResult SetProperty(const std::string& property, const NPVariant *value) = 0;

    virtual PluginResult RemoveProperty(const std::string& property, NPIdentifier name) = 0;

    virtual PluginResult InvokeMethod(const std::string& method_name, const NPVariant* args, uint32_t argCount, NPVariant* result) = 0;

protected:
    NPP npp_;
    NPClass* npclass_;
};

#endif