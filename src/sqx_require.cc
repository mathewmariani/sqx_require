/**
 * Copyright (c) 2017 Mathew Mariani
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

// sqx
#include "sqx_require.h"

// squirrel
#include <squirrel.h>
#include <sqstdio.h>

void sqx_pushpackagetable(SQVM* v) {
	sq_pushregistrytable(v);
	sq_pushstring(v, "__package", -1);
	if (SQ_FAILED(sq_rawget(v, -2))) {
		sq_newtable(v);
		sq_pushstring(v, "__package", -1);

		// keep table on the stack
		sq_push(v, -2);
		sq_rawset(v, -4);
	}
}

SQInteger sqx_require(SQVM* v) {
	// process arguments
	const char* filename;
	sq_getstring(v, -1, &filename);

	// remove arguments
	int nargs = (sq_gettop(v) - 1);
	sq_pop(v, nargs);

	sqx_pushpackagetable(v);
	sq_pushstring(v, filename, -1);
	if (SQ_FAILED(sq_rawget(v, -2))) {
		sqstd_dofile(v, filename, SQTrue, SQTrue);
		sq_pushstring(v, filename, -1);

		// keep the return value on the stack
		sq_push(v, -2);
		sq_rawset(v, -4);
	}

	sq_remove(v, -3);	// registry table
	sq_remove(v, -2);	// package table

	return 1;
}

int sqx_register_require(SQVM* v) {
	sq_pushstring(v, "require", -1);
	sq_newclosure(v, sqx_require, 0);
	sq_setparamscheck(v, 2, _SC("ts"));
	sq_setnativeclosurename(v, -1, "require");
	sq_newslot(v, -3, SQFalse);
	return 1;
}
