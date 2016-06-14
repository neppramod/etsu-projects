/**
  * main.cpp
  * A simple tcp/ip socket-based server
  */

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
#include <fstream>

// App include's
#include "message.h"
#include "communication.h"
#include "client.h"

#define SERVER_LIST_FILE_NAME "neighbors"
// For threading
#include<pthread.h>
void *server_handler (void *sock_desc);
void *client_handler(void *sock_desc);

// 0=new client, 1=exit, 2=query, 3=response
enum {
    CLIENT_NEW_CONNECTION_REQUEST,
    CLIENT_EXIT_REQUEST,
    CLIENT_QUERY_REQUEST,
    SERVER_RESPONSE_REQUEST
};

// Default port number if user does not specify it
#define PORT_FILE_NAME "portnums"
#define MAXNODES 80
#define CLIENT_DOMAIN_NAME_LENGTH 256  // client's domain name size from serviceRequest

using namespace std;

char *nodes[MAXNODES]; // Keeps a table of clients.
int node_index = 0;    // Keep track of node

int main ()
{

    int sockdesc;			// Socket descriptor
    char portnum[81];		// Port number
    int upper_bound_portnum; // upper bound port numbers from file
    ifstream port_file;         // File to read port number (portnums)
    int connection;			// Return value from accept( )

    Communication communication;	      // Communication class for doing the communication
    pthread_t *thread1;         // Thread for serving multiple clients
    pthread_t *client_thread;   // Thread for creating its own client


    // Get the port number from file called portnums
    port_file.open(PORT_FILE_NAME);
    while (port_file >> portnum >> upper_bound_portnum);

    cout << "Server: Port " << portnum << " in use" << endl;
    int portint = communication.create_server_connection(&sockdesc, portnum, upper_bound_portnum);

    /* TODO: Not clear. Add this server's information also in the nodes list for
     * connecting nodes to reconnect to it. Otherwise their neighbors will never contain this node.
     */

    serviceRequest serviceRequestMessage;
    gethostname(serviceRequestMessage.domainName, CLIENT_DOMAIN_NAME_LENGTH);
    char domainInfo[80];
    sprintf(domainInfo, "%s %d", serviceRequestMessage.domainName, portint);
    nodes[node_index++] = strdup(domainInfo);


    /* Create client thread after server start. */
    client_thread = (pthread_t *) malloc (sizeof (pthread_t));

    if (pthread_create
            (client_thread, NULL, &client_handler, (void *) &portint) < 0)
    {
        cout << "Server: Error in creating default client thread" << endl;
    }
    else
    {
        cout << "Server: Default client creation successful" << endl;
    }

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
        //cout << "Server: Calling accept" << endl;

        // Accept a connect, check the returned descriptor
        /*
        connection = accept (sockdesc, NULL, NULL);
        if (connection < 0)
        {
            cout << "Server: Error in accept" << endl;
            exit (0);
        }
        */
        connection = communication.client_connection_accept(&sockdesc);
        if (connection >= 0)
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
                    (thread1, NULL, &server_handler, (void *) &connection) < 0)
            {
                cout << "Server: Error in creating thread" << endl;
            }
            else
            {
                //*/
                cout << "Server: Thread creation successful" << endl;
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


void *client_handler(void *portintvr)
{
    int portint = *((int *)portintvr);
    Client client;
    client.start(portint);
}

void *server_handler (void *conn)
{
    int value; // return value from read
    serviceRequest *serviceRequestMessage; // Service request message object
    int connection = *((int *) conn);
    int requestType = 0;  // Simple variable for serviceRequestMessage->requestType
    ifstream server_list_input_file;  // File to read server list (neighbors)
    ofstream server_list_output_file; // File to write server list (neighbors)

    /* Make sure to send a char array list of nodes when requestType == 1 */
    while(requestType != 1) {
        serviceRequestMessage = (serviceRequest *) malloc(sizeof(serviceRequest));
        value = read (connection, (char *) serviceRequestMessage, sizeof (serviceRequest));

        if(value != sizeof (serviceRequest))
        {
            cout << "Server: Error, read( ) returned a bad value" << endl;
        }
        requestType = serviceRequestMessage->requestType;

        cout << "Server: Client requestType: " << requestType << endl;

        // Change serviceRequestMessage's requestType to SERVER_RESPONSE_REQUEST (3)
        serviceRequestMessage->requestType = SERVER_RESPONSE_REQUEST;

        if (requestType == CLIENT_QUERY_REQUEST) {

            cout << "Server: Client message: " << serviceRequestMessage->message << endl;
            write (connection, (char *) serviceRequestMessage, sizeof(serviceRequest));

        } else if (requestType == CLIENT_EXIT_REQUEST){

//            char *server_list_message = (char *)malloc(80*256);

//            // prepare a list separated by \n to write to neighbors
//            int i;
//            for (i = 0; i < node_index-1; i++) {
//                strcat(server_list_message, nodes[i]);
//                strcat(server_list_message, "\n");
//            }
//            // trick for not putting \n at end
//            if (i >= 0)
//                strcat(server_list_message, nodes[i]);

//            //server_list_message = strdup("This is just a list");

            write(connection, (char *) nodes[0], 256);

            close(connection);

        } else if (requestType == CLIENT_NEW_CONNECTION_REQUEST) {

            cout << "Server: Client sent server's domainname: " << serviceRequestMessage->domainName
                 << " Port: " << serviceRequestMessage->portNumber << endl;

            /* Save unique information to node */
            char domainInfo[80];
            sprintf(domainInfo, "%s %d", serviceRequestMessage->domainName, serviceRequestMessage->portNumber);

            /* Check the domain name and port of requesting client's server, add if new */
            int found = 0;
            for (int i = 0; i < node_index; i++) {
                if (strcmp(domainInfo, nodes[i]) == 0) {
                    found = 1;
                    cout << "Server: Found previous occurance of node " << nodes[i] << ". Not adding to list " << endl;
                }
            }
            if (!found){
                nodes[node_index++] = strdup(domainInfo);

                cout << "Server: Saving list to " << SERVER_LIST_FILE_NAME << endl;
                server_list_output_file.open(SERVER_LIST_FILE_NAME, std::ios::app);
                server_list_output_file << nodes[node_index-1];
                server_list_output_file << '\n';
                server_list_output_file.close();
            }

        } // else if

    }

    free(serviceRequestMessage);
}


