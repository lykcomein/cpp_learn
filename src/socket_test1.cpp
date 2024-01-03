//socket create connect test in windows
#include <iostream>
#include "inc/socket_test1.h"

using namespace boost;

int client_end_point()
/*
生成终端节点(通过IP地址和端口号生成)(客户端)
终端节点：用来通信的端对端节点；
*/
{
  std::string raw_ip_address = "127.0.0.1";
  unsigned short port_num = 3333;

  boost::system::error_code ec;

  asio::ip::address ip_address = asio::ip::address::from_string(raw_ip_address, ec);

  if(ec.value() != 0){
    std::cout << "Failed to parse the IP address. Error code =  "<< ec.value() << ". Message: " << ec.message();

    //生成端点
    asio::ip::tcp::endpoint ep(ip_address, port_num);

  }
  return 0;
}

int server_end_point()
/*
服务器端创建端口
*/
{
  unsigned short port_num = 3333; //端口号
  asio::ip::address ip_address = asio::ip::address_v6::any();

  asio::ip::tcp::endpoint ep(ip_address, port_num);

  return 0;
}

int create_tcp_socket()
/*
创建socket
*/
{
  //一共四步
  asio::io_context ios;//创建上下文iocontext

  asio::ip::tcp protocol = asio::ip::tcp::v6(); //选择协议

  asio::ip::tcp::socket sock(ios);//生成socket

  boost::system::error_code ec;

  sock.open(protocol, ec);//打开socket

  if(ec.value() != 0){
    std::cout << "Failed to open thr socket! Error code = " << ec.value() << ". Message: " << ec.message() << std::endl;
    return ec.value();
  }

  return 0;

}

int create_acceptor_socket()
/*
服务端生成一个socket来接收连接
*/
{
  asio::io_context ios;

  asio::ip::tcp protocol = asio::ip::tcp::v6();

  asio::ip::tcp::acceptor acceptor(ios);

  boost::system::error_code ec;

  acceptor.open(protocol, ec);

  if(ec.value() != 0){

    std::cout << "Failed to open the acceptor socket!" << "Error code = " << ec.value() << ". Message: " << ec.message() << std::endl;

    return ec.value();
  }

  return 0;
}

int bind_acceptor_socket()
/*
绑定acceptor生成的socket到指定的端点；
所有连接这个端点的连接都可以被接收到。
*/
{
  unsigned short port_num = 3333;
  asio::ip::tcp::endpoint ep(asio::ip::address_v4::any(), port_num);

  asio::io_context ios;

  asio::ip::tcp::acceptor acceptor(ios, ep.protocol());

  boost::system::error_code ec;

  acceptor.bind(ep, ec);

  if(ec.value() != 0){
        std::cout << "Failed to bind the acceptor socket." << "Error code = " << ec.value() << ". Message: " << ec.message() << std::endl;
        return ec.value();
  }
  return 0;
}

int connect_to_end()
/*
客户端连接指定的端点
*/
{
  std::string raw_ip_address = "127.0.0.1";
  unsigned short port_num = 3333;

  try{
    asio::ip::tcp::endpoint ep(asio::ip::address::from_string(raw_ip_address), port_num);

    asio::io_context ios;

    asio::ip::tcp::socket sock(ios, ep.protocol());

    sock.connect(ep);

  }
  catch(system::system_error& e){
    std::cout << "Error occured! Error code = " << e.code() << ". Message: " << e.what() << std::endl;

    return e.code().value();
  }
  return 0;
}

int accept_new_connect()
/*
服务器接受连接
*/
{
  const int BACKLOG_SIZE = 30;

  unsigned short port_num = 3333;

  asio::ip::tcp::endpoint ep(asio::ip::address_v4::any(), port_num);

  asio::io_context ios;

  try{
    asio::ip::tcp::acceptor acceptor(ios, ep.protocol());

    acceptor.bind(ep);

    acceptor.listen(BACKLOG_SIZE);

    asio::ip::tcp::socket sock(ios);

    acceptor.accept(sock);
  }
  catch (system::system_error& e) {
      std::cout << "Error occured! Error code = " << e.code() << ". Message: " << e.what() << std::endl;
      return e.code().value();
  }

  return 0;

}