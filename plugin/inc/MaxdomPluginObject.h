///////////////////////////////////////////////////////////
//  File:            MaxdomPluginObject.h
//  Brif:            Define MaxdomPluginObject, provide customer interface for web browser.
//  Created on:      2018.5.10 17:16:50
//  Original author: Walle <chenweiqi@cvte.com>
///////////////////////////////////////////////////////////

#ifndef __MAXDOM_PLUGIN_OBJECT_H__
#define __MAXDOM_PLUGIN_OBJECT_H__
#include "CVTPluginInterface.h"
#include <iostream>
#include <memory>

#define SERIAL_NUMBER_PROPERTY    "serialnumber"
#define PRODUCT_NAME_PROPERTY    "productname"
#define MAC_ADDRESS_PROPERTY            "mac_address"
#define FIRMWARE_VERSION_PROPERTY    "firmwareversion"
#define VENDOR_PROPERTY    "vendor"
#define RESOLUTION_PROPERTY    "resolution"
#define NETWORK_PROPERTY    "network"
#define TECHPLATFORM_PROPERTY    "techplatform"
#define DEBUG_FREE_PROPERTY    "debug_free"
#define PASERIAL_NUMBER_PROPERTY "paserialnumber"
#define SECURE_SERIAL_NUMBER_PROPERTY "secureSerialNumber"


class MaxdomPluginImpl;
class MaxdomPluginObject: public CVTPluginInterface
{
public:
    MaxdomPluginObject(NPP npp, NPClass *npclass);
    ~MaxdomPluginObject();

    bool IsPropertyExisted(const std::string& property);

    bool IsMethodNameExisted(const std::string& medthod_name);

    PluginResult GetProperty(const std::string& property, NPVariant* result);

    PluginResult SetProperty(const std::string& property, const NPVariant *value);

    PluginResult RemoveProperty(const std::string& property, NPIdentifier name);

    PluginResult InvokeMethod(const std::string& method_name, const NPVariant* args, uint32_t argCount, NPVariant* result);

private:
    std::auto_ptr<MaxdomPluginImpl> pImpl;

};

#endif