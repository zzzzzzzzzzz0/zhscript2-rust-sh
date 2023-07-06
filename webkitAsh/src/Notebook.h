/*
 * Notebook.h
 *
 *  Created on: 2020年8月28日
 *      Author: zzzzzzzzzzz
 */

#ifndef NOTEBOOK_H_
#define NOTEBOOK_H_

#include "View.h"

class NotebookOpt_ {
public:
	bool append_ = false, no_close_ = false, no_focus_ = false, left_ = false, hori_ = false;
};

class Notebook_ : public Base_ {
private:
	GtkWidget *scrolled_ = nullptr;
	GtkNotebook* hr1_ = nullptr;
public:
	Notebook_(void* own);
	virtual ~Notebook_();
	void* own_ = nullptr;

	void say_init__();

	GtkNotebook* hr1__() {return hr1_;}
	GtkWidget *scrolled__() {return scrolled_;}

	void add__(View_* v, NotebookOpt_* nbo);
	bool cb__(Parm_ p, void* ret1, Ret_ ret);

	int curr__() {return gtk_notebook_get_current_page (hr1_);}
	void curr__(int i) {gtk_notebook_set_current_page (hr1_, i);}
	int num__(GtkWidget *w) {return gtk_notebook_page_num(hr1_, w);}
	GtkWidget* nth__(int i) {return gtk_notebook_get_nth_page(hr1_, i);}
	int len__() {return gtk_notebook_get_n_pages(hr1_);}

	void rm__(GtkWidget *w) {gtk_notebook_remove_page(hr1_, num__(w));}

	static Notebook_* from__(GtkWidget *w);
	static Notebook_* from__(const std::string&);
};

#endif /* NOTEBOOK_H_ */
