/*
 * main.cpp
 *
 *  Created on: 2020年12月8日
 *      Author: zzzzzzzzzzz
 */

#include <webkit2/webkit-web-extension.h>

#include "Chan.h"
static Chan_ chan_;

static gboolean cb_send_request__(WebKitWebPage *wp, WebKitURIRequest *r, WebKitURIResponse *rr, gpointer unused) {
	const char* uri = webkit_uri_request_get_uri(r);
	if(uri[0] == 'h'
	&& uri[1] == 't'
	&& uri[2] == 't'
	&& uri[3] == 'p') {
		std::string s;
		s = "cb_send_request__";
		s += "“";
		s += uri;
		s += "”、";
		SoupMessageHeaders *h = webkit_uri_request_get_http_headers (r);
		const char *t = soup_message_headers_get_content_type (h, NULL);
		if(t) {
			s += "“";
			s += t;
			s += "”";
		}
		s += "\n";
		if(chan_.write__(s.c_str(), s.size())) {
			if(chan_.read_line__(s)) {
				s = s.substr(0, s.size() - 1);
				//printf("%s %s\n", uri, s.c_str());
				if(s == "x")
					return TRUE;
				if(s.empty() || s == "y") {} else
					webkit_uri_request_set_uri (r, s.c_str());
			}
		}
	}
	return FALSE;
}

static void cb_page_created__(WebKitWebExtension *e, WebKitWebPage *wp, gpointer unused) {
	g_signal_connect_object (wp, "send-request", G_CALLBACK (cb_send_request__), NULL, (GConnectFlags)0);
}

extern "C" G_MODULE_EXPORT void
webkit_web_extension_initialize_with_user_data(WebKitWebExtension *e, GVariant *gv) {
	g_signal_connect(e, "page-created", G_CALLBACK(cb_page_created__), NULL);

	chan_.gvar__(gv);
	chan_.init_2__(false);
}

