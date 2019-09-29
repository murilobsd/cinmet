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
#include "request.h"
#include "util.h"

/*
 * Searching stations by federative unit.
 * Eg: "SP"
 */
size_t
search_sta_uf(const char *uf, Stations *in, Stations *out)
{
	size_t count = 0;
	
	printf("Searching stations by UF: '%s'\n", uf); 
	
	while(in != NULL) {
		if (in->estacao != NULL) {
			if (strncmp(in->estacao->uf, uf, 2) == 0) {
				insert_station(in->estacao, out);
				count++;
			}
		}
		in = in->prox;
	}
	return (count);
}

/*
 * Get list of automatic stations on INMET.
 */
Stations *
get_stations(void)
{
	Stations *sts;
	Station *s, *s1, *s2;

	s = init_station();
	s1 = init_station();
	s2 = init_station();
	sts = init_stations();

	s->lon = 12.12345;
	s->lat = 54.3210;
	strcpy(s->uf, "SP");
	s1->lon = 9.8765;
	s1->lat = 5.6789;
	strcpy(s1->uf, "SP");
	s2->lon = 10.8765;
	s2->lat = 11.6789;
	strcpy(s2->uf, "MG");
	insert_station(s, sts);
	insert_station(s1, sts);
	insert_station(s2, sts);

	return (sts);
}

void
insert_station(Station *s, Stations *ss)
{
	Stations *n_sts;
	
	n_sts = init_stations();

	if (ss == NULL) {
		warnx("stations is null");
		clean_stations(n_sts);
		return;
	}
	n_sts->estacao = s;
	n_sts->prox = ss->prox;
	ss->prox = n_sts;
}

void 
dump_stations(Stations *ss)
{
	while(ss != NULL) {
		dump_station(ss->estacao);
		ss = ss->prox;
	}
}


void 
dump_station(Station *s)
{
	if (s == NULL)
		return;
	printf("UF: %s\n", s->uf);
	printf("Latitude: %f\n", s->lat);
	printf("Longitude: %f\n", s->lon);
}

void
clean_stations(Stations *ss)
{
	if (ss == NULL)
		return;

	while(ss != NULL) {
		clean_station(ss->estacao);
		ss = ss->prox;
	}
	free(ss);
}

void
clean_station(Station *s)
{
	if (s == NULL)
		return;
	free(s);
}

Stations *
init_stations(void)
{
	Stations *ss;

	ss = xmalloc(sizeof(Stations));
	ss->estacao = NULL;
	ss->prox = NULL;

	return (ss);
}

Station *
init_station(void)
{
	Station *sta;
	
	sta = xmalloc(sizeof(Station));

	return (sta);
}
