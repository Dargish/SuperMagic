#pragma once

#define SMRT_VERSION 1.0.0
#define SMRT_VERSION_US 1_0_0

#define SMRT_NAMESPACE smrt_ ## SMRT_VERSION_US

#define SMRT_NAMESPACE_USING using namespace SMRT_NAMESPACE;

#define SMRT_NAMESPACE_ENTER namespace SMRT_NAMESPACE

#include <SMRT/DataTypes.h>
#include <stdexcept>

SMRT_NAMESPACE_ENTER
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
