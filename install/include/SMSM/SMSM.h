#pragma once

#define SMSM_VERSION 1.0.0
#define SMSM_VERSION_US 1_0_0

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

#if defined SMSM_EXPORT
	#define SMSMAPI EXPORT
#else
	#define SMSMAPI IMPORT
#endif

#define SMSM_NAMESPACE smog_ ## SMSM_VERSION_US

#define SMSM_NAMESPACE_USING using namespace SMSM_NAMESPACE;

#define SMSM_NAMESPACE_ENTER namespace SMSM_NAMESPACE

#include <SMSM/DataTypes.h>

#define SMSM_TYPENAME(NAME) \
	static constexpr char const* TYPE_NAME = #NAME; \
	virtual std::string typeName() const \
	{ \
		return NAME::TYPE_NAME; \
	}
