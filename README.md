# Chat
***
#### Sobre este projeto
***
O projeto é constituido de dois programas, o servidor que suporta ate 10 clientes simultaneamente este que deve ser iniciado e configurado entes dos clinetes, o cliente que se conecta ao servidor através do IP.  

#### Execução
***
 ###### Servidor:

Compilação: 
```
gcc -o serve serverTCP.c -lpthread 
```

Execução : Logo após a o programa sao necessarios a porta e o nome do chat

 ```
 ./serve 22000 batepapo
  ``` 
###### Cliente:

complilação: 
```
gcc -o client clientTCP.c -lpthread
```

execução : Logo após a o programa sao necessarios a porta e o IP do chat e o nome de usuario


```
./client 22000 127.0.0.1 thiago 
```

