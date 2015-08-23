/*
 Rocrail - Model Railroad Software

Copyright (c) 2002-2015 Robert Jan Versluis, Rocrail.net

 


 All rights reserved.
*/
#ifndef _LOCSELDLG_H_
#define _LOCSELDLG_H_

#if defined(__GNUG__) && !defined(NO_GCC_PRAGMA)
#pragma interface "locseldlg.h"
#endif

/*!
 * Includes
 */
#include "rocs/public/node.h"

////@begin includes
////@end includes

/*!
 * Forward declarations
 */

////@begin forward declarations
////@end forward declarations

/*!
 * Control identifiers
 */

////@begin control identifiers
#define ID_MYDIALOG 10186
#define ID_BITMAPBUTTON_SEL_LOC 10001
#define ID_LISTBOX_SEL_LOC 10000
#define SYMBOL_LOCSELDLG_STYLE wxCAPTION|wxRESIZE_BORDER|wxSYSTEM_MENU|wxCLOSE_BOX
#define SYMBOL_LOCSELDLG_TITLE _("Select Loc")
#define SYMBOL_LOCSELDLG_IDNAME ID_MYDIALOG
#define SYMBOL_LOCSELDLG_SIZE wxDefaultSize
#define SYMBOL_LOCSELDLG_POSITION wxDefaultPosition
////@end control identifiers

/*!
 * Compatibility
 */

#ifndef wxCLOSE_BOX
#define wxCLOSE_BOX 0x1000
#endif

/*!
 * LocSelDlg class declaration
 */

class LocSelDlg: public wxDialog
{    
    DECLARE_DYNAMIC_CLASS( LocSelDlg )
    DECLARE_EVENT_TABLE()

  void InitIndex();
  void InitValues();
  iONode m_Props;
  iONode m_MICini;
  bool m_MICmode;
  const char* m_LocID;
  bool m_AddCars;
  bool m_AddAll;  // including cars without an interface address

public:
    /// Constructors
    LocSelDlg( );
    LocSelDlg( wxWindow* parent, iONode locprops=NULL, bool mic=false, const char* locid=NULL, bool cars=false, bool all=false );

    iONode getProperties(){ return m_Props;}
    void SelectNext();
    void SelectPrev();
    void OnStop(wxMouseEvent& event);
    void OnEscape(wxMouseEvent& event);
    void OnSpeed(wxMouseEvent& event);

    /// Creation
    bool Create( wxWindow* parent, wxWindowID id = SYMBOL_LOCSELDLG_IDNAME, const wxString& caption = SYMBOL_LOCSELDLG_TITLE, const wxPoint& pos = SYMBOL_LOCSELDLG_POSITION, const wxSize& size = SYMBOL_LOCSELDLG_SIZE, long style = SYMBOL_LOCSELDLG_STYLE );

    /// Creates the controls and sizers
    void CreateControls();

////@begin LocSelDlg event handler declarations

    /// wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BITMAPBUTTON_SEL_LOC
    void OnBitmapbuttonSelLocClick( wxCommandEvent& event );

    /// wxEVT_COMMAND_LISTBOX_SELECTED event handler for ID_LISTBOX_SEL_LOC
    void OnListboxSelLocSelected( wxCommandEvent& event );

    /// wxEVT_COMMAND_LISTBOX_DOUBLECLICKED event handler for ID_LISTBOX_SEL_LOC
    void OnListboxSelLocDoubleClicked( wxCommandEvent& event );

////@end LocSelDlg event handler declarations

////@begin LocSelDlg member function declarations

    /// Retrieves bitmap resources
    wxBitmap GetBitmapResource( const wxString& name );

    /// Retrieves icon resources
    wxIcon GetIconResource( const wxString& name );
////@end LocSelDlg member function declarations

    /// Should we show tooltips?
    static bool ShowToolTips();

////@begin LocSelDlg member variables
    wxBitmapButton* m_LocImageIndex;
    wxListBox* m_List;
////@end LocSelDlg member variables
};

#endif
    // _LOCSELDLG_H_
