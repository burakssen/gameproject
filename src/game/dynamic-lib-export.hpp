#pragma once

#if defined(_WIN32) || defined(_WIN64)
#ifdef DYNAMICLIB_EXPORT
#define EXPORT_FUNC __declspec(dllexport)
#else
#define EXPORT_FUNC __declspec(dllimport)
#endif
#else
#ifdef DYNAMICLIB_EXPORT
#define EXPORT_FUNC __attribute__((visibility("default")))
#else
#define EXPORT_FUNC
#endif
#endif