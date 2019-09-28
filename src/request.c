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

#include "request.h"
#include "xmalloc.h"

size_t 
wfunc(void *ptr, size_t size, size_t nmemb, void *stream) {
    if (stream) {
        Response *response = (Response *)stream;
        size_t new_len = response->len + size * nmemb;
        response->body = xrealloc(response->body, new_len + 1);
        memcpy(response->body + response->len, ptr, size * nmemb);
        response->body[new_len] = '\0';
        response->len = new_len;
        return size * nmemb;
    }
    return 0;
}

void 
init_resp(Response *response) {
    response->len = 0;
    response->body = xmalloc(response->len+1);
    response->body[0] = '\0';
}
