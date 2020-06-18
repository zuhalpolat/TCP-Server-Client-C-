#include <iostream>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <netdb.h>
#include <unistd.h>

using namespace std;

int main(int argc, char *argv[])
{
    // User should give IpAddress and Port informations
    if(argc != 3)
    {
        cerr << "Usage: IPAddress Port" << endl;
        exit(0);
    }

    char *serverIp = argv[1];
    int port = atoi(argv[2]);
    
    struct hostent* host = gethostbyname(serverIp);

    // Creating socket
    int clientSD = socket(AF_INET, SOCK_STREAM, 0);

    // Fill the information in a sendSockAddr structure
    sockaddr_in sendSockAddr;
    memset(&sendSockAddr, 0, sizeof(sendSockAddr));
    sendSockAddr.sin_family = AF_INET;
    sendSockAddr.sin_port = htons(port);
    sendSockAddr.sin_addr.s_addr = inet_addr(inet_ntoa(*(struct in_addr*)*host->h_addr_list));

    // Connect to server
    int status = connect(clientSD, (sockaddr*)&sendSockAddr, sizeof(sendSockAddr));

    if(status < 0)
    {
        cerr << "Can't connect to socket!" << endl;
        exit(0);
    }

    char buffer[250];
    string data;

    // While loop to get and send message
    while(1)
    {
        cout << ">> ";
        getline(cin, data);

        memset(&buffer, 0, sizeof(buffer));
        strcpy(buffer, data.c_str());

        send(clientSD, (char*)&buffer, strlen(buffer), 0);

        if(data == "exit")  
            break;

        memset(&buffer, 0, sizeof(buffer));
        recv(clientSD, (char*)&buffer, sizeof(buffer), 0);

        cout << "Server: " << buffer << endl;
    }

    close(clientSD);
    cout << "\nConnection has been closed!" << endl;
    return 0;
}