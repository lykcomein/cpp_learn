#ifndef _SOCKET_TEST1_H_
#define _SOCKET_TEST1_H_
#include <boost/asio.hpp>
#include <iostream>

extern int client_end_point();
extern int server_and_point();
extern int create_tcp_socket();
extern int create_acceptor_socket();
extern int bind_acceptor_socket();
extern int connect_to_end();
extern int dns_conect_to_end();
#endif