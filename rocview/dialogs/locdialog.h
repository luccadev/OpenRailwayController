/*
 Rocrail - Model Railroad Software

Copyright (c) 2002-2015 Robert Jan Versluis, Rocrail.net

 


 All rights reserved.
*/
#ifndef _LOCDIALOG_H_
#define _LOCDIALOG_H_

#if defined(__GNUG__) && !defined(__APPLE__)
#pragma interface "locdialog.cpp"
#endif

/*!
 * Includes
 */
#include "rocs/public/node.h"
#include "rocs/public/list.h"

////@begin includes
#include "wx/notebook.h"
#include "wx/listctrl.h"
#include "wx/statline.h"
#include "wx/spinctrl.h"
#include "wx/grid.h"
////@end includes

#include "basedlg.h"


/*!
 * Forward declarations
 */

////@begin forward declarations
class wxNotebook;
class wxListCtrl;
class wxBoxSizer;
class wxSpinCtrl;
class wxGrid;
////@end forward declarations

/*!
 * Control identifiers
 */

////@begin control identifiers
#define ID_DIALOG_LOC 10000
#define ID_BITMAPBUTTON 10123
#define ID_NOTEBOOK 10001
#define ID_PANEL_INDEX 10060
#define ID_LISTCTRLINDEX_LC 10062
#define ID_BUTTON_LOC_NEW 10121
#define ID_BUTTON_DELETE 10122
#define ID_BUTTON_LOCO_DOC 10353
#define ID_LOC_COPY 10280
#define ID_BUTTON_IMPORTLOCOS 10253
#define ID_LOC_ONRESTOREFX 10432
#define ID_LOC_RESTORESPEED 10434
#define ID_LOC_MANUALLY 10328
#define ID_LOC_SHOW 10433
#define ID_PANEL_GENERAL 10004
#define ID_ABOX_ID 10494
#define ID_TEXTCTRL_ID 10005
#define ID_ABOX_IDENT 10501
#define ID_ABOX_ROADNAME 10495
#define wxID_STATIC_DESCRIPTION 10018
#define ID_TEXTCTRL_DESCRIPTION 10006
#define ID_SELECT_LOCOIMAGE 10172
#define wxID_STATIC_LENGTH 10019
#define ID_ABOX_CATNR 10496
#define ID_TEXTCTRL_CATALOGNR 10008
#define ID_ABOX_DECODERTYPE 10497
#define ID_BUTTON_SHOWDOC 10391
#define wxID_STATIC_PURCHASED 10021
#define ID_TEXTCTRL_PURCHASED 10009
#define ID_STATICTEXT1 10064
#define ID_LC_SERVICED 10313
#define ID_LOC_ACTIONS 10380
#define ID_PANEL_INTERFACE 10010
#define wxID_STATIC_IID 10024
#define ID_TEXTCTRL_IID 10012
#define wxID_STATIC_LC_BUS 10250
#define ID_TEXTCTRL_LC_BUS 10249
#define wxID_STATIC_ADDRESS 10023
#define ID_TEXTCTRL_ADDRESS 10011
#define wxID_STATIC_PROTOCOL 10025
#define ID_CHOICE_PROTOCOL 10013
#define wxID_STATIC_PROT_VER 10176
#define ID_TEXTCTRL_PROTVER 10175
#define wxID_STATIC_SPEEDSTEPS 10177
#define ID_TEXTCTRL_SPEEDSTEPS 10178
#define wxID_STATIC_FUNCNT 10179
#define ID_TEXTCTRL_FUNCNT 10180
#define wxID_STATIC_V_MIN 10026
#define ID_TEXTCTRL_V_MIN 10014
#define wxID_STATIC_V_MAX 10027
#define ID_TEXTCTRL_V_MAX 10015
#define wxID_STATIC_MASS 10028
#define ID_TEXTCTRL_MASS 10029
#define wxID_STATIC_LOC_V_MODE 10116
#define ID_CHECKBOX_LOC_CONTROLLED 10117
#define wxID_STATIC_LOC_PLACING 10118
#define ID_CHECKBOX_LOC_PLACING 10119
#define ID_PANEL_DETAILS 10030
#define wxID_STATIC_BLOCKWAIT 10031
#define ID_TEXTCTRL_BLOCKWAIT 10032
#define ID_RADIOBOX_CARGO 10003
#define ID_CHECKBOX_COMMUTER 10114
#define ID_RADIOBOX_ENGINE 10002
#define ID_PANEL_FUNCTIONS 10035
#define ID_BUTTON_F0 10061
#define ID_LOC_ICONF0 10431
#define ID_LOC_FN_GROUP_PREV 10054
#define ID_LOC_FN_GROUP 10276
#define wxID_STATIC_F1 10044
#define ID_TEXTCTRL_F1 10036
#define ID_BUTTON_F1 10037
#define ID_LOC_SOUND1 10435
#define ID_LOC_ICONF1 10324
#define wxID_STATIC_F2 10045
#define ID_TEXTCTRL_F2 10038
#define ID_BUTTON_F2 10039
#define ID_LOC_SOUND2 10436
#define ID_LOC_ICONF2 10428
#define wxID_STATIC_F3 10046
#define ID_TEXTCTRL_F3 10040
#define ID_BUTTON_F3 10041
#define ID_LOC_SOUND3 10437
#define ID_LOC_ICONF3 10429
#define wxID_STATIC_F4 10047
#define ID_TEXTCTRL_F4 10042
#define ID_BUTTON_F4 10043
#define ID_LOC_SOUND4 10438
#define ID_LOC_ICONF4 10430
#define ID_PANEL_LOC_CONSIST 10200
#define ID_CONSTS_LIGHTSOFF 10349
#define ID_MU_SYNCLIGHTS 10338
#define ID_BUTTON_LOC_CONSIST_ADD 10201
#define ID_BUTTON_LOC_CONSIST_DELETE 10213
#define ID_PANEL_LOC_CV 10345
#define ID_GRID_LOC_CV 10346
#define ID_BUTTON_LC_CV_DESC 10347
#define ID_PANEL_LOC_BBT 10337
#define ID_LOC_BBTLIST2 10427
#define ID_BBT_ADD 10457
#define ID_BUTTON_BBT_DELETE 10424
#define ID_BBT_COPY 10455
#define ID_BUTTON_BBT_DELETEALL 10425
#define ID_BBT_MODIFY 10426
#define ID_BBT_EXPORT 10459
#define ID_BBT_IMPORT 10460
#define ID_BBT_FIXALL 10491
#define ID_BBT_GENATE_IN 10456
#define ID_PANEL_LOC_SBT 10470
#define wxID_STATIC_LOC_V_STEP 10033
#define ID_LOC_REGULATED 10375
#define ID_SBT_LIST 10471
#define ID_SBT_ADD 10472
#define ID_SBT_DELETE 10473
#define ID_SBT_MODIFY 10474
#define SYMBOL_LOCDIALOG_STYLE wxCAPTION|wxRESIZE_BORDER|wxSYSTEM_MENU|wxCLOSE_BOX
#define SYMBOL_LOCDIALOG_TITLE _("Dialog")
#define SYMBOL_LOCDIALOG_IDNAME ID_DIALOG_LOC
#define SYMBOL_LOCDIALOG_SIZE wxDefaultSize
#define SYMBOL_LOCDIALOG_POSITION wxDefaultPosition
////@end control identifiers

/*!
 * Compatibility
 */

#ifndef wxCLOSE_BOX
#define wxCLOSE_BOX 0x1000
#endif
#ifndef wxFIXED_MINSIZE
#define wxFIXED_MINSIZE 0
#endif

/*!
 * LocDialog class declaration
 */

class LocDialog: public wxDialog, public BaseDialog
{
    DECLARE_EVENT_TABLE()

  void initLabels();
  bool InitIndex();
  void InitValues();
  void initFunctions();
  bool Evaluate();
  bool evaluateFunctions();
  bool m_bSave;
  void EditFunction( int nr, wxString txt );
  int m_TabAlign;
  void initCVDesc();
  const char* m_CVDesc[256];
  int m_iSelectedCV;
  iONode m_CVNodes[1024];
  int m_iFunGroup;
  int m_BBTSortCol;
  iOList m_BBTList;
  iOList sortBBT();
  int m_SBTSortCol;
  iOList m_SBTList;
  iOList sortSBT();

public:
    /// Constructors
    LocDialog( wxWindow* parent, iONode p_Props, bool save=true);

    /// Creation
    bool Create( wxWindow* parent, wxWindowID id = SYMBOL_LOCDIALOG_IDNAME, const wxString& caption = SYMBOL_LOCDIALOG_TITLE, const wxPoint& pos = SYMBOL_LOCDIALOG_POSITION, const wxSize& size = SYMBOL_LOCDIALOG_SIZE, long style = SYMBOL_LOCDIALOG_STYLE );

    /// Creates the controls and sizers
    void CreateControls();
    iONode getProperties(){ return m_Props;}
    void OnSelectPage( wxCommandEvent& event );
    void SelectNext();
    void SelectPrev();
    void initBBT();
    void initSBT();
    bool OnApply();

////@begin LocDialog event handler declarations

    /// wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BITMAPBUTTON
    void OnBitmapbuttonClick( wxCommandEvent& event );

    /// wxEVT_COMMAND_LIST_ITEM_SELECTED event handler for ID_LISTCTRLINDEX_LC
    void OnListctrlindexLcSelected( wxListEvent& event );

    /// wxEVT_COMMAND_LIST_COL_CLICK event handler for ID_LISTCTRLINDEX_LC
    void OnListctrlindexLcColLeftClick( wxListEvent& event );

    /// wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BUTTON_LOC_NEW
    void OnButtonLocNewClick( wxCommandEvent& event );

    /// wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BUTTON_DELETE
    void OnButtonDeleteClick( wxCommandEvent& event );

    /// wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BUTTON_LOCO_DOC
    void OnButtonLocoDocClick( wxCommandEvent& event );

    /// wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_LOC_COPY
    void OnLocCopyClick( wxCommandEvent& event );

    /// wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BUTTON_IMPORTLOCOS
    void OnButtonImportlocosClick( wxCommandEvent& event );

    /// wxEVT_COMMAND_CHECKBOX_CLICKED event handler for ID_LOC_ONRESTOREFX
    void OnRestoreFxClick( wxCommandEvent& event );

    /// wxEVT_COMMAND_CHECKBOX_CLICKED event handler for ID_LOC_RESTORESPEED
    void OnRestoreSpeedClick( wxCommandEvent& event );

    /// wxEVT_COMMAND_CHECKBOX_CLICKED event handler for ID_LOC_MANUALLY
    void OnLocManuallyClick( wxCommandEvent& event );

    /// wxEVT_COMMAND_CHECKBOX_CLICKED event handler for ID_LOC_SHOW
    void OnShowClick( wxCommandEvent& event );

    /// wxEVT_LEFT_UP event handler for ID_ABOX_ID
    void OnAboxID( wxMouseEvent& event );

    /// wxEVT_LEFT_UP event handler for ID_ABOX_IDENT
    void OnAboxIdent( wxMouseEvent& event );

    /// wxEVT_LEFT_UP event handler for ID_ABOX_ROADNAME
    void OnAboxRoadname( wxMouseEvent& event );

    /// wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_SELECT_LOCOIMAGE
    void OnSelectLocoimage( wxCommandEvent& event );

    /// wxEVT_LEFT_UP event handler for ID_ABOX_CATNR
    void OnAboxCatnr( wxMouseEvent& event );

    /// wxEVT_LEFT_UP event handler for ID_ABOX_DECODERTYPE
    void onABoxDecoderType( wxMouseEvent& event );

    /// wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BUTTON_SHOWDOC
    void OnButtonShowdocClick( wxCommandEvent& event );

    /// wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_LC_SERVICED
    void OnLcServicedClick( wxCommandEvent& event );

    /// wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_LOC_ACTIONS
    void OnLocActionsClick( wxCommandEvent& event );

    /// wxEVT_COMMAND_TEXT_UPDATED event handler for ID_TEXTCTRL_SPEEDSTEPS
    void OnTextctrlSpeedstepsTextUpdated( wxCommandEvent& event );

    /// wxEVT_COMMAND_TEXT_ENTER event handler for ID_TEXTCTRL_SPEEDSTEPS
    void OnTextctrlSpeedstepsEnter( wxCommandEvent& event );

    /// wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BUTTON_F0
    void OnButtonF0Click( wxCommandEvent& event );

    /// wxEVT_LEFT_DCLICK event handler for ID_LOC_ICONF0
    void OnLocIconf0( wxMouseEvent& event );

    /// wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_LOC_FN_GROUP_PREV
    void OnLocFnGroupPrevClick( wxCommandEvent& event );

    /// wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_LOC_FN_GROUP
    void OnLocFnGroupClick( wxCommandEvent& event );

    /// wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BUTTON_F1
    void OnButtonF1Click( wxCommandEvent& event );

    /// wxEVT_LEFT_DCLICK event handler for ID_LOC_SOUND1
    void OnLocSound1( wxMouseEvent& event );

    /// wxEVT_LEFT_DCLICK event handler for ID_LOC_ICONF1
    void OnLocIconf1( wxMouseEvent& event );

    /// wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BUTTON_F2
    void OnButtonF2Click( wxCommandEvent& event );

    /// wxEVT_LEFT_DCLICK event handler for ID_LOC_SOUND2
    void OnLocSound2( wxMouseEvent& event );

    /// wxEVT_LEFT_DCLICK event handler for ID_LOC_ICONF2
    void OnLocIconf2( wxMouseEvent& event );

    /// wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BUTTON_F3
    void OnButtonF3Click( wxCommandEvent& event );

    /// wxEVT_LEFT_DCLICK event handler for ID_LOC_SOUND3
    void OnLocSound3( wxMouseEvent& event );

    /// wxEVT_LEFT_DCLICK event handler for ID_LOC_ICONF3
    void OnLocIconf3( wxMouseEvent& event );

    /// wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BUTTON_F4
    void OnButtonF4Click( wxCommandEvent& event );

    /// wxEVT_LEFT_DCLICK event handler for ID_LOC_SOUND4
    void OnLocSound4( wxMouseEvent& event );

    /// wxEVT_LEFT_DCLICK event handler for ID_LOC_ICONF4
    void OnLocIconf4( wxMouseEvent& event );

    /// wxEVT_COMMAND_CHECKBOX_CLICKED event handler for ID_CONSTS_LIGHTSOFF
    void OnConsistLightsoffClick( wxCommandEvent& event );

    /// wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BUTTON_LOC_CONSIST_ADD
    void OnButtonLocConsistAddClick( wxCommandEvent& event );

    /// wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BUTTON_LOC_CONSIST_DELETE
    void OnButtonLocConsistDeleteClick( wxCommandEvent& event );

    /// wxEVT_GRID_CELL_LEFT_CLICK event handler for ID_GRID_LOC_CV
    void OnCVCellLeftClick( wxGridEvent& event );

    /// wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BUTTON_LC_CV_DESC
    void OnButtonLcCvDescClick( wxCommandEvent& event );

    /// wxEVT_COMMAND_LIST_ITEM_SELECTED event handler for ID_LOC_BBTLIST2
    void OnLocBbtlist2Selected( wxListEvent& event );

    /// wxEVT_COMMAND_LIST_COL_CLICK event handler for ID_LOC_BBTLIST2
    void OnLocBbtlist2ColLeftClick( wxListEvent& event );

    /// wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BBT_ADD
    void OnBbtAddClick( wxCommandEvent& event );

    /// wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BUTTON_BBT_DELETE
    void OnButtonBbtDeleteClick( wxCommandEvent& event );

    /// wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BBT_COPY
    void OnBbtCopyClick( wxCommandEvent& event );

    /// wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BUTTON_BBT_DELETEALL
    void OnButtonBbtDeleteallClick( wxCommandEvent& event );

    /// wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BBT_MODIFY
    void OnBbtModifyClick( wxCommandEvent& event );

    /// wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BBT_EXPORT
    void OnBbtExportClick( wxCommandEvent& event );

    /// wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BBT_IMPORT
    void OnBbtImportClick( wxCommandEvent& event );

    /// wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BBT_FIXALL
    void OnBbtFixallClick( wxCommandEvent& event );

    /// wxEVT_COMMAND_CHECKBOX_CLICKED event handler for ID_BBT_GENATE_IN
    void OnBbtGenateInClick( wxCommandEvent& event );

    /// wxEVT_COMMAND_CHECKBOX_CLICKED event handler for ID_LOC_REGULATED
    void OnLocRegulatedClick( wxCommandEvent& event );

    /// wxEVT_COMMAND_LIST_ITEM_SELECTED event handler for ID_SBT_LIST
    void OnSbtListSelected( wxListEvent& event );

    /// wxEVT_COMMAND_LIST_COL_CLICK event handler for ID_SBT_LIST
    void OnSbtListColLeftClick( wxListEvent& event );

    /// wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_SBT_ADD
    void OnSbtAddClick( wxCommandEvent& event );

    /// wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_SBT_DELETE
    void OnSbtDeleteClick( wxCommandEvent& event );

    /// wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_SBT_MODIFY
    void OnSbtModifyClick( wxCommandEvent& event );

    /// wxEVT_COMMAND_BUTTON_CLICKED event handler for wxID_CANCEL
    void OnCancelClick( wxCommandEvent& event );

    /// wxEVT_COMMAND_BUTTON_CLICKED event handler for wxID_APPLY
    void OnApplyClick( wxCommandEvent& event );

    /// wxEVT_COMMAND_BUTTON_CLICKED event handler for wxID_OK
    void OnOkClick( wxCommandEvent& event );

    /// wxEVT_COMMAND_BUTTON_CLICKED event handler for wxID_HELP
    void OnHelpClick( wxCommandEvent& event );

////@end LocDialog event handler declarations

////@begin LocDialog member function declarations

    iONode GetProps() const { return m_Props ; }
    void SetProps(iONode value) { m_Props = value ; }

    /// Retrieves bitmap resources
    wxBitmap GetBitmapResource( const wxString& name );

    /// Retrieves icon resources
    wxIcon GetIconResource( const wxString& name );
////@end LocDialog member function declarations

    /// Should we show tooltips?
    static bool ShowToolTips();

////@begin LocDialog member variables
    wxBitmapButton* m_LocImage;
    wxNotebook* m_Notebook;
    wxPanel* m_IndexPanel;
    wxListCtrl* m_List2;
    wxButton* m_New;
    wxButton* m_Delete;
    wxButton* m_Doc;
    wxButton* m_Copy;
    wxButton* m_ImportLocos;
    wxCheckBox* m_GuestImport;
    wxCheckBox* m_RestoreFx;
    wxCheckBox* m_RestoreFxAlways;
    wxCheckBox* m_RestoreSpeed;
    wxCheckBox* m_LocManually;
    wxCheckBox* m_Show;
    wxStaticText* m_labTrain;
    wxTextCtrl* m_Train;
    wxPanel* m_General_Panel;
    wxBoxSizer* m_GeneralSizer;
    wxStaticText* m_label_ID;
    wxTextCtrl* m_ID;
    wxStaticText* m_labShortID;
    wxTextCtrl* m_ShortID;
    wxStaticText* m_labIdent;
    wxTextCtrl* m_Ident;
    wxStaticText* m_labRoadname;
    wxTextCtrl* m_Roadname;
    wxStaticText* m_labNumber;
    wxTextCtrl* m_Number;
    wxStaticText* m_Label_Description;
    wxTextCtrl* m_Description;
    wxStaticText* m_labImageName;
    wxTextCtrl* m_ImageName;
    wxButton* m_SelectLocoImag;
    wxStaticText* m_labImageNr;
    wxSpinCtrl* m_ImageNr;
    wxStaticText* m_Label_Length;
    wxSpinCtrl* m_Length;
    wxStaticText* m_labNrCars;
    wxSpinCtrl* m_NrCars;
    wxStaticText* m_Label_CatalogNr;
    wxTextCtrl* m_CatNr;
    wxStaticText* m_labDecType;
    wxTextCtrl* m_DecoderType;
    wxStaticText* m_labDocumentation;
    wxTextCtrl* m_Documentation;
    wxButton* m_ShowDoc;
    wxStaticText* m_Label_Purchased;
    wxTextCtrl* m_Purchased;
    wxStaticText* m_labValue;
    wxTextCtrl* m_Value;
    wxStaticText* m_Label_Runtime;
    wxTextCtrl* m_RunTime;
    wxStaticText* m_labMTime;
    wxTextCtrl* m_MTime;
    wxStaticText* m_labMDate;
    wxTextCtrl* m_MDate;
    wxCheckBox* m_UseShortID;
    wxStaticText* m_labThrottleNr;
    wxSpinCtrl* m_ThrottleNr;
    wxButton* m_Serviced;
    wxStaticText* m_labMInt;
    wxSpinCtrl* m_MInt;
    wxStaticText* m_labRemark;
    wxTextCtrl* m_Remark;
    wxButton* m_Actions;
    wxPanel* m_Interface_Panel;
    wxStaticText* m_Label_IID;
    wxComboBox* m_IID;
    wxStaticText* m_Label_Bus;
    wxTextCtrl* m_Bus;
    wxStaticText* m_Label_Address;
    wxTextCtrl* m_Address;
    wxTextCtrl* m_SecAddress;
    wxStaticText* m_Label_Protocol;
    wxChoice* m_Protocol;
    wxStaticText* m_LabelProtVersion;
    wxTextCtrl* m_ProtVersion;
    wxStaticText* m_LabelSpeedSteps;
    wxTextCtrl* m_SpeedSteps;
    wxTextCtrl* m_SecSpeedSteps;
    wxStaticText* m_LabelFunCnt;
    wxTextCtrl* m_FunCnt;
    wxStaticBox* m_VelocityBox;
    wxStaticText* m_Label_V_min;
    wxTextCtrl* m_V_min;
    wxStaticText* m_Label_V_Rmin;
    wxTextCtrl* m_V_Rmin;
    wxStaticText* m_Label_V_mid;
    wxTextCtrl* m_V_mid;
    wxStaticText* m_Label_V_Rmid;
    wxTextCtrl* m_V_Rmid;
    wxStaticText* m_labVcru;
    wxTextCtrl* m_V_cru;
    wxStaticText* m_labVRcru;
    wxTextCtrl* m_V_Rcru;
    wxStaticText* m_Label_V_max;
    wxTextCtrl* m_V_max;
    wxTextCtrl* m_VmaxSec;
    wxStaticText* m_Label_V_Rmax;
    wxTextCtrl* m_V_Rmax;
    wxStaticBox* m_OptionsBox;
    wxStaticText* m_Label_Mass;
    wxTextCtrl* m_Mass;
    wxStaticText* m_labDirPause;
    wxTextCtrl* m_DirPause;
    wxStaticText* m_LabelV_mode;
    wxCheckBox* m_V_mode_percent;
    wxStaticText* m_LabelPlacing;
    wxCheckBox* m_Placing;
    wxCheckBox* m_Info4Throttle;
    wxStaticBox* m_AccelerationBox;
    wxCheckBox* m_AdjustAccel;
    wxStaticText* m_labMaxLoad;
    wxSpinCtrl* m_MaxLoad;
    wxStaticText* m_labMinAccel;
    wxSpinCtrl* m_MinAccel;
    wxStaticText* m_labMaxAccel;
    wxSpinCtrl* m_MaxAccel;
    wxPanel* m_DetailsPanel;
    wxStaticText* m_Label_Blockwait;
    wxTextCtrl* m_Blockwait;
    wxStaticText* m_labBlockWaitSec;
    wxStaticText* m_labMaxWaitTime;
    wxTextCtrl* m_MaxWaitTime;
    wxStaticText* m_labMaxBlockWaitSec;
    wxStaticText* m_labEventTimer;
    wxTextCtrl* m_EventTimer;
    wxStaticText* m_labEventTimerMS;
    wxStaticText* m_labEvtCorrection;
    wxSpinCtrl* m_EvtCorrection;
    wxStaticText* m_labTimerCorrectionPercent;
    wxStaticText* m_labPriority;
    wxSpinCtrl* m_Priority;
    wxStaticText* m_labSwapTimer;
    wxSpinCtrl* m_SwapTimer;
    wxStaticText* m_labSwapTimerMS;
    wxStaticText* m_labStartupTour;
    wxComboBox* m_StartupTour;
    wxStaticText* m_labStartupSchedule;
    wxComboBox* m_StartupSchedule;
    wxRadioBox* m_CargoBox;
    wxCheckBox* m_Commuter;
    wxCheckBox* m_UseScheduleTime;
    wxCheckBox* m_secondNextBlock;
    wxCheckBox* m_ShortIn;
    wxCheckBox* m_InAtPre2In;
    wxCheckBox* m_UseManualRoutes;
    wxCheckBox* m_UseOwnWaittime;
    wxCheckBox* m_Check2In;
    wxCheckBox* m_UseDepartDelay;
    wxCheckBox* m_FreeBlockOnEnter;
    wxCheckBox* m_V0onSwap;
    wxCheckBox* m_BBT;
    wxCheckBox* m_ReduceSpeedAtEnter;
    wxCheckBox* m_ResetPlacing;
    wxRadioBox* m_EngineBox;
    wxStaticText* m_labClass;
    wxTextCtrl* m_Class;
    wxRadioBox* m_Era;
    wxPanel* m_FunctionPanel;
    wxStaticText* m_labF0Nr;
    wxStaticText* m_labF0Desc;
    wxStaticText* m_labF0Timer;
    wxStaticText* m_labF0Events;
    wxStaticText* m_labF0Icon;
    wxStaticText* m_Label_f0;
    wxTextCtrl* m_f0;
    wxSpinCtrl* m_TimerF0;
    wxButton* m_Button_f0;
    wxTextCtrl* m_F0Icon;
    wxStaticText* m_labFnGroup;
    wxButton* m_FunctionGroup;
    wxStaticText* m_labFnNr;
    wxStaticText* m_labFnDesc;
    wxStaticText* m_labFnTimer;
    wxStaticText* m_labFnEvents;
    wxStaticText* m_labSound;
    wxStaticText* m_labIcon;
    wxStaticText* m_labFnAddr;
    wxStaticText* m_labAddrFn;
    wxStaticText* m_Label_f1;
    wxTextCtrl* m_f1;
    wxSpinCtrl* m_TimerF1;
    wxButton* m_Button_f1;
    wxTextCtrl* m_Sound1;
    wxTextCtrl* m_Icon_f1;
    wxSpinCtrl* m_F1Addr;
    wxSpinCtrl* m_F1AddrFn;
    wxStaticText* m_Label_f2;
    wxTextCtrl* m_f2;
    wxSpinCtrl* m_TimerF2;
    wxButton* m_Button_f2;
    wxTextCtrl* m_Sound2;
    wxTextCtrl* m_Icon_f2;
    wxSpinCtrl* m_F2Addr;
    wxSpinCtrl* m_F2AddrFn;
    wxStaticText* m_Label_f3;
    wxTextCtrl* m_f3;
    wxSpinCtrl* m_TimerF3;
    wxButton* m_Button_f3;
    wxTextCtrl* m_Sound3;
    wxTextCtrl* m_Icon_f3;
    wxSpinCtrl* m_F3Addr;
    wxSpinCtrl* m_F3AddrFn;
    wxStaticText* m_Label_f4;
    wxTextCtrl* m_f4;
    wxSpinCtrl* m_TimerF4;
    wxButton* m_Button_f4;
    wxTextCtrl* m_Sound4;
    wxTextCtrl* m_Icon_f4;
    wxSpinCtrl* m_F4Addr;
    wxSpinCtrl* m_F4AddrFn;
    wxPanel* m_ConsistsPanel;
    wxStaticBox* m_labDetails;
    wxCheckBox* m_LightsOff;
    wxCheckBox* m_SyncLights;
    wxCheckBox* m_SyncFun;
    wxCheckBox* m_FSync1;
    wxCheckBox* m_FSync2;
    wxCheckBox* m_FSync3;
    wxCheckBox* m_FSync4;
    wxCheckBox* m_FSync5;
    wxCheckBox* m_FSync6;
    wxCheckBox* m_FSync7;
    wxCheckBox* m_FSync8;
    wxCheckBox* m_FSync9;
    wxCheckBox* m_FSync10;
    wxCheckBox* m_FSync11;
    wxCheckBox* m_FSync12;
    wxCheckBox* m_FSync13;
    wxCheckBox* m_FSync14;
    wxCheckBox* m_FSync15;
    wxCheckBox* m_FSync16;
    wxCheckBox* m_FSync17;
    wxCheckBox* m_FSync18;
    wxCheckBox* m_FSync19;
    wxCheckBox* m_FSync20;
    wxCheckBox* m_FSync21;
    wxCheckBox* m_FSync22;
    wxCheckBox* m_FSync23;
    wxCheckBox* m_FSync24;
    wxCheckBox* m_FSync25;
    wxCheckBox* m_FSync26;
    wxCheckBox* m_FSync27;
    wxCheckBox* m_FSync28;
    wxStaticText* m_labConsistList;
    wxListBox* m_ConsistList;
    wxStaticText* m_labConsistLocID;
    wxComboBox* m_ConsistLocID;
    wxButton* m_AddConsistLoc;
    wxButton* m_DeleteConsistLoc;
    wxPanel* m_CVPanel;
    wxGrid* m_CVList;
    wxStaticText* m_labCVDesc;
    wxTextCtrl* m_CVDescription;
    wxButton* m_CVDescModify;
    wxPanel* m_BBTPanel;
    wxStaticText* m_labBBTSteps;
    wxSpinCtrl* m_BBTSteps;
    wxStaticText* m_labBBTStepsDummy;
    wxStaticText* m_labBBTStartInterval;
    wxSpinCtrl* m_BBTStartInterval;
    wxStaticText* m_labBBTMaxDiff;
    wxSpinCtrl* m_BBTMaxDiff;
    wxStaticText* m_labBBT10ms;
    wxStaticText* m_labBBTCorrection;
    wxSpinCtrl* m_BBTCorrection;
    wxStaticText* m_labBBTPer;
    wxRadioBox* m_BBTKey;
    wxStaticText* m_labBBTCalculation;
    wxListCtrl* m_BBTList2;
    wxStaticText* m_labBBTFromBlock;
    wxComboBox* m_BBTFromBlock;
    wxStaticText* m_labBBTBlock;
    wxComboBox* m_BBTBlock;
    wxStaticText* m_labBBTInterval;
    wxSpinCtrl* m_BBTInterval;
    wxStaticText* m_labBBTRoute;
    wxComboBox* m_BBTRoute;
    wxStaticText* m_labBBTSpeed;
    wxSpinCtrl* m_BBTSpeed;
    wxStaticText* m_labBBTDelay;
    wxSpinCtrl* m_BBTDelay;
    wxButton* m_BBTAdd;
    wxButton* m_BBTDelete;
    wxButton* m_BBTCopy;
    wxButton* m_BBTDeleteAll;
    wxButton* m_BBTModify;
    wxButton* m_BBTExport;
    wxButton* m_BBTImport;
    wxButton* m_BBTFixAll;
    wxCheckBox* m_BBTFixed;
    wxCheckBox* m_BBTGenerateIn;
    wxPanel* m_SBTPanel;
    wxStaticBox* m_SBTDefaultBox;
    wxStaticText* m_labDecelerate;
    wxSpinCtrl* m_Decelerate;
    wxStaticText* m_LabelV_step;
    wxSpinCtrl* m_Accel;
    wxCheckBox* m_Regulated;
    wxListCtrl* m_SBTList2;
    wxStaticText* m_labSBTBlock;
    wxComboBox* m_SBTBlock;
    wxStaticText* m_labSBTTrain;
    wxComboBox* m_SBTTrain;
    wxStaticText* m_labSBTInterval;
    wxSpinCtrl* m_SBTInterval;
    wxStaticText* m_labSBTDecelerate;
    wxSpinCtrl* m_SBTDecelerate;
    wxButton* m_SBTAdd;
    wxButton* m_SBTDelete;
    wxButton* m_SBTModify;
    wxButton* m_Cancel;
    wxButton* m_Apply;
    wxButton* m_OK;
    iONode m_Props;
////@end LocDialog member variables
    int m_iBBTSel;
    int m_iSBTSel;
};

/*!
 * LocDialog class declaration
 */


#endif
    // _LOCDIALOG_H_
