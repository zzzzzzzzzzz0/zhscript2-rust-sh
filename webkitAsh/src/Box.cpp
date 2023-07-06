/*
 * Box.cpp
 *
 *  Created on: 2020年9月5日
 *      Author: zzzzzzzzzzz
 */

#include "Box.h"

void Box_::center__(GtkWidget *w, bool expand, bool fill) {
	gtk_box_pack_start(center1_, w, expand, fill, 0);
}
void Box_::right__(GtkWidget *w, bool expand, bool fill) {
	gtk_box_pack_end (center1_, w, expand, fill, 0);
}
void Box_::left__(GtkWidget *w, bool expand, bool fill) {
	gtk_box_pack_start (left1_, w, expand, fill, 0);
}
void Box_::up__(GtkWidget *w, bool expand, bool fill) {
	gtk_box_pack_start (base1_, w, expand, fill, 0);
}
void Box_::down__(GtkWidget *w, bool expand, bool fill) {
	gtk_box_pack_start (down1_, w, expand, fill, 0);
}

GtkWidget *Box_::curr__() {
	GtkWidget *ret = nullptr;
	GList* ls = gtk_container_get_children(GTK_CONTAINER (center_));
	while ((ls = g_list_next(ls)) != nullptr) {
		GtkWidget *w = GTK_WIDGET(ls->data);
		if(!ret)
			ret = w;
	}
	g_list_free(ls);
	return ret;
}

void Box_::add__(Box_* box, GtkWidget *widget) {
	gtk_container_add (GTK_CONTAINER (widget), box->hr_);
}
Box_::Box_() {
	hr_ = gtk_box_new(GTK_ORIENTATION_VERTICAL,0);
	base1_ = GTK_BOX(hr_);

	down_ = gtk_box_new(GTK_ORIENTATION_VERTICAL,0);
	down1_ = GTK_BOX(down_);
	gtk_box_pack_end (base1_, down_, false, false, 0);

	center_ = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,0);
	center1_ = GTK_BOX(center_);
	gtk_box_pack_end(base1_, center_, true, true, 0);

	left_ = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,0);
	left1_ = GTK_BOX(left_);
	gtk_box_pack_start (center1_, left_, false, false, 0);
}

Box_::~Box_() {
}

