# CINMET
> Rápida biblioteca para consumir e interpretar dados meteorológicos da rede INMET.

## Porque?

O Instituto Nacional de Meteorologia **[INMET](http://www.inmet.gov.br/portal/)** 
oferece inúmeras informações meteorológicas para as mais diversas
tomadas de decisão.

Uma das informações relevantes para agricultura, indústria e ciência são os dados
**brutos** gerados pelas estações de campo ligadas que se conectam na rede mundial,
mais conhecidas como *estações automáticas*.

Essas estações se estendem por todo território Brasileiro inclusive outros países. Até
o presente momento que é escrito esse readme ao todo são 579 estações, Os dados 
são gerados de hora em hora e os usuários tem acesso público a esses dados **somente**
de um ano contando do dia da consulta.

O problema, além de algumas instabilidades, captchas, formulários, mapas... 
está no momento de portar esses dados para alguma formatação que
seja de simples interpretação para programa de computadores. 

No próprio site o [INMET](http://www.inmet.gov.br/portal/) disponibiliza o download para
o formato CSV, mas o que era para ser um CSV acaba sendo um HTML com umas
**linhas embranco** :finnadie: **caracteres HTML**, abaixo mostro um exemplo e saída.

**Exemplo de saída dada pelo INMET**
```
                                                                                                                                                                                                                                                                                                                                                              
codigo_estacao,data,hora,temp_inst,temp_max,temp_min,umid_inst,umid_max,umid_min,
pto_orvalho_inst,pto_orvalho_max,pto_orvalho_min,pressao,pressao_max,pressao_min,
vento_direcao,vento_vel,
  vento_rajada,radiacao,precipitacao<br>
  A764,23/09/2019,00,22.9,24.9,22.9,62,62,57,15.2,15.8,15.2,
  948.6,948.7,947.8,5.1,159,12.3,-3.60,0.0<br>A764,23/09/2019,
  01,21.3,22.9,21.3,65,65,62,14.5,15.2,14.5,949.4,949.4,
  948.6,5.6,153,11.8,-3.60,0.0<br>A764,23/09/2019,02,20.2,
  21.3,20.2,67,67,65,13.9,14.5,13.9,
  949.9,949.9,949.3,5.0,158,11.4,-3.60,0.0<br>A764
```

Por fim necessitava interpretar dados diariamente de todas essas estações do período
de dois anos/a cada hora! 

**Isso mesmo estamos falando de uma média 321024 dados/h**.

Surgiu a necessida da biblioteca **CIMET**, uma biblioteca **SIMPLES, RÁPIDA e LIVRE** objetivo principal é conseguir obter, processar esses dados e dar a oportunidade de outros programas terem acesso a as informações geradas.
