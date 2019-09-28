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

/* station.c */

/* url list automatic stations */
#define ST_URL "http://www.inmet.gov.br/sonabra/maps/pg_mapa.php" 

#define ST_MAX_CITY 50
#define ST_MAX_NAME 50
#define ST_MAX 579      /* número de estações 27/06/2019 */

// regex
#define RE_LON \
        "Longitude:[[:space:]]([[:punct:]]?[[:digit:]]{1,2}" \
        "[[:punct:]][[:digit:]]+)"
#define RE_LAT \
        "Latitude:[[:space:]]?([[:punct:]]?[[:digit:]]{1,2}" \
        "[[:punct:]][[:digit:]]+)"
#define RE_COD          "OMM:</b> ([[:digit:]]+)"
#define RE_URL          "pg_dspDadosCodigo_sim\\.php\\?([A-Za-z0-9]+==)"
#define RE_NOME         "</b>[[:space:]]?([[:alpha:]]+-[A-Z][0-9]+)"
#define RE_UF           "label = '([A-Z]{2})"
#define RE_CIDADE       "label = 'AC - (Feij.)"
//#define RE_CIDADE       "label = '[A-Z]{2} - (([A-z]+[[:space:]]?)+)'"
#define RE_INICIO       "Aberta em: ([0-9]{2}\\/[0-9]{2}\\/[0-9]{4})"

#define URL             "http://www.inmet.gov.br/sonabra/pg_dspDados" \
                        "Codigo_sim.php?%s"

/*
 * Automatic station
 */
typedef struct station_t {
        char            cidade[ST_MAX_CITY];
        char            nome[ST_MAX_NAME];
        char            uf[2];
        char            url[2000];
        char            url_imagem[2000];
        float           lat;
        float           lon;
        uint32_t        omm;
        time_t          inicio;
} Station; 

/*
 * Automatic station weather data within one hour.
 */
typedef struct w_data_t {
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
        struct w_data_t *next;
        size_t          length;                 /* size vector */
} WeatherData;

extern WeatherData *    weather_init(void);
extern void             weather_free(WeatherData *);
extern size_t           parse_file(FILE *);
void * 			xmalloc(size_t);
void *			xreallocarray(void *, size_t, size_t);

#endif // _INMET_H
