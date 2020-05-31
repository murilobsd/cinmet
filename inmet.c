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

static struct field fields[3];

struct field *
html_parse_form(char *content, size_t size, size_t *numFields)
{
	/*const int	maxFields = 3;*/
	const char 	*field1 = "aleaValue";
	*numFields = 3;
	//char *field1Value;

	printf("Field1: %s\n", field1);

	int is_enter = 0;
	int count = 0;

	//field1Value = strchr(content, 'v');
	for (size_t i = 0; i < size; i++) {
		if (i + 1 < size && is_enter == 0)
			if (content[i] == 'v' && content[i+1] == 'a') {
				printf("Acho que encontrei\n");
				is_enter = 1;
				count = 1;
			}
		if (is_enter == 1) {
			count += 1;
		}

		if (count == 9) {
			int para = 0;
			int num = 0;
			char value[80];
			while (para == 0) {
				if (content[i] != '"')
					value[num] = content[i];
				else {
					value[num++] = '\0';
					para = 1;
				}
				num++;
				i++;
			}
			//printf("%c\n", content[i]);
			printf("value: %s\n", value);
			count = 0;
			is_enter = 0;
		}
	}

	return NULL;
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
