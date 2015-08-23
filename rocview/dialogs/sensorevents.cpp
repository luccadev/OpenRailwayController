/*
 Rocrail - Model Railroad Software
 Copyright (c) 2002-2015 Robert Jan Versluis, Rocrail.net
 All rights reserved.
*/

#include <wx/clipbrd.h>
#include <wx/dataobj.h>
#include <wx/dnd.h>

#include "sensorevents.h"

#include "rocview/public/guiapp.h"
#include "rocview/dialogs/locseldlg.h"

#include "rocview/wrapper/public/Gui.h"
#include "rocview/wrapper/public/SensorMonitor.h"

#include "rocrail/wrapper/public/Feedback.h"
#include "rocrail/wrapper/public/Item.h"
#include "rocrail/wrapper/public/Loc.h"
#include "rocrail/wrapper/public/Car.h"
#include "rocrail/wrapper/public/ModelCmd.h"

#include "rocs/public/trace.h"


SensorEventsDlg::SensorEventsDlg( wxWindow* parent )
    :SensorEventsGen( parent )
{
  m_FbEvent = NULL;
  m_SortCol = 0;

  initLabels();
  initValues();
  GetSizer()->Layout();
  GetSizer()->Fit(this);
  GetSizer()->SetSizeHints(this);
  wxGetApp().setSensorEventListener(this);

  iONode ini = wxGetApp().getIni();
  iONode sensmon = wGui.getsensormonitor(ini);
  if( sensmon != NULL ) {
    if( wSensorMonitor.getcx(sensmon) > 0 && wSensorMonitor.getcy(sensmon) > 0 ) {
      SetSize(wSensorMonitor.getx(sensmon), wSensorMonitor.gety(sensmon), wSensorMonitor.getcx(sensmon), wSensorMonitor.getcy(sensmon));
    }
    else
      SetSize(wSensorMonitor.getx(sensmon), wSensorMonitor.gety(sensmon));
  }

  m_Reset->Enable(false);
  m_AssignIdent->Enable(false);
}


void SensorEventsDlg::initLabels() {
  SetTitle(wxGetApp().getMsg( "sensormonitor" ));
  m_EventList->InsertColumn(0, wxGetApp().getMsg( "iid" ), wxLIST_FORMAT_LEFT );
  m_EventList->InsertColumn(1, wxGetApp().getMsg( "id" ), wxLIST_FORMAT_LEFT );
  m_EventList->InsertColumn(2, wxGetApp().getMsg( "bus" ), wxLIST_FORMAT_RIGHT );
  m_EventList->InsertColumn(3, wxGetApp().getMsg( "address" ), wxLIST_FORMAT_RIGHT );
  m_EventList->InsertColumn(4, wxGetApp().getMsg( "state" ), wxLIST_FORMAT_CENTER );
  m_EventList->InsertColumn(5, wxGetApp().getMsg( "identifier" ), wxLIST_FORMAT_LEFT );
  m_EventList->InsertColumn(6, wxGetApp().getMsg( "counter" ), wxLIST_FORMAT_RIGHT );
  m_EventList->InsertColumn(7, wxGetApp().getMsg( "wheelcount" ), wxLIST_FORMAT_RIGHT );
  m_EventList->InsertColumn(8, wxGetApp().getMsg( "countedcars" ), wxLIST_FORMAT_RIGHT );
  m_EventList->InsertColumn(9, wxGetApp().getMsg( "load" ), wxLIST_FORMAT_RIGHT );
  m_EventList->InsertColumn(10, wxGetApp().getMsg( "stamp" ), wxLIST_FORMAT_LEFT );
  m_EventList->InsertColumn(11, wxT( "GPS" ), wxLIST_FORMAT_LEFT );
  m_Refresh->SetLabel(wxGetApp().getMsg( "refresh" ));
  m_Reset->SetLabel(wxGetApp().getMsg( "reset" ));
  m_AssignIdent->SetLabel(wxGetApp().getMsg( "assignident" ));
}

static bool m_bSortInvert = false;

static int __sortIID(obj* _a, obj* _b)
{
    iONode a = (iONode)*_a;
    iONode b = (iONode)*_b;
    const char* idA = wItem.getiid( a );
    const char* idB = wItem.getiid( b );
    return m_bSortInvert ? strcmp( idB, idA ):strcmp( idA, idB );
}


static int __sortID(obj* _a, obj* _b)
{
    iONode a = (iONode)*_a;
    iONode b = (iONode)*_b;
    const char* idA = wItem.getid( a );
    const char* idB = wItem.getid( b );
    return m_bSortInvert ? strcmp( idB, idA ):strcmp( idA, idB );
}


static int __sortBus(obj* _a, obj* _b)
{
    iONode a = (iONode)*_a;
    iONode b = (iONode)*_b;
    int busA = wItem.getbus( a );
    int busB = wItem.getbus( b );
    if( busA > busB )
      return m_bSortInvert ? -1:1;
    if( busA < busB )
      return m_bSortInvert ? 1:-1;
    return 0;
}


static int __sortAddr(obj* _a, obj* _b)
{
    iONode a = (iONode)*_a;
    iONode b = (iONode)*_b;
    int addrA = wFeedback.getaddr( a );
    int addrB = wFeedback.getaddr( b );
    if( addrA > addrB )
      return m_bSortInvert ? -1:1;
    if( addrA < addrB )
      return m_bSortInvert ? 1:-1;
    return 0;
}


static int __sortStamp(obj* _a, obj* _b)
{
    iONode a = (iONode)*_a;
    iONode b = (iONode)*_b;
    const char* idA = NodeOp.getStr(a, "stamp", "");
    const char* idB = NodeOp.getStr(b, "stamp", "");
    return m_bSortInvert ? strcmp( idB, idA ):strcmp( idA, idB );
}


static int __sortIdent(obj* _a, obj* _b)
{
    iONode a = (iONode)*_a;
    iONode b = (iONode)*_b;
    const char* idA = wFeedback.getidentifier(a);
    const char* idB = wFeedback.getidentifier(b);
    return m_bSortInvert ? strcmp( idB, idA ):strcmp( idA, idB );
}


static int __sortState(obj* _a, obj* _b)
{
    iONode a = (iONode)*_a;
    iONode b = (iONode)*_b;
    int addrA = wFeedback.isstate( a );
    int addrB = wFeedback.isstate( b );
    if( addrA > addrB )
      return m_bSortInvert ? -1:1;
    if( addrA < addrB )
      return m_bSortInvert ? 1:-1;
    return 0;
}


static int __sortCounter(obj* _a, obj* _b)
{
    iONode a = (iONode)*_a;
    iONode b = (iONode)*_b;
    int addrA = wFeedback.getcounter( a );
    int addrB = wFeedback.getcounter( b );
    if( addrA > addrB )
      return m_bSortInvert ? -1:1;
    if( addrA < addrB )
      return m_bSortInvert ? 1:-1;
    return 0;
}


static int __sortWheelCount(obj* _a, obj* _b)
{
    iONode a = (iONode)*_a;
    iONode b = (iONode)*_b;
    int addrA = wFeedback.getwheelcount( a );
    int addrB = wFeedback.getwheelcount( b );
    if( addrA > addrB )
      return m_bSortInvert ? -1:1;
    if( addrA < addrB )
      return m_bSortInvert ? 1:-1;
    return 0;
}


static int __sortCarCount(obj* _a, obj* _b)
{
    iONode a = (iONode)*_a;
    iONode b = (iONode)*_b;
    int addrA = wFeedback.getcountedcars( a );
    int addrB = wFeedback.getcountedcars( b );
    if( addrA > addrB )
      return m_bSortInvert ? -1:1;
    if( addrA < addrB )
      return m_bSortInvert ? 1:-1;
    return 0;
}


static int __sortLoad(obj* _a, obj* _b)
{
    iONode a = (iONode)*_a;
    iONode b = (iONode)*_b;
    int addrA = wFeedback.getload( a );
    int addrB = wFeedback.getload( b );
    if( addrA > addrB )
      return m_bSortInvert ? -1:1;
    if( addrA < addrB )
      return m_bSortInvert ? 1:-1;
    return 0;
}


void SensorEventsDlg::initValues() {
  m_EventList->DeleteAllItems();
  iOList list = wxGetApp().getSensorEvents();

  if( m_SortCol == 1 ) {
    ListOp.sort(list, &__sortIID);
  }
  else if( m_SortCol == 2 ) {
    ListOp.sort(list, &__sortBus);
  }
  else if( m_SortCol == 3 ) {
    ListOp.sort(list, &__sortAddr);
  }
  else if( m_SortCol == 4 ) {
    ListOp.sort(list, &__sortState);
  }
  else if( m_SortCol == 5 ) {
    ListOp.sort(list, &__sortIdent);
  }
  else if( m_SortCol == 6 ) {
    ListOp.sort(list, &__sortCounter);
  }
  else if( m_SortCol == 7 ) {
    ListOp.sort(list, &__sortWheelCount);
  }
  else if( m_SortCol == 8 ) {
    ListOp.sort(list, &__sortCarCount);
  }
  else if( m_SortCol == 9 ) {
    ListOp.sort(list, &__sortLoad);
  }
  else if( m_SortCol == 10 ) {
    ListOp.sort(list, &__sortStamp);
  }
  else {
    ListOp.sort(list, &__sortID);
  }


  int cnt = ListOp.size( list );
  for( int i = 0; i < cnt; i++ ) {
    iONode fbevent = (iONode)ListOp.get( list, i );
    m_EventList->InsertItem( i, wxString(wFeedback.getiid(fbevent), wxConvUTF8) );
    m_EventList->SetItem( i, 1, wxString(wFeedback.getid(fbevent), wxConvUTF8) );
    m_EventList->SetItem( i, 2, wxString::Format(wxT("%d"), wFeedback.getbus(fbevent) ) );
    m_EventList->SetItem( i, 3, wxString::Format(wxT("%d"), wFeedback.getaddr(fbevent) ) );
    m_EventList->SetItem( i, 4, wxString::Format(wxT("%d"), wFeedback.isstate(fbevent)?1:0 ) );
    m_EventList->SetItem( i, 5, wxString(wFeedback.getidentifier(fbevent), wxConvUTF8) );
    m_EventList->SetItem( i, 6, wxString::Format(wxT("%d"), wFeedback.getcounter(fbevent) ) );
    m_EventList->SetItem( i, 7, wxString::Format(wxT("%d"), wFeedback.getwheelcount(fbevent) ) );
    m_EventList->SetItem( i, 8, wxString::Format(wxT("%d"), wFeedback.getcountedcars(fbevent) ) );
    m_EventList->SetItem( i, 9, wxString::Format(wxT("%d"), wFeedback.getload(fbevent) ) );
    m_EventList->SetItem( i, 10, wxString(NodeOp.getStr(fbevent, "stamp", ""), wxConvUTF8) );
    m_EventList->SetItem( i, 11, wxString::Format(wxT("%d,%d,%d"), wFeedback.getgpsx(fbevent), wFeedback.getgpsy(fbevent), wFeedback.getgpsz(fbevent) ) );
    m_EventList->SetItemPtrData(i, (wxUIntPtr)fbevent);
  }
  // resize
  for( int n = 0; n < 11; n++ ) {
    m_EventList->SetColumnWidth(n, wxLIST_AUTOSIZE_USEHEADER);
    int autoheadersize = m_EventList->GetColumnWidth(n);
    m_EventList->SetColumnWidth(n, wxLIST_AUTOSIZE);
    int autosize = m_EventList->GetColumnWidth(n);
    if(autoheadersize > autosize )
      m_EventList->SetColumnWidth(n, wxLIST_AUTOSIZE_USEHEADER);
  }
}


void SensorEventsDlg::onRefresh( wxCommandEvent& event ) {
  initValues();
}

bool SensorEventsDlg::Validate() {
  wxCommandEvent event( wxEVT_COMMAND_BUTTON_CLICKED );
  event.SetEventObject(m_Refresh);
  wxPostEvent( m_Refresh, event );
  return false;
}

void SensorEventsDlg::onOK( wxCommandEvent& event ) {
  int x,y;
  GetPosition(&x,&y);
  int cx,cy;
  GetSize(&cx,&cy);

  iONode ini = wxGetApp().getIni();
  iONode sensmon = wGui.getsensormonitor(ini);
  if( sensmon == NULL ) {
    sensmon = NodeOp.inst(wSensorMonitor.name(), ini, ELEMENT_NODE);
    NodeOp.addChild(ini, sensmon);
  }
  wSensorMonitor.setx(sensmon,x);
  wSensorMonitor.sety(sensmon,y);
  wSensorMonitor.setcx(sensmon,cx);
  wSensorMonitor.setcy(sensmon,cy);

  wxGetApp().setSensorEventListener(NULL);
  wxGetApp().getFrame()->resetSensorMonitorRef();
  Destroy();

}

void SensorEventsDlg::onClose( wxCloseEvent& event ) {
  wxCommandEvent e;
  onOK(e);
}

void SensorEventsDlg::onListSelected( wxListEvent& event ) {
  int index = event.GetIndex();
  m_FbEvent = (iONode)m_EventList->GetItemData(index);
  m_Reset->Enable(true);
  m_AssignIdent->Enable(true);
}


void SensorEventsDlg::onReset( wxCommandEvent& event ) {
  if( m_FbEvent != NULL && wFeedback.getid( m_FbEvent ) != NULL ) {
    iONode cmd = NodeOp.inst( wFeedback.name(), NULL, ELEMENT_NODE );
    wFeedback.setiid( cmd, wFeedback.getiid( m_FbEvent ) );
    wFeedback.setid( cmd, wFeedback.getid( m_FbEvent ) );
    wFeedback.setcmd( cmd, wFeedback.reset );
    wxGetApp().sendToRocrail( cmd );
    cmd->base.del(cmd);
    m_Reset->Enable(false);
    m_AssignIdent->Enable(false);
    m_FbEvent = NULL;
  }
}


void SensorEventsDlg::onColClick( wxListEvent& event ) {
  if( m_SortCol == event.GetColumn() )
    m_bSortInvert = !m_bSortInvert;
  else
    m_bSortInvert = false;

  m_SortCol = event.GetColumn();
  initValues();
}


void SensorEventsDlg::onDrag( wxListEvent& event ) {
  if( m_FbEvent == NULL )
    return;

  wxString my_text = _T("bus:")+wxString::Format(_T("%d:"), wFeedback.getbus(m_FbEvent) )+wxString::Format(_T("%d::"), wFeedback.getaddr(m_FbEvent)) + wxString(wFeedback.getiid(m_FbEvent), wxConvUTF8);
  wxTextDataObject my_data(my_text);
  wxDropSource dragSource( this );
  dragSource.SetData( my_data );
  wxDragResult result = dragSource.DoDragDrop(wxDrag_CopyOnly);
}


void SensorEventsDlg::onHelp( wxCommandEvent& event ) {
  wxGetApp().openLink( "sensormon" );
}

void SensorEventsDlg::onAssign( wxCommandEvent& event ) {
  if( m_FbEvent == NULL )
    return;
  // ToDo: Assign the identifier of the selected event to Loco or Car...
  LocSelDlg*  dlg = new LocSelDlg(this, NULL, false, NULL, true, true );

  if( wxID_OK == dlg->ShowModal() ) {
    iONode l_Props = dlg->getProperties();
    if( l_Props != NULL ) {
      TraceOp.trc( "sensormon", TRCLEVEL_INFO, __LINE__, 9999, "assigne [%s] to mobile=%s", wFeedback.getidentifier(m_FbEvent), wItem.getid(l_Props) );

      if( StrOp.equals( wLoc.name(), NodeOp.getName(l_Props)))
        wLoc.setidentifier(l_Props, wFeedback.getidentifier(m_FbEvent));
      else
        wCar.setident(l_Props, wFeedback.getidentifier(m_FbEvent));

      if( !wxGetApp().isStayOffline() ) {
        /* Notify RocRail. */
        iONode cmd = NodeOp.inst( wModelCmd.name(), NULL, ELEMENT_NODE );
        wModelCmd.setcmd( cmd, wModelCmd.modify );
        NodeOp.addChild( cmd, (iONode)NodeOp.base.clone( l_Props ) );
        wxGetApp().sendToRocrail( cmd );
        cmd->base.del(cmd);
      }
      else {
        wxGetApp().setLocalModelModified(true);
      }

    }
  }
  dlg->Destroy();
  Raise();
}


