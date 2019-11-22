tar:server  client
server:server.c
	gcc -g -Wall -o  $@  $< -lpthread
client:client.c
	gcc -g -Wall  -o  $@ $< -lpthread
c:
	rm -rf server client  FIFO
