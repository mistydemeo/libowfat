#ifndef SOCKET_H
#define SOCKET_H

#include "uint16.h"
#include "uint32.h"

int socket_tcp4(void);
int socket_udp4(void);
int socket_tcp6(void);
int socket_udp6(void);

#define socket_tcp() socket_tcp4()
#define socket_udp() socket_udp4()

int socket_connect4(int s,const char* ip,uint16 port);
int socket_connect6(int s,const char* ip,uint16 port,uint32 scope_id);
int socket_connected(int s);
int socket_bind4(int s,const char* ip,uint16 port);
int socket_bind4_reuse(int s,const char* ip,uint16 port);
int socket_bind6(int s,const char* ip,uint16 port,uint32 scope_id);
int socket_bind6_reuse(int s,const char* ip,uint16 port,uint32 scope_id);
int socket_listen(int s,unsigned int backlog);
int socket_accept4(int s,char* ip,uint16* port);
int socket_accept6(int s,char* ip,uint16* port,uint32* scope_id);
int socket_recv4(int s,char* buf,unsigned int len,char* ip,uint16* port);
int socket_recv6(int s,char* buf,unsigned int len,char* ip,uint16* port,uint32* scope_id);
int socket_send4(int s,const char* buf,unsigned int len,const char* ip,uint16 port);
int socket_send6(int s,const char* buf,unsigned int len,const char* ip,uint16 port,uint32 scope_id);
int socket_local4(int s,char* ip,uint16* port);
int socket_local6(int s,char* ip,uint16* port,uint32* scope_id);
int socket_remote4(int s,char* ip,uint16* port);
int socket_remote6(int s,char* ip,uint16* port,uint32* scope_id);

/* enable sending udp packets to the broadcast address */
int socket_broadcast(int s);
/* join a multicast group on the given interface */
int socket_mcjoin4(int s,const char* groupip,const char* _interface);
int socket_mcjoin6(int s,const char* groupip,int _interface);
/* leave a multicast group on the given interface */
int socket_mcleave4(int s,const char* groupip);
int socket_mcleave6(int s,const char* groupip);
/* set multicast TTL/hop count for outgoing packets */
int socket_mcttl4(int s,char hops);
int socket_mchopcount6(int s,char hops);
/* enable multicast loopback */
int socket_mcloop4(int s,char hops);
int socket_mcloop6(int s,char hops);

void socket_tryreservein(int s,int size);

const char* socket_getifname(uint32 _interface);
uint32 socket_getifidx(const char* ifname);

int noipv6;

#ifdef __MINGW32__
#include <winsock2.h>
#include <ws2tcpip.h>

#define EWOULDBLOCK WSAEWOULDBLOCK
#define EINPROGRESS WSAEINPROGRESS
#define EALREADY WSAEALREADY
#define ENOTSOCK WSAENOTSOCK
#define EDESTADDRREQ WSAEDESTADDRREQ
#define EMSGSIZE WSAEMSGSIZE
#define EPROTOTYPE WSAEPROTOTYPE
#define ENOPROTOOPT WSAENOPROTOOPT
#define EPROTONOSUPPORT WSAEPROTONOSUPPORT
#define ESOCKTNOSUPPORT WSAESOCKTNOSUPPORT
#define EOPNOTSUPP WSAEOPNOTSUPP
#define EPFNOSUPPORT WSAEPFNOSUPPORT
#define EAFNOSUPPORT WSAEAFNOSUPPORT
#define EADDRINUSE WSAEADDRINUSE
#define EADDRNOTAVAIL WSAEADDRNOTAVAIL
#define ENETDOWN WSAENETDOWN
#define ENETUNREACH WSAENETUNREACH
#define ENETRESET WSAENETRESET
#define ECONNABORTED WSAECONNABORTED
#define ECONNRESET WSAECONNRESET
#define ENOBUFS WSAENOBUFS
#define EISCONN WSAEISCONN
#define ENOTCONN WSAENOTCONN
#define ESHUTDOWN WSAESHUTDOWN
#define ETOOMANYREFS WSAETOOMANYREFS
#define ETIMEDOUT WSAETIMEDOUT
#define ECONNREFUSED WSAECONNREFUSED
#define ELOOP WSAELOOP
#define EHOSTDOWN WSAEHOSTDOWN
#define EHOSTUNREACH WSAEHOSTUNREACH
#define EPROCLIM WSAEPROCLIM
#define EUSERS WSAEUSERS
#define EDQUOT WSAEDQUOT
#define ESTALE WSAESTALE
#define EREMOTE WSAEREMOTE
#define EDISCON WSAEDISCON

#endif

#endif
