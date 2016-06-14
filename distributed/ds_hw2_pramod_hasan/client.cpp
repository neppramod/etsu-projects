#include "client.h"
#include "communication.h"
#include "message.h"

#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <iostream>
#include <fstream>
#include <string.h>


#define SERVER_LIST_FILE_NAME "neighbors"

// 0=new client, 1=exit, 2=query, 3=response
enum {
    CLIENT_NEW_CONNECTION_REQUEST,
    CLIENT_EXIT_REQUEST,
    CLIENT_QUERY_REQUEST,
    SERVER_RESPONSE_REQUEST
};
//#define CLIENT_NEW_CONNECTION_REQUEST_TYPE 0 // 0=new client, 1=exit, 2=query, 3=response
#define CLIENT_DOMAIN_NAME_LENGTH 256  // client's domain name size from serviceRequest
#define SERVER_NODE_LIST_SIZE 23040 // 256x90

using namespace std;

Client::Client()
{
}

/* Start the client. portint is this server's used port */
void Client::start(int srv_port_num)
{

    int sockdesc;          // Socket number (*not* the port number)
    char hostname[81];       // Server name
    char portnum[81];        // Server port number (note: char* not int)
    int value;               // Return value from read()
    ifstream server_list_input_file;  // File to read server list (neighbors)
    ofstream server_list_output_file; // File to write server list (neighbors)

    string clientquery;

    serviceRequest serviceRequestMessage; // Record for data
    Communication *communication = new Communication();	      // Communication class for doing the communication

    /* Get hostname and portnum from file or by assigning to user */
    server_list_input_file.open(SERVER_LIST_FILE_NAME);

    /* Check if neighbors is empty */
    std::streampos pos = server_list_input_file.tellg();
    server_list_input_file.seekg (0, server_list_input_file.end);
    bool neighbors_empty = !server_list_input_file.tellg(); // true if empty file
    server_list_input_file.seekg (pos, server_list_input_file.beg); //restore stream position

    int connection = -1;

    // create the socket descriptor first
    communication->create_socket_descriptor(&sockdesc);

    // Try to connect using neighbors file
    if(server_list_input_file.is_open() && !neighbors_empty) {

        cout << "Client: Reading from neighbors" << endl;

        while (server_list_input_file >> hostname >> portnum) {

            if((hostname[0] != '\0') && (portnum[0] != '\0')) {
                connection = communication->create_client_connection(&sockdesc, hostname, portnum);                
                if (connection == 0) {
                    cout << "Client: Connected to " << hostname << " " << portnum << endl;
                    break;
                }
            }

        }
    }
    server_list_input_file.close();

    if (connection == -1) {
        cout << "Client: Enter hostname and port eg 192.168.0.255 3100 (below on prompt)" << endl;
        cin >> hostname >> portnum;
        connection = communication->create_client_connection(&sockdesc, hostname, portnum);
    }

    // This check not needed I guess
    if((hostname[0] == '\0') || (portnum[0] == '\0')) {
        cout << "Client: Hostname and portnumber could not be defined. Exiting.." << endl;
        exit(1);
    }

    // Create initial message to send hostname and port
    serviceRequestMessage.requestType = CLIENT_NEW_CONNECTION_REQUEST; // new request
    gethostname(serviceRequestMessage.domainName, CLIENT_DOMAIN_NAME_LENGTH); // put domainName of client
    serviceRequestMessage.portNumber = srv_port_num;

    // Send the message to the server
    write(sockdesc, (char *)&serviceRequestMessage, sizeof(serviceRequest));

    // Read some message from server, prompt for query or quit
    // On quit save the list from server

    while(serviceRequestMessage.requestType != 1) {
        //cout << "Clientquery: " << clientquery << endl << endl;
        cout << "Client: Enter text to query, 'e' to exit" << endl;
        cout << "Client : ";
        //cin >> clientquery;
        getline(cin, clientquery);

        /* Want to read different struct if it is CLIENT_EXIT_REQUEST requestId, to save neighbors */
        if(clientquery[0] == 'e' && clientquery[1] == '\0') {
            serviceRequestMessage.requestType = CLIENT_EXIT_REQUEST;

            // Send the message to the server
            write(sockdesc, (char *)&serviceRequestMessage, sizeof(serviceRequest));

            // TODO: Cleanup, make the size of buffer bigger.
            char *server_list_message = (char *)malloc(SERVER_NODE_LIST_SIZE);
            // Read the value from server to save to file
            value = read(sockdesc, (char *)server_list_message, SERVER_NODE_LIST_SIZE);

            cout << "Client: Received this list from server" << endl << server_list_message << endl;


//            // Now, save this list to neighbors file
//            cout << "Client: Saving list to " << SERVER_LIST_FILE_NAME << endl;
//            server_list_output_file.open(SERVER_LIST_FILE_NAME);
//            server_list_output_file << server_list_message;
//            server_list_output_file.close();

//            free(server_list_message);
            char *oneline1 = (char *)malloc(SERVER_NODE_LIST_SIZE);
            char *oneline2 = (char *)malloc(SERVER_NODE_LIST_SIZE);
            int hostname_exists = 0;
            server_list_input_file.open(SERVER_LIST_FILE_NAME);
            while (server_list_input_file >> oneline1>>oneline2) {
                strcat(oneline1," ");
                strcat(oneline1, oneline2);

              if (strcmp(server_list_message,oneline1) == 0) {
                  hostname_exists = 1;
                  break;
                }
            }
            server_list_input_file.close();

            if(!hostname_exists) {
                        // Now, save this list to neighbors file
                        cout << "Client: Saving list to " << SERVER_LIST_FILE_NAME << endl;
                        server_list_output_file.open(SERVER_LIST_FILE_NAME, std::ios::app);
                        server_list_output_file << server_list_message;
                        server_list_output_file << '\n';
                        server_list_output_file.close();

                        free(server_list_message);
            }

        } else {
            serviceRequestMessage.requestType = CLIENT_QUERY_REQUEST;
            strcpy(serviceRequestMessage.message, clientquery.c_str());

            // Send the message to the server
            write(sockdesc, (char *)&serviceRequestMessage, sizeof(serviceRequest));

            // Read the value from server
            value = read(sockdesc, (char *) &serviceRequestMessage, sizeof(serviceRequest));

            // Check the return value
            if (value != sizeof(serviceRequestMessage))
                cout << "Client: Error: message received was not the correct size" << endl;

            // Display value received from server
            cout << "Client: Server sent me back request type: " << serviceRequestMessage.requestType << endl;
            cout << "Client: Server sent me back '" << serviceRequestMessage.message << "'" << endl;
        }
    }

    // Close the socket
    close(sockdesc);

}
