#include "client.h"


using namespace std;

// TODO: Fix client coding style
Client::Client()
{
    communication = new Communication();
    node_index = 0;  // start with index of 0
    connection = -1; // -1 for invalid connection
}

// Create socket descriptor
void Client::createSocketDescriptor()
{
    // create the socket descriptor first
    communication->create_socket_descriptor(&sockdesc);
}

// Initialize neighbor nodes
void Client::initializeNeighboNodes()
{
    ifstream neighbors_list_input_file;  // File to read server list (neighbors)

    /* Read the list from neighbors file and match server's index */
    neighbors_list_input_file.open(NEIGHBORS_LIST_FILE_NAME);

    if (neighbors_list_input_file.is_open())
    {
        char neighbors_host[BUFFER_SIZE];
        char neighbors_port[BUFFER_SIZE];
        //int i = 0;

        while(neighbors_list_input_file >> neighbors_host >> neighbors_port)
        {
            //cout << (i+1) << ". " << neighbors_host << ":" << neighbors_port << endl;
            //sprintf(neighbors_address, "%s %d", neighbors_host, neighbors_port);
            strcpy(neighbors_list[node_index].host_name, neighbors_host);
            strcpy(neighbors_list[node_index].host_port, neighbors_port);
            node_index++;
            //nodes[node_index++] = strdup(neighbors_address);
        }
    }
    else
    {
        cout << "Client: Could not open neighbors" << endl;
    }

}

// Start the client. portint is this server's used port
void Client::start(int srv_port_num)
{

    ofstream neighbors_list_output_file; // File to write server list (neighbors)
    string clientquery;                 // Client request
    char clientquerychar[BUFFER_SIZE];




while (true) {

    // Show the list here

    cout << "Client: (Enter Index)" << endl;
    cout << "Client : ";
    getline(cin, clientquery);

    if (clientquery[0] == '0' && clientquery[1] == '\0')
        cout << "Client: none selected" << endl;
    else {
        // first initialize our nodes variable
        initializeNeighboNodes();
        int neighbor_index = atoi(clientquery.c_str());
        cout << "Client: selected " << neighbor_index << endl;

        if (neighbors_list[neighbor_index-1].host_name == '\0')
        {
            cout << "Invalid index" << endl;
        }
        else
        {
            //char host_port[BUFFER_SIZE];
            //strcpy(host_port, nodes[neighbor_index-1]);
            //cout << "Connecting to " << neighbors_list[neighbor_index-1].host_name << ":" << neighbors_list[neighbor_index-1].host_port << endl;

            // Connect to the server
            createSocketDescriptor();
            connection = communication->create_client_connection(&sockdesc,
                                                                 neighbors_list[neighbor_index-1].host_name,
                    neighbors_list[neighbor_index-1].host_port);

             if (connection == 0) {


                // Ping the server with request type 2
                serviceRequestMessage.requestType = CLIENT_QUERY_REQUEST;
                strcpy(serviceRequestMessage.requestString, "ping");

                write(sockdesc, (char *)&serviceRequestMessage, sizeof(serviceRequest));
                value = read(sockdesc, (char *) &serviceRequestMessage, sizeof(serviceRequest));

                cout << "Client: server sent: " << serviceRequestMessage.requestString << endl;

                // Send the payload
                serviceRequestMessage.requestType = CLIENT_PAYLOAD_SHARE;

                cout << "Node index size " << node_index << endl;

                int node_limit = 3;
                if (node_index < 3)
                    node_limit = node_index;


                char payload_str[1024];

                if (node_index > 0 ) {
                    char tmp_pay_list[BUFFER_SIZE];

                    sprintf(tmp_pay_list, "%d;", node_limit);
                    strcat(payload_str, tmp_pay_list);

                    for (int i = 0; i < node_limit -1; i++) {
                        sprintf(tmp_pay_list, "%s;%s;", neighbors_list[i].host_name, neighbors_list[i].host_port);
                        strcat(payload_str, tmp_pay_list);
                    }

                    sprintf(tmp_pay_list, "%s;%s", neighbors_list[node_limit - 1].host_name, neighbors_list[node_limit - 1].host_port);
                    strcat(payload_str, tmp_pay_list);
                }

                // set the payload
                strcpy(serviceRequestMessage.payload, payload_str);

                cout << "Client: Sending payload " << serviceRequestMessage.payload << endl;
                cout << "Client: to " << neighbors_list[neighbor_index-1].host_name << " "
                     <<  neighbors_list[neighbor_index-1].host_port << endl;

                write(sockdesc, (char *)&serviceRequestMessage, sizeof(serviceRequest));


                // Exit request
                serviceRequestMessage.requestType = CLIENT_EXIT_REQUEST;
                write(sockdesc, (char *)&serviceRequestMessage, sizeof(serviceRequest));


                close(connection);

            }
             else {
                 cout << "Client: Could not connect to the server "<< endl;
             }
        }
    }

} // big while

}


