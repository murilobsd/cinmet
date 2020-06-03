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

#include <time.h>

#include <curl/curl.h>

#ifndef INMET_H
#define INMET_H

/*
 * INMET allows searching in a maximum period of 1 year, that is, the maximum
 * number of data returned does not exceed 5000. The calculation would be:
 * 		MAX_NUM_DATA = 24 * 1 * 365 = 8760
 */
#define B64_EQUALS	65
#define B64_INVALID	66
#define B64_WHITESPACE	64
#define DATE_FORMAT 	"%d/%m/%Y"
#define HTTP_AGENT	"cinmet/0.0.1"
#define MAX_FIELDS	20
#define MAX_NUM_DATA 	8760
#define MAX_STA_COD	5
#define MAX_TOKENS 	(8760 * MAX_FIELDS)

/*
 * Structure represents data from INMET automatic stations.
 */
struct auto_sta_data {
	char 		code[MAX_STA_COD]; 	/* station code A000 */
	float		dew_inst;		/* dew point */
	float		dew_max;		/* max dew point */
	float		dew_min;		/* min point */
	float		hum_inst;		/* humidity */
	float		hum_max;		/* max humidity */
	float		hum_min;		/* min humidity */
	float		precipitation;		/* precipitation */
	float		press_max;		/* pressure max */
	float		press_min;		/* min pressure */
	float		pressure;		/* pressure */
	float		radiation;		/* radiation */
	float		temp_inst;		/* temperature */
	float		temp_max;		/* max temperature */
	float		temp_min;		/* min temperature */
	float		w_dir;			/* wind direction */
	float		w_gust;			/* gust of wind */
	float		w_speed;		/* wind speed */
	struct tm 	date;			/* date + hour */
};

/* station.c */
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

/* request.c */
struct req {
	CURL 		*curl;
	CURLcode	 res;
	const char 	*url;
	char 		*body;
	size_t		 body_sz;
};

struct resp {
	long	 	 status_code;
	char 		*data;
	size_t 	 	 size;
	struct req 	*req;
};

struct req	 *req_init(const char *, char *, size_t);
void		  req_free(struct req *);
void		  http_free(struct resp *);
struct resp	 *http_get(struct req *);
struct resp	 *http_post(struct req *);

#endif /* INMET_H */
