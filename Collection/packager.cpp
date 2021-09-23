#include "packager.h"

int packet_sender(float * data){
	int socket_desc;
	struct sockaddr_in server;
	char *message;
    std::string arr[3];

    for (int i = 0; i < 3; i++){
        arr[i] = std::to_string(data[i]);
    }
	
	//Create socket
	socket_desc = socket(AF_INET , SOCK_DGRAM, 0);
	if (socket_desc == -1) printf("Could not create socket");
		
	server.sin_addr.s_addr = inet_addr("192.168.3.22");
	// server.sin_addr.s_addr = inet_addr("255.255.255.255");
	server.sin_family = AF_INET;
	server.sin_port = htons(9999);

	//Connect to remote server
	if (connect(socket_desc , (struct sockaddr *)&server , sizeof(server)) < 0){
		puts("connect error");
		return 1;
	}
	
	puts("Connected\n");
	
	//Send some data
	message = "hello";
	if( send(socket_desc , message , strlen(message) , 0) < 0){
		puts("Send failed");
		return 1;
	}
	puts("Data Send\n");
	
	return 0;
}