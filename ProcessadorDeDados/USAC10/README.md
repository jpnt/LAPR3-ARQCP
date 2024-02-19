# USAC10 - Serialização da informação dos sensores; Escrever informação num ficheiro

#### Design

Como guardar a informação serializada no ficheiro:

Serializar apenas uma linha e escrever no ficheiro "uma a uma"? Não. Pois muitas
escritas no disco irá afetar o desempenho da aplicação. É ineficiente.

Daí chegamos à conclusão que vamos serializar a informação de todos os sensores
e fazer uma só escrita no ficheiro de forma a minimizar o acesso ao disco.

#### Estruturação dos dados

char* srlInfo[numSensores];

sensor_id,write_counter,type,unit,mediana#  --> srlInfo[0]
sensor_id,write_counter,type,unit,mediana#  --> srlInfo[1]
...
