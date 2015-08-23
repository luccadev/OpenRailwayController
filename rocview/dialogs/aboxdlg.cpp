/*
 Rocrail - Model Railroad Software
 Copyright (c) 2002-2015 Robert Jan Versluis, Rocrail.net
 All rights reserved.
*/



#include "aboxdlg.h"
#include "wx/wxprec.h"

#ifndef WX_PRECOMP
#include "wx/wx.h"
#include "wx/defs.h"
#endif

#include <wx/filedlg.h>
#include <wx/mimetype.h>
#include <wx/filename.h>

#include "rocview/public/guiapp.h"
#include "rocview/wrapper/public/Gui.h"
#include "rocview/wrapper/public/ABox.h"
#include "rocview/wrapper/public/ABoxApp.h"

#include "rocrail/wrapper/public/DataReq.h"
#include "rocrail/wrapper/public/DirEntry.h"
#include "rocrail/wrapper/public/FileEntry.h"

#include "rocs/public/strtok.h"
#include "rocs/public/system.h"

#include "rocview/res/icons.hpp"

static bool ms_Sort = true;

ABoxDlg::ABoxDlg( wxWindow* parent, const char* text, const char* title ):AboxDlgGen( parent )
{
  m_StubList = ListOp.inst();
  m_SelectedStub = wxNOT_FOUND;
  m_ReadOnly = false;
  m_SortCol = 0;
  m_AddedFilename[0] = '\0';
  m_AddedUID[0] = '\0';
  m_AddedPart = -1;
  m_DownloadFilename[0] = '\0';
  m_DownloadUID[0] = '\0';
  m_DownloadPart = -1;
  m_Enable = true;

  m_Ini = wGui.getabox( wxGetApp().getIni() );
  if( m_Ini == NULL ) {
    m_Ini = NodeOp.inst(wABox.name(), wxGetApp().getIni(), ELEMENT_NODE);
    NodeOp.addChild( wxGetApp().getIni(), m_Ini );
  }

  m_FindInText->SetValue(wABox.isfindintext(m_Ini)?true:false);
  m_FindInCategory->SetValue(wABox.isfindincategory(m_Ini)?true:false);
  m_FindInFilename->SetValue(wABox.isfindinfilename(m_Ini)?true:false);
  m_FindInDate->SetValue(wABox.isfindindate(m_Ini)?true:false);
  m_ShowPath->SetValue(wABox.isshowpath(m_Ini)?true:false);
  m_Link->SetValue(wABox.islink(m_Ini)?true:false);

  m_Open->Enable(false);
  m_SelectApp->Enable(false);
  m_Modify->Enable(false);
  m_Delete->Enable(false);
  //m_Link->Enable(false); // only links are supported

  initLabels();

  m_FromDate->SetValue(wxDateTime::Now());
  m_ToDate->SetValue(wxDateTime::Now());

  iONode cmd = NodeOp.inst( wDataReq.name(), NULL, ELEMENT_NODE );
  wDataReq.setcmd( cmd, wDataReq.abox_getcategories );
  wxGetApp().sendToRocrail( cmd );
  cmd->base.del(cmd);

  if( title != NULL ) {
    SetTitle(wxT("Archivebox: ") + wxString(title,wxConvUTF8) );
  }

  if( text != NULL ) {
    m_FindText->SetValue( wxString(text,wxConvUTF8) );
    doFind(text);
  }
  else
    doFind("");
}

ABoxDlg::~ABoxDlg() {
  clearStubList();
}

void ABoxDlg::clearStubList() {
  for(int i = 0; i < ListOp.size(m_StubList); i++) {
    iONode stub = (iONode)ListOp.get(m_StubList, i);
    NodeOp.base.del(stub);
  }
  ListOp.clear(m_StubList);
}

void ABoxDlg::initLabels() {
  m_Find->SetLabel( wxGetApp().getMsg( "find" ) );
  m_FindInText->SetLabel( wxGetApp().getMsg( "text" ) );
  m_FindInCategory->SetLabel( wxGetApp().getMsg( "category" ) );
  m_FindInFilename->SetLabel( wxGetApp().getMsg( "filename" ) );
  m_FindInDate->SetLabel( wxGetApp().getMsg( "date" ) );
  m_labFromDate->SetLabel( wxGetApp().getMsg( "fromdate" ) );
  m_labToDate->SetLabel( wxGetApp().getMsg( "todate" ) );
  m_Add->SetLabel( wxGetApp().getMsg( "add" ) );
  m_Open->SetLabel( wxGetApp().getMsg( "open" ) );
  m_SelectApp->SetLabel( wxGetApp().getMsg( "select" ) + wxT("...") );
  m_Modify->SetLabel( wxGetApp().getMsg( "modify" ) );
  m_Delete->SetLabel( wxGetApp().getMsg( "delete" ) );
  m_labFile->SetLabel( wxGetApp().getMsg( "file" ) );
  m_labText->SetLabel( wxGetApp().getMsg( "text" ) );
  m_labCategory->SetLabel( wxGetApp().getMsg( "category" ) );
  m_labResultText->SetLabel( wxGetApp().getMsg( "text" ) );
  m_labResultNote->SetLabel( wxGetApp().getMsg( "note" ) );
  m_Link->SetLabel( wxGetApp().getMsg( "link" ) );
  m_ShowPath->SetLabel( wxGetApp().getMsg( "showpath" ) );

  m_FindBox->GetStaticBox()->SetLabel( wxGetApp().getMsg( "find" ) );
  m_UploadBox->GetStaticBox()->SetLabel( wxGetApp().getMsg( "add" ) );
  m_ResultBox->GetStaticBox()->SetLabel( wxGetApp().getMsg( "result" ) );

  m_Stubs->InsertColumn(0, wxGetApp().getMsg( "file" ), wxLIST_FORMAT_LEFT );
  m_Stubs->InsertColumn(1, wxGetApp().getMsg( "category" ), wxLIST_FORMAT_LEFT );
  m_Stubs->InsertColumn(2, wxGetApp().getMsg( "text" ), wxLIST_FORMAT_LEFT );
  m_Stubs->InsertColumn(3, wxT( "UID" ), wxLIST_FORMAT_LEFT );
  m_Stubs->InsertColumn(4, wxGetApp().getMsg( "link" ), wxLIST_FORMAT_CENTER );
  m_Stubs->InsertColumn(5, wxGetApp().getMsg( "date" ), wxLIST_FORMAT_CENTER );
  m_Stubs->InsertColumn(6, wxGetApp().getMsg( "size" ), wxLIST_FORMAT_RIGHT );

  m_bmpFind->SetBitmap(*_img_find);
  m_bmpUpload->SetBitmap(*_img_upload);
  m_bmpOpen->SetBitmap(*_img_view);

}

void ABoxDlg::EnableDlg(bool enable) {
  m_Enable = enable;

  m_Find->Enable(enable);
  if( m_Enable )
    m_Add->Enable(!m_ReadOnly);
  else
    m_Add->Enable(enable);
  m_Open->Enable(enable);
  m_SelectApp->Enable(enable);
  m_Modify->Enable(enable);
  m_Delete->Enable(enable);
  m_Stubs->Enable(enable);
  m_Link->Enable(enable);
  m_ShowPath->Enable(enable);
  m_bmpFind->Enable(enable);
  m_bmpUpload->Enable(enable);
  m_bmpOpen->Enable(enable);
}

void ABoxDlg::doFind( const char* text ) {
  wABox.setfindintext(m_Ini, m_FindInText->IsChecked()?True:False);
  wABox.setfindincategory(m_Ini, m_FindInCategory->IsChecked()?True:False);
  wABox.setfindinfilename(m_Ini, m_FindInFilename->IsChecked()?True:False);
  wABox.setfindindate(m_Ini, m_FindInDate->IsChecked()?True:False);

  iONode cmd = NodeOp.inst( wDataReq.name(), NULL, ELEMENT_NODE );
  wDataReq.setcmd( cmd, wDataReq.abox_find );
  wDataReq.settext( cmd, text );
  wDataReq.setfindintext( cmd, m_FindInText->IsChecked()?True:False );
  wDataReq.setfindincategory( cmd, m_FindInCategory->IsChecked()?True:False );
  wDataReq.setfindinfilename( cmd, m_FindInFilename->IsChecked()?True:False );
  wDataReq.setfindindate( cmd, m_FindInDate->IsChecked()?True:False );

  wxDateTime fromdate = m_FromDate->GetValue();
  wxDateTime todate   = m_ToDate->GetValue();
  char* dateStr = StrOp.fmt("%d%02d%02d", fromdate.GetYear(), fromdate.GetMonth()+1, fromdate.GetDay());
  wDataReq.setfromdate(cmd, dateStr);
  StrOp.free(dateStr);
  dateStr = StrOp.fmt("%d%02d%02d", todate.GetYear(), todate.GetMonth()+1, todate.GetDay());
  wDataReq.settodate(cmd, dateStr);
  StrOp.free(dateStr);

  wxGetApp().sendToRocrail( cmd );
  cmd->base.del(cmd);
}

void ABoxDlg::onFind( wxCommandEvent& event ) {
  doFind(m_FindText->GetValue().mb_str(wxConvUTF8));
}

void ABoxDlg::onFindTextEnter( wxCommandEvent& event ) {
  doFind(m_FindText->GetValue().mb_str(wxConvUTF8));
}

void ABoxDlg::onSelectFile( wxCommandEvent& event ) {
  wxFileDialog* fdlg = new wxFileDialog(this);
  if( fdlg->ShowModal() == wxID_OK ) {
    m_Filename->SetValue(fdlg->GetPath());
  }
  fdlg->Destroy();
  Raise();
}

void ABoxDlg::onAdd( wxCommandEvent& event ) {
  if( m_Filename->GetValue().IsEmpty() || m_Text->GetValue().IsEmpty() || m_Category->GetValue().IsEmpty() ) {
    // Upload criteria missing.
    int action = wxMessageDialog( this, wxGetApp().getMsg("missingcriteria"), _T("Rocrail"), wxOK | wxICON_EXCLAMATION ).ShowModal();
    return;
  }
  if( StrOp.startsWithi(m_Filename->GetValue().mb_str(wxConvUTF8), "http"))
    m_Link->SetValue(true);

  wABox.setlink(m_Ini, m_Link->IsChecked()?True:False);

  iONode cmd = NodeOp.inst( wDataReq.name(), NULL, ELEMENT_NODE );
  wDataReq.setcmd( cmd, wDataReq.abox_addlink );
  wDataReq.setlink( cmd, m_Link->IsChecked()?True:False);

  iONode direntry = NodeOp.inst(wDirEntry.name(), cmd, ELEMENT_NODE );
  NodeOp.addChild(cmd, direntry);
  iONode fileentry = NodeOp.inst(wFileEntry.name(), cmd, ELEMENT_NODE );
  NodeOp.addChild(direntry, fileentry);

  wFileEntry.setfname( fileentry, m_Filename->GetValue().mb_str(wxConvUTF8) );

  // save the file path in case it must be uploaded
  m_AddedUID[0] = '\0';
  if( !m_Link->IsChecked() ) {
    StrOp.copy( m_AddedFilename, wFileEntry.getfname(fileentry) );
    EnableDlg(false);
  }
  else
    m_AddedFilename[0] = '\0';

  wFileEntry.settext( fileentry, m_Text->GetValue().mb_str(wxConvUTF8) );
  wFileEntry.setcategory( fileentry, m_Category->GetValue().mb_str(wxConvUTF8) );
  if( !StrOp.startsWithi(wFileEntry.getfname(fileentry), "http"))
    wFileEntry.setsize(fileentry, FileOp.fileSize(wFileEntry.getfname(fileentry)));

  if( !StrOp.startsWithi(wFileEntry.getfname(fileentry), "http")) {
    char   dateStr[20];
    long aTime = FileOp.fileTime( wFileEntry.getfname(fileentry) );
    strftime( dateStr, sizeof(dateStr), "%Y%m%d", localtime(&aTime) );
    wFileEntry.setfiledate(fileentry, dateStr);
    strftime( dateStr, sizeof(dateStr), "%H%M%S", localtime(&aTime) );
    wFileEntry.setfiletime(fileentry, dateStr);
  }

  char* s = NodeOp.base.toString(cmd);
  TraceOp.trc( "aboxdlg", TRCLEVEL_INFO, __LINE__, 9999, "add: %s", s );
  StrOp.free(s);

  wxGetApp().sendToRocrail( cmd );
  cmd->base.del(cmd);

  m_FindText->SetValue(m_Text->GetValue());

  m_Filename->SetValue(wxT(""));
  m_Text->SetValue(wxT(""));
  m_Category->SetValue(wxT(""));

  onFind(event);

  cmd = NodeOp.inst( wDataReq.name(), NULL, ELEMENT_NODE );
  wDataReq.setcmd( cmd, wDataReq.abox_getcategories );
  wxGetApp().sendToRocrail( cmd );
  cmd->base.del(cmd);
}

void ABoxDlg::executeStub(const char* filepath) {
  const char* ext = StrOp.getExtension(filepath);
  iONode theAboxApp = NULL;
  iONode aboxapp = wABox.getaboxapp(m_Ini);
  while(aboxapp != NULL) {
    if( StrOp.equalsi(wABoxApp.getext(aboxapp), ext ) ) {
      theAboxApp = aboxapp;
      break;
    }
    aboxapp = wABox.nextaboxapp(m_Ini, aboxapp);
  }
  if( theAboxApp != NULL ) {
    wxExecute(wxString(wABoxApp.getapp(theAboxApp),wxConvUTF8) + wxT(" \"") + wxString(filepath,wxConvUTF8) + wxT("\"") );
    return;
  }

  wxFileType *filetype=wxTheMimeTypesManager->GetFileTypeFromExtension(wxString(StrOp.getExtension(filepath),wxConvUTF8));
  if( filetype == NULL ) {
    char* tip = StrOp.fmt( wxGetApp().getCMsg("nodefaultapplicationfound"), filepath );
    int action = wxMessageDialog( this, wxString(tip,wxConvUTF8), _T("Rocrail"), wxOK | wxICON_EXCLAMATION ).ShowModal();
    StrOp.free(tip);
    return;
  }
  wxString command=filetype->GetOpenCommand(wxString(filepath,wxConvUTF8));
  TraceOp.trc( "aboxdlg", TRCLEVEL_INFO, __LINE__, 9999, "execute [%s]", (const char*)command.mb_str(wxConvUTF8) );
  if( command.IsEmpty() ) {
    // No default application...
    char* tip = StrOp.fmt( wxGetApp().getCMsg("nodefaultapplicationfound"), filepath );
    int action = wxMessageDialog( this, wxString(tip,wxConvUTF8), _T("Rocrail"), wxOK | wxICON_EXCLAMATION ).ShowModal();
    StrOp.free(tip);
  }
  else {
    wxExecute(command);
  }
}

void ABoxDlg::openStub() {
  iONode stub = (iONode)m_Stubs->GetItemData(m_SelectedStub);
  if( NodeOp.getBool(stub, "link", True) ) {
    executeStub(NodeOp.getStr(stub, "path", "-"));
  }
  else {
    // Download file.
    wxString tempdir = wxFileName::GetTempDir();
    char* filepath = StrOp.fmt("%s%c%s", (const char*)tempdir.mb_str(wxConvUTF8), SystemOp.getFileSeparator(), NodeOp.getStr(stub, "path", "-") );
    TraceOp.trc( "aboxdlg", TRCLEVEL_INFO, __LINE__, 9999, "tempdir [%s]", filepath );

    if( FileOp.exist(filepath) ) {
      executeStub(filepath);
    }
    else {
      EnableDlg(false);
      StrOp.copy(m_DownloadFilename, NodeOp.getStr(stub, "path", "-"));
      StrOp.copy(m_DownloadUID, NodeOp.getStr(stub, "uid", "-"));
      m_DownloadPart = 0;

      iONode cmd = NodeOp.inst( wDataReq.name(), NULL, ELEMENT_NODE );
      wDataReq.setcmd( cmd, wDataReq.abox_getdata );
      wDataReq.setid( cmd, NodeOp.getStr(stub, "uid", "-") );
      wDataReq.setcategory( cmd, NodeOp.getStr(stub, "category", "-") );
      wDataReq.setfilename(cmd, NodeOp.getStr(stub, "path", "-"));
      wDataReq.setdatapart(cmd, m_DownloadPart);
      wxGetApp().sendToRocrail( cmd );
      cmd->base.del(cmd);
    }

    StrOp.free(filepath);
  }
}

#define MAXHEIGHT 100
#define MAXWIDTH  100
void ABoxDlg::showStub() {
  iONode stub = (iONode)m_Stubs->GetItemData(m_SelectedStub);
  m_ResultText->SetValue(wxString(NodeOp.getStr(stub, "text", "-"),wxConvUTF8));
  m_ResultNote->SetValue(wxString(NodeOp.getStr(stub, "note", ""),wxConvUTF8));

  char* path = NULL;
  if( NodeOp.getBool(stub, "link", True) ) {
    path = StrOp.dup(NodeOp.getStr(stub, "path", "-"));
  }
  else {
    wxString tempdir = wxFileName::GetTempDir();
    path = StrOp.fmt("%s%c%s", (const char*)tempdir.mb_str(wxConvUTF8), SystemOp.getFileSeparator(), NodeOp.getStr(stub, "path", "-") );
  }
  if( path != NULL ) {
    wxImage image( wxString(path,wxConvUTF8) );
    StrOp.free(path);
    if( image.IsOk() ) {
      int h = image.GetHeight();
      int w = image.GetWidth();
      if( h > MAXHEIGHT || w > MAXWIDTH ) {
        float scaleH = (float)h / (float)MAXHEIGHT;
        float scaleW = (float)w / (float)MAXWIDTH;
        float scale = 1.0;
        if( scaleH > scaleW )
          scale = scaleH;
        else
          scale = scaleW;
        float width = (float)w / scale;
        float height = (float)h / scale;
        wxBitmap bmp(image.Scale((int)width, (int)height, wxIMAGE_QUALITY_HIGH));
        m_Preview->SetBitmap(bmp);
      }
      else {
        wxBitmap bmp(image);
        m_Preview->SetBitmap(bmp);
      }
    }
    else {
      if( StrOp.endsWithi(path, ".pdf") )
        m_Preview->SetBitmap(*_img_pdf);
      else
        m_Preview->SetBitmap(*_img_document);
    }
  }
  else {
    m_Preview->SetBitmap(*_img_document);
  }

  m_Preview->Refresh();
  m_PreviewSizer->Layout();

}

void ABoxDlg::onStubActivated( wxListEvent& event ) {
  m_SelectedStub = event.GetIndex();
  m_Open->Enable(true);
  m_SelectApp->Enable(true);
  m_Modify->Enable(!m_ReadOnly);
  m_Delete->Enable(!m_ReadOnly);
  openStub();
}

void ABoxDlg::onStubSelected( wxListEvent& event ) {
  m_SelectedStub = event.GetIndex();
  m_Open->Enable(true);
  m_SelectApp->Enable(true);
  m_Modify->Enable(!m_ReadOnly);
  m_Delete->Enable(!m_ReadOnly);
  showStub();
}


static int __sortPath(obj* _a, obj* _b) {
    iONode a = (iONode)*_a;
    iONode b = (iONode)*_b;
    const char* idA = NodeOp.getStr(a, "path", "-");
    const char* idB = NodeOp.getStr(b, "path", "-");
    return ms_Sort ? strcmp( idA, idB ):strcmp( idB, idA );
}
static int __sortFilename(obj* _a, obj* _b) {
    iONode a = (iONode)*_a;
    iONode b = (iONode)*_b;
    const char* idA = FileOp.ripPath(NodeOp.getStr(a, "path", "-"));
    const char* idB = FileOp.ripPath(NodeOp.getStr(b, "path", "-"));
    return ms_Sort ? strcmp( idA, idB ):strcmp( idB, idA );
}
static int __sortCategory(obj* _a, obj* _b) {
    iONode a = (iONode)*_a;
    iONode b = (iONode)*_b;
    const char* idA = NodeOp.getStr(a, "category", "-");
    const char* idB = NodeOp.getStr(b, "category", "-");
    return ms_Sort ? strcmp( idA, idB ):strcmp( idB, idA );
}
static int __sortText(obj* _a, obj* _b) {
    iONode a = (iONode)*_a;
    iONode b = (iONode)*_b;
    const char* idA = NodeOp.getStr(a, "text", "-");
    const char* idB = NodeOp.getStr(b, "text", "-");
    return ms_Sort ? strcmp( idA, idB ):strcmp( idB, idA );
}
static int __sortUID(obj* _a, obj* _b) {
    iONode a = (iONode)*_a;
    iONode b = (iONode)*_b;
    const char* idA = NodeOp.getStr(a, "uid", "-");
    const char* idB = NodeOp.getStr(b, "uid", "-");
    return ms_Sort ? strcmp( idA, idB ):strcmp( idB, idA );
}
static int __sortLink(obj* _a, obj* _b) {
    iONode a = (iONode)*_a;
    iONode b = (iONode)*_b;
    const char* idA = NodeOp.getBool(a, "link", True)?"X":"-";
    const char* idB = NodeOp.getBool(b, "link", True)?"X":"-";
    return ms_Sort ? strcmp( idA, idB ):strcmp( idB, idA );
}
static int __sortDate(obj* _a, obj* _b) {
    iONode a = (iONode)*_a;
    iONode b = (iONode)*_b;
    const char* idA = NodeOp.getStr(a, "filedate", "-");
    const char* idB = NodeOp.getStr(b, "filedate", "-");
    return ms_Sort ? strcmp( idA, idB ):strcmp( idB, idA );
}
static int __sortSize(obj* _a, obj* _b) {
    iONode a = (iONode)*_a;
    iONode b = (iONode)*_b;
    long A = NodeOp.getLong(a, "size", 0);
    long B = NodeOp.getLong(b, "size", 0);
    if( A > B )
      return ms_Sort?-1:1;
    if( A < B )
      return ms_Sort?1:-1;
    return 0;
}


void ABoxDlg::initResult() {
  m_Stubs->DeleteAllItems();
  m_ResultText->SetValue(wxT(""));
  m_ResultNote->SetValue(wxT(""));

  m_Preview->SetBitmap(*_img_abox);
  m_Preview->Refresh();
  m_PreviewSizer->Layout();


  iOList list = ListOp.inst();
  int listSize = ListOp.size(m_StubList);
  for( int idx = 0; idx < listSize; idx++ ) {
    ListOp.add(list, ListOp.get(m_StubList, idx));
  }

  if( m_SortCol == 1 ) {
    ListOp.sort(list, &__sortCategory);
  }
  else if( m_SortCol == 2 ) {
    ListOp.sort(list, &__sortText);
  }
  else if( m_SortCol == 3 ) {
    ListOp.sort(list, &__sortUID);
  }
  else if( m_SortCol == 4 ) {
    ListOp.sort(list, &__sortLink);
  }
  else if( m_SortCol == 5 ) {
    ListOp.sort(list, &__sortDate);
  }
  else if( m_SortCol == 6 ) {
    ListOp.sort(list, &__sortSize);
  }
  else {
    if( m_ShowPath->IsChecked() )
      ListOp.sort(list, &__sortPath);
    else
      ListOp.sort(list, &__sortFilename);
  }

  listSize = ListOp.size(list);
  for( int idx = 0; idx < listSize; idx++ ) {
    iONode stub = (iONode)ListOp.get( list, idx);
    if( m_ShowPath->IsChecked() )
      m_Stubs->InsertItem( idx, wxString(NodeOp.getStr(stub, "path", "-"),wxConvUTF8) );
    else {
      char* s = StrOp.dup(NodeOp.getStr(stub, "path", "-"));
      m_Stubs->InsertItem( idx, wxString(FileOp.ripPath(s),wxConvUTF8) );
      StrOp.free(s);
    }
    m_Stubs->SetItem( idx, 1, wxString(NodeOp.getStr(stub, "category", "-"),wxConvUTF8) );
    m_Stubs->SetItem( idx, 2, wxString(NodeOp.getStr(stub, "text", "-"),wxConvUTF8) );
    m_Stubs->SetItem( idx, 3, wxString(NodeOp.getStr(stub, "uid", "-"),wxConvUTF8) );
    m_Stubs->SetItem( idx, 4, wxString(NodeOp.getBool(stub, "link", True)?"X":"-",wxConvUTF8) );
    m_Stubs->SetItem( idx, 5, wxString(NodeOp.getStr(stub, "filedate", "-"),wxConvUTF8) );
    m_Stubs->SetItem( idx, 6, wxString(NodeOp.getStr(stub, "size", "0"),wxConvUTF8) );
    m_Stubs->SetItemPtrData(idx, (wxUIntPtr)stub);
  }

  ListOp.base.del(list);

  // resize
  for( int n = 0; n < 7; n++ ) {
    m_Stubs->SetColumnWidth(n, wxLIST_AUTOSIZE_USEHEADER);
    int autoheadersize = m_Stubs->GetColumnWidth(n);
    m_Stubs->SetColumnWidth(n, wxLIST_AUTOSIZE);
    int autosize = m_Stubs->GetColumnWidth(n);
    if(autoheadersize > autosize )
      m_Stubs->SetColumnWidth(n, wxLIST_AUTOSIZE_USEHEADER);
  }
}

bool ABoxDlg::readDataBlock(const char* filename, iONode node, int nr) {
  bool lastBlock = false;
  iOFile f = FileOp.inst( m_AddedFilename, OPEN_READONLY );
  if( f != NULL ) {
    long totalsize = FileOp.fileSize(filename);
    byte* buffer = (byte*)allocMem(DATABLOCK+1);
    FileOp.setpos(f, nr*DATABLOCK);
    long bufferSize = DATABLOCK;
    if( (totalsize - nr*DATABLOCK <  DATABLOCK) || totalsize - nr*DATABLOCK == DATABLOCK ) {
      bufferSize = totalsize - nr*DATABLOCK;
      lastBlock = true;
    }
    TraceOp.trc( "aboxdlg", TRCLEVEL_INFO, __LINE__, 9999, "uploading file data %ld of %ld (last=%s)", bufferSize, totalsize, lastBlock?"true":"false" );

    FileOp.read(f, (char*)buffer, bufferSize);

    char* filedata = StrOp.byteToStr(buffer, bufferSize);
    wDataReq.setdata(node, filedata );
    wDataReq.setdataparts(node, totalsize / DATABLOCK + ( (totalsize % DATABLOCK) > 0 ? 1:0 ) );
    wDataReq.settotalsize(node, totalsize);

    FileOp.base.del(f);
    wDataReq.setdatapart(node, nr);
    freeMem(buffer);
    StrOp.free(filedata);
  }
  return lastBlock;
}

void ABoxDlg::event(iONode node) {
  char* s = NodeOp.base.toString(node);
  TraceOp.trc( "aboxdlg", TRCLEVEL_INFO, __LINE__, 9999, "event: %.256s", s );
  StrOp.free(s);

  if( wDataReq.getcmd(node) == wDataReq.abox_addlink ) {
    const char* uid = wDataReq.getid(node);
    iONode direntry = wDataReq.getdirentry(node);
    if( direntry != NULL && wDirEntry.getfileentry(direntry) != NULL ) {
      iONode fileentry = wDirEntry.getfileentry(direntry);
      TraceOp.trc( "aboxdlg", TRCLEVEL_INFO, __LINE__, 9999, "uid=%s for [%s] added=[%s]", uid, wFileEntry.getfname(fileentry), m_AddedFilename );
      /*
      char* s = StrOp.fmt("%s:\nUID=%s\n%s=%s", wxGetApp().getCMsg("upload"), uid, wxGetApp().getCMsg("file"), wFileEntry.getfname(fileentry) );
      int action = wxMessageDialog( this, wxString(s,wxConvUTF8), _T("Rocrail"), wxOK ).ShowModal();
      StrOp.free(s);
      */
      if( StrOp.equals( wFileEntry.getfname(fileentry), m_AddedFilename ) ) {
        TraceOp.trc( "aboxdlg", TRCLEVEL_INFO, __LINE__, 9999, "start upload of [%s]...", wFileEntry.getfname(fileentry) );
        StrOp.copy( m_AddedUID, uid );
        iONode cmd = NodeOp.inst( wDataReq.name(), NULL, ELEMENT_NODE );
        wDataReq.setcmd( cmd, wDataReq.abox_filedata );
        wDataReq.setid( cmd, uid );
        wDataReq.setcategory(cmd, wFileEntry.getcategory(fileentry));
        wDataReq.setfilename(cmd, FileOp.ripPath(m_AddedFilename));
        wDataReq.setdatapart(cmd, 0);

        if( readDataBlock(wFileEntry.getfname(fileentry), cmd, 0) ) {
          m_AddedFilename[0] = '\0';
          m_AddedUID[0] = '\0';
          EnableDlg(true);
        }
        wxGetApp().sendToRocrail( cmd );
        cmd->base.del(cmd);
      }
    }
  }

  else if( wDataReq.getcmd(node) == wDataReq.abox_getdata ) {
    TraceOp.trc( "aboxdlg", TRCLEVEL_INFO, __LINE__, 9999, "getdata..." );
    /*
     * <datareq cmd="11" id="20150816093859345" category="Zomaar" filename="paspoort-2014.jpeg" datapart="0" controlcode="" server="infw5601F5A0" data="FFD8FFE0
     */
    if( StrOp.equals(m_DownloadUID, wDataReq.getid(node)) ) {

      if(wDataReq.getrc(node) != 0) {
        m_DownloadFilename[0] = '\0';
        m_DownloadUID[0] = '\0';
        m_DownloadPart = -1;
        m_labDownloadState->SetLabel(wxT(""));
        EnableDlg(true);
        int action = wxMessageDialog( this, wxT("Error getting file data!"), _T("Rocrail"), wxOK | wxICON_EXCLAMATION ).ShowModal();
        return;
      }

      wxString tempdir = wxFileName::GetTempDir();
      char* filepath = StrOp.fmt("%s%c%s", (const char*)tempdir.mb_str(wxConvUTF8), SystemOp.getFileSeparator(), wDataReq.getfilename(node)  );

      iOFile f = FileOp.inst(filepath, OPEN_APPEND);
      if( f != NULL ) {
        const char* byteStr = wDataReq.getdata(node);
        byte* filedata = StrOp.strToByte( byteStr );
        int len = StrOp.len(byteStr)/2;
        FileOp.write(f, (char*)filedata, len);
        FileOp.base.del(f);
        freeMem(filedata);
      }

      if( !wDataReq.isack(node) ) {
        // get next part
        iONode cmd = NodeOp.inst( wDataReq.name(), NULL, ELEMENT_NODE );
        wDataReq.setcmd( cmd, wDataReq.abox_getdata );
        wDataReq.setid( cmd, wDataReq.getid(node) );
        wDataReq.setcategory( cmd, wDataReq.getcategory(node) );
        wDataReq.setfilename(cmd, wDataReq.getfilename(node) );
        m_DownloadPart++;
        m_labDownloadState->SetLabel(wxString::Format(wxT("%d"), m_DownloadPart));
        wDataReq.setdatapart(cmd, m_DownloadPart);
        wxGetApp().sendToRocrail( cmd );
        cmd->base.del(cmd);
      }
      else {
        m_DownloadFilename[0] = '\0';
        m_DownloadUID[0] = '\0';
        m_DownloadPart = -1;
        m_labDownloadState->SetLabel(wxT(""));
        EnableDlg(true);
        executeStub(filepath);
      }
      StrOp.free(filepath);
    }
  }


  else if( wDataReq.getcmd(node) == wDataReq.abox_filedata ) {
    TraceOp.trc( "aboxdlg", TRCLEVEL_INFO, __LINE__, 9999, "filedata..." );
    // <datareq cmd="10" id="20150816081059871" category="Zomaar" datapart="0" dataparts="33" totalsize="794973" data=""
    //   controlcode="" server="infw2368A4D0" ack="true"/>
    if( wDataReq.isack(node) ) {
      if( StrOp.equals(m_AddedUID, wDataReq.getid(node) ) ) {
        iONode cmd = NodeOp.inst( wDataReq.name(), NULL, ELEMENT_NODE );
        wDataReq.setcmd( cmd, wDataReq.abox_filedata );
        wDataReq.setid( cmd, wDataReq.getid(node) );
        wDataReq.setcategory(cmd, wDataReq.getcategory(node));
        wDataReq.setfilename(cmd, wDataReq.getfilename(node));
        wDataReq.setdatapart(cmd, wDataReq.getdatapart(node)+1);

        m_labUploadState->SetLabel(wxString::Format(wxT("%d"), wDataReq.getdatapart(cmd)));

        if( readDataBlock(m_AddedFilename, cmd, wDataReq.getdatapart(cmd)) ) {
          m_AddedFilename[0] = '\0';
          m_AddedUID[0] = '\0';
          m_labUploadState->SetLabel(wxT(""));
          EnableDlg(true);
        }
        wxGetApp().sendToRocrail( cmd );
        cmd->base.del(cmd);
      }
    }

  }

  else if( wDataReq.getcmd(node) == wDataReq.abox_getcategories ) {
    m_ReadOnly = wDataReq.isreadonly(node)?true:false;
    if( m_Enable )
      m_Add->Enable(!m_ReadOnly);
    m_Category->Clear();
    wxString findtext = m_FindText->GetValue();
    m_FindText->Clear();
    m_FindText->SetValue(findtext);
    iOStrTok tok = StrTokOp.inst( wDataReq.getcategory( node ), ',' );
    while( StrTokOp.hasMoreTokens(tok) ) {
      const char* category = StrTokOp.nextToken( tok );
      m_Category->Append( wxString(category,wxConvUTF8) );
      m_FindText->Append( wxString(category,wxConvUTF8) );
    }
  }

  else if( wDataReq.getcmd(node) == wDataReq.abox_find ) {
    m_SelectedStub = wxNOT_FOUND;
    m_Open->Enable(false);
    m_SelectApp->Enable(false);
    m_Modify->Enable(false);
    m_Delete->Enable(false);
    m_Stubs->DeleteAllItems();
    clearStubList();

    char* s = NodeOp.base.toString(node);
    TraceOp.trc( "aboxdlg", TRCLEVEL_INFO, __LINE__, 9999, "found [%s]", s );
    StrOp.free(s);

    iONode stub = NodeOp.findNode( node, "stub");
    while( stub != NULL ) {
      iONode clone = (iONode)NodeOp.base.clone(stub);
      ListOp.add(m_StubList, (obj)clone);
      stub = NodeOp.findNextNode( node, stub);
    }
    initResult();
    if(wDataReq.istoomanyhits(node)) {
      // Show warning.
      int action = wxMessageDialog( this, wxGetApp().getMsg("toomanyhits"), _T("Rocrail"), wxOK | wxICON_EXCLAMATION ).ShowModal();
    }
  }

}

void ABoxDlg::onHelp( wxCommandEvent& event ) {
  wxGetApp().openLink( "abox:archivebox" );
}

void ABoxDlg::onClose( wxCloseEvent& event ) {
  wxCommandEvent cmdEvent;
  onOK(cmdEvent);
}

void ABoxDlg::onOK( wxCommandEvent& event ) {
  if( StrOp.len(m_AddedFilename) > 0 ) {
    char* tip = StrOp.fmt( wxGetApp().getCMsg("uploadingfile"), m_AddedFilename );
    int action = wxMessageDialog( this, wxString(tip,wxConvUTF8), _T("Rocrail"), wxOK | wxCANCEL | wxICON_EXCLAMATION ).ShowModal();
    StrOp.free(tip);
    if( action == wxID_OK )
      return;
  }
  if( StrOp.len(m_DownloadFilename) > 0 ) {
    char* tip = StrOp.fmt( wxGetApp().getCMsg("downloadingfile"), m_DownloadFilename );
    int action = wxMessageDialog( this, wxString(tip,wxConvUTF8), _T("Rocrail"), wxOK | wxCANCEL | wxICON_EXCLAMATION ).ShowModal();
    StrOp.free(tip);
    if( action == wxID_OK )
      return;
  }
  EndModal( wxID_OK );
}

void ABoxDlg::onOpen( wxCommandEvent& event ) {
  if( m_SelectedStub != wxNOT_FOUND ) {
    openStub();
  }
}

void ABoxDlg::onOpenPreview( wxMouseEvent& event ) {
  if( m_SelectedStub != wxNOT_FOUND ) {
    openStub();
  }
}

void ABoxDlg::onDelete( wxCommandEvent& event ) {
  if( m_SelectedStub != wxNOT_FOUND ) {
    int action = wxMessageDialog( this, wxGetApp().getMsg("removewarning"), _T("Rocrail"), wxYES_NO | wxICON_EXCLAMATION ).ShowModal();
    if( action == wxID_NO )
      return;
    iONode stub = (iONode)m_Stubs->GetItemData(m_SelectedStub);
    iONode cmd = NodeOp.inst( wDataReq.name(), NULL, ELEMENT_NODE );
    wDataReq.setcmd( cmd, wDataReq.abox_deletelink );
    NodeOp.addChild(cmd, (iONode)NodeOp.base.clone(stub));
    wxGetApp().sendToRocrail( cmd );
    cmd->base.del(cmd);

    onFind(event);
  }
}

void ABoxDlg::onStubCol( wxListEvent& event ) {
  if(m_SortCol == event.GetColumn())
    ms_Sort = !ms_Sort;
  else
    ms_Sort = true;

  m_SortCol = event.GetColumn();
  initResult();
}


void ABoxDlg::onModify( wxCommandEvent& event ) {
  if( m_SelectedStub != wxNOT_FOUND ) {
    iONode stub = (iONode)m_Stubs->GetItemData(m_SelectedStub);
    iONode cmd = NodeOp.inst( wDataReq.name(), NULL, ELEMENT_NODE );
    wDataReq.setcmd( cmd, wDataReq.abox_modifylink );
    iONode clone = (iONode)NodeOp.base.clone(stub);
    NodeOp.setStr(clone, "text", m_ResultText->GetValue().mb_str(wxConvUTF8) );
    NodeOp.setStr(clone, "note", m_ResultNote->GetValue().mb_str(wxConvUTF8) );
    NodeOp.addChild(cmd, clone);
    wxGetApp().sendToRocrail( cmd );
    cmd->base.del(cmd);

    onFind(event);
  }
}

void ABoxDlg::onShowPath( wxCommandEvent& event ) {
  wABox.setshowpath(m_Ini, m_ShowPath->IsChecked()?True:False);
  initResult();
}


void ABoxDlg::onFromDate( wxDateEvent& event ) {
  wxDateTime date = m_FromDate->GetValue();
  TraceOp.trc( "aboxdlg", TRCLEVEL_INFO, __LINE__, 9999, "from date: %d%02d%02d", date.GetYear(), date.GetMonth()+1, date.GetDay() );
}

void ABoxDlg::onToDate( wxDateEvent& event ) {
  wxDateTime date = m_ToDate->GetValue();
  TraceOp.trc( "aboxdlg", TRCLEVEL_INFO, __LINE__, 9999, "to date: %d%02d%02d", date.GetYear(), date.GetMonth()+1, date.GetDay() );
}

void ABoxDlg::onBmpFind( wxMouseEvent& event ) {
  wxCommandEvent cmdEvent;
  onFind(cmdEvent);
}

void ABoxDlg::onBmpAdd( wxMouseEvent& event ) {
  wxCommandEvent cmdEvent;
  onAdd(cmdEvent);
}

void ABoxDlg::onBmpOpen( wxMouseEvent& event ) {
  wxCommandEvent cmdEvent;
  onOpen(cmdEvent);
}

void ABoxDlg::onSelectApp( wxCommandEvent& event ) {
  if( m_SelectedStub == wxNOT_FOUND )
    return;

  iONode stub = (iONode)m_Stubs->GetItemData(m_SelectedStub);
  const char* ext = StrOp.getExtension(NodeOp.getStr(stub, "path", "-"));

  wxFileDialog* fdlg = new wxFileDialog(this);
  if( fdlg->ShowModal() == wxID_OK ) {
    iONode theAboxApp = NULL;
    iONode aboxapp = wABox.getaboxapp(m_Ini);
    while(aboxapp != NULL) {
      if( StrOp.equalsi(wABoxApp.getext(aboxapp), ext ) ) {
        theAboxApp = aboxapp;
        break;
      }
      aboxapp = wABox.nextaboxapp(m_Ini, aboxapp);
    }
    if( theAboxApp == NULL ) {
      theAboxApp = NodeOp.inst(wABoxApp.name(), m_Ini, ELEMENT_NODE);
      wABoxApp.setext(theAboxApp, ext);
      NodeOp.addChild( m_Ini, theAboxApp);
    }
    wABoxApp.setapp(theAboxApp, fdlg->GetPath().mb_str(wxConvUTF8) );

  }
  fdlg->Destroy();
  Raise();


}


