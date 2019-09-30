/*
 * Copyright (c) 2019 Murilo Ijanc' <mbsd@m0x.ru>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */
#include <curl/curl.h>

#include <string.h>

#include "inmet.h"

static size_t 		wfunc(void *, size_t , size_t , void *);
static void 		init_resp(Response *);

static size_t 
wfunc(void *ptr, size_t size, size_t nmemb, void *stream) {
    	if (stream) {
        	Response *response = (Response *)stream;
        	size_t new_len = response->len + size * nmemb;
        	response->content = xrealloc(response->content, new_len + 1);
        	memcpy(response->content + response->len, ptr, size * nmemb);
        	response->content[new_len] = '\0';
        	response->len = new_len;
        	return size * nmemb;
    	}
    	return 0;
}

static void 
init_resp(Response *response) {
    	response->len = 0;
	response->code = 0;
    	response->content = xmalloc(response->len+1);
    	response->content[0] = '\0';
}

Response 
request(char *url, char *method) {
	Response 		resp;
	CURL 			*curl = NULL;
	struct curl_slist 	*headers = NULL;

	curl_global_init(CURL_GLOBAL_ALL);
	curl = curl_easy_init();
	init_resp(&resp);

	if (curl) {
		curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, method);
		headers = curl_slist_append(headers, USER_AGENT);
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
		curl_easy_setopt(curl, CURLOPT_URL, url);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, wfunc);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &resp);
		printf("Requesting: %s\n", url);
		curl_easy_perform(curl);
		curl_easy_cleanup(curl);
		curl_slist_free_all(headers);
		curl_global_cleanup();
    	}

	return (resp);
}
