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

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "inmet.h"

static struct resp 	*resp_init(void);
static void		 resp_free(struct resp *);
static size_t		 http_write_cb(void *, size_t, size_t, void *);


struct resp *
http_post(struct req *rq)
{
	return (0);
}

struct resp *
http_get(struct req *rq)
{
	struct resp *rs = NULL;

	rs = resp_init();

	curl_easy_setopt(rq->curl, CURLOPT_URL, rq->url);
	curl_easy_setopt(rq->curl, CURLOPT_WRITEFUNCTION, http_write_cb);
	curl_easy_setopt(rq->curl, CURLOPT_WRITEDATA, (void *)rs);


	/* come baby */
	rq->res = curl_easy_perform(rq->curl);

/*
	TODO: Checar através de uma outra função a resposta se tem err ou nao 
	
	if (rq->res == CURLE_OK) {
		curl_easy_getinfo(rq->curl, CURLINFO_RESPONSE_CODE,
		    &rs->status_code);
	} else
		return NULL;
*/

	rs->req = rq;

	return rs;
}

static
size_t http_write_cb(void *contents, size_t size, size_t nmemb, void *userp)
{
	size_t realsize = size * nmemb;
	struct resp *rs = (struct resp *)userp;


	/* resize the response data */
	char *ptr = realloc(rs->data, rs->size + realsize + 1);
	if (ptr == NULL)
		return 0;

	rs->data = ptr;

	/* copy new "chunk" */
	memcpy(&(rs->data[rs->size]), contents, realsize);
	rs->size += realsize;
	rs->data[rs->size] = 0;

	return realsize;
}

void
http_free(struct resp *rs)
{
	if (rs == NULL) return;

	/* clean request */
	if (rs->req != NULL)
		req_free(rs->req);

	/* clean response */
	resp_free(rs);

	/* we're done with libcurl, so clean it up */
	curl_global_cleanup();
}

void
req_free(struct req *rq)
{
	if (rq != NULL) return;

	if (rq->curl != NULL)
		curl_easy_cleanup(rq->curl);

	free(rq);
}

struct req *
req_init(const char *url, char *body, size_t body_sz)
{
	struct req *rq;


	rq = (struct req *)malloc(sizeof(struct req));

	if (rq == NULL)
		return NULL;

	curl_global_init(CURL_GLOBAL_ALL);

	/* init curl */
	rq->curl = curl_easy_init();

	/* curl set verbose */
	curl_easy_setopt(rq->curl, CURLOPT_VERBOSE, 0L);

	/* curl cookie jar enable for this session */
	curl_easy_setopt(rq->curl, CURLOPT_COOKIEJAR, "-");

	if (rq->curl == NULL) {
		free(rq);
		return NULL;
	}

	rq->url = url;
	rq->body = body;
	rq->body_sz = body_sz;

	return rq;
}

static void
resp_free(struct resp *rs)
{
	if (rs == NULL) return;

	if (rs->data != NULL)
		free(rs->data);

	rs->size = 0;

	free(rs);
}

static struct resp *
resp_init(void)
{
	struct resp *rs;

	rs = (struct resp *)malloc(sizeof(struct resp));
	rs->data = (char *)malloc(1);
	rs->size = 0;

	return rs;
}
