/*
 * View.cpp
 *
 *  Created on: 2020年8月23日
 *      Author: zzzzzzzzzzz
 */

#include "View.h"
#include "ext.h"
#include "util2.h"
#include <JavaScriptCore/JavaScript.h>

static void add__(JSValueRef& value, JSGlobalContextRef& context, VS_& p) {
	if(JSValueIsArray(context, value)) {
		JSObjectRef o = JSValueToObject(context, value, NULL);
		JSPropertyNameArrayRef properties = JSObjectCopyPropertyNames(context, o);
		size_t count =  JSPropertyNameArrayGetCount(properties);
		JSPropertyNameArrayRelease(properties);

		for (size_t i = 0; i < count; i++) {
			JSValueRef propertyValue = JSObjectGetPropertyAtIndex(context, o, i, NULL);
			add__(propertyValue, context, p);
		}
		return;
	}

	JSStringRef js_str_value;
	gchar      *str_value;
	gsize       str_length;

	js_str_value = JSValueToStringCopy (context, value, NULL);
	str_length = JSStringGetMaximumUTF8CStringSize (js_str_value);
	str_value = (gchar *)g_malloc (str_length);
	JSStringGetUTF8CString (js_str_value, str_value, str_length);
	JSStringRelease (js_str_value);
	p.push_back(str_value);
	g_free (str_value);
}

class Data1_ {
public:
	View_* v_;
	std::string s_;
};

static void finished__(GObject *object, GAsyncResult *result, gpointer user_data) {
	WebKitJavascriptResult *js_result;
	GError                 *error = NULL;
	Data1_* data1 = (Data1_*)user_data;

	js_result = webkit_web_view_run_javascript_finish (WEBKIT_WEB_VIEW (object), result, &error);
	if (!js_result) {
		g_printerr("%s\n", error->message);
		g_error_free (error);
	} else {
		JSGlobalContextRef context = webkit_javascript_result_get_global_context (js_result);
		JSValueRef value = webkit_javascript_result_get_value (js_result);
		VS_ p;
		add__(value, context, p);
		call__(data1->v_, nullptr, nullptr, data1->s_, false, p.begin(), p.end());
		webkit_javascript_result_unref (js_result);
	}
	delete data1;
}

static void run_js__(WebKitWebView *wv, const char* s, Data1_* ud) {
	if(ud)
		webkit_web_view_run_javascript (wv, s, NULL, finished__, ud);
	else
		webkit_web_view_run_javascript (wv, s, NULL, nullptr, NULL);
}

static void cb_clicked__(GtkButton *button, Button_* btn) {
	call__(btn->v_, nullptr, nullptr, btn->code_, true, btn->args_.begin(), btn->args_.end());
}

#include "pub/eventget.h"
class view_event_get___ : public pub::event_get___ {
public:
	void jieshi__(void *hr, const std::string& code, const std::string& name,
				const std::vector<std::string>* p1, std::vector<std::string>* ret) {
		VS_ p;
		p.push_back(name);
		if(p1)
			for(auto s : *p1)
				p.push_back(s);
		call__(hr, nullptr, nullptr, code, true, p.begin(), p.end(), ret);
	}
};
static view_event_get___ event_get_;

static pub::tags___ tags_ = {
		{"插脚", "j", 1},
		{"刷新", "r", 0},
		{"后退", "<", 0},
		{"前进", ">", 0},
		{"网址", "u", 0},
		{"名", "n", 0},
		{"缩放", "z", 0},
		{"敏感", "S", 0},
		{"背景色", "B", 1},
		{"调试器", "I", 0},
		{"禁js", "J", 0},
		{"ua", "@", 0},
		//{"cookie", "C", 1},
		{"代理", "#", 1},
		{"钮提示", "bT", 1},
		{"藏钮", "b-", 0},
		{"显钮", "bs", 0},
		{"加钮", "b+", 3},
		{"事件", "e", 0},
		{"页鼠标穿透", "!m", 0},
};
bool View_::cb__(Parm_ p, void* ret1, Ret_ ret) {
	std::string tag;
	switch(tags_.get__(p, tag)) {
	case 'y': {
		auto ret__ = [&](const char* s, bool dunhao = false) {ret_or__(s, dunhao, ret1, ret);};

		switch(tag[0]) {
		case 'j':
			run_js__(hr1__(), p[1].c_str(), p.size() > 2 ? new Data1_ {this, p[2]} : nullptr);
			break;
		case 'r': webkit_web_view_reload (hr1__()); break;
		case '<': webkit_web_view_go_back (hr1__()); break;
		case '>': webkit_web_view_go_forward (hr1__()); break;
		case 'u':
			if(p.size() > 1) {
				webkit_web_view_load_uri(hr1__(), p[1].c_str());
			} else
				ret__(webkit_web_view_get_uri (hr1__()));
			break;
		case 'n':
			ret__(name__());
			break;
		case 'z':
			if(p.size() > 1) {
				webkit_web_view_set_zoom_level(hr1__(), std::stod(p[1]));
			} else
				ret__(std::to_string(webkit_web_view_get_zoom_level (hr1__())).c_str());
			break;
		case 'S':
			if(p.size() > 1) {
				gtk_widget_set_sensitive(hr__(), bool__(p,1, true));
			} else {
				ret__(std::to_string(gtk_widget_get_sensitive(hr__())).c_str());
			}
			break;
		case 'B': {
			GdkRGBA bc;
			if(!gdk_rgba_parse (&bc, p[1].c_str())) {
				throw p[1] + " 格式错误";
			}
			webkit_web_view_set_background_color(hr1__(), &bc);
			break; }
		case 'I': {
			WebKitWebInspector *wi = webkit_web_view_get_inspector (hr1__());
			webkit_web_inspector_show(wi);
			break; }
		case 'J':
			webkit_settings_set_enable_javascript (set__(), false);
			break;
		case '@':
			if(p.size() > 1)
				webkit_settings_set_user_agent(set__(), p[1].c_str());
			else
				ret__(webkit_settings_get_user_agent(set__()));
			break;
		//case 'C': cookie__(ctt_, p[1]); break;
		case '#': {
			WebKitNetworkProxySettings* s = webkit_network_proxy_settings_new(p[1].c_str(), nullptr);
			webkit_web_context_set_network_proxy_settings(
					ctt_ ? ctt_ : webkit_web_context_get_default(),
					WEBKIT_NETWORK_PROXY_MODE_CUSTOM, s);
			webkit_network_proxy_settings_free(s);
			break; }
		case 'b':
			switch(tag[1]) {
			case '+': {
				const std::string& name = p[1];
				Button_* btn = new Button_{name, this, p[2], {name}};
				GtkIconSize icon_size = GTK_ICON_SIZE_MENU;
				std::string box = "钮盒";
				tags_get__({
					{"-大小", "s", 1},
					{"-钮盒2", "b", 0},
					{"-钮盒3", "b", 0},
				}, p, 4, [&](const std::string& tag, size_t i) {
					switch(tag[0]) {
					case 's': icon_size = (GtkIconSize)std::stoi(p[i]); break;
					case 'b': box = p[i].substr(1); break;
					}
				}, [&](size_t i) -> bool {
					btn->args_.push_back(p[i]);
					return true;
				});
				g_signal_connect(add_btn__(btn, p[3].c_str(), icon_size, GTK_BOX(var__(box.c_str()))),
						"clicked", G_CALLBACK(cb_clicked__), btn);
				gtk_widget_set_tooltip_markup(btn->hr_, name.c_str());
				break; }
			default:
				for(size_t i = tag[1] == 'T' ? 2 : 1; i < p.size(); i++) {
					for(Button_* btn : btns_) {
						if(btn->name_ == p[i]) {
							switch(tag[1]) {
							case 'T': gtk_widget_set_tooltip_markup(btn->hr_, p[1].c_str()); break;
							case '-': gtk_widget_hide (btn->hr_); break;
							case 's': gtk_widget_show (btn->hr_); break;
							}
						}
					}
				}
				break;
			}
			break;
		case 'e':
			switch(event_get_.api__(p, hr__(), this)) {
			case '<': throw SIZE_MAX;
			}
			break;
		case '!':
			switch(tag[1]) {
			case 'm': chuantou__(hr__()); break;
			}
			break;
		}
		return true; }
	case '<': throw SIZE_MAX;
	}
	return false;
}

void View_::cookie__(WebKitWebContext* c, const std::string& file) {
	WebKitCookieManager* cm = webkit_web_context_get_cookie_manager(c);
	std::string txt = ".txt";
	size_t i = file.rfind(txt), i2 = file.length() > txt.length() ? file.length() - txt.length() : 0;
	webkit_cookie_manager_set_persistent_storage(cm, file.c_str(), i == i2 ?
			WEBKIT_COOKIE_PERSISTENT_STORAGE_TEXT :
			WEBKIT_COOKIE_PERSISTENT_STORAGE_SQLITE);
	WebKitCookieAcceptPolicy cap = WEBKIT_COOKIE_POLICY_ACCEPT_ALWAYS;
	webkit_cookie_manager_set_accept_policy(cm, cap);
}

GtkWidget* View_::add_btn__(Button_* btn2, const char* icon_name, GtkIconSize icon_size, GtkBox* box) {
	if(!btn2)
		btn2 = new Button_{"关闭", this};

	GtkWidget *btn = gtk_button_new();
	GtkButton* btn1 = GTK_BUTTON(btn);
	gtk_button_set_relief(btn1, GTK_RELIEF_NONE);
	gtk_button_set_image(btn1, gtk_image_new_from_icon_name(icon_name, icon_size));
	gtk_box_pack_start (box, btn, false, false, 0);
	gtk_widget_show (btn);

	btn2->hr_ = btn;
	btns_.push_back(btn2);

	return btn;
}

View_* View_::from__(GtkWidget *w) {
	return (View_*)Base_::var__(w, "");
}

#include "Chan.h"
class Chanx_ : public Chan_ {
	void get__(std::string& line) {
		size_t i = startswith__(line.c_str(), "cb_send_request__");
		if(i) {
			std::string url = line.substr(i, line.size() - i - 1);
			line.clear();
			VS_ ret;
			call__(nullptr, nullptr, nullptr, {"请求", url}, &ret);
			switch(ret.size()) {
			case 1:
				line += ret[0];
				break;
			}
		} else {
			line.clear();
		}
		line += "\n";
		write__(line.c_str(), line.size());
	}
};
static Chanx_ chan_;

static gboolean closeWebViewCb(WebKitWebView* webView, View_* v)
{
	close__(v);
	return TRUE;
}

static gboolean
cb_script_dialog__ (WebKitWebView      *web_view,
               WebKitScriptDialog *dialog,
               gpointer            user_data) {
	switch (webkit_script_dialog_get_dialog_type(dialog)) {
	case WEBKIT_SCRIPT_DIALOG_PROMPT: {
		const char* s = webkit_script_dialog_get_message(dialog);
		if(s == std::string("zhscript:")) {
			const char* s2 = webkit_script_dialog_prompt_get_default_text(dialog);
			VS_ ret;
			callj__((View_*)user_data, nullptr, nullptr, s2, false, {}, &ret);
			webkit_script_dialog_prompt_set_text(dialog, ret[0].c_str());
			return true;
		}
		break; }
	default: break;
	}
	return false;
}

static GtkWidget* cb_create__ (WebKitWebView *web_view, WebKitNavigationAction *navigation_action, gpointer user_data) {
	return new_view__(web_view, false, nullptr, nullptr, "", "", "", "", "", "")->hr__();
}

void cb_ready_to_show__ (WebKitWebView *web_view, View_* v) {
	call__(v, nullptr, nullptr, {"ready_to_show"});
}

static void cb_title__(WebKitWebView *webView, GParamSpec *pspec, View_* v) {
	Notebook_* nb = (Notebook_*)v->var__("nb");
	call__(v, nullptr, nullptr, {"标题", webkit_web_view_get_title(webView), nb->num__(v->hr__()) == nb->curr__() ? "1" : ""
			/*, pspec->name, pspec->_blurb, pspec->_nick*/});
}

static void cb_load_changed__(WebKitWebView  *web_view, WebKitLoadEvent load_event, View_* v) {
	VS_ p;
	p.push_back("装载");
	const char* s = nullptr;
	switch (load_event) {
	case WEBKIT_LOAD_STARTED:    s = "始"; break;
	case WEBKIT_LOAD_REDIRECTED: s = "重定向"; break;
	case WEBKIT_LOAD_COMMITTED:  s = "确定"; break;
	case WEBKIT_LOAD_FINISHED:   s = "终"; break;
	}
	p.push_back(s);
	const char* url = webkit_web_view_get_uri(web_view);
	if(url)
		p.push_back(url);
	call__(v, nullptr, nullptr, p.begin(), p.end());
}

static gboolean cb_permission_request__(WebKitWebView *web_view, WebKitPermissionRequest *request, View_* v) {
	call__(v, nullptr, nullptr, {"权限", std::to_string(webkit_permission_request_get_type())});
	webkit_permission_request_allow (request);
/*    GtkWidget *dialog = gtk_message_dialog_new (nullptr,
                                                GTK_DIALOG_MODAL,
                                                GTK_MESSAGE_QUESTION,
                                                GTK_BUTTONS_YES_NO,
                                                "Allow Permission Request?");
    gtk_widget_show (dialog);
    gint result = gtk_dialog_run (GTK_DIALOG (dialog));

    switch (result) {
    case GTK_RESPONSE_YES:
        webkit_permission_request_allow (request);
        break;
    default:
        webkit_permission_request_deny (request);
        break;
    }
    gtk_widget_destroy (dialog);*/
	return TRUE;
}

static void cb_uri_scheme_request__ (WebKitURISchemeRequest *request, gpointer user_data) {
	VS_ ret;
	{
		gchar *code = g_uri_unescape_string(webkit_uri_scheme_request_get_path (request), NULL);
		call__(user_data, nullptr, nullptr, code, false, {}, &ret);
		switch(ret.size()) {
		case 1: case 2:
			g_free(code);
			break;
		default: {
			GError *error = g_error_new (1, 0, "%s", code);
			g_free(code);
			webkit_uri_scheme_request_finish_error (request, error);
			g_error_free (error);
			return; }
		}
	}
	GInputStream *stream;
	if(ret.size() > 1 && ret[1].empty()) {
		GFile *file = g_file_new_for_path(ret[0].c_str());
		stream = (GInputStream *)g_file_read(file, NULL, NULL);
		webkit_uri_scheme_request_finish(request, stream, -1, NULL);
		g_object_unref(file);
		g_object_unref (stream);
	} else {
		/*const std::string &contents = ret[0];*/
		gsize stream_length = ret[0].length();
		GString *result = g_string_new(ret[0].c_str());
		ret[0].clear();
		//stream = g_memory_input_stream_new_from_data (contents.c_str(), stream_length, nullptr);
		stream = g_memory_input_stream_new_from_data(g_string_free(result, FALSE), stream_length, g_free);
		webkit_uri_scheme_request_finish (request, stream, stream_length,
				ret.size() > 1 ? ret[1].c_str() : "text/html");
	}
}

std::vector<View_*> ls_;

View_* View_::from__(const std::string& name) {
	for(View_* i2 : ls_) {
		if(i2->name__() == name) {
			return i2;
		}
	}
	return nullptr;
}

View_::View_(WebKitWebView *rv, bool is_priv) {
	if(rv)
			hr_ = webkit_web_view_new_with_related_view(rv);
	else {
		if(is_priv) {
			ctt_ = webkit_web_context_new_ephemeral();

			webkit_web_context_set_web_extensions_directory(ctt_, webkitx_.c_str());
			chan_.init__();
			webkit_web_context_set_web_extensions_initialization_user_data(ctt_, chan_.gvar__());

			webkit_web_context_register_uri_scheme(ctt_, "zhscript", cb_uri_scheme_request__, this, NULL);
			WebKitSecurityManager *wksm = webkit_web_context_get_security_manager(ctt_);
			webkit_security_manager_register_uri_scheme_as_local(wksm, "zhscript");
			webkit_security_manager_register_uri_scheme_as_cors_enabled(wksm, "zhscript");

			hr_ = webkit_web_view_new_with_context(ctt_);
		} else
			hr_ = webkit_web_view_new();
	}
	var__("", this);

	WebKitSettings *wks = webkit_web_view_get_settings (hr1__());
	webkit_settings_set_allow_file_access_from_file_urls(wks, true);
	webkit_settings_set_allow_universal_access_from_file_urls(wks, true);
	//webkit_settings_set_allow_top_navigation_to_data_urls(wks, true);
	webkit_settings_set_enable_developer_extras(wks, true);
	webkit_settings_set_enable_write_console_messages_to_stdout(wks, true);
	webkit_settings_set_enable_webgl(wks, true);

	g_signal_connect(hr1__(), "close", G_CALLBACK(closeWebViewCb), this);
	g_signal_connect(hr1__(), "create", G_CALLBACK(cb_create__), this);
	g_signal_connect(hr1__(), "ready-to-show", G_CALLBACK(cb_ready_to_show__), this);
	g_signal_connect(hr1__(), "script_dialog", G_CALLBACK(cb_script_dialog__), this);
	g_signal_connect(hr1__(), "notify::title", G_CALLBACK(cb_title__), this);
	g_signal_connect(hr1__(), "load-changed", G_CALLBACK(cb_load_changed__), this);
	g_signal_connect(hr1__(), "permission-request", G_CALLBACK(cb_permission_request__), this);

	ls_.push_back(this);
}
void View_::say_init__() {
	call__(this, nullptr, nullptr, {"初始"});
}

View_::~View_() {
	ls_.erase(std::find(ls_.begin(), ls_.end(), this));
	for(Button_* i : btns_) {
		delete i;
	}
}

