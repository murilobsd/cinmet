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
#ifndef _INMET_H
#define _INMET_H

/*
 * Automatic station weather data within one hour.
 */
struct w_data {
        char            codigo_estacao[4];      /* code Eg. A764 */
        float           precipitação;           /* preciption */
        float           pressao_inst;           /* inst pressure */
        float           pressao_max;            /* max pressure */
        float           pressao_min;            /* min pressure */
        float           pto_orvalho_inst;       /* inst dew point */ 
        float           pto_orvalho_max;        /* max dew point */
        float           pto_orvalho_min;        /* min dew point */
        float           radiacao;               /* radiation */
        float           temp_inst;              /* inst temperature */
        float           temp_max;               /* max temperature */
        float           temp_min;               /* min temperature */
        float           umid_inst;              /* inst humidity */ 
        float           umid_max;               /* max humidity */
        float           umid_min;               /* min humidity */
        float           vento_direcao;          /* wind direction*/
        float           vento_raj;              /* gust wind */ 
        float           vento_vel;              /* wind velocity */
        time_t          data;                   /* datetime */
        struct w_data   *next;
        size_t          length;                 /* size vector */
} WeatherData;

extern WeatherData *    weather_init(void);
extern void             weather_free(WeatherData *);
extern size_t           parse_file(FILE *);

#endif // _INMET_H
