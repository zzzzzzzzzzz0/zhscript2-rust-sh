/*
 * Box.h
 *
 *  Created on: 2020年9月5日
 *      Author: zzzzzzzzzzz
 */

#ifndef BOX_H_
#define BOX_H_

#include "Base.h"

class Box_ : public Base_ {
private:
	GtkWidget *center_ = nullptr, *left_ = nullptr, *down_ = nullptr;
	GtkBox *base1_ = nullptr, *center1_ = nullptr, *left1_ = nullptr, *down1_ = nullptr;
public:
	Box_();
	virtual ~Box_();
	static void add__(Box_* box, GtkWidget *widget);

	void center__(GtkWidget *w, bool expand = true, bool fill = true);
	void right__(GtkWidget *w, bool expand = false, bool fill = false);
	void left__(GtkWidget *w, bool expand = false, bool fill = false);
	void up__(GtkWidget *w, bool expand = false, bool fill = false);
	void down__(GtkWidget *w, bool expand = false, bool fill = false);

	GtkWidget *curr__();
};

#endif /* BOX_H_ */
