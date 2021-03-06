#ifndef SOCKET_CONNECTOR_H
#define SOCKET_CONNECTOR_H
#include <socket_connection/receiver.h>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <aio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <fcntl.h>
#include <errno.h>
#include <vector>
#include <sys/select.h>
#include <socket_connection/socket_listener.h>


namespace socket_connection{
/**
 * @brief The SocketConnector class A class that holds basic unix stuff for socket-connection
 */
class SocketConnector{
    static int iDCounter;
    int iD;
    bool connected;
    Receiver receiver;

    int bufferSize;
    int fileDescriptor;

protected:
    /**
     * @brief timeout the timeout for the connection, by default zero
     */
    timeval timeout;
    /**
     * file descriptor set
     */
    fd_set fds;
public:
    struct sockaddr_in socket_addr;
    /**
     * stores the size of the address of the client, used to accept calls
     */
    socklen_t adress_length;
    /**
     * @brief SocketConnector
     * @param buffersize by default 1024000
     */
    SocketConnector(int buffersize = 1024000);
    /** Just for later handling, not required by the system*/
    std::string address;
    /** Just for later handling, not required by the system*/
    int port;

    /**
     * @brief isConnected
     * @return true if the connection is established
     */
    bool isConnected();
    /**
     * @brief setConnected call this method if the connection was established or cut
     * @param state
     */
    void setConnected(bool state);
    /**
     * @brief getReceiver the buffer-wrapper to receive messages
     * @return
     */
    Receiver& getReceiver();

    /**
     * @brief setFileDescriptor used to receive and send messages
     * @param f
     */
    void setFileDescriptor(int f);
    /**
     * @brief close closes the File Descriptor
     */
    void close();

    /**
     * @brief getFileDescriptor used to receive and send messages
     * @return
     */
    int getFileDescriptor();

    friend bool operator==(const SocketConnector& lhs, const SocketConnector& rhs){
            return lhs.fileDescriptor == rhs.fileDescriptor;
        }

    /**
     * @brief SocketConnector::sendMessage write a message into the given fileDescriptor
     * @param buffer
     * @param bytesToSend
     * @return
     */
    bool sendMessage(const void *buffer, int bytesToSend,bool addSize = true);
    int getID() const;

};
}
#endif /* SOCKET_CONNECTOR_H */
