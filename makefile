server: server.c
	gcc -g -O0 server.c -lsqlite3 -o server

client: client.c
	gcc -g -O0 -o client client.c

