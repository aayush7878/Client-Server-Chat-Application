#include<iostream>
#include<WinSock2.h>
#include<ws2tcpip.h>
#include<tchar.h>
using namespace std;

#pragma comment(lib, "ws2_32.lib")

/*
    //initialize winsock library 
    //create the socket 
    //get ip and port
    //bind the ip/port with the socket
    //listen on the socket
    //accept
    //close the socket
    //cleanup the winsock
*/

bool Initialize(){
    WSDATA data;
    return WSAStartup(MAKEWORD(2, 2), &data) == 0;
}

int main(){
    if(!Initialize()){
        cout<<"winsock initialization failed\n";
        return 0;
    }

    cout<<"server program\n";

    SOCKET listenSocket = socket(AF_INET, SOCK_STREAM, 0);

    if(listenSocket == INVALID_SOCKET){
        cout<<"socket creation failed\n";
        return 0;
    }

    //create address structure
    int port = 6969;
    sockaddr_in serveraddress;
    serveraddress.sin_family = AF_INET;
    serveraddress.sin_port = htons(port); //host to network short

    //convert the ipaddress (0.0.0.0) -> put this inside the sin_family in binary form 
    if(InetPton(AF_INET, _T("0.0.0.0"), &serveraddress.sin_addr) != 1){
        cout<<"setting address structure failed\n";
        closesocket(listenSocket);
        WSACleanup();
        return 0;
    };

    //bind
    if(bind(listenSocket, reinterpret_cast<sockaddr*>(&serveraddress), sizeof(serveraddress)) == SOCKET_ERROR){
        cout<<"bind failed\n";
        closesocket(listenSocket);
        WSACleanup();
        return 0;
    }

    //listen
    if(listen(listenSocket, SOMAXCONN) === SOCKET_ERROR){
        cout<<"listen failed\n";
        closesocket(listenSocket);
        WSACleanup();
        return 0;
    }

    cout<<"server has started listening on port : "<<port<<"\n";

    WSACleanup();
    return 0;
    
}
