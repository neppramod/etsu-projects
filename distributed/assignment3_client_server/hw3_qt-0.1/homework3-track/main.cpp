/**
* main.cpp
* A simple tcp/ip socket-based server client
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
#include <string>
#include <stdio.h>
#include <fstream>

// App include's
#include "message.h"
#include "communication.h"
#include "client.h"
#include "constants.h"
#include "stringtok.h"
#include "neighbors.h"
#include "utility.h"

#define SERVER_LIST_FILE_NAME "neighbors"
// For threading
#include<pthread.h>
void *server_handler (void *sock_desc);
void *client_handler(void *sock_desc);

char *nodes[MAXNODES];  // Keeps a table of clients
int node_index = 0;     // Keep track of node
neighbors neighbors_list[BUFFER_SIZE];

using namespace std;

void update_list(char *payload)
{
    char **tokens;
    tokens = str_split(payload, ';');
    Utility utility;

    if (tokens)
    {
        int i, j;
        char save_tokens[81];
        char new_neighbors[1024];

        for (i = 1; *(tokens + i); i+=2)
        {
            strcpy(save_tokens,"");
            strcat(save_tokens, *(tokens + i));
            strcat(save_tokens, " ");
            strcat(save_tokens, *(tokens + (i+1)));

            int found = 0;
            for (j = 0; j < node_index; j++) {
                char neighbor_address_line[81];
                strcpy(neighbor_address_line,"");
                strcat(neighbor_address_line, neighbors_list[j].host_name);
                strcat(neighbor_address_line, " ");
                strcat(neighbor_address_line, neighbors_list[j].host_port);


                if (strcmp(neighbor_address_line, save_tokens) == 0) {
                    cout << "Server: " << neighbor_address_line << " exists" << endl;
                    found = 1;
                    break;
                }
            }

            if (!found) {
                strcat(new_neighbors, save_tokens);
                strcat(new_neighbors, "\n");
            }
        }

        cout << "New neighbors " << new_neighbors << endl;
        cout<< "Entire List " << endl;
        for (j = 0; j < node_index; j++) {
            cout << neighbors_list[j].host_name << " " << neighbors_list[j].host_port << endl;
        }
        cout << new_neighbors;

        utility.saveFile(NEIGHBORS_LIST_FILE_NAME, new_neighbors);

    }
}

int main()
{
    int sockdesc;            // Socket descriptor
    char portnum[BUFFER_SIZE];        // Port number
    int upper_bound_portnum; // upper bound port numbers from file
    ifstream port_file;      // File to read port number (portnums)
    ifstream neighbors_list_input_file;  // File to read server list (neighbors)
    int connection;          // Return value from accept()

    Communication communication;            // Communication class for doing the communication
    pthread_t *other_client_threads;        // Thread for serving multiple clients
    pthread_t *client_thread;               // Thread for creating its own client



    // Get the port number from file called portnums
    port_file.open(PORT_FILE_NAME);
    while (port_file >> portnum >> upper_bound_portnum);

    cout << "Server: Port " << portnum << " in use" << endl;
    int portint = communication.create_server_connection(&sockdesc, portnum, upper_bound_portnum);

    // Display a list of known neighbors
    cout << "Connect to the neighbors (use index) :" << endl;
    cout << "-----------------------------" << endl;

    neighbors_list_input_file.open(NEIGHBORS_LIST_FILE_NAME);

    if (neighbors_list_input_file.is_open())
    {
        char neighbors_host[BUFFER_SIZE];
        char neighbors_port[BUFFER_SIZE];
        char neighbors_address[CLIENT_DOMAIN_NAME_LENGTH];
        int i = 0;

        cout << "0. none" << endl;
        while(neighbors_list_input_file >> neighbors_host >> neighbors_port)
        {
            cout << (i+1) << ". " << neighbors_host << ":" << neighbors_port << endl;
            //sprintf(neighbors_address, "%s %d", neighbors_host, neighbors_port);
            i++;
            strcpy(neighbors_list[node_index].host_name, neighbors_host);
            strcpy(neighbors_list[node_index].host_port, neighbors_port);
            node_index++;
            //nodes[node_index++] = strdup(neighbors_address);
        }
    }
    else
    {
        cout << "Server: Could not open neighbors" << endl;
    }

    cout << "-----------------------------" << endl;


    // Create a client thread after starting the server
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


    // Server loop to handle multiple clients
    for (;;)
    {
        connection = communication.client_connection_accept(&sockdesc);

        if (connection >= 0)
        {
            // Create a new thread
            other_client_threads = (pthread_t *) malloc(sizeof(pthread_t));

            if (pthread_create
                    (other_client_threads, NULL, &server_handler, (void *) &connection) < 0)
            {
                cout << "Server: Error in creating thread" << endl;
            }
            else
            {
                cout << "Server: Thread creation successful" << endl;
                continue;
            }
        }
    }

    // Close the connection
    close(connection);
    return 0;
}

void *client_handler(void *portintvr)
{
    int portint = *((int *)portintvr);
    Client client;
    client.start(portint);
}

void *server_handler(void *conn)
{
    int value;                                  // Return value from read
    serviceRequest *serviceRequestMessage;      // Service request message object
    int connection = *((int *) conn);
    int requestType = 0;  // Simple variable for serviceRequestMessage->requestType
    ifstream neighbors_list_input_file;  // File to read server list (neighbors)
    ofstream neighbors_list_output_file; // File to write server list (neighbors)


    // Wait while request type 1 (exit) is not requested from client
    while(requestType != CLIENT_EXIT_REQUEST) {
        serviceRequestMessage = (serviceRequest *) malloc(sizeof(serviceRequest));
        value = read (connection, (char *) serviceRequestMessage, sizeof (serviceRequest));
        cout << "Server: client sent: " << serviceRequestMessage->requestString << endl;

        if(value != sizeof (serviceRequest))
        {
            cout << "Server: Error, read( ) returned a bad value" << endl;
        }

        requestType = serviceRequestMessage->requestType;
        cout << "Server: Client requestType: " << requestType << endl;

        if (requestType == CLIENT_QUERY_REQUEST) {

            // Change serviceRequestMessage's requestType to SERVER_RESPONSE_REQUEST (3)
            serviceRequestMessage->requestType = SERVER_RESPONSE_REQUEST;
            strcpy(serviceRequestMessage->requestString, "alive");

            write (connection, (char *) serviceRequestMessage, sizeof(serviceRequest));
        } else if (requestType == CLIENT_PAYLOAD_SHARE) {
            cout << "Server: (payload) : " << serviceRequestMessage->payload << endl;

            update_list(serviceRequestMessage->payload);

        } else if (requestType == CLIENT_EXIT_REQUEST) {
            close(connection);
        }


    } // while exits
}


