///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Sep  8 2010)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __aboxdlggen__
#define __aboxdlggen__

#include <wx/string.h>
#include <wx/button.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/checkbox.h>
#include <wx/sizer.h>
#include <wx/combobox.h>
#include <wx/stattext.h>
#include <wx/datectrl.h>
#include <wx/dateevt.h>
#include <wx/statbox.h>
#include <wx/textctrl.h>
#include <wx/listctrl.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/statbmp.h>
#include <wx/dialog.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class AboxDlgGen
///////////////////////////////////////////////////////////////////////////////
class AboxDlgGen : public wxDialog 
{
	private:
	
	protected:
		wxStaticBoxSizer* m_FindBox;
		wxButton* m_Find;
		wxCheckBox* m_FindInText;
		wxCheckBox* m_FindInCategory;
		wxCheckBox* m_FindInFilename;
		wxCheckBox* m_FindInDate;
		wxComboBox* m_FindText;
		wxStaticText* m_labFromDate;
		wxDatePickerCtrl* m_FromDate;
		wxStaticText* m_labToDate;
		wxDatePickerCtrl* m_ToDate;
		wxStaticBoxSizer* m_UploadBox;
		wxStaticText* m_labCategory;
		wxComboBox* m_Category;
		wxStaticText* m_labText;
		wxTextCtrl* m_Text;
		wxStaticText* m_labFile;
		wxTextCtrl* m_Filename;
		wxButton* m_SelectFile;
		wxCheckBox* m_Link;
		wxButton* m_Add;
		wxStaticBoxSizer* m_ResultBox;
		wxListCtrl* m_Stubs;
		wxCheckBox* m_ShowPath;
		wxBoxSizer* m_PreviewSizer;
		wxStaticText* m_labResultText;
		wxTextCtrl* m_ResultText;
		wxStaticText* m_labResultNote;
		wxTextCtrl* m_ResultNote;
		wxStaticBitmap* m_Preview;
		wxButton* m_Open;
		wxButton* m_Modify;
		wxButton* m_Delete;
		wxStdDialogButtonSizer* m_StdButtons;
		wxButton* m_StdButtonsOK;
		wxButton* m_StdButtonsHelp;
		
		// Virtual event handlers, overide them in your derived class
		virtual void onFind( wxCommandEvent& event ) { event.Skip(); }
		virtual void onFindTextEnter( wxCommandEvent& event ) { event.Skip(); }
		virtual void onFromDate( wxDateEvent& event ) { event.Skip(); }
		virtual void onToDate( wxDateEvent& event ) { event.Skip(); }
		virtual void onSelectFile( wxCommandEvent& event ) { event.Skip(); }
		virtual void onAdd( wxCommandEvent& event ) { event.Skip(); }
		virtual void onStubCol( wxListEvent& event ) { event.Skip(); }
		virtual void onStubActivated( wxListEvent& event ) { event.Skip(); }
		virtual void onStubSelected( wxListEvent& event ) { event.Skip(); }
		virtual void onShowPath( wxCommandEvent& event ) { event.Skip(); }
		virtual void onOpenPreview( wxMouseEvent& event ) { event.Skip(); }
		virtual void onOpen( wxCommandEvent& event ) { event.Skip(); }
		virtual void onModify( wxCommandEvent& event ) { event.Skip(); }
		virtual void onDelete( wxCommandEvent& event ) { event.Skip(); }
		virtual void onHelp( wxCommandEvent& event ) { event.Skip(); }
		virtual void onOK( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		AboxDlgGen( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("ArchiveBox"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER );
		~AboxDlgGen();
	
};

#endif //__aboxdlggen__