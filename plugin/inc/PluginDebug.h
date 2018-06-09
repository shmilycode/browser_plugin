///////////////////////////////////////////////////////////
//  File:            PluginDebug.h
//  Brif:            Debug infomation
//  Created on:      2018.5.14 11:17:50
//  Original author: Walle <chenweiqi@cvte.com>
///////////////////////////////////////////////////////////

#ifndef __PLUGIN_DEBUG_H__
#define __PLUGIN_DEBUG_H__

#ifndef PLUGIN_DEBUG_LEVEL
#define PLUGIN_DEBUG_LEVEL
#define PLUGIN_DEBUG_LEVEL_FUNCTION 5
#define PLUGIN_DEBUG_LEVEL_INFO 4
#define PLUGIN_DEBUG_LEVEL_DEBUG 3
#define PLUGIN_DEBUG_LEVEL_ERROR 2
#define PLUGIN_DEBUG_LEVEL_TRACE 1
#endif

#ifndef CUSTOMER_PLUGIN_DEBUG_LEVEL
#define CUSTOMER_PLUGIN_DEBUG_LEVEL PLUGIN_DEBUG_LEVEL_TRACE
#endif

//debug
#if (CUSTOMER_PLUGIN_DEBUG_LEVEL >= PLUGIN_DEBUG_LEVEL_FUNCTION)
#define PLUGIN_FUNCTION() printf("\033[1;32m%s,line=%d,function=%s\033[0m\n",__FILE__,__LINE__,__FUNCTION__)
#else 
#define PLUGIN_FUNCTION()
#endif

#if (CUSTOMER_PLUGIN_DEBUG_LEVEL >= PLUGIN_DEBUG_LEVEL_DEBUG)
#define PLUGIN_DEBUG(fmt, arg...) printf(fmt, ##arg)
#else#define PLUGIN_DEBUG(fmt, arg...)
#endif

#if (CUSTOMER_PLUGIN_DEBUG_LEVEL >= PLUGIN_DEBUG_LEVEL_INFO)
#define PLUGIN_INFO(fmt, arg...) printf(fmt, ##arg)
#else#define PLUGIN_INFO(fmt, arg...)
#endif

#if (CUSTOMER_PLUGIN_DEBUG_LEVEL >= PLUGIN_DEBUG_LEVEL_ERROR)
#define PLUGIN_ERROR(fmt, arg...) printf(fmt, ##arg)
#else#define PLUGIN_ERROR(fmt, arg...)
#endif

#if (CUSTOMER_PLUGIN_DEBUG_LEVEL >= PLUGIN_DEBUG_LEVEL_TRACE)
#define PLUGIN_ERROR_TRACE() printf("\033[1;31m[%d, %s] Trace Error!\033[0m\n",__LINE__,__FUNCTION__)
#else#define PLUGIN_ERROR_TRACE()
#endif

#endif