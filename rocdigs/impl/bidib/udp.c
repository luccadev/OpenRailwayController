/*
 Rocrail - Model Railroad Software

Copyright (c) 2002-2015 Robert Jan Versluis, Rocrail.net

 All rights reserved.
*/

#include "rocdigs/impl/bidib_impl.h"

#include "rocdigs/impl/bidib/udp.h"

#include "rocs/public/trace.h"
#include "rocs/public/mem.h"
#include "rocs/public/str.h"
#include "rocs/public/strtok.h"
#include "rocs/public/thread.h"
#include "rocs/public/serial.h"
#include "rocs/public/system.h"

#include "rocrail/wrapper/public/DigInt.h"

#include "rocdigs/impl/bidib/bidib_messages.h"
#include "rocdigs/impl/bidib/bidibutils.h"


Boolean udpInit( obj inst ) {
  iOBiDiBData data = Data(inst);

  TraceOp.trc( name, TRCLEVEL_INFO, __LINE__, 9999, "host    = %s", wDigInt.gethost( data->ini ) );
  TraceOp.trc( name, TRCLEVEL_INFO, __LINE__, 9999, "port    = %d", wDigInt.getport( data->ini ) );
  TraceOp.trc( name, TRCLEVEL_INFO, __LINE__, 9999, "----------------------------------------" );

  data->rwUDP = SocketOp.inst( wDigInt.gethost(data->ini), wDigInt.getport(data->ini), False, True, False );
  if( SocketOp.bind(data->rwUDP) ) {
    data->commOK = True;
  }

  return True;
}


Boolean udpConnect( obj inst ) {
  iOBiDiBData data = Data(inst);
  return False;
}


void udpDisconnect( obj inst ) {
  iOBiDiBData data = Data(inst);
  data->commOK = False;
}


int udpRead ( obj inst, unsigned char *msg ) {
  iOBiDiBData data = Data(inst);
  char buffer[256];
  int size = SocketOp.recvfrom( data->rwUDP, buffer, 256, NULL, NULL );;
  if( size > 0 ) {
    MemOp.copy( msg, buffer, size );
    size = bidibDeEscapeMessage(msg, size);
    TraceOp.dump ( "bidibRead", TRCLEVEL_BYTE, (char*)msg, size );
    byte crc = bidibCheckSum(msg, size );
    if( crc != 0 ) {
      TraceOp.trc( "bidibserial", TRCLEVEL_EXCEPTION, __LINE__, 9999, "invalid checksum" );
      return 0;
    }
    return size;
  }
  return 0;
}


Boolean udpWrite( obj inst, unsigned char *path, unsigned char code, unsigned char* pdata, int datalen, void* node ) {
  iOBiDiBData data = Data(inst);
  int   size = 0;
  byte  msg[256];

  int msgidx  = 0;
  int dataidx = 0;

  /*                  pathidx: 0  1  2  3
   * Addr can be 4 bytes long. XX XX XX XX */
  for( msgidx = 0; msgidx < 4; msgidx++ ) {
    msg[1+msgidx] = path[msgidx]; // address
    if( msg[1+msgidx] == 0 )
      break;
  }

  msgidx += 2; // point to sequence offset

  if( node != NULL )
    msg[msgidx] = ((iOBiDiBNode)node)->seq++;
  else
    msg[msgidx] = 0;
  msgidx++;

  msg[msgidx] = code;
  msgidx++;

  if( pdata != NULL ) {
    for( dataidx = 0; dataidx < datalen; dataidx++ )
      msg[msgidx+dataidx] = pdata[dataidx]; // address
  }

  size = msgidx+dataidx;
  msg[0] = size-1;

  TraceOp.dump ( "preWrite", TRCLEVEL_BYTE, (char*)msg, size );
  size = bidibMakeMessage(msg, size);

  data->commOK = SocketOp.sendto( data->rwUDP, (char*)msg, size, NULL, 0 );
  return data->commOK;
}


Boolean udpAvailable( obj inst ) {
  iOBiDiBData data = Data(inst);
  int packetSize = SocketOp.recvfrom( data->rwUDP, NULL, 256, NULL, NULL );
  return packetSize > 0 ? True:False;
}

