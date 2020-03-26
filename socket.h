#include <stdio.h> //printf
#include <stdlib.h>
#include <string.h> //strlen
#include <ctype.h>
#include <time.h>
#include <math.h>
#include <sys/socket.h> //socket
#include <arpa/inet.h> //ipet_addr
#include <unistd.h>  //write
#include <bitset>
#include "rsa.h"
#include "error_functions.h"

int Scanf(const char* format,...){

    int count;
    va_list ap;

    va_start(ap,format);
    count = vfscanf(stdin, format, ap);
    va_end(ap);
    return count;
} 


int Recv(int sockfd, void *buf, size_t len, int flags){
    
    memset(buf, 0, strlen((const char*)buf));
    if( (len = recv(sockfd , buf, len , flags)) < 0){
        fatal_sys_exit("%s","Recv error");
    }
    return len;
}

int Send(int sockfd, const void *buf, size_t len, int flags){

    if( (len = send(sockfd, buf, len, flags)) < 0 ){
        fatal_sys_exit("%s","Send error");
    }
    return len;
}

int Rand100(){
    int seed = (int)time(NULL);
    srand(seed);
    return rand() % 100 + 1;
    puts("New Keys completely Created\n");
}

void Generate_keys(){

   puts("regenerating keys, please be patient...");

  FILE *keyFile;
   Uint32_t tmpPub, tmpPriv, tmpProd;
  keyFile = fopen("myKey.txt", "w");

  srand(time(NULL));
  for(int i = 0 ; i < 100 ; ++i){
    get_keys(&tmpPub, &tmpPriv, &tmpProd);
    fprintf(keyFile, "%lu %lu %lu\n", tmpPub, tmpPriv, tmpProd);
  }
  fclose(keyFile);
}

void Initial_keys(int num, Uint32_t *serPub, Uint32_t *serPriv, Uint32_t *serProd){

    if(num == 0){

      Generate_keys();

      Initial_keys(Rand100(), serPub, serPriv, serProd);
    }else{

      FILE *keyFile;
      int n = num;
      keyFile = fopen("myKey.txt","r");
      if(!keyFile){
        Generate_keys();
	keyFile = fopen("myKey.txt","r");
      }
      while(n--){
        fscanf(keyFile, "%lu %lu %lu", serPub, serPriv, serProd);
      }
      fclose(keyFile);
    }
}
