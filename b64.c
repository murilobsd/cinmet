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

static const char b64[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
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

int
b64_encode(const void *buf, size_t buflen, char *out, size_t outlen)
{
	const uint8_t *data = (const uint8_t *)buf;
	size_t x;
	size_t resultindex = 0;
	uint32_t n = 0;
	int padcount = buflen % 3;
	uint8_t n0, n1, n2, n3;

	for (x = 0; x < buflen; x += 3) {
		n = ((uint32_t)data[x]) << 16;
		if ((x+1) < buflen)
			n += ((uint32_t)data[x+1]) << 8;
		if ((x+2) < buflen)
			n += data[x+2];

		n0 = (uint8_t)(n >> 18) & 63;
		n1 = (uint8_t)(n >> 12) & 63;
		n2 = (uint8_t)(n >> 6) & 63;
		n3 = (uint8_t)n & 63;

		if (resultindex >= outlen) return 1;
		out[resultindex++] = b64[n0];
		if (resultindex >= outlen) return 1;
		out[resultindex++] = b64[n1];

		if ((x+1) < buflen) {
			if (resultindex >= outlen) return 1;
			out[resultindex++] = b64[n2];
		}

		if ((x+2) < buflen) {
			if (resultindex >= outlen) return 1;
			out[resultindex++] = b64[n3];
		}
	}

	if (padcount > 0) {
		for (; padcount < 3; padcount++) {
			if (resultindex >= outlen) return 1;
			out[resultindex++] = '=';
		}
	}

	if (resultindex >= outlen) return 1;
	out[resultindex] = 0;
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
		//printf("%c\n", *in);
		unsigned char c = d[*in++];
		printf("%c\n", c);

		switch (c) {
		case B64_WHITESPACE:
			continue;
		case B64_INVALID:
			printf("Char invalido\n");
			return 1;
		case B64_EQUALS:
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
