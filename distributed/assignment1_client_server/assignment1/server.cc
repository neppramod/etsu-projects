//

// server.cc

//

// A simple tcp/ip socket-based server.

//   Handles exactly one connection and one request

//



// System include's

#include <stdlib.h>

#include <unistd.h>

#include <sys/types.h>

#include <sys/socket.h>

#include <netinet/in.h>

#include <netdb.h>

#include <iostream>

#include <string.h>

#include <stdio.h>



// App include's

#include "message.h"


// For threading
#include<pthread.h>
void *connection_handler (void *sock_desc);

int findAClient(int requestID);
void registerAClient(int requestID);
void unregisterAClient(int index);


// Default port number if user does not specify it

#define DEFAULT_PORT_NUMBER "4000"
#define MAXCLIENT 80



using namespace std;

serviceRequest *serviceRequestMessage; // Service request message
int value;			// Return from read( )
int connection;			// Return value from accept( )

int clientIds[MAXCLIENT] = {0}; // Keeps a table of clients. Assuming 0 is invalid requestID;


int main (int argc, char **argv)
{

    int sockdesc;			// Socket descriptor

    struct addrinfo *myinfo;	// Address record

    char portnum[81];		// Port number

    pthread_t *thread1;		// For thread creation



    // Use connection, not sockdesc, for read/write

    // get the portnum

    // Create the socket with domain, type, protocol as

    //    internet, stream, default

    sockdesc = socket (AF_INET, SOCK_STREAM, 0);

    if (sockdesc < 0)

    {

        cout << "Error creating socket" << endl;

        exit (0);

    }				// if



    // Get the port number from the command line with -p option

    //   else use default

    if (argc == 3)

    {

        int c;

        while ((c = getopt (argc, argv, "p:")) != -1)
        {
            switch (c)
            {
            case 'p':
                strcpy (portnum, optarg);
                break;
            default:
                break;
            }
        }
    }

    else

    {

        cout << "Default port number " << DEFAULT_PORT_NUMBER << " in use." << endl;
        strcpy (portnum, DEFAULT_PORT_NUMBER);

    }				// if

    cout << "Port " << portnum << " in use." << endl;

    // Set up the address record for this machine
    int portint;

    while (true)
    {


        if (getaddrinfo ("0.0.0.0", portnum, NULL, &myinfo) != 0)

        {

            cout << "Error getting address" << endl;

            exit (0);

        }			// if



        // Bind the socket to an address

        if (bind (sockdesc, myinfo->ai_addr, myinfo->ai_addrlen) < 0)

        {

            cout << "Error binding to socket. Let's get new port address" <<
                 endl;

            portint = atoi (portnum);
            portint++;
            //itoa(portint, portnum, 10);
            sprintf (portnum, "%d", portint);
            cout << "Port changed to " << portnum << endl;

            continue;

            //exit(0);


        }
        else
        {
            break;
        }

    }				// while ends


    // Now listen to the socket

    if (listen (sockdesc, 1) < 0)

    {

        cout << "Error in listen" << endl;

        exit (0);

    }				// if



    // Note: this loop is typical of servers that accept multiple

    // connections on the same port - normally, after accept( )

    // returns, you'd fork off a process to handle that request, or

    // create a thread to do the same, passing the returned value as

    // a parameter for read( ) and write( ) to use -

    // that is, accept( ) returns a new descriptor -

    // you actually talk on a different socket in the child.

    // The main program would then loop around, and wait at accept( )

    // for another request for a connection, then hand that new

    // connection off to a child or thread, etc.

    // So the server runs forever - see the for loop parameters -

    // well, until you kill it manually.  Here, we break from

    // the for loop after one message.



    for (;;)

    {

        cout << "Calling accept" << endl;

        // Accept a connect, check the returned descriptor

        connection = accept (sockdesc, NULL, NULL);

        if (connection < 0)

        {

            cout << "Error in accept" << endl;

            exit (0);

        }

        else

        {



            // Here's where the fork( ) or pthread_create( ) call would

            // normally go, passing connection (returned by accept( )

            // above) as a parameter.  connection is a file descriptor

            // attached to a different port, so that the server can

            // continue to accept connections on the original port.

            //

            // Instead of all that, this program just does the

            // following:

            // Read exactly one message

            // Note that the first parameter of read is the returned

            // value from accept( ) above.



            // create a new thread
            thread1 = (pthread_t *) malloc (sizeof (pthread_t));


            if (pthread_create
                    (thread1, NULL, &connection_handler, (void *) &connection) < 0)
            {
                cout << "Error in creating thread" << endl;
            }
            else
            {
                //*/

                cout << "Thread creation successful" << endl;
                continue;

            }			// thread ends

            // Then quit

            //break;

        }			// if



    }				// for



    // Close the connection

    close (connection);

    return 0;



}


void *connection_handler (void *sock_desc)
{
    int requestType = 0;

    while(requestType != 1)   // until the client sends requestType=1
    {
        serviceRequestMessage = (serviceRequest *) malloc(sizeof(serviceRequest));

        value = read (connection, (char *) serviceRequestMessage, sizeof (serviceRequest));


        if(value != sizeof (serviceRequest))

        {

            cout << "Error, read( ) returned a bad value" << endl;

        }

        cout << "Debug: value = " << value << endl;



        // Display the message

        cout << "\nServer received: "  << endl;
        cout << "requestType: " << serviceRequestMessage->requestType << endl;
        cout << "domainName: " << serviceRequestMessage->domainName << endl;
        cout << "requestID: " << serviceRequestMessage->requestID << endl << endl;

        requestType = serviceRequestMessage->requestType;


        // Add the client's domainName to a table

        int foundIndex = findAClient(serviceRequestMessage->requestID);

        if(foundIndex == -1)
        {
            cout << "Registering a new user" << endl;
            registerAClient(serviceRequestMessage->requestID);

            // Change the request type to 3 for response
            serviceRequestMessage->requestType = 3;
            write (connection, (char *) serviceRequestMessage, sizeof(serviceRequest));
        }
        else
        {

            cout << "Found client with Request ID :" << serviceRequestMessage->requestID<< endl;

            if(serviceRequestMessage->requestType == 1)
            {
                cout << "Client sent exiting requestType. Unregistering the client" << endl;
                unregisterAClient(foundIndex);
                serviceRequestMessage->requestType = 3;
                write (connection, (char *) serviceRequestMessage, sizeof(serviceRequest));

                close(connection);
                // for time being we don't want to quit the server;
            }
            else
            {

                // change the requestType to 3 before writing back because 3=response
                serviceRequestMessage->requestType = 3;
                write (connection, (char *) serviceRequestMessage, sizeof(serviceRequest));
            }
        }
    } // while

    free(serviceRequestMessage);

}


/* Returns index where it is found, -1 otherwise */
int findAClient(int requestID)
{
    int i;
    int index = -1;
    for (i = 0; i < MAXCLIENT; i++)
    {
        if(clientIds[i] == requestID)
        {
            index = i;
            break;
        }
    }

    return index;
}

/* Adds client to the list */
void registerAClient(int requestID)
{
    int i;
    int registered = 0;
    for (i = 0; i < MAXCLIENT; i++)
    {
        if(clientIds[i] == 0)
        {
            clientIds[i] = requestID;
            registered = 1;
            break;
        }
    }

    if(!registered)
        cout << "Could not register the client" << endl;
}

/* Remove the client from the list */
void unregisterAClient(int index)
{
    clientIds[index] = 0;
}
