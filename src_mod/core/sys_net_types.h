#ifndef __SYS_NET_TYPES_H__
#define __SYS_NET_TYPES_H__

// This file contains types used in sys_net.h

typedef unsigned char byte;

typedef enum netadrtype_t
{
    NA_BAD = 0, // an address lookup failed
    NA_BOT = 0,
    NA_LOOPBACK = 2,
    NA_BROADCAST,
    NA_IP,
    NA_IP6,
    NA_TCP,
    NA_TCP6,
    NA_MULTICAST6,
    NA_UNSPEC,
    NA_DOWN
} netadrtype_t;

typedef enum netsrc_t
{
    NS_CLIENT = 0,
    NS_SERVER
} netsrc_t;

typedef struct netadr_t
{
    netadrtype_t type;
    int scope_id;
    unsigned short port;
    unsigned short pad;
    int sock; //Socket FD. 0 = any socket
    union {
        byte ip[4];
        byte ipx[10];
        byte ip6[16];
    };
} netadr_t;

typedef enum tcpclientstate_t
{
    TCP_AUTHWAIT = 0,
    TCP_AUTHNOTME,
    TCP_AUTHBAD,
    TCP_AUTHAGAIN,
    TCP_AUTHSUCCESSFULL
} tcpclientstate_t;

#endif
