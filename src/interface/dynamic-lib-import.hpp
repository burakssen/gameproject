#pragma once

#include <dlfcn.h>
#include <sys/stat.h>
#include <unistd.h>

#ifdef __APPLE__
#define LIB_EXTENSION ".dylib"
#define DLL_HANDLE void *
#define LOAD_LIBRARY(name) dlopen(name, RTLD_NOW)
#define GET_FUNCTION(handle, name) dlsym(handle, name)
#define FREE_LIBRARY(handle) dlclose(handle)
#elif _WIN32
#define LIB_EXTENSION ".dll"
#define DLL_HANDLE HMODULE
#define LOAD_LIBRARY(name) LoadLibraryA(name)
#define GET_FUNCTION(handle, name) GetProcAddress(handle, name)
#define FREE_LIBRARY(handle) FreeLibrary(handle)
#else
#define LIB_EXTENSION ".so"
#define DLL_HANDLE void *
#define LOAD_LIBRARY(name) dlopen(name, RTLD_NOW)
#define GET_FUNCTION(handle, name) dlsym(handle, name)
#define FREE_LIBRARY(handle) dlclose(handle)
#endif
