/*
 Rocrail - Model Railroad Software
 Copyright (c) 2002-2015 Robert Jan Versluis, Rocrail.net
 All rights reserved.
*/

#include "xmlscriptdlg.h"
#include "wx/wxprec.h"

#ifndef WX_PRECOMP
#include "wx/wx.h"
#include "wx/defs.h"
#endif

#include <wx/clipbrd.h>
#include <wx/dataobj.h>

#include "rocview/public/guiapp.h"
#include "rocview/public/base.h"
#include "rocrail/wrapper/public/DataReq.h"
#include "rocrail/wrapper/public/Item.h"
#include "rocrail/wrapper/public/Plan.h"

#include "rocs/public/trace.h"
#include "rocs/public/doc.h"
#include "rocs/public/node.h"

XmlScriptDlg::XmlScriptDlg( wxWindow* parent, iONode node ):xmlscriptdlggen( parent )
{
  m_Data = node;
  initLabels();
  GetSizer()->Layout();
  GetSizer()->Fit(this);
  GetSizer()->SetSizeHints(this);

  char* title = StrOp.fmt("XmlScript: %s", wDataReq.getfilename(m_Data) );
  SetTitle(wxString(title,wxConvUTF8) );
  StrOp.free(title);

  m_XML->SetValue( wxString(wDataReq.getdata(node),wxConvUTF8) );
}

void XmlScriptDlg::initLabels() {
  m_Validate->SetLabel( wxGetApp().getMsg( "validate" ) );
  m_Insert->SetLabel( wxGetApp().getMsg( "insert" ) );
  m_labStatement->SetLabel( wxGetApp().getMsg( "statement" ) );
  m_labCommandID->SetLabel( wxGetApp().getMsg( "id" ) );
  m_labCommand->SetLabel( wxGetApp().getMsg( "command" ) );

  m_Statement->Append(wxT("-- STATEMENTS --"));
  m_Statement->Append(wxT("break"));
  m_Statement->Append(wxT("call"));
  m_Statement->Append(wxT("comment"));
  m_Statement->Append(wxT("exit"));
  m_Statement->Append(wxT("foreach"));
  m_Statement->Append(wxT("if"));
  m_Statement->Append(wxT("sleep"));
  m_Statement->Append(wxT("sub"));
  m_Statement->Append(wxT("switch"));
  m_Statement->Append(wxT("while"));

  m_Statement->Append(wxT("-- COMMANDS --"));
  m_Statement->Append(wxT("automat"));
  m_Statement->Append(wxT("block"));
  m_Statement->Append(wxT("car"));
  m_Statement->Append(wxT("fiddleyard"));
  m_Statement->Append(wxT("function"));
  m_Statement->Append(wxT("location"));
  m_Statement->Append(wxT("locomotive"));
  m_Statement->Append(wxT("operator"));
  m_Statement->Append(wxT("output"));
  m_Statement->Append(wxT("route"));
  m_Statement->Append(wxT("sensor"));
  m_Statement->Append(wxT("signal"));
  m_Statement->Append(wxT("stagingblock"));
  m_Statement->Append(wxT("switch"));
  m_Statement->Append(wxT("system"));
  m_Statement->Append(wxT("text"));
  m_Statement->Append(wxT("variable"));
  // Buttons
  m_stdButtonSave->SetLabel( wxGetApp().getMsg( "save" ) );
  m_stdButtonCancel->SetLabel( wxGetApp().getMsg( "cancel" ) );
}

void XmlScriptDlg::onCancel( wxCommandEvent& event )
{
  EndModal(0);
}
void XmlScriptDlg::onClose( wxCloseEvent& event ) {
  EndModal(0);
}

bool XmlScriptDlg::validateXML(bool okmessage) {
  char* xml = StrOp.dup(m_XML->GetValue().mb_str(wxConvUTF8));
  long erroffset = 0;
  long scriptlen = StrOp.len(xml);
  long textsize  = m_XML->GetLastPosition();
  iODoc doc = DocOp.parseErr(xml, (int*)&erroffset);
  if( doc == NULL ) {
    wxMessageDialog( this, wxT("Not well formed XML. Error offset is ") + wxString::Format(wxT("%d of %d(%d)"),
        (int)erroffset, (int)scriptlen, (int)textsize ), wxT("Rocrail"), wxOK | wxICON_EXCLAMATION ).ShowModal();

    m_XML->Clear();
    bool backRed = false;
    for( int i = 0; i < scriptlen; i++ ) {
      if( i == erroffset ) {
        m_XML->SetDefaultStyle(wxTextAttr(*wxBLACK, Base::getRed()));
        backRed = true;
      }
      char str[2];
      str[0] = xml[i];
      str[1] = '\0';
      m_XML->AppendText(wxString(str,wxConvUTF8));
      if( backRed && xml[i] == '\n' ) {
        m_XML->SetDefaultStyle(wxTextAttr(*wxBLACK, *wxWHITE));
        backRed = false;
      }
    }

    StrOp.free(xml);
    return false;
  }
  iONode root = DocOp.getRootNode(doc);
  if( root == NULL ) {
    DocOp.base.del(doc);
    wxMessageDialog( this, wxT("Root node is missing."), wxT("Rocrail"), wxOK | wxICON_EXCLAMATION ).ShowModal();
    StrOp.free(xml);
    return false;
  }
  NodeOp.base.del(root);
  if( okmessage )
    wxMessageDialog( this, wxT("XMLScript is well formed."), wxT("Rocrail"), wxOK ).ShowModal();

  m_XML->Clear();
  m_XML->SetDefaultStyle(wxTextAttr(*wxBLACK, *wxWHITE));
  m_XML->SetValue( wxString(xml,wxConvUTF8) );
  StrOp.free(xml);
  return true;
}

void XmlScriptDlg::onValidate( wxCommandEvent& event ) {
  validateXML();
}

void XmlScriptDlg::onHelp( wxCommandEvent& event )
{
  wxGetApp().openLink( "xmlscripting" );
}

void XmlScriptDlg::onSave( wxCommandEvent& event )
{
  if( validateXML(false) ) {
    iONode cmd = NodeOp.inst( wDataReq.name(), NULL, ELEMENT_NODE );
    wDataReq.setcmd( cmd, wDataReq.writexmlscript );
    wDataReq.setfilename( cmd, wDataReq.getfilename(m_Data) );
    wDataReq.setdata( cmd, m_XML->GetValue().mb_str(wxConvUTF8) );
    wxGetApp().sendToRocrail( cmd );
    cmd->base.del(cmd);
    EndModal( wxID_OK );
  }
}


void XmlScriptDlg::onInsert( wxCommandEvent& event ) {
  char* statement = NULL;

  /* Statements */
  if( m_Statement->GetValue().StartsWith(wxT("if")) )
    statement = StrOp.dup("  <if condition=\"\">\n    <then>\n    </then>\n    <else>\n    </else>\n  </if>\n");
  else if( m_Statement->GetValue().StartsWith(wxT("foreach")) )
    statement = StrOp.dup("  <foreach table=\"\" condition=\"\">\n  </foreach>\n");
  else if( m_Statement->GetValue().StartsWith(wxT("while")) )
    statement = StrOp.dup("  <while condition=\"\">\n  </while>\n");
  else if( m_Statement->GetValue().StartsWith(wxT("switch")) )
    statement = StrOp.dup("  <switch var=\"\">\n    <case val=\"\">\n    </case>\n    <default>\n    </default>\n  </switch>\n");
  else if( m_Statement->GetValue().StartsWith(wxT("sub")) )
    statement = StrOp.dup("  <sub file=\"\" id=\"\"/>\n");
  else if( m_Statement->GetValue().StartsWith(wxT("call")) )
    statement = StrOp.dup("  <call id=\"\"/>\n");
  else if( m_Statement->GetValue().StartsWith(wxT("break")) )
    statement = StrOp.dup("  <break cmt=\"\"/>\n");
  else if( m_Statement->GetValue().StartsWith(wxT("exit")) )
    statement = StrOp.dup("  <exit cmt=\"\"/>\n");
  else if( m_Statement->GetValue().StartsWith(wxT("sleep")) )
    statement = StrOp.dup("  <sleep time=\"\"/>\n");
  else if( m_Statement->GetValue().StartsWith(wxT("comment")) )
    statement = StrOp.dup("  <!-- okay -->\n");

  /* Commands */
  else if( m_Statement->GetValue().StartsWith(wxT("variable")) )
    statement = StrOp.dup("  <vr id=\"\" text=\"\" value=\"\"/>\n");

  else if( m_Statement->GetValue().StartsWith(wxT("text")) )
    statement = StrOp.dup("  <tx id=\"\" format=\"\"/>\n");

  else if( m_Statement->GetValue().StartsWith(wxT("sensor")) )
    statement = StrOp.dup("  <fb id=\"\" cmd=\"\"/>\n");

  else if( m_Statement->GetValue().StartsWith(wxT("locomotive")) )
    statement = StrOp.dup("  <lc id=\"\" cmd=\"\"/>\n");

  else if( m_Statement->GetValue().StartsWith(wxT("switch")) )
    statement = StrOp.dup("  <sw id=\"\" cmd=\"\"/>\n");

  else if( m_Statement->GetValue().StartsWith(wxT("signal")) )
    statement = StrOp.dup("  <sg id=\"\" cmd=\"\"/>\n");

  else if( m_Statement->GetValue().StartsWith(wxT("function")) )
    statement = StrOp.dup("  <fn id=\"\" fnchanged=\"\" f?=\"\"/>\n");

  else if( m_Statement->GetValue().StartsWith(wxT("output")) )
    statement = StrOp.dup("  <co id=\"\" cmd=\"\"/>\n");

  else if( m_Statement->GetValue().StartsWith(wxT("block")) ) {
    const char* cmdStr = "cmd";
    const char* extra  = "";
    if(m_Command->GetValue().StartsWith(wxT("open")) || m_Command->GetValue().StartsWith(wxT("closed")) )
      cmdStr = "state";
    if(m_Command->GetValue().StartsWith(wxT("reserve")) )
      extra = " lcid=\"\"";
    if(m_Command->GetValue().StartsWith(wxT("classadd")) || m_Command->GetValue().StartsWith(wxT("classdel")) || m_Command->GetValue().StartsWith(wxT("classset")))
      extra = " class=\"\"";
    statement = StrOp.fmt("  <bk id=\"%s\" %s=\"%s\"%s/>\n",
        (const char*)m_CommandID->GetValue().mb_str(wxConvUTF8),
        cmdStr,
        (const char*)m_Command->GetValue().mb_str(wxConvUTF8),
        extra);
  }

  else if( m_Statement->GetValue().StartsWith(wxT("route")) )
    statement = StrOp.dup("  <st id=\"\" cmd=\"\"/>\n");

  else if( m_Statement->GetValue().StartsWith(wxT("operator")) )
    statement = StrOp.dup("  <operator id=\"\" cmd=\"\"/>\n");

  else if( m_Statement->GetValue().StartsWith(wxT("system")) )
    statement = StrOp.dup("  <sys id=\"\" cmd=\"\"/>\n");

  else if( m_Statement->GetValue().StartsWith(wxT("automat")) ) {
    statement = StrOp.fmt("  <auto cmd=\"%s\"/>\n", (const char*)m_Command->GetValue().mb_str(wxConvUTF8));
  }

  else if( m_Statement->GetValue().StartsWith(wxT("car")) ) {
    statement = StrOp.fmt("  <car id=\"%s\" cmd=\"%s\"/>\n",
        (const char*)m_CommandID->GetValue().mb_str(wxConvUTF8),
        (const char*)m_Command->GetValue().mb_str(wxConvUTF8));
  }

  else if( m_Statement->GetValue().StartsWith(wxT("location")) )
    statement = StrOp.dup("  <location id=\"\" cmd=\"\"/>\n");

  else if( m_Statement->GetValue().StartsWith(wxT("stagingblock")) )
    statement = StrOp.dup("  <sb id=\"\" cmd=\"\"/>\n");

  else if( m_Statement->GetValue().StartsWith(wxT("fiddleyard")) ) {
    const char* cmdStr = "cmd";
    if(m_Command->GetValue().StartsWith(wxT("open")) || m_Command->GetValue().StartsWith(wxT("closed")) )
      cmdStr = "state";
    statement = StrOp.fmt("  <seltab id=\"%s\" %s=\"%s\"/>\n",
        (const char*)m_CommandID->GetValue().mb_str(wxConvUTF8),
        cmdStr,
        (const char*)m_Command->GetValue().mb_str(wxConvUTF8) );
  }

  if( statement != NULL ) {
    TraceOp.trc( "xmlscriptdlg", TRCLEVEL_INFO, __LINE__, 9999,"copy=%s", statement );

    wxClipboard* cb = wxTheClipboard;
    if( cb != NULL ) {
      if( cb->Open() ) {
        wxString text( wxString(statement,wxConvUTF8) );
        if( !text.IsEmpty() ) {
          wxTextDataObject *data = new wxTextDataObject( text );
          cb->SetData( data );
        }
        cb->Close();
        TraceOp.trc( "xmlscriptdlg", TRCLEVEL_INFO, __LINE__, 9999,"paste..." );
        m_XML->Paste();
      }
    }
    StrOp.free(statement);
  }

}

static int __sortStr(obj* _a, obj* _b) {
    const char* a = (const char*)*_a;
    const char* b = (const char*)*_b;
    return strcmp( a, b );
}

void XmlScriptDlg::onStatement( wxCommandEvent& event ) {
  m_CommandID->Clear();
  m_Command->Clear();

  iONode model = wxGetApp().getModel();
  iOList list = ListOp.inst();

  /* automat */
  if( m_Statement->GetValue().StartsWith(wxT("automat")) ) {
    m_Command->Append( wxT("off") );
    m_Command->Append( wxT("on") );
    m_Command->Append( wxT("reset") );
    m_Command->Append( wxT("resume") );
    m_Command->Append( wxT("start") );
    m_Command->Append( wxT("startvirtual") );
    m_Command->Append( wxT("stop") );
    m_Command->Append( wxT("v0locos") );
    m_Command->Append( wxT("vrestorelocos") );
  }

  /* block */
  else if( m_Statement->GetValue().StartsWith(wxT("block")) ) {
    iONode bklist = wPlan.getbklist( model );
    if( bklist != NULL ) {
      int cnt = NodeOp.getChildCnt( bklist );
      for( int i = 0; i < cnt; i++ ) {
        iONode bk = NodeOp.getChild( bklist, i );
        ListOp.add(list, (obj)wItem.getid( bk ));
      }
    }
    m_Command->Append( wxT("classadd") );
    m_Command->Append( wxT("classdel") );
    m_Command->Append( wxT("classset") );
    m_Command->Append( wxT("closed") );
    m_Command->Append( wxT("open") );
    m_Command->Append( wxT("reserve") );
    m_Command->Append( wxT("resetfifo") );
    m_Command->Append( wxT("resetwc") );
    m_Command->Append( wxT("startassembletrain") );
    m_Command->Append( wxT("stopassembletrain") );
  }

  /* car */
  else if( m_Statement->GetValue().StartsWith(wxT("car")) ) {
    iONode carlist = wPlan.getcarlist( model );
    if( carlist != NULL ) {
      int cnt = NodeOp.getChildCnt( carlist );
      for( int i = 0; i < cnt; i++ ) {
        iONode car = NodeOp.getChild( carlist, i );
        ListOp.add(list, (obj)wItem.getid( car ));
      }
    }
    m_Command->Append( wxT("empty") );
    m_Command->Append( wxT("loaded") );
    m_Command->Append( wxT("maintenance") );
  }

  /* FY */
  else if( m_Statement->GetValue().StartsWith(wxT("fiddleyard")) ) {
    iONode fylist = wPlan.getseltablist( model );
    if( fylist != NULL ) {
      int cnt = NodeOp.getChildCnt( fylist );
      for( int i = 0; i < cnt; i++ ) {
        iONode fy = NodeOp.getChild( fylist, i );
        ListOp.add(list, (obj)wItem.getid( fy ));
      }
    }
    m_Command->Append( wxT("#") );
    m_Command->Append( wxT("closed") );
    m_Command->Append( wxT("next") );
    m_Command->Append( wxT("open") );
    m_Command->Append( wxT("prev") );
    m_Command->Append( wxT("unlock") );
  }

  ListOp.sort(list, &__sortStr);
  int cnt = ListOp.size( list );
  for( int i = 0; i < cnt; i++ ) {
    const char* id = (const char*)ListOp.get( list, i );
    m_CommandID->Append( wxString(id,wxConvUTF8) );
  }

  ListOp.base.del(list);
}

