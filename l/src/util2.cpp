/*
 * util2.cpp
 *
 *  Created on: 2021年3月27日
 *      Author: zzzzzzzzzzz
 */

#include "util2.h"



void repl__(const std::string& s, const std::string& sp,
		std::function<void(const std::string&)> fn1, std::function<void()> fn2) {
	size_t from = 0;
	for(;;) {
		size_t i = s.find(sp, from);
		fn1(s.substr(from, i - from));
		if(i == std::string::npos)
			break;
		fn2();
		from = i + sp.length();
	}
}

size_t startswith__(const char* s, const char* s2) {
	if(s && s2)
	for(size_t i = 0;; i++) {
		if(!s2[i])
			return i;
		if(!s[i] || s[i] != s2[i])
			return 0;
	}
	return 0;
}

