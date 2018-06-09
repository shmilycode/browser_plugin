///////////////////////////////////////////////////////////
//  File:            PluginNPN.h
//  Brif:            Define NPNetscape functions for user. This file only package the function's in NPNNetscapeFuncs.
//  Created on:      2018.5.14 14:04:20
//  Original author: Walle <chenweiqi@cvte.com>
///////////////////////////////////////////////////////////
#define CUSTOMER_PLUGIN_DEBUG_LEVEL PLUGIN_DEBUG_LEVEL_ERROR

#include "npfunctions.h"
#include "npruntime.h"
#include "PluginDebug.h"
#include "assert.h"

extern NPNetscapeFuncs* sBrowserFuncs;

#define CHECK_BROWSER_FUNCS(p) \
	if(p == NULL) \
	{\
		PLUGIN_ERROR("\033[1;31m[%d, %s] NPNetscapeFuncs is NULL!!!\033[0m\n",__LINE__,__FUNCTION__);\
		assert(0);\
	}


void* NPN_MemAlloc(uint32_t size)
{
	PLUGIN_FUNCTION();
	CHECK_BROWSER_FUNCS(sBrowserFuncs);
	void * rv = NULL;
	rv = sBrowserFuncs->memalloc(size);
	return rv;
}

void NPN_MemFree(void* ptr)
{
	PLUGIN_FUNCTION();
	CHECK_BROWSER_FUNCS(sBrowserFuncs);
	sBrowserFuncs->memfree(ptr);
}

NPError NPN_GetValue(NPP instance, NPNVariable variable, void *value)
{
	PLUGIN_FUNCTION();
	CHECK_BROWSER_FUNCS(sBrowserFuncs);
	NPError rv = sBrowserFuncs->getvalue(instance, variable, value);
	return rv;
}

NPError NPN_SetValue(NPP instance, NPPVariable variable, void *value)
{
	PLUGIN_FUNCTION();
	CHECK_BROWSER_FUNCS(sBrowserFuncs);
	NPError rv = sBrowserFuncs->setvalue(instance, variable, value);
	return rv;
}

NPUTF8 *NPN_UTF8FromIdentifier(NPIdentifier identifier)
{
	PLUGIN_FUNCTION();
	CHECK_BROWSER_FUNCS(sBrowserFuncs);
	return sBrowserFuncs->utf8fromidentifier(identifier);
}

NPObject *NPN_CreateObject(NPP npp, NPClass *aClass)
{
	PLUGIN_FUNCTION();
	CHECK_BROWSER_FUNCS(sBrowserFuncs);
	return sBrowserFuncs->createobject(npp, aClass);
}

NPObject *NPN_RetainObject(NPObject *obj)
{
	PLUGIN_FUNCTION();
	CHECK_BROWSER_FUNCS(sBrowserFuncs);
	return sBrowserFuncs->retainobject(obj);
}

void NPN_ReleaseObject(NPObject *obj)
{
	PLUGIN_FUNCTION();
	CHECK_BROWSER_FUNCS(sBrowserFuncs);
	return sBrowserFuncs->releaseobject(obj);
}

bool NPN_Invoke(NPP npp, NPObject* obj, NPIdentifier methodName,
                const NPVariant *args, uint32_t argCount, NPVariant *result)
{
	PLUGIN_FUNCTION();
	CHECK_BROWSER_FUNCS(sBrowserFuncs);
	return sBrowserFuncs->invoke(npp, obj, methodName, args, argCount, result);
}

bool NPN_InvokeDefault(NPP npp, NPObject* obj, const NPVariant *args,
                       uint32_t argCount, NPVariant *result)
{
	PLUGIN_FUNCTION();
	CHECK_BROWSER_FUNCS(sBrowserFuncs);
	return sBrowserFuncs->invokeDefault(npp, obj, args, argCount, result);
}

bool NPN_GetProperty(NPP npp, NPObject* obj, NPIdentifier propertyName,
                     NPVariant *result)
{
	PLUGIN_FUNCTION();
	CHECK_BROWSER_FUNCS(sBrowserFuncs);
	return sBrowserFuncs->getproperty(npp, obj, propertyName, result);
}

bool NPN_SetProperty(NPP npp, NPObject* obj, NPIdentifier propertyName,
                     const NPVariant *value)
{
	PLUGIN_FUNCTION();
	CHECK_BROWSER_FUNCS(sBrowserFuncs);
	return sBrowserFuncs->setproperty(npp, obj, propertyName, value);
}

void NPN_SetException(NPObject* obj, const NPUTF8 *message)
{
	PLUGIN_FUNCTION();
	CHECK_BROWSER_FUNCS(sBrowserFuncs);
	sBrowserFuncs->setexception(obj, message);
}