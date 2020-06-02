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

#include "inmet.h"

static struct resp 	*resp_init(void);
static void		 resp_free(struct resp *);

struct resp *
http_post(struct req *rq)
{
	return (0);
}

struct resp *
http_get(struct req *rq)
{

	return (0);
}

void
http_free(struct resp *rs)
{
	if (rs == NULL) return;

	if (rs->req != NULL)
		req_free(rs->req);

	resp_free(rs);
}

void
req_free(struct req *rq)
{
	if (rq != NULL) return;

	if (rq->curl != NULL)
		curl_easy_cleanup(rq->curl);

	if (rq->url != NULL)
		free(rq->url);

	free(rq);
}

struct req *
req_init(const char *url, char *body, size_t body_sz)
{
	struct req *rq;

	rq = (struct req *)malloc(sizeof(struct req));
	if (rq == NULL)
		return NULL;

	rq->curl = curl_easy_init();
	if (rq->curl == NULL) {
		free(rq);
		return NULL;
	}

	rq->url = strdup(url);
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
	struct resp *r;

	r = (struct resp *)malloc(sizeof(struct resp));
	r->data = (char *)malloc(1);
	r->size = 0;

	return r;
}
