# ProcessadorDeDados

#### Uso

./processadordedados /dev/ttyS0 config_file dir_intermedio 10

Recebe como argumento:

1. caminho do ficheiro que permite receber dados do ColetorDeDados
2. ficheiro de configuração
3. diretório para colocar os dados para o componente SaidaDeDados
4. número de leituras a efetuar antes de enviar dados para a SaidaDeDados

#### Funcionamento

O funcionamento do componente ProcessadorDeDados é cíclico:

```
while 1 do
    Contadorleitura ← 0;
    repeat
        Read data from sensor ; /* received from ColectorDedados */
        Extract info;
        Insert info into sensor Data Struct;
    until ContadorLeitura=d ;
    foreach sensor do
        Compute median; write counter ← write counter + 1;
        serialize info;
    end
    create the ’AAAAMMDDHHMMSS sensors.txt’ file and write all sensors
                                        info ; /* sent to SaidaDeDados */
end
```
