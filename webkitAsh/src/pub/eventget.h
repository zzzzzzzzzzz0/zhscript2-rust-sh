/*
 * eventget.h
 *
 *  Created on: 2019年2月15日
 *      Author: zzzzzzzzzzz
 */

#ifndef PUB_EVENTGET_H_
#define PUB_EVENTGET_H_

#include <string>
#include <vector>
#include <gtk/gtk.h>

namespace pub {

class event___ {
public:
	std::string code_, name_;
	gboolean b_;
};

class event_get___ {
public:
	event_get___();
	virtual ~event_get___();

	char api__(const std::vector<std::string>& p, GtkWidget *hr, void* hr2, size_t from = 1);
	virtual void jieshi__(void *hr, const std::string& code, const std::string& name,
			const std::vector<std::string>* p = nullptr, std::vector<std::string>* ret = nullptr) = 0;
};

} /* namespace pub */

#endif /* PUB_EVENTGET_H_ */
