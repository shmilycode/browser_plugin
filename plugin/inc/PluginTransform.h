///////////////////////////////////////////////////////////
//  File:            PluginTransform.h
//  Brif:            Provide some functions to transform from normal type to NPVariant type.
//  Created on:      2018.5.14 17:06:23
//  Original author: Walle <chenweiqi@cvte.com>
///////////////////////////////////////////////////////////
#ifndef __PLUGIN_TRANSFORM_H__
#define __PLUGIN_TRANSFORM_H__
#include "npfunctions.h"
#include "npruntime.h"
#include "PluginDebug.h"
#include <iostream>
#include <cstring>
	
template<typename T>
	class TypeTrait
	{
	public:
		typedef T value_type;

		static char* member_allocate(size_t size);
		static bool variant_init(NPVariant* dest, value_type* src, size_t size);
		static bool variant_init(NPVariant* dest, value_type src);
	};

template<>
	class TypeTrait<char>
	{
	public:
		static char* memory_allocate(size_t size)
		{
			PLUGIN_FUNCTION();
			char* dest = reinterpret_cast<char*>(NPN_MemAlloc(size));
			return dest;
		}

		static bool variant_init(NPVariant* dest, char* src, size_t size)
		{
			PLUGIN_FUNCTION();
			if (NULL == src)	
				return false;
	
			STRINGN_TO_NPVARIANT(src, size, *dest);
			return true;
		}
	};

template<typename T, typename Trait>
	class VariantTransform
	{
	public:
		static bool Transform(const T* value, NPVariant* result, size_t size);	
	};

template<typename Trait>
	class VariantTransform<char, Trait>
	{
	public:
		static bool Transform(const char* value, NPVariant* result, size_t size)
		{
			PLUGIN_FUNCTION();
			typedef Trait type_trait;	
			char* mem = type_trait::memory_allocate(size+1);
			if (NULL == mem)
			{
				PLUGIN_ERROR_TRACE();
				return false;
			}
			memset(mem, 0, size + 1);
			strncpy(mem, value, size);
			return type_trait::variant_init(result, mem, size);
		}
	};

template<typename T, typename Trait = TypeTrait<char> >
	class VariantTransform;

template<typename T>
	class char_trait;

typedef VariantTransform<char> TransformFromString;

#endif