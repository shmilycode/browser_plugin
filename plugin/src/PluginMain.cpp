///////////////////////////////////////////////////////////
//  File:            PluginMain.c
//  Brif:            Define some necessary define for NPAPI. 
//  Created on:      2018.5.10 17:16:50
//  Original author: Walle <chenweiqi@cvte.com>
///////////////////////////////////////////////////////////
#define CUSTOMER_PLUGIN_DEBUG_LEVEL PLUGIN_DEBUG_LEVEL_FUNCTION

#include "PluginMain.h"
#include "CVTPluginInterface.h"
#include "MaxdomPluginObject.h"
#include "npfunctions.h"
#include "npruntime.h"
#include "PluginDebug.h"
#include <iostream>
#include <cstdio>
#include <cstring>

static char PLUGIN_NAME[] = "maxdom systeminfoobject";
static char PLUGIN_DESCRIPTION[] = "Device Indentification";
static char MIME_TYPES[] = "systeminfoobject:*:sysinfo;";
static char PLUGIN_VERSION[] = "1.0.0.0";

NPNetscapeFuncs* sBrowserFuncs = NULL;

//Functions for scriptablePluginClass
static NPObject* plugin_Allocate(NPP npp, NPClass *aClass);
static void plugin_Deallocate(NPObject *npobj);
static bool plugin_hasMethod(NPObject *obj, NPIdentifier methodName);
static bool plugin_Invoke(NPObject *obj, NPIdentifier methodName, const NPVariant *args, uint32_t argCount, NPVariant *result);
static bool plugin_hasProperty(NPObject *obj, NPIdentifier propertyName);
static bool plugin_getProperty(NPObject *obj, NPIdentifier propertyName, NPVariant *result);

static struct NPClass scriptablePluginClass = {
    NP_CLASS_STRUCT_VERSION,
    plugin_Allocate,
    plugin_Deallocate,
    NULL,
    plugin_hasMethod,
    plugin_Invoke,
    NULL,
    plugin_hasProperty,
    plugin_getProperty,
    NULL,
    NULL,
};

//NPP Functions Implements
NP_EXPORT(NPError) NP_Initialize(NPNetscapeFuncs* bFuncs, NPPluginFuncs* pFuncs)
{
    PLUGIN_FUNCTION();
    sBrowserFuncs = bFuncs;

    pFuncs->newp = NPP_New;
    pFuncs->destroy = NPP_Destroy;
    pFuncs->setwindow = NPP_SetWindow;
    pFuncs->newstream = NPP_NewStream;
    pFuncs->destroystream = NPP_DestroyStream;
    pFuncs->asfile = NPP_StreamAsFile;
    pFuncs->writeready = NPP_WriteReady;
    pFuncs->write = NPP_Write;
    pFuncs->print = NPP_Print;
    pFuncs->event = NPP_HandleEvent;
    pFuncs->urlnotify = NPP_URLNotify;
    pFuncs->getvalue = NPP_GetValue;
    pFuncs->setvalue = NPP_SetValue;

    return NPERR_NO_ERROR;
}

NP_EXPORT(char*) NP_GetPluginVersion()
{
    PLUGIN_FUNCTION();
	return PLUGIN_VERSION;
}

NP_EXPORT(const char*) NP_GetMIMEDescription()
{
    PLUGIN_FUNCTION();
	return MIME_TYPES;
}

NP_EXPORT(NPError) NP_GetValue(void* future, NPPVariable aVariable, void* aValue) {
    PLUGIN_FUNCTION();
	switch (aVariable) {
	case NPPVpluginNameString:
		*((char**)aValue) = PLUGIN_NAME;
		break;
	case NPPVpluginDescriptionString:
		*((char**)aValue) = PLUGIN_DESCRIPTION;
		break;
	default:
		return NPERR_INVALID_PARAM;
		break;
	}
	return NPERR_NO_ERROR;
}

NP_EXPORT(NPError) NP_Shutdown()
{
	return NPERR_NO_ERROR;
}

NPError NPP_New(NPMIMEType pluginType, NPP instance, uint16_t mode,
                int16_t argc, char* argn[], char* argv[], NPSavedData* saved)
{
    PLUGIN_FUNCTION();

    // mark the plugin windowless explicitly
    // (NP API docu: this should be done before the next 'mark transparent' call)
    if (NPN_SetValue(instance, NPPVpluginWindowBool, (void*) false) != NPERR_NO_ERROR)
    { 
        PLUGIN_ERROR_TRACE();
    } // Opera always returns a generic NPError on this call (not known why);
                   // nevertheless Opera considers this as a windowless plugin, cf. NPP_SetWindow

    // mark the plugin transparent explicitly
    // (this is necessary to make the plugin area invisible!)
    if (NPN_SetValue(instance, NPPVpluginTransparentBool, (void*) true) != NPERR_NO_ERROR)
    {
        PLUGIN_ERROR_TRACE();
    }

    if(!instance->pdata)
    {
      instance->pdata = NPN_CreateObject(instance, &scriptablePluginClass);
    }

    return NPERR_NO_ERROR;
}

NPError NPP_Destroy(NPP instance, NPSavedData** save)
{
    PLUGIN_FUNCTION();
    // If we created a plugin instance, we'll destroy and clean it up.
    NPObject *pluginInstance = (NPObject*)instance->pdata;
    if(pluginInstance) {
        NPN_ReleaseObject(pluginInstance);
        instance->pdata = NULL;
    }
    return NPERR_NO_ERROR;
}

NPError NPP_SetWindow(NPP instance, NPWindow* window)
{
    PLUGIN_FUNCTION();
    if (window == NULL)
    {
        PLUGIN_ERROR_TRACE();
    }
    else if (window->type != NPWindowTypeDrawable)
    {
        PLUGIN_ERROR_TRACE();
    }

    // need not call NPN_InvalidateRect or NPN_ForceRedraw here because
    // Opera will anyway send one paint event for the plugin area after this call

    return NPERR_NO_ERROR;
}

NPError NPP_NewStream(NPP instance, NPMIMEType type, NPStream* stream,
                      NPBool seekable, uint16_t* stype)
{
    PLUGIN_FUNCTION();
    *stype = NP_NORMAL;
    return NPERR_NO_ERROR;
}

NPError NPP_DestroyStream(NPP instance, NPStream* stream, NPError reason)
{
    PLUGIN_FUNCTION();
    return NPERR_NO_ERROR;
}

void NPP_StreamAsFile(NPP instance, NPStream* stream, const char* fname)
{
    PLUGIN_FUNCTION();
}

int32_t NPP_WriteReady(NPP instance, NPStream* stream)
{
    PLUGIN_FUNCTION();
    return 8192;
}

int32_t NPP_Write(NPP instance, NPStream* stream, int32_t offset, int32_t len, void* buffer)
{
    PLUGIN_FUNCTION();
    return -1;
}

void NPP_Print(NPP instance, NPPrint* platformPrint)
{
    PLUGIN_FUNCTION();
}

int16_t NPP_HandleEvent(NPP instance, void* evt)
{
    PLUGIN_FUNCTION();
    return 0;
}

void NPP_URLNotify(NPP instance, const char* url, NPReason reason, void* notifyData)
{
    PLUGIN_FUNCTION();
}

#if NP_VERSION_MAJOR==0 && NP_VERSION_MINOR<=11
#define NPP void*
#endif

NPError NPP_GetValue(NPP instance, NPPVariable variable, void *value)
{
    PLUGIN_FUNCTION();
    NPObject* object_value(NULL);
	NPError ret(NPERR_NO_ERROR);
	if (instance)
	{
		object_value = static_cast<NPObject*>(instance->pdata);
	}
  
	PLUGIN_DEBUG("variable = %d\n", (int)variable);
    switch (variable)
    {
	    case NPPVpluginNameString:
	    {
	        *((char**)value)= PLUGIN_NAME;
	    } break;
	    case NPPVpluginDescriptionString:
	    {
			*((char**)value) = PLUGIN_DESCRIPTION;
	    } break;
	    case NPPVpluginScriptableNPObject:
	    {
		    if (NULL != object_value)
		    {
			    PLUGIN_DEBUG("object_value: %p\n", object_value);
			    NPN_RetainObject(object_value);
			    PLUGIN_DEBUG("object_value: %p\n", object_value);
			    *((NPObject **)value) = object_value;
		    }
		    else
		    {
			    ret = NPERR_GENERIC_ERROR;
		    }
	    } break;
		case NPPVpluginNeedsXEmbed:
	    {
		    *((NPBool *)value) = 1;
	    } break;
		case NPPVpluginScriptableIID:
		case NPPVpluginScriptableInstance:
	    {
		    /// XPCOM scripting, obsolete
		    ret = NPERR_GENERIC_ERROR;
	    } break;
    break;
	    default:
	    {
	        PLUGIN_ERROR_TRACE();
		    ret = NPERR_INVALID_PARAM;
	    }
    };
	PLUGIN_DEBUG("ret = %d\n", (int)ret);
	return ret;
}

NPError NPP_SetValue(NPP instance, NPNVariable variable, void *value)
{
    PLUGIN_FUNCTION();
    return NPERR_NO_ERROR;
}

#if NP_VERSION_MAJOR==0 && NP_VERSION_MINOR<=11
#undef NPP
#endif

typedef struct InstanceData
{
  NPObject object;
  NPP instance;
} InstanceData;

static NPObject* plugin_Allocate(NPP npp, NPClass *aClass)
{
    PLUGIN_FUNCTION();
  	return new MaxdomPluginObject(npp,aClass);
}

static void plugin_Deallocate(NPObject *npobj)
{
    PLUGIN_FUNCTION();
	delete static_cast<CVTPluginInterface*>(npobj);
}

static bool plugin_hasMethod(NPObject *obj, NPIdentifier methodName)
{
    PLUGIN_FUNCTION();
    // This function will be called when we invoke method on this plugin elements.
  	bool result;
    NPUTF8 *name = NPN_UTF8FromIdentifier(methodName);
    CVTPluginInterface* plugin_obj = static_cast<CVTPluginInterface*>(obj);
	result = plugin_obj->IsMethodNameExisted(name);
    NPN_MemFree(name);
    return result;
}

static bool plugin_Invoke(NPObject *obj, NPIdentifier methodName, const NPVariant *args, uint32_t argCount, NPVariant *result)
{
    PLUGIN_FUNCTION();
    bool ret = false;
    NPUTF8 *name = NPN_UTF8FromIdentifier(methodName);
    CVTPluginInterface* plugin_obj = static_cast<CVTPluginInterface*>(obj);
  	if(plugin_obj->InvokeMethod(name,args,argCount,result) == RESULT_SUCCESS)
    {
        ret = true;
    }
    else
    {
	    PLUGIN_ERROR("[%s %d] Invoke Method Failed!\n", __FUNCTION__, __LINE__);
    }
    NPN_MemFree(name);
    return ret;
}

static bool plugin_hasProperty(NPObject *obj, NPIdentifier propertyName)
{
    PLUGIN_FUNCTION();
    bool ret = false;

    NPUTF8 *name = NPN_UTF8FromIdentifier(propertyName);
    CVTPluginInterface* plugin_obj = static_cast<CVTPluginInterface*>(obj);
  	ret = plugin_obj->IsPropertyExisted(name);

  	if(!ret)
  	{
  		if(strcmp(name,"Name") == 0)
  		{
  			ret = true;
  		}else if(strcmp(name,"ID")==0){
  			ret = true;
  		}
  	}
    NPN_MemFree(name);
    return ret;
}

static bool plugin_getProperty(NPObject *obj, NPIdentifier propertyName, NPVariant *result)
{
    PLUGIN_FUNCTION();
    bool ret = false;
    NPUTF8 *name = NPN_UTF8FromIdentifier(propertyName);
    CVTPluginInterface* plugin_obj = static_cast<CVTPluginInterface*>(obj);
  	ret = plugin_obj->GetProperty(name, result);
	if (true == ret)	
	{
		char* result_str = new char[result->value.stringValue.UTF8Length + 1];
		memcpy(result_str, result->value.stringValue.UTF8Characters, result->value.stringValue.UTF8Length);
		result_str[result->value.stringValue.UTF8Length] = 0;
		PLUGIN_INFO("result is %s %d\n", result_str, result->value.stringValue.UTF8Length);
		delete[] result_str;
	}
  	NPN_MemFree(name);
	return ret;
}
