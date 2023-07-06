/*
 * Notebook.cpp
 *
 *  Created on: 2020年8月28日
 *      Author: zzzzzzzzzzz
 */

#include "Notebook.h"
#include "ext.h"

static void cb_clicked__(GtkButton *button, View_* v) {
	VS_ ret;
	call__(v, nullptr, nullptr, {"钮关闭"}, &ret);
	if(ret.size() == 1 && ret[0] == "x")
		return;
	close__(v);
}

void Notebook_::add__(View_* v, NotebookOpt_* nbo) {
	v->var__("nb", this);
	GtkWidget* webView = v->hr__();

	GtkOrientation ori1 = GTK_ORIENTATION_VERTICAL, ori2 = GTK_ORIENTATION_HORIZONTAL;
	if(nbo && nbo->hori_)
		ori1 = GTK_ORIENTATION_HORIZONTAL;
	GtkWidget *box = gtk_box_new(ori1, 0);
	/*{
		GtkStyleContext *sc = gtk_widget_get_style_context(box);
		gtk_style_context_add_class(sc, "red-background");
	}*/
	GtkBox* box1 = GTK_BOX(box);
	auto f1 = [&]() {
		GtkWidget *box2 = gtk_box_new(ori2, 0);
		GtkBox* box21 = GTK_BOX(box2);
		{
			GtkWidget *box3;
			box3 = gtk_box_new(ori2, 0);
			gtk_box_pack_start (box21, box3, false, false, 0);
			v->var__("钮盒3", box3);
			box3 = gtk_box_new(ori2, 0);
			gtk_box_pack_start (box21, box3, true, false, 0);
			v->var__("钮盒", box3);
			box3 = gtk_box_new(ori2, 0);
			gtk_box_pack_start (box21, box3, false, false, 0);
			v->var__("钮盒2", box3);
		}
		if(!nbo || !nbo->no_close_)
			g_signal_connect(v->add_btn__(nullptr, "gtk-close", GTK_ICON_SIZE_MENU, box21),
				"clicked", G_CALLBACK(cb_clicked__), v);
		gtk_box_pack_start (box1, box2, false, false, 0);
	};
	auto f2 = [&]() {
		GtkWidget* label = gtk_label_new (nullptr);
		gtk_box_pack_start (box1, label, true, true, 0);
		v->var__("标签", label);
	};
	if(nbo && nbo->hori_) {
		f2();
		gtk_box_pack_start (box1, gtk_label_new ("  "), false, false, 0);
		f1();
	} else {
		f1();
		f2();
	}
	do {
		if(nbo && nbo->left_) {
			gtk_notebook_insert_page (hr1__(), webView, box, 0);
			break;
		}
		if(!nbo || !nbo->append_) {
			int page_num = curr__();
			if(page_num >= 0) {
				v->var__("从", nth__(page_num));
				page_num++;
				gtk_notebook_insert_page (hr1__(), webView, box, page_num);
				break;
			}
		}
		gtk_notebook_append_page (hr1__(), webView, box);
	} while(false);
	gtk_notebook_set_tab_reorderable (hr1__(), webView, true);

	v->say_init__();
	gtk_widget_show_all (box);
	gtk_widget_show (webView);

	if(!nbo || !nbo->no_focus_) {
		curr__(num__(webView));
		gtk_widget_grab_focus(webView);
	}
}

static pub::tags___ tags_ = {
		{"簿名", "n", 0},
		{"顶标签页", "t", 0},
		{"底标签页", "b", 0},
		{"左标签页", "l", 0},
		{"右标签页", "r", 0},
		{"无标签", "N0", 0},
		{"不计", "N1", 0},
		{"可空", "N2", 0},
};
bool Notebook_::cb__(Parm_ p, void* ret1, Ret_ ret) {
	std::string tag;
	switch(tags_.get__(p, tag)) {
	case 'y': {
		auto ret__ = [&](const char* s, bool dunhao = false) {ret_or__(s, dunhao, ret1, ret);};

		GtkNotebook* nb = hr1__();
		switch(tag[0]) {
		case 'n':
			ret__(name__());
			break;
		case 'l': gtk_notebook_set_tab_pos (nb, GTK_POS_LEFT); break;
		case 'r': gtk_notebook_set_tab_pos (nb, GTK_POS_RIGHT); break;
		case 'b': gtk_notebook_set_tab_pos (nb, GTK_POS_BOTTOM); break;
		case 't': gtk_notebook_set_tab_pos (nb, GTK_POS_TOP); break;
		case 'N':
			switch(tag[1]) {
			case '0': {
				bool b = !(p.size() == 2 && p[1] == "*" ? gtk_notebook_get_show_tabs (nb) : bool__(p, 1, true));
				gtk_notebook_set_show_tabs (nb, b);
				gtk_notebook_set_show_border (nb, b);
				break; }
			default: var__(p[0].c_str(), (void*)1); break;
			}
			break;
		}
		return true; }
	case '<': throw SIZE_MAX;
	}
	return false;
}

Notebook_* Notebook_::from__(GtkWidget *w) {
	return (Notebook_*)Base_::var__(w, "nb");
}

static void switch_page__(GtkNotebook *notebook, GtkWidget *page, guint page_num, Notebook_* nb) {
	View_* v = View_::from__(page);
	call__(v, nb, nullptr, {"切换"});
}

static std::vector<Notebook_*> ls_;

Notebook_* Notebook_::from__(const std::string& name) {
	for(Notebook_* i2 : ls_) {
		if(i2->name__() == name) {
			return i2;
		}
	}
	return nullptr;
}

Notebook_::Notebook_(void* own) {
	own_ = own;

	hr_ = gtk_notebook_new ();
	hr1_ = GTK_NOTEBOOK(hr_);
	gtk_notebook_set_scrollable (hr1_, true);
	gtk_notebook_popup_enable (hr1_);

	g_signal_connect(hr1_, "switch-page", G_CALLBACK(switch_page__), this);

	scrolled_ = gtk_scrolled_window_new (NULL, NULL);
	Base_::var__(scrolled_, "nb", this);
	gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolled_), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
	GtkWidget* viewport = gtk_viewport_new (NULL,NULL);
	gtk_container_add (GTK_CONTAINER(scrolled_), viewport);
	gtk_container_add (GTK_CONTAINER (viewport), hr_);

	ls_.push_back(this);
}
void Notebook_::say_init__() {
	call__(nullptr, this, nullptr, {"簿初始"});
}

Notebook_::~Notebook_() {
	ls_.erase(std::find(ls_.begin(), ls_.end(), this));
	for(int i = 0; i < len__(); i++) {
		delete View_::from__(nth__(i));
	}
}

