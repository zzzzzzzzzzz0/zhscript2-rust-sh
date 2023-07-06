/*
 * Window.cpp
 *
 *  Created on: 2020年9月6日
 *      Author: zzzzzzzzzzz
 */

#include "Window.h"
#include "ext.h"
#include <algorithm>

static bool bool2__(Parm_ p, size_t i, bool curr) {
	return p.size() == i + 1 && p[i] == "*" ? curr : bool__(p, i, true);
}
static bool nbool__(Parm_ p, size_t i, bool curr) {return !bool2__(p, i, curr);}

#include "pub/eventget.h"
class event_get___ : public pub::event_get___ {
public:
	void jieshi__(void *hr, const std::string& code, const std::string& name,
				const std::vector<std::string>* p1, std::vector<std::string>* ret) {
		VS_ p;
		p.push_back(name);
		if(p1)
			for(auto s : *p1)
				p.push_back(s);
		call__(nullptr, nullptr, hr, code, true, p.begin(), p.end(), ret);
	}
};
static event_get___ event_get_;

static gboolean idle_close__(gpointer user_data) {
	gtk_widget_destroy(GTK_WIDGET(user_data));
	return G_SOURCE_REMOVE;
}

static pub::tags___ tags_ = {
		{"移动", "m", 0},
		{"标题", "t", 0},
		{"图标", "i", 1},
		{"隐藏", "h", 0},
		{"是隐藏", "h?", 0},
		{"居中", "c", 0},
		{"最大化", "A1", 0},
		{"撤最大化", "A", 0},
		{"最小化", "I1", 0},
		{"撤最小化", "I", 0},
		{"窗名", "n", 0},
		{"宽高", "s", 0},
		{"预宽高", "sd", 0},
		{"定宽高", "sr", 0},
		{"置顶", "T1", 0},
		{"撤置顶", "T", 0},
		{"置底", "B1", 0},
		{"撤置底", "B", 0},
		{"总可见", "D1", 0},
		{"撤总可见", "D", 0},
		{"全屏", "F1", 0},
		{"撤全屏", "F", 0},
		{"是全屏", "F?", 0},
		{"不在任务栏", "!t", 0},
		{"鼠标穿透", "!m", 0},
		{"无修饰", "!d", 0},
		{"类名", "C", 1},
		{"窗事件", "e", 0},
		{"关闭", "x", 0},
};
bool Window_::cb__(Parm_ p, void* ret1, Ret_ ret) {
	std::string tag;
	switch(tags_.get__(p, tag)) {
	case 'y': {
		auto ret__ = [&](const char* s, bool dunhao = false) {ret_or__(s, dunhao, ret1, ret);};

		switch(tag[0]) {
		case 'm': {
			int x, y;
			gtk_window_get_position(hr1__(), &x, &y);
			if(p.size() > 1) {
				int x2 = std::stoi(p[1]);
				int y2 = p.size() > 2 ? std::stoi(p[2]) : x2;
				if(x2 < 0) {
					if(x2 < -1000000) x2 += 1000000;
					x2 += x;
				}
				if(y2 < 0) {
					if(y2 < -1000000) y2 += 1000000;
					y2 += y;
				}
				gtk_window_move(hr1__(), x2, y2);
			} else {
				ret__(std::to_string(x).c_str());
				ret__(std::to_string(y).c_str(), true);
			}
			break; }
		case 't':
			if(p.size() > 1) {
				gtk_window_set_title(hr1__(), p[1].c_str());
			} else
				ret__(gtk_window_get_title(hr1__()));
			break;
		case 'i': {
			const std::string& name = p[1];
			GdkPixbuf* pb;
			if(p.size() > 2)
				pb = gtk_icon_theme_load_icon(gtk_icon_theme_get_default(), name.c_str(), std::atoi(p[2].c_str()),
						GTK_ICON_LOOKUP_USE_BUILTIN, nullptr);
			else
				pb = gdk_pixbuf_new_from_file(name.c_str(), nullptr);
			gtk_window_set_icon_name(hr1__(), name.c_str());
			gtk_window_set_icon(hr1__(), pb);
			break; }
		case 'h':
			if(tag[1]) {
				if(no_show_all_)
					ret__("1");
			} else {
				bool b = bool__(p, 1, true);
				no_show_all_ = b;
				if(b) gtk_widget_hide(hr__());
				else  show_all__();
			}
			break;
		case 'c': gtk_window_set_position(hr1__(), GTK_WIN_POS_CENTER); break;
		case 'A':
			if(tag[1]) gtk_window_maximize (hr1__());
			else     gtk_window_unmaximize (hr1__());
			break;
		case 'I':
			if(tag[1]) gtk_window_iconify (hr1__());
			else     gtk_window_deiconify (hr1__());
			break;
		case 'n':
			ret__(name__());
			break;
		case 's':
			if(p.size() > 1) {
				int w = std::stoi(p[1]);
				int h = p.size() > 2 ? std::stoi(p[2]) : w;
				if(w < 0)
					w += gdk_screen_width();
				if(h < 0)
					h += gdk_screen_height();
				switch(tag[1]) {
				default:
					gtk_window_resize(hr1__(), w, h);
					break;
				case 'd':
					gtk_window_set_default_size (hr1__(), w, h);
					break;
				case 'r':
					gtk_widget_set_size_request (hr_, w, h);
					break;
				}
			} else {
				gint w, h;
				gtk_window_get_size (hr1__(), &w, &h);
				ret__(std::to_string(w).c_str());
				ret__(std::to_string(h).c_str(), true);
			}
			break;
		case 'T': gtk_window_set_keep_above (hr1__(), tag[1]); break;
		case 'B': gtk_window_set_keep_below (hr1__(), tag[1]); break;
		case 'D':
			if(tag[1]) gtk_window_stick(hr1__());
			else     gtk_window_unstick(hr1__());
			break;
		case 'F':
			switch(tag[1]) {
			case '?': if(is_fullscreen__()) ret__("1"); break;
			case '1':  gtk_window_fullscreen(hr1__()); break;
			default: gtk_window_unfullscreen(hr1__()); break;
			}
			break;
		case '!':
			switch(tag[1]) {
			case 't':
				gtk_window_set_skip_taskbar_hint(hr1__(),
						bool2__(p, 1, !gtk_window_get_skip_taskbar_hint(hr1__())));
				break;
			case 'd':
				gtk_window_set_decorated(hr1__(),
						nbool__(p, 1, gtk_window_get_decorated(hr1__())));
				break;
			case 'm': chuantou__(hr__()); break;
			}
			break;
		case 'C': {
			const std::string& cn = p[1];
			const std::string& cc = p[p.size() > 2 ? 2 : 1];
			gtk_window_set_wmclass(hr1__(),
					cn == "NULL" ? NULL : cn.c_str(),
					cc == "NULL" ? NULL : cc.c_str());
			break; }
		case 'e':
			switch(event_get_.api__(p, hr__(), this)) {
			case '<': throw SIZE_MAX;
			}
			break;
		case 'x':
			g_idle_add(idle_close__, hr__());
			break;
		}
		return true; }
	case '<': throw SIZE_MAX;
	}
	return false;
}

bool Window_::is_fullscreen__() {
	gint w, h;
	gtk_window_get_size (hr1__(), &w, &h);
	return w >= gdk_screen_width() && h >= gdk_screen_height();
}

void Window_::del__(Notebook_* nb) {
	nb_.erase(std::find(nb_.begin(), nb_.end(), nb));
	delete nb;
	bool destroy = true;
	for(Notebook_* nb : nb_) {
		if(!nb->var__("不计")) {
			destroy = false;
			break;
		}
	}
	if(destroy)
		gtk_widget_destroy(hr_);
}

bool Window_::exist__(const std::string& name, View_*& v) {
	for(Notebook_* nb : nb_) {
		for(int i = 0; i < nb->len__(); i++) {
			GtkWidget* w = nb->nth__(i);
			if(name == View_::name__(w)) {
				nb->curr__(i);
				v = View_::from__(w);
				return true;
			}
		}
	}
	return false;
}

int Window_::find__(const std::string& name, Notebook_*& nb) {
	char c = name[0];
	if(c >= '0' && c <= '9') {
		size_t i = std::stoi(name);
		if(i < nb_.size()) {
			nb = nb_[i];
			return -1;
		} else
			return 0;
	}
	for(Notebook_* nb1 : nb_) {
		if(name == nb1->name__()) {
			nb = nb1;
			return 1;
		}
	}
	return 0;
}
bool Window_::find__(const std::string& name, Box_*& box, Notebook_*& nb) {
	for(Box_* box1 : box_) {
		if(name == box1->name__()) {
			box = box1;
			nb = nullptr;
			GtkWidget *w = box->curr__();
			if(w) {
				nb = Notebook_::from__(w);
			}
			return true;
		}
	}
	return false;
}
bool Window_::find__(const std::string& s, View_*& v, Notebook_*& nb, Box_*& box) {
	std::string name, nb_name, box_name;
	{
		int i = 0;
		repl__(s, "#", [&](const std::string& s) {
			switch(i++) {
			case 0: name = s; break;
			case 1: nb_name = s; break;
			case 2: box_name = s; break;
			}
		}, []{});
	}

	v = nullptr;
	nb = nullptr;
	box = nullptr;

	if(!box_name.empty() && !find__(box_name, box, nb))
		return false;

	auto f__ = [&](Notebook_* nb) -> View_* {
		for(int i = 0; i < nb->len__(); i++) {
			GtkWidget* w = nb->nth__(i);
			if((name.empty() && i == nb->curr__()) || name == View_::name__(w)) {
				return View_::from__(w);
			}
		}
		return nullptr;
	};
	if(!nb_name.empty()) {
		switch(find__(nb_name, nb)) {
		//case -1: return true;
		case 0: return false;
		}
		if((v = f__(nb)))
			return true;
	} else {
		for(Notebook_* nb1 : nb_) {
			if((v = f__(nb1))) {
				nb = nb1;
				return true;
			}
		}
	}
	if(nb || box)
		return true;
	return false;
}

static void pos__(const std::string& pos, Box_* box, GtkWidget *w) {
	if(pos == "-上") {
		box->up__(w);
	} else if(pos == "-左") {
		box->left__(w);
	} else if(pos == "-下") {
		box->down__(w);
	} else if(pos == "-右") {
		box->right__(w);
	} else {
		box->center__(w);
	}
}
void Window_::add__(View_* v, NotebookOpt_* nbo, Notebook_* nb,
		const std::string& pos, const std::string& nb_pos, const std::string& box_pos,
		const std::string& nb_name, const std::string& box_name) {
	Box_* box = box__();
	bool can_new_nb = true, can_new_box = true;
	auto new_nb = [&]() {
		if(can_new_nb)
			can_new_nb = false;
		else
			return;
		nb = new_nb__();
		if(!nb_name.empty())
			nb->name__(nb_name.c_str());
		nb->say_init__();
		pos__(nb_pos, box, nb->scrolled__());
	};
	auto new_box = [&]() {
		if(can_new_box)
			can_new_box = false;
		else
			return;
		Box_* box1 = box;
		box = new_box__();
		if(!box_name.empty())
			box->name__(box_name.c_str());
		pos__(box_pos, box1, box->hr__());
	};

	if(!box_name.empty()) {
		if(!find__(box_name, box, nb)) {
			new_box();
		}
	}
	if(!nb_name.empty() && !find__(nb_name, nb))
		new_nb();
	if(!nb) nb = nb__();

	if(!box_pos.empty()) {
		new_box();
		new_nb();
	}
	else if(!nb_pos.empty()) {
		new_nb();
	}
	nb->add__(v, nbo);
}

Notebook_* Window_::nb__() {
	if(i_nb_ >= nb_.size()) {
		if(nb_.empty())
			return nullptr;
		return nb_[0];
	}
	return nb_[i_nb_];
}
Notebook_* Window_::new_nb__() {
	i_nb_ = nb_.size();
	Notebook_* nb = new Notebook_(this);
	nb_.push_back(nb);
	return nb;
}
Box_* Window_::box__() {
	if(i_box_ >= box_.size()) {
		if(box_.empty())
			return nullptr;
		return box_[0];
	}
	return box_[i_box_];
}
Box_* Window_::new_box__() {
	i_box_ = box_.size();
	Box_* box = new Box_();
	box_.push_back(box);
	return box;
}

static void destroyWindowCb(GtkWidget* widget, Window_* window)
{
	if(is_main_window__(window)) {
		quit__();
		return;
	}
	delete window;
}

std::vector<Window_*> Window_::ls_;

Window_::Window_(bool is_app_paintable, bool is_popup) {
	hr_ = gtk_window_new(is_popup ? GTK_WINDOW_POPUP : GTK_WINDOW_TOPLEVEL);
	hr1_ = GTK_WINDOW(hr_);
	g_signal_connect(hr_, "destroy", G_CALLBACK(destroyWindowCb), this);

	if(is_app_paintable) {
		gtk_widget_set_app_paintable(hr_, TRUE);
		GdkScreen *screen = gtk_widget_get_screen(hr_);
		GdkVisual *visual = gdk_screen_get_rgba_visual(screen);
		if (!visual)
			visual = gdk_screen_get_system_visual(screen);
		gtk_widget_set_visual(hr_, visual);
	}

	Box_* box = new_box__();
	Box_::add__(box, hr_);

	Notebook_* nb = new_nb__();
	box->center__(nb->scrolled__());

	ls_.push_back(this);
}

Window_::~Window_() {
	ls_.erase(std::find(ls_.begin(), ls_.end(), this));
	for(Notebook_* i : nb_) {
		delete i;
	}
	for(Box_* i : box_) {
		delete i;
	}
}

