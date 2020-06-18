#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

using namespace std;

int main(int argc, char *argv[])
{
    // User should enter the port info
    if(argc != 2)
    {
        cerr << "Usage: port" << endl;
        exit(0);
    }

    int port = atoi(argv[1]);

    // Create the socket
    int serverSd = socket(AF_INET, SOCK_STREAM, 0);
    
    if(serverSd < 0)
    {
        cerr << "Can't initialize socket!"<< endl;
        exit(0);
    }

    // Set a socket and connection tools
    sockaddr_in servAddr;
    memset(&servAddr, 0, sizeof(servAddr));
    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(port);
    servAddr.sin_addr.s_addr = htonl(INADDR_ANY);

    // Bind the ip address and port to a socket
    int bindStatus = bind(serverSd, (struct sockaddr*)&servAddr, sizeof(servAddr));

    if(bindStatus < 0)
    {
        cerr << "Can't binding socket to local address!" << endl;
        exit(0);
    }

    // Lİsten for up to 5 requests at a time
    listen(serverSd, 5);

    // Receive a request from client using accept
    sockaddr_in newSocketAddr;
    socklen_t newSocketSize = sizeof(newSocketAddr);

    // Wait for connection from client
    int newSd = accept(serverSd, (sockaddr *)&newSocketAddr, &newSocketSize);

    if(newSd < 0)
    {
        cerr << "Can't accepting the request from client!" << endl;
        exit(0);
    }

    char buffer[500];
    string data;

    // While loop to accept data and send message
    while(1)
    {
        memset(&buffer, 0, sizeof(buffer));

        // Wait for client to send data
        recv(newSd, (char*)buffer, sizeof(buffer), 0);

        if(!strcmp(buffer, "exit"))
        {
            cout << "\nClient has quit the session" << endl;
            break;
        }

        cout << "Client: " << buffer << endl;

        data = "Your message has been received!";
        memset(&buffer, 0, sizeof(buffer));
        strcpy(buffer, data.c_str());

        // Send message to client
        send(newSd, (char*)buffer, strlen(buffer), 0);
    }

    // Close the socket
    close(newSd);
    close(serverSd);
    
    cout << "Connection has been closed!" << endl;
    return 0;
}