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
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "inmet.h"

static size_t 	extract_data(char *, const char *, char ***);
static void 	parse_stations(char *, Stations *);

/*
 * Extract longitude with content.
 */
size_t 
extract_data(char *content, const char *regex, char ***esult)
{
	int		error = 0;
	size_t 		count = 0;
	regex_t 	re;
	regmatch_t 	match[2];
	char **result	= NULL;

	result = (char **)xmalloc(579 * sizeof(char *));

        if (regcomp(&re, regex, REG_EXTENDED|REG_NEWLINE) != 0)
                err(1, "failed to compile regex '%s'", RE_LON);

	error = regexec(&re, content, 2, match, 0);

	while(error == 0) {
		/*result = (char **)realloc(result, (count + 1) * sizeof(char *));
		if (result == NULL)
			err(1, "realloc");
*/
		/*printf("casou do caracteres = %lld ao %lld\n", 
			match[1].rm_so, match[1].rm_eo);
		*/

		/*if (count < sizeof(result)) {
			realloc(**result, sizeof(char) + 1);
		}*/

		/* match case */		
		//printf("%lu\n", count);
		result[count] = xmalloc(sizeof(char *) * ((match[1].rm_eo - match[1].rm_so) + 1));
		memset(result[count], '\0', (match[1].rm_eo - match[1].rm_so) + 1);
		memcpy(result[count], content + match[1].rm_so, match[1].rm_eo - match[1].rm_so);
		//printf("Match: %s\n", result[count]);

		content += match[1].rm_eo;	/* update start string */
		count++;
		error = regexec(&re, content, 2, match, REG_NOTBOL);
	}

	for (size_t i = count; i < count; i--) {
		printf("%s\n", result[i]);
		free(result[i]);
	}

	if (result != NULL) free(result);

	return (count);
}

/* 
 * Parse HTML
 */
static void 
parse_stations(char *content, Stations *out)
{
	size_t 	count, i;
	char 	**result = NULL;

	printf("Parse stations\n");

	
	if ((count = extract_data(content, RE_LON, &result)) != 0) {
		printf("Quantidade de longitude encontradas: %lu\n", count);
		/*
		for (i = 0; i < count; i++) {
			printf("Longitude: %s\n", result[i]);
		}*/
	}

}

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
	Stations *sts = NULL;
	Response resp;

	sts = init_stations();

	resp = request(ST_URL_LIST, "GET");
	if (resp.len != 0)
		parse_stations(resp.content, sts);

	if (resp.content != NULL) free(resp.content);

	return (sts);
}

/*
 * Insert station on stations.
 */
void
insert_station(Station *s, Stations *ss)
{
	Stations *n_sts;
	/* new stations */
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

/*
 * Show stations
 */
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
