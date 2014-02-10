#include "Acceptor.h"

#include "TcpStream.h"

#include <sys/socket.h>

Acceptor::Acceptor(const InetAddress& listenAddr)
  : listenSock_(Socket::createTcp())
{
  listenSock_.bindOrDie(listenAddr);
  listenSock_.listenOrDie();
}

TcpStreamPtr Acceptor::accept()
{
  // FIXME: use accept4
  int sockfd = ::accept(listenSock_.fd(), NULL, NULL);
  if (sockfd >= 0)
  {
    return TcpStreamPtr(new TcpStream(Socket(sockfd)));
  }
  else
  {
    return TcpStreamPtr();
  }
}
