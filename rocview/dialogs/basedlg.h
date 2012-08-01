/*
 Copyright (C) 2002-2012 Rob Versluis, Rocrail.net

 Without an official permission commercial use is not permitted.
 Forking this project is not permitted.
 */
#ifndef BASEDLG_CPP_
#define BASEDLG_CPP_

#include <wx/listctrl.h>

#include "rocs/public/node.h"


class BaseDialog
{   
public:
  void doDoc( wxCommandEvent& event, const char* xslName );
  bool existID( wxWindow* dlg, iONode list, iONode props, wxString id );
  void initList(wxListCtrl* list, wxWindow* parent, bool showPos=true, bool showAddr=true);
  void fillIndex( iONode Items);
  void setIDSelection( const char* ID );
  iONode setSelection( int index );
  iONode getSelection(int index=-1);
  iONode selectNext();
  iONode selectPrev();
  int findID( const char* ID );
  void appendItem( iONode Item);
  void sortOnColumn( int col );

  wxWindow* m_Parent;
  wxListCtrl* m_ItemList;
  iONode m_Items;
  int m_SortCol;
  bool m_ShowPos;
  bool m_ShowAddr;
  const char* m_SelectedID;
  int m_colID;
  int m_colIID;
  int m_colAddr;
  int m_colDesc;
  int m_colShow;
  int m_colPos;
  int m_colOri;
};


#endif /*BASEDLG_CPP_*/
