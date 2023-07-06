/*
 * View.h
 *
 *  Created on: 2020年8月23日
 *      Author: zzzzzzzzzzz
 */

#ifndef VIEW_H_
#define VIEW_H_

#include <webkit2/webkit2.h>
#include <string>
#include <vector>
#include "typ.h"
#include "Base.h"

class View_;
class Button_ {
public:
	std::string name_;
	View_* v_;
	std::string code_;
	VS_ args_;
	GtkWidget *hr_;
};

class View_ : public Base_ {
private:
	std::vector<Button_*> btns_;
	WebKitWebContext* ctt_ = nullptr;
	WebKitSettings *set__() {return webkit_web_view_get_settings (hr1__());}
public:
	View_(WebKitWebView *rv = nullptr, bool is_priv = false);
	virtual ~View_();

	void say_init__();

	WebKitWebView *hr1__() {return WEBKIT_WEB_VIEW(hr_);}

	bool cb__(Parm_ p, void* ret1, Ret_ ret);
	GtkWidget* add_btn__(Button_* btn, const char* icon_name, GtkIconSize icon_size, GtkBox* box);

	static View_* from__(GtkWidget *w);
	static View_* from__(const std::string&);

	static void cookie__(WebKitWebContext* c, const std::string& file);
};

#endif /* VIEW_H_ */
