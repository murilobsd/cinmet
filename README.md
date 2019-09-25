# INMET
> Rápida biblioteca para interpretar dados meteorológicos.

## Porque?

O [INMET](http://www.inmet.gov.br/portal/) (Instituto Nacional de Meteorologia)
oferece inúmeras informações meteorológicas para tomada de decisão.

Uma das informações relevantes para agricultura, indústria e ciência são os dados
*brutos* gerados pelas estações automáticas (estãçoes de campo ligadas na rede mundial) 
que se estendem em todos os estados brasileiros. Os dados são gerados de hora
em hora e os usuários tem acesso público até um ano contando do dia da consulta.

O problema está no momento de portar esses dados para alguma formatação que
seja de simples leitura, no próprio site o [INMET](http://www.inmet.gov.br/portal/) disponibiliza o download para
o formato CSV, mas o que era para ser um CSV acaba sendo um HTML com umas
linhas embranco =/ enfim um caso para quem quiser ler esses dados.

**Exemplo de saída dada pelo INMET**
```
                                                                                                                                                                                                                                                                                                                                                              
codigo_estacao,data,hora,temp_inst,temp_max,temp_min,umid_inst,umid_max,umid_min,pto_orvalho_inst,pto_orvalho_max,pto_orvalho_min,pressao,pressao_max,pressao_min,vento_direcao,vento_vel,
  vento_rajada,radiacao,precipitacao<br>A764,23/09/2019,00,22.9,24.9,22.9,62,62,57,15.2,15.8,15.2,948.6,948.7,947.8,5.1,159,12.3,-3.60,0.0<br>A764,23/09/2019,01,21.3,22.9,21.3,65,65,62,14.5,15.2,14.5,949.4,949.4,948.6,5.6,153,11.8,-3.60,0.0<br>A764,23/09/2019,02,20.2,21.3,20.2,67,67,65,13.9,14.5,13.9,949.9,949.9,949.3,5.0,158,11.4,-3.60,0.0<br>A764
```
