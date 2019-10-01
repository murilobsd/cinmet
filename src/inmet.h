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

// url list automatic stations
#define ST_URL_LIST "http://www.inmet.gov.br/sonabra/maps/pg_mapa.php"

#define ST_INVALID_VAL -999.0	/* valores embranco */
#define ST_MAX_CITY 	50
#define ST_MAX_NAME 	50
#define ST_MAX 		579     /* number of stations up to 27/06/2019 */

// regex
#define RE_LON \
        "Longitude:[[:space:]]([[:punct:]]?[[:digit:]]{1,2}" \
        "[[:punct:]][[:digit:]]+)"
#define RE_LAT \
        "Latitude:[[:space:]]?([[:punct:]]?[[:digit:]]{1,2}" \
        "[[:punct:]][[:digit:]]+)"
// #define RE_COD          "OMM:</b>[[:space:]]?([[:digit:]]+)"
#define RE_URL          "pg_dspDadosCodigo_sim\\.php\\?([A-Za-z0-9]+==)"
#define RE_NOME         "</b>[[:space:]]?([[:alpha:]]+-[A-Z][0-9]+)"
#define RE_UF           "label = '([A-Z]{2})"
//#define RE_CIDADE       "label = 'AC - (Feij.)"
#define RE_CIDADE       "label = '[A-Z]{2}[[:space:]]?\\-[[:space:]]?(([A-z]+[[:space:]]?)+)'"
#define RE_INICIO       "Aberta em: ([0-9]{2}\\/[0-9]{2}\\/[0-9]{4})"

#define URL             "http://www.inmet.gov.br/sonabra/pg_dspDados" \
                        "Codigo_sim.php?%s"
/*
 * Automatic station
 */
typedef struct statation_t {
        char           	cidade[ST_MAX_CITY]; 	/* city name */
        char           	nome[ST_MAX_NAME]; 	/* name */
        char           	uf[3];			/* federative unit */
        char           	url[2000];		/* url weather data */
        float          	lat;			/* lattitude degress */
        float          	lon;			/* longitude degress */
        time_t         	inicio;			/* started station */
} Station;

typedef struct stas_t {
	Station		*estacao;		/* station type */
	struct stas_t	*prox;			/* next station address */
} Stations;

/*
 * Automatic station weather data within one hour.
 */
typedef struct w_data_t {
        char            codigo_estacao[4];      /* code Eg. A764 */
        float           precipitacao;           /* preciption */
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

WeatherData *    	weather_init(void);
void             	weather_free(WeatherData *);
size_t           	parse_file(FILE *);
size_t			search_sta_uf(const char *, Stations *, Stations *);
Stations *		get_stations(void);
void			insert_station(Station *, Stations *);
void 			dump_stations(Stations *);
void			dump_station(Station *);
void			clean_stations(Stations *);
void			clean_station(Station *);
Stations *		init_stations(void);
Station *		init_station(void);

/* request.c */

#define USER_AGENT \
	"User-Agent: cinmet-0.0.1 / https://github.com/murilobsd/inmet"

/*
 * Response
 */
typedef struct response_t {
        char            *content;
        size_t          len;
        long 		code;			/* status code */
} Response;

/*
 * Request
 */
typedef struct request_t {
        char            url[2000];
        char            method[8];
} Request;

Response 		request(char *, char *);

/* util.c */
void * 			xmalloc(size_t);
void *			xrealloc(void *, size_t);

#endif // _INMET_H
