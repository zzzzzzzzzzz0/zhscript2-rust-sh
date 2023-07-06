/*
 * L4.h
 *
 *  Created on: 2020年7月15日
 *      Author: zzzzzzzzzzz
 */

#ifndef L4_H_
#define L4_H_

#include "typ.h"

class L4_ {
private:
	void* hr_ = nullptr;
	bool open__(const char* path, std::string &err);
	bool sym__(const char* name, void** ret, std::string &err);

	void *eval_ = nullptr, *free_ = nullptr, *load_ = nullptr;
	void *add_ = nullptr, *dunhao_ = nullptr;
	void *path_ = nullptr;

	void free__(char* s) {((void(*)(char*))free_)(s);}
public:
	L4_();
	virtual ~L4_();
	int init__(int argc, char** argv, std::string& err, std::string* path2 = nullptr);
	int load__(const char* src) {return ((int(*)(const char*))load_)(src);}
	int load2__(const char* arg0);

	std::string eval__(const std::string& s, const ILs_& a = {}, int* err = nullptr);
	/*int eval__(const std::string& s, const ILs_& a, Ret_ ret);
	int eval__(const std::string& s, It_ begin, It_ end, Ret_ ret);*/

	int eval__(Cb_ cb, const std::string& p1, const std::string& src1, bool arg0, const ILs_& a, Ret_ ret);
	int eval__(Cb_ cb, const std::string& p1, const std::string& src1, bool arg0, It_ begin, It_ end, Ret_ ret);
	int evalj__(Cb_ cb, const std::string& p1, const std::string& src1, bool arg0, const ILs_& a, Ret_ ret);

	char* eval_1__(int* err, const char* src, Ret_ p, char ctl);
	std::string eval_2__(char* ret0) {
		std::string ret = ret0;
		free__(ret0);
		return ret;
	}
	void eval_3__(const std::string& s, Ret_ ret);
	void eval_3j__(const std::string& s, Ret_ ret);

	void add__(void* ret, const std::string& s) {((void(*)(void*,const char*))add_)(ret, s.c_str());}
	void adddunhao__(void* ret) {((void(*)(void*))dunhao_)(ret);}
	void path__(const std::string& s) {((void(*)(const char*))path_)(s.c_str());}
};

std::string def_shi__(Cb_ cb, void* ret, const std::string& p1);
bool exists__(const std::string& filename, const char* typ = nullptr);
bool realpath__(std::string &path);
bool dir__(const std::string &path, std::string &dir);

#endif /* L4_H_ */
