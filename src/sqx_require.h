/**
 * Copyright (c) 2017 Mathew Mariani
 *
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the MIT license. See `sqx_require.cc` for details.
 */

#ifndef SQX_REQUIRE_H
#define SQX_REQUIRE_H

// forward declare SQVM
struct SQVM;

#if defined(WIN32) || defined(_WIN32)
	#define SQX_API __declspec(dllexport)
#else
	#define SQX_API
#endif

#ifdef __cplusplus
extern "C" {
#endif

SQX_API int sqx_register_require(SQVM* v);

#ifdef __cplusplus
}
#endif

#endif // SQX_REQUIRE_H
