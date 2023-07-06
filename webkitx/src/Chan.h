/*
 * Chan.h
 *
 *  Created on: 2020年12月8日
 *      Author: zzzzzzzzzzz
 */

#ifndef CHAN_H_
#define CHAN_H_

#include <glib.h>
#include <string>

class Chan_ {
private:
	bool init_ = false;
	GIOChannel *gioc_ = nullptr;
public:
	Chan_();
	virtual ~Chan_();
	virtual void get__(std::string& line) {}

	int in_[2], out_[2];
	bool init__();
	void init_2__(bool watch);

	GVariant *gvar__() {return g_variant_new("(ii)", out_[0], in_[1]);}
	void gvar__(GVariant *gv) {g_variant_get(gv, "(ii)", &in_[0], &out_[1]);}

	bool write__(const char* s, size_t len);

	bool read_line__(std::string& line) {return read_line__(gioc_, line);}
	bool read_line__(GIOChannel *gioc, std::string& line);
};

#endif /* CHAN_H_ */
