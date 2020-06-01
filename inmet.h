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

#ifndef INMET_H
#define INMET_H

#include <time.h>

/*
 * INMET allows searching in a maximum period of 1 year, that is, the maximum
 * number of data returned does not exceed 5000. The calculation would be:
 * 		MAX_NUM_DATA = 24 * 1 * 365 = 8760
 */
#define B64_EQUALS	65
#define B64_INVALID	66
#define B64_WHITESPACE	64
#define DATE_FORMAT 	"%d/%m/%Y"
#define MAX_FIELDS	20
#define MAX_NUM_DATA 	8760
#define MAX_STA_COD	5
#define MAX_TOKENS 	(8760 * MAX_FIELDS)

/*
 * Structure represents data from INMET automatic stations.
 */
struct sta_data {
	char 		code[MAX_STA_COD]; 	/* station code A000 */
	struct tm 	data;			/* date + hour */
	float		temp_inst;		/* temperature */
	float		temp_max;		/* max temperature */
	float		temp_min;		/* min temperature */
	float		umid_inst;		/* humidity */
	float		umid_max;		/* max humidity */
	float		umid_min;		/* min humidity */
	float		pto_orvalho_inst;	/* dew point */
	float		pto_orvalho_max;	/* max dew point */
	float		pto_orvalho_min;	/* min point */
	float		pressao;		/* pressure */
	float		pressao_max;		/* pressure max */
	float		pressao_min;		/* min pressure */
	float		vento_vel;		/* wind speed */
	float		vento_direcao;		/* wind direction */
	float		vento_rajada;		/* gust of wind */
	float		radiacao;		/* radiation */
	float		precipitacao;		/* precipitation */
};

struct field {
	char 	*name;
	char	*value;
};
struct field 	*html_parse_form(char *, size_t, size_t *);

struct html {
	char 	*content;
	size_t 	size;
};

struct html	 html_open_file(const char *);
void		 html_free(struct html *);
int		 data_parse(char *, size_t, size_t *);

/* b64.c */
int		 b64_decode(char *, size_t, unsigned char *, size_t *);
int		 b64_encode(const void *, size_t, char *, size_t);

#endif /* INMET_H */
