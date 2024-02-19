# USAC08 - Receber dados do Coletor

#### Implementação

```c
char strDestino[256];

int s_port = coletordata_open_serial_port(coletorDataFile);

coletordata_read_serial_port(s_port, strDestino);

printf("%s\n", strDestino);
```
