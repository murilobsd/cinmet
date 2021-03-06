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
#include <err.h>
#include <stdlib.h>
#include <string.h>

#include "inmet.h"

int
main(int argc, char *argv[])
{
	Stations *ss, *sts_sp;
	size_t num_sta_sp = 0;

	/* init sts_sp */
	sts_sp = init_stations();
	
	/* get list of stations */
	ss = get_stations();
	//dump_stations(ss);

	/* search stations by federative unit (UF) */
	if ((num_sta_sp = search_sta_uf("MG", ss, sts_sp)) == 0)
		printf("Not found stations on SP\n");
	else
		dump_stations(sts_sp);

	/* clean list stations of uf SP */
	//clean_stations(sts_sp);
	if (sts_sp != NULL) free(sts_sp);
	/* clean list stations */
	clean_stations(ss);
/*
        const char *filename = "bebedouro.html";
        FILE *file;
        size_t status;

        if ((file = fopen(filename, "r")) == NULL)
                err(1, "%s", filename);

	if ((status = parse_file(file)) != 0)
		errx(1, "%s", filename);

        if (file != NULL) fclose(file);
*/
        return (0);
}

