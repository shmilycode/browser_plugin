///////////////////////////////////////////////////////////
//  File:            MaxdomPluginObject.cpp
//  Brif:            Define MaxdomPluginObject, provide customer interface for web browser.
//  Created on:      2018.5.10 17:16:50
//  Original author: Walle <chenweiqi@cvte.com>
///////////////////////////////////////////////////////////
#define CUSTOMER_PLUGIN_DEBUG_LEVEL PLUGIN_DEBUG_LEVEL_FUNCTION
#include "MaxdomPluginObject.h"
#include "SystemInfoManager.h"
#include "PluginDebug.h"
#include "PluginTransform.h"
#include <map>
#include <iostream>
#include <cstring>


class MaxdomPluginImpl
{
	friend class MaxdomPluginObject;
	typedef bool (MaxdomPluginImpl::*GetPropertyFunctionPtr)(NPVariant* );
public:
    MaxdomPluginImpl()
    {
		PLUGIN_FUNCTION();
	    GetPropertyFunctionMap[SERIAL_NUMBER_PROPERTY] =  &MaxdomPluginImpl::get_serialnumber;
        GetPropertyFunctionMap[MAC_ADDRESS_PROPERTY] = &MaxdomPluginImpl::get_mac_address;
        GetPropertyFunctionMap[PRODUCT_NAME_PROPERTY] = &MaxdomPluginImpl::get_productname;
        GetPropertyFunctionMap[FIRMWARE_VERSION_PROPERTY] = &MaxdomPluginImpl::get_firmwareversion;
        GetPropertyFunctionMap[VENDOR_PROPERTY] = &MaxdomPluginImpl::get_vendor;
        GetPropertyFunctionMap[RESOLUTION_PROPERTY] = &MaxdomPluginImpl::get_resolution;
        GetPropertyFunctionMap[NETWORK_PROPERTY] = &MaxdomPluginImpl::get_network;
        GetPropertyFunctionMap[TECHPLATFORM_PROPERTY] = &MaxdomPluginImpl::get_techplatform;
        GetPropertyFunctionMap[DEBUG_FREE_PROPERTY] = &MaxdomPluginImpl::get_debug_free;
        GetPropertyFunctionMap[PASERIAL_NUMBER_PROPERTY] = &MaxdomPluginImpl::get_paserial_number;
        GetPropertyFunctionMap[SECURE_SERIAL_NUMBER_PROPERTY] = &MaxdomPluginImpl::get_secure_serial_number;
    }

    std::map<std::string, GetPropertyFunctionPtr> GetPropertyFunctionMap;
public:
    /* The device's unique serial number
     * or any other unique ID string.
     * May instead hold the secure serial number 
     */
    bool get_serialnumber(NPVariant* result)
    {
		PLUGIN_FUNCTION();
        std::string serial_number = SystemInfoManager::GetInstance()->get_serialnumber();
        if(serial_number.empty())
            return false;
	    return TransformFromString::Transform(serial_number.c_str(), result, serial_number.size());
    }

    /* 
     * The device's mac address
     */
    bool get_mac_address(NPVariant* result)
    {
		PLUGIN_FUNCTION();
        std::string mac_address = SystemInfoManager::GetInstance()->get_mac_address();
        if(mac_address.empty())
            return false;

	    return TransformFromString::Transform(mac_address.c_str(), result, mac_address.size());
    }

    /* 
     * The device's model designation
     */
    bool get_productname(NPVariant* result)
    {
		PLUGIN_FUNCTION();
        std::string productname = SystemInfoManager::GetInstance()->get_productname();
        if(productname.empty())
            return false;
        
	    return TransformFromString::Transform(productname.c_str(), result, productname.size());
    }

    /* Version number of installed
     * firmware image.
     */
    bool get_firmwareversion(NPVariant* result)
    {
		PLUGIN_FUNCTION();
        std::string firmwareversion = SystemInfoManager::GetInstance()->get_firmwareversion();
        if(firmwareversion.empty())
            return false;
        
	    return TransformFromString::Transform(firmwareversion.c_str(), result, firmwareversion.size());
    }

    /* 
     * Name of the manufacturer
     */
    bool get_vendor(NPVariant* result)
    {
		PLUGIN_FUNCTION();
        std::string vendor = SystemInfoManager::GetInstance()->get_vendor();
        if(vendor.empty())
            return false;

	    return TransformFromString::Transform(vendor.c_str(), result, vendor.size());
    }

    /* Approximate native resolution
     * available for the web browser.
     * May be different from the
     * device's output resolution
     */
    bool get_resolution(NPVariant* result)
    {
		PLUGIN_FUNCTION();
        std::string resolution = SystemInfoManager::GetInstance()->get_resolution();
        if(resolution.empty())
            return false;

	    return TransformFromString::Transform(resolution.c_str(), result, resolution.size());
    }

    /*
     * Indicating the active networking mode. 
     */
    bool get_network(NPVariant* result)
    {
		PLUGIN_FUNCTION();
        std::string network = SystemInfoManager::GetInstance()->get_network();
        if(network.empty())
            return false;

	    return TransformFromString::Transform(network.c_str(), result, network.size());
    }

    /* Rough classification of the device
     * type. Currently may only be one
     * of STB or TV.
     */
    bool get_techplatform(NPVariant* result)
    {
		PLUGIN_FUNCTION();
        std::string techplatform = SystemInfoManager::GetInstance()->get_techplatform();
        if(techplatform.empty())
            return false;

	    return TransformFromString::Transform(techplatform.c_str(), result, techplatform.size());
    }

    /* Information about the browser's
     * current memory condition.
     */
    bool get_debug_free(NPVariant* result)
    {
		PLUGIN_FUNCTION();
        std::string debug_free = SystemInfoManager::GetInstance()->get_debug_free();
        if(debug_free.empty())
            return false;

	    return TransformFromString::Transform(debug_free.c_str(), result, debug_free.size());
    }

    bool get_uniqueId(NPVariant* result)
    {
		PLUGIN_FUNCTION();
        std::string unique_id = SystemInfoManager::GetInstance()->get_uniqueId();
        if(unique_id.empty())
            return false;

	    return TransformFromString::Transform(unique_id.c_str(), result, unique_id.size());
    }

    bool get_paserial_number(NPVariant* result)
    {
		PLUGIN_FUNCTION();
        std::string paserial_number = SystemInfoManager::GetInstance()->get_paserial_number();
        if(paserial_number.empty())
            return false;

	    return TransformFromString::Transform(paserial_number.c_str(), result, paserial_number.size());
    }

    bool get_chip_id(NPVariant* result)
    {
		PLUGIN_FUNCTION();
        std::string chip_id = SystemInfoManager::GetInstance()->get_chip_id();
        if(chip_id.empty())
            return false;

	    return TransformFromString::Transform(chip_id.c_str(), result, chip_id.size());
    }
	
	bool get_secure_serial_number(NPVariant* result)
	{
		PLUGIN_FUNCTION();
        std::string secure_serial_number = SystemInfoManager::GetInstance()->get_secure_serial_number();
        if(secure_serial_number.empty())
            return false;

	    return TransformFromString::Transform(secure_serial_number.c_str(), result, secure_serial_number.size());
	}
};

MaxdomPluginObject::MaxdomPluginObject(NPP npp, NPClass* npclass)
    :CVTPluginInterface(npp, npclass), pImpl(new MaxdomPluginImpl)
{
    PLUGIN_FUNCTION();
}

MaxdomPluginObject::~MaxdomPluginObject()
{
    PLUGIN_FUNCTION();
}

bool MaxdomPluginObject::IsPropertyExisted(const std::string& property)
{
    PLUGIN_FUNCTION();
    return (pImpl->GetPropertyFunctionMap.find(property) != pImpl->GetPropertyFunctionMap.end()) ? true : false;
}

bool MaxdomPluginObject::IsMethodNameExisted(const std::string& medthod_name)
{
    PLUGIN_FUNCTION();
    return false;
}

PluginResult MaxdomPluginObject::GetProperty(const std::string& property, NPVariant* result)
{
    PLUGIN_FUNCTION();
    if(IsPropertyExisted(property) != true)
        return RESULT_UNSUPPORT;
    
	bool (MaxdomPluginImpl::*GetPropertyFunctionPtr)(NPVariant* ) = pImpl->GetPropertyFunctionMap[property];
    if(((*pImpl).*GetPropertyFunctionPtr)(result) != 0)
        return RESULT_FAILED;
    return RESULT_SUCCESS;
}

PluginResult MaxdomPluginObject::SetProperty(const std::string& property, const NPVariant *value)
{
    PLUGIN_FUNCTION();
    return RESULT_FAILED;
}

PluginResult MaxdomPluginObject::RemoveProperty(const std::string& property, NPIdentifier name)
{
    PLUGIN_FUNCTION();
    return RESULT_FAILED;
}

PluginResult MaxdomPluginObject::InvokeMethod(const std::string& method_name, const NPVariant* args, uint32_t argCount, NPVariant* result)
{
    PLUGIN_FUNCTION();
    return RESULT_FAILED;
}