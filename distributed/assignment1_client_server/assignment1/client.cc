//

// client.cc

//

// Example of a simple tcp/ip socket-based client

//

#define CLIENT_REQUEST_TYPE 0                   // request type, 0=new client, 1 = client is exiting,
// 2 = query, 3 = response
#define CLIENT_DOMAIN_NAME "mydomain"           // client's domain name
#define CLIENT_REQUEST_ID 26546                 // some random number

// System include's

#include <stdlib.h>

#include <unistd.h>

#include <sys/types.h>

#include <sys/socket.h>

#include <netinet/in.h>

#include <arpa/inet.h>

#include <netdb.h>

#include <iostream>

#include <string.h>

#include <time.h> // for sleep



// Put app include's after system include's

#include "message.h"



using namespace std;



// Port number if the user does not specify it

//#define DEFAULT_PORT_NUMBER "4000"



int main(int argc, char** argv)

{

    struct addrinfo *myinfo; // Address record

    int sockdesc;            // Socket number (*not* the port number)

    char hostname[81];       // Server name

    char portnum[81];        // Server port number (note: char*, not int)

    int connection;          // Return value from connect( )

    int value;               // Return value from read( )



    //message mymessage;       // Record for data
    serviceRequest serviceRequestMessage;	// Record for data



    // Startup: specify the server name and mandatory port number

    if ( argc == 5 )

    {

        int c;

        while((c = getopt(argc, argv, "s:p:")) != -1)
        {
            switch(c)
            {
            case 's':
                strcpy(hostname, optarg);
                break;
            case 'p':
                strcpy(portnum, optarg);
                break;

            }
        }

    }
    else
    {
        cout << "Usage: client -s <host> [-p <portnum>]" << endl;

        exit(0);
    }


    // Use AF_UNIX for unix pathnames instead

    // Use SOCK_DGRAM for UDP datagrams

    cout << "Debug: Before socket" << endl;

    sockdesc = socket(AF_INET, SOCK_STREAM, 0);

    if ( sockdesc < 0 )

    {

        cout << "Error creating socket" << endl;

        exit(0);

    }



    // Set up the address record

    cout << "Debug: Before getaddrinfo" << endl;

    if ( getaddrinfo(hostname, portnum, NULL, &myinfo) != 0 )

    {

        cout << "Error getting address" << endl;

        exit(0);

    }



    // Connect to the host

    cout << "Debug: Before connect" << endl;

    connection = connect(sockdesc, myinfo->ai_addr, myinfo->ai_addrlen);

    if ( connection < 0 )

    {

        cout << "Error in connect" << endl;

        exit(0);

    }

    cout << "Debug: Client connection = " << connection << endl;



    // Create a message to send to server


    serviceRequestMessage.requestType = CLIENT_REQUEST_TYPE; // new request // 0
    strcpy(serviceRequestMessage.domainName,CLIENT_DOMAIN_NAME);
    serviceRequestMessage.requestID = CLIENT_REQUEST_ID;

    cout << "Sending requestType " << serviceRequestMessage.requestType << endl;
    cout << "domainName: " << serviceRequestMessage.domainName << endl;
    cout << "requestID: " << serviceRequestMessage.requestID << endl;

    // Send the message to the server

    write(sockdesc, (char*)&serviceRequestMessage, sizeof(serviceRequest));

    // read that value from server
    value = read(sockdesc, (char*)&serviceRequestMessage, sizeof(serviceRequest));

    // Check the return value

    if ( value != sizeof(serviceRequestMessage) )
    {

        cout << "Error: message received was not the correct size" << endl;

    }

    cout << "Server sent me back request type " << serviceRequestMessage.requestType << endl;

    // if



    cout << "Sending requestType = 2 for query" << endl;
    serviceRequestMessage.requestType = 2;
    write(sockdesc, (char*)&serviceRequestMessage, sizeof(serviceRequest));


    // read that value from server
    value = read(sockdesc, (char*)&serviceRequestMessage, sizeof(serviceRequest));

    // Check the return value
    if ( value != sizeof(serviceRequestMessage) )
    {

        cout << "Error: message received was not the correct size" << endl;

    }

    cout << "Server sent me back request type " << serviceRequestMessage.requestType << endl;



    cout << "Again sending requestType = 2 for query" << endl;
    serviceRequestMessage.requestType = 2;
    write(sockdesc, (char*)&serviceRequestMessage, sizeof(serviceRequest));


    // read that value from server
    value = read(sockdesc, (char*)&serviceRequestMessage, sizeof(serviceRequest));

    // Check the return value
    if ( value != sizeof(serviceRequestMessage) )
    {

        cout << "Error: message received was not the correct size" << endl;

    }

    cout << "Server sent me back request type " << serviceRequestMessage.requestType << endl;



    cout << "Sending requestType = 1 to quit" << endl;
    serviceRequestMessage.requestType = 1;

    write(sockdesc, (char*)&serviceRequestMessage, sizeof(serviceRequest));


    // Read back exactly one message
    value = read(sockdesc, (char*)&serviceRequestMessage, sizeof(serviceRequest));


    // Check the return value
    if ( value != sizeof(serviceRequestMessage) )
    {

        cout << "Error: message received was not the correct size" << endl;

    }
    // if



    // Display the received message
    cout << "Debug: Client gets back: " << endl;

    cout << "requestType: " << serviceRequestMessage.requestType << endl;
    cout << "domainName: " << serviceRequestMessage.domainName << endl;
    cout << "requestID: " << serviceRequestMessage.requestID << endl;



    // Close the socket
    close(sockdesc);


    return 0;

} // main( )




