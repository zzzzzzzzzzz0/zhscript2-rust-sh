/*
 * Chan.cpp
 *
 *  Created on: 2020年12月8日
 *      Author: zzzzzzzzzzz
 */

#include "Chan.h"
#include <glib/gstdio.h>
#include <unistd.h>

static gboolean read__(GIOChannel *gioc, GIOCondition gioco, gpointer user_data) {
	Chan_* thiz = (Chan_*)user_data;
	std::string line;
	if(thiz->read_line__(gioc, line)) {
		thiz->get__(line);
	}
	return TRUE;
}

bool Chan_::read_line__(GIOChannel *gioc, std::string& line) {
	GError *err = NULL;
	gchar *s = NULL;
	gsize len = 0;
	GIOStatus ret = g_io_channel_read_line (gioc, &s, &len, NULL, &err);
	// G_IO_STATUS_ERROR
	if(ret != G_IO_STATUS_NORMAL)
	if (err) {
		g_error ("Error reading: %s\n", err->message);
		g_error_free (err);
	}
	if(s) {
		line = s;
		g_free (s);
		return true;
	}
	return false;
}

bool Chan_::write__(const char*s, size_t len) {
	if(write(out_[1], s, len) < 0)
		return false;
	return true;
}

bool Chan_::init__() {
	if(init_)
		return true;
	init_ = true;

	if (pipe(out_) < 0 || pipe(in_) < 0)
		return false;
	init_2__(true);
	return true;
}

void Chan_::init_2__(bool watch) {
	GIOChannel *gioc = g_io_channel_unix_new(in_[0]);
	g_io_channel_set_encoding(gioc, NULL, NULL);
	g_io_channel_set_close_on_unref(gioc, TRUE);
	if(watch)
		g_io_add_watch(gioc, G_IO_IN, read__, this);
	gioc_ = gioc;
}

Chan_::Chan_() {
}

Chan_::~Chan_() {
}

