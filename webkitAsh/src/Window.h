/*
 * Window.h
 *
 *  Created on: 2020年9月6日
 *      Author: zzzzzzzzzzz
 */

#ifndef WINDOW_H_
#define WINDOW_H_

#include "Notebook.h"
#include "Box.h"

class Window_ : public Base_ {
private:
	GtkWindow* hr1_ = nullptr;
	bool no_show_all_ = true;

	std::vector<Notebook_*> nb_;
	std::vector<Box_*> box_;
	Notebook_* new_nb__();
	Box_* new_box__();
	int find__(const std::string& name, Notebook_*& nb);
	bool find__(const std::string& name, Box_*& box, Notebook_*& nb);
	bool is_fullscreen__();
public:
	Window_(bool is_app_paintable, bool is_popup);
	virtual ~Window_();

	GtkWindow* hr1__() {return hr1_;}

	size_t i_nb_ = 0, i_box_ = 0;
	Notebook_* nb__();
	Box_* box__();

	void add__(View_* v, NotebookOpt_* nbo, Notebook_* nb,
			const std::string& pos, const std::string& nb_pos, const std::string& box_pos,
			const std::string& nb_name, const std::string& box_name);
	void del__(Notebook_* nb);
	bool find__(const std::string& name, View_*& v, Notebook_*& nb, Box_*& box);
	bool exist__(const std::string& name, View_*& );

	bool cb__(Parm_ p, void* ret1, Ret_ ret);

	void show_all__() {
		gtk_widget_show_all(hr_);
		no_show_all_ = false;
	}

	static std::vector<Window_*> ls_;
};

#endif /* WINDOW_H_ */
