#include <cstdarg>
#include "Window.h"
#include "ext.h"

#include "L4.h"
static L4_ l4_;

static std::string cb_, css_;
static Window_ *main_window_ = nullptr;

bool is_main_window__(Window_* w) {return w == main_window_;}

View_* new_view__(WebKitWebView *rv, bool is_priv, NotebookOpt_* nbo, Notebook_* nb,
		const std::string& pos, const std::string& nb_pos, const std::string& box_pos,
		const std::string& name, const std::string& nb_name, const std::string& box_name) {
	View_* v = new View_(rv, is_priv);
	if(!name.empty())
		v->name__(name.c_str());
	Window_* w = nullptr;
	if(rv && !nb) {
		nb = Notebook_::from__(GTK_WIDGET(rv));
	}
	if(!w && nb)
		w = (Window_*)nb->own_;
	(w ? w : main_window_)->add__(v, nbo, nb, pos, nb_pos, box_pos, nb_name, box_name);
	return v;
}

static void page1__(WebKitWebView *webView) {
	auto z__ = [](const char* s, const char* cod1, const char* cod2) {
		std::string ret;
		ret += R""(<input type=button onclick=")"";
		ret += cod1;
		ret += "prompt('zhscript:',this.value)";
		ret += cod2;
		ret += R""(" value=")"";
		repl__(s, "\"", [&](const std::string& ss) {
			ret += ss;
		}, [&](){
			ret += "&quot;";
		});
		ret += R""(">)"";
		return ret;
	};
	auto zs = [&](const char* s) {
		return z__(s, "alert(", ")");
	};
	auto zs1 = [&](const char* s) {
		return z__(s, "", "");
	};
	auto zs2 = [&](const char* s) {
		return z__(s, "var s=", ";var a=eval(s);alert(s+'\\n\\n'+a+'\\n'+a.length)");
	};
	webkit_web_view_load_html(webView, (R""(<title>page1__</title>
<input type=button onclick='alert()'>
<input type=button onclick="var ret=prompt('1','2'); if(ret)alert(ret)">
<input type=button onclick="alert(prompt('zhscript:1','2'))">

)""
			+ zs("1制表符2")
			+ zs2("1、22、、、、true、false、null、undefined、啊、'\"")
			+ zs("‘外壳’换行换行‘窗口’")
			+ zs2("‘参数0【顶】’、‘参数【顶】’、‘参数栈【顶】’")
			+ zs1("使新开、http://weibo.com")
			+ zs1(R""(使加钮、赞、下代码
	显示‘参数0’换行
上代码、gtk-about)"")
			+ zs1(R""(使加钮、最大化、下代码
	使‘参数0’
上代码、gtk-fullscreen、
-钮盒2)"")
			+ zs2("1。使网址。、哦哦、。使宽高")
			+ zs1("使新开、http://weibo.com、-名、微博")
			+ zs1(R""(使-直、微博、加钮、赞、下代码
	显示‘参数’‘参数0’先使网址了换行
上代码、gtk-about、-大小、6、啊、哦哦)"")
			+ R""(
<br><br>
<textarea style="width:600px;height:100px;" onclick="prompt('zhscript:',this.value)">
使新开、zhscript:下代码
	“<meta charset="utf-8" />
	<img src='file:/usr/share/icons/HighContrast/48x48/actions/system-run.png'>”<br>
	‘外壳’<hr>‘参数0【顶】’<br>‘参数【顶】’
上代码
</textarea>
<br><br>
<a href="http://baidu.com">b</a> 
<br><br>
<a href="javascript:window.close()">close</a> 
)"").c_str(), NULL);
}

static void g_log__(const gchar *log_domain, GLogLevelFlags log_level,const gchar *message,gpointer user_data){
	if(user_data)
		g_printerr("%#x-%s: %s\n", log_level, log_domain, message);
}

static gboolean idle_xa__(gpointer user_data) {
	Notebook_* nb = (Notebook_*)user_data;
	for(; nb->len__() > 0;)
		close__(View_::from__(nb->nth__(0)));
	return G_SOURCE_REMOVE;
}

class idle___ {
public:
	std::string code_;
	View_* v_;
	Notebook_* nb_;
	Window_* w_;
};
static gboolean idle__(gpointer user_data);

static pub::tags___ tags_ = {
		{"标签", "L", 0},
		{"标签提示", "T", 0},
		{"激活", "a", 0},
		{"屏宽高", "s", 0},
		{"新开", "n", 1},
		{"页关闭", "x", 0},
		{"页关闭所有", "xa", 0},
		{"页关闭相关", "xt", 0},
};
static pub::tags___ tags2_ = {
		{"创建", "c", 0},
		{"cookie", "C", 1},
		{"懒", "_", 1},
		{"回调", " ", 1},
		{"css", "s", 1},
		{"g_log", "L", 2},
};
static void cb__(void* ret1, Ret_ ret, void* v1, void* nb1, void* w1, size_t argc, ...) {
	VS_ p;
	try {
		Box_* box = nullptr;
		Notebook_* nb = (Notebook_*)nb1;
		View_* v = (View_*)v1;
		Window_* window = (Window_*)w1;
		auto f3__ = [&](const char* s, std::string* s2 = nullptr) {
			bool b = false;
			if(s) {
				std::string s1 = s;
				if(s1[0] == '>') {
					if(s1[1] == '>') {
						nb = Notebook_::from__(s1.substr(2));
						b = nb;
					} else {
						v = View_::from__(s1.substr(1));
						b = v;
					}
				} else
				if(find__(s1, window)) {
					if(window) {
						if(s1.empty()) {
							nb = window->nb__();
							b = true;
						} else {
							b = window->find__(s1, v, nb, box);
						}
					}
				} else
					if(main_window_)
						b = main_window_->find__(s1, v, nb, box);
				if(s2)
					*s2 = s1;
			}
			return b;
		};
		{
			va_list argv;
			va_start(argv, argc);
			for (size_t i = 0; i < argc; i++) {
				const char* s = va_arg(argv, const char*);
				if(i == 0 && s) {
					std::string s1 = s;
					if(s1 == "-直") {
						if(i < argc) {
							i++;
							bool b = f3__(va_arg(argv, const char*), &s1);
							if(!b)
								throw "“" + s1 + "”未找到（符合“名#薄名#盒名&窗名”或“>名”或“>>薄名”？）";
						}
						continue;
					}
				}
				p.push_back(s ? s : "NULL");
			}
			va_end(argv);
		}
		if(v && v->cb__(p, ret1, ret)) return;
		auto f3_2__ = [&]() {
			if(!nb && v)
				nb = (Notebook_*)v->var__("nb");
			if(nb && !window)
				window = (Window_*)nb->own_;
			if(!nb && window)
				nb = window->nb__();
			if(!nb && !window && main_window_)
				nb = main_window_->nb__();
		};
		f3_2__();
		if(nb && nb->cb__(p, ret1, ret)) return;
		if(!window) window = main_window_;
		if(window && window->cb__(p, ret1, ret)) return;

		//auto p__ = [&](size_t i) -> const std::string& {return p_or__(p, i);};
		auto ret__ = [&](const char* s, bool dunhao = false) {ret_or__(s, dunhao, ret1, ret);};

		std::string tag;
		switch(tags_.get__(p, tag)) {
		case 'y': {
			auto var__ = [&](const char *name) {
				if(!v) throw "!v";
				return v->var__(name);
			};
			switch(tag[0]) {
			case 'L': {
				GtkLabel *l = GTK_LABEL(var__("标签"));
				if(p.size() > 1) {
					gtk_label_set_markup(l, p[1].c_str());
				} else
					ret__(gtk_label_get_text(l));
				break; }
			case 'T': {
				GtkWidget *w = GTK_WIDGET(var__("标签"));
				if(p.size() > 1)
					gtk_widget_set_tooltip_markup(w, p[1].c_str());
				else
					ret__(gtk_widget_get_tooltip_markup(w));
				break; }
			case 'a': {
				bool b = true;
				if(p.size() > 1) {
					v = nullptr;
					nb = nullptr;
					window = nullptr;
					b = f3__(p[1].c_str());
					f3_2__();
				}
				if(b) {
					nb->curr__(nb->num__(v->hr__()));
					gtk_window_present(window->hr1__());
				}
				break; }
			case 's':
				ret__(std::to_string(gdk_screen_width()).c_str());
				ret__(std::to_string(gdk_screen_height()).c_str(), true);
				return;
			case 'n': {
				if(!window) throw "!w";
				window->i_nb_ =
				window->i_box_ = 0;

				const std::string& url = p[1];
				if(url.empty()) break;
				std::string name, box_name, nb_name, pos, box_pos, nb_pos;
				int w = -1, h = -1;
				bool is_priv = true;
				NotebookOpt_ nbo;
				tags_get__({
					{"-名", "n", 1},
					{"-簿名", "nn", 1},
					{"-盒名", "nb", 1},
					{"-追加", "a", 0},
					{"-前固", "l", 0},
					{"-不可关闭", "X", 0},
					{"-不激活", "F", 0},
					{"-横", "H", 0},
					{"-上", "P", 0},
					{"-下", "P", 0},
					{"-左", "P", 0},
					{"-右", "P", 0},
					{"-位", "p", 1},
					{"簿", "Pn", 0},
					{"盒", "Pb", 0},
					{"-宽", "w", 1},
					{"-高", "h", 1},
					{"-非私", "/", 0},
				}, p, 2, [&](const std::string& tag, size_t i) {
					switch(tag[0]) {
					case 'n':
						switch(tag[1]) {
						case 'n': nb_name = p[i]; break;
						case 'b': box_name = p[i]; break;
						default: name = p[i]; break;
						}
						break;
					case 'a': nbo.append_ = true; break;
					case 'l': nbo.left_ = true; break;
					case 'X': nbo.no_close_ = true; break;
					case 'F': nbo.no_focus_ = true; break;
					case 'H': nbo.hori_ = true; break;
					case 'P':
						switch(tag[1]) {
						case 'n': case 'b':
							switch(tag[1]) {
							case 'n': nb_pos = pos; break;
							case 'b': box_pos = pos; break;
							}
							pos.clear();
							break;
						default: pos = p[i]; break;
						}
						break;
					case 'w': w = std::stoi(p[i]); break;
					case 'h': h = std::stoi(p[i]); break;
					case '/': is_priv = false; break;
					}
				}, [](size_t) -> bool {return false;});
				View_* v2;
				if(!name.empty() && window->exist__(name, v2)) {

				} else
					v2 = new_view__(v ? v->hr1__() : nullptr, is_priv, &nbo, nb,
							pos, nb_pos, box_pos, name, nb_name, box_name);
				if(w != -1 || h != -1)
					gtk_widget_set_size_request (window->nb__()->scrolled__(), w, h);
				WebKitWebView *webView = v2->hr1__();
				if(url == "page1__") {
					page1__(webView);
					break;
				}
				webkit_web_view_load_uri(webView, url.c_str());
				break; }
			case 'x':
				switch(tag[1]) {
				case 't':
					/*std::vector<pub::view___ *> ls, paichu;
					get_tree__(view, nb, paichu, ls);
					for(auto v : ls) {
						close__(v);
					}*/
					break;
				case 'a':
					g_idle_add(idle_xa__, nb);
					break;
				default:
					close__(v);
					break;
				}
				break;
			}
			return; }
		case '<': throw SIZE_MAX;
		}
		switch(tags2_.get__(p, tag)) {
		case 'y': {
			switch(tag[0]) {
			case 'c': {
				bool is_app_paintable = false, is_popup = false;
				std::string name;
				tags_get__({
					{"-自绘", "a", 0},
					{"-弹出窗", "p", 0},
					{"-名", "n", 1},
				}, p, 1, [&](const std::string& tag, size_t i) {
					switch(tag[0]) {
					case 'a': is_app_paintable = true; break;
					case 'p': is_popup = true; break;
					case 'n': name = p[i]; break;
					}
				}, [](size_t) -> bool {return false;});
				if(!name.empty()) {
					if((window = window__(name))) {
						gtk_window_present(window->hr1__());
						return;
					}
				}
				window = new Window_(is_app_paintable, is_popup);
				nb = window->nb__();
				if(!name.empty()) {
					window->name__(name.c_str());
					nb->name__(name.c_str());
				}
				if(!main_window_)
					main_window_ = window;
				nb->say_init__();
				call__(nullptr, nullptr, window, {"窗初始"});
				break; }
			case 'C': View_::cookie__(webkit_web_context_get_default(), p[1]); break;
			case '_': {
				idle___* idle = new idle___();
				idle->code_ = p[1];
				idle->v_ = v;
				idle->nb_ = nb;
				idle->w_ = window;
				g_idle_add(idle__, idle);
				break; }
			case ' ': cb_ = p[1]; break;
			case 's': css_ = p[1]; break;
			case 'L':
				for(size_t i = 1; i < p.size();) {
					const std::string& s = p[i++];
					const char* log_domain = s == "NULL" ? NULL : s.c_str();
					gpointer user_data = (i < p.size() && bool__(p[i++]) ? (gpointer)1 : NULL);
					g_log_set_handler (log_domain, (GLogLevelFlags)(G_LOG_LEVEL_MASK), g_log__, user_data);
				}
				break;
			}
			return; }
		case '<': throw SIZE_MAX;
		}
		g_printerr("不支持");
	} catch(size_t i) {
		g_printerr("参数不足");
		if(i < SIZE_MAX)
			g_printerr(" (%lu)", i);
	}
	catch(std::exception& e) {g_printerr("%s", e.what());}
	catch(const char* s) {g_printerr("%s", s);}
	catch(const std::string& s) {g_printerr("%s", s.c_str());}
	g_printerr("\n");
	for(auto i : p) {
		g_printerr("“%s”\n", i.c_str());
	}
}

static std::string p1__(void* v, void* nb, void* w) {
	return  "-u:" + std::to_string((unsigned long)v) +
			"-u:" + std::to_string((unsigned long)nb) +
			"-u:" + std::to_string((unsigned long)w);
}
static void err__(int err) {
	if(err) {
		if(err > 0) quit_ = err;
		quit__();
	}
}
void call__(void* v, void* nb, void* w, ILs_ a, Ret_ ret) {
	call__(v, nb, w, cb_, true, a, ret);
}
void call__(void* v, void* nb, void* w, It_ begin, It_ end, Ret_ ret) {
	call__(v, nb, w, cb_, true, begin, end, ret);
}
void call__(void* v, void* nb, void* w, const std::string& src1, bool arg0, ILs_ a, Ret_ ret) {
	err__(l4_.eval__(cb__, p1__(v, nb, w), src1, arg0, a, ret));
}
void call__(void* v, void* nb, void* w, const std::string& src1, bool arg0, It_ begin, It_ end, Ret_ ret) {
	err__(l4_.eval__(cb__, p1__(v, nb, w), src1, arg0, begin, end, ret));
}
void callj__(void* v, void* nb, void* w, const std::string& src1, bool arg0, ILs_ a, Ret_ ret) {
	err__(l4_.evalj__(cb__, p1__(v, nb, w), src1, arg0, a, ret));
}
void ret_or__(const char* s, bool dunhao, void* ret1, Ret_ ret) {
	if(dunhao) l4_.adddunhao__(ret1);
	if(!s) return;
	l4_.add__(ret1, s);
	//if(ret) ret->push_back(s);
};

static gboolean idle__(gpointer user_data) {
	idle___* idle = (idle___*)user_data;
	call__(idle->v_, idle->nb_, idle->w_, idle->code_, false, {}, nullptr);
	delete idle;
	return G_SOURCE_REMOVE;
}

std::string webkitx_;
int quit_ = 0;

int main(int argc, char* argv[])
{
	gtk_init(&argc, &argv);
	{
		std::string err;
		int err2 = l4_.init__(argc, argv, err, &webkitx_);
		if(err2) {
			if(!err.empty())
				g_printerr("%s\n", err.c_str());
			return err2;
		}
	}
	l4_.eval__(R"(
解释下代码
	模块“应用”。
	)" + def_shi__(cb__, nullptr, p1__(nullptr, nullptr, nullptr)) + R"(
	赋予“z$.h”以
	window.z$ = function() {
		if(arguments.length == 0)
			return;
		“var f” = function(o) {
			“var p” = '';
			p += “'、'”;
			if(Array.isArray(o)) {
				for(“var i2” = 0; i2 < o.length; i2++)
					p += f(o[i2]);
			} else {
				p += “'下原样'” + o + “'上原样'”;
			}
			return(p);
		};
		“var p” = '';
		for(“var i” = 1; i < arguments.length; i++)
			p += f(arguments[i]);
		return(eval(prompt('zhscript:', “'解释下代码'” +
			arguments[0] +
		“'上代码'” + p)));
	};
	。
上代码。
)");
	if(!webkitx_.empty())
		webkitx_ += "webkitx";
	{
		int err = l4_.load2__(argv[0]);
		if(err) {
			if(err < 0) {
				return 0;
			}
			return err;
		}
		std::string src = l4_.eval__("‘参数0【顶】’");
		if(!src.empty()) {
			l4_.path__(src);
		}
	}
	if(!css_.empty()) {
		GtkCssProvider* cp = gtk_css_provider_new();
		gtk_css_provider_load_from_data(cp, css_.c_str(), css_.size(), nullptr);
		gtk_style_context_add_provider_for_screen(gdk_screen_get_default(),
				GTK_STYLE_PROVIDER(cp), GTK_STYLE_PROVIDER_PRIORITY_USER);
	}
	for(Window_* w : Window_::ls_) {
		w->show_all__();
	}
	gtk_main();

	return quit_;
}

