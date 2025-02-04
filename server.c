
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>


int main() {

        int portno;

	//open a file to serve the response
	FILE *html_data;
	html_data = fopen("index.html" , "r");
	
	char response_data[1024];
	fgets(response_data, 1024, html_data);
	


	char http_header[2048] = "HTTP/1.1 200 OK\r\n\n";
	strcat(http_header , response_data);


	//create a socket
	int server_socket;
	server_socket = socket(AF_INET , SOCK_STREAM , 0);

	//define the address
	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(portno);
	server_address.sin_addr.s_addr = INADDR_ANY;
	
	//binding with the client
	bind(server_socket, (struct sockaddr *) &server_address, sizeof(server_address));
	
	
	//listening
	listen(server_socket, 20);
	int client_socket;
	
	while(1){
		client_socket = accept(server_socket , NULL , NULL);
		send(client_socket , http_header , sizeof(http_header) , 0);
		close(client_socket);
	}
return 0;	
}
