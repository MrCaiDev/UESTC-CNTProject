/**
 * @name: net.cpp
 * @author: MrCai
 * @description: 网元应用层。
 */
#include <iostream>
#include <winsock2.h>
#include "include/param.h"
#include "include/socket.cpp"
#include "include/coding.cpp"
using namespace std;

int main(int argc, char *argv[]) {
    cout << "------------------Net------------------" << endl;
    int port = 0;
    int mode = 0;
    char buffer[MAX_BUFFER_SIZE];
    string message = "";

    WSADATA wsaData = initWSA();
    CNTSocket sock(SOCK_DGRAM);

    cout << "APP port at: ";
    cin >> port;
    sock.bindUpperPort(port);

    cout << "NET port at: ";
    cin >> port;
    sock.bindSelfPort(port);

    cout << "PHY port at: ";
    cin >> port;
    sock.bindLowerPort(port);

    while (true) {
        cout << "---------------------------------------" << endl;
        cout << "Select mode: (1::Send, 2::Recv)" << endl << ">>> ";
        cin >> mode;
        if (mode == 1) {
            cout << "Message to send: ";
            cin >> message;
            sock.sendToLower(message);
            message.clear();
        } else if (mode == 2) {
            sock.recvFromUpper(buffer);
            cout << "Message received: " << buffer << endl;
            memset(buffer, 0, MAX_BUFFER_SIZE);
        } else {
            cout << "Invalid option!" << endl;
        }
    }
}
