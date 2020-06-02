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

#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "inmet.h"

int
main(void)
{
	struct html 	h;
	struct html 	h_data;
	const char 	*form = "./form_sta.html";
	const char 	*datafile = "./data_sta.html";
	size_t numFields = 0;
	size_t h_data_size = 0;

	const char 	*b64en = "NDcwOQ=="; // "4709"
	const char 	*b64de = "A307"; // "QTMwNw=="

	unsigned char captcha[10];
	size_t captchasize = 10;

	char staid[10];
	size_t staid_size = 9;

	h = html_open_file(form);

	if (h.size == 0)
		return(1);

	printf("%s\n", h.content);


	html_parse_form(h.content, h.size, &numFields);

	int err = b64_decode((char *)b64en, strlen(b64en), captcha, &captchasize);
	if (err != 0)
		printf("Erro decode\n");

	printf("Captcha: %s\n", captcha);

	h_data = html_open_file(datafile);

	if (h_data.size == 0) {
		html_free(&h);
		return(1);
	}

	printf("%s\n", h_data.content);

	data_parse(h_data.content, h_data.size, &h_data_size);

	err = b64_encode((const void *)b64de, strlen(b64de), staid, staid_size);
	if (err != 0)
		printf("Erro decode\n");

	printf("Station ID: %s\n", staid);

	const char *url = "http://www.inmet.gov.br/sonabra/pg_dspDadosCodigo_sim.php?QTMwNw==";
	struct req *rq = req_init(url, NULL, 0);
	struct resp *rp = NULL;

	if ((rp = http_get(rq)) == NULL)
		req_free(rq);

	printf("Status code: %lu\n", rp->status_code);

	http_free(rp);
	html_free(&h);
	html_free(&h_data);

        return (0);
}
