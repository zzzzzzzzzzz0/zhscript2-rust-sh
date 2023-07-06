/*
 * typ.h
 *
 *  Created on: 2020年8月30日
 *      Author: zzzzzzzzzzz
 */

#ifndef TYP_H_
#define TYP_H_

#include <string>
#include <vector>

using ILs_ = std::initializer_list<std::string>;
using VS_ = std::vector<std::string>;
using It_ = VS_::iterator;
using Parm_ = const VS_&;
using Ret_ = VS_*;

using Cb_ = void (*)(void* ret1, Ret_ ret, void*, void*, void*, size_t argc, ...);

#endif /* TYP_H_ */
