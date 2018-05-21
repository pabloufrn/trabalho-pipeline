# trabalho-pipeline

# compilação
No linux, use o comando `make debug` para compilar em modo de depuração ou `make` para compilar em modo normal.
Caso não esteja no linux, use o comando `g++ -Wall -std=c++11 -g -D DEBUG -I include src/* -o exec` para compilar em modo de depuração ou
`g++ -Wall -std=c++11 -I include src/* -o exec` para compilar em modo normal
# execução
Use o comando `./exec [arquivo de entrada] -o [arquivo da saida]` no linux ou `exec << [arquivo de entrada]` no windows
Se não quiser passar arquivo de entrada escreva cada instrução separada por um fim de linha (Enter) e aperte ctrl+d para finalizar a entrada (não use ctrl+c)  

Programa desenvolvido Thiago José Da Silva e Pablo Emanuell Lopes Targino.
