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
#include <stdio.h>
#include <stdlib.h>

#include "inmet.h"
#include "request.h"
#include "util.h"

Stations *
get_stations(void)
{
	Stations *sts;
	Station *s;

	s = init_station();
	sts = init_stations();

	s->lon = 12.12345;
	s->lat = 54.3210;
	sts->estacao = s;

	return (sts);
}

void 
dump_stations(Stations *ss)
{
	Stations *sts;

	for (sts = ss; sts != NULL; sts = ss->prox)
		dump_station(ss->estacao);
}


void 
dump_station(Station *s)
{
	if (s == NULL)
		return;
	printf("Latitude: %f\n", s->lat);
	printf("Longitude: %f\n", s->lon);
}

void
clean_stations(Stations *ss)
{
	Stations *sts;

	if (ss == NULL)
		return;

	for (sts = ss; sts != NULL; sts = ss->prox) {
		clean_station(ss->estacao);
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
