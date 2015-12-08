#pragma once

#define SMOG_VERSION 1.0.0
#define SMOG_VERSION_US 1_0_0

#if defined _WIN32
	#define EXPORT __declspec(dllexport)
	#define IMPORT __declspec(dllimport)
#elif defined __GNUC__
	#define EXPORT __attribute__((visibility("default")))
	#define IMPORT
#else
	#warning "Unrecognised Operating System"
	#define EXPORT
	#define IMPORT
#endif

#if defined SMOG_EXPORT
	#define SMOGAPI EXPORT
#else
	#define SMOGAPI IMPORT
#endif

#define SMOG_NAMESPACE smog_ ## SMOG_VERSION_US

#define SMOG_NAMESPACE_USING using namespace SMOG_NAMESPACE;

#define SMOG_NAMESPACE_ENTER namespace SMOG_NAMESPACE

#include <SMOG/DataTypes.h>
#include <stdexcept>

SMOG_NAMESPACE_ENTER
{
	void initialiseGlew();

	void checkGLErrors();

	void printBacktrace();

	void printError(const std::string& message);

	void printWarning(const std::string& message);

	void printNotice(const std::string& message);

	#define ERROR(MESSAGE) \
	printError(MESSAGE); \
	throw std::runtime_error(MESSAGE);

	#define WARN(MESSAGE) \
	printWarning(MESSAGE);

	#define NOTICE(MESSAGE) \
	printNotice(MESSAGE);
}
