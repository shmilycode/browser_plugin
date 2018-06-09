///////////////////////////////////////////////////////////
//  File:            SystemInfoManager.cpp
//  Brif:            Define some neccessary interface to get system infomation.
//  Created on:      2018.5.11 10:20:30
//  Original author: Walle <chenweiqi@cvte.com>
///////////////////////////////////////////////////////////
#define CUSTOMER_PLUGIN_DEBUG_LEVEL PLUGIN_DEBUG_LEVEL_FUNCTION
#include "SystemInfoManager.h"
#include "PluginDebug.h"
#include <iostream>
#include <cstdio>
#include <cstring>
#include <sstream>

#define SYSTEM_INFO_FUNCTION() printf("\033[1;32m%s,line=%d,function=%s\033[0m\n",__FILE__,__LINE__,__FUNCTION__)
#define SYSTEM_INFO_DEBUG(fmt, ...) printf(fmt, ##_VA_ARGS__)
#define SYSTEM_INFO_INFO(fmt, ...) printf(fmt, ##_VA_ARGS__)
#define SYSTEM_INFO_ERROR(fmt, ...) printf(fmt, ##_VA_ARGS__)

#define MEMTOTAL_INFO "MemTotal"
#define MEMFREE_INFO "MemFree"
#define BUFFERS_INFO "Buffers"
#define CACHED_INFO "Cached"
#define SWAPCACHED_INFO "SwapCached"
		//MemTotal: 515164 kB  
		//MemFree: 7348 kB  
		//Buffers: 7892 kB  
		//Cached: 241852  kB  
		//SwapCached: 0 kB  
SystemInfoManager* SystemInfoManager::instance_ = new SystemInfoManager;

SystemInfoManager* SystemInfoManager::GetInstance()
{
    return instance_;
}

SystemInfoManager::SystemInfoManager()
{
    SYSTEM_INFO_FUNCTION();
}

SystemInfoManager::~SystemInfoManager()
{
    SYSTEM_INFO_FUNCTION();
}

/* The device's unique serial number
 * or any other unique ID string.
 * May instead hold the secure serial number 
 */
std::string SystemInfoManager::get_serialnumber()
{
    SYSTEM_INFO_FUNCTION();
	return std::string(__FUNCTION__);
}

/* 
 * The device's mac address
 */
std::string SystemInfoManager::get_mac_address()
{
    SYSTEM_INFO_FUNCTION();
	return std::string(__FUNCTION__);
}

/* 
 * The device's model designation
 */
std::string SystemInfoManager::get_productname()
{
    SYSTEM_INFO_FUNCTION();
	return std::string(__FUNCTION__);
}

/* Version number of installed
 * firmware image.
 */
std::string SystemInfoManager::get_firmwareversion()
{
    SYSTEM_INFO_FUNCTION();
	return std::string(__FUNCTION__);
}

/* 
 * Name of the manufacturer
 */
std::string SystemInfoManager::get_vendor()
{
    SYSTEM_INFO_FUNCTION();
	return std::string(__FUNCTION__);
}

/* Approximate native resolution
 * available for the web browser.
 * May be different from the
 * device's output resolution
 */
std::string SystemInfoManager::get_resolution()
{
    SYSTEM_INFO_FUNCTION();
	return std::string(__FUNCTION__);
}

/*
 * Indicating the active networking mode. 
 */
std::string SystemInfoManager::get_network()
{
    SYSTEM_INFO_FUNCTION();
	return std::string(__FUNCTION__);
}

/* Rough classification of the device
 * type. Currently may only be one
 * of STB or TV.
 */
std::string SystemInfoManager::get_techplatform()
{
    SYSTEM_INFO_FUNCTION();
	return std::string(__FUNCTION__);
}

/* Information about the browser's
 * current memory condition.
 */
std::string SystemInfoManager::get_debug_free()
{
    SYSTEM_INFO_FUNCTION();
	std::string free_result;
	
	FILE *fd;  
	char buff[512];
	char MemTotalStr[20];
	unsigned long  MemTotalValue;
	char MemFreeStr[20];
	unsigned long  MemFreeValue;
	char BuffersStr[20];
	unsigned long  BuffersValue;
	char CachedStr[20];
	unsigned long	 CachedValue;
	char SwapCachedStr[20];
	unsigned long  SwapCachedValue;
	fd = fopen("/proc/meminfo", "r");  
	if (fd == NULL)
	{
		return free_result;
	}
	fgets(buff, sizeof(buff), fd);  
	sscanf(buff, "%s %lu ", MemTotalStr, &MemTotalValue);  
	fgets(buff, sizeof(buff), fd);  
	sscanf(buff, "%s %lu ", MemFreeStr, &MemFreeValue);  
	fgets(buff, sizeof(buff), fd);  
	sscanf(buff, "%s %lu ", BuffersStr, &BuffersValue);  
	fgets(buff, sizeof(buff), fd);  
	sscanf(buff, "%s %lu ", CachedStr, &CachedValue);  
	fgets(buff, sizeof(buff), fd);   
	sscanf(buff, "%s %lu", SwapCachedStr, &SwapCachedValue);  
	fclose(fd);	
	
	std::ostringstream result_stream;
	result_stream << MEMTOTAL_INFO << ":" << MemTotalValue << " ";
	result_stream << MEMFREE_INFO << ":" << MemFreeValue << " ";
	result_stream << BUFFERS_INFO << ":" << BuffersValue << " ";
	result_stream << CACHED_INFO << ":" << CachedValue << " ";
	result_stream << SWAPCACHED_INFO << ":" << SwapCachedValue;
	free_result = result_stream.str();

	return free_result;
}

std::string SystemInfoManager::get_secure_serial_number()
{
	SYSTEM_INFO_FUNCTION();
	std::string result;
	return result;
}

std::string SystemInfoManager::get_paserial_number()
{
	SYSTEM_INFO_FUNCTION();
	return std::string(__FUNCTION__);
}
