/*
 * L4.cpp
 *
 *  Created on: 2020年7月15日
 *      Author: zzzzzzzzzzz
 */

#include "L4.h"
#include "util2.h"
#include <dlfcn.h>
#include <sys/stat.h>
#include <unistd.h>

template<class It>
std::string z__(L4_* this1, const std::string& head, const std::string& src1, char ctl, It begin, It end, int* err, void* ret) {
	std::string s = head.empty() ? "解释‘参数1’、‘参数栈【2】’" : head;
	VS_ p;
	auto add__ = [&](auto s2) {
		p.push_back(s2);
	};
	add__(src1);
	for(auto it = begin; it != end; ++it) add__(*it);
	return this1->eval_2__(this1->eval_1__(err, s.c_str(), &p, ctl));
}
std::string L4_::eval__(const std::string& s, const ILs_& a, int* err) {
	return z__(this, "", s, '0', a.begin(), a.end(), err, nullptr);
}
/*int L4_::eval__(const std::string& s, const ILs_& a, Ret_ ret) {
	int err = 0;
	eval_3__(z__(this, "", s, '0', a.begin(), a.end(), &err, ret), ret);
	return err;
}
int L4_::eval__(const std::string& s, It_ begin, It_ end, Ret_ ret) {
	int err = 0;
	eval_3__(z__(this, "", s, '0', begin, end, &err, ret), ret);
	return err;
}*/

template<class It>
std::string z__(L4_* this1, Cb_ cb, const std::string& p1, const std::string& src1, char ctl,
		bool arg0, It begin, It end, int* err, void* ret) {
	return z__(this1, def_shi__(cb, ret, p1) +
			(arg0 ? "解释【‘参数2’】‘参数1’、‘参数栈【3】’" : "解释‘参数1’、‘参数栈【2】’"),
			src1, ctl, begin, end, err, ret);
}
int L4_::eval__(Cb_ cb, const std::string& p1, const std::string& src1, bool arg0, const ILs_& a, Ret_ ret) {
	int err = 0;
	eval_3__(z__(this, cb, p1, src1, '0', arg0, a.begin(), a.end(), &err, ret), ret);
	return err;
}
int L4_::eval__(Cb_ cb, const std::string& p1, const std::string& src1, bool arg0, It_ begin, It_ end, Ret_ ret) {
	int err = 0;
	eval_3__(z__(this, cb, p1, src1, '0', arg0, begin, end, &err, ret), ret);
	return err;
}
int L4_::evalj__(Cb_ cb, const std::string& p1, const std::string& src1, bool arg0, const ILs_& a, Ret_ ret) {
	int err = 0;
	eval_3j__(z__(this, cb, p1, src1, 'j', arg0, a.begin(), a.end(), &err, ret), ret);
	return err;
}

static void p2arg__(Ret_ p, size_t& argc, const char**& argv) {
	if(p) {
		argc = p->size();
		argv = new const char*[argc];
		for(size_t i = 0; i < argc; i++) {
			const std::string& s = (*p)[i];
			argv[i] = s == "NULL" ? nullptr : s.c_str();
		}
	}
}
char* L4_::eval_1__(int* err, const char* src, Ret_ p, char ctl) {
	size_t argc = 0;
	const char** argv = nullptr;
	p2arg__(p, argc, argv);
	char* ret = ((char*(*)(int*, char, const char*, size_t, const char**))eval_)(err, ctl, src, argc, argv);
	if(argv) delete argv;
	return ret;
}

void L4_::eval_3__(const std::string& s, Ret_ ret) {
	if(!ret)
		return;
	repl__(s, "|\f", [&](const std::string& ss) {
		ret->push_back(ss);
	}, [](){});
}

void L4_::eval_3j__(const std::string& s, Ret_ ret) {
	if(!ret)
		return;
	if(s[0] == '[' && !ret->empty()) {
		std::string s2 = s.substr(0, 1);
		for(auto s3 : *ret) {
			s2 += '"';
			repl__(s3, "\"", [&](const std::string& ss) {
				s2 += ss;
			}, [&](){
				s2 += "\\\"";
			});
			s2 += "\",";
		}
		s2 += s.substr(1);
		ret->clear();
		ret->push_back(s2);
	} else {
		ret->push_back(s);
	}
}

bool L4_::open__(const char* path, std::string &err) {
	hr_ = dlopen(path, RTLD_LAZY);
	if(hr_)
		return true;
	err += "\n";
	err += dlerror();
	return false;
}

bool L4_::sym__(const char* name, void** ret, std::string &err) {
	*ret = dlsym(hr_, name);
	if(*ret)
		return true;
	err += "\n";
	err += dlerror();
	return false;
}

int L4_::init__(int argc, char** argv, std::string& err, std::string* path2) {
	std::string path, shl = argv[0], soname = "l4.so";
	{
		std::string s2 = "-zhscript-l4-";
		for(int i = 1; i < argc; i++) {
			char* s = argv[i];
			if(startswith__(s, s2.c_str())) {
				std::string s3 = s;
				s3 = s3.substr(s2.size());
				size_t i3 = s3.find(' ');
				if(i3 != std::string::npos)
					s3 = s3.substr(0, i3);
				soname += s3;
				break;
			}
		}
	}

	VS_ paths;
	while(exists__(shl, "l")) {
		paths.push_back(shl);
		//printf("shl\t%s\n", shl.c_str());
		if(shl[0] == '/' || startswith__(shl.c_str(), "./bin/")) {
			std::string path;
			if(dir__(shl, path)) {
				path += "lib";
				//printf("path\t%s\n", path.c_str());
				if(exists__(path, "dl"))
					break;
			}
		}
		if(!realpath__(shl))
			break;
	}
	for(;;) {
		auto o__ = [&](const char* path2) {
			if(open__(path2, err)) {
				paths.push_back(path2);
				//printf("path2\t%s\n", path2);
				path = path2;
				return true;
			} else
				return false;
		};
		{
			std::string path;
			if(dir__(shl, path)) {
				path += soname;
				if(o__(path.c_str()))
					break;
			}
		}
		//if(o__("/usr/lib/zhscript2-rust/l4.so")) break;
		return 255;
	}
	if(!sym__("c_i__", &eval_, err)) return 255;
	if(!sym__("c_i_free__", &free_, err)) return 255;
	if(!sym__("c_load__", &load_, err)) return 255;
	if(!sym__("c_add__", &add_, err)) return 255;
	if(!sym__("c_dunhao__", &dunhao_, err)) return 255;
	if(!sym__("c_path__", &path_, err)) return 255;
	for(auto s : paths) {
		path__(s);
	}
	void *p;
	if(!sym__("c_lpars__", &p, err)) return 255;
	int err2 = 0;
	((void(*)(int*, int, char**))p)(&err2, argc, argv);
	if(err2) return err2;
	if(!sym__("c_cfg_shl__", &p, err)) return 255;
	((void(*)(const char*))p)(shl.c_str());

	eval__("赋予“l4.so”【顶】、“外壳”【顶】、“窗口”【顶】以“" + path + "”、“" + shl + "”、“linux”");
	if(path2)
		*path2 = path;
	return 0;
}

int L4_::load2__(const char* arg0) {
	std::string src;
	for(;;) {
		int err = load__(src.c_str());
		if(err) {
			if(err == 250) {
				src = eval__("‘参数0【顶】’");
				if(src.empty()) {
					src += arg0;
					src += ".zs";
					if(exists__(src))
						continue;
					src = arg0;
					bool ok = false;
					for(;;) {
						size_t i = src.size() - 1;
						//printf("src\t%s %lu\n", src.c_str(), i);
						if(src[i] == 's' && src[i - 1] == 'z' && src[i - 2] == '_') {
							src[i - 2] = '.';
							if(exists__(src)) {
								ok = true;
								break;
							}
						}
						if(src[i] == '-') {
							src = src.substr(0, i);
						} else
							break;
					}
					if(ok)
						continue;
					return err;
				} else
					return err;
			} else
				return err;
		}
		return err;
	}
}

L4_::L4_() {
}

L4_::~L4_() {
}

std::string def_shi__(Cb_ cb, void* ret, const std::string& p1) {
	return "函数“接口”以“*" + std::to_string((unsigned long)cb) + "”、“-R-u:" +
			std::to_string((unsigned long)ret) + p1 + R"(-Z”。
定义使以下代码
	调用‘接口’、‘参数栈’。
上代码。
)";
}

bool exists__(const std::string& filename, const char* typ) {
	struct stat buf;
	if(lstat(filename.c_str(), &buf) != 0)
		return false;
	if(typ) {
		for(; *typ; typ++) {
			switch(*typ) {
			case 'l':
				if(S_ISLNK(buf.st_mode))
					return true;
				break;
			case 'd':
				if(S_ISDIR(buf.st_mode))
					return true;
				break;
			}
		}
		return false;
	}
	return true;
}
bool realpath__(std::string &path) {
	char buf[512] = "";
	ssize_t i = readlink(path.c_str(), buf,512);
	if(i == -1 || i == 0)
		return false;
	if(buf[0] == '/')
		path = buf;
	else {
		if(dir__(path, path))
			path += buf;
	}
	return true;
}
bool dir__(const std::string &path, std::string &dir) {
	size_t i = path.rfind('/');
	if(i != std::string::npos) {
		dir = path.substr(0, i + 1);
		return true;
	}
	return false;
}
