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
#include <stdint.h>

#include "inmet.h"

int
data_parse(char *in, size_t inlen, size_t *outlen)
{
	char *p;
	char *tokens[MAX_TOKENS];
	char *last;
	int i = 0;
	size_t x;

	/* split br */
	for ((p = strtok_r(in, "<br>", &last)); p;
	    (p = strtok_r(NULL, "<br>", &last))) {
		if (i < MAX_TOKENS - 1)
			tokens[i++] = p;
	}

	tokens[i] = NULL;
	//printf("Sizeof token: %lu", sizeof(tokens));
	for (x = 12; x < i; x++) {
		printf("%s\n", tokens[x]);
		char *field = strtok(tokens[x], ",");
		int count = 1;
		while (field) {
			if (count == 2) {
				/* campo date */
				struct tm tm;
				if (dttotm((const char *)field, &tm) == 0)
					printf("Dia: %d Mês: %d Ano: %d\n", 
					    tm.tm_mday, (tm.tm_mon+1), 
					    (1900 +tm.tm_year));
			} else if (count > 3) {
				/* campos das variaveis meteorologicas */
				float res = strtof(field, (char **)NULL);
				printf("Campo %d: %s (original)\n", count, field);
				printf("Campo %d: %.2f (convertido)\n", count, res);
			} else 
				printf("Campo %d: %s\n", count, field);
			field = strtok(NULL, ",");
			count +=1;
		}

	}
	return (0);
}

/* 
 * This function obtains the form fields that will be sent to INMET to obtain 
 * the meteorological data from the automatic station.
 */
char *
staa_parse_form_data(const char *html, size_t hsize, size_t *out_len)
{
	const int max_fields = 3;

	int is_enter = 0;
	int count = 0;
	int found = 0;
	size_t i;

	//char *form_fields = "aleaValue=%s&xaleaValue=%s&xID=%s&aleaNum=%s";
	char captcha[10];
	size_t captchasize = 10;
	char *f_field = (char *)malloc(200);
	*out_len = strlen(f_field) + 1;

	memset(f_field, 0, 200);

	while (html != NULL && *html != '\0') {
		if (*html == 'v' && *++html == 'a' && is_enter == 0) {
			is_enter = 1;
			count = 2;
		}
		if (is_enter == 1)
			count +=1;
		if (count == 9) {
			int token_end = 1;
			char value[80];
			int pos = 0;

			while (token_end == 1) {
				if (*html != '"') {
					value[pos] = *html;
					pos++;
					++html;
				} else {
					value[pos] = '\0';
					if (found == 0) {
						strcat(f_field, "aleaValue=");
						strcat(f_field, value);
						strcat(f_field, "&");
						b64_decode(value, strlen(value), captcha, &captchasize);
						if (captchasize > 0) {
							strcat(f_field, "aleaNum=");
							strcat(f_field, captcha);
							strcat(f_field, "&");
						}
						token_end = 0;
							
					} else if (found == 1) {
						strcat(f_field, "xaleaValue=");
						strcat(f_field, value);
						strcat(f_field, "&");
						token_end = 0;
					} else if (found == 2) {
						strcat(f_field, "xID=");
						strcat(f_field, value);
						token_end = 0;
					}
					found += 1;
				}
			}
			is_enter = 0;
			count = 0;
		}
		if (found == 3)
			break;
		++html;
	}

	return f_field;
}

struct html
html_open_file(const char *filename)
{
	FILE *fp = NULL;
	size_t size;
	struct html h = {.size = 0, .content = NULL};

	size = 0;

	if (filename == NULL)
		goto err;

	if ((fp = fopen(filename, "rb")) == NULL)
		goto err;

	if (fseek(fp, 0, SEEK_END) != 0)
		goto err;

	size = ftell(fp);

	if (fseek(fp, 0, SEEK_SET) != 0)
		goto err;

	if (size <= 0)
		goto err;

	h.size = size;
	h.content = (char *)malloc(size + 1);

	if (h.content == NULL)
		goto err;

	size_t nread = fread(h.content, 1, size, fp);

	if (nread != size)
		goto err;

	fclose(fp);
	return h;

err:
	if (fp != NULL) fclose(fp);
	if (h.content != NULL) free(h.content);
	return h;
}

void
html_free(struct html *h)
{
	if (h == NULL) return;

	if (h->content != NULL)
		free(h->content);
}
