/*
 * eventget.cpp
 *
 *  Created on: 2019年2月15日
 *      Author: zzzzzzzzzzz
 */

#include "eventget.h"

namespace pub {

class data___ {
public:
	event___* e_;
	event_get___* g_;
	void *hr_;
	gboolean jieshi__(const std::vector<std::string>* p = nullptr, std::vector<std::string>* ret = nullptr) {
		g_->jieshi__(hr_, e_->code_, e_->name_, p, ret);
		return e_->b_;
	}
};

static gboolean event_mouse__(GtkWidget *widget, GdkEventButton *event, data___* data) {
	std::vector<std::string> p;
	p.push_back(std::to_string(event->button));
	p.push_back(std::to_string(event->x));
	p.push_back(std::to_string(event->y));
	return data->jieshi__(&p);
}
static gboolean event_key__(GtkWidget *widget, GdkEventKey *event, data___* data) {
	event___* e = data->e_;
	std::string state;
	if((event->state & GDK_SUPER_MASK))
		state += "Super";
	if((event->state & GDK_SHIFT_MASK))
		state += "Shift";
	if((event->state & GDK_CONTROL_MASK))
		state += "Control";
	if((event->state & GDK_MOD1_MASK))
		state += "Alt";
	//ext_->jieshi23__(e->code_.c_str(), e->name_.c_str(), nullptr, "ss", gdk_keyval_name(event->keyval), state.c_str());
	std::vector<std::string> p, ret;
	p.push_back(gdk_keyval_name(event->keyval));
	p.push_back(state);
	data->jieshi__(&p, &ret);
	if(!e->b_ && ret.size() == 1 && ret[0] == "x") {
		return TRUE;
	}
	return e->b_;
}
static gboolean event_scroll__(GtkWidget *widget, GdkEventScroll *scroll, data___* data) {
	std::vector<std::string> p;
	p.push_back(std::to_string(scroll->direction));
	return data->jieshi__(&p);
}
static gboolean event_other__(GtkWidget *widget, GdkEvent *event, data___* data) {
	return data->jieshi__();
}


char event_get___::api__(const std::vector<std::string>& p, GtkWidget *hr, void* hr2, size_t from) {
	bool b = TRUE;
	GObject *obj = G_OBJECT(hr);
	for(size_t i2 = from; i2 < p.size();) {
		const std::string& p2 = p[i2++];
		if(p2 == "-ret0") {
			b = FALSE;
			continue;
		}
		if(p2 == "-ret1") {
			b = TRUE;
			continue;
		}
		if(i2 >= p.size()) {
			return '<';
		}
		const std::string& p3 = p[i2++];
		event___* e = new event___();
		e->code_ = p3;
		e->name_ = p2;
		e->b_ = b;
		data___* d = new data___();
		d->e_ = e;
		d->g_ = this;
		d->hr_ = hr2;
		std::string head = "key";
		if(p2.compare(0, head.size(), head) == 0) {
			g_signal_connect(obj, p2.c_str(), G_CALLBACK(event_key__), d);
			continue;
		}
		head = "button";
		if(p2.compare(0, head.size(), head) == 0 || p2 == "motion-notify-event") {
			g_signal_connect(obj, p2.c_str(), G_CALLBACK(event_mouse__), d);
			continue;
		}
		if(p2 == "scroll-event") {
			g_signal_connect(obj, p2.c_str(), G_CALLBACK(event_scroll__), d);
			continue;
		}
		if(p2 == "configure-event") {
			e->b_ = FALSE;
		}
		g_signal_connect(obj, p2.c_str(), G_CALLBACK(event_other__), d);
	}
	return 0;
}

event_get___::event_get___() {
}

event_get___::~event_get___() {
}

} /* namespace pub */
