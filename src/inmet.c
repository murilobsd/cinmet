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

static int parse_line(char *);

WeatherData *
weather_init(void)
{
        WeatherData *w;

        if ((w = malloc(1 * sizeof(WeatherData))) == NULL)
                        err(1, NULL);
        return w;
}

void
weather_free(WeatherData *w)
{
        if (w == NULL)
                return;
        for (int i = 0; i < w->length; i++) {
                free(w->next);
        }
        free(w);
}

static int
parse_line(char *l)
{
        int count = 0;
        size_t len_line;
        char value[20];
        len_line = strlen(l);

        for (int i = 0; i < len_line; i++) {
                if (l[i] != '\0') {
                        if (l[i] == ',') {
                                value[count] = '\0';
                                printf("Valor: %s\n", value);
                                value[0] = '\0';
                                count = 0;
                        } else {
                                value[count] = l[i];
                                count++;
                        }
                }
        }
        
        return(0);
}

size_t
parse_file(FILE *fp)
{
        /* TODO: dynamic allocate/re line */
	char ch, line[500];
	size_t count = 0, line_value = 0, header = 0, match = 0;

        while ((ch = getc(fp)) != EOF) {
                if (ch != '\n' && ch != ' ') {
                        if (ch == '<' || ch == 'b' || ch == 'r' || ch == '>') {
                                match++;
                        } else {
                                match = 0;
                        }
                        if (match == 4) {
                                line[line_value-3] = '\0';
                                if (header != 0)
                                        parse_line(line);
                                header++;
                                match = 0;
                                line_value = 0;
                                count++;
                        } else {
                                line[line_value] = (char)ch;
                                line_value++;
                        }
                }
        }
	return (0);
}
