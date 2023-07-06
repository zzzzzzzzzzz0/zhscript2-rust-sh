/*
 * tag.cpp
 *
 *  Created on: 2017年8月5日
 *      Author: zzzzzzzzzzz
 */

#include "tag.h"

namespace pub {

char tags___::get__(const std::vector<std::string>& p, std::string &tag, size_t *argc, size_t from) {
	if(p.size() <= from)
		return '<';
	for(tag___ i : a_) {
		if(p[from] == i.flag_) {
			if(p.size() - from >= i.argc_ + 1) {
				tag = i.flag2_;
				if(argc)
					*argc = i.argc_;
				return 'y';
			}
			return '<';
		}
	}
	return 'n';
}

} /* namespace pub */
