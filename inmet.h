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


struct station_data {
	char codigo_estacao[5];
	char data[11];
	uint8_t hora;
	float temp_inst;
	float temp_max;
	float temp_min;
	float umid_inst;
	float umid_max;
	float umid_min;
	float pto_orvalho_inst;
	float pto_orvalho_max;
	float pto_orvalho_min;
	float pressao;
	float pressao_max;
	float pressao_min;
	float vento_vel;
	float vento_direcao;
	float vento_rajada;
	float radiacao;
	float precipitacao;
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
int		 b64_decode(char *, size_t, unsigned char *, size_t *);
int		 b64_encode(const void *, size_t, char *, size_t);
int		 data_parse(char *, size_t, size_t *);

#endif /* INMET_H */
