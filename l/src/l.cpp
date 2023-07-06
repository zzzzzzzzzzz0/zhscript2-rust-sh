/*
 * l.cpp
 *
 *  Created on: 2020年9月15日
 *      Author: zzzzzzzzzzz
 */

#include <cstdio>
#include <cstdarg>

#include "L4.h"

int main(int argc, char* argv[])
{
	L4_ l4_;
	{
		std::string err;
		int err2 = l4_.init__(argc, argv, err);
		if(err2) {
			fprintf(stderr, "%s\n", err.c_str());
			return err2;
		}
	}
	int err = l4_.load2__(argv[0]);
	return err < 0 ? 0 : err;
}

