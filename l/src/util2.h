/*
 * util2.h
 *
 *  Created on: 2021年3月27日
 *      Author: zzzzzzzzzzz
 */

#ifndef UTIL2_H_
#define UTIL2_H_

#include <functional>
#include <string>

void repl__(const std::string& s, const std::string& sp,
		std::function<void(const std::string&)> fn1, std::function<void()> fn2);

size_t startswith__(const char* s, const char* s2);



#endif /* UTIL2_H_ */
