lib_name = npapi_plugin.so
lib_target = $(lib_name)
CFLAGS = -Wall -DXP_UNIX=1 -DMOZ_X11=1 -fPIC -g -I ./inc -I ../npapi/inc

plugin_headers = ../npapi/inc/npapi.h ../npapi/inc/npfunctions.h ../npapi/inc/npruntime.h ../npapi/inc/nptypes.h ./inc/CVTPluinInterface.h ./inc/MaxdomPluginObject.h ./inc/PluginMain.h ./inc/SystemInfoManager.h
plugin_sources = ./src/MaxdomPluginObject.cpp ./src/PluginMain.cpp ./SystemInfoManager.cpp
plugin_objs = MaxdomPluginObject.o  PluginMain.o  SystemInfoManager.o

MaxdomPluginObject.o : ./src/MaxdomPluginObject.cpp $(plugin_headers)
	$(CXX) $(CFLAGS) -c ./src/MaxdomPluginObject.cpp

PluginMain.o : ./src/PluginMain.cpp $(plugin_headers)
	$(CXX) $(CFLAGS) -c ./src/PluginMain.cpp

SystemInfoManager.o : ./src/SystemInfoManager.cpp $(plugin_headers)
	$(CXX) $(CFLAGS) -c ./src/SystemInfoManager.cpp

$(lib_target):$(plugin_objs)
	$(CC) $(ld_flags) -Wl,-soname,$(lib_name) -o $@ $^

