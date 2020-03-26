/*
    C ECHO client example using sockets
*/
#include "socket.h"
 
int main(int argc , char *argv[])
{

    if(argc < 2){

      puts("Usage: client [mode] <ip>");
      return 1;
    }
    
    int sock, mode, ip;
    struct sockaddr_in server;
    char message[1000] , server_reply[2000], cipher[2000];
     
    if(argc == 2){
      mode = 0;
      ip = 1;
    }else if(argc == 3){
      mode = (int)argv[1][0] - '0';
      ip = 2;
    }

    //Create socket
    sock = socket(AF_INET , SOCK_STREAM , 0);
    if (sock == -1)
    {
        printf("Could not create socket");
    }
    puts("Socket created");
     
    server.sin_addr.s_addr = inet_addr(argv[ip]);
    server.sin_family = AF_INET;
    server.sin_port = htons( 8888 );
 
    //Connect to remote server
    if (connect(sock , (struct sockaddr *)&server , sizeof(server)) < 0)
    {
        perror("connect failed. Error");
        return 1;
    }

    //recieve keys
    Uint32_t pub, prod;
    recv(sock , server_reply , 2000 , 0);
    sscanf(server_reply, "%lu,%lu", &pub, &prod);
    memset(server_reply , 0, strlen(server_reply)); 
    puts("Connected\n");

    if(mode){
      sprintf(message, "%d", mode);
      if(send(sock, message, strlen(message), 0) < 0)
        puts("failed to turn off decrypted mode");
      else
        puts("direct mode");  
    }else{
      sprintf(message, "%d", mode);
      if(send(sock, message, strlen(message), 0) < 0)
        puts("failed to turn on decrypted mode");
      else
        puts("decrypted mode");
    }
    memset(message, 0, strlen(message));
     
    //keep communicating with server
    while(1)
    {
        printf("Enter message : ");
        Scanf( "%s", message);
        encrypt(message, cipher, pub ,prod);
        //Send some data
        if( send(sock , cipher , strlen(cipher) , 0) < 0)
        {
            puts("Send failed");
            return 1;
        }
         
        //Receive a reply from the server
        if( recv(sock , server_reply , 2000 , 0) < 0)
        {
            puts("recv failed");
            break;
        }
        printf("Server reply : %s    \n",server_reply);
/*        for(int i = 0; i < strlen(server_reply); ++i){
          std::bitset<16> bt = server_reply[i];
	  printf("%lu  %d\n", bt.to_ulong(),bt[0]);
        }*/
	memset(message, 0, strlen(message));
	memset(server_reply , 0, strlen(server_reply));
    }
     
    close(sock);
    return 0;
}
