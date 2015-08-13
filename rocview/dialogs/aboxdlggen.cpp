///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Sep  8 2010)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "aboxdlggen.h"

///////////////////////////////////////////////////////////////////////////

AboxDlgGen::AboxDlgGen( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxVERTICAL );
	
	wxFlexGridSizer* fgSizer1;
	fgSizer1 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer1->AddGrowableCol( 1 );
	fgSizer1->SetFlexibleDirection( wxBOTH );
	fgSizer1->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_Find = new wxButton( this, wxID_ANY, wxT("Find"), wxDefaultPosition, wxDefaultSize, 0 );
	m_Find->SetDefault(); 
	fgSizer1->Add( m_Find, 0, wxALL, 5 );
	
	m_FindText = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_FindText->SetMinSize( wxSize( 200,-1 ) );
	
	fgSizer1->Add( m_FindText, 0, wxALL|wxEXPAND, 5 );
	
	bSizer3->Add( fgSizer1, 0, wxEXPAND, 5 );
	
	m_staticline1 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer3->Add( m_staticline1, 0, wxEXPAND | wxALL, 5 );
	
	wxFlexGridSizer* fgSizer3;
	fgSizer3 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer3->AddGrowableCol( 1 );
	fgSizer3->SetFlexibleDirection( wxBOTH );
	fgSizer3->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_SelectFile = new wxButton( this, wxID_ANY, wxT("File..."), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer3->Add( m_SelectFile, 0, wxALL, 5 );
	
	m_Filename = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer3->Add( m_Filename, 0, wxALL|wxEXPAND, 5 );
	
	bSizer3->Add( fgSizer3, 0, wxEXPAND, 5 );
	
	wxFlexGridSizer* fgSizer2;
	fgSizer2 = new wxFlexGridSizer( 0, 3, 0, 0 );
	fgSizer2->AddGrowableCol( 1 );
	fgSizer2->AddGrowableCol( 2 );
	fgSizer2->SetFlexibleDirection( wxBOTH );
	fgSizer2->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText1 = new wxStaticText( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText1->Wrap( -1 );
	fgSizer2->Add( m_staticText1, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxTOP|wxRIGHT|wxLEFT, 5 );
	
	m_labCategory = new wxStaticText( this, wxID_ANY, wxT("Category"), wxDefaultPosition, wxDefaultSize, 0 );
	m_labCategory->Wrap( -1 );
	fgSizer2->Add( m_labCategory, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxTOP|wxRIGHT|wxLEFT, 5 );
	
	m_labText = new wxStaticText( this, wxID_ANY, wxT("Text"), wxDefaultPosition, wxDefaultSize, 0 );
	m_labText->Wrap( -1 );
	fgSizer2->Add( m_labText, 0, wxTOP|wxRIGHT|wxLEFT|wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_Add = new wxButton( this, wxID_ANY, wxT("Add"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer2->Add( m_Add, 0, wxALL, 5 );
	
	m_Category = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer2->Add( m_Category, 0, wxALL|wxEXPAND, 5 );
	
	m_Text = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer2->Add( m_Text, 0, wxALL|wxEXPAND, 5 );
	
	bSizer3->Add( fgSizer2, 0, wxEXPAND, 5 );
	
	m_Stubs = new wxListCtrl( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_HRULES|wxLC_REPORT|wxLC_SINGLE_SEL|wxSUNKEN_BORDER );
	m_Stubs->SetMinSize( wxSize( 600,300 ) );
	
	bSizer3->Add( m_Stubs, 1, wxALL|wxEXPAND, 5 );
	
	m_StdButtons = new wxStdDialogButtonSizer();
	m_StdButtonsOK = new wxButton( this, wxID_OK );
	m_StdButtons->AddButton( m_StdButtonsOK );
	m_StdButtons->Realize();
	bSizer3->Add( m_StdButtons, 0, wxEXPAND|wxALL|wxALIGN_RIGHT, 5 );
	
	this->SetSizer( bSizer3 );
	this->Layout();
	bSizer3->Fit( this );
	
	this->Centre( wxBOTH );
	
	// Connect Events
	m_Find->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( AboxDlgGen::onFind ), NULL, this );
	m_SelectFile->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( AboxDlgGen::onSelectFile ), NULL, this );
	m_Add->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( AboxDlgGen::onAdd ), NULL, this );
	m_Stubs->Connect( wxEVT_COMMAND_LIST_ITEM_ACTIVATED, wxListEventHandler( AboxDlgGen::onStubActivated ), NULL, this );
	m_Stubs->Connect( wxEVT_COMMAND_LIST_ITEM_SELECTED, wxListEventHandler( AboxDlgGen::onStubSelected ), NULL, this );
}

AboxDlgGen::~AboxDlgGen()
{
	// Disconnect Events
	m_Find->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( AboxDlgGen::onFind ), NULL, this );
	m_SelectFile->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( AboxDlgGen::onSelectFile ), NULL, this );
	m_Add->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( AboxDlgGen::onAdd ), NULL, this );
	m_Stubs->Disconnect( wxEVT_COMMAND_LIST_ITEM_ACTIVATED, wxListEventHandler( AboxDlgGen::onStubActivated ), NULL, this );
	m_Stubs->Disconnect( wxEVT_COMMAND_LIST_ITEM_SELECTED, wxListEventHandler( AboxDlgGen::onStubSelected ), NULL, this );
	
}
