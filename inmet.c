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

#define WHITESPACE 64
#define EQUALS     65
#define INVALID    66

static const unsigned char d[] = {
    66,66,66,66,66,66,66,66,66,66,64,66,66,66,66,66,66,66,66,66,66,66,66,66,66,
    66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,62,66,66,66,63,52,53,
    54,55,56,57,58,59,60,61,66,66,66,65,66,66,66, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
    10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,66,66,66,66,66,66,26,27,28,
    29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,66,66,
    66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,
    66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,
    66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,
    66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,
    66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,
    66,66,66,66,66,66
};

static struct field fields[3];

int
data_parse(char *in, size_t inlen, size_t *outlen)
{

	return (0);
}

int
b64_decode(char *in, size_t inlen, unsigned char *out, size_t *outlen)
{
	char *end = in + inlen;
	char iter = 0;
	uint32_t buf = 0;
	size_t len = 0;

	while (in < end) {
		printf("%c\n", *in);
		unsigned char c = d[*in++];
		printf("%c\n", c);

		switch (c) {
		case WHITESPACE:
			continue;
		case INVALID:
			printf("Char invalido\n");
			return 1;
		case EQUALS:
		      in = end;
		      continue;
		default:
		      printf("char: %c\n", c);
		      buf = buf << 6 | c;
		      iter++;
		      if (iter == 4) {
			      if ((len += 3) > *outlen) {
				      printf("Overflow\n");
				      return 1;
			      }
			      *(out++) = (buf >> 16) & 255;
			      *(out++) = (buf >> 8) & 255;
			      *(out++) = buf & 255;
			      buf = 0; iter = 0;
		      }


		}


	}

	if (iter == 3) {
		if ((len += 2) > *outlen) return 1;
		*(out++) = (buf >> 10) & 255;
		*(out++) = (buf >> 2) & 255;
	} else if (iter == 2) {
		if (++len > *outlen) return 1;
		*(out++) = (buf >> 4) & 255;
	}

	*(out++) = '\0';
	*outlen = len;

	return 0;
}


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
	int found = 0;

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
			found += 1;
		}

		if (found == 3)
			break;
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
