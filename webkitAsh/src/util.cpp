/*
 * util.cpp
 *
 *  Created on: 2020年8月29日
 *      Author: zzzzzzzzzzz
 */

#include "ext.h"

bool find__(std::string& name1, Window_*& ret) {
	size_t i = name1.find('&');
	if(i != std::string::npos) {
		std::string name = name1.substr(i + 1);
		name1 = name1.substr(0, i);
		char c = name[0];
		if(c >= '0' && c <= '9') {
			size_t i = std::stoi(name);
			if(i < Window_::ls_.size()) {
				ret = Window_::ls_[i];
			}
			return true;
		}
		ret = window__(name);
		return true;
	}
	return false;
}

Window_* window__(std::string& name) {
	for(Window_* w : Window_::ls_) {
		const char* name1 = w->name__();
		//printf("window__ %lu %p %s %s\n",Window_::ls_.size(),w,name.c_str(),name1);
		if(name1 && name1 == name) {
			return w;
		}
	}
	return nullptr;
}

void close__(View_* v) {
	Notebook_* nb = (Notebook_*)v->var__("nb");
	void* from = nullptr;
	if(nb->num__(v->hr__()) == nb->curr__())
		from = v->var__("从");
	call__(v, nb, nullptr, {"关闭"});
	nb->rm__(v->hr__());
	delete v;
	int n = nb->len__();
	if(n == 0) {
		if(nb->var__("可空"))
			return;
		Window_* w = (Window_*)nb->own_;
		w->del__(nb);
		return;
	}
	if(from) {
		for(int i = 0; i < n; i++) {
			GtkWidget* w = nb->nth__(i);
			if(w == from) {
				nb->curr__(i);
				break;
			}
		}
	}
}

void quit__() {
	call__(nullptr, nullptr, nullptr, {"退出"});
	gtk_main_quit();
}

void chuantou__(GtkWidget *widget) {
	cairo_region_t *r = cairo_region_create();
	gtk_widget_input_shape_combine_region (widget, r);
	cairo_region_destroy(r);
}

void tags_get__(pub::tags___ tags, Parm_ p, size_t from,
		std::function<void(const std::string&, size_t)> fn,
		std::function<bool(size_t)> fn2) {
	std::string tag;
	size_t argc;
	for(; from < p.size();) {
		switch(tags.get__(p, tag, &argc, from)) {
		case 'y': {
			from += 1;
			fn(tag, argc == 0 ? from-1 : from);
			from += argc;
			break; }
		case 'n':
			if(!fn2(from))
				throw "选项“" + p[from] + "”不支持";
			from += 1;
			break;
		case '<': throw SIZE_MAX;
		}
	}
}

const std::string& p_or__(Parm_ p, size_t i) {
	if(i >= p.size()) throw i;
	return p[i];
};

bool bool__(const std::string& val) {
	return !(val.empty() || val == "0" || val == "false" || val == "NULL");
}
bool bool__(const std::vector<std::string>& p, size_t i, bool b) {
	return p.size() > i ? bool__(p[i]) : b;
}


