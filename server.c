#include "socket.h"
 
int main(int argc , char *argv[])
{
    
    int socket_desc , client_sock , c , read_size, mode, num;
    struct sockaddr_in server , client;
    char client_message[2000], cipher[2000], buff[1000];
 
    if(argc < 2)
      num = Rand100();
    else{
      num = atoi(argv[1]);
      if(num < 0 || num > 100){
        puts("Usage: server [num] num has to between 0 to 100.");
        return 0;
      }
    }
   
    Uint32_t serPub, serPriv, serProd;
    Initial_keys(num, &serPub, &serPriv, &serProd);

    //Create socket
    socket_desc = socket(AF_INET , SOCK_STREAM , 0);
    if (socket_desc == -1)
    {
        printf("Could not create socket");
    }
    puts("Socket created");
     
    //Prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons( 8888 );
     
    //Bind
    if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0)
    {
        //print the error message
        perror("bind failed. Error");
        return 1;
    }
    puts("bind done");
     
    //Listen
    listen(socket_desc , 3);
     
    //Accept and incoming connection
    puts("Waiting for incoming connections...");
    c = sizeof(struct sockaddr_in);
     
    //accept connection from an incoming client
    client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c);
    if (client_sock < 0)
    {
        perror("accept failed");
        return 1;
    }
    puts("Connection accepted,encrypting channel...");
    
    sprintf(client_message, "%lu,%lu", serPub, serProd);
    write(client_sock, client_message, strlen(client_message));
    memset(client_message, 0, strlen(client_message));    
    puts("encrypted channel builded");

    if(Recv(client_sock, client_message, 2000, 0) > 0)
      sscanf(client_message, "%d", &mode);
    
    memset(client_message, 0, strlen(client_message));
    //Receive a message from client
    while( (read_size = Recv(client_sock , cipher , 2000 , 0)) > 0 )
    {
        //Send the message back to client
        if(!mode){
          decrypt(cipher, client_message, serPriv, serProd);
          write(client_sock , client_message , strlen(client_message));
          memset(client_message, 0, strlen(client_message));
        }else{
          write(client_sock, cipher, strlen(cipher));
          memset(cipher, 0, strlen(cipher));
        }
        memset(client_message, 0, strlen(client_message));
    }
     
    if(read_size == 0)
    {
        puts("Client disconnected");
        fflush(stdout);
    }
     
    return 0;
}
