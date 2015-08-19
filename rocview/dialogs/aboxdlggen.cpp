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
	
	m_FindBox = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Find") ), wxHORIZONTAL );
	
	m_Find = new wxButton( this, wxID_ANY, wxT("Find"), wxDefaultPosition, wxDefaultSize, 0 );
	m_FindBox->Add( m_Find, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxBoxSizer* bSizer31;
	bSizer31 = new wxBoxSizer( wxVERTICAL );
	
	m_FindInText = new wxCheckBox( this, wxID_ANY, wxT("Text"), wxDefaultPosition, wxDefaultSize, 0 );
	m_FindInText->SetValue(true); 
	bSizer31->Add( m_FindInText, 0, wxBOTTOM|wxRIGHT|wxLEFT, 5 );
	
	m_FindInCategory = new wxCheckBox( this, wxID_ANY, wxT("Category"), wxDefaultPosition, wxDefaultSize, 0 );
	m_FindInCategory->SetValue(true); 
	bSizer31->Add( m_FindInCategory, 0, wxBOTTOM|wxRIGHT|wxLEFT, 5 );
	
	m_FindInFilename = new wxCheckBox( this, wxID_ANY, wxT("Filename"), wxDefaultPosition, wxDefaultSize, 0 );
	m_FindInFilename->SetValue(true); 
	bSizer31->Add( m_FindInFilename, 0, wxBOTTOM|wxRIGHT|wxLEFT, 5 );
	
	m_FindInDate = new wxCheckBox( this, wxID_ANY, wxT("Date"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer31->Add( m_FindInDate, 0, wxRIGHT|wxLEFT, 5 );
	
	m_FindBox->Add( bSizer31, 0, wxEXPAND|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxVERTICAL );
	
	m_FindText = new wxComboBox( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, NULL, wxTE_PROCESS_ENTER ); 
	bSizer4->Add( m_FindText, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxEXPAND, 5 );
	
	wxFlexGridSizer* fgSizer41;
	fgSizer41 = new wxFlexGridSizer( 0, 4, 0, 0 );
	fgSizer41->AddGrowableCol( 1 );
	fgSizer41->AddGrowableCol( 3 );
	fgSizer41->SetFlexibleDirection( wxBOTH );
	fgSizer41->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_labFromDate = new wxStaticText( this, wxID_ANY, wxT("From"), wxDefaultPosition, wxDefaultSize, 0 );
	m_labFromDate->Wrap( -1 );
	fgSizer41->Add( m_labFromDate, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_FromDate = new wxDatePickerCtrl( this, wxID_ANY, wxDefaultDateTime, wxDefaultPosition, wxDefaultSize, wxDP_DEFAULT|wxDP_SHOWCENTURY );
	fgSizer41->Add( m_FromDate, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxEXPAND, 5 );
	
	m_labToDate = new wxStaticText( this, wxID_ANY, wxT("To"), wxDefaultPosition, wxDefaultSize, 0 );
	m_labToDate->Wrap( -1 );
	fgSizer41->Add( m_labToDate, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_ToDate = new wxDatePickerCtrl( this, wxID_ANY, wxDefaultDateTime, wxDefaultPosition, wxDefaultSize, wxDP_DEFAULT|wxDP_SHOWCENTURY );
	fgSizer41->Add( m_ToDate, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxEXPAND, 5 );
	
	bSizer4->Add( fgSizer41, 0, wxEXPAND, 5 );
	
	m_FindBox->Add( bSizer4, 1, wxALIGN_CENTER_VERTICAL, 5 );
	
	bSizer3->Add( m_FindBox, 0, wxEXPAND|wxALL, 5 );
	
	m_UploadBox = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Upload") ), wxVERTICAL );
	
	wxFlexGridSizer* fgSizer2;
	fgSizer2 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer2->AddGrowableCol( 1 );
	fgSizer2->SetFlexibleDirection( wxBOTH );
	fgSizer2->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_labCategory = new wxStaticText( this, wxID_ANY, wxT("Category"), wxDefaultPosition, wxDefaultSize, 0 );
	m_labCategory->Wrap( -1 );
	fgSizer2->Add( m_labCategory, 0, wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT|wxALL, 5 );
	
	m_Category = new wxComboBox( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, NULL, 0 ); 
	fgSizer2->Add( m_Category, 0, wxEXPAND|wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_labText = new wxStaticText( this, wxID_ANY, wxT("Text"), wxDefaultPosition, wxDefaultSize, 0 );
	m_labText->Wrap( -1 );
	fgSizer2->Add( m_labText, 0, wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT|wxBOTTOM|wxRIGHT|wxLEFT, 5 );
	
	m_Text = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer2->Add( m_Text, 0, wxEXPAND|wxALIGN_CENTER_VERTICAL|wxBOTTOM|wxRIGHT|wxLEFT, 5 );
	
	m_labFile = new wxStaticText( this, wxID_ANY, wxT("File"), wxDefaultPosition, wxDefaultSize, 0 );
	m_labFile->Wrap( -1 );
	fgSizer2->Add( m_labFile, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxBOTTOM|wxRIGHT|wxLEFT, 5 );
	
	wxFlexGridSizer* fgSizer3;
	fgSizer3 = new wxFlexGridSizer( 0, 3, 0, 0 );
	fgSizer3->AddGrowableCol( 0 );
	fgSizer3->SetFlexibleDirection( wxBOTH );
	fgSizer3->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_Filename = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer3->Add( m_Filename, 0, wxEXPAND|wxALIGN_CENTER_VERTICAL|wxBOTTOM|wxRIGHT|wxLEFT, 5 );
	
	m_SelectFile = new wxButton( this, wxID_ANY, wxT("..."), wxDefaultPosition, wxSize( 50,-1 ), 0 );
	fgSizer3->Add( m_SelectFile, 0, wxALIGN_CENTER_VERTICAL|wxBOTTOM|wxRIGHT|wxLEFT, 5 );
	
	m_Link = new wxCheckBox( this, wxID_ANY, wxT("Link"), wxDefaultPosition, wxDefaultSize, 0 );
	m_Link->SetValue(true); 
	fgSizer3->Add( m_Link, 0, wxALIGN_CENTER_VERTICAL|wxBOTTOM|wxRIGHT|wxLEFT, 5 );
	
	fgSizer2->Add( fgSizer3, 0, wxEXPAND, 5 );
	
	m_UploadBox->Add( fgSizer2, 0, wxEXPAND, 5 );
	
	m_Add = new wxButton( this, wxID_ANY, wxT("Add"), wxDefaultPosition, wxDefaultSize, 0 );
	m_UploadBox->Add( m_Add, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	bSizer3->Add( m_UploadBox, 0, wxEXPAND|wxALL, 5 );
	
	m_ResultBox = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Result") ), wxVERTICAL );
	
	m_Stubs = new wxListCtrl( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_HRULES|wxLC_REPORT|wxLC_SINGLE_SEL );
	m_Stubs->SetMinSize( wxSize( 600,200 ) );
	
	m_ResultBox->Add( m_Stubs, 1, wxEXPAND, 5 );
	
	m_ShowPath = new wxCheckBox( this, wxID_ANY, wxT("Show path"), wxDefaultPosition, wxDefaultSize, 0 );
	m_ResultBox->Add( m_ShowPath, 0, wxBOTTOM|wxRIGHT|wxLEFT, 5 );
	
	m_PreviewSizer = new wxBoxSizer( wxHORIZONTAL );
	
	wxFlexGridSizer* fgSizer4;
	fgSizer4 = new wxFlexGridSizer( 2, 2, 0, 0 );
	fgSizer4->AddGrowableCol( 1 );
	fgSizer4->AddGrowableRow( 1 );
	fgSizer4->SetFlexibleDirection( wxBOTH );
	fgSizer4->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_labResultText = new wxStaticText( this, wxID_ANY, wxT("Text"), wxDefaultPosition, wxDefaultSize, 0 );
	m_labResultText->Wrap( -1 );
	fgSizer4->Add( m_labResultText, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT, 5 );
	
	m_ResultText = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer4->Add( m_ResultText, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxEXPAND, 5 );
	
	m_labResultNote = new wxStaticText( this, wxID_ANY, wxT("Note"), wxDefaultPosition, wxDefaultSize, 0 );
	m_labResultNote->Wrap( -1 );
	fgSizer4->Add( m_labResultNote, 0, wxBOTTOM|wxRIGHT|wxLEFT|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT, 5 );
	
	m_ResultNote = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE );
	m_ResultNote->SetMinSize( wxSize( -1,50 ) );
	
	fgSizer4->Add( m_ResultNote, 1, wxBOTTOM|wxRIGHT|wxLEFT|wxEXPAND|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_PreviewSizer->Add( fgSizer4, 1, wxEXPAND, 5 );
	
	m_Preview = new wxStaticBitmap( this, wxID_ANY, wxNullBitmap, wxDefaultPosition, wxSize( -1,-1 ), 0 );
	m_PreviewSizer->Add( m_Preview, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_ResultBox->Add( m_PreviewSizer, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxHORIZONTAL );
	
	m_Open = new wxButton( this, wxID_ANY, wxT("Open"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer2->Add( m_Open, 0, wxALL, 5 );
	
	m_Modify = new wxButton( this, wxID_ANY, wxT("Modify"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer2->Add( m_Modify, 0, wxALL, 5 );
	
	m_Delete = new wxButton( this, wxID_ANY, wxT("Delete"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer2->Add( m_Delete, 0, wxALL, 5 );
	
	m_ResultBox->Add( bSizer2, 0, wxEXPAND, 5 );
	
	bSizer3->Add( m_ResultBox, 1, wxEXPAND|wxALL, 5 );
	
	m_StdButtons = new wxStdDialogButtonSizer();
	m_StdButtonsOK = new wxButton( this, wxID_OK );
	m_StdButtons->AddButton( m_StdButtonsOK );
	m_StdButtonsHelp = new wxButton( this, wxID_HELP );
	m_StdButtons->AddButton( m_StdButtonsHelp );
	m_StdButtons->Realize();
	bSizer3->Add( m_StdButtons, 0, wxEXPAND|wxALL|wxALIGN_RIGHT, 5 );
	
	this->SetSizer( bSizer3 );
	this->Layout();
	bSizer3->Fit( this );
	
	this->Centre( wxBOTH );
	
	// Connect Events
	m_Find->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( AboxDlgGen::onFind ), NULL, this );
	m_FindText->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( AboxDlgGen::onFindTextEnter ), NULL, this );
	m_FromDate->Connect( wxEVT_DATE_CHANGED, wxDateEventHandler( AboxDlgGen::onFromDate ), NULL, this );
	m_ToDate->Connect( wxEVT_DATE_CHANGED, wxDateEventHandler( AboxDlgGen::onToDate ), NULL, this );
	m_SelectFile->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( AboxDlgGen::onSelectFile ), NULL, this );
	m_Add->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( AboxDlgGen::onAdd ), NULL, this );
	m_Stubs->Connect( wxEVT_COMMAND_LIST_COL_CLICK, wxListEventHandler( AboxDlgGen::onStubCol ), NULL, this );
	m_Stubs->Connect( wxEVT_COMMAND_LIST_ITEM_ACTIVATED, wxListEventHandler( AboxDlgGen::onStubActivated ), NULL, this );
	m_Stubs->Connect( wxEVT_COMMAND_LIST_ITEM_SELECTED, wxListEventHandler( AboxDlgGen::onStubSelected ), NULL, this );
	m_ShowPath->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( AboxDlgGen::onShowPath ), NULL, this );
	m_Preview->Connect( wxEVT_LEFT_UP, wxMouseEventHandler( AboxDlgGen::onOpenPreview ), NULL, this );
	m_Open->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( AboxDlgGen::onOpen ), NULL, this );
	m_Modify->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( AboxDlgGen::onModify ), NULL, this );
	m_Delete->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( AboxDlgGen::onDelete ), NULL, this );
	m_StdButtonsHelp->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( AboxDlgGen::onHelp ), NULL, this );
	m_StdButtonsOK->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( AboxDlgGen::onOK ), NULL, this );
}

AboxDlgGen::~AboxDlgGen()
{
	// Disconnect Events
	m_Find->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( AboxDlgGen::onFind ), NULL, this );
	m_FindText->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( AboxDlgGen::onFindTextEnter ), NULL, this );
	m_FromDate->Disconnect( wxEVT_DATE_CHANGED, wxDateEventHandler( AboxDlgGen::onFromDate ), NULL, this );
	m_ToDate->Disconnect( wxEVT_DATE_CHANGED, wxDateEventHandler( AboxDlgGen::onToDate ), NULL, this );
	m_SelectFile->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( AboxDlgGen::onSelectFile ), NULL, this );
	m_Add->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( AboxDlgGen::onAdd ), NULL, this );
	m_Stubs->Disconnect( wxEVT_COMMAND_LIST_COL_CLICK, wxListEventHandler( AboxDlgGen::onStubCol ), NULL, this );
	m_Stubs->Disconnect( wxEVT_COMMAND_LIST_ITEM_ACTIVATED, wxListEventHandler( AboxDlgGen::onStubActivated ), NULL, this );
	m_Stubs->Disconnect( wxEVT_COMMAND_LIST_ITEM_SELECTED, wxListEventHandler( AboxDlgGen::onStubSelected ), NULL, this );
	m_ShowPath->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( AboxDlgGen::onShowPath ), NULL, this );
	m_Preview->Disconnect( wxEVT_LEFT_UP, wxMouseEventHandler( AboxDlgGen::onOpenPreview ), NULL, this );
	m_Open->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( AboxDlgGen::onOpen ), NULL, this );
	m_Modify->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( AboxDlgGen::onModify ), NULL, this );
	m_Delete->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( AboxDlgGen::onDelete ), NULL, this );
	m_StdButtonsHelp->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( AboxDlgGen::onHelp ), NULL, this );
	m_StdButtonsOK->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( AboxDlgGen::onOK ), NULL, this );
	
}