/*
 Rocrail - Model Railroad Software

Copyright (c) 2002-2015 Robert Jan Versluis, Rocrail.net

 All rights reserved.
*/

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include "rocs/public/rocs.h"
#include "rocs/public/objbase.h"
#include "rocs/public/trace.h"
#include "rocs/public/doc.h"
#include "rocs/public/node.h"
#include "rocs/public/thread.h"
#include "rocs/public/file.h"
#include "rocs/public/mem.h"
#include "rocs/public/str.h"
#include "rocs/public/strtok.h"
#include "rocs/public/cmdln.h"
#include "rocs/public/stats.h"
#include "rocs/public/system.h"
#include "rocs/public/lib.h"

#include "rocrail/impl/app_impl.h"
#include "rocrail/public/clntcon.h"
#include "rocrail/public/control.h"
#include "rocrail/public/model.h"
#include "rocrail/public/http.h"
#include "rocrail/public/snmp.h"

#include "rocrail/wrapper/public/Cmdline.h"
#include "rocrail/wrapper/public/ConCmd.h"
#include "rocrail/wrapper/public/Global.h"
#include "rocrail/wrapper/public/RocRail.h"
#include "rocrail/wrapper/public/Ctrl.h"
#include "rocrail/wrapper/public/Tcp.h"
#include "rocrail/wrapper/public/Trace.h"
#include "rocrail/wrapper/public/SysCmd.h"
#include "rocrail/wrapper/public/AutoCmd.h"
#include "rocrail/wrapper/public/Exception.h"
#include "rocrail/wrapper/public/SvnLog.h"
#include "rocrail/wrapper/public/SvnLogEntry.h"
#include "rocrail/wrapper/public/SrcpCon.h"
#include "rocrail/wrapper/public/Program.h"
#include "rocrail/wrapper/public/SnmpService.h"
#include "rocrail/wrapper/public/Plan.h"
#include "rocrail/wrapper/public/Weather.h"

#include "common/version.h"


static iOApp __appinst = NULL;

static const char* backtrace[10] = {NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL};
static iOMutex __exceptionMutex = NULL;
static void __exception( int level, char* msg ) {
  if( __exceptionMutex == NULL ) {
    /* not thread safe */
    return;
  }
  else if( MutexOp.wait( __exceptionMutex ) ) {
    /* Broadcast to clients. Node6 */
    iONode e = NodeOp.inst( wException.name(), NULL, ELEMENT_NODE );
    int i = 0;
    int len = StrOp.len( msg );
    for( i = 0; i < len; i++ ) {
      if( msg[i] == '\"' )
        msg[i] = ' ';
    }
    wException.settext( e, msg );
    wException.setlevel( e, level );
    AppOp.broadcastEvent( e );

    StrOp.free((char*)backtrace[0]);
    for( i = 0; i < 9; i++ ) {
      backtrace[i] = backtrace[i+1];
    }
    backtrace[9] = StrOp.dup( msg );

    if( __appinst != NULL ) {
      iOAppData data = Data(__appinst);
      if( level == TRCLEVEL_EXCEPTION && data->snmp != NULL ) {
        SNMPOp.exception( data->snmp, msg);
      }
    }

    /* Release the mux. */
    MutexOp.post( __exceptionMutex );
  }
}

static const char** _getBackTrace(void) {
  return backtrace;
}



/*
 ***** OBase functions.
 */
static const char* __id( void* inst ) {
  return NULL;
}

static void* __event( void* inst, const void* evt ) {
  return NULL;
}

static const char* __name(void) {
  return name;
}
static unsigned char* __serialize(void* inst, long* size) {
  return NULL;
}
static void __deserialize(void* inst, unsigned char* a) {
}
static char* __toString(void* inst) {
  if( __appinst != NULL ) {
    iOAppData data = Data(__appinst);
    return NodeOp.toEscString( data->ini );
  }
  else
    return NULL;
}
static void __del(void* inst) {
}
static void* __properties(void* inst) {
  return NULL;
}
static int __count(void) {
  return 1;
}
static struct OBase* __clone( void* inst ) {
  return NULL;
}
static Boolean __equals( void* inst1, void* inst2 ) {
  return False;
}

static const char* _getIniFile(void) {
  TraceOp.trc( name, TRCLEVEL_METHOD, __LINE__, 9999, "_getIniFile()" );
  if( __appinst != NULL ) {
    iOAppData data = Data(__appinst);
    return data->szIniFile;
  }
  else { /* NULL */
    TraceOp.trc( name, TRCLEVEL_EXCEPTION, __LINE__, 9999, "inst == NULL!" );
    return NULL;
  }
}


static const char* _getLibPath( void ) {
  if( __appinst != NULL ) {
    iOAppData data = Data(__appinst);
    return data->szLibPath;
  }
  return NULL;
}

static const char* _getImgPath( void ) {
  if( __appinst != NULL ) {
    iOAppData data = Data(__appinst);
    if( data->szImgPath == NULL )
      return wRocRail.getimgpath(AppOp.getIni());
    else
      return data->szImgPath;
  }
  return NULL;
}

static const char* _getIconPath( void ) {
  if( __appinst != NULL )
    return wRocRail.geticonpath(AppOp.getIni());
  return NULL;
}

static int _getrevno( void ) {
  if( __appinst != NULL ) {
    iOAppData data = Data(__appinst);
    return data->revno;
  }
  return 0;
}


static iONode _getIni( void ) {
  if( __appinst != NULL ) {
    iOAppData data = Data(__appinst);
    return data->ini;
  }
  return NULL;
}


static Boolean _isCreateModplan( void ) {
  if( __appinst != NULL ) {
    iOAppData data = Data(__appinst);
    if( data->createmodplan )
      return True;
    else
      return wRocRail.iscreatemodplan( data->ini);
  }
  return False;
}


static Boolean _isRunAtStartup( void ) {
  if( __appinst != NULL ) {
    iOAppData data = Data(__appinst);
    return data->run;
  }
  return False;
}


static iONode _getNewIni( void ) {
  if( __appinst != NULL ) {
    iOAppData data = Data(__appinst);
    if( data->newini != NULL )
      return data->newini;
    else
      return data->ini;
  }
  return NULL;
}


static const char* _getdonkey( void ) {
  if( __appinst != NULL ) {
    iOAppData data = Data(__appinst);
    return data->donkey;
  }
  else
    return "";
}

static const char* _getdoneml( void ) {
  if( __appinst != NULL ) {
    iOAppData data = Data(__appinst);
    return data->doneml;
  }
  else
    return "";
}

static Boolean _isKeyValid( void ) {
  if( __appinst != NULL ) {
    iOAppData data = Data(__appinst);
    unsigned char* donkey = StrOp.strToByte(data->donkey);
    char* decodedKey = SystemOp.decode(donkey, StrOp.len(data->donkey)/2, data->doneml);
    Boolean isExpired = SystemOp.isExpired(decodedKey, NULL, NULL, wGlobal.vmajor, wGlobal.vminor);

    freeMem(decodedKey);
    freeMem(donkey);

    if( isExpired ) {
      TraceOp.trc( name, TRCLEVEL_INFO, __LINE__, 9999, "no valid donation key found" );
    }
    else {
      return True;
    }
  }
  return False;
}


static void _setIni( iONode ini ) {
  if( __appinst != NULL ) {
    iOAppData data  = Data(__appinst);
    iONode    trace = wRocRail.gettrace( ini );
    iONode     ctrl = wRocRail.getctrl( ini );
    iONode curtrace = wRocRail.gettrace( data->ini );
    iONode  curctrl = wRocRail.getctrl( data->ini );

    if( curctrl != NULL && ctrl != NULL) {
      wCtrl.setvirtualtimer(curctrl, wCtrl.getvirtualtimer(ctrl));
      wCtrl.setweather(curctrl, wCtrl.isweather(ctrl));
    }

    if( trace != NULL && curtrace != NULL) {
      TraceOp.trc( name, TRCLEVEL_WARNING, __LINE__, 9999, "trace levels changes are activated, other setting at restart..." );

      TraceOp.trc( name, TRCLEVEL_BYTE, __LINE__, 9999, "_setIni: trace levels [old][new]: auto[%d][%d] byte[%d][%d] debug[%d][%d] monitor[%d][%d] info[%d][%d] calc[%d][%d]",
          wTrace.isautomatic( curtrace ), wTrace.isautomatic( trace ),
          wTrace.isbyte(      curtrace ), wTrace.isbyte(      trace ),
          wTrace.isdebug(     curtrace ), wTrace.isdebug(     trace ),
          wTrace.ismonitor(   curtrace ), wTrace.ismonitor(   trace ),
          wTrace.isinfo(      curtrace ), wTrace.isinfo(      trace ),
          wTrace.iscalc(      curtrace ), wTrace.iscalc(      trace ) );

      wTrace.setautomatic( curtrace, wTrace.isautomatic( trace ) );
      wTrace.setbyte( curtrace, wTrace.isbyte( trace ) );
      wTrace.setdebug( curtrace, wTrace.isdebug( trace ) );
      wTrace.setmonitor( curtrace, wTrace.ismonitor( trace ) );
      wTrace.setinfo( curtrace, wTrace.isinfo( trace ) );
      wTrace.setcalc( curtrace, wTrace.iscalc( trace ) );

      tracelevel trcLvlOld = TraceOp.getLevel( NULL );
      tracelevel trcLvlNew = trcLvlOld ;

      if( wTrace.isautomatic( curtrace ) )
        trcLvlNew |= TRCLEVEL_USER1 ;
      else
        trcLvlNew &= ~TRCLEVEL_USER1 ;

      if( wTrace.isbyte( curtrace ) )
        trcLvlNew |= TRCLEVEL_BYTE ;
      else
        trcLvlNew &= ~TRCLEVEL_BYTE ;

      if( wTrace.isdebug( curtrace ) )
        trcLvlNew |= (TRCLEVEL_DEBUG | TRCLEVEL_XMLH) ;
      else
        trcLvlNew &= ~(TRCLEVEL_DEBUG | TRCLEVEL_XMLH) ;

      if( wTrace.ismonitor( curtrace ) )
        trcLvlNew |= TRCLEVEL_MONITOR ;
      else
        trcLvlNew &= ~TRCLEVEL_MONITOR ;

      if( wTrace.isinfo( curtrace ) )
        trcLvlNew |= TRCLEVEL_INFO ;
      else
        trcLvlNew &= ~TRCLEVEL_INFO ;

      if( wTrace.iscalc( curtrace ) )
        trcLvlNew |= TRCLEVEL_CALC ;
      else
        trcLvlNew &= ~TRCLEVEL_CALC ;

      TraceOp.trc( name, TRCLEVEL_BYTE, __LINE__, 9999, "_setIni: trcLvlOld[%08.8X] trcLvlNew[%08.8X]", trcLvlOld, trcLvlNew );

      if( trcLvlOld != trcLvlNew )
        TraceOp.setLevel( NULL, trcLvlNew );
    }

    /* free up newini from previous setIni */
    if( data->newini != NULL )
      NodeOp.base.del(data->newini);
    data->newini = (iONode)NodeOp.base.clone( ini );

    AppOp.saveIni();
  }
}

static iONode _getIniNode( const char* name ) {
  if( __appinst != NULL ) {
    iOAppData data = Data(__appinst);
    if( data->ini != NULL ) {
      return NodeOp.findNode( data->ini, name );
    }
    else
      return NULL;
  }
  return NULL;
}

static iOModel _getModel( void ) {
  if( __appinst != NULL ) {
    iOAppData data = Data(__appinst);
    return data->model;
  }
  return NULL;
}

static iOControl _getControl( void ) {
  if( __appinst != NULL ) {
    iOAppData data = Data(__appinst);
    return data->control;
  }
  return NULL;
}

static iOWeather _getWeather( void ) {
  if( __appinst != NULL ) {
    iOAppData data = Data(__appinst);
    return data->weather;
  }
  return NULL;
}

static iOClntCon _getClntCon( void ) {
  if( __appinst != NULL ) {
    iOAppData data = Data(__appinst);
    return data->clntCon;
  }
  return NULL;
}

static iOSrcpCon _getSrcpCon( void ) {
  if( __appinst != NULL ) {
    iOAppData data = Data(__appinst);
    return data->srcpCon;
  }
  return NULL;
}

static int __logo( void ) {
  iOAppData data = Data(__appinst);
  int svn = 0;
  long expdays = 0;
  /* Logo. */
  TraceOp.println( "--------------------------------------------------" );
  TraceOp.println( "                                            lll   " );
  TraceOp.println( "                                        iii lll   " );
  TraceOp.println( "                                            lll   " );
  TraceOp.println( " rrrrrr   ooooo   ccccc rrrrrr   aaaaaa iii lll   " );
  TraceOp.println( " rrr rrr ooo ooo ccc    rrr rrr aaa aaa iii lll   " );
  TraceOp.println( " rrr     ooo ooo ccc    rrr     aaa aaa iii lll   " );
  TraceOp.println( " rrr      ooooo   ccccc rrr      aaaaaa iii  lll  " );
  TraceOp.println( "--------------------------------------------------" );
  TraceOp.println( " TM and Copyright 2002-2015 Robert Jan Versluis."   );
  TraceOp.println( " All Rights Reserved."                              );
  TraceOp.println( "   r.j.versluis@rocrail.net"                        );
  TraceOp.println( "   http://www.rocrail.net"                          );
  TraceOp.println( "--------------------------------------------------" );
  TraceOp.println( " %s %d [%s]", wGlobal.productname, revisionnr, commithash );

  if( revisionnr > 0 ){
    svn = revisionnr;
  }
  else {
/*
    iODoc doc = DocOp.parse(svnLog);
    if( doc != NULL ) {
      iONode log = DocOp.getRootNode(doc);
      DocOp.base.del(doc);
      if( log != NULL ) {
        svn = wSvnLogEntry.getrevision( wSvnLog.getlogentry(log) );
        TraceOp.println( " svn %d", svn );
        NodeOp.base.del(log);
      }
    }
*/
  }
  TraceOp.println( " Build: %s %s",
                   wGlobal.buildDate,
                   wGlobal.buildTime );
  TraceOp.println( " %s", SystemOp.getBuild() );
  TraceOp.println( " processid = %d", SystemOp.getpid() );
  TraceOp.println( "       mac = %s", SocketOp.getMAC( NULL ) );
  TraceOp.println( "--------------------------------------------------" );
  /*TraceOp.printHeader();*/

  if( SystemOp.isExpired(SystemOp.decode(StrOp.strToByte(data->donkey),
      StrOp.len(data->donkey)/2, data->doneml), NULL, &expdays, wGlobal.vmajor, wGlobal.vminor) ) {
    TraceOp.println( "*******************************************************************" );
    TraceOp.println( "* Rocrail runs entirely on volunteer labor.                       *");
    TraceOp.println( "* However, Rocrail also needs contributions of money.             *");
    TraceOp.println( "* Your continued support is vital for keeping Rocrail available.  *");
    TraceOp.println( "* If you already did donate you can ask a key: donate@rocrail.net *");
    TraceOp.println( "*******************************************************************" );
  }


  return svn;
}

static void __help( void ) {
  /* Help. */
  TraceOp.println( "----------------------------------------------------------------------"  );
  TraceOp.println( "Rocrail commandline options:"  );
  TraceOp.println( "-------------------------+--------------------------------------------"  );
  TraceOp.println( "--help or -?             | Displays this help and quit." );
  TraceOp.println( "-version                 | Displays version info and quit." );
  TraceOp.println( "-doc                     | Writes documentation in %s.html.", wGlobal.productname );
  TraceOp.println( "-------------------------+--------------------------------------------"  );
  TraceOp.println( "-debug                   | Switch on debug tracelevel." );
  TraceOp.println( "-byte                    | Switch on byte tracelevel." );
  TraceOp.println( "-parse                   | Switch on xml parse tracelevel." );
  TraceOp.println( "-monitor                 | Switch on controller monitor tracelevel." );
  TraceOp.println( "-info                    | Switch on info tracelevel." );
  TraceOp.println( "-http                    | Switch on http tracelevel." );
  TraceOp.println( "-------------------------+--------------------------------------------"  );
  TraceOp.println( "-console                 | Read console input." );
  TraceOp.println( "-nocom                   | Switch off communication." );
  TraceOp.println( "-auto                    | Power and auto mode on." );
  TraceOp.println( "-run                     | Start all locos." );
  TraceOp.println( "-resume                  | Start prev. locos." );
  TraceOp.println( "-w [workdir]             | Change the programs working directory." );
  TraceOp.println( "-l [libdir]              | Library directory." );
  TraceOp.println( "-img [imgdir]            | Images directory." );
  TraceOp.println( "-p [portnr]              | Service port for clients. [%d]", wTcp.getport(NULL) );
  TraceOp.println( "-i [inifile]             | Ini file. [%s].", wRocRail.getfile(NULL) );
  TraceOp.println( "-t [tracefile]           | Ini file. [%s].", wTrace.getrfile(NULL) );
  TraceOp.println( "-x [planfile]            | Ini file. [%s].", wRocRail.getplanfile(NULL) );
  TraceOp.println( "-f                       | Init field." );
  TraceOp.println( "-nodevcheck              | Disable check for serial devices at startup." );
  TraceOp.println( "-stress                  | Enable the stress runner for testing communication." );
  TraceOp.println( "-------------------------+--------------------------------------------"  );
  TraceOp.println( "-installservice          | Install Rocrail as Windows service." );
  TraceOp.println( "-deleteservice           | Uninstall Rocrail as Windows service." );
  TraceOp.println( "-------------------------+--------------------------------------------"  );
}

/** ------------------------------------------------------------
  * private __conhelp()
  * See wrapper.xml: ConCmd.
  */
static void __conhelp() {
    TraceOp.println( "-C-o-n-s-o-l-e---C-o-m-m-a-n-d-s-----------" );
    TraceOp.println( " ? - Help" );
    TraceOp.println( " q - Shutdown" );
    TraceOp.println( " p - Power ON" );
    TraceOp.println( " y - Power OFF" );
    TraceOp.println( " x - Read all slots" );
    TraceOp.println( " 5 - Query network" );
    TraceOp.println( " 8 - Start of Day" );
    TraceOp.println( " t - List all active threads" );
    TraceOp.println( " z - Analyse track plan" );
    TraceOp.println( " l - Cleanup analyzed route info" );

    TraceOp.println( " i - Initfield" );
    TraceOp.println( " s - Stop auto mode" );
    TraceOp.println( " e - Emergency break" );

    TraceOp.println( " m - Shows memory(object) use" );
    TraceOp.println( " %c - Toggle info tracelevel [%s]",    wConCmd.info,    (TraceOp.getLevel( NULL ) & TRCLEVEL_INFO)?"ON":"OFF" );
    TraceOp.println( " %c - Toggle debug tracelevel [%s]",   wConCmd.debug,   (TraceOp.getLevel( NULL ) & TRCLEVEL_DEBUG)?"ON":"OFF" );
    TraceOp.println( " %c - Toggle byte tracelevel [%s]",    wConCmd.byte,    (TraceOp.getLevel( NULL ) & TRCLEVEL_BYTE)?"ON":"OFF" );
/*  TraceOp.println( " %c - Toggle wrapper tracelevel" ); not defined/used */
    TraceOp.println( " %c - Toggle automat tracelevel [%s]", wConCmd.automat, (TraceOp.getLevel( NULL ) & TRCLEVEL_USER1)?"ON":"OFF" );
    TraceOp.println( " %c - Toggle http tracelevel [%s]",    wConCmd.http,    (TraceOp.getLevel( NULL ) & TRCLEVEL_USER2)?"ON":"OFF" );
    TraceOp.println( " %c - Toggle monitor tracelevel [%s]", wConCmd.monitor, (TraceOp.getLevel( NULL ) & TRCLEVEL_MONITOR)?"ON":"OFF" );
    TraceOp.println( " %c - Toggle memory tracelevel [%s]",  wConCmd.memtrc,  (TraceOp.getLevel( NULL ) & TRCLEVEL_MEMORY)?"ON":"OFF" );
}


static void __syscmd( const char* command ) {
  if( __appinst != NULL ) {
    iOAppData data = Data(__appinst);
    iONode cmd = NodeOp.inst( wSysCmd.name(), NULL, ELEMENT_NODE);
    wSysCmd.setcmd( cmd, command );
    wSysCmd.setinformall(cmd, True);
    TraceOp.trc( name, TRCLEVEL_INFO, __LINE__, 9999, "SysCommand: %s", command );
    ControlOp.cmd( data->control, (iONode)NodeOp.base.clone(cmd), NULL );
    AppOp.broadcastEvent( cmd );
  }
}


static void __queryModules() {
  iOAppData data = Data(__appinst);
  iONode cmd = NodeOp.inst( wProgram.name(), NULL, ELEMENT_NODE );
  wProgram.setlntype( cmd, wProgram.lntype_sv );
  wProgram.setcmd( cmd, wProgram.lncvget );
  wProgram.setaddr( cmd, 0 );
  wProgram.setmodid( cmd, 0 );
  wProgram.setcv( cmd, 0 );
  TraceOp.trc( name, TRCLEVEL_INFO, __LINE__, 9999, "Query modules..." );
  ControlOp.cmd( data->control, cmd, NULL );
}



static void __checkConsole( iOAppData data ) {
  /* Check for command. */
  int c = getchar();

  if( c == wConCmd.debug ) {
    TraceOp.trc( name, TRCLEVEL_INFO, __LINE__, 9999, "Toggle debug tracelevel." );
    TraceOp.setLevel( NULL, TraceOp.getLevel( NULL ) ^ TRCLEVEL_DEBUG );
    TraceOp.setLevel( NULL, TraceOp.getLevel( NULL ) ^ TRCLEVEL_XMLH );
  }
  else if( c == wConCmd.byte ) {
    TraceOp.trc( name, TRCLEVEL_INFO, __LINE__, 9999, "Toggle byte tracelevel." );
    TraceOp.setLevel( NULL, TraceOp.getLevel( NULL ) ^ TRCLEVEL_BYTE );
  }
  else if( c == wConCmd.memtrc ) {
    TraceOp.trc( name, TRCLEVEL_INFO, __LINE__, 9999, "Toggle memory tracelevel." );
    TraceOp.setLevel( NULL, TraceOp.getLevel( NULL ) ^ TRCLEVEL_MEMORY );
  }
  else if( c == wConCmd.automat ) {
    TraceOp.trc( name, TRCLEVEL_INFO, __LINE__, 9999, "Toggle auto tracelevel." );
    TraceOp.setLevel( NULL, TraceOp.getLevel( NULL ) ^ TRCLEVEL_USER1 );
  }
  else if( c == wConCmd.http ) {
    TraceOp.trc( name, TRCLEVEL_INFO, __LINE__, 9999, "Toggle http tracelevel." );
    TraceOp.setLevel( NULL, TraceOp.getLevel( NULL ) ^ TRCLEVEL_USER2 );
  }
  else if( c == wConCmd.monitor ) {
    TraceOp.trc( name, TRCLEVEL_INFO, __LINE__, 9999, "Toggle monitor tracelevel." );
    TraceOp.setLevel( NULL, TraceOp.getLevel( NULL ) ^ TRCLEVEL_MONITOR );
  }
  else if( c == wConCmd.info ) {
    TraceOp.trc( name, TRCLEVEL_INFO, __LINE__, 9999, "Toggle info tracelevel." );
    TraceOp.setLevel( NULL, TraceOp.getLevel( NULL ) ^ TRCLEVEL_INFO );
  }
  else if( c == wConCmd.quit ) {
    TraceOp.trc( name, TRCLEVEL_INFO, __LINE__, 9999, "Shutdown requested." );
    data->consoleMode = False;
    AppOp.shutdown(0, "Console command");
  }
  else if( c == wConCmd.initfield ) {
    TraceOp.trc( name, TRCLEVEL_INFO, __LINE__, 9999, "Initfield requested." );
    ModelOp.initField( data->model, True );
  }
  else if( c == wConCmd.threads ) {
    AppOp.listThreads();
  }
  else if( c == wConCmd.poweron ) {
    AppOp.go();
  }
  else if( c == wConCmd.poweroff ) {
    AppOp.stop();
  }
  else if( c == wConCmd.slots ) {
    __syscmd( wSysCmd.slots );
  }
  else if( c == wConCmd.query ) {
    __queryModules();
  }
  else if( c == wConCmd.sod ) {
    __syscmd( wSysCmd.sod );
  }
  else if( c == wConCmd.stopautomode ) {
    iONode cmd = NULL;
    clntcon_callback pfun = ControlOp.getCallback(data->control);
    cmd = NodeOp.inst( wAutoCmd.name(), NULL, ELEMENT_NODE );
    wAutoCmd.setcmd( cmd, wAutoCmd.off );
    pfun( (obj)AppOp.getControl(), cmd );
  }
  else if( c == wConCmd.ebreak ) {
    iONode cmd = NULL;
    clntcon_callback pfun = ControlOp.getCallback(data->control);
    cmd = NodeOp.inst( wSysCmd.name(), NULL, ELEMENT_NODE );
    wSysCmd.setcmd( cmd, wSysCmd.ebreak );
    pfun( (obj)AppOp.getControl(), cmd );
  }
  else if( c == wConCmd.config ) {
    __syscmd( wSysCmd.config );
  }
  else if( c == wConCmd.analyse ) {
    ModelOp.analyse( data->model, False );
  }
  else if( c == wConCmd.analyseclean ) {
    ModelOp.analyse( data->model, True );
  }
  else if( c == wConCmd.memory )
    rocsStatistics( True );
  else if( c == wConCmd.help )
    __conhelp();
}


static char* __readIniFile(const char* inifilename) {
  char* iniXml = NULL;

  if( FileOp.exist(inifilename) && FileOp.fileSize(inifilename) > 0 ) {
    iOFile iniFile = FileOp.inst( inifilename, True );
    if( iniFile != NULL ) {
      TraceOp.trc( name, TRCLEVEL_INFO, __LINE__, 9999, "using ini file: %s", FileOp.getFilename(iniFile) );
      freeMem(iniXml);
      iniXml = allocMem( FileOp.size( iniFile ) + 1 );
      FileOp.read( iniFile, iniXml, FileOp.size( iniFile ) );
      FileOp.close( iniFile );
    }
  }

  if( iniXml == NULL ) {
    char* backupfile = StrOp.fmt("%s.bak", inifilename );
    if( FileOp.exist(backupfile) && FileOp.fileSize(backupfile) > 0 ) {
      iOFile iniFile = FileOp.inst( backupfile, True );
      if( iniFile != NULL ) {
        TraceOp.trc( name, TRCLEVEL_WARNING, __LINE__, 9999, "using backup ini file: %s", FileOp.getFilename(iniFile) );
        iniXml = allocMem( FileOp.size( iniFile ) + 1 );
        FileOp.read( iniFile, iniXml, FileOp.size( iniFile ) );
        FileOp.close( iniFile );
      }
    }
    StrOp.free(backupfile);
  }

  return iniXml;
}

static Boolean bShutdown = False;

static int _Main( iOApp inst, int argc, char** argv ) {
  iOAppData data = Data(inst);
  iOTrace trc = NULL;
  Boolean cd = False;

  /* check commandline arguments */
  iOCmdLn     arg     = CmdLnOp.inst( argc, (const char**)argv );
  tracelevel  debug   = CmdLnOp.hasKey( arg, wCmdline.debug  ) ? TRCLEVEL_DEBUG:0;
  tracelevel  dump    = CmdLnOp.hasKey( arg, wCmdline.byte   ) ? TRCLEVEL_BYTE:0;
  tracelevel  parse   = CmdLnOp.hasKey( arg, wCmdline.parse  ) ? TRCLEVEL_PARSE:0;
  tracelevel  monitor = CmdLnOp.hasKey( arg, wCmdline.monitor) ? TRCLEVEL_MONITOR:0;
  tracelevel  info    = CmdLnOp.hasKey( arg, wCmdline.info   ) ? TRCLEVEL_INFO:0;
  tracelevel  http    = CmdLnOp.hasKey( arg, wCmdline.http   ) ? TRCLEVEL_USER2:0;

  const char* wd      = CmdLnOp.getStr( arg, wCmdline.workdir );
  const char* tf      = CmdLnOp.getStr( arg, wCmdline.trcfile );
  const char* pf      = CmdLnOp.getStr( arg, wCmdline.planfile );
  const char* lf      = CmdLnOp.getStr( arg, wCmdline.locofile );
  const char* port    = CmdLnOp.getStr( arg, wCmdline.port );
  const char* nf      = CmdLnOp.getStr( arg, wCmdline.inifile );

  Boolean initfield   = CmdLnOp.hasKey( arg, wCmdline.initfield );
  Boolean      help   = CmdLnOp.hasKey( arg, wCmdline.help ) | CmdLnOp.hasKey( arg, "-?" );
  Boolean     nocom   = CmdLnOp.hasKey( arg, wCmdline.nocom );
  Boolean   console   = CmdLnOp.hasKey( arg, wCmdline.console );
  Boolean       doc   = CmdLnOp.hasKey( arg, wCmdline.doc );
  Boolean   version   = CmdLnOp.hasKey( arg, wCmdline.version );
  Boolean   service   = CmdLnOp.hasKey( arg, wCmdline.service );
  Boolean       lcd   = CmdLnOp.hasKey( arg, wCmdline.lcd );
  Boolean nodevcheck  = CmdLnOp.hasKey( arg, wCmdline.nodevcheck );


  Boolean automode    = CmdLnOp.hasKey( arg, wCmdline.automode );
  Boolean resume      = CmdLnOp.hasKey( arg, wCmdline.resume );
  data->run           = CmdLnOp.hasKey( arg, wCmdline.run );
  data->stress        = CmdLnOp.hasKey( arg, wCmdline.stress );
  data->createmodplan = CmdLnOp.hasKey( arg, wCmdline.modplan );
  data->szLibPath     = CmdLnOp.getStr( arg, wCmdline.libpath );
  data->szImgPath     = CmdLnOp.getStr( arg, wCmdline.imgpath );

  /* change the programs working directory */
  if( wd != NULL ) {
    cd = FileOp.cd( wd );
  }

  trc = TraceOp.inst( debug | dump | monitor | parse | info | http | TRCLEVEL_WARNING | TRCLEVEL_CALC | TRCLEVEL_STATUS, tf, True );
  TraceOp.setAppID( trc, "r" );

  if( wd != NULL ) {
    char* pwd = FileOp.pwd();
    TraceOp.trc( name, cd?TRCLEVEL_CALC:TRCLEVEL_EXCEPTION, __LINE__, 9999, "workdir [%s] pwd [%s]", wd, pwd );
    StrOp.free(pwd);
    if( !cd ) {
      cd = FileOp.cd( wd );
      if( !cd )
        TraceOp.terrno( name, TRCLEVEL_EXCEPTION, __LINE__, 9999, errno, "Error changing workdir" );
    }
  }


  data->consoleMode = console;

  if( service ) {
    /* block reading console */
    console = False;
    nocom   = False;
  }
  else {
    if( help ) {
      data->revno = __logo();
      __help();
      return 0;
    }
    else if( doc ) {
      /* Write the embeded documentation into local HTML files: */
      extern const char rocrail_doc[]; /* xspooler.ini doc */

      char* fname = StrOp.fmt( "%s.html", wGlobal.productname );
      iOFile f = FileOp.inst( fname, OPEN_WRITE );
      __logo();
      if( f != NULL ) {
        Boolean ok = FileOp.write( f, rocrail_doc, StrOp.len( rocrail_doc ) );
        FileOp.base.del( f );
        TraceOp.println( "%s %s", fname, ok?"successfully written.":"not written."  );
      }
      StrOp.free( fname );
      return 0;
    }
    else if( version ) {
      __logo();
      return 0;
    }
  }


  /* Read the Inifile: */
  {
    char* iniXml = NULL;
    iODoc iniDoc = NULL;
    Boolean newIni = False;
    data->szIniFile = nf?nf:wRocRail.getfile(NULL);
    iniXml = __readIniFile(data->szIniFile);
    if( iniXml == NULL ) {
      iniXml = StrOp.fmt( "<%s/>", wRocRail.name());
      newIni = True;
      TraceOp.trc( name, TRCLEVEL_EXCEPTION, __LINE__, 9999, "empty ini file! [%s]", data->szIniFile );
    }

    /* Parse the Inifile: */
    iniDoc = DocOp.parse( iniXml );
    if( iniDoc != NULL ) {
      data->ini = DocOp.getRootNode( iniDoc );
      if( newIni ) {
        /* activate use block side routes for new work spaces */
        iONode ctrl = NodeOp.inst( wCtrl.name(), data->ini, ELEMENT_NODE );
        NodeOp.addChild( data->ini, ctrl );
      }
    }
    else {
      TraceOp.trc( name, TRCLEVEL_EXCEPTION, __LINE__, 9999, "Invalid ini file! [%s]", nf?nf:wRocRail.getfile(NULL) );
      return -1;
    }
  }

  if( nodevcheck ) {
    wRocRail.setnodevcheck(data->ini, nodevcheck );
  }

  if( FileOp.exist(wRocRail.getkeypath(data->ini)) ) {
    iOFile f = FileOp.inst( wRocRail.getkeypath(data->ini), OPEN_READONLY );
    char* buffer = (char*)allocMem( FileOp.size( f ) +1 );
    FileOp.read( f, buffer, FileOp.size( f ) );
    FileOp.base.del( f );
    iOStrTok tok = StrTokOp.inst( buffer, ';' );
    if( StrTokOp.hasMoreTokens(tok))
      data->doneml = StrOp.dup(StrTokOp.nextToken(tok) );
    if( StrTokOp.hasMoreTokens(tok))
      data->donkey = StrOp.dup(StrTokOp.nextToken(tok) );
    StrTokOp.base.del( tok );
    freeMem(buffer);
  }
  if( data->donkey == NULL || StrOp.len(data->donkey) == 0 ) {
    data->donkey = wRocRail.getdonkey( data->ini );
    data->donkey = wRocRail.getdoneml( data->ini );
  }

  if( wRocRail.isrunasroot( data->ini ) ) {
      TraceOp.trc( name, TRCLEVEL_INFO, __LINE__, 9999, "Try to run rocrail as root..." );
      if( !SystemOp.setAdmin() ) {
         TraceOp.trc( name, TRCLEVEL_EXCEPTION, __LINE__, 9999, "Only user 'root' can start rocrail! Abort!" );
         return -1;
      }
  }

  if( data->szLibPath == NULL ) {
    data->szLibPath = wRocRail.getlibpath( data->ini );
  }

  if( info != TRCLEVEL_INFO ){ /* Check info tracelevel. */
    int         level = TraceOp.getLevel( trc );
    Boolean infoParam = wTrace.isinfo( wRocRail.gettrace( data->ini ) );
    Boolean   infoCmd = (info & TRCLEVEL_INFO) ? True:False;
    if( infoCmd != infoParam ) {
      level &= 0xfffff ^ TRCLEVEL_INFO;
      level |= infoParam ? TRCLEVEL_INFO:0;
      TraceOp.setLevel( trc, level );
    }
  }

  /* Tracefile and listener */
  if( wRocRail.gettrace( data->ini ) == NULL ) {
    iONode trace = NodeOp.inst( wTrace.name(), data->ini, ELEMENT_NODE );
    NodeOp.addChild( data->ini, trace );
  }

  if( wTrace.isdebug( wRocRail.gettrace( data->ini ) ) || debug )
    TraceOp.setLevel( trc, TraceOp.getLevel( trc ) | TRCLEVEL_DEBUG );
  if( wTrace.isautomatic( wRocRail.gettrace( data->ini ) ) )
    TraceOp.setLevel( trc, TraceOp.getLevel( trc ) | TRCLEVEL_USER1 );
  if( wTrace.ismonitor( wRocRail.gettrace( data->ini ) ) || monitor )
    TraceOp.setLevel( trc, TraceOp.getLevel( trc ) | TRCLEVEL_MONITOR );
  if( wTrace.isbyte( wRocRail.gettrace( data->ini ) ) || dump )
    TraceOp.setLevel( trc, TraceOp.getLevel( trc ) | TRCLEVEL_BYTE );
  if( wTrace.isparse( wRocRail.gettrace( data->ini ) ) || parse )
    TraceOp.setLevel( trc, TraceOp.getLevel( trc ) | TRCLEVEL_PARSE );
  if( wTrace.iscalc( wRocRail.gettrace( data->ini ) ) )
    TraceOp.setLevel( trc, TraceOp.getLevel( trc ) | TRCLEVEL_CALC );


  /* Tracefile and listener */
  {
    iONode tini = wRocRail.gettrace( data->ini );
    char*    tracefilename = NULL;
    const char*   protpath = wTrace.getprotpath( tini );
    Boolean        unique  = wTrace.isunique( tini );
    const char*        tf2 = wTrace.getrfile( tini );
    int               size = wTrace.getsize( tini );
    int                 nr = wTrace.getnr( tini );
    Boolean  exceptionfile = wTrace.isexceptionfile( tini );
    const char*     invoke = wTrace.getinvoke( tini );
    Boolean    invokeasync = wTrace.isinvokeasync( tini );
    int           dumpsize = wTrace.getdumpsize( tini );

    TraceOp.setFileSize( trc, size );
    TraceOp.setNrFiles( trc, nr );
    TraceOp.setExceptionFile( trc, exceptionfile );
    TraceOp.setInvoke( trc, invoke, invokeasync );
    TraceOp.setDumpsize( trc, dumpsize );

    if( tf == NULL )
      tf = tf2;
    else {
      char* p = FileOp.getPath( tf );
      TraceOp.trc( name, TRCLEVEL_DEBUG, __LINE__, 9999, "ProtPath set to [%s]. (tf=\"%s\")", p, tf );
      wTrace.setprotpath( tini, p );
      StrOp.free( p );
      protpath = wTrace.getprotpath( tini );
      wTrace.setrfile( tini, FileOp.ripPath( tf ) );
    }

    /* Check protpath. */
    if( protpath != NULL ) {
      if( !FileOp.access( protpath ) ) {
        if( FileOp.mkdir( protpath ) )
          TraceOp.trc( name, TRCLEVEL_DEBUG, __LINE__, 9999, "ProtPath [%s] created.", protpath );
        else {
          TraceOp.trc( name, TRCLEVEL_WARNING, __LINE__, 1002,
              "Protocol path [%s] invalid.(Using current folder.", protpath );
          protpath = NULL;
        }
      }
      else
        TraceOp.trc( name, TRCLEVEL_DEBUG, __LINE__, 9999, "ProtPath [%s] OK.", protpath );
    }

    if( protpath != NULL && !FileOp.isAbsolute( tf ) ) {
      char* stamp = StrOp.createStamp();

      if( !FileOp.isAbsolute( protpath ) ) {
        char* wd = FileOp.pwd();
        tracefilename = StrOp.fmt( "%s%c%s%c%s%s",
                                   wd,
                                   SystemOp.getFileSeparator(),
                                   protpath,
                                   SystemOp.getFileSeparator(),
                                   tf,
                                   unique ? stamp:"" );
        StrOp.free( wd );
      }
      else {
        tracefilename = StrOp.fmt( "%s%c%s%s",
                                   protpath,
                                   SystemOp.getFileSeparator(),
                                   tf,
                                   unique ? stamp:"" );
      }

      StrOp.free( stamp );
    }
    else {
      char* stamp = StrOp.createStamp();
      tracefilename = StrOp.fmt( "%s%s", tf, unique ? stamp:"" );
      StrOp.free( stamp );
    }

    TraceOp.setFilename( trc, tracefilename );
    TraceOp.setExceptionListener( trc, __exception, False, wTrace.islisten2all(tini) );

    StrOp.free( tracefilename );
  }



  /* Logo. */
  data->revno = __logo();
  TraceOp.trc( name, TRCLEVEL_INFO, __LINE__, 9999, "dpIID = [%s]", wRocRail.getdpiid(data->ini) );
  TraceOp.trc( name, TRCLEVEL_INFO, __LINE__, 9999, "ptIID = [%s]", wRocRail.getptiid(data->ini) );
  TraceOp.trc( name, TRCLEVEL_INFO, __LINE__, 9999, "svIID = [%s]", wRocRail.getsviid(data->ini) );
  TraceOp.trc( name, TRCLEVEL_INFO, __LINE__, 9999, "lcIID = [%s]", wRocRail.getlciid(data->ini) );

  /* planDoc */
  pf = pf?pf:wRocRail.getplanfile(data->ini);
  lf = lf?lf:wRocRail.getlocs(data->ini);
  data->model = ModelOp.inst( pf, lf );
  if( !ModelOp.init( data->model ) ) {
    TraceOp.trc( name, TRCLEVEL_EXCEPTION, __LINE__, 9999, "unable to create model: EXIT" );
    return 0;
  }

  MemOp.setDebug( False );


  /* Control */
  data->control = ControlOp.inst( nocom );

  /* Weather */
  data->weather = WeatherOp.inst(ModelOp.getWeather(data->model, wRocRail.getweatherid(data->ini)));

  /* Client connection */
  {
    iONode tcp = wRocRail.gettcp(data->ini);
    int iPort = 0;
    if( tcp == NULL ) {
      tcp = NodeOp.inst( wTcp.name(), data->ini, ELEMENT_NODE );
      NodeOp.addChild( data->ini, tcp );
    }

    iPort = port?atoi(port):wTcp.getport(tcp);
    data->clntCon = ClntConOp.inst( tcp, iPort, ControlOp.getCallback( data->control), (obj)data->control );
  }

  /* Client connection */
  {
    iONode srcpini = wRocRail.getsrcpcon(data->ini);
    if( srcpini != NULL && wSrcpCon.getport(srcpini) > 0 && wSrcpCon.isactive(srcpini) ) {
      data->srcpCon = SrcpConOp.inst( srcpini, ControlOp.getCallback( data->control), (obj)data->control );
    }
  }

  /* Http (Optional)*/
  {
    iONode http = wRocRail.gethttp( data->ini );
    if( http != NULL ) {
      iONode tcp  = wRocRail.gettcp(data->ini);
      const char* controlcode = NULL;
      const char* slavecode   = NULL;
      if( tcp != NULL ) {
        controlcode = wTcp.getcontrolcode(tcp);
        slavecode   = wTcp.getslavecode(tcp);
      }
      data->http = HttpOp.inst( http, ControlOp.getCallback( data->control), (obj)data->control, wRocRail.getimgpath(data->ini), controlcode, slavecode );
    }
  }

  /* ABox */
  typedef iIArchiveBox (* LPFNGETARCHIVEBOX)( const char*, const iOTrace, int );

  if( StrOp.len( wRocRail.getaboxhome(data->ini) ) > 0 ) {
    unsigned char* donkey = StrOp.strToByte(AppOp.getdonkey());
    char* decodedKey = SystemOp.decode(donkey, StrOp.len(AppOp.getdonkey())/2, AppOp.getdoneml());
    char* libpath = StrOp.fmt( "%s%c%s", AppOp.getLibPath(), SystemOp.getFileSeparator(), "rocabox" );
    iOLib pLib = LibOp.inst(libpath);
    if( pLib != NULL ) {
      LPFNGETARCHIVEBOX  pInitFun = (LPFNGETARCHIVEBOX)LibOp.getProc( pLib, "getArchiveBox" );
      if (pInitFun != NULL) {
        data->abox = pInitFun( wRocRail.getaboxhome(data->ini), TraceOp.get(), SystemOp.isExpired(decodedKey, NULL, NULL, wGlobal.vmajor, wGlobal.vminor) );
        data->abox->find((obj)data->abox, "Zoek iets");
      }
    }
  }

  /* Snmp (Optional)*/
  {
    iONode snmp = wRocRail.getSnmpService( data->ini );
    if( snmp != NULL && wSnmpService.isactive(snmp) )
      data->snmp = SNMPOp.inst( snmp );
  }


  if( wRocRail.ispoweronatinit(data->ini) ) {
    AppOp.go();
  }

  ModelOp.initField( data->model, initfield );

  /* update the feedback arrays */
  ModelOp.updateFB( data->model );

  /* run every thing at startup */
  if( automode ) {
    iONode cmd = NULL;
    clntcon_callback pfun = ControlOp.getCallback(data->control);

    /* power on */
    AppOp.go();

    /* auto mode on */
    cmd = NodeOp.inst( wAutoCmd.name(), NULL, ELEMENT_NODE );
    wAutoCmd.setcmd( cmd, wAutoCmd.on );
    pfun( (obj)AppOp.getControl(), cmd );

    /* start all */
    if(data->run || resume) {
      cmd = NodeOp.inst( wAutoCmd.name(), NULL, ELEMENT_NODE );
      wAutoCmd.setcmd( cmd, resume? wAutoCmd.resume:wAutoCmd.start );
      pfun( (obj)AppOp.getControl(), cmd );
    }
  }

  /* Memory watcher */
  while( !bShutdown ) {
    static int cnt1 = 0;
    int cnt2 = MemOp.getAllocCount();
    if( cnt2 > cnt1 ) {
      TraceOp.trc( name, TRCLEVEL_BYTE, __LINE__, 9999, "memory allocations old=%u new=%u", cnt1, cnt2 );
      if(wTrace.ismeminfo( wRocRail.gettrace( data->ini ) ))
        rocsStatistics( True );
    }
    cnt1 = cnt2;
    ThreadOp.sleep( 1000 );

    /* Check for command. */
    if( data->consoleMode )
      __checkConsole( data );
  };

  return 0;
}


/** ------------------------------------------------------------
  * AppOp.listThreads()
  * Traced out all activated rocs::OThread objects.
  */
static void _listThreads(void) {
  iOList thList = ThreadOp.getAll();
  int cnt = ListOp.size( thList );
  int i = 0;
  TraceOp.trc( name, TRCLEVEL_INFO, __LINE__, 9999, "%d active threads.", cnt );

  for( i = 0; i < cnt; i++ ) {
    iOThread th = (iOThread)ListOp.get( thList, i );
    const char* tname = ThreadOp.getName( th );
    TraceOp.trc( name, TRCLEVEL_INFO, __LINE__, 9999, "Thread[%d] [%s]", i, tname );
  }
  /* Cleanup. */
  thList->base.del( thList );
}


static void _saveIni( void ) {
  if( __appinst != NULL ) {

    iOAppData data = Data(__appinst);
    iONode ini = (data->newini != NULL ? data->newini:data->ini);

    /* backup existing ini: */

    if( FileOp.exist(data->szIniFile) && FileOp.fileSize(data->szIniFile) > 0 ) {
      char* backupfile = StrOp.fmt( "%s.bak", data->szIniFile );
      TraceOp.trc( name, TRCLEVEL_INFO, __LINE__, 9999, "backing up %s to %s...",
          data->szIniFile, backupfile );
      if( FileOp.exist(backupfile) )
        FileOp.remove( backupfile );
      FileOp.rename( data->szIniFile, backupfile );
      StrOp.free( backupfile );
    }

    /* write the donkey in a file and remove it from the ini: */
    if( StrOp.len(wRocRail.getdonkey(ini)) > 0 ) {
      char* lic = StrOp.fmt("%s;%s", wRocRail.getdoneml( ini ), wRocRail.getdonkey( ini ) );
      iOFile f = FileOp.inst( wRocRail.getkeypath(data->ini), OPEN_WRITE );
      if( f != NULL ) {
        FileOp.writeStr(f, lic);
        FileOp.base.del(f);
      }
      StrOp.free(lic);
      data->donkey = StrOp.dup(wRocRail.getdonkey( ini ));
      data->doneml = StrOp.dup(wRocRail.getdoneml( ini ));

      wRocRail.setdonkey(ini, "" );
      wRocRail.setdoneml(ini, "" );
    }


    /* Write the Inifile: */
    {
      iOFile iniFile = FileOp.inst( data->szIniFile, OPEN_WRITE );

      if( iniFile != NULL ) {
        char* iniStr = NodeOp.toEscString( ini );
        TraceOp.trc( name, TRCLEVEL_INFO, __LINE__, 9999,
            "saving ini %s%s...", data->szIniFile, data->newini==NULL?"":"(new)" );
        FileOp.write( iniFile, iniStr, StrOp.len( iniStr ) );
        FileOp.close( iniFile );
        StrOp.free(iniStr);
      }
    }
  }
}


static Boolean _shutdown( int network, const char* signame ) {
  if( __appinst != NULL ) {

    iOAppData data = Data(__appinst);

    /* send shutdown command */
    iONode cmd = NodeOp.inst( wSysCmd.name(), NULL, ELEMENT_NODE);
    wSysCmd.setcmd( cmd, wSysCmd.shutdown );
    wSysCmd.setinformall( cmd, True );
    wSysCmd.setval( cmd, network );
    TraceOp.trc( name, TRCLEVEL_INFO, __LINE__, 9999, "SHUTDOWN" );
    if( data->control != NULL )
      ControlOp.cmd( data->control, cmd, NULL );

    /* inform clients */
    if( AppOp.getClntCon() != NULL ) {
      iONode broadcast = NodeOp.inst( wSysCmd.name(), NULL, ELEMENT_NODE);
      wSysCmd.setcmd( broadcast, wSysCmd.shutdown );
      wSysCmd.setinformall( broadcast, True );
      TraceOp.trc( name, TRCLEVEL_INFO, __LINE__, 9999, "Informing clients..." );
      AppOp.broadcastEvent( broadcast );
      ThreadOp.sleep(100);
    }

    /* time for clients to disconnect propperly */
    ThreadOp.sleep(100);

    if( data->snmp != NULL )
      SNMPOp.shutdown( data->snmp );

    /* Inform Model. */
    if( data->model != NULL && ModelOp.isSaveOnShutdown(data->model) ) {
      TraceOp.trc( name, TRCLEVEL_INFO, __LINE__, 9999, "Informing model..." );
      ModelOp.save(data->model, True); /* Remove generated objects. */
    }

    if( data->consoleMode ) {
      TraceOp.trc( name, TRCLEVEL_WARNING, __LINE__, 9999, "For shutdown in console mode use q<enter>" );
      return False;
    }

    if( bShutdown ) {
      TraceOp.trc( name, TRCLEVEL_INFO, __LINE__, 9999, "Shutdown already pending..." );
      return True;
    }

    /* signal all threads to stop */
    TraceOp.trc( name, TRCLEVEL_INFO, __LINE__, 9999, "Informing all threads..." );
    ThreadOp.requestQuitAll();

    if( signame != NULL )
      TraceOp.trc( name, TRCLEVEL_WARNING, __LINE__, 9999, "Shutting down because of [%s]", signame );
    else
      TraceOp.trc( name, TRCLEVEL_INFO, __LINE__, 9999, "Shutting down..." );

    {
      iOList thList = ThreadOp.getAll();
      int cnt = ListOp.size( thList );
      int i = 0;
      for( i = 0; i < cnt; i++ ) {
        iOThread th = (iOThread)ListOp.get( thList, i );
        const char* thname = ThreadOp.getName( th );
        TraceOp.trc( name, TRCLEVEL_INFO, __LINE__, 9999, "Thread[%d] <%s> still active.", i, thname );
      };
    }

    if( data->http != NULL )
      HttpOp.shutdown( data->http );

    TraceOp.trc( name, TRCLEVEL_INFO, __LINE__, 9999, "Informing controller..." );
    if( data->weather != NULL )
      WeatherOp.halt( data->weather );
    ControlOp.halt( data->control );

    AppOp.saveIni();

    /* signal main loop */
    bShutdown = True;

    TraceOp.trc( name, TRCLEVEL_INFO, __LINE__, 9999, "Exit." );
    return True;
  }
  return False;
}

static void _stop( void ) {
  if( __appinst != NULL ) {
    iOAppData data = Data(__appinst);
    iONode cmd = NodeOp.inst( wSysCmd.name(), NULL, ELEMENT_NODE);
    wSysCmd.setcmd( cmd, wSysCmd.stop );
    wSysCmd.setinformall( cmd, True );
    TraceOp.trc( name, TRCLEVEL_INFO, __LINE__, 9999, "POWER OFF" );
    if( data->control != NULL )
      ControlOp.cmd( data->control, (iONode)NodeOp.base.clone(cmd), NULL );
    if( AppOp.getClntCon() != NULL )
      AppOp.broadcastEvent( cmd );
  }
}

static void _ebreak( void ) {
  if( __appinst != NULL ) {
    iOAppData data = Data(__appinst);
    iONode cmd = NodeOp.inst( wSysCmd.name(), NULL, ELEMENT_NODE);
    wSysCmd.setcmd( cmd, wSysCmd.ebreak );
    wSysCmd.setinformall( cmd, True );
    TraceOp.trc( name, TRCLEVEL_INFO, __LINE__, 9999, "EBREAK" );
    if( data->control != NULL )
      ControlOp.cmd( data->control, (iONode)NodeOp.base.clone(cmd), NULL );
  }
}

static void _go( void ) {
  if( __appinst != NULL ) {
    iOAppData data = Data(__appinst);
    iONode cmd = NodeOp.inst( wSysCmd.name(), NULL, ELEMENT_NODE);
    wSysCmd.setcmd( cmd, wSysCmd.go );
    wSysCmd.setinformall( cmd, True );
    TraceOp.trc( name, TRCLEVEL_INFO, __LINE__, 9999, "POWER ON" );
    ControlOp.cmd( data->control, cmd, NULL );
  }
}


static long _getStartTime( void ) {
  TraceOp.trc( name, TRCLEVEL_METHOD, __LINE__, 9999, "_getStartTime()" );
  if( __appinst != NULL ) {
    iOAppData data = Data(__appinst);
    return data->appstartTime;
  }
  else { /* NULL */
    TraceOp.trc( name, TRCLEVEL_EXCEPTION, __LINE__, 9999, "inst == NULL!" );
    return 0;
  }
}

static Boolean _isConsoleMode( void ) {
  TraceOp.trc( name, TRCLEVEL_METHOD, __LINE__, 9999, "_isConsoleMode()" );
  if( __appinst != NULL ) {
    iOAppData data = Data(__appinst);
    return data->consoleMode;
  }
  else { /* NULL */
    TraceOp.trc( name, TRCLEVEL_EXCEPTION, __LINE__, 9999, "inst == NULL!" );
    return False;
  }
}

static Boolean _isStress( void ) {
  TraceOp.trc( name, TRCLEVEL_METHOD, __LINE__, 9999, "_isStress()" );
  if( __appinst != NULL ) {
    iOAppData data = Data(__appinst);
    return data->stress;
  }
  else { /* NULL */
    TraceOp.trc( name, TRCLEVEL_EXCEPTION, __LINE__, 9999, "inst == NULL!" );
    return False;
  }
}


static void _broadcastEvent( iONode event ) {
  if( __appinst != NULL ) {
    iOAppData data = Data(__appinst);
    if( data->clntCon != NULL )
      ClntConOp.broadcastEvent(data->clntCon, (iONode)NodeOp.base.clone(event));
    if( data->srcpCon != NULL )
      SrcpConOp.broadcastEvent(data->srcpCon, (iONode)NodeOp.base.clone(event));
    if( data->http != NULL && !HttpOp.isEnded(data->http) )
      HttpOp.broadcastEvent(data->http, (iONode)NodeOp.base.clone(event));

    NodeOp.base.del(event);
  }
}

static void _link( int count, Boolean up ) {
  if( __appinst != NULL ) {
    iOAppData data = Data(__appinst);
    if( data->snmp != NULL ) {
      SNMPOp.link(data->snmp, count, up);
    }
  }
}


static void _play( const char* record ) {
  if( __appinst != NULL ) {
    iOAppData data = Data(__appinst);
    if( data->script == NULL ) {
      data->script = ScriptOp.inst(NULL);
      ScriptOp.setCallback(data->script, (obj)data->control);
    }
    ScriptOp.setScript(data->script, record);
    ScriptOp.Play(data->script);
  }
}


static void _stopPlay( void ) {
  if( __appinst != NULL ) {
    iOAppData data = Data(__appinst);
    if( data->script != NULL ) {
      ScriptOp.Stop(data->script);
    }
  }
}


static iOApp _inst(void) {
  if( __appinst == NULL ) {
    iOApp     app  = allocMem( sizeof( struct OApp ) );
    iOAppData data = allocMem( sizeof( struct OAppData ) );

    /* OBase operations */
    MemOp.basecpy( app, &AppOp, 0, sizeof( struct OApp ), data );
    __appinst = app;

    __exceptionMutex = MutexOp.inst( NULL, True );

    data->appstartTime = time(NULL);
    data->szLibPath = NULL;
    data->donkey = "";
    data->doneml = "";

    SystemOp.inst();
  }

  return __appinst;
}

static iOApp _getApp( void ) {
  return __appinst;
}


/* ----- DO NOT REMOVE OR EDIT THIS INCLUDE LINE! -----*/
#include "rocrail/impl/app.fm"
/* ----- DO NOT REMOVE OR EDIT THIS INCLUDE LINE! -----*/
