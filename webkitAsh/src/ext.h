/*
 * ext.h
 *
 *  Created on: 2020年8月24日
 *      Author: zzzzzzzzzzz
 */

#ifndef EXT_H_
#define EXT_H_

#include "typ.h"
#include "pub/tag.h"
#include "View.h"
#include "Notebook.h"
#include "Window.h"
#include <functional>

void call__(void* v, void* nb, void* w, ILs_ a, Ret_ ret = nullptr);
void call__(void* v, void* nb, void* w, It_ begin, It_ end, Ret_ ret = nullptr);
void call__(void* v, void* nb, void* w, const std::string& src1, bool arg0, ILs_ a, Ret_ ret = nullptr);
void call__(void* v, void* nb, void* w, const std::string& src1, bool arg0, It_ begin, It_ end, Ret_ ret = nullptr);
void callj__(void* v, void* nb, void* w, const std::string& src1, bool arg0, ILs_ a, Ret_ ret);

void repl__(const std::string& s, const std::string& sp,
		std::function<void(const std::string&)> fn1, std::function<void()> fn2);
void tags_get__(pub::tags___ tags, Parm_ p, size_t from,
		std::function<void(const std::string&, size_t)> fn,
		std::function<bool(size_t)> fn2);
const std::string& p_or__(Parm_ p, size_t i);
void ret_or__(const char* s, bool dunhao, void* ret1, Ret_ ret);
bool bool__(const std::string& val);
bool bool__(const std::vector<std::string>& p, size_t i, bool b);

View_* new_view__(WebKitWebView *rv, bool is_priv, NotebookOpt_* nbo, Notebook_* nb,
		const std::string& pos, const std::string& nb_pos, const std::string& box_pos,
		const std::string& name, const std::string& nb_name, const std::string& box_name);
void close__(View_* v);

bool find__(std::string& name, Window_*& w);
Window_* window__(std::string& name);
bool is_main_window__(Window_* w);

extern std::string webkitx_;

extern int quit_;
void quit__();

void chuantou__(GtkWidget *widget);

#endif /* EXT_H_ */
