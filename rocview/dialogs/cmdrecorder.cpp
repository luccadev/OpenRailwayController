/* Rocrail - Model Railroad Software Copyright (C) 2002-2013 Rob Versluis, Rocrail.net Without an official permission commercial use is not permitted. Forking this project is not permitted. This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later version. This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details. You should have received a copy of the GNU General Public License along with this program; if not, write to the Free Software Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.*/#include "cmdrecorder.h"#include "rocs/public/strtok.h"#include "rocview/symbols/svg.h"#include "rocview/public/base.h"#include "rocview/res/icons.hpp"#include "rocview/public/guiapp.h"#include "rocrail/public/script.h"#include "rocview/wrapper/public/Gui.h"CmdRecorder::CmdRecorder( wxWindow* parent )  :CmdRecorderGen( parent ){  m_Stop->SetBitmapLabel(*_img_stop);  m_Pause->SetBitmapLabel(*_img_pause);  m_Record->SetBitmapLabel(*_img_record);  m_Play->SetBitmapLabel(*_img_play);  GetSizer()->Layout();  GetSizer()->Fit(this);  GetSizer()->SetSizeHints(this);  Boolean recording = ScriptOp.isRecording(wxGetApp().getScript());  Boolean playing   = ScriptOp.isPlaying(wxGetApp().getScript(), NULL);  m_Record->Enable( recording?false:true );  m_Play->Enable( recording?false:true );  m_Pause->Enable( recording?false:true );  initList();}void CmdRecorder::onRecord( wxCommandEvent& event ){  if( !ScriptOp.isRecording(wxGetApp().getScript()) ) {    ScriptOp.setRecording(wxGetApp().getScript(), True);    m_Record->Enable( false );    m_Play->Enable( false );    m_Pause->Enable( false );  }}void CmdRecorder::onStop( wxCommandEvent& event ){  if( ScriptOp.isRecording(wxGetApp().getScript()) ) {    ScriptOp.setRecording(wxGetApp().getScript(), False);    m_Record->Enable( true );    m_Play->Enable( true );    m_Pause->Enable( true );    initList();  }  if( ScriptOp.isPlaying(wxGetApp().getScript(), NULL) ) {    ScriptOp.Stop(wxGetApp().getScript());  }}void CmdRecorder::onPause( wxCommandEvent& event ){  int linenr = 0;  if( ScriptOp.isPlaying(wxGetApp().getScript(), &linenr ) ) {    ScriptOp.Pause(wxGetApp().getScript());  }  m_CmdList->SetSelection(linenr);}void CmdRecorder::onPlay( wxCommandEvent& event ){  if( !ScriptOp.isRecording(wxGetApp().getScript()) ) {    ScriptOp.Play(wxGetApp().getScript());  }}void CmdRecorder::onCmdSelected( wxCommandEvent& event ){  int sel = m_CmdList->GetSelection();  if( sel != wxNOT_FOUND ) {    m_Cmd->SetValue(m_CmdList->GetString(sel));  }}void CmdRecorder::onModify( wxCommandEvent& event ){  int sel = m_CmdList->GetSelection();  if( sel != wxNOT_FOUND ) {    m_CmdList->SetString(sel, m_Cmd->GetValue());    int cnt = m_CmdList->GetCount();    char* script = NULL;    for( int i = 0; i < cnt; i++ ) {      script = StrOp.cat( script, m_CmdList->GetString(i).mb_str(wxConvUTF8) );      script = StrOp.cat( script, "\n" );    }    ScriptOp.setScript(wxGetApp().getScript(), script);    initList();  }}void CmdRecorder::onExport( wxCommandEvent& event ){  const char* l_openpath = wGui.getopenpath( wxGetApp().getIni() );  wxString ms_FileExt = _T("Commands (*.txt)|*.txt");  wxFileDialog* fdlg = new wxFileDialog(this, wxGetApp().getMenu("export"), wxString(l_openpath,wxConvUTF8), _T(""), ms_FileExt, wxFD_SAVE);  if( fdlg->ShowModal() == wxID_OK ) {    iONode model = wxGetApp().getModel();    // Check for existence.    wxString path = fdlg->GetPath();    if( FileOp.exist( path.mb_str(wxConvUTF8) ) ) {      int action = wxMessageDialog( this, wxGetApp().getMsg("fileexistwarning"), _T("Rocrail"), wxYES_NO | wxICON_EXCLAMATION ).ShowModal();      if( action == wxID_NO ) {        fdlg->Destroy();        return;      }    }    if( !path.Contains( _T(".txt") ) )      path.Append( _T(".txt") );    iOFile f = FileOp.inst( path.mb_str(wxConvUTF8), OPEN_WRITE );    if( f != NULL ) {      const char* cmds = ScriptOp.base.toString(wxGetApp().getScript());      FileOp.writeStr(f, cmds);      FileOp.base.del( f );    }  }  fdlg->Destroy();}void CmdRecorder::initList() {  m_CmdList->Clear();  const char* cmds = ScriptOp.base.toString(wxGetApp().getScript());  iOStrTok tok = StrTokOp.inst(cmds, '\n');  while( StrTokOp.hasMoreTokens(tok)) {    const char* cmd = StrTokOp.nextToken(tok);    m_CmdList->Append(wxString(cmd,wxConvUTF8));  }}void CmdRecorder::onImport( wxCommandEvent& event ){  wxString ms_FileExt = _T("Commands (*.txt)|*.txt");  const char* l_openpath = wGui.getopenpath( wxGetApp().getIni() );  wxFileDialog* fdlg = new wxFileDialog(this, wxGetApp().getMenu("import"), wxString(l_openpath,wxConvUTF8) , _T(""), ms_FileExt, wxFD_OPEN);  if( fdlg->ShowModal() == wxID_OK ) {    if( fdlg->GetPath().Len() > 0 && FileOp.exist(fdlg->GetPath().mb_str(wxConvUTF8)) ) {      iOFile f = FileOp.inst( fdlg->GetPath().mb_str(wxConvUTF8), OPEN_READONLY );      char* buffer = (char*)allocMem( FileOp.size( f ) +1 );      FileOp.read( f, buffer, FileOp.size( f ) );      ScriptOp.setScript(wxGetApp().getScript(), buffer);      FileOp.base.del( f );      initList();    }  }  fdlg->Destroy();}void CmdRecorder::onDelete( wxCommandEvent& event ){  int sel = m_CmdList->GetSelection();  if( sel != wxNOT_FOUND ) {    m_CmdList->Delete(sel);    int cnt = m_CmdList->GetCount();    char* script = NULL;    for( int i = 0; i < cnt; i++ ) {      script = StrOp.cat( script, m_CmdList->GetString(i).mb_str(wxConvUTF8) );      script = StrOp.cat( script, "\n" );    }    ScriptOp.setScript(wxGetApp().getScript(), script);    initList();  }}void CmdRecorder::onInsert( wxCommandEvent& event ){  int sel = m_CmdList->GetSelection();  if( sel != wxNOT_FOUND ) {    m_CmdList->Insert(m_Cmd->GetValue(), sel);  }  else {    m_CmdList->Append(m_Cmd->GetValue());  }  int cnt = m_CmdList->GetCount();  char* script = NULL;  for( int i = 0; i < cnt; i++ ) {    script = StrOp.cat( script, m_CmdList->GetString(i).mb_str(wxConvUTF8) );    script = StrOp.cat( script, "\n" );  }  ScriptOp.setScript(wxGetApp().getScript(), script);  initList();}void CmdRecorder::onOK( wxCommandEvent& event ){  Destroy();}void CmdRecorder::onClose( wxCloseEvent& event ){  Destroy();}