///////////////////////////////////////////////////////////
//  File:            SystemInfoManager.h
//  Brif:            Define some neccessary interface to get system infomation.
//  Created on:      2018.5.11 10:20:30
//  Original author: Walle <chenweiqi@cvte.com>
///////////////////////////////////////////////////////////
#ifndef __SYSTEM_INFO_MANAGER_H__
#define __SYSTEM_INFO_MANAGER_H__
#include <string>

class SystemInfoManager
{
public:
    static SystemInfoManager* GetInstance();
    static SystemInfoManager* instance_;
    /* The device's unique serial number
     * or any other unique ID string.
     * May instead hold the secure serial number 
     */
    std::string get_serialnumber();

    /* 
     * The device's mac address
     */
    std::string get_mac_address();

    /* 
     * The device's model designation
     */
    std::string get_productname();

    /* Version number of installed
     * firmware image.
     */
    std::string get_firmwareversion();

    /* 
     * Name of the manufacturer
     */
    std::string get_vendor();

    /* Approximate native resolution
     * available for the web browser.
     * May be different from the
     * device's output resolution
     */
    std::string get_resolution();

    /*
     * Indicating the active networking mode. 
     */
    std::string get_network();

    /* Rough classification of the device
     * type. Currently may only be one
     * of STB or TV.
     */
    std::string get_techplatform();

    /* Information about the browser's
     * current memory condition.
     */
    std::string get_debug_free();

    std::string get_uniqueId();

    std::string get_paserial_number();

    std::string get_chip_id();
	
	std::string get_secure_serial_number();

private:
    SystemInfoManager();
    ~SystemInfoManager();
};

#endif
