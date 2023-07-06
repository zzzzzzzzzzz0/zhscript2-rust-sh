/*
 * Base.h
 *
 *  Created on: 2020年9月6日
 *      Author: zzzzzzzzzzz
 */

#ifndef BASE_H_
#define BASE_H_

#include <gtk/gtk.h>
//#include <string>

class Base_ {
protected:
	GtkWidget *hr_ = nullptr;
	//std::string name_;
public:
	Base_();
	virtual ~Base_();

	GtkWidget *hr__() {return hr_;}

	void name__(const char* name) {
		gtk_widget_set_name(hr_, name);
		//name_ = name;
	}
	const char* name__() {
		return name__(hr_);
		//return name_.c_str();
	}

	void var__(const char *name, gpointer data) {var__(hr_, name, data);}
	auto var__(const char *name) -> gpointer {return var__(hr_, name);}

	static const char* name__(GtkWidget* hr) {
		return gtk_widget_get_name(hr);
	}
	static void var__(GtkWidget* hr, const char *name, gpointer data) {
		g_object_set_data(G_OBJECT(hr), name, data);
	}
	static gpointer var__(GtkWidget* hr, const char *name) {
		return g_object_get_data(G_OBJECT(hr), name);
	}
};

#endif /* BASE_H_ */
