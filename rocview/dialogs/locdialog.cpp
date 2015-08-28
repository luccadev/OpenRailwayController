/*
 Rocrail - Model Railroad Software

Copyright (c) 2002-2015 Robert Jan Versluis, Rocrail.net

 


 All rights reserved.
*/
#if defined(__GNUG__) && !defined(__APPLE__)
#pragma implementation "locdialog.h"
#endif

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#include "wx/defs.h"
#endif

////@begin includes
#include "wx/imaglist.h"
////@end includes
#include <wx/filedlg.h>

#include "locdialog.h"
#include "fundialog.h"
#include "actionsctrldlg.h"

#include "rocview/public/guiapp.h"
#include "rocview/public/base.h"
#include "rocrail/wrapper/public/ModelCmd.h"
#include "rocrail/wrapper/public/Plan.h"
#include "rocrail/wrapper/public/Loc.h"
#include "rocrail/wrapper/public/Item.h"
#include "rocrail/wrapper/public/LocList.h"
#include "rocrail/wrapper/public/FunDef.h"
#include "rocview/wrapper/public/Gui.h"
#include "rocrail/wrapper/public/CVByte.h"
#include "rocrail/wrapper/public/Schedule.h"
#include "rocrail/wrapper/public/Tour.h"
#include "rocrail/wrapper/public/BBT.h"
#include "rocrail/wrapper/public/SBT.h"
#include "rocrail/wrapper/public/Block.h"
#include "rocrail/wrapper/public/Route.h"
#include "rocrail/wrapper/public/Operator.h"


#include "rocs/public/trace.h"
#include "rocs/public/strtok.h"
#include "rocs/public/system.h"

#include "rocview/res/icons.hpp"

#include "rocview/xpm/nopict.xpm"

////@begin XPM images
////@end XPM images

/*!
 * LocDialog type definition
 */

/*!
 * LocDialog event table definition
 */

BEGIN_EVENT_TABLE( LocDialog, wxDialog )

////@begin LocDialog event table entries
    EVT_BUTTON( ID_BITMAPBUTTON, LocDialog::OnBitmapbuttonClick )
    EVT_LIST_ITEM_SELECTED( ID_LISTCTRLINDEX_LC, LocDialog::OnListctrlindexLcSelected )
    EVT_LIST_COL_CLICK( ID_LISTCTRLINDEX_LC, LocDialog::OnListctrlindexLcColLeftClick )
    EVT_BUTTON( ID_BUTTON_LOC_NEW, LocDialog::OnButtonLocNewClick )
    EVT_BUTTON( ID_BUTTON_DELETE, LocDialog::OnButtonDeleteClick )
    EVT_BUTTON( ID_BUTTON_LOCO_DOC, LocDialog::OnButtonLocoDocClick )
    EVT_BUTTON( ID_LOC_COPY, LocDialog::OnLocCopyClick )
    EVT_BUTTON( ID_BUTTON_IMPORTLOCOS, LocDialog::OnButtonImportlocosClick )
    EVT_CHECKBOX( ID_LOC_ONRESTOREFX, LocDialog::OnRestoreFxClick )
    EVT_CHECKBOX( ID_LOC_RESTORESPEED, LocDialog::OnRestoreSpeedClick )
    EVT_CHECKBOX( ID_LOC_MANUALLY, LocDialog::OnLocManuallyClick )
    EVT_CHECKBOX( ID_LOC_SHOW, LocDialog::OnShowClick )
    EVT_BUTTON( ID_SELECT_LOCOIMAGE, LocDialog::OnSelectLocoimage )
    EVT_BUTTON( ID_BUTTON_SHOWDOC, LocDialog::OnButtonShowdocClick )
    EVT_BUTTON( ID_LC_SERVICED, LocDialog::OnLcServicedClick )
    EVT_BUTTON( ID_LOC_ACTIONS, LocDialog::OnLocActionsClick )
    EVT_TEXT( ID_TEXTCTRL_SPEEDSTEPS, LocDialog::OnTextctrlSpeedstepsTextUpdated )
    EVT_TEXT_ENTER( ID_TEXTCTRL_SPEEDSTEPS, LocDialog::OnTextctrlSpeedstepsEnter )
    EVT_BUTTON( ID_BUTTON_F0, LocDialog::OnButtonF0Click )
    EVT_BUTTON( ID_LOC_FN_GROUP_PREV, LocDialog::OnLocFnGroupPrevClick )
    EVT_BUTTON( ID_LOC_FN_GROUP, LocDialog::OnLocFnGroupClick )
    EVT_BUTTON( ID_BUTTON_F1, LocDialog::OnButtonF1Click )
    EVT_BUTTON( ID_BUTTON_F2, LocDialog::OnButtonF2Click )
    EVT_BUTTON( ID_BUTTON_F3, LocDialog::OnButtonF3Click )
    EVT_BUTTON( ID_BUTTON_F4, LocDialog::OnButtonF4Click )
    EVT_CHECKBOX( ID_CONSTS_LIGHTSOFF, LocDialog::OnConsistLightsoffClick )
    EVT_BUTTON( ID_BUTTON_LOC_CONSIST_ADD, LocDialog::OnButtonLocConsistAddClick )
    EVT_BUTTON( ID_BUTTON_LOC_CONSIST_DELETE, LocDialog::OnButtonLocConsistDeleteClick )
    EVT_GRID_CELL_LEFT_CLICK( LocDialog::OnCVCellLeftClick )
    EVT_BUTTON( ID_BUTTON_LC_CV_DESC, LocDialog::OnButtonLcCvDescClick )
    EVT_LIST_ITEM_SELECTED( ID_LOC_BBTLIST2, LocDialog::OnLocBbtlist2Selected )
    EVT_LIST_COL_CLICK( ID_LOC_BBTLIST2, LocDialog::OnLocBbtlist2ColLeftClick )
    EVT_BUTTON( ID_BBT_ADD, LocDialog::OnBbtAddClick )
    EVT_BUTTON( ID_BUTTON_BBT_DELETE, LocDialog::OnButtonBbtDeleteClick )
    EVT_BUTTON( ID_BBT_COPY, LocDialog::OnBbtCopyClick )
    EVT_BUTTON( ID_BUTTON_BBT_DELETEALL, LocDialog::OnButtonBbtDeleteallClick )
    EVT_BUTTON( ID_BBT_MODIFY, LocDialog::OnBbtModifyClick )
    EVT_BUTTON( ID_BBT_EXPORT, LocDialog::OnBbtExportClick )
    EVT_BUTTON( ID_BBT_IMPORT, LocDialog::OnBbtImportClick )
    EVT_BUTTON( ID_BBT_FIXALL, LocDialog::OnBbtFixallClick )
    EVT_CHECKBOX( ID_BBT_GENATE_IN, LocDialog::OnBbtGenateInClick )
    EVT_CHECKBOX( ID_LOC_REGULATED, LocDialog::OnLocRegulatedClick )
    EVT_LIST_ITEM_SELECTED( ID_SBT_LIST, LocDialog::OnSbtListSelected )
    EVT_LIST_COL_CLICK( ID_SBT_LIST, LocDialog::OnSbtListColLeftClick )
    EVT_BUTTON( ID_SBT_ADD, LocDialog::OnSbtAddClick )
    EVT_BUTTON( ID_SBT_DELETE, LocDialog::OnSbtDeleteClick )
    EVT_BUTTON( ID_SBT_MODIFY, LocDialog::OnSbtModifyClick )
    EVT_BUTTON( wxID_CANCEL, LocDialog::OnCancelClick )
    EVT_BUTTON( wxID_APPLY, LocDialog::OnApplyClick )
    EVT_BUTTON( wxID_OK, LocDialog::OnOkClick )
    EVT_BUTTON( wxID_HELP, LocDialog::OnHelpClick )
////@end LocDialog event table entries
    EVT_MENU( ID_PANEL_GENERAL, LocDialog::OnSelectPage )

END_EVENT_TABLE()

/*!
 * LocDialog constructors
 */

static bool ms_BBTSort = true;
static bool ms_SBTSort = true;

LocDialog::LocDialog(  wxWindow* parent, iONode p_Props, bool save )
{
  m_TabAlign = wxGetApp().getTabAlign();
  Create( parent, -1, wxGetApp().getMsg( "loctable" ) );
  m_Props = p_Props;
  m_bSave = save;
  m_iSelectedCV = -1;
  m_iFunGroup = 0;
  m_iBBTSel = wxNOT_FOUND;
  m_iSBTSel = wxNOT_FOUND;
  m_BBTList = NULL;
  m_SBTList = NULL;

  initLabels();
  initCVDesc();

  m_IndexPanel->GetSizer()->Layout();
  m_General_Panel->GetSizer()->Layout();
  m_Interface_Panel->GetSizer()->Layout();
  m_DetailsPanel->GetSizer()->Layout();
  m_FunctionPanel->GetSizer()->Layout();
  m_CVPanel->GetSizer()->Layout();
  m_BBTPanel->GetSizer()->Layout();
  m_SBTPanel->GetSizer()->Layout();
  m_ConsistsPanel->GetSizer()->Layout();

  m_Notebook->Fit();

  GetSizer()->Fit(this);
  GetSizer()->SetSizeHints(this);

  if( InitIndex() ) {
    InitValues();
    //m_Notebook->SetSelection( 1 );
    wxCommandEvent event( wxEVT_COMMAND_MENU_SELECTED, ID_PANEL_GENERAL );
    wxPostEvent( this, event );
  }

  m_List2->SetFocus();
}

void LocDialog::SelectNext() {
  m_Props = selectNext();
  InitValues();
}


void LocDialog::SelectPrev() {
  m_Props = selectPrev();
  InitValues();
}


void LocDialog::OnSelectPage(wxCommandEvent& event) {
  m_Notebook->SetSelection( 1 );
}


/* comparator for sorting by id: */
static int __sortID(obj* _a, obj* _b)
{
    iONode a = (iONode)*_a;
    iONode b = (iONode)*_b;
    const char* idA = wItem.getid( a );
    const char* idB = wItem.getid( b );
    return strcmp( idA, idB );
}

/* comparator for sorting by id: */
static int __sortStr(obj* _a, obj* _b)
{
    const char* a = (const char*)*_a;
    const char* b = (const char*)*_b;
    return strcmp( a, b );
}


void LocDialog::initLabels() {
  m_Notebook->SetPageText( 0, wxGetApp().getMsg( "index" ) );
  m_Notebook->SetPageText( 1, wxGetApp().getMsg( "general" ) );
  m_Notebook->SetPageText( 2, wxGetApp().getMsg( "interface" ) );
  m_Notebook->SetPageText( 3, wxGetApp().getMsg( "details" ) );
  m_Notebook->SetPageText( 4, wxGetApp().getMsg( "functions" ) );
  m_Notebook->SetPageText( 5, wxGetApp().getMsg( "multipleunit" ) );

  // Index
  initList(m_List2, this, false, true, true, true, false, true);
  m_New->SetLabel( wxGetApp().getMsg( "new" ) );
  m_Delete->SetLabel( wxGetApp().getMsg( "delete" ) );
  m_Doc->SetLabel( wxGetApp().getMsg( "doc_report" ) );
  m_ImportLocos->SetLabel( wxGetApp().getMenu( "import" ) );
  m_GuestImport->SetLabel( wxGetApp().getMsg( "guestimport" ) );
  m_Copy->SetLabel( wxGetApp().getMsg( "copy" ) );
  m_labTrain->SetLabel( wxGetApp().getMsg( "train" ) );
  m_LocManually->SetLabel( wxGetApp().getMsg( "manually" ) );


  // General
  m_label_ID->SetLabel( wxGetApp().getMsg( "id" ) + wxT(" @"));
  m_labShortID->SetLabel( wxGetApp().getMsg( "shortid" ) );
  m_labRoadname->SetLabel( wxGetApp().getMsg( "roadname" ) + wxT(" @") );
  m_labNumber->SetLabel( wxGetApp().getMsg( "number" ) );
  m_Label_Description->SetLabel( wxGetApp().getMsg( "description" ) );
  m_Label_Length->SetLabel( wxGetApp().getMsg( "length" ) );
  m_Label_CatalogNr->SetLabel( wxGetApp().getMsg( "catnr" ) + wxT(" @") );
  m_Label_Purchased->SetLabel( wxGetApp().getMsg( "purchased" ) );
  m_labValue->SetLabel( wxGetApp().getMsg( "value" ) );
  m_Label_Runtime->SetLabel( wxGetApp().getMsg( "runtime" ) );
  m_labDecType->SetLabel( wxGetApp().getMsg( "decodertype" ) + wxT(" @") );
  m_labIdent->SetLabel( wxGetApp().getMsg( "identifier" ) + wxT(" @") );
  m_Ident->SetToolTip( wxGetApp().getTip( "identifier" ) );
  m_labRemark->SetLabel( wxGetApp().getMsg( "remark" ) );
  m_labImageName->SetLabel( wxGetApp().getMsg( "image" ) );
  m_labImageNr->SetLabel( wxGetApp().getMsg( "number" ) );
  m_labNrCars->SetLabel( wxGetApp().getMsg( "nrcars" ) );
  m_Show->SetLabel( wxGetApp().getMsg( "show" ) );
  m_labMTime->SetLabel( wxGetApp().getMsg( "mtime" ) );
  m_labMDate->SetLabel( wxGetApp().getMsg( "mdate" ) );
  m_labMInt->SetLabel( wxGetApp().getMsg( "mint" ) );
  m_MTime->SetToolTip( wxGetApp().getTip( "mtime" ) );
  m_MInt->SetToolTip( wxGetApp().getTip( "mint" ) );
  m_Serviced->SetLabel( wxGetApp().getMsg( "serviced" ) );
  m_Serviced->SetToolTip( wxGetApp().getTip( "serviced" ) );
  m_UseShortID->SetLabel( wxGetApp().getMsg( "use" ) + _T(" ") + wxGetApp().getMsg( "shortid" ) );
  m_Actions->SetLabel( wxGetApp().getMsg( "actions" )+_T("...") );
  m_labDocumentation->SetLabel( wxGetApp().getMsg( "documentation" ) );
  m_labThrottleNr->SetLabel( wxGetApp().getMsg( "locctrl" ) );

  // Interface
  BaseDialog::addIIDs(m_IID);

  m_Label_Bus->SetLabel( wxGetApp().getMsg( "bus" ) );
  m_Label_Address->SetLabel( wxGetApp().getMsg( "address" ) );
  m_Label_IID->SetLabel( wxGetApp().getMsg( "iid" ) );
  m_Label_Protocol->SetLabel( wxGetApp().getMsg( "protocol" ) );
  m_LabelProtVersion->SetLabel( wxGetApp().getMsg( "protocol_version" ) );
  m_LabelSpeedSteps->SetLabel( wxGetApp().getMsg( "speedsteps" ) );
  m_LabelFunCnt->SetLabel( wxGetApp().getMsg( "functioncount" ) );
  m_Label_V_min->SetLabel( wxGetApp().getMsg( "v_min" ) );
  m_Label_V_mid->SetLabel( wxGetApp().getMsg( "v_mid" ) );
  m_labVcru->SetLabel( wxGetApp().getMsg( "v_cru" ) );
  m_Label_V_max->SetLabel( wxGetApp().getMsg( "v_max" ) );

  m_Label_V_Rmin->SetLabel( wxGetApp().getMsg( "v_rmin" ) );
  m_Label_V_Rmid->SetLabel( wxGetApp().getMsg( "v_rmid" ) );
  m_labVRcru->SetLabel( wxGetApp().getMsg( "v_rcru" ) );
  m_Label_V_Rmax->SetLabel( wxGetApp().getMsg( "v_rmax" ) );
  m_V_Rmin->SetToolTip( wxGetApp().getTip( "v_rmin" ) );
  m_V_Rmax->SetToolTip( wxGetApp().getTip( "v_rmax" ) );

  m_LabelV_mode->SetLabel( wxGetApp().getMsg( "v_mode" ) );
  m_V_mode_percent->SetLabel( wxGetApp().getMsg( "percent" ) );
  m_Label_Mass->SetLabel( wxGetApp().getMsg( "mass" ) );
  m_LabelPlacing->SetLabel( wxGetApp().getMsg( "placing" ) );
  m_Placing->SetLabel( wxGetApp().getMsg( "default" ) );
  m_labDirPause->SetLabel( wxGetApp().getMsg( "dirpause" ) );
  m_DirPause->SetToolTip( wxGetApp().getTip( "dirpause" ) );
  m_RestoreFx->SetLabel( wxGetApp().getMsg( "restorefx" ) );
  m_RestoreSpeed->SetLabel( wxGetApp().getMsg( "restorespeed" ) );
  m_Info4Throttle->SetLabel( wxGetApp().getMsg( "info4throttle" ) );
  m_labMaxLoad->SetLabel( wxGetApp().getMsg( "maxload" ) );
  m_labMinAccel->SetLabel( wxGetApp().getMsg( "minaccel" ) );
  m_labMaxAccel->SetLabel( wxGetApp().getMsg( "maxaccel" ) );
  m_AdjustAccel->SetLabel( wxGetApp().getMsg( "adjustaccel" ) );
  m_VelocityBox->SetLabel( wxGetApp().getMsg( "speed" ) );
  m_OptionsBox->SetLabel( wxGetApp().getMsg( "options" ) );
  m_AccelerationBox->SetLabel( wxGetApp().getMsg( "acceleration" ) );

  // Details
  m_Label_Blockwait->SetLabel( wxGetApp().getMsg( "blockwait" ) );
  m_labBlockWaitSec->SetLabel( wxGetApp().getMsg( "seconds" ) );
  m_labMaxWaitTime->SetLabel( wxGetApp().getMsg( "maxwaittime" ) );
  m_labMaxBlockWaitSec->SetLabel( wxGetApp().getMsg( "seconds" ) );
  m_labEventTimer->SetLabel( wxGetApp().getMsg( "eventtimer" ) );
  m_labEventTimerMS->SetLabel( wxGetApp().getMsg( "milliseconds" ) );
  m_labSwapTimer->SetLabel( wxGetApp().getMsg( "swaptimer" ) );
  m_labSwapTimerMS->SetLabel( wxGetApp().getMsg( "milliseconds" ) );
  m_labEvtCorrection->SetLabel( wxGetApp().getMsg( "evtcorrection" ) );
  m_labPriority->SetLabel( wxGetApp().getMsg( "priority" ) );
  m_Priority->SetToolTip( wxGetApp().getTip( "priority" ) );
  m_UseScheduleTime->SetLabel( wxGetApp().getMsg( "usescheduletime" ) );
  m_Commuter->SetLabel( wxGetApp().getMsg( "commuter" ) );
  m_EngineBox->SetLabel( wxGetApp().getMsg( "engine" ) );
  m_EngineBox->SetString( 0, wxGetApp().getMsg( "diesel" ) );
  m_EngineBox->SetString( 1, wxGetApp().getMsg( "steam" ) );
  m_EngineBox->SetString( 2, wxGetApp().getMsg( "electric" ) );
  m_EngineBox->SetString( 3, wxGetApp().getMsg( "automobile" ) );
  m_CargoBox->SetLabel( wxGetApp().getMsg( "cargo" ) );
  m_CargoBox->SetString( 0, wxGetApp().getMsg( "others" ) );
  m_CargoBox->SetString( 1, wxGetApp().getMsg( "goods" ) );
  m_CargoBox->SetString( 2, wxGetApp().getMsg( "local" ) );
  m_CargoBox->SetString( 3, wxGetApp().getMsg( "mixed" ) );
  m_CargoBox->SetString( 4, wxGetApp().getMsg( "cleaning" ) );
  m_CargoBox->SetString( 5, wxGetApp().getMsg( "ice" ) );
  m_CargoBox->SetString( 6, wxGetApp().getMsg( "post" ) );
  m_CargoBox->SetString( 7, wxGetApp().getMsg( "light" ) );
  m_CargoBox->SetString( 8, wxGetApp().getMsg( "lightgoods" ) );
  m_CargoBox->SetString( 9, wxGetApp().getMsg( "regional" ) );
  m_CargoBox->SetString( 10, wxGetApp().getMsg( "all" ) );
  m_CargoBox->SetString( 11, wxGetApp().getMsg( "shunting" ) );
  m_secondNextBlock->SetLabel( wxGetApp().getMsg( "secondnextblock" ) );
  m_ShortIn->SetLabel( wxGetApp().getMsg( "useshortinevent" ) );
  m_InAtPre2In->SetLabel( wxGetApp().getMsg( "inatpre2in" ) );
  m_UseManualRoutes->SetLabel( wxGetApp().getMsg( "usemanualroutes" ) );
  m_UseOwnWaittime->SetLabel( wxGetApp().getMsg( "useownwaittime" ) );
  m_Check2In->SetLabel( wxGetApp().getMsg( "check2in" ) );
  m_UseDepartDelay->SetLabel( wxGetApp().getMsg( "usedepartdelay" ) );
  m_FreeBlockOnEnter->SetLabel( wxGetApp().getMsg( "freeblockonenter" ) );
  m_ReduceSpeedAtEnter->SetLabel( wxGetApp().getMsg( "reducespeedatenter" ) );
  m_Era->SetLabel( wxGetApp().getMsg( "era" ) );
  m_labClass->SetLabel( wxGetApp().getMsg( "class" ) );
  m_V0onSwap->SetLabel( wxGetApp().getMsg( "v0onswap" ) );
  m_ResetPlacing->SetLabel( wxGetApp().getMsg( "resetplacing" ) );

  m_labStartupSchedule->SetLabel( wxGetApp().getMsg( "startupschedule" ) );
  m_StartupSchedule->Append( _T("") );
  iONode model = wxGetApp().getModel();
  iOList list = ListOp.inst();

  if( model != NULL ) {
    iONode sclist = wPlan.getsclist( model );
    if( sclist != NULL ) {
      int cnt = NodeOp.getChildCnt( sclist );
      for( int i = 0; i < cnt; i++ ) {
        iONode sc = NodeOp.getChild( sclist, i );
        ListOp.add(list, (obj)wSchedule.getid( sc ));
      }
    }

    ListOp.sort(list, &__sortStr);
    int cnt = ListOp.size( list );
    for( int i = 0; i < cnt; i++ ) {
      const char* id = (const char*)ListOp.get( list, i );
      m_StartupSchedule->Append( wxString(id,wxConvUTF8) );
    }

  }

  ListOp.base.del(list);

  m_labStartupTour->SetLabel( wxGetApp().getMsg( "startuptour" ) );
  m_StartupTour->Append( _T("") );
  list = ListOp.inst();

  if( model != NULL ) {
    iONode tourlist = wPlan.gettourlist( model );
    if( tourlist != NULL ) {
      int cnt = NodeOp.getChildCnt( tourlist );
      for( int i = 0; i < cnt; i++ ) {
        iONode tour = NodeOp.getChild( tourlist, i );
        ListOp.add(list, (obj)wTour.getid( tour ));
      }
    }

    ListOp.sort(list, &__sortStr);
    int cnt = ListOp.size( list );
    for( int i = 0; i < cnt; i++ ) {
      const char* id = (const char*)ListOp.get( list, i );
      m_StartupTour->Append( wxString(id,wxConvUTF8) );
    }

  }

  ListOp.base.del(list);

  // Functions
  m_labFnNr->SetLabel( _T("") );
  m_labFnDesc->SetLabel( wxGetApp().getMsg( "description" ) );
  m_labFnTimer->SetLabel( wxGetApp().getMsg( "timer" ) );
  m_labFnEvents->SetLabel( wxGetApp().getMsg( "events" ) );
  m_labFnAddr->SetLabel( wxGetApp().getMsg( "address" ) );
  m_labSound->SetLabel( wxGetApp().getMsg( "sound" ) );
  m_labIcon->SetLabel( wxGetApp().getMsg( "icon" ) );

  m_labF0Nr->SetLabel( _T("") );
  m_labF0Desc->SetLabel( wxGetApp().getMsg( "description" ) );
  m_labF0Timer->SetLabel( wxGetApp().getMsg( "timer" ) );
  m_labF0Events->SetLabel( wxGetApp().getMsg( "events" ) );
  m_labF0Icon->SetLabel( wxGetApp().getMsg( "icon" ) );

  // Consist
  m_labDetails->SetLabel( wxGetApp().getMsg( "details" ) );
  m_LightsOff->SetLabel( wxGetApp().getMsg( "lightsoff" ) );
  m_SyncFun->SetLabel( wxGetApp().getMsg( "sync" ) + _T(" ") + wxGetApp().getMsg( "functions" ) );
  m_SyncLights->SetLabel( wxGetApp().getMsg( "sync" ) + _T(" ") + wxGetApp().getMsg( "lights" ) );
  m_labConsistList->SetLabel( wxGetApp().getMsg( "members" ) );
  m_labConsistLocID->SetLabel( wxGetApp().getMsg( "locid" ) );
  m_AddConsistLoc->SetLabel( wxGetApp().getMsg( "add" ) );
  m_DeleteConsistLoc->SetLabel( wxGetApp().getMsg( "delete" ) );

  // CV's
  m_CVList->SetRowLabelSize(0);
  m_CVList->EnableEditing(false);
  m_CVList->EnableDragGridSize(false);
  m_CVList->SetSelectionMode(wxGrid::wxGridSelectRows);
  m_CVList->SetColLabelValue(0, _T("CV"));
  m_CVList->SetColLabelValue(1, wxGetApp().getMsg( "value" ));
  m_CVList->SetColLabelValue(2, wxGetApp().getMsg( "description" ));
  m_CVList->AutoSizeColumns();
  m_CVList->AutoSizeRows();
  m_CVDescModify->SetLabel( wxGetApp().getMsg( "modify" ) );
  m_labCVDesc->SetLabel( wxGetApp().getMsg( "description" ) );
  m_CVDescModify->Enable(false);
  m_CVDescription->Enable(false);

  // BBT
  m_BBTList2->InsertColumn(0, wxGetApp().getMsg( "fromblock" ), wxLIST_FORMAT_LEFT );
  m_BBTList2->InsertColumn(1, wxGetApp().getMsg( "block" ), wxLIST_FORMAT_LEFT );
  m_BBTList2->InsertColumn(2, wxGetApp().getMsg( "interval" ), wxLIST_FORMAT_RIGHT );
  m_BBTList2->InsertColumn(3, wxGetApp().getMsg( "steps" ), wxLIST_FORMAT_RIGHT );
  m_BBTList2->InsertColumn(4, wxGetApp().getMsg( "counter" ), wxLIST_FORMAT_RIGHT );
  m_BBTList2->InsertColumn(5, wxGetApp().getMsg( "fixed" ), wxLIST_FORMAT_CENTER );
  m_BBTList2->InsertColumn(6, wxGetApp().getMsg( "route" ), wxLIST_FORMAT_LEFT );
  m_BBTList2->InsertColumn(7, wxGetApp().getMsg( "speed" ), wxLIST_FORMAT_RIGHT );
  m_BBTList2->InsertColumn(8, wxT( "IN" ), wxLIST_FORMAT_CENTER );
  m_BBTList2->InsertColumn(9, wxGetApp().getMsg( "delay" ), wxLIST_FORMAT_RIGHT );

  m_labBBTSteps->SetLabel( wxGetApp().getMsg( "steps" ) );
  m_labBBTMaxDiff->SetLabel( wxGetApp().getMsg( "maxdiff" ) );
  m_labBBTCorrection->SetLabel( wxGetApp().getMsg( "correction" ) );
  m_labBBTStartInterval->SetLabel( wxGetApp().getMsg( "startinterval" ) );
  m_labBBTCalculation->SetLabel( wxGetApp().getMsg( "calc" ) );
  m_labBBTFromBlock->SetLabel( wxGetApp().getMsg( "fromblock" ) );
  m_labBBTBlock->SetLabel( wxGetApp().getMsg( "block" ) );
  m_labBBTInterval->SetLabel( wxGetApp().getMsg( "interval" ) );
  m_labBBTDelay->SetLabel( wxGetApp().getMsg( "delay" ) );
  m_BBTFixed->SetLabel( wxGetApp().getMsg( "fixed" ) );
  m_BBTGenerateIn->SetLabel( wxGetApp().getMsg( "generatein" ) );
  m_BBTModify->SetLabel( wxGetApp().getMsg( "modify" ) );
  m_BBTDelete->SetLabel( wxGetApp().getMsg( "delete" ) );
  m_BBTCopy->SetLabel( wxGetApp().getMsg( "copy" ) );
  m_BBTDeleteAll->SetLabel( wxGetApp().getMsg( "deleteall" ) );
  m_BBTAdd->SetLabel( wxGetApp().getMsg( "add" ) );
  m_BBTFixAll->SetLabel( wxGetApp().getMsg( "togglefix" ) );

  m_BBTKey->SetLabel( wxGetApp().getMsg( "use" ) );
  m_BBTKey->SetString( 0, wxGetApp().getMsg( "block" ) );
  m_BBTKey->SetString( 1, wxGetApp().getMsg( "fromblock" ) );
  m_BBTKey->SetString( 2, wxGetApp().getMsg( "route" ) );
  m_BBTKey->SetString( 3, wxGetApp().getMsg( "speed" ) );

  list = ListOp.inst();
  if( model != NULL ) {
    iONode blocklist = wPlan.getbklist( model );
    if( blocklist != NULL ) {
      int cnt = NodeOp.getChildCnt( blocklist );
      for( int i = 0; i < cnt; i++ ) {
        iONode block = NodeOp.getChild( blocklist, i );
        ListOp.add(list, (obj)wBlock.getid( block ));
      }
    }

    ListOp.sort(list, &__sortStr);
    int cnt = ListOp.size( list );
    for( int i = 0; i < cnt; i++ ) {
      const char* id = (const char*)ListOp.get( list, i );
      m_BBTFromBlock->Append( wxString(id,wxConvUTF8) );
      m_BBTBlock->Append( wxString(id,wxConvUTF8) );
      m_SBTBlock->Append( wxString(id,wxConvUTF8) );
    }
  }
  ListOp.base.del(list);

  list = ListOp.inst();
  if( model != NULL ) {
    iONode routelist = wPlan.getstlist( model );
    if( routelist != NULL ) {
      int cnt = NodeOp.getChildCnt( routelist );
      for( int i = 0; i < cnt; i++ ) {
        iONode route = NodeOp.getChild( routelist, i );
        ListOp.add(list, (obj)wRoute.getid( route ));
      }
    }

    ListOp.sort(list, &__sortStr);
    int cnt = ListOp.size( list );
    for( int i = 0; i < cnt; i++ ) {
      const char* id = (const char*)ListOp.get( list, i );
      m_BBTRoute->Append( wxString(id,wxConvUTF8) );
    }
  }
  ListOp.base.del(list);

  m_BBTImport->SetLabel( wxGetApp().getMsg( "import" ) + wxT("...") );
  m_BBTExport->SetLabel( wxGetApp().getMsg( "export" ) + wxT("...") );

  // SBT
  m_SBTDefaultBox->SetLabel( wxGetApp().getMsg( "default" ) );
  m_labDecelerate->SetLabel( wxGetApp().getMsg( "decelerate" ) );
  m_LabelV_step->SetLabel( wxGetApp().getMsg( "interval" ) );
  m_Regulated->SetLabel( wxGetApp().getMsg( "regulated" ) );
  m_Regulated->SetToolTip( wxGetApp().getTip( "regulated" ) );
  m_labSBTBlock->SetLabel( wxGetApp().getMsg( "block" ) );
  m_labSBTTrain->SetLabel( wxGetApp().getMsg( "train" ) );
  m_labSBTInterval->SetLabel( wxGetApp().getMsg( "interval" ) );
  m_labSBTDecelerate->SetLabel( wxGetApp().getMsg( "decelerate" ) );
  m_SBTModify->SetLabel( wxGetApp().getMsg( "modify" ) );
  m_SBTDelete->SetLabel( wxGetApp().getMsg( "delete" ) );
  m_SBTAdd->SetLabel( wxGetApp().getMsg( "add" ) );
  m_SBTList2->InsertColumn(0, wxGetApp().getMsg( "block" ), wxLIST_FORMAT_LEFT );
  m_SBTList2->InsertColumn(1, wxGetApp().getMsg( "train" ), wxLIST_FORMAT_LEFT );
  m_SBTList2->InsertColumn(2, wxGetApp().getMsg( "interval" ), wxLIST_FORMAT_LEFT );
  m_SBTList2->InsertColumn(3, wxGetApp().getMsg( "decelerate" ), wxLIST_FORMAT_LEFT );

  m_SBTTrain->Clear();
  m_SBTTrain->Append( wxT("") );

  list = ListOp.inst();
  if( model != NULL ) {
    iONode oplist = wPlan.getoperatorlist( model );
    if( oplist != NULL ) {
      int cnt = NodeOp.getChildCnt( oplist );
      for( int i = 0; i < cnt; i++ ) {
        iONode op = NodeOp.getChild( oplist, i );
        ListOp.add(list, (obj)wOperator.getid( op ));
      }
    }

    ListOp.sort(list, &__sortStr);
    int cnt = ListOp.size( list );
    for( int i = 0; i < cnt; i++ ) {
      const char* id = (const char*)ListOp.get( list, i );
      m_SBTTrain->Append( wxString(id,wxConvUTF8) );
    }
  }
  ListOp.base.del(list);

  // Buttons
  m_OK->SetLabel( wxGetApp().getMsg( "ok" ) );
  m_Cancel->SetLabel( wxGetApp().getMsg( "cancel" ) );
  m_Apply->SetLabel( wxGetApp().getMsg( "apply" ) );
  m_Apply->Enable( m_bSave );
}

static int __sortCV(obj* _a, obj* _b)
{
    iONode a = (iONode)*_a;
    iONode b = (iONode)*_b;
    int nrA = wCVByte.getnr( a );
    int nrB = wCVByte.getnr( b );
    if( nrA == nrB )
      return 0;
    if( nrA > nrB )
      return 1;
    return -1;
}


bool LocDialog::InitIndex() {
  TraceOp.trc( "locdlg", TRCLEVEL_INFO, __LINE__, 9999, "InitIndex" );

  m_ConsistLocID->Clear();

  iONode model = wxGetApp().getModel();
  if( model != NULL ) {
    iONode lclist = wPlan.getlclist( model );
    if( lclist != NULL ) {
      fillIndex(lclist);
      iOList list = ListOp.inst();
      int cnt = NodeOp.getChildCnt( lclist );
      for( int i = 0; i < cnt; i++ ) {
        iONode lc = NodeOp.getChild( lclist, i );
        const char* id = wLoc.getid( lc );
        if( id != NULL ) {
          ListOp.add(list, (obj)lc);
        }
      }

      ListOp.sort(list, &__sortID);
      cnt = ListOp.size( list );
      for( int i = 0; i < cnt; i++ ) {
        iONode lc = (iONode)ListOp.get( list, i );
        const char* id = wLoc.getid( lc );
        m_ConsistLocID->Append( wxString(id,wxConvUTF8) );
      }
      /* clean up the temp. list */
      ListOp.base.del(list);

      if( m_Props != NULL ) {
        setIDSelection(wLoc.getid( m_Props ));
        return true;
      }
      else {
        m_Props = setSelection(0);
      }
      initBBT();
    }

  }
  return false;
}


void LocDialog::initFunctions() {
  // flags for functions
  wxTextCtrl* l_fx[] = {m_f0,m_f1,m_f2,m_f3,m_f4};
  wxTextCtrl* l_sound[] = {NULL,m_Sound1,m_Sound2,m_Sound3,m_Sound4};
  wxTextCtrl* l_icon[] = {m_F0Icon,m_Icon_f1,m_Icon_f2,m_Icon_f3,m_Icon_f4};
  wxStaticText* l_labfx[] = {m_Label_f1,m_Label_f2,m_Label_f3,m_Label_f4};
  wxSpinCtrl* l_timer[] = {m_TimerF0,m_TimerF1,m_TimerF2,m_TimerF3,m_TimerF4};
  wxSpinCtrl* l_addr[] = {NULL,m_F1Addr,m_F2Addr,m_F3Addr,m_F4Addr};
  wxSpinCtrl* l_addrfn[] = {NULL,m_F1AddrFn,m_F2AddrFn,m_F3AddrFn,m_F4AddrFn};

  for( int i = 0; i < 5; i++ ) {
    l_fx[i]->SetValue( _T("") );
    l_timer[i]->SetValue(0);
    if( i > 0 ) {
      l_addr[i]->SetValue(0);
      l_addrfn[i]->SetValue(0);
      l_sound[i]->SetValue( _T("") );
      l_icon[i]->SetValue( _T("") );
    }
  }
  for( int i = 0; i < 4; i++ ) {
    l_labfx[i]->SetLabel( wxString::Format(_T("F%d"), i+1+m_iFunGroup*4 ) );
  }
  m_labFnGroup->SetLabel( wxString::Format(_T("%d"),1+m_iFunGroup ) );

  m_FunctionPanel->GetSizer()->Layout();

  // Init Functions
  TraceOp.trc( "locdlg", TRCLEVEL_INFO, __LINE__, 9999, "Init functions %s", wLoc.getid( m_Props ) );
  iONode fundef = wLoc.getfundef( m_Props );
  while( fundef != NULL ) {

    wxString fntxt( wFunDef.gettext( fundef ),wxConvUTF8 );
    wxString soundtxt( wFunDef.getsound( fundef ),wxConvUTF8 );
    wxString icontxt( wFunDef.geticon( fundef ),wxConvUTF8 );
    int funnr = wFunDef.getfn( fundef );
    TraceOp.trc( "locdlg", TRCLEVEL_INFO, __LINE__, 9999,
        "function[%d] name[%s]", funnr, wFunDef.gettext( fundef ) );

    if( funnr == 0 ) {
      l_fx[0]->SetValue( fntxt );
      l_timer[0]->SetValue( wFunDef.gettimer(fundef) );
      l_icon[0]->SetValue( icontxt );
    }
    else if( funnr == m_iFunGroup * 4 + 1 ) {
      l_fx[1]->SetValue( fntxt );
      l_sound[1]->SetValue( soundtxt );
      l_icon[1]->SetValue( icontxt );
      l_timer[1]->SetValue( wFunDef.gettimer(fundef) );
      l_addr[1]->SetValue( wFunDef.getaddr(fundef) );
      l_addrfn[1]->SetValue( wFunDef.getmappedfn(fundef) );
    }
    else if( funnr == m_iFunGroup * 4 + 2 ) {
      l_fx[2]->SetValue( fntxt );
      l_sound[2]->SetValue( soundtxt );
      l_icon[2]->SetValue( icontxt );
      l_timer[2]->SetValue( wFunDef.gettimer(fundef) );
      l_addr[2]->SetValue( wFunDef.getaddr(fundef) );
      l_addrfn[2]->SetValue( wFunDef.getmappedfn(fundef) );
    }
    else if( funnr == m_iFunGroup * 4 + 3 ) {
      l_fx[3]->SetValue( fntxt );
      l_sound[3]->SetValue( soundtxt );
      l_icon[3]->SetValue( icontxt );
      l_timer[3]->SetValue( wFunDef.gettimer(fundef) );
      l_addr[3]->SetValue( wFunDef.getaddr(fundef) );
      l_addrfn[3]->SetValue( wFunDef.getmappedfn(fundef) );
    }
    else if( funnr == m_iFunGroup * 4 + 4 ) {
      l_fx[4]->SetValue( fntxt );
      l_sound[4]->SetValue( soundtxt );
      l_icon[4]->SetValue( icontxt );
      l_timer[4]->SetValue( wFunDef.gettimer(fundef) );
      l_addr[4]->SetValue( wFunDef.getaddr(fundef) );
      l_addrfn[4]->SetValue( wFunDef.getmappedfn(fundef) );
    }

    fundef = wLoc.nextfundef( m_Props, fundef );
  }

}


void LocDialog::InitValues() {
  if( m_Props == NULL ) {
    return;
  }

  char* title = StrOp.fmt( "%s %s", (const char*)wxGetApp().getMsg("loc").mb_str(wxConvUTF8), wLoc.getid( m_Props ) );
  SetTitle( wxString(title,wxConvUTF8) );
  StrOp.free( title );

  TraceOp.trc( "locdlg", TRCLEVEL_INFO, __LINE__, 9999, "InitValues %s", wLoc.getid( m_Props ) );
  // Init General
  if( wLoc.getimage( m_Props ) != NULL && StrOp.len(wLoc.getimage(m_Props)) > 0 ) {
    bool isSupported = true;
    wxBitmapType bmptype = wxBITMAP_TYPE_XPM;
    if( StrOp.endsWithi( wLoc.getimage( m_Props ), ".gif" ) )
      bmptype = wxBITMAP_TYPE_GIF;
    else if( StrOp.endsWithi( wLoc.getimage( m_Props ), ".png" ) )
      bmptype = wxBITMAP_TYPE_PNG;
    else {
      TraceOp.trc( "locdlg", TRCLEVEL_WARNING, __LINE__, 9999, "unsupported image format %s", wLoc.getimage( m_Props ) );
      isSupported = false;
    }

    const char* imagepath = wGui.getimagepath(wxGetApp().getIni());
    const char* imagename = FileOp.ripPath( wLoc.getimage( m_Props ) );
    char* pixpath;


    pixpath = StrOp.fmt( "%s%c%s", imagepath, SystemOp.getFileSeparator(), imagename );

    if( !wGui.isfsutf8(wxGetApp().getIni()) ) {
      char* tmp = pixpath;
      pixpath = SystemOp.utf2latin(pixpath);
      StrOp.free(tmp);
    }

    if( isSupported && imagename != NULL && StrOp.len(imagename) > 0 && FileOp.exist(pixpath)) {
      TraceOp.trc( "locdlg", TRCLEVEL_INFO, __LINE__, 9999, "picture [%s]", pixpath );
      if( wGui.isfsutf8(wxGetApp().getIni()) )
        m_LocImage->SetBitmapLabel( wxBitmap(wxString(pixpath,wxConvUTF8), bmptype) );
      else
        m_LocImage->SetBitmapLabel( wxBitmap(wxString::From8BitData((const char*)pixpath), bmptype) );
    }
    else {
      TraceOp.trc( "locdlg", TRCLEVEL_WARNING, __LINE__, 9999, "picture [%s] not found", pixpath );
      if( wGui.isgrayicons(wxGetApp().getIni()) )
        m_LocImage->SetBitmapLabel( *_img_noimg );
      else
        m_LocImage->SetBitmapLabel( wxBitmap(nopict_xpm) );
    }
    m_LocImage->SetToolTip(wxString(wLoc.getdesc( m_Props ),wxConvUTF8));

    StrOp.free(pixpath);


    //m_LocImage->SetBitmapLabel( wxBitmap(wxString(wLoc.getimage( m_Props ),wxConvUTF8), bmptype) );
    //m_LocImageIndex->SetBitmapLabel( wxBitmap(wxString(wLoc.getimage( m_Props ),wxConvUTF8), bmptype) );
  }
  else {
    if( wGui.isgrayicons(wxGetApp().getIni()) )
      m_LocImage->SetBitmapLabel( *_img_noimg );
    else
      m_LocImage->SetBitmapLabel( wxBitmap(nopict_xpm) );
    //m_LocImageIndex->SetBitmapLabel( wxBitmap(nopict_xpm) );
  }
  m_LocImage->Refresh();
  //m_LocImageIndex->Refresh();

  m_Train->SetValue( wxString(wLoc.gettrain( m_Props ),wxConvUTF8) );
  m_ImageNr->SetValue(wLoc.getimagenr( m_Props ));
  m_Show->SetValue(wLoc.isshow( m_Props ));
  m_LocManually->SetValue(wLoc.ismanually( m_Props ));
  m_UseShortID->SetValue(wLoc.isuseshortid( m_Props ));
  m_ID->SetValue( wxString(wLoc.getid( m_Props ),wxConvUTF8) );
  m_ShortID->SetValue( wxString(wLoc.getshortid( m_Props ),wxConvUTF8) );
  m_ThrottleNr->SetValue( wLoc.getthrottlenr( m_Props ) );
  m_Roadname->SetValue( wxString(wLoc.getroadname( m_Props ),wxConvUTF8) );
  m_Number->SetValue( wxString(wLoc.getnumber( m_Props ),wxConvUTF8) );
  m_Description->SetValue( wxString(wLoc.getdesc( m_Props ),wxConvUTF8) );
  m_DecoderType->SetValue( wxString(wLoc.getdectype( m_Props ),wxConvUTF8) );
  m_Documentation->SetValue( wxString(wLoc.getdocu( m_Props ),wxConvUTF8) );
  m_ImageName->SetValue( wxString(wLoc.getimage( m_Props ),wxConvUTF8) );
  m_Remark->SetValue( wxString(wLoc.getremark( m_Props ),wxConvUTF8) );
  m_Length->SetValue( wLoc.getlen( m_Props ) );
  m_NrCars->SetValue( wLoc.getnrcars( m_Props ) );
  m_CatNr->SetValue( wxString(wLoc.getcatnr( m_Props ),wxConvUTF8) );
  m_Purchased->SetValue( wxString(wLoc.getpurchased( m_Props ),wxConvUTF8) );
  m_Value->SetValue( wxString(wLoc.getvalue( m_Props ),wxConvUTF8) );
  int runtime = wLoc.getruntime( m_Props );
  char* str = StrOp.fmt( "%d:%02d.%02d",
      runtime/3600,
      (runtime%3600)/60,
      (runtime%3600)%60 );
  m_RunTime->SetValue( wxString(str,wxConvUTF8) ); StrOp.free( str );

  int mtime = wLoc.getmtime( m_Props );
  int deltatime = runtime-mtime;
  str = StrOp.fmt( "%d:%02d.%02d (%d:%02d.%02d)", mtime/3600, (mtime%3600)/60, (mtime%3600)%60 ,
      deltatime/3600, (deltatime%3600)/60, (deltatime%3600)%60 );
  m_MTime->SetValue( wxString(str,wxConvUTF8) ); StrOp.free( str );
  m_MInt->SetValue( wLoc.getmint( m_Props ) );

  if( wLoc.getmdate( m_Props ) > 0 ) {
    long ltime = wLoc.getmdate( m_Props );
    struct tm* ltm = localtime( &ltime );
    str = StrOp.fmt( "%d-%d-%d", ltm->tm_mday, ltm->tm_mon+1, ltm->tm_year + 1900);
    m_MDate->SetValue( wxString(str,wxConvUTF8) ); StrOp.free( str );
  }
  else {
    m_MDate->SetValue( wxT("") );
  }

  if( wLoc.getmint( m_Props ) > 0 ) {
    if(wLoc.getruntime( m_Props ) - wLoc.getmtime( m_Props ) > wLoc.getmint( m_Props ) * 3600 ) {
      m_Serviced->SetBackgroundColour( Base::getRed() );
    }
    else {
      m_Serviced->SetBackgroundColour( Base::getGreen() );
    }
  }

  m_StartupSchedule->SetStringSelection( wLoc.getstartupscid( m_Props ) == NULL ?
                                _T(""):wxString(wLoc.getstartupscid( m_Props ),wxConvUTF8)  );

  m_StartupTour->SetStringSelection( wLoc.getstartuptourid( m_Props ) == NULL ?
                                _T(""):wxString(wLoc.getstartuptourid( m_Props ),wxConvUTF8)  );

  m_Ident->SetValue( wxString(wLoc.getidentifier( m_Props ),wxConvUTF8) );
  m_Era->SetSelection( wLoc.getera( m_Props ) );

  // Init Interface
  str = StrOp.fmt( "%d", wLoc.getbus( m_Props ) );
  m_Bus->SetValue( wxString(str,wxConvUTF8) ); StrOp.free( str );
  str = StrOp.fmt( "%d", wLoc.getaddr( m_Props ) );
  m_Address->SetValue( wxString(str,wxConvUTF8) ); StrOp.free( str );
  str = StrOp.fmt( "%d", wLoc.getsecaddr( m_Props ) );
  m_SecAddress->SetValue( wxString(str,wxConvUTF8) ); StrOp.free( str );
  m_IID->SetValue( wxString(wLoc.getiid( m_Props ),wxConvUTF8) );

  if( StrOp.equals( wLoc.prot_P, wLoc.getprot( m_Props ) ) )
    m_Protocol->SetSelection( 0 );
  else if( StrOp.equals( wLoc.prot_M, wLoc.getprot( m_Props ) ) )
    m_Protocol->SetSelection( 1 );
  else if( StrOp.equals( wLoc.prot_N, wLoc.getprot( m_Props ) ) )
    m_Protocol->SetSelection( 2 );
  else if( StrOp.equals( wLoc.prot_L, wLoc.getprot( m_Props ) ) )
    m_Protocol->SetSelection( 3 );
  else if( StrOp.equals( wLoc.prot_A, wLoc.getprot( m_Props ) ) )
    m_Protocol->SetSelection( 4 );
  else if( StrOp.equals( wLoc.prot_C, wLoc.getprot( m_Props ) ) )
    m_Protocol->SetSelection( 5 );
  else if( StrOp.equals( wLoc.prot_S, wLoc.getprot( m_Props ) ) )
    m_Protocol->SetSelection( 6 );
  else if( StrOp.equals( wLoc.prot_X, wLoc.getprot( m_Props ) ) )
    m_Protocol->SetSelection( 7 );

  str = StrOp.fmt( "%d", wLoc.getprotver( m_Props ) );
  m_ProtVersion->SetValue( wxString(str,wxConvUTF8) ); StrOp.free( str );
  str = StrOp.fmt( "%d", wLoc.getfncnt( m_Props ) );
  m_FunCnt->SetValue( wxString(str,wxConvUTF8) ); StrOp.free( str );
  str = StrOp.fmt( "%d", wLoc.getspcnt( m_Props ) );
  m_SpeedSteps->SetValue( wxString(str,wxConvUTF8) ); StrOp.free( str );
  str = StrOp.fmt( "%d", wLoc.getsecspcnt( m_Props ) );
  m_SecSpeedSteps->SetValue( wxString(str,wxConvUTF8) ); StrOp.free( str );

  str = StrOp.fmt( "%d", wLoc.getV_min( m_Props ) );
  m_V_min->SetValue( wxString(str,wxConvUTF8) ); StrOp.free( str );
  str = StrOp.fmt( "%d", wLoc.getV_mid( m_Props ) );
  m_V_mid->SetValue( wxString(str,wxConvUTF8) ); StrOp.free( str );
  str = StrOp.fmt( "%d", wLoc.getV_cru( m_Props ) );
  m_V_cru->SetValue( wxString(str,wxConvUTF8) ); StrOp.free( str );
  str = StrOp.fmt( "%d", wLoc.getV_max( m_Props ) );
  m_V_max->SetValue( wxString(str,wxConvUTF8) ); StrOp.free( str );
  str = StrOp.fmt( "%d", wLoc.getV_maxsec( m_Props ) );
  m_VmaxSec->SetValue( wxString(str,wxConvUTF8) ); StrOp.free( str );
  str = StrOp.fmt( "%d", wLoc.getV_Rmin( m_Props ) );
  m_V_Rmin->SetValue( wxString(str,wxConvUTF8) ); StrOp.free( str );
  str = StrOp.fmt( "%d", wLoc.getV_Rmid( m_Props ) );
  m_V_Rmid->SetValue( wxString(str,wxConvUTF8) ); StrOp.free( str );
  str = StrOp.fmt( "%d", wLoc.getV_Rcru( m_Props ) );
  m_V_Rcru->SetValue( wxString(str,wxConvUTF8) ); StrOp.free( str );
  str = StrOp.fmt( "%d", wLoc.getV_Rmax( m_Props ) );
  m_V_Rmax->SetValue( wxString(str,wxConvUTF8) ); StrOp.free( str );
  str = StrOp.fmt( "%d", wLoc.getmass( m_Props ) );
  m_Mass->SetValue( wxString(str,wxConvUTF8) ); StrOp.free( str );

  m_V_mode_percent->SetValue( StrOp.equals( wLoc.V_mode_percent, wLoc.getV_mode( m_Props ) ) ? true:false );

  m_Placing->SetValue( wLoc.isplacing( m_Props ) ? true:false );
  m_Regulated->SetValue( wLoc.isregulated( m_Props ) ? true:false );
  m_RestoreFx->SetValue( wLoc.isrestorefx( m_Props ) ? true:false );
  m_RestoreFxAlways->SetValue( wLoc.isrestorefxalways( m_Props ) ? true:false );
  m_RestoreSpeed->SetValue( wLoc.isrestorespeed( m_Props ) ? true:false );
  m_Info4Throttle->SetValue( wLoc.isinfo4throttle( m_Props ) ? true:false );

  m_Accel->SetValue( wLoc.getV_step( m_Props ) );
  if( wLoc.isregulated( m_Props ) || wLoc.getspcnt( m_Props ) > 14 ) {
    //m_Accel->Enable( false );
  }

  str = StrOp.fmt( "%d", wLoc.getdirpause( m_Props ) );
  m_DirPause->SetValue( wxString(str,wxConvUTF8) ); StrOp.free( str );

  m_AdjustAccel->SetValue(wLoc.isadjustaccel(m_Props) ? true:false);
  m_MaxLoad->SetValue(wLoc.getmaxload(m_Props));
  m_MinAccel->SetValue(wLoc.getaccelmin(m_Props));
  m_MaxAccel->SetValue(wLoc.getaccelmax(m_Props));
  m_Decelerate->SetValue(wLoc.getdecelerate(m_Props));

  // Init Details
  str = StrOp.fmt( "%d", wLoc.getblockwaittime( m_Props ) );
  m_Blockwait->SetValue( wxString(str,wxConvUTF8) ); StrOp.free( str );
  str = StrOp.fmt( "%d", wLoc.getmaxwaittime( m_Props ) );
  m_MaxWaitTime->SetValue( wxString(str,wxConvUTF8) ); StrOp.free( str );
  str = StrOp.fmt( "%d", wLoc.getevttimer( m_Props ) );
  m_EventTimer->SetValue( wxString(str,wxConvUTF8) ); StrOp.free( str );
  m_SwapTimer->SetValue( wLoc.getswaptimer( m_Props ) );
  m_EvtCorrection->SetValue( wLoc.getent2incorr( m_Props ) );
  m_Priority->SetValue( wLoc.getpriority( m_Props ) );
  m_UseScheduleTime->SetValue( wLoc.isusescheduletime( m_Props ) ? true:false );
  m_Commuter->SetValue( wLoc.iscommuter( m_Props ) ? true:false );
  m_ShortIn->SetValue( wLoc.isshortin( m_Props ) ? true:false );
  m_InAtPre2In->SetValue( wLoc.isinatpre2in( m_Props ) ? true:false );
  m_UseManualRoutes->SetValue( wLoc.isusemanualroutes( m_Props ) ? true:false );
  m_UseOwnWaittime->SetValue( wLoc.isuseownwaittime( m_Props ) ? true:false );
  m_UseDepartDelay->SetValue( wLoc.isusedepartdelay( m_Props ) ? true:false );
  m_FreeBlockOnEnter->SetValue( wLoc.isfreeblockonenter( m_Props ) ? true:false );
  m_ReduceSpeedAtEnter->SetValue( wLoc.isreducespeedatenter( m_Props ) ? true:false );
  m_Check2In->SetValue( wLoc.ischeck2in( m_Props ) );
  m_V0onSwap->SetValue( wLoc.isv0onswap( m_Props ) ? true:false );
  m_ResetPlacing->SetValue( wLoc.isresetplacing( m_Props ) ? true:false );

  int engine = 0;
  if( StrOp.equals( wLoc.engine_diesel, wLoc.getengine( m_Props ) ) )
    engine = 0;
  else if( StrOp.equals( wLoc.engine_steam, wLoc.getengine( m_Props ) ) )
    engine = 1;
  else if( StrOp.equals( wLoc.engine_electric, wLoc.getengine( m_Props ) ) )
    engine = 2;
  else if( StrOp.equals( wLoc.engine_automobile, wLoc.getengine( m_Props ) ) )
    engine = 3;
  m_EngineBox->SetSelection( engine );
  int cargo = 0;
  if( StrOp.equals( wLoc.cargo_none, wLoc.getcargo( m_Props ) ) )
    cargo = 0;
  else if( StrOp.equals( wLoc.cargo_goods, wLoc.getcargo( m_Props ) ) )
    cargo = 1;
  else if( StrOp.equals( wLoc.cargo_person, wLoc.getcargo( m_Props ) ) )
    cargo = 2;
  else if( StrOp.equals( wLoc.cargo_mixed, wLoc.getcargo( m_Props ) ) )
    cargo = 3;
  else if( StrOp.equals( wLoc.cargo_cleaning, wLoc.getcargo( m_Props ) ) )
    cargo = 4;
  else if( StrOp.equals( wLoc.cargo_ice, wLoc.getcargo( m_Props ) ) )
    cargo = 5;
  else if( StrOp.equals( wLoc.cargo_post, wLoc.getcargo( m_Props ) ) )
    cargo = 6;
  else if( StrOp.equals( wLoc.cargo_light, wLoc.getcargo( m_Props ) ) )
    cargo = 7;
  else if( StrOp.equals( wLoc.cargo_lightgoods, wLoc.getcargo( m_Props ) ) )
    cargo = 8;
  else if( StrOp.equals( wLoc.cargo_regional, wLoc.getcargo( m_Props ) ) )
    cargo = 9;
  else if( StrOp.equals( wLoc.cargo_all, wLoc.getcargo( m_Props ) ) )
    cargo = 10;
  else if( StrOp.equals( wLoc.cargo_shunting, wLoc.getcargo( m_Props ) ) )
    cargo = 11;
  m_CargoBox->SetSelection( cargo );
  m_secondNextBlock->SetValue( wLoc.issecondnextblock( m_Props ) );

  m_Class->SetValue(wxString(wLoc.getclass(m_Props),wxConvUTF8));


  // functions
  initFunctions();


  // Consist
  wxCheckBox* funsync[] = {m_FSync1 ,m_FSync2 ,m_FSync3 ,m_FSync4 ,m_FSync5 ,m_FSync6 ,m_FSync7 ,m_FSync8 ,m_FSync9 ,m_FSync10,m_FSync11,m_FSync12,m_FSync13,m_FSync14,
                           m_FSync15,m_FSync16,m_FSync17,m_FSync18,m_FSync19,m_FSync20,m_FSync21,m_FSync22,m_FSync23,m_FSync24,m_FSync25,m_FSync26,m_FSync27,m_FSync28};
  int fmap = wLoc.getconsist_syncfunmap( m_Props );

  for( int i = 0; i < 28; i++ ) {
    funsync[i]->SetValue( (fmap & (1 << i)) ? true:false );
  }

  m_LightsOff->SetValue( wLoc.isconsist_lightsoff( m_Props ) ? true:false );
  m_SyncLights->Enable(!m_LightsOff->IsChecked());
  m_SyncFun->SetValue( wLoc.isconsist_syncfun( m_Props ) ? true:false );
  m_SyncLights->SetValue( wLoc.isconsist_synclights( m_Props ) ? true:false );
  m_ConsistList->Clear();
  iOStrTok  consist = StrTokOp.inst( wLoc.getconsist ( m_Props ), ',' );
  while( StrTokOp.hasMoreTokens( consist ) ) {
    const char* tok = StrTokOp.nextToken( consist );
    m_ConsistList->Append( wxString(tok,wxConvUTF8) );
  };
  StrTokOp.base.del( consist );

  // CV's
  TraceOp.trc( "locdlg", TRCLEVEL_INFO, __LINE__, 9999, "CV list...");
  iOList list = ListOp.inst();
  iONode cv = wLoc.getcvbyte( m_Props );
  while( cv != NULL ) {
    if( wCVByte.getnr( cv ) > 0 && wCVByte.getnr( cv ) <= 1024 ) {
      ListOp.add(list, (obj)cv);
    }
    cv = wLoc.nextcvbyte( m_Props, cv );
  };

  TraceOp.trc( "locdlg", TRCLEVEL_INFO, __LINE__, 9999, "CVs...");
  if( m_CVList->GetNumberRows() > 0 )
    m_CVList->DeleteRows( 0, m_CVList->GetNumberRows() );
  ListOp.sort(list, &__sortCV);
  int cnt = ListOp.size( list );
  for( int i = 0; i < cnt && cnt < 1024; i++ ) {
    iONode cv = (iONode)ListOp.get( list, i );
    char* cvnr = StrOp.fmt( "%d", wCVByte.getnr( cv ) );
    char* cvval = StrOp.fmt( "%d", wCVByte.getvalue( cv ) );
    const char* cvdesc = wCVByte.getdesc(cv);
    m_CVNodes[wCVByte.getnr( cv )] = cv;
    m_CVList->AppendRows();
    int row = m_CVList->GetNumberRows()-1;
    m_CVList->SetCellValue(row, 0, wxString(cvnr,wxConvUTF8) );
    m_CVList->SetCellValue(row, 1, wxString(cvval,wxConvUTF8) );
    if( cvdesc != NULL && StrOp.len(cvdesc) > 0 )
      m_CVList->SetCellValue(row, 2, wxString(cvdesc,wxConvUTF8) );
    else
      m_CVList->SetCellValue(row, 2, wxString(m_CVDesc[wCVByte.getnr( cv )&0xff],wxConvUTF8) );
    m_CVList->SetReadOnly( row, 0, true );
    m_CVList->SetReadOnly( row, 1, true );
    m_CVList->SetReadOnly( row, 2, true );
    StrOp.free( cvnr );
    StrOp.free( cvval );
  }
  /* clean up the temp. list */
  ListOp.base.del(list);


  m_CVList->AutoSizeColumns();

  m_BBT->SetValue( wLoc.isusebbt( m_Props ) ? true:false );
  m_BBTSteps->SetValue( wLoc.getbbtsteps( m_Props ) );
  m_BBTStartInterval->SetValue( wLoc.getbbtstartinterval( m_Props ) );
  m_BBTMaxDiff->SetValue( wLoc.getbbtmaxdiff( m_Props ) );
  m_BBTCorrection->SetValue( wLoc.getbbtcorrection( m_Props ) );
  m_BBTKey->SetSelection(wLoc.getbbtkey( m_Props ));

  initBBT();
  initSBT();

  m_BBTDelete->Enable(false);
  m_BBTCopy->Enable(false);
  m_BBTDeleteAll->Enable( m_BBTList2->GetItemCount() > 0 ? true:false);

}


bool LocDialog::evaluateFunctions() {
  // evaluate Functions
  wxTextCtrl* l_fx[] = {m_f0,m_f1,m_f2,m_f3,m_f4};
  wxTextCtrl* l_sound[] = {NULL,m_Sound1,m_Sound2,m_Sound3,m_Sound4};
  wxTextCtrl* l_icon[] = {m_F0Icon,m_Icon_f1,m_Icon_f2,m_Icon_f3,m_Icon_f4};
  wxSpinCtrl* l_timer[] = {m_TimerF0,m_TimerF1,m_TimerF2,m_TimerF3,m_TimerF4};
  wxSpinCtrl* l_addr[] = {NULL,m_F1Addr,m_F2Addr,m_F3Addr,m_F4Addr};
  wxSpinCtrl* l_addrfn[] = {NULL,m_F1AddrFn,m_F2AddrFn,m_F3AddrFn,m_F4AddrFn};
  int function[] = {0,0,0,0,0};

  if( l_fx[0]->GetValue().Length() > 0 )
    function[0] = 1;

  for( int i = 1; i < 5; i++ ) {
    if( l_fx[i]->GetValue().Length() > 0 )
      function[i] = 1;
  }

  TraceOp.trc( "locdlg", TRCLEVEL_INFO, __LINE__, 9999, "evaluate function group %d", m_iFunGroup + 1);


  iONode fundef = wLoc.getfundef( m_Props );
  while( fundef != NULL ) {
    wxString fntxt( wFunDef.gettext( fundef ),wxConvUTF8 );
    int fnr = wFunDef.getfn( fundef );

    if( fnr == 0 ) {
      TraceOp.trc( "locdlg", TRCLEVEL_INFO, __LINE__, 9999, "modify function  %d", fnr );
      wFunDef.settext( fundef, m_f0->GetValue().mb_str(wxConvUTF8)  );
      wFunDef.settimer( fundef, m_TimerF0->GetValue() );
      wFunDef.seticon( fundef, m_F0Icon->GetValue().mb_str(wxConvUTF8)  );
      function[0] = 0;
    }
    else if( fnr >= 1 + m_iFunGroup*4 && fnr <= 5 + m_iFunGroup*4 ) {
      TraceOp.trc( "locdlg", TRCLEVEL_INFO, __LINE__, 9999, "modify function  %d", fnr );
      switch( fnr - m_iFunGroup*4 ) {
        case 1 :
          wFunDef.settext( fundef, m_f1->GetValue().mb_str(wxConvUTF8)  );
          wFunDef.setsound( fundef, m_Sound1->GetValue().mb_str(wxConvUTF8)  );
          wFunDef.seticon( fundef, m_Icon_f1->GetValue().mb_str(wxConvUTF8)  );
          wFunDef.settimer( fundef, m_TimerF1->GetValue() );
          wFunDef.setaddr( fundef, m_F1Addr->GetValue() );
          wFunDef.setmappedfn( fundef, m_F1AddrFn->GetValue() );
          function[fnr - m_iFunGroup*4] = 0;
          break;
        case 2 :
          wFunDef.settext( fundef, m_f2->GetValue().mb_str(wxConvUTF8)  );
          wFunDef.setsound( fundef, m_Sound2->GetValue().mb_str(wxConvUTF8)  );
          wFunDef.seticon( fundef, m_Icon_f2->GetValue().mb_str(wxConvUTF8)  );
          wFunDef.settimer( fundef, m_TimerF2->GetValue() );
          wFunDef.setaddr( fundef, m_F2Addr->GetValue() );
          wFunDef.setmappedfn( fundef, m_F2AddrFn->GetValue() );
          function[fnr - m_iFunGroup*4] = 0;
          break;
        case 3 :
          wFunDef.settext( fundef, m_f3->GetValue().mb_str(wxConvUTF8)  );
          wFunDef.setsound( fundef, m_Sound3->GetValue().mb_str(wxConvUTF8)  );
          wFunDef.seticon( fundef, m_Icon_f3->GetValue().mb_str(wxConvUTF8)  );
          wFunDef.settimer( fundef, m_TimerF3->GetValue() );
          wFunDef.setaddr( fundef, m_F3Addr->GetValue() );
          wFunDef.setmappedfn( fundef, m_F3AddrFn->GetValue() );
          function[fnr - m_iFunGroup*4] = 0;
          break;
        case 4 :
          wFunDef.settext( fundef, m_f4->GetValue().mb_str(wxConvUTF8)  );
          wFunDef.setsound( fundef, m_Sound4->GetValue().mb_str(wxConvUTF8)  );
          wFunDef.seticon( fundef, m_Icon_f4->GetValue().mb_str(wxConvUTF8)  );
          wFunDef.settimer( fundef, m_TimerF4->GetValue() );
          wFunDef.setaddr( fundef, m_F4Addr->GetValue() );
          wFunDef.setmappedfn( fundef, m_F4AddrFn->GetValue() );
          function[fnr - m_iFunGroup*4] = 0;
          break;
      }
    }
    fundef = wLoc.nextfundef( m_Props, fundef );
  }

  if( function[0] == 1 ) {
    fundef = NodeOp.inst( wFunDef.name(), m_Props, ELEMENT_NODE );
    NodeOp.addChild( m_Props, fundef );
    wFunDef.setfn( fundef, 0 );
    wFunDef.settext( fundef, l_fx[0]->GetValue().mb_str(wxConvUTF8) );
    wFunDef.settimer( fundef, m_TimerF0->GetValue() );
  }
  for( int i = 1; i < 5; i++ ) {
    if( function[i] == 1 ) {
      int f = i + m_iFunGroup*4;
      TraceOp.trc( "locdlg", TRCLEVEL_INFO, __LINE__, 9999, "adding function  %d", f );
      fundef = NodeOp.inst( wFunDef.name(), m_Props, ELEMENT_NODE );
      NodeOp.addChild( m_Props, fundef );
      wFunDef.setfn( fundef, f );
      wFunDef.settext( fundef, l_fx[i]->GetValue().mb_str(wxConvUTF8) );
      wFunDef.setsound( fundef, l_sound[i]->GetValue().mb_str(wxConvUTF8) );
      wFunDef.seticon( fundef, l_icon[i]->GetValue().mb_str(wxConvUTF8) );
      wFunDef.settimer( fundef, l_timer[i]->GetValue() );
      wFunDef.setaddr( fundef, l_addr[i]->GetValue() );
      wFunDef.setmappedfn( fundef, l_addrfn[i]->GetValue() );
    }
  }
  return true;
}

bool LocDialog::Evaluate() {
  if( m_Props == NULL )
    return false;

  TraceOp.trc( "locdlg", TRCLEVEL_INFO, __LINE__, 9999, "Evaluate %s", wLoc.getid( m_Props ) );

  if( m_ID->GetValue().Len() == 0 ) {
    wxMessageDialog( this, wxGetApp().getMsg("invalidid"), _T("Rocrail"), wxOK | wxICON_ERROR ).ShowModal();
    m_ID->SetValue( wxString(wLoc.getid( m_Props ),wxConvUTF8) );
    return false;
  }

  if( wItem.isgenerated(m_Props) && !m_GuestImport->IsChecked() ) {
    // Modifying a guest loco; Remove generated flag to prevent removing it at shutdown.
    wItem.setgenerated(m_Props, False);
  }

  // evaluate General
  wItem.setprev_id( m_Props, wItem.getid(m_Props) );
  wLoc.setid( m_Props, m_ID->GetValue().mb_str(wxConvUTF8) );
  wLoc.setshortid( m_Props, m_ShortID->GetValue().mb_str(wxConvUTF8) );
  wLoc.setroadname( m_Props, m_Roadname->GetValue().mb_str(wxConvUTF8) );
  wLoc.setnumber( m_Props, m_Number->GetValue().mb_str(wxConvUTF8) );
  wLoc.setdesc( m_Props, m_Description->GetValue().mb_str(wxConvUTF8) );
  wLoc.setdectype( m_Props, m_DecoderType->GetValue().mb_str(wxConvUTF8) );
  wLoc.setdocu( m_Props, m_Documentation->GetValue().mb_str(wxConvUTF8) );
  wLoc.setimage( m_Props, m_ImageName->GetValue().mb_str(wxConvUTF8) );
  wLoc.setimagenr( m_Props, m_ImageNr->GetValue() );
  wLoc.setremark( m_Props, m_Remark->GetValue().mb_str(wxConvUTF8) );
  wLoc.setlen( m_Props, m_Length->GetValue() );
  wLoc.setnrcars( m_Props, m_NrCars->GetValue() );
  wLoc.setcatnr( m_Props, m_CatNr->GetValue().mb_str(wxConvUTF8) );
  wLoc.setpurchased( m_Props, m_Purchased->GetValue().mb_str(wxConvUTF8) );
  wLoc.setvalue( m_Props, m_Value->GetValue().mb_str(wxConvUTF8) );
  wLoc.setidentifier( m_Props, m_Ident->GetValue().mb_str(wxConvUTF8) );
  wLoc.setshow( m_Props, m_Show->IsChecked()?True:False);
  wLoc.setuseshortid( m_Props, m_UseShortID->IsChecked()?True:False);
  wLoc.setmint( m_Props, m_MInt->GetValue() );
  wLoc.setthrottlenr( m_Props, m_ThrottleNr->GetValue() );
  wLoc.setmanually( m_Props, m_LocManually->IsChecked()?True:False);

  // evaluate Interface
  int val = atoi( m_Bus->GetValue().mb_str(wxConvUTF8) );
  wLoc.setbus( m_Props, val );
  val = atoi( m_Address->GetValue().mb_str(wxConvUTF8) );
  wLoc.setaddr( m_Props, val );
  val = atoi( m_SecAddress->GetValue().mb_str(wxConvUTF8) );
  wLoc.setsecaddr( m_Props, val );
  wLoc.setiid( m_Props, m_IID->GetValue().mb_str(wxConvUTF8) );

  if( m_Protocol->GetSelection() == 0 )
    wLoc.setprot( m_Props, wLoc.prot_P );
  else if( m_Protocol->GetSelection() == 1 )
    wLoc.setprot( m_Props, wLoc.prot_M );
  else if( m_Protocol->GetSelection() == 2 )
    wLoc.setprot( m_Props, wLoc.prot_N );
  else if( m_Protocol->GetSelection() == 3 )
    wLoc.setprot( m_Props, wLoc.prot_L );
  else if( m_Protocol->GetSelection() == 4 )
    wLoc.setprot( m_Props, wLoc.prot_A );
  else if( m_Protocol->GetSelection() == 5 )
    wLoc.setprot( m_Props, wLoc.prot_C );
  else if( m_Protocol->GetSelection() == 6 )
    wLoc.setprot( m_Props, wLoc.prot_S );
  else if( m_Protocol->GetSelection() == 7 )
    wLoc.setprot( m_Props, wLoc.prot_X );

  val = atoi( m_ProtVersion->GetValue().mb_str(wxConvUTF8) );
  wLoc.setprotver( m_Props, val );
  val = atoi( m_SpeedSteps->GetValue().mb_str(wxConvUTF8) );
  wLoc.setspcnt( m_Props, val );
  val = atoi( m_SecSpeedSteps->GetValue().mb_str(wxConvUTF8) );
  wLoc.setsecspcnt( m_Props, val );
  val = atoi( m_ProtVersion->GetValue().mb_str(wxConvUTF8) );
  wLoc.setprotver( m_Props, val );

  val = atoi( m_FunCnt->GetValue().mb_str(wxConvUTF8) );
  wLoc.setfncnt( m_Props, val );

  val = atoi( m_V_min->GetValue().mb_str(wxConvUTF8) );
  wLoc.setV_min( m_Props, val );
  val = atoi( m_V_mid->GetValue().mb_str(wxConvUTF8) );
  wLoc.setV_mid( m_Props, val );
  val = atoi( m_V_cru->GetValue().mb_str(wxConvUTF8) );
  wLoc.setV_cru( m_Props, val );
  val = atoi( m_V_max->GetValue().mb_str(wxConvUTF8) );
  wLoc.setV_max( m_Props, val );
  val = atoi( m_VmaxSec->GetValue().mb_str(wxConvUTF8) );
  wLoc.setV_maxsec( m_Props, val );
  val = atoi( m_V_Rmin->GetValue().mb_str(wxConvUTF8) );
  wLoc.setV_Rmin( m_Props, val );
  val = atoi( m_V_Rmid->GetValue().mb_str(wxConvUTF8) );
  wLoc.setV_Rmid( m_Props, val );
  val = atoi( m_V_Rcru->GetValue().mb_str(wxConvUTF8) );
  wLoc.setV_Rcru( m_Props, val );
  val = atoi( m_V_Rmax->GetValue().mb_str(wxConvUTF8) );
  wLoc.setV_Rmax( m_Props, val );
  wLoc.setV_step( m_Props, m_Accel->GetValue() );
  val = atoi( m_Mass->GetValue().mb_str(wxConvUTF8) );
  wLoc.setmass( m_Props, val );
  wLoc.setV_mode( m_Props, m_V_mode_percent->GetValue() ? wLoc.V_mode_percent:wLoc.V_mode_kmh );
  wLoc.setplacing( m_Props, m_Placing->GetValue() ? True:False );
  wLoc.setregulated( m_Props, m_Regulated->GetValue() ? True:False );
  wLoc.setrestorefx( m_Props, m_RestoreFx->GetValue() ? True:False );
  wLoc.setrestorefxalways( m_Props, m_RestoreFxAlways->GetValue() ? True:False );
  wLoc.setrestorespeed( m_Props, m_RestoreSpeed->GetValue() ? True:False );
  wLoc.setinfo4throttle( m_Props, m_Info4Throttle->GetValue() ? True:False );

  val = atoi( m_DirPause->GetValue().mb_str(wxConvUTF8) );
  wLoc.setdirpause( m_Props, val );

  wLoc.setadjustaccel(m_Props, m_AdjustAccel->IsChecked() ? True:False);
  wLoc.setmaxload(m_Props, m_MaxLoad->GetValue());
  wLoc.setaccelmin(m_Props, m_MinAccel->GetValue());
  wLoc.setaccelmax(m_Props, m_MaxAccel->GetValue());
  wLoc.setdecelerate(m_Props, m_Decelerate->GetValue());


  // evaluate Details
  val = atoi( m_Blockwait->GetValue().mb_str(wxConvUTF8) );
  wLoc.setblockwaittime( m_Props, val );
  val = atoi( m_MaxWaitTime->GetValue().mb_str(wxConvUTF8) );
  wLoc.setmaxwaittime( m_Props, val );
  val = atoi( m_EventTimer->GetValue().mb_str(wxConvUTF8) );
  wLoc.setevttimer( m_Props, val );
  wLoc.setswaptimer( m_Props, m_SwapTimer->GetValue() );
  wLoc.setent2incorr( m_Props, m_EvtCorrection->GetValue() );
  wLoc.setpriority( m_Props, m_Priority->GetValue() );
  wLoc.setusescheduletime( m_Props, m_UseScheduleTime->GetValue() ? True:False );
  wLoc.setcommuter( m_Props, m_Commuter->GetValue() ? True:False );
  wLoc.setshortin( m_Props, m_ShortIn->GetValue() ? True:False );
  wLoc.setinatpre2in( m_Props, m_InAtPre2In->GetValue() ? True:False );
  wLoc.setusemanualroutes( m_Props, m_UseManualRoutes->GetValue() ? True:False );
  wLoc.setuseownwaittime( m_Props, m_UseOwnWaittime->GetValue() ? True:False );
  wLoc.setstartupscid( m_Props, m_StartupSchedule->GetStringSelection().mb_str(wxConvUTF8) );
  wLoc.setstartuptourid( m_Props, m_StartupTour->GetStringSelection().mb_str(wxConvUTF8) );
  wLoc.setcheck2in( m_Props, m_Check2In->IsChecked() ? True:False );
  wLoc.setusedepartdelay( m_Props, m_UseDepartDelay->IsChecked() ? True:False );
  wLoc.setfreeblockonenter( m_Props, m_FreeBlockOnEnter->IsChecked() ? True:False );
  wLoc.setreducespeedatenter( m_Props, m_ReduceSpeedAtEnter->IsChecked() ? True:False );
  wLoc.setv0onswap( m_Props, m_V0onSwap->IsChecked() ? True:False );
  wLoc.setresetplacing( m_Props, m_ResetPlacing->IsChecked() ? True:False );

  int engine = m_EngineBox->GetSelection();
  if( engine == 0 )
    wLoc.setengine( m_Props, wLoc.engine_diesel );
  else if( engine == 1 )
    wLoc.setengine( m_Props, wLoc.engine_steam );
  else if( engine == 2 )
    wLoc.setengine( m_Props, wLoc.engine_electric );
  else if( engine == 3 )
    wLoc.setengine( m_Props, wLoc.engine_automobile );

  int cargo = m_CargoBox->GetSelection();
  if( cargo == 0 )
    wLoc.setcargo( m_Props, wLoc.cargo_none );
  else if( cargo == 1 )
    wLoc.setcargo( m_Props, wLoc.cargo_goods );
  else if( cargo == 2 )
    wLoc.setcargo( m_Props, wLoc.cargo_person );
  else if( cargo == 3 )
    wLoc.setcargo( m_Props, wLoc.cargo_mixed );
  else if( cargo == 4 )
    wLoc.setcargo( m_Props, wLoc.cargo_cleaning );
  else if( cargo == 5 )
    wLoc.setcargo( m_Props, wLoc.cargo_ice );
  else if( cargo == 6 )
    wLoc.setcargo( m_Props, wLoc.cargo_post );
  else if( cargo == 7 )
    wLoc.setcargo( m_Props, wLoc.cargo_light );
  else if( cargo == 8 )
    wLoc.setcargo( m_Props, wLoc.cargo_lightgoods );
  else if( cargo == 9 )
    wLoc.setcargo( m_Props, wLoc.cargo_regional );
  else if( cargo == 10 )
    wLoc.setcargo( m_Props, wLoc.cargo_all );
  else if( cargo == 11 )
    wLoc.setcargo( m_Props, wLoc.cargo_shunting );

  wLoc.setsecondnextblock( m_Props, m_secondNextBlock->IsChecked() ? True:False );
  wLoc.setera( m_Props, m_Era->GetSelection() );
  wLoc.setclass(m_Props, m_Class->GetValue().mb_str(wxConvUTF8) );

  // Functions
  evaluateFunctions();

  // Consist
  wxCheckBox* funsync[] = {m_FSync1 ,m_FSync2 ,m_FSync3 ,m_FSync4 ,m_FSync5 ,m_FSync6 ,m_FSync7 ,m_FSync8 ,m_FSync9 ,m_FSync10,m_FSync11,m_FSync12,m_FSync13,m_FSync14,
                           m_FSync15,m_FSync16,m_FSync17,m_FSync18,m_FSync19,m_FSync20,m_FSync21,m_FSync22,m_FSync23,m_FSync24,m_FSync25,m_FSync26,m_FSync27,m_FSync28};
  int fmap = 0;

  for( int i = 0; i < 28; i++ ) {
    if( funsync[i]->IsChecked() )
      fmap |= (1 << i);
  }
  wLoc.setconsist_syncfunmap( m_Props, fmap );


  wLoc.setconsist_lightsoff( m_Props, m_LightsOff->GetValue() ? True:False );
  wLoc.setconsist_syncfun( m_Props, m_SyncFun->GetValue() ? True:False );
  wLoc.setconsist_synclights( m_Props, m_SyncLights->GetValue() ? True:False );
  int locos = m_ConsistList->GetCount();
  char* consist = StrOp.cat( NULL, "" );
  for( int i = 0; i < locos; i++ ) {
    if( i > 0 )
      consist = StrOp.cat( consist, "," );
    consist = StrOp.cat( consist, m_ConsistList->GetString(i).mb_str(wxConvUTF8) );
  }
  wLoc.setconsist( m_Props, consist);
  TraceOp.trc( "locdlg", TRCLEVEL_INFO, __LINE__, 9999, "Consist [%s]", consist );
  StrOp.free(consist);

  wLoc.setusebbt( m_Props, m_BBT->GetValue() ? True:False );
  wLoc.setbbtsteps( m_Props, m_BBTSteps->GetValue() );
  wLoc.setbbtstartinterval( m_Props, m_BBTStartInterval->GetValue() );
  wLoc.setbbtmaxdiff( m_Props, m_BBTMaxDiff->GetValue() );
  wLoc.setbbtcorrection( m_Props, m_BBTCorrection->GetValue() );
  wLoc.setbbtkey( m_Props, m_BBTKey->GetSelection() );

  return true;
}


/*!
 * LocDialog creator
 */

bool LocDialog::Create( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
////@begin LocDialog member initialisation
    m_Props = NULL;
    m_LocImage = NULL;
    m_Notebook = NULL;
    m_IndexPanel = NULL;
    m_List2 = NULL;
    m_New = NULL;
    m_Delete = NULL;
    m_Doc = NULL;
    m_Copy = NULL;
    m_ImportLocos = NULL;
    m_GuestImport = NULL;
    m_RestoreFx = NULL;
    m_RestoreFxAlways = NULL;
    m_RestoreSpeed = NULL;
    m_LocManually = NULL;
    m_Show = NULL;
    m_labTrain = NULL;
    m_Train = NULL;
    m_General_Panel = NULL;
    m_GeneralSizer = NULL;
    m_label_ID = NULL;
    m_ID = NULL;
    m_labShortID = NULL;
    m_ShortID = NULL;
    m_labIdent = NULL;
    m_Ident = NULL;
    m_labRoadname = NULL;
    m_Roadname = NULL;
    m_labNumber = NULL;
    m_Number = NULL;
    m_Label_Description = NULL;
    m_Description = NULL;
    m_labImageName = NULL;
    m_ImageName = NULL;
    m_SelectLocoImag = NULL;
    m_labImageNr = NULL;
    m_ImageNr = NULL;
    m_Label_Length = NULL;
    m_Length = NULL;
    m_labNrCars = NULL;
    m_NrCars = NULL;
    m_Label_CatalogNr = NULL;
    m_CatNr = NULL;
    m_labDecType = NULL;
    m_DecoderType = NULL;
    m_labDocumentation = NULL;
    m_Documentation = NULL;
    m_ShowDoc = NULL;
    m_Label_Purchased = NULL;
    m_Purchased = NULL;
    m_labValue = NULL;
    m_Value = NULL;
    m_Label_Runtime = NULL;
    m_RunTime = NULL;
    m_labMTime = NULL;
    m_MTime = NULL;
    m_labMDate = NULL;
    m_MDate = NULL;
    m_UseShortID = NULL;
    m_labThrottleNr = NULL;
    m_ThrottleNr = NULL;
    m_Serviced = NULL;
    m_labMInt = NULL;
    m_MInt = NULL;
    m_labRemark = NULL;
    m_Remark = NULL;
    m_Actions = NULL;
    m_Interface_Panel = NULL;
    m_Label_IID = NULL;
    m_IID = NULL;
    m_Label_Bus = NULL;
    m_Bus = NULL;
    m_Label_Address = NULL;
    m_Address = NULL;
    m_SecAddress = NULL;
    m_Label_Protocol = NULL;
    m_Protocol = NULL;
    m_LabelProtVersion = NULL;
    m_ProtVersion = NULL;
    m_LabelSpeedSteps = NULL;
    m_SpeedSteps = NULL;
    m_SecSpeedSteps = NULL;
    m_LabelFunCnt = NULL;
    m_FunCnt = NULL;
    m_VelocityBox = NULL;
    m_Label_V_min = NULL;
    m_V_min = NULL;
    m_Label_V_Rmin = NULL;
    m_V_Rmin = NULL;
    m_Label_V_mid = NULL;
    m_V_mid = NULL;
    m_Label_V_Rmid = NULL;
    m_V_Rmid = NULL;
    m_labVcru = NULL;
    m_V_cru = NULL;
    m_labVRcru = NULL;
    m_V_Rcru = NULL;
    m_Label_V_max = NULL;
    m_V_max = NULL;
    m_VmaxSec = NULL;
    m_Label_V_Rmax = NULL;
    m_V_Rmax = NULL;
    m_OptionsBox = NULL;
    m_Label_Mass = NULL;
    m_Mass = NULL;
    m_labDirPause = NULL;
    m_DirPause = NULL;
    m_LabelV_mode = NULL;
    m_V_mode_percent = NULL;
    m_LabelPlacing = NULL;
    m_Placing = NULL;
    m_Info4Throttle = NULL;
    m_AccelerationBox = NULL;
    m_AdjustAccel = NULL;
    m_labMaxLoad = NULL;
    m_MaxLoad = NULL;
    m_labMinAccel = NULL;
    m_MinAccel = NULL;
    m_labMaxAccel = NULL;
    m_MaxAccel = NULL;
    m_DetailsPanel = NULL;
    m_Label_Blockwait = NULL;
    m_Blockwait = NULL;
    m_labBlockWaitSec = NULL;
    m_labMaxWaitTime = NULL;
    m_MaxWaitTime = NULL;
    m_labMaxBlockWaitSec = NULL;
    m_labEventTimer = NULL;
    m_EventTimer = NULL;
    m_labEventTimerMS = NULL;
    m_labEvtCorrection = NULL;
    m_EvtCorrection = NULL;
    m_labTimerCorrectionPercent = NULL;
    m_labPriority = NULL;
    m_Priority = NULL;
    m_labSwapTimer = NULL;
    m_SwapTimer = NULL;
    m_labSwapTimerMS = NULL;
    m_labStartupTour = NULL;
    m_StartupTour = NULL;
    m_labStartupSchedule = NULL;
    m_StartupSchedule = NULL;
    m_CargoBox = NULL;
    m_Commuter = NULL;
    m_UseScheduleTime = NULL;
    m_secondNextBlock = NULL;
    m_ShortIn = NULL;
    m_InAtPre2In = NULL;
    m_UseManualRoutes = NULL;
    m_UseOwnWaittime = NULL;
    m_Check2In = NULL;
    m_UseDepartDelay = NULL;
    m_FreeBlockOnEnter = NULL;
    m_V0onSwap = NULL;
    m_BBT = NULL;
    m_ReduceSpeedAtEnter = NULL;
    m_ResetPlacing = NULL;
    m_EngineBox = NULL;
    m_labClass = NULL;
    m_Class = NULL;
    m_Era = NULL;
    m_FunctionPanel = NULL;
    m_labF0Nr = NULL;
    m_labF0Desc = NULL;
    m_labF0Timer = NULL;
    m_labF0Events = NULL;
    m_labF0Icon = NULL;
    m_Label_f0 = NULL;
    m_f0 = NULL;
    m_TimerF0 = NULL;
    m_Button_f0 = NULL;
    m_F0Icon = NULL;
    m_labFnGroup = NULL;
    m_FunctionGroup = NULL;
    m_labFnNr = NULL;
    m_labFnDesc = NULL;
    m_labFnTimer = NULL;
    m_labFnEvents = NULL;
    m_labSound = NULL;
    m_labIcon = NULL;
    m_labFnAddr = NULL;
    m_labAddrFn = NULL;
    m_Label_f1 = NULL;
    m_f1 = NULL;
    m_TimerF1 = NULL;
    m_Button_f1 = NULL;
    m_Sound1 = NULL;
    m_Icon_f1 = NULL;
    m_F1Addr = NULL;
    m_F1AddrFn = NULL;
    m_Label_f2 = NULL;
    m_f2 = NULL;
    m_TimerF2 = NULL;
    m_Button_f2 = NULL;
    m_Sound2 = NULL;
    m_Icon_f2 = NULL;
    m_F2Addr = NULL;
    m_F2AddrFn = NULL;
    m_Label_f3 = NULL;
    m_f3 = NULL;
    m_TimerF3 = NULL;
    m_Button_f3 = NULL;
    m_Sound3 = NULL;
    m_Icon_f3 = NULL;
    m_F3Addr = NULL;
    m_F3AddrFn = NULL;
    m_Label_f4 = NULL;
    m_f4 = NULL;
    m_TimerF4 = NULL;
    m_Button_f4 = NULL;
    m_Sound4 = NULL;
    m_Icon_f4 = NULL;
    m_F4Addr = NULL;
    m_F4AddrFn = NULL;
    m_ConsistsPanel = NULL;
    m_labDetails = NULL;
    m_LightsOff = NULL;
    m_SyncLights = NULL;
    m_SyncFun = NULL;
    m_FSync1 = NULL;
    m_FSync2 = NULL;
    m_FSync3 = NULL;
    m_FSync4 = NULL;
    m_FSync5 = NULL;
    m_FSync6 = NULL;
    m_FSync7 = NULL;
    m_FSync8 = NULL;
    m_FSync9 = NULL;
    m_FSync10 = NULL;
    m_FSync11 = NULL;
    m_FSync12 = NULL;
    m_FSync13 = NULL;
    m_FSync14 = NULL;
    m_FSync15 = NULL;
    m_FSync16 = NULL;
    m_FSync17 = NULL;
    m_FSync18 = NULL;
    m_FSync19 = NULL;
    m_FSync20 = NULL;
    m_FSync21 = NULL;
    m_FSync22 = NULL;
    m_FSync23 = NULL;
    m_FSync24 = NULL;
    m_FSync25 = NULL;
    m_FSync26 = NULL;
    m_FSync27 = NULL;
    m_FSync28 = NULL;
    m_labConsistList = NULL;
    m_ConsistList = NULL;
    m_labConsistLocID = NULL;
    m_ConsistLocID = NULL;
    m_AddConsistLoc = NULL;
    m_DeleteConsistLoc = NULL;
    m_CVPanel = NULL;
    m_CVList = NULL;
    m_labCVDesc = NULL;
    m_CVDescription = NULL;
    m_CVDescModify = NULL;
    m_BBTPanel = NULL;
    m_labBBTSteps = NULL;
    m_BBTSteps = NULL;
    m_labBBTStepsDummy = NULL;
    m_labBBTStartInterval = NULL;
    m_BBTStartInterval = NULL;
    m_labBBTMaxDiff = NULL;
    m_BBTMaxDiff = NULL;
    m_labBBT10ms = NULL;
    m_labBBTCorrection = NULL;
    m_BBTCorrection = NULL;
    m_labBBTPer = NULL;
    m_BBTKey = NULL;
    m_labBBTCalculation = NULL;
    m_BBTList2 = NULL;
    m_labBBTFromBlock = NULL;
    m_BBTFromBlock = NULL;
    m_labBBTBlock = NULL;
    m_BBTBlock = NULL;
    m_labBBTInterval = NULL;
    m_BBTInterval = NULL;
    m_labBBTRoute = NULL;
    m_BBTRoute = NULL;
    m_labBBTSpeed = NULL;
    m_BBTSpeed = NULL;
    m_labBBTDelay = NULL;
    m_BBTDelay = NULL;
    m_BBTAdd = NULL;
    m_BBTDelete = NULL;
    m_BBTCopy = NULL;
    m_BBTDeleteAll = NULL;
    m_BBTModify = NULL;
    m_BBTExport = NULL;
    m_BBTImport = NULL;
    m_BBTFixAll = NULL;
    m_BBTFixed = NULL;
    m_BBTGenerateIn = NULL;
    m_SBTPanel = NULL;
    m_SBTDefaultBox = NULL;
    m_labDecelerate = NULL;
    m_Decelerate = NULL;
    m_LabelV_step = NULL;
    m_Accel = NULL;
    m_Regulated = NULL;
    m_SBTList2 = NULL;
    m_labSBTBlock = NULL;
    m_SBTBlock = NULL;
    m_labSBTTrain = NULL;
    m_SBTTrain = NULL;
    m_labSBTInterval = NULL;
    m_SBTInterval = NULL;
    m_labSBTDecelerate = NULL;
    m_SBTDecelerate = NULL;
    m_SBTAdd = NULL;
    m_SBTDelete = NULL;
    m_SBTModify = NULL;
    m_Cancel = NULL;
    m_Apply = NULL;
    m_OK = NULL;
////@end LocDialog member initialisation

////@begin LocDialog creation
    SetExtraStyle(wxWS_EX_BLOCK_EVENTS);
    wxDialog::Create( parent, id, caption, pos, size, style );

    CreateControls();
    if (GetSizer())
    {
        GetSizer()->SetSizeHints(this);
    }
    Centre();
////@end LocDialog creation
    return true;
}

/*!
 * Control creation for LocDialog
 */

void LocDialog::CreateControls()
{
////@begin LocDialog content construction
    LocDialog* itemDialog1 = this;

    wxBoxSizer* itemBoxSizer2 = new wxBoxSizer(wxVERTICAL);
    itemDialog1->SetSizer(itemBoxSizer2);

    m_LocImage = new wxBitmapButton( itemDialog1, ID_BITMAPBUTTON, wxNullBitmap, wxDefaultPosition, wxSize(-1, 88), wxBU_AUTODRAW );
    itemBoxSizer2->Add(m_LocImage, 0, wxGROW|wxALL, 5);

    m_Notebook = new wxNotebook( itemDialog1, ID_NOTEBOOK, wxDefaultPosition, wxDefaultSize, m_TabAlign );

    m_IndexPanel = new wxPanel( m_Notebook, ID_PANEL_INDEX, wxDefaultPosition, wxDefaultSize, wxSUNKEN_BORDER|wxTAB_TRAVERSAL );
    wxBoxSizer* itemBoxSizer6 = new wxBoxSizer(wxVERTICAL);
    m_IndexPanel->SetSizer(itemBoxSizer6);

    m_List2 = new wxListCtrl( m_IndexPanel, ID_LISTCTRLINDEX_LC, wxDefaultPosition, wxSize(100, 100), wxLC_REPORT|wxLC_SINGLE_SEL|wxLC_HRULES );
    itemBoxSizer6->Add(m_List2, 1, wxGROW|wxALL, 5);

    wxBoxSizer* itemBoxSizer8 = new wxBoxSizer(wxHORIZONTAL);
    itemBoxSizer6->Add(itemBoxSizer8, 0, wxGROW|wxALL, 5);
    wxFlexGridSizer* itemFlexGridSizer9 = new wxFlexGridSizer(0, 3, 0, 0);
    itemBoxSizer8->Add(itemFlexGridSizer9, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);
    m_New = new wxButton( m_IndexPanel, ID_BUTTON_LOC_NEW, _("New"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer9->Add(m_New, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_Delete = new wxButton( m_IndexPanel, ID_BUTTON_DELETE, _("Delete"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer9->Add(m_Delete, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_Doc = new wxButton( m_IndexPanel, ID_BUTTON_LOCO_DOC, _("Doc"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer9->Add(m_Doc, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_Copy = new wxButton( m_IndexPanel, ID_LOC_COPY, _("Copy"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer9->Add(m_Copy, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_ImportLocos = new wxButton( m_IndexPanel, ID_BUTTON_IMPORTLOCOS, _("Import..."), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer9->Add(m_ImportLocos, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_GuestImport = new wxCheckBox( m_IndexPanel, wxID_ANY, _("Guest"), wxDefaultPosition, wxDefaultSize, 0 );
    m_GuestImport->SetValue(false);
    itemFlexGridSizer9->Add(m_GuestImport, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticLine* itemStaticLine16 = new wxStaticLine( m_IndexPanel, wxID_STATIC, wxDefaultPosition, wxDefaultSize, wxLI_VERTICAL );
    itemBoxSizer8->Add(itemStaticLine16, 0, wxGROW|wxALL, 5);

    wxFlexGridSizer* itemFlexGridSizer17 = new wxFlexGridSizer(0, 2, 0, 0);
    itemBoxSizer8->Add(itemFlexGridSizer17, 0, wxGROW|wxALL, 5);
    wxFlexGridSizer* itemFlexGridSizer18 = new wxFlexGridSizer(0, 2, 0, 0);
    itemFlexGridSizer17->Add(itemFlexGridSizer18, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    m_RestoreFx = new wxCheckBox( m_IndexPanel, ID_LOC_ONRESTOREFX, _("Restore functions"), wxDefaultPosition, wxDefaultSize, 0 );
    m_RestoreFx->SetValue(false);
    itemFlexGridSizer18->Add(m_RestoreFx, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxLEFT, 5);

    m_RestoreFxAlways = new wxCheckBox( m_IndexPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
    m_RestoreFxAlways->SetValue(false);
    itemFlexGridSizer18->Add(m_RestoreFxAlways, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxRIGHT, 5);

    m_RestoreSpeed = new wxCheckBox( m_IndexPanel, ID_LOC_RESTORESPEED, _("Restore speed"), wxDefaultPosition, wxDefaultSize, 0 );
    m_RestoreSpeed->SetValue(false);
    itemFlexGridSizer17->Add(m_RestoreSpeed, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxLEFT|wxRIGHT, 5);

    m_LocManually = new wxCheckBox( m_IndexPanel, ID_LOC_MANUALLY, _("Manually"), wxDefaultPosition, wxDefaultSize, 0 );
    m_LocManually->SetValue(false);
    itemFlexGridSizer17->Add(m_LocManually, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_Show = new wxCheckBox( m_IndexPanel, ID_LOC_SHOW, _("Show"), wxDefaultPosition, wxDefaultSize, 0 );
    m_Show->SetValue(false);
    itemFlexGridSizer17->Add(m_Show, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticLine* itemStaticLine24 = new wxStaticLine( m_IndexPanel, wxID_STATIC, wxDefaultPosition, wxDefaultSize, wxLI_VERTICAL );
    itemBoxSizer8->Add(itemStaticLine24, 0, wxGROW|wxALL, 5);

    wxFlexGridSizer* itemFlexGridSizer25 = new wxFlexGridSizer(0, 1, 0, 0);
    itemBoxSizer8->Add(itemFlexGridSizer25, 1, wxALIGN_TOP, 5);
    m_labTrain = new wxStaticText( m_IndexPanel, wxID_ANY, _("Train"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer25->Add(m_labTrain, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_BOTTOM|wxLEFT|wxRIGHT|wxTOP, 5);

    m_Train = new wxTextCtrl( m_IndexPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY|wxTE_CENTRE );
    m_Train->Enable(false);
    itemFlexGridSizer25->Add(m_Train, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    itemFlexGridSizer25->AddGrowableCol(0);

    m_Notebook->AddPage(m_IndexPanel, _("Index"));

    m_General_Panel = new wxPanel( m_Notebook, ID_PANEL_GENERAL, wxDefaultPosition, wxDefaultSize, wxSUNKEN_BORDER|wxTAB_TRAVERSAL );
    wxBoxSizer* itemBoxSizer29 = new wxBoxSizer(wxHORIZONTAL);
    m_General_Panel->SetSizer(itemBoxSizer29);

    m_GeneralSizer = new wxBoxSizer(wxVERTICAL);
    itemBoxSizer29->Add(m_GeneralSizer, 1, wxALIGN_TOP|wxALL, 0);
    wxFlexGridSizer* itemFlexGridSizer31 = new wxFlexGridSizer(0, 2, 0, 0);
    m_GeneralSizer->Add(itemFlexGridSizer31, 1, wxGROW|wxALL, 5);
    m_label_ID = new wxStaticText( m_General_Panel, ID_ABOX_ID, _("ID @"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer31->Add(m_label_ID, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL|wxADJUST_MINSIZE, 5);

    wxFlexGridSizer* itemFlexGridSizer33 = new wxFlexGridSizer(0, 4, 0, 0);
    itemFlexGridSizer31->Add(itemFlexGridSizer33, 0, wxGROW|wxALIGN_CENTER_VERTICAL, 5);
    m_ID = new wxTextCtrl( m_General_Panel, ID_TEXTCTRL_ID, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer33->Add(m_ID, 1, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_labShortID = new wxStaticText( m_General_Panel, wxID_ANY, _("Short ID:"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer33->Add(m_labShortID, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_ShortID = new wxTextCtrl( m_General_Panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer33->Add(m_ShortID, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxRIGHT|wxTOP|wxBOTTOM, 5);

    itemFlexGridSizer33->AddGrowableCol(0);

    m_labIdent = new wxStaticText( m_General_Panel, ID_ABOX_IDENT, _("Identifier @"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer31->Add(m_labIdent, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxLEFT|wxRIGHT|wxBOTTOM|wxADJUST_MINSIZE, 5);

    m_Ident = new wxTextCtrl( m_General_Panel, wxID_ANY, _("0"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer31->Add(m_Ident, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxLEFT|wxRIGHT|wxBOTTOM, 5);

    m_labRoadname = new wxStaticText( m_General_Panel, ID_ABOX_ROADNAME, _("Roadname @"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer31->Add(m_labRoadname, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxLEFT|wxRIGHT|wxBOTTOM, 5);

    m_Roadname = new wxTextCtrl( m_General_Panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer31->Add(m_Roadname, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxLEFT|wxRIGHT|wxBOTTOM, 5);

    m_labNumber = new wxStaticText( m_General_Panel, wxID_ANY, _("Number"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer31->Add(m_labNumber, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxLEFT|wxRIGHT|wxBOTTOM, 5);

    m_Number = new wxTextCtrl( m_General_Panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer31->Add(m_Number, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxLEFT|wxRIGHT|wxBOTTOM, 5);

    m_Label_Description = new wxStaticText( m_General_Panel, wxID_STATIC_DESCRIPTION, _("Description:"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer31->Add(m_Label_Description, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxLEFT|wxRIGHT|wxBOTTOM|wxADJUST_MINSIZE, 5);

    m_Description = new wxTextCtrl( m_General_Panel, ID_TEXTCTRL_DESCRIPTION, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer31->Add(m_Description, 1, wxGROW|wxALIGN_CENTER_VERTICAL|wxLEFT|wxRIGHT, 5);

    m_labImageName = new wxStaticText( m_General_Panel, wxID_ANY, _("Image:"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer31->Add(m_labImageName, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxFlexGridSizer* itemFlexGridSizer46 = new wxFlexGridSizer(0, 4, 0, 0);
    itemFlexGridSizer31->Add(itemFlexGridSizer46, 0, wxGROW|wxALIGN_CENTER_VERTICAL, 5);
    m_ImageName = new wxTextCtrl( m_General_Panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer46->Add(m_ImageName, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_SelectLocoImag = new wxButton( m_General_Panel, ID_SELECT_LOCOIMAGE, _("..."), wxDefaultPosition, wxSize(30, -1), 0 );
    itemFlexGridSizer46->Add(m_SelectLocoImag, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_labImageNr = new wxStaticText( m_General_Panel, wxID_ANY, _("Image Nr."), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer46->Add(m_labImageNr, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_ImageNr = new wxSpinCtrl( m_General_Panel, wxID_ANY, wxT("0"), wxDefaultPosition, wxSize(60, -1), wxSP_ARROW_KEYS, 0, 256, 0 );
    itemFlexGridSizer46->Add(m_ImageNr, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxRIGHT|wxTOP|wxBOTTOM, 5);

    itemFlexGridSizer46->AddGrowableCol(0);

    m_Label_Length = new wxStaticText( m_General_Panel, wxID_STATIC_LENGTH, _("Length:"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer31->Add(m_Label_Length, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxLEFT|wxRIGHT|wxBOTTOM|wxADJUST_MINSIZE, 5);

    wxFlexGridSizer* itemFlexGridSizer52 = new wxFlexGridSizer(0, 3, 0, 0);
    itemFlexGridSizer31->Add(itemFlexGridSizer52, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    m_Length = new wxSpinCtrl( m_General_Panel, wxID_ANY, wxT("0"), wxDefaultPosition, wxSize(100, -1), wxSP_ARROW_KEYS, 0, 10000, 0 );
    itemFlexGridSizer52->Add(m_Length, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxLEFT|wxRIGHT|wxBOTTOM, 5);

    m_labNrCars = new wxStaticText( m_General_Panel, wxID_ANY, _("Nr. Cars"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer52->Add(m_labNrCars, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxLEFT|wxRIGHT|wxBOTTOM, 5);

    m_NrCars = new wxSpinCtrl( m_General_Panel, wxID_ANY, wxT("0"), wxDefaultPosition, wxSize(60, -1), wxSP_ARROW_KEYS, 0, 999, 0 );
    itemFlexGridSizer52->Add(m_NrCars, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxRIGHT|wxBOTTOM, 5);

    itemFlexGridSizer52->AddGrowableCol(0);

    m_Label_CatalogNr = new wxStaticText( m_General_Panel, ID_ABOX_CATNR, _("CatalogNr @"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer31->Add(m_Label_CatalogNr, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxLEFT|wxRIGHT|wxBOTTOM|wxADJUST_MINSIZE, 5);

    m_CatNr = new wxTextCtrl( m_General_Panel, ID_TEXTCTRL_CATALOGNR, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer31->Add(m_CatNr, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxLEFT|wxRIGHT|wxBOTTOM, 5);

    m_labDecType = new wxStaticText( m_General_Panel, ID_ABOX_DECODERTYPE, _("Decoder type @"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer31->Add(m_labDecType, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxLEFT|wxRIGHT|wxBOTTOM, 5);

    m_DecoderType = new wxTextCtrl( m_General_Panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer31->Add(m_DecoderType, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxLEFT|wxRIGHT|wxBOTTOM, 5);

    m_labDocumentation = new wxStaticText( m_General_Panel, wxID_ANY, _("Documentation"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer31->Add(m_labDocumentation, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxLEFT|wxRIGHT|wxBOTTOM, 5);

    wxFlexGridSizer* itemFlexGridSizer61 = new wxFlexGridSizer(0, 2, 0, 0);
    itemFlexGridSizer31->Add(itemFlexGridSizer61, 0, wxGROW|wxALIGN_CENTER_VERTICAL, 5);
    m_Documentation = new wxTextCtrl( m_General_Panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer61->Add(m_Documentation, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxLEFT|wxRIGHT|wxBOTTOM, 5);

    m_ShowDoc = new wxButton( m_General_Panel, ID_BUTTON_SHOWDOC, _("..."), wxDefaultPosition, wxSize(40, -1), 0 );
    itemFlexGridSizer61->Add(m_ShowDoc, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxRIGHT|wxBOTTOM, 5);

    itemFlexGridSizer61->AddGrowableCol(0);

    m_Label_Purchased = new wxStaticText( m_General_Panel, wxID_STATIC_PURCHASED, _("Purchased:"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer31->Add(m_Label_Purchased, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxLEFT|wxRIGHT|wxBOTTOM|wxADJUST_MINSIZE, 5);

    wxFlexGridSizer* itemFlexGridSizer65 = new wxFlexGridSizer(0, 3, 0, 0);
    itemFlexGridSizer31->Add(itemFlexGridSizer65, 0, wxGROW|wxALIGN_CENTER_VERTICAL, 5);
    m_Purchased = new wxTextCtrl( m_General_Panel, ID_TEXTCTRL_PURCHASED, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer65->Add(m_Purchased, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxLEFT|wxRIGHT|wxBOTTOM, 5);

    m_labValue = new wxStaticText( m_General_Panel, wxID_ANY, _("Value:"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer65->Add(m_labValue, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxLEFT|wxRIGHT|wxBOTTOM, 5);

    m_Value = new wxTextCtrl( m_General_Panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer65->Add(m_Value, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxLEFT|wxRIGHT|wxBOTTOM, 5);

    itemFlexGridSizer65->AddGrowableCol(0);
    itemFlexGridSizer65->AddGrowableCol(2);

    itemFlexGridSizer31->AddGrowableCol(1);

    wxFlexGridSizer* itemFlexGridSizer69 = new wxFlexGridSizer(0, 4, 0, 0);
    m_GeneralSizer->Add(itemFlexGridSizer69, 0, wxGROW, 5);
    itemFlexGridSizer69->AddGrowableCol(3);

    wxFlexGridSizer* itemFlexGridSizer70 = new wxFlexGridSizer(0, 6, 0, 0);
    m_GeneralSizer->Add(itemFlexGridSizer70, 0, wxGROW, 5);
    m_Label_Runtime = new wxStaticText( m_General_Panel, ID_STATICTEXT1, _("Runtime:"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer70->Add(m_Label_Runtime, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL|wxADJUST_MINSIZE, 5);

    m_RunTime = new wxTextCtrl( m_General_Panel, wxID_ANY, _("0"), wxDefaultPosition, wxDefaultSize, wxTE_READONLY|wxTE_CENTRE );
    m_RunTime->Enable(false);
    itemFlexGridSizer70->Add(m_RunTime, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxRIGHT|wxTOP|wxBOTTOM, 5);

    m_labMTime = new wxStaticText( m_General_Panel, wxID_ANY, _("M-Time:"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer70->Add(m_labMTime, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_MTime = new wxTextCtrl( m_General_Panel, wxID_ANY, _("0"), wxDefaultPosition, wxDefaultSize, wxTE_CENTRE );
    m_MTime->Enable(false);
    itemFlexGridSizer70->Add(m_MTime, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxRIGHT|wxTOP|wxBOTTOM, 5);

    m_labMDate = new wxStaticText( m_General_Panel, wxID_ANY, _("M-Date:"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer70->Add(m_labMDate, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_MDate = new wxTextCtrl( m_General_Panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_CENTRE );
    m_MDate->Enable(false);
    itemFlexGridSizer70->Add(m_MDate, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxRIGHT|wxTOP|wxBOTTOM, 5);

    itemFlexGridSizer70->AddGrowableCol(3);

    wxFlexGridSizer* itemFlexGridSizer77 = new wxFlexGridSizer(0, 3, 0, 0);
    m_GeneralSizer->Add(itemFlexGridSizer77, 0, wxALIGN_LEFT, 5);
    m_UseShortID = new wxCheckBox( m_General_Panel, wxID_ANY, _("Use short ID"), wxDefaultPosition, wxDefaultSize, 0 );
    m_UseShortID->SetValue(false);
    itemFlexGridSizer77->Add(m_UseShortID, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_labThrottleNr = new wxStaticText( m_General_Panel, wxID_ANY, _("Throttle Nr."), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer77->Add(m_labThrottleNr, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxLEFT|wxTOP|wxBOTTOM, 5);

    m_ThrottleNr = new wxSpinCtrl( m_General_Panel, wxID_ANY, wxT("0"), wxDefaultPosition, wxSize(80, -1), wxSP_ARROW_KEYS, 0, 255, 0 );
    itemFlexGridSizer77->Add(m_ThrottleNr, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxBoxSizer* itemBoxSizer81 = new wxBoxSizer(wxVERTICAL);
    itemBoxSizer29->Add(itemBoxSizer81, 0, wxGROW|wxALL, 5);
    m_Serviced = new wxButton( m_General_Panel, ID_LC_SERVICED, _("Serviced"), wxDefaultPosition, wxSize(-1, 30), 0 );
    itemBoxSizer81->Add(m_Serviced, 0, wxALIGN_LEFT|wxALL, 5);

    wxFlexGridSizer* itemFlexGridSizer83 = new wxFlexGridSizer(0, 2, 0, 0);
    itemBoxSizer81->Add(itemFlexGridSizer83, 0, wxGROW, 5);
    m_labMInt = new wxStaticText( m_General_Panel, wxID_ANY, _("M-Int.:"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer83->Add(m_labMInt, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_MInt = new wxSpinCtrl( m_General_Panel, wxID_ANY, wxT("0"), wxDefaultPosition, wxSize(100, -1), wxSP_ARROW_KEYS, 0, 1000, 0 );
    itemFlexGridSizer83->Add(m_MInt, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticLine* itemStaticLine86 = new wxStaticLine( m_General_Panel, wxID_STATIC, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
    itemBoxSizer81->Add(itemStaticLine86, 0, wxGROW|wxALL, 5);

    m_labRemark = new wxStaticText( m_General_Panel, wxID_ANY, _("Remark"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer81->Add(m_labRemark, 0, wxALIGN_LEFT|wxLEFT|wxRIGHT, 5);

    m_Remark = new wxTextCtrl( m_General_Panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE );
    itemBoxSizer81->Add(m_Remark, 1, wxGROW|wxLEFT|wxRIGHT|wxBOTTOM, 5);

    m_Actions = new wxButton( m_General_Panel, ID_LOC_ACTIONS, _("Actions..."), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer81->Add(m_Actions, 0, wxALIGN_LEFT|wxALL, 5);

    m_Notebook->AddPage(m_General_Panel, _("General"));

    m_Interface_Panel = new wxPanel( m_Notebook, ID_PANEL_INTERFACE, wxDefaultPosition, wxDefaultSize, wxSUNKEN_BORDER|wxTAB_TRAVERSAL );
    wxBoxSizer* itemBoxSizer91 = new wxBoxSizer(wxVERTICAL);
    m_Interface_Panel->SetSizer(itemBoxSizer91);

    wxBoxSizer* itemBoxSizer92 = new wxBoxSizer(wxVERTICAL);
    itemBoxSizer91->Add(itemBoxSizer92, 0, wxGROW|wxALL, 5);
    wxFlexGridSizer* itemFlexGridSizer93 = new wxFlexGridSizer(0, 2, 0, 0);
    itemBoxSizer92->Add(itemFlexGridSizer93, 0, wxGROW|wxALL, 5);
    m_Label_IID = new wxStaticText( m_Interface_Panel, wxID_STATIC_IID, _("IID:"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer93->Add(m_Label_IID, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL|wxADJUST_MINSIZE, 2);

    wxArrayString m_IIDStrings;
    m_IID = new wxComboBox( m_Interface_Panel, ID_TEXTCTRL_IID, wxEmptyString, wxDefaultPosition, wxDefaultSize, m_IIDStrings, wxCB_DROPDOWN );
    itemFlexGridSizer93->Add(m_IID, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_Label_Bus = new wxStaticText( m_Interface_Panel, wxID_STATIC_LC_BUS, _("Bus:"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer93->Add(m_Label_Bus, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL|wxADJUST_MINSIZE, 2);

    m_Bus = new wxTextCtrl( m_Interface_Panel, ID_TEXTCTRL_LC_BUS, _("0"), wxDefaultPosition, wxSize(160, -1), wxTE_CENTRE );
    itemFlexGridSizer93->Add(m_Bus, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 2);

    m_Label_Address = new wxStaticText( m_Interface_Panel, wxID_STATIC_ADDRESS, _("Address:"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer93->Add(m_Label_Address, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL|wxADJUST_MINSIZE, 2);

    wxBoxSizer* itemBoxSizer99 = new wxBoxSizer(wxHORIZONTAL);
    itemFlexGridSizer93->Add(itemBoxSizer99, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    m_Address = new wxTextCtrl( m_Interface_Panel, ID_TEXTCTRL_ADDRESS, _("0"), wxDefaultPosition, wxDefaultSize, wxTE_CENTRE );
    itemBoxSizer99->Add(m_Address, 0, wxALIGN_CENTER_VERTICAL|wxALL, 2);

    m_SecAddress = new wxTextCtrl( m_Interface_Panel, wxID_ANY, _("0"), wxDefaultPosition, wxDefaultSize, wxTE_CENTRE );
    itemBoxSizer99->Add(m_SecAddress, 0, wxALIGN_CENTER_VERTICAL|wxALL, 2);

    m_Label_Protocol = new wxStaticText( m_Interface_Panel, wxID_STATIC_PROTOCOL, _("Protocol:"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer93->Add(m_Label_Protocol, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL|wxADJUST_MINSIZE, 2);

    wxFlexGridSizer* itemFlexGridSizer103 = new wxFlexGridSizer(0, 3, 0, 0);
    itemFlexGridSizer93->Add(itemFlexGridSizer103, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    wxArrayString m_ProtocolStrings;
    m_ProtocolStrings.Add(_("ServerDefined"));
    m_ProtocolStrings.Add(_("Motorola"));
    m_ProtocolStrings.Add(_("NMRA-DCC"));
    m_ProtocolStrings.Add(_("NMRA-DCC long"));
    m_ProtocolStrings.Add(_("Analog"));
    m_ProtocolStrings.Add(_("Car"));
    m_ProtocolStrings.Add(_("SX1"));
    m_ProtocolStrings.Add(_("SX2"));
    m_Protocol = new wxChoice( m_Interface_Panel, ID_CHOICE_PROTOCOL, wxDefaultPosition, wxDefaultSize, m_ProtocolStrings, 0 );
    m_Protocol->SetStringSelection(_("ServerDefined"));
    itemFlexGridSizer103->Add(m_Protocol, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 2);

    m_LabelProtVersion = new wxStaticText( m_Interface_Panel, wxID_STATIC_PROT_VER, _("ProtVersion:"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer103->Add(m_LabelProtVersion, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL|wxADJUST_MINSIZE, 2);

    m_ProtVersion = new wxTextCtrl( m_Interface_Panel, ID_TEXTCTRL_PROTVER, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_CENTRE );
    itemFlexGridSizer103->Add(m_ProtVersion, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 2);

    m_LabelSpeedSteps = new wxStaticText( m_Interface_Panel, wxID_STATIC_SPEEDSTEPS, _("Speed steps:"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer93->Add(m_LabelSpeedSteps, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL|wxADJUST_MINSIZE, 2);

    wxBoxSizer* itemBoxSizer108 = new wxBoxSizer(wxHORIZONTAL);
    itemFlexGridSizer93->Add(itemBoxSizer108, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    m_SpeedSteps = new wxTextCtrl( m_Interface_Panel, ID_TEXTCTRL_SPEEDSTEPS, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_CENTRE );
    itemBoxSizer108->Add(m_SpeedSteps, 0, wxALIGN_CENTER_VERTICAL|wxALL, 2);

    m_SecSpeedSteps = new wxTextCtrl( m_Interface_Panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_CENTRE );
    itemBoxSizer108->Add(m_SecSpeedSteps, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_LabelFunCnt = new wxStaticText( m_Interface_Panel, wxID_STATIC_FUNCNT, _("Functions:"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer93->Add(m_LabelFunCnt, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL|wxADJUST_MINSIZE, 2);

    m_FunCnt = new wxTextCtrl( m_Interface_Panel, ID_TEXTCTRL_FUNCNT, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_CENTRE );
    itemFlexGridSizer93->Add(m_FunCnt, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 2);

    itemFlexGridSizer93->AddGrowableCol(1);

    wxBoxSizer* itemBoxSizer113 = new wxBoxSizer(wxHORIZONTAL);
    itemBoxSizer91->Add(itemBoxSizer113, 0, wxGROW|wxALL, 5);
    m_VelocityBox = new wxStaticBox(m_Interface_Panel, wxID_ANY, _("Velocity"));
    wxStaticBoxSizer* itemStaticBoxSizer114 = new wxStaticBoxSizer(m_VelocityBox, wxVERTICAL);
    itemBoxSizer113->Add(itemStaticBoxSizer114, 0, wxGROW|wxALL, 5);
    wxFlexGridSizer* itemFlexGridSizer115 = new wxFlexGridSizer(0, 4, 0, 0);
    itemStaticBoxSizer114->Add(itemFlexGridSizer115, 0, wxALIGN_LEFT, 5);
    m_Label_V_min = new wxStaticText( m_Interface_Panel, wxID_STATIC_V_MIN, _("V_min:"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer115->Add(m_Label_V_min, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxLEFT|wxTOP|wxBOTTOM|wxADJUST_MINSIZE, 2);

    m_V_min = new wxTextCtrl( m_Interface_Panel, ID_TEXTCTRL_V_MIN, _("0"), wxDefaultPosition, wxSize(60, -1), wxTE_CENTRE );
    m_V_min->SetMaxLength(3);
    itemFlexGridSizer115->Add(m_V_min, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxRIGHT|wxTOP|wxBOTTOM, 2);

    m_Label_V_Rmin = new wxStaticText( m_Interface_Panel, wxID_ANY, _("V_Rmin:"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer115->Add(m_Label_V_Rmin, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxLEFT|wxTOP|wxBOTTOM|wxADJUST_MINSIZE, 5);

    m_V_Rmin = new wxTextCtrl( m_Interface_Panel, wxID_ANY, _("0"), wxDefaultPosition, wxSize(60, -1), wxTE_CENTRE );
    itemFlexGridSizer115->Add(m_V_Rmin, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxRIGHT|wxTOP|wxBOTTOM, 5);

    m_Label_V_mid = new wxStaticText( m_Interface_Panel, wxID_ANY, _("V_mid:"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer115->Add(m_Label_V_mid, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxLEFT|wxBOTTOM|wxADJUST_MINSIZE, 2);

    m_V_mid = new wxTextCtrl( m_Interface_Panel, wxID_ANY, _("0"), wxDefaultPosition, wxSize(60, -1), wxTE_CENTRE );
    m_V_mid->SetMaxLength(3);
    itemFlexGridSizer115->Add(m_V_mid, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxRIGHT|wxBOTTOM, 2);

    m_Label_V_Rmid = new wxStaticText( m_Interface_Panel, wxID_ANY, _("V_Rmid:"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer115->Add(m_Label_V_Rmid, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxLEFT|wxBOTTOM|wxADJUST_MINSIZE, 5);

    m_V_Rmid = new wxTextCtrl( m_Interface_Panel, wxID_ANY, _("0"), wxDefaultPosition, wxSize(60, -1), wxTE_CENTRE );
    itemFlexGridSizer115->Add(m_V_Rmid, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxRIGHT|wxBOTTOM, 5);

    m_labVcru = new wxStaticText( m_Interface_Panel, wxID_ANY, _("V_cru:"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer115->Add(m_labVcru, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxLEFT|wxBOTTOM, 2);

    m_V_cru = new wxTextCtrl( m_Interface_Panel, wxID_ANY, _("0"), wxDefaultPosition, wxSize(60, -1), wxTE_CENTRE );
    itemFlexGridSizer115->Add(m_V_cru, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxRIGHT|wxBOTTOM, 2);

    m_labVRcru = new wxStaticText( m_Interface_Panel, wxID_STATIC, _("V_Rcru:"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer115->Add(m_labVRcru, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxLEFT|wxBOTTOM, 5);

    m_V_Rcru = new wxTextCtrl( m_Interface_Panel, wxID_ANY, _("0"), wxDefaultPosition, wxSize(60, -1), wxTE_CENTRE );
    itemFlexGridSizer115->Add(m_V_Rcru, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxRIGHT|wxBOTTOM, 5);

    m_Label_V_max = new wxStaticText( m_Interface_Panel, wxID_STATIC_V_MAX, _("V_max:"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer115->Add(m_Label_V_max, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxLEFT|wxBOTTOM|wxADJUST_MINSIZE, 2);

    wxBoxSizer* itemBoxSizer129 = new wxBoxSizer(wxHORIZONTAL);
    itemFlexGridSizer115->Add(itemBoxSizer129, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    m_V_max = new wxTextCtrl( m_Interface_Panel, ID_TEXTCTRL_V_MAX, _("100"), wxDefaultPosition, wxSize(60, -1), wxTE_CENTRE );
    m_V_max->SetMaxLength(3);
    itemBoxSizer129->Add(m_V_max, 0, wxALIGN_CENTER_VERTICAL|wxRIGHT|wxBOTTOM, 2);

    m_VmaxSec = new wxTextCtrl( m_Interface_Panel, wxID_ANY, _("14"), wxDefaultPosition, wxSize(60, -1), wxTE_CENTRE );
    m_VmaxSec->SetMaxLength(3);
    itemBoxSizer129->Add(m_VmaxSec, 0, wxALIGN_CENTER_VERTICAL|wxLEFT|wxRIGHT|wxBOTTOM, 5);

    m_Label_V_Rmax = new wxStaticText( m_Interface_Panel, wxID_ANY, _("V_Rmax:"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer115->Add(m_Label_V_Rmax, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxLEFT|wxBOTTOM|wxADJUST_MINSIZE, 5);

    m_V_Rmax = new wxTextCtrl( m_Interface_Panel, wxID_ANY, _("0"), wxDefaultPosition, wxSize(60, -1), wxTE_CENTRE );
    itemFlexGridSizer115->Add(m_V_Rmax, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxRIGHT|wxBOTTOM, 5);

    m_OptionsBox = new wxStaticBox(m_Interface_Panel, wxID_ANY, _("Options"));
    wxStaticBoxSizer* itemStaticBoxSizer134 = new wxStaticBoxSizer(m_OptionsBox, wxVERTICAL);
    itemBoxSizer113->Add(itemStaticBoxSizer134, 0, wxGROW|wxALL, 5);
    wxFlexGridSizer* itemFlexGridSizer135 = new wxFlexGridSizer(0, 2, 0, 0);
    itemStaticBoxSizer134->Add(itemFlexGridSizer135, 0, wxALIGN_LEFT, 5);
    m_Label_Mass = new wxStaticText( m_Interface_Panel, wxID_STATIC_MASS, _("Mass:"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer135->Add(m_Label_Mass, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxLEFT|wxTOP|wxBOTTOM|wxADJUST_MINSIZE, 2);

    m_Mass = new wxTextCtrl( m_Interface_Panel, ID_TEXTCTRL_MASS, _("0"), wxDefaultPosition, wxSize(60, -1), wxTE_CENTRE );
    m_Mass->SetMaxLength(3);
    itemFlexGridSizer135->Add(m_Mass, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxRIGHT|wxTOP|wxBOTTOM, 2);

    m_labDirPause = new wxStaticText( m_Interface_Panel, wxID_ANY, _("Dir pause:"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer135->Add(m_labDirPause, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxLEFT|wxTOP|wxBOTTOM|wxADJUST_MINSIZE, 5);

    m_DirPause = new wxTextCtrl( m_Interface_Panel, wxID_ANY, _("0"), wxDefaultPosition, wxSize(60, -1), wxTE_CENTRE );
    m_DirPause->SetMaxLength(4);
    itemFlexGridSizer135->Add(m_DirPause, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxRIGHT|wxTOP|wxBOTTOM, 2);

    m_LabelV_mode = new wxStaticText( m_Interface_Panel, wxID_STATIC_LOC_V_MODE, _("V_mode:"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer135->Add(m_LabelV_mode, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxLEFT|wxTOP|wxBOTTOM|wxADJUST_MINSIZE, 2);

    m_V_mode_percent = new wxCheckBox( m_Interface_Panel, ID_CHECKBOX_LOC_CONTROLLED, _("percent"), wxDefaultPosition, wxDefaultSize, wxCHK_2STATE );
    m_V_mode_percent->SetValue(false);
    itemFlexGridSizer135->Add(m_V_mode_percent, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxRIGHT|wxTOP|wxBOTTOM, 2);

    m_LabelPlacing = new wxStaticText( m_Interface_Panel, wxID_STATIC_LOC_PLACING, _("Placing:"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer135->Add(m_LabelPlacing, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxLEFT|wxTOP|wxBOTTOM|wxADJUST_MINSIZE, 2);

    m_Placing = new wxCheckBox( m_Interface_Panel, ID_CHECKBOX_LOC_PLACING, _("default"), wxDefaultPosition, wxDefaultSize, wxCHK_2STATE );
    m_Placing->SetValue(true);
    itemFlexGridSizer135->Add(m_Placing, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxRIGHT|wxTOP|wxBOTTOM, 2);

    wxStaticText* itemStaticText144 = new wxStaticText( m_Interface_Panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer135->Add(itemStaticText144, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxLEFT|wxRIGHT|wxTOP, 2);

    m_Info4Throttle = new wxCheckBox( m_Interface_Panel, wxID_ANY, _("info4throttle"), wxDefaultPosition, wxDefaultSize, 0 );
    m_Info4Throttle->SetValue(false);
    itemFlexGridSizer135->Add(m_Info4Throttle, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxRIGHT|wxTOP|wxBOTTOM, 2);

    wxStaticText* itemStaticText146 = new wxStaticText( m_Interface_Panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer135->Add(itemStaticText146, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxLEFT|wxRIGHT|wxTOP, 2);

    itemFlexGridSizer135->AddGrowableCol(1);

    m_AccelerationBox = new wxStaticBox(m_Interface_Panel, wxID_ANY, _("Acceleration"));
    wxStaticBoxSizer* itemStaticBoxSizer147 = new wxStaticBoxSizer(m_AccelerationBox, wxVERTICAL);
    itemBoxSizer113->Add(itemStaticBoxSizer147, 0, wxGROW|wxALL, 5);
    wxBoxSizer* itemBoxSizer148 = new wxBoxSizer(wxVERTICAL);
    itemStaticBoxSizer147->Add(itemBoxSizer148, 0, wxALIGN_CENTER_HORIZONTAL, 5);
    m_AdjustAccel = new wxCheckBox( m_Interface_Panel, wxID_ANY, _("Adjust acceleration"), wxDefaultPosition, wxDefaultSize, 0 );
    m_AdjustAccel->SetValue(false);
    itemBoxSizer148->Add(m_AdjustAccel, 0, wxALIGN_LEFT|wxALL, 5);

    wxFlexGridSizer* itemFlexGridSizer150 = new wxFlexGridSizer(0, 2, 0, 0);
    itemBoxSizer148->Add(itemFlexGridSizer150, 0, wxALIGN_LEFT, 5);
    m_labMaxLoad = new wxStaticText( m_Interface_Panel, wxID_ANY, _("Max. load"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer150->Add(m_labMaxLoad, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxLEFT|wxBOTTOM, 5);

    m_MaxLoad = new wxSpinCtrl( m_Interface_Panel, wxID_ANY, wxT("0"), wxDefaultPosition, wxSize(100, -1), wxSP_ARROW_KEYS, 0, 999999, 0 );
    itemFlexGridSizer150->Add(m_MaxLoad, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxRIGHT|wxBOTTOM, 5);

    m_labMinAccel = new wxStaticText( m_Interface_Panel, wxID_ANY, _("Min. CV3"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer150->Add(m_labMinAccel, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxLEFT|wxBOTTOM, 5);

    m_MinAccel = new wxSpinCtrl( m_Interface_Panel, wxID_ANY, wxT("0"), wxDefaultPosition, wxSize(80, -1), wxSP_ARROW_KEYS, 0, 255, 0 );
    itemFlexGridSizer150->Add(m_MinAccel, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxRIGHT|wxBOTTOM, 5);

    m_labMaxAccel = new wxStaticText( m_Interface_Panel, wxID_ANY, _("Max. CV3"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer150->Add(m_labMaxAccel, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxLEFT|wxBOTTOM, 5);

    m_MaxAccel = new wxSpinCtrl( m_Interface_Panel, wxID_ANY, wxT("0"), wxDefaultPosition, wxSize(80, -1), wxSP_ARROW_KEYS, 0, 255, 0 );
    itemFlexGridSizer150->Add(m_MaxAccel, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxRIGHT|wxBOTTOM, 5);

    itemFlexGridSizer150->AddGrowableCol(1);

    m_Notebook->AddPage(m_Interface_Panel, _("Interface"));

    m_DetailsPanel = new wxPanel( m_Notebook, ID_PANEL_DETAILS, wxDefaultPosition, wxDefaultSize, wxSUNKEN_BORDER|wxTAB_TRAVERSAL );
    wxBoxSizer* itemBoxSizer158 = new wxBoxSizer(wxVERTICAL);
    m_DetailsPanel->SetSizer(itemBoxSizer158);

    wxBoxSizer* itemBoxSizer159 = new wxBoxSizer(wxHORIZONTAL);
    itemBoxSizer158->Add(itemBoxSizer159, 0, wxGROW|wxALL, 5);
    wxBoxSizer* itemBoxSizer160 = new wxBoxSizer(wxVERTICAL);
    itemBoxSizer159->Add(itemBoxSizer160, 0, wxALIGN_TOP|wxALL, 5);
    wxFlexGridSizer* itemFlexGridSizer161 = new wxFlexGridSizer(0, 2, 0, 0);
    itemBoxSizer160->Add(itemFlexGridSizer161, 0, wxGROW, 5);
    m_Label_Blockwait = new wxStaticText( m_DetailsPanel, wxID_STATIC_BLOCKWAIT, _("Block wait"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer161->Add(m_Label_Blockwait, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL|wxADJUST_MINSIZE, 5);

    wxFlexGridSizer* itemFlexGridSizer163 = new wxFlexGridSizer(0, 2, 0, 0);
    itemFlexGridSizer161->Add(itemFlexGridSizer163, 0, wxGROW|wxALIGN_CENTER_VERTICAL, 5);
    m_Blockwait = new wxTextCtrl( m_DetailsPanel, ID_TEXTCTRL_BLOCKWAIT, _("0"), wxDefaultPosition, wxDefaultSize, wxTE_CENTRE );
    itemFlexGridSizer163->Add(m_Blockwait, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_labBlockWaitSec = new wxStaticText( m_DetailsPanel, wxID_ANY, _("sec"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer163->Add(m_labBlockWaitSec, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxRIGHT|wxTOP|wxBOTTOM, 5);

    m_labMaxWaitTime = new wxStaticText( m_DetailsPanel, wxID_ANY, _("Max. block wait"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer161->Add(m_labMaxWaitTime, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxFlexGridSizer* itemFlexGridSizer167 = new wxFlexGridSizer(0, 2, 0, 0);
    itemFlexGridSizer161->Add(itemFlexGridSizer167, 0, wxGROW|wxALIGN_CENTER_VERTICAL, 5);
    m_MaxWaitTime = new wxTextCtrl( m_DetailsPanel, wxID_ANY, _("0"), wxDefaultPosition, wxDefaultSize, wxTE_CENTRE );
    itemFlexGridSizer167->Add(m_MaxWaitTime, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_labMaxBlockWaitSec = new wxStaticText( m_DetailsPanel, wxID_ANY, _("sec"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer167->Add(m_labMaxBlockWaitSec, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxRIGHT|wxTOP|wxBOTTOM, 5);

    m_labEventTimer = new wxStaticText( m_DetailsPanel, wxID_ANY, _("Event timer"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer161->Add(m_labEventTimer, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxLEFT|wxRIGHT|wxBOTTOM, 5);

    wxFlexGridSizer* itemFlexGridSizer171 = new wxFlexGridSizer(0, 2, 0, 0);
    itemFlexGridSizer161->Add(itemFlexGridSizer171, 0, wxGROW|wxALIGN_CENTER_VERTICAL, 5);
    m_EventTimer = new wxTextCtrl( m_DetailsPanel, wxID_ANY, _("0"), wxDefaultPosition, wxDefaultSize, wxTE_CENTRE );
    itemFlexGridSizer171->Add(m_EventTimer, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxLEFT|wxRIGHT|wxBOTTOM, 5);

    m_labEventTimerMS = new wxStaticText( m_DetailsPanel, wxID_ANY, _("ms"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer171->Add(m_labEventTimerMS, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxRIGHT|wxTOP|wxBOTTOM, 5);

    m_labEvtCorrection = new wxStaticText( m_DetailsPanel, wxID_ANY, _("Timer correction"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer161->Add(m_labEvtCorrection, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxLEFT|wxRIGHT|wxBOTTOM, 5);

    wxFlexGridSizer* itemFlexGridSizer175 = new wxFlexGridSizer(0, 2, 0, 0);
    itemFlexGridSizer161->Add(itemFlexGridSizer175, 0, wxGROW|wxALIGN_CENTER_VERTICAL, 5);
    m_EvtCorrection = new wxSpinCtrl( m_DetailsPanel, wxID_ANY, wxT("100"), wxDefaultPosition, wxSize(80, -1), wxSP_ARROW_KEYS, 1, 1000, 100 );
    itemFlexGridSizer175->Add(m_EvtCorrection, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxLEFT|wxRIGHT|wxBOTTOM, 5);

    m_labTimerCorrectionPercent = new wxStaticText( m_DetailsPanel, wxID_ANY, _("%"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer175->Add(m_labTimerCorrectionPercent, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxRIGHT|wxTOP|wxBOTTOM, 5);

    m_labPriority = new wxStaticText( m_DetailsPanel, wxID_ANY, _("Priority"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer161->Add(m_labPriority, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxLEFT|wxRIGHT|wxBOTTOM, 5);

    m_Priority = new wxSpinCtrl( m_DetailsPanel, wxID_ANY, wxT("10"), wxDefaultPosition, wxSize(80, -1), wxSP_ARROW_KEYS, 0, 100, 10 );
    itemFlexGridSizer161->Add(m_Priority, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxLEFT|wxRIGHT|wxBOTTOM, 5);

    m_labSwapTimer = new wxStaticText( m_DetailsPanel, wxID_ANY, _("Swap timer"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer161->Add(m_labSwapTimer, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxLEFT|wxRIGHT|wxBOTTOM, 5);

    wxFlexGridSizer* itemFlexGridSizer181 = new wxFlexGridSizer(0, 2, 0, 0);
    itemFlexGridSizer161->Add(itemFlexGridSizer181, 0, wxGROW|wxALIGN_CENTER_VERTICAL, 5);
    m_SwapTimer = new wxSpinCtrl( m_DetailsPanel, wxID_ANY, wxT("0"), wxDefaultPosition, wxSize(80, -1), wxSP_ARROW_KEYS, 0, 1000, 0 );
    itemFlexGridSizer181->Add(m_SwapTimer, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxLEFT|wxRIGHT|wxBOTTOM, 5);

    m_labSwapTimerMS = new wxStaticText( m_DetailsPanel, wxID_ANY, _("ms"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer181->Add(m_labSwapTimerMS, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxRIGHT|wxTOP|wxBOTTOM, 5);

    m_labStartupTour = new wxStaticText( m_DetailsPanel, wxID_STATIC, _("Startup tour"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer161->Add(m_labStartupTour, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxLEFT|wxRIGHT|wxBOTTOM, 5);

    wxArrayString m_StartupTourStrings;
    m_StartupTour = new wxComboBox( m_DetailsPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(160, -1), m_StartupTourStrings, wxCB_READONLY );
    itemFlexGridSizer161->Add(m_StartupTour, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxLEFT|wxRIGHT|wxBOTTOM, 5);

    m_labStartupSchedule = new wxStaticText( m_DetailsPanel, wxID_ANY, _("Starup schedule"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer161->Add(m_labStartupSchedule, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxLEFT|wxRIGHT|wxBOTTOM, 5);

    wxArrayString m_StartupScheduleStrings;
    m_StartupSchedule = new wxComboBox( m_DetailsPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(160, -1), m_StartupScheduleStrings, wxCB_READONLY );
    itemFlexGridSizer161->Add(m_StartupSchedule, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxLEFT|wxRIGHT|wxBOTTOM, 5);

    itemFlexGridSizer161->AddGrowableCol(1);

    wxArrayString m_CargoBoxStrings;
    m_CargoBoxStrings.Add(_("&None"));
    m_CargoBoxStrings.Add(_("&Goods"));
    m_CargoBoxStrings.Add(_("&Passengers"));
    m_CargoBoxStrings.Add(_("&Mixed"));
    m_CargoBoxStrings.Add(_("&Cleaning"));
    m_CargoBoxStrings.Add(_("&ICE"));
    m_CargoBoxStrings.Add(_("&Post"));
    m_CargoBoxStrings.Add(_("&light"));
    m_CargoBoxStrings.Add(_("&lightgoods"));
    m_CargoBoxStrings.Add(_("&Regional"));
    m_CargoBoxStrings.Add(_("&All"));
    m_CargoBoxStrings.Add(_("&Shunting"));
    m_CargoBox = new wxRadioBox( m_DetailsPanel, ID_RADIOBOX_CARGO, _("Cargo"), wxDefaultPosition, wxDefaultSize, m_CargoBoxStrings, 3, wxRA_SPECIFY_COLS );
    m_CargoBox->SetSelection(0);
    itemBoxSizer160->Add(m_CargoBox, 0, wxALIGN_LEFT|wxALL, 5);

    wxStaticLine* itemStaticLine189 = new wxStaticLine( m_DetailsPanel, wxID_STATIC, wxDefaultPosition, wxDefaultSize, wxLI_VERTICAL );
    itemBoxSizer159->Add(itemStaticLine189, 0, wxGROW|wxALL, 5);

    wxBoxSizer* itemBoxSizer190 = new wxBoxSizer(wxVERTICAL);
    itemBoxSizer159->Add(itemBoxSizer190, 0, wxALIGN_TOP|wxALL, 5);
    m_Commuter = new wxCheckBox( m_DetailsPanel, ID_CHECKBOX_COMMUTER, _("Commuter train"), wxDefaultPosition, wxDefaultSize, wxCHK_2STATE );
    m_Commuter->SetValue(false);
    itemBoxSizer190->Add(m_Commuter, 0, wxALIGN_LEFT|wxLEFT|wxRIGHT, 5);

    m_UseScheduleTime = new wxCheckBox( m_DetailsPanel, wxID_ANY, _("Use schedule departure time"), wxDefaultPosition, wxDefaultSize, 0 );
    m_UseScheduleTime->SetValue(false);
    itemBoxSizer190->Add(m_UseScheduleTime, 0, wxALIGN_LEFT|wxLEFT|wxRIGHT, 5);

    m_secondNextBlock = new wxCheckBox( m_DetailsPanel, wxID_ANY, _("Reserve second next block"), wxDefaultPosition, wxDefaultSize, 0 );
    m_secondNextBlock->SetValue(false);
    itemBoxSizer190->Add(m_secondNextBlock, 0, wxALIGN_LEFT|wxLEFT|wxRIGHT, 5);

    m_ShortIn = new wxCheckBox( m_DetailsPanel, wxID_ANY, _("Use shortin event"), wxDefaultPosition, wxDefaultSize, 0 );
    m_ShortIn->SetValue(false);
    itemBoxSizer190->Add(m_ShortIn, 0, wxALIGN_LEFT|wxLEFT|wxRIGHT, 5);

    m_InAtPre2In = new wxCheckBox( m_DetailsPanel, wxID_ANY, _("Stop at pre2in event"), wxDefaultPosition, wxDefaultSize, 0 );
    m_InAtPre2In->SetValue(false);
    itemBoxSizer190->Add(m_InAtPre2In, 0, wxALIGN_LEFT|wxLEFT|wxRIGHT, 5);

    m_UseManualRoutes = new wxCheckBox( m_DetailsPanel, wxID_ANY, _("Use manual routes"), wxDefaultPosition, wxDefaultSize, 0 );
    m_UseManualRoutes->SetValue(false);
    itemBoxSizer190->Add(m_UseManualRoutes, 0, wxALIGN_LEFT|wxLEFT|wxRIGHT, 5);

    m_UseOwnWaittime = new wxCheckBox( m_DetailsPanel, wxID_ANY, _("Use own wait time"), wxDefaultPosition, wxDefaultSize, 0 );
    m_UseOwnWaittime->SetValue(false);
    itemBoxSizer190->Add(m_UseOwnWaittime, 0, wxALIGN_LEFT|wxLEFT|wxRIGHT, 5);

    m_Check2In = new wxCheckBox( m_DetailsPanel, wxID_ANY, _("Check for free destination until reaching IN"), wxDefaultPosition, wxDefaultSize, 0 );
    m_Check2In->SetValue(false);
    itemBoxSizer190->Add(m_Check2In, 0, wxALIGN_LEFT|wxLEFT|wxRIGHT, 5);

    m_UseDepartDelay = new wxCheckBox( m_DetailsPanel, wxID_ANY, _("Use depart delay"), wxDefaultPosition, wxDefaultSize, 0 );
    m_UseDepartDelay->SetValue(false);
    itemBoxSizer190->Add(m_UseDepartDelay, 0, wxALIGN_LEFT|wxLEFT|wxRIGHT, 5);

    m_FreeBlockOnEnter = new wxCheckBox( m_DetailsPanel, wxID_ANY, _("Free block on enter"), wxDefaultPosition, wxDefaultSize, 0 );
    m_FreeBlockOnEnter->SetValue(false);
    itemBoxSizer190->Add(m_FreeBlockOnEnter, 0, wxALIGN_LEFT|wxLEFT|wxRIGHT, 5);

    m_V0onSwap = new wxCheckBox( m_DetailsPanel, wxID_ANY, _("V0 on swap"), wxDefaultPosition, wxDefaultSize, 0 );
    m_V0onSwap->SetValue(false);
    itemBoxSizer190->Add(m_V0onSwap, 0, wxALIGN_LEFT|wxLEFT|wxRIGHT, 5);

    m_BBT = new wxCheckBox( m_DetailsPanel, wxID_ANY, _("BBT"), wxDefaultPosition, wxDefaultSize, 0 );
    m_BBT->SetValue(false);
    itemBoxSizer190->Add(m_BBT, 0, wxALIGN_LEFT|wxLEFT|wxRIGHT, 5);

    m_ReduceSpeedAtEnter = new wxCheckBox( m_DetailsPanel, wxID_ANY, _("Reduce speed at enter"), wxDefaultPosition, wxDefaultSize, 0 );
    m_ReduceSpeedAtEnter->SetValue(false);
    itemBoxSizer190->Add(m_ReduceSpeedAtEnter, 0, wxALIGN_LEFT|wxLEFT|wxRIGHT, 5);

    m_ResetPlacing = new wxCheckBox( m_DetailsPanel, wxID_ANY, _("Reset placing and direction"), wxDefaultPosition, wxDefaultSize, 0 );
    m_ResetPlacing->SetValue(false);
    itemBoxSizer190->Add(m_ResetPlacing, 0, wxALIGN_LEFT|wxLEFT|wxRIGHT|wxBOTTOM, 5);

    wxArrayString m_EngineBoxStrings;
    m_EngineBoxStrings.Add(_("&Diesel"));
    m_EngineBoxStrings.Add(_("&Steam"));
    m_EngineBoxStrings.Add(_("&Electric"));
    m_EngineBoxStrings.Add(_("&Automobile"));
    m_EngineBox = new wxRadioBox( m_DetailsPanel, ID_RADIOBOX_ENGINE, _("Engine"), wxDefaultPosition, wxDefaultSize, m_EngineBoxStrings, 2, wxRA_SPECIFY_ROWS );
    m_EngineBox->SetSelection(0);
    itemBoxSizer190->Add(m_EngineBox, 0, wxALIGN_LEFT|wxLEFT|wxRIGHT|wxTOP, 5);

    wxFlexGridSizer* itemFlexGridSizer206 = new wxFlexGridSizer(0, 3, 0, 0);
    itemBoxSizer190->Add(itemFlexGridSizer206, 0, wxGROW, 5);
    m_labClass = new wxStaticText( m_DetailsPanel, wxID_ANY, _("Class"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer206->Add(m_labClass, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxLEFT|wxTOP|wxBOTTOM, 5);

    m_Class = new wxTextCtrl( m_DetailsPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
    m_Class->SetMaxLength(8);
    itemFlexGridSizer206->Add(m_Class, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxArrayString m_EraStrings;
    m_EraStrings.Add(_("&I"));
    m_EraStrings.Add(_("&II"));
    m_EraStrings.Add(_("&III"));
    m_EraStrings.Add(_("&IV"));
    m_EraStrings.Add(_("&V"));
    m_EraStrings.Add(_("&VI"));
    m_Era = new wxRadioBox( m_DetailsPanel, wxID_ANY, _("Era"), wxDefaultPosition, wxDefaultSize, m_EraStrings, 1, wxRA_SPECIFY_ROWS );
    m_Era->SetSelection(0);
    itemFlexGridSizer206->Add(m_Era, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxLEFT|wxRIGHT|wxBOTTOM, 5);

    itemFlexGridSizer206->AddGrowableCol(1);

    m_Notebook->AddPage(m_DetailsPanel, _("Details"));

    m_FunctionPanel = new wxPanel( m_Notebook, ID_PANEL_FUNCTIONS, wxDefaultPosition, wxDefaultSize, wxSUNKEN_BORDER|wxTAB_TRAVERSAL );
    wxBoxSizer* itemBoxSizer211 = new wxBoxSizer(wxVERTICAL);
    m_FunctionPanel->SetSizer(itemBoxSizer211);

    wxFlexGridSizer* itemFlexGridSizer212 = new wxFlexGridSizer(0, 5, 0, 0);
    itemBoxSizer211->Add(itemFlexGridSizer212, 0, wxGROW|wxALL, 5);
    m_labF0Nr = new wxStaticText( m_FunctionPanel, wxID_ANY, _("#"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer212->Add(m_labF0Nr, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_labF0Desc = new wxStaticText( m_FunctionPanel, wxID_STATIC, _("Description"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer212->Add(m_labF0Desc, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_labF0Timer = new wxStaticText( m_FunctionPanel, wxID_ANY, _("Timer"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer212->Add(m_labF0Timer, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_labF0Events = new wxStaticText( m_FunctionPanel, wxID_ANY, _("Events"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer212->Add(m_labF0Events, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_labF0Icon = new wxStaticText( m_FunctionPanel, wxID_ANY, _("Icon"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer212->Add(m_labF0Icon, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_Label_f0 = new wxStaticText( m_FunctionPanel, wxID_ANY, _("f0"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer212->Add(m_Label_f0, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxLEFT|wxRIGHT|wxADJUST_MINSIZE, 2);

    m_f0 = new wxTextCtrl( m_FunctionPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer212->Add(m_f0, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxLEFT|wxRIGHT, 2);

    m_TimerF0 = new wxSpinCtrl( m_FunctionPanel, wxID_ANY, wxT("0"), wxDefaultPosition, wxSize(70, -1), wxSP_ARROW_KEYS, 0, 100, 0 );
    itemFlexGridSizer212->Add(m_TimerF0, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);

    m_Button_f0 = new wxButton( m_FunctionPanel, ID_BUTTON_F0, _("..."), wxDefaultPosition, wxSize(40, 25), 0 );
    itemFlexGridSizer212->Add(m_Button_f0, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxLEFT|wxRIGHT, 2);

    m_F0Icon = new wxTextCtrl( m_FunctionPanel, ID_LOC_ICONF0, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer212->Add(m_F0Icon, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxLEFT|wxRIGHT, 5);

    itemFlexGridSizer212->AddGrowableCol(1);

    wxStaticLine* itemStaticLine223 = new wxStaticLine( m_FunctionPanel, wxID_STATIC, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
    itemBoxSizer211->Add(itemStaticLine223, 0, wxGROW|wxALL, 5);

    wxFlexGridSizer* itemFlexGridSizer224 = new wxFlexGridSizer(0, 3, 0, 0);
    itemBoxSizer211->Add(itemFlexGridSizer224, 0, wxALIGN_CENTER_HORIZONTAL|wxLEFT|wxRIGHT|wxTOP, 5);
    wxButton* itemButton225 = new wxButton( m_FunctionPanel, ID_LOC_FN_GROUP_PREV, _("< Fg"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer224->Add(itemButton225, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_labFnGroup = new wxStaticText( m_FunctionPanel, wxID_ANY, _("1"), wxDefaultPosition, wxDefaultSize, 0 );
    m_labFnGroup->SetFont(wxFont(12, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxT("Sans")));
    itemFlexGridSizer224->Add(m_labFnGroup, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_FunctionGroup = new wxButton( m_FunctionPanel, ID_LOC_FN_GROUP, _("Fg >"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer224->Add(m_FunctionGroup, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxFlexGridSizer* itemFlexGridSizer228 = new wxFlexGridSizer(0, 8, 0, 0);
    itemBoxSizer211->Add(itemFlexGridSizer228, 0, wxGROW|wxALL, 5);
    m_labFnNr = new wxStaticText( m_FunctionPanel, wxID_ANY, _("#"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer228->Add(m_labFnNr, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_labFnDesc = new wxStaticText( m_FunctionPanel, wxID_ANY, _("Description"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer228->Add(m_labFnDesc, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_labFnTimer = new wxStaticText( m_FunctionPanel, wxID_ANY, _("Timer"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer228->Add(m_labFnTimer, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_labFnEvents = new wxStaticText( m_FunctionPanel, wxID_ANY, _("Events"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer228->Add(m_labFnEvents, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_labSound = new wxStaticText( m_FunctionPanel, wxID_ANY, _("Sound"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer228->Add(m_labSound, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_labIcon = new wxStaticText( m_FunctionPanel, wxID_ANY, _("Icon"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer228->Add(m_labIcon, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_labFnAddr = new wxStaticText( m_FunctionPanel, wxID_ANY, _("Address"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer228->Add(m_labFnAddr, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_labAddrFn = new wxStaticText( m_FunctionPanel, wxID_ANY, _("fx"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer228->Add(m_labAddrFn, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_Label_f1 = new wxStaticText( m_FunctionPanel, wxID_STATIC_F1, _("f1"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer228->Add(m_Label_f1, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxLEFT|wxRIGHT|wxTOP|wxADJUST_MINSIZE, 2);

    m_f1 = new wxTextCtrl( m_FunctionPanel, ID_TEXTCTRL_F1, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer228->Add(m_f1, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_TimerF1 = new wxSpinCtrl( m_FunctionPanel, wxID_ANY, wxT("0"), wxDefaultPosition, wxSize(70, -1), wxSP_ARROW_KEYS, 0, 1000, 0 );
    itemFlexGridSizer228->Add(m_TimerF1, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);

    m_Button_f1 = new wxButton( m_FunctionPanel, ID_BUTTON_F1, _("..."), wxDefaultPosition, wxSize(40, 25), 0 );
    itemFlexGridSizer228->Add(m_Button_f1, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 2);

    m_Sound1 = new wxTextCtrl( m_FunctionPanel, ID_LOC_SOUND1, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer228->Add(m_Sound1, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_Icon_f1 = new wxTextCtrl( m_FunctionPanel, ID_LOC_ICONF1, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer228->Add(m_Icon_f1, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_F1Addr = new wxSpinCtrl( m_FunctionPanel, wxID_ANY, wxT("0"), wxDefaultPosition, wxSize(80, -1), wxSP_ARROW_KEYS, 0, 65535, 0 );
    itemFlexGridSizer228->Add(m_F1Addr, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxLEFT|wxRIGHT, 5);

    m_F1AddrFn = new wxSpinCtrl( m_FunctionPanel, wxID_ANY, wxT("0"), wxDefaultPosition, wxSize(80, -1), wxSP_ARROW_KEYS, 0, 65535, 0 );
    itemFlexGridSizer228->Add(m_F1AddrFn, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxLEFT|wxRIGHT, 5);

    m_Label_f2 = new wxStaticText( m_FunctionPanel, wxID_STATIC_F2, _("f2"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer228->Add(m_Label_f2, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxLEFT|wxRIGHT|wxADJUST_MINSIZE, 2);

    m_f2 = new wxTextCtrl( m_FunctionPanel, ID_TEXTCTRL_F2, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer228->Add(m_f2, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_TimerF2 = new wxSpinCtrl( m_FunctionPanel, wxID_ANY, wxT("0"), wxDefaultPosition, wxSize(70, -1), wxSP_ARROW_KEYS, 0, 1000, 0 );
    itemFlexGridSizer228->Add(m_TimerF2, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);

    m_Button_f2 = new wxButton( m_FunctionPanel, ID_BUTTON_F2, _("..."), wxDefaultPosition, wxSize(40, 25), 0 );
    itemFlexGridSizer228->Add(m_Button_f2, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 2);

    m_Sound2 = new wxTextCtrl( m_FunctionPanel, ID_LOC_SOUND2, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer228->Add(m_Sound2, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_Icon_f2 = new wxTextCtrl( m_FunctionPanel, ID_LOC_ICONF2, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer228->Add(m_Icon_f2, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_F2Addr = new wxSpinCtrl( m_FunctionPanel, wxID_ANY, wxT("0"), wxDefaultPosition, wxSize(80, -1), wxSP_ARROW_KEYS, 0, 65535, 0 );
    itemFlexGridSizer228->Add(m_F2Addr, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxLEFT|wxRIGHT, 5);

    m_F2AddrFn = new wxSpinCtrl( m_FunctionPanel, wxID_ANY, wxT("0"), wxDefaultPosition, wxSize(80, -1), wxSP_ARROW_KEYS, 0, 65535, 0 );
    itemFlexGridSizer228->Add(m_F2AddrFn, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxLEFT|wxRIGHT, 5);

    m_Label_f3 = new wxStaticText( m_FunctionPanel, wxID_STATIC_F3, _("f3"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer228->Add(m_Label_f3, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxLEFT|wxRIGHT|wxADJUST_MINSIZE, 2);

    m_f3 = new wxTextCtrl( m_FunctionPanel, ID_TEXTCTRL_F3, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer228->Add(m_f3, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_TimerF3 = new wxSpinCtrl( m_FunctionPanel, wxID_ANY, wxT("0"), wxDefaultPosition, wxSize(70, -1), wxSP_ARROW_KEYS, 0, 1000, 0 );
    itemFlexGridSizer228->Add(m_TimerF3, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);

    m_Button_f3 = new wxButton( m_FunctionPanel, ID_BUTTON_F3, _("..."), wxDefaultPosition, wxSize(40, 25), 0 );
    itemFlexGridSizer228->Add(m_Button_f3, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 2);

    m_Sound3 = new wxTextCtrl( m_FunctionPanel, ID_LOC_SOUND3, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer228->Add(m_Sound3, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_Icon_f3 = new wxTextCtrl( m_FunctionPanel, ID_LOC_ICONF3, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer228->Add(m_Icon_f3, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_F3Addr = new wxSpinCtrl( m_FunctionPanel, wxID_ANY, wxT("0"), wxDefaultPosition, wxSize(80, -1), wxSP_ARROW_KEYS, 0, 65535, 0 );
    itemFlexGridSizer228->Add(m_F3Addr, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxLEFT|wxRIGHT, 5);

    m_F3AddrFn = new wxSpinCtrl( m_FunctionPanel, wxID_ANY, wxT("0"), wxDefaultPosition, wxSize(80, -1), wxSP_ARROW_KEYS, 0, 65535, 0 );
    itemFlexGridSizer228->Add(m_F3AddrFn, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxLEFT|wxRIGHT, 5);

    m_Label_f4 = new wxStaticText( m_FunctionPanel, wxID_STATIC_F4, _("f4"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer228->Add(m_Label_f4, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxLEFT|wxRIGHT|wxADJUST_MINSIZE, 2);

    m_f4 = new wxTextCtrl( m_FunctionPanel, ID_TEXTCTRL_F4, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer228->Add(m_f4, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_TimerF4 = new wxSpinCtrl( m_FunctionPanel, wxID_ANY, wxT("0"), wxDefaultPosition, wxSize(70, -1), wxSP_ARROW_KEYS, 0, 1000, 0 );
    itemFlexGridSizer228->Add(m_TimerF4, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);

    m_Button_f4 = new wxButton( m_FunctionPanel, ID_BUTTON_F4, _("..."), wxDefaultPosition, wxSize(40, 25), 0 );
    itemFlexGridSizer228->Add(m_Button_f4, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 2);

    m_Sound4 = new wxTextCtrl( m_FunctionPanel, ID_LOC_SOUND4, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer228->Add(m_Sound4, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_Icon_f4 = new wxTextCtrl( m_FunctionPanel, ID_LOC_ICONF4, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer228->Add(m_Icon_f4, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_F4Addr = new wxSpinCtrl( m_FunctionPanel, wxID_ANY, wxT("0"), wxDefaultPosition, wxSize(80, -1), wxSP_ARROW_KEYS, 0, 65535, 0 );
    itemFlexGridSizer228->Add(m_F4Addr, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxLEFT|wxRIGHT, 5);

    m_F4AddrFn = new wxSpinCtrl( m_FunctionPanel, wxID_ANY, wxT("0"), wxDefaultPosition, wxSize(80, -1), wxSP_ARROW_KEYS, 0, 65535, 0 );
    itemFlexGridSizer228->Add(m_F4AddrFn, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxLEFT|wxRIGHT, 5);

    itemFlexGridSizer228->AddGrowableCol(1);

    m_Notebook->AddPage(m_FunctionPanel, _("Functions"));

    m_ConsistsPanel = new wxPanel( m_Notebook, ID_PANEL_LOC_CONSIST, wxDefaultPosition, wxDefaultSize, wxSUNKEN_BORDER|wxTAB_TRAVERSAL );
    wxBoxSizer* itemBoxSizer270 = new wxBoxSizer(wxVERTICAL);
    m_ConsistsPanel->SetSizer(itemBoxSizer270);

    m_labDetails = new wxStaticBox(m_ConsistsPanel, wxID_ANY, _("Details"));
    wxStaticBoxSizer* itemStaticBoxSizer271 = new wxStaticBoxSizer(m_labDetails, wxVERTICAL);
    itemBoxSizer270->Add(itemStaticBoxSizer271, 0, wxGROW|wxALL, 5);
    m_LightsOff = new wxCheckBox( m_ConsistsPanel, ID_CONSTS_LIGHTSOFF, _("Keep lights off"), wxDefaultPosition, wxDefaultSize, 0 );
    m_LightsOff->SetValue(false);
    itemStaticBoxSizer271->Add(m_LightsOff, 0, wxALIGN_LEFT|wxALL, 5);

    m_SyncLights = new wxCheckBox( m_ConsistsPanel, ID_MU_SYNCLIGHTS, _("Synchronize lights"), wxDefaultPosition, wxDefaultSize, 0 );
    m_SyncLights->SetValue(false);
    itemStaticBoxSizer271->Add(m_SyncLights, 0, wxALIGN_LEFT|wxALL, 5);

    m_SyncFun = new wxCheckBox( m_ConsistsPanel, wxID_ANY, _("Synchronise functions"), wxDefaultPosition, wxDefaultSize, 0 );
    m_SyncFun->SetValue(false);
    itemStaticBoxSizer271->Add(m_SyncFun, 0, wxALIGN_LEFT|wxLEFT|wxRIGHT|wxBOTTOM, 5);

    wxFlexGridSizer* itemFlexGridSizer275 = new wxFlexGridSizer(0, 14, 0, 0);
    itemStaticBoxSizer271->Add(itemFlexGridSizer275, 0, wxALIGN_LEFT|wxLEFT, 25);
    wxStaticText* itemStaticText276 = new wxStaticText( m_ConsistsPanel, wxID_ANY, _("1"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer275->Add(itemStaticText276, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);

    wxStaticText* itemStaticText277 = new wxStaticText( m_ConsistsPanel, wxID_ANY, _("2"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer275->Add(itemStaticText277, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);

    wxStaticText* itemStaticText278 = new wxStaticText( m_ConsistsPanel, wxID_ANY, _("3"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer275->Add(itemStaticText278, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);

    wxStaticText* itemStaticText279 = new wxStaticText( m_ConsistsPanel, wxID_ANY, _("4"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer275->Add(itemStaticText279, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);

    wxStaticText* itemStaticText280 = new wxStaticText( m_ConsistsPanel, wxID_ANY, _("5"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer275->Add(itemStaticText280, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);

    wxStaticText* itemStaticText281 = new wxStaticText( m_ConsistsPanel, wxID_ANY, _("6"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer275->Add(itemStaticText281, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);

    wxStaticText* itemStaticText282 = new wxStaticText( m_ConsistsPanel, wxID_ANY, _("7"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer275->Add(itemStaticText282, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);

    wxStaticText* itemStaticText283 = new wxStaticText( m_ConsistsPanel, wxID_ANY, _("8"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer275->Add(itemStaticText283, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);

    wxStaticText* itemStaticText284 = new wxStaticText( m_ConsistsPanel, wxID_ANY, _("9"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer275->Add(itemStaticText284, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);

    wxStaticText* itemStaticText285 = new wxStaticText( m_ConsistsPanel, wxID_ANY, _("10"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer275->Add(itemStaticText285, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);

    wxStaticText* itemStaticText286 = new wxStaticText( m_ConsistsPanel, wxID_ANY, _("11"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer275->Add(itemStaticText286, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);

    wxStaticText* itemStaticText287 = new wxStaticText( m_ConsistsPanel, wxID_ANY, _("12"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer275->Add(itemStaticText287, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);

    wxStaticText* itemStaticText288 = new wxStaticText( m_ConsistsPanel, wxID_ANY, _("13"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer275->Add(itemStaticText288, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);

    wxStaticText* itemStaticText289 = new wxStaticText( m_ConsistsPanel, wxID_ANY, _("14"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer275->Add(itemStaticText289, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);

    m_FSync1 = new wxCheckBox( m_ConsistsPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
    m_FSync1->SetValue(false);
    itemFlexGridSizer275->Add(m_FSync1, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);

    m_FSync2 = new wxCheckBox( m_ConsistsPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
    m_FSync2->SetValue(false);
    itemFlexGridSizer275->Add(m_FSync2, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);

    m_FSync3 = new wxCheckBox( m_ConsistsPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
    m_FSync3->SetValue(false);
    itemFlexGridSizer275->Add(m_FSync3, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);

    m_FSync4 = new wxCheckBox( m_ConsistsPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
    m_FSync4->SetValue(false);
    itemFlexGridSizer275->Add(m_FSync4, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);

    m_FSync5 = new wxCheckBox( m_ConsistsPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
    m_FSync5->SetValue(false);
    itemFlexGridSizer275->Add(m_FSync5, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);

    m_FSync6 = new wxCheckBox( m_ConsistsPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
    m_FSync6->SetValue(false);
    itemFlexGridSizer275->Add(m_FSync6, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);

    m_FSync7 = new wxCheckBox( m_ConsistsPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
    m_FSync7->SetValue(false);
    itemFlexGridSizer275->Add(m_FSync7, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);

    m_FSync8 = new wxCheckBox( m_ConsistsPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
    m_FSync8->SetValue(false);
    itemFlexGridSizer275->Add(m_FSync8, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);

    m_FSync9 = new wxCheckBox( m_ConsistsPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
    m_FSync9->SetValue(false);
    itemFlexGridSizer275->Add(m_FSync9, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);

    m_FSync10 = new wxCheckBox( m_ConsistsPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
    m_FSync10->SetValue(false);
    itemFlexGridSizer275->Add(m_FSync10, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);

    m_FSync11 = new wxCheckBox( m_ConsistsPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
    m_FSync11->SetValue(false);
    itemFlexGridSizer275->Add(m_FSync11, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);

    m_FSync12 = new wxCheckBox( m_ConsistsPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
    m_FSync12->SetValue(false);
    itemFlexGridSizer275->Add(m_FSync12, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);

    m_FSync13 = new wxCheckBox( m_ConsistsPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
    m_FSync13->SetValue(false);
    itemFlexGridSizer275->Add(m_FSync13, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);

    m_FSync14 = new wxCheckBox( m_ConsistsPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
    m_FSync14->SetValue(false);
    itemFlexGridSizer275->Add(m_FSync14, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);

    wxStaticText* itemStaticText304 = new wxStaticText( m_ConsistsPanel, wxID_ANY, _("15"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer275->Add(itemStaticText304, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);

    wxStaticText* itemStaticText305 = new wxStaticText( m_ConsistsPanel, wxID_ANY, _("16"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer275->Add(itemStaticText305, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);

    wxStaticText* itemStaticText306 = new wxStaticText( m_ConsistsPanel, wxID_ANY, _("17"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer275->Add(itemStaticText306, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);

    wxStaticText* itemStaticText307 = new wxStaticText( m_ConsistsPanel, wxID_ANY, _("18"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer275->Add(itemStaticText307, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);

    wxStaticText* itemStaticText308 = new wxStaticText( m_ConsistsPanel, wxID_ANY, _("19"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer275->Add(itemStaticText308, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);

    wxStaticText* itemStaticText309 = new wxStaticText( m_ConsistsPanel, wxID_ANY, _("20"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer275->Add(itemStaticText309, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);

    wxStaticText* itemStaticText310 = new wxStaticText( m_ConsistsPanel, wxID_ANY, _("21"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer275->Add(itemStaticText310, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);

    wxStaticText* itemStaticText311 = new wxStaticText( m_ConsistsPanel, wxID_ANY, _("22"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer275->Add(itemStaticText311, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);

    wxStaticText* itemStaticText312 = new wxStaticText( m_ConsistsPanel, wxID_ANY, _("23"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer275->Add(itemStaticText312, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);

    wxStaticText* itemStaticText313 = new wxStaticText( m_ConsistsPanel, wxID_ANY, _("24"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer275->Add(itemStaticText313, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);

    wxStaticText* itemStaticText314 = new wxStaticText( m_ConsistsPanel, wxID_ANY, _("25"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer275->Add(itemStaticText314, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);

    wxStaticText* itemStaticText315 = new wxStaticText( m_ConsistsPanel, wxID_ANY, _("26"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer275->Add(itemStaticText315, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);

    wxStaticText* itemStaticText316 = new wxStaticText( m_ConsistsPanel, wxID_ANY, _("27"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer275->Add(itemStaticText316, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);

    wxStaticText* itemStaticText317 = new wxStaticText( m_ConsistsPanel, wxID_ANY, _("28"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer275->Add(itemStaticText317, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);

    m_FSync15 = new wxCheckBox( m_ConsistsPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
    m_FSync15->SetValue(false);
    itemFlexGridSizer275->Add(m_FSync15, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);

    m_FSync16 = new wxCheckBox( m_ConsistsPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
    m_FSync16->SetValue(false);
    itemFlexGridSizer275->Add(m_FSync16, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);

    m_FSync17 = new wxCheckBox( m_ConsistsPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
    m_FSync17->SetValue(false);
    itemFlexGridSizer275->Add(m_FSync17, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);

    m_FSync18 = new wxCheckBox( m_ConsistsPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
    m_FSync18->SetValue(false);
    itemFlexGridSizer275->Add(m_FSync18, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);

    m_FSync19 = new wxCheckBox( m_ConsistsPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
    m_FSync19->SetValue(false);
    itemFlexGridSizer275->Add(m_FSync19, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);

    m_FSync20 = new wxCheckBox( m_ConsistsPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
    m_FSync20->SetValue(false);
    itemFlexGridSizer275->Add(m_FSync20, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);

    m_FSync21 = new wxCheckBox( m_ConsistsPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
    m_FSync21->SetValue(false);
    itemFlexGridSizer275->Add(m_FSync21, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);

    m_FSync22 = new wxCheckBox( m_ConsistsPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
    m_FSync22->SetValue(false);
    itemFlexGridSizer275->Add(m_FSync22, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);

    m_FSync23 = new wxCheckBox( m_ConsistsPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
    m_FSync23->SetValue(false);
    itemFlexGridSizer275->Add(m_FSync23, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);

    m_FSync24 = new wxCheckBox( m_ConsistsPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
    m_FSync24->SetValue(false);
    itemFlexGridSizer275->Add(m_FSync24, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);

    m_FSync25 = new wxCheckBox( m_ConsistsPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
    m_FSync25->SetValue(false);
    itemFlexGridSizer275->Add(m_FSync25, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);

    m_FSync26 = new wxCheckBox( m_ConsistsPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
    m_FSync26->SetValue(false);
    itemFlexGridSizer275->Add(m_FSync26, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);

    m_FSync27 = new wxCheckBox( m_ConsistsPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
    m_FSync27->SetValue(false);
    itemFlexGridSizer275->Add(m_FSync27, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);

    m_FSync28 = new wxCheckBox( m_ConsistsPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
    m_FSync28->SetValue(false);
    itemFlexGridSizer275->Add(m_FSync28, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);

    wxStaticLine* itemStaticLine332 = new wxStaticLine( m_ConsistsPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
    itemBoxSizer270->Add(itemStaticLine332, 0, wxGROW|wxALL, 5);

    m_labConsistList = new wxStaticText( m_ConsistsPanel, wxID_ANY, _("Locomotives"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer270->Add(m_labConsistList, 0, wxALIGN_LEFT|wxALL, 5);

    wxArrayString m_ConsistListStrings;
    m_ConsistList = new wxListBox( m_ConsistsPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_ConsistListStrings, wxLB_SINGLE );
    itemBoxSizer270->Add(m_ConsistList, 1, wxGROW|wxALL, 5);

    wxFlexGridSizer* itemFlexGridSizer335 = new wxFlexGridSizer(0, 2, 0, 0);
    itemBoxSizer270->Add(itemFlexGridSizer335, 0, wxGROW|wxALL, 5);
    m_labConsistLocID = new wxStaticText( m_ConsistsPanel, wxID_ANY, _("LocID"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer335->Add(m_labConsistLocID, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxArrayString m_ConsistLocIDStrings;
    m_ConsistLocID = new wxComboBox( m_ConsistsPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, m_ConsistLocIDStrings, wxCB_DROPDOWN );
    itemFlexGridSizer335->Add(m_ConsistLocID, 1, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    itemFlexGridSizer335->AddGrowableCol(1);

    wxBoxSizer* itemBoxSizer338 = new wxBoxSizer(wxHORIZONTAL);
    itemBoxSizer270->Add(itemBoxSizer338, 0, wxGROW|wxALL, 5);
    m_AddConsistLoc = new wxButton( m_ConsistsPanel, ID_BUTTON_LOC_CONSIST_ADD, _("Add"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer338->Add(m_AddConsistLoc, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_DeleteConsistLoc = new wxButton( m_ConsistsPanel, ID_BUTTON_LOC_CONSIST_DELETE, _("Delete"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer338->Add(m_DeleteConsistLoc, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_Notebook->AddPage(m_ConsistsPanel, _("Consists"));

    m_CVPanel = new wxPanel( m_Notebook, ID_PANEL_LOC_CV, wxDefaultPosition, wxDefaultSize, wxSUNKEN_BORDER|wxTAB_TRAVERSAL );
    wxBoxSizer* itemBoxSizer342 = new wxBoxSizer(wxVERTICAL);
    m_CVPanel->SetSizer(itemBoxSizer342);

    m_CVList = new wxGrid( m_CVPanel, ID_GRID_LOC_CV, wxDefaultPosition, wxSize(200, 150), wxSUNKEN_BORDER|wxHSCROLL|wxVSCROLL );
    m_CVList->SetDefaultColSize(50);
    m_CVList->SetDefaultRowSize(25);
    m_CVList->SetColLabelSize(25);
    m_CVList->SetRowLabelSize(50);
    m_CVList->CreateGrid(1, 3, wxGrid::wxGridSelectCells);
    itemBoxSizer342->Add(m_CVList, 1, wxGROW|wxALL, 5);

    wxFlexGridSizer* itemFlexGridSizer344 = new wxFlexGridSizer(0, 2, 0, 0);
    itemBoxSizer342->Add(itemFlexGridSizer344, 0, wxGROW|wxALL, 5);
    m_labCVDesc = new wxStaticText( m_CVPanel, wxID_ANY, _("Description"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer344->Add(m_labCVDesc, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_CVDescription = new wxTextCtrl( m_CVPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer344->Add(m_CVDescription, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_CVDescModify = new wxButton( m_CVPanel, ID_BUTTON_LC_CV_DESC, _("Modify"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer344->Add(m_CVDescModify, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxLEFT|wxRIGHT|wxBOTTOM, 5);

    itemFlexGridSizer344->AddGrowableCol(1);

    m_Notebook->AddPage(m_CVPanel, _("CV"));

    m_BBTPanel = new wxPanel( m_Notebook, ID_PANEL_LOC_BBT, wxDefaultPosition, wxDefaultSize, wxSUNKEN_BORDER|wxTAB_TRAVERSAL );
    wxBoxSizer* itemBoxSizer349 = new wxBoxSizer(wxVERTICAL);
    m_BBTPanel->SetSizer(itemBoxSizer349);

    wxBoxSizer* itemBoxSizer350 = new wxBoxSizer(wxHORIZONTAL);
    itemBoxSizer349->Add(itemBoxSizer350, 0, wxALIGN_LEFT, 5);
    wxFlexGridSizer* itemFlexGridSizer351 = new wxFlexGridSizer(0, 3, 0, 0);
    itemBoxSizer350->Add(itemFlexGridSizer351, 0, wxALIGN_CENTER_VERTICAL, 5);
    m_labBBTSteps = new wxStaticText( m_BBTPanel, wxID_ANY, _("Steps"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer351->Add(m_labBBTSteps, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_BBTSteps = new wxSpinCtrl( m_BBTPanel, wxID_ANY, wxT("10"), wxDefaultPosition, wxSize(100, -1), wxSP_ARROW_KEYS, 4, 16, 10 );
    itemFlexGridSizer351->Add(m_BBTSteps, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_labBBTStepsDummy = new wxStaticText( m_BBTPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer351->Add(m_labBBTStepsDummy, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_labBBTStartInterval = new wxStaticText( m_BBTPanel, wxID_ANY, _("Start interval"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer351->Add(m_labBBTStartInterval, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxLEFT|wxRIGHT|wxBOTTOM, 5);

    m_BBTStartInterval = new wxSpinCtrl( m_BBTPanel, wxID_ANY, wxT("10"), wxDefaultPosition, wxSize(100, -1), wxSP_ARROW_KEYS, 10, 250, 10 );
    itemFlexGridSizer351->Add(m_BBTStartInterval, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxLEFT|wxRIGHT|wxBOTTOM, 5);

    wxStaticText* itemStaticText357 = new wxStaticText( m_BBTPanel, wxID_ANY, _("* 10ms"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer351->Add(itemStaticText357, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxRIGHT|wxBOTTOM, 5);

    m_labBBTMaxDiff = new wxStaticText( m_BBTPanel, wxID_ANY, _("Max. difference"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer351->Add(m_labBBTMaxDiff, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxLEFT|wxRIGHT|wxBOTTOM, 5);

    m_BBTMaxDiff = new wxSpinCtrl( m_BBTPanel, wxID_ANY, wxT("250"), wxDefaultPosition, wxSize(100, -1), wxSP_ARROW_KEYS, 10, 500, 250 );
    itemFlexGridSizer351->Add(m_BBTMaxDiff, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxLEFT|wxRIGHT|wxBOTTOM, 5);

    m_labBBT10ms = new wxStaticText( m_BBTPanel, wxID_ANY, _("* 10ms"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer351->Add(m_labBBT10ms, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxRIGHT|wxBOTTOM, 5);

    m_labBBTCorrection = new wxStaticText( m_BBTPanel, wxID_ANY, _("Correction"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer351->Add(m_labBBTCorrection, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxLEFT|wxRIGHT|wxBOTTOM, 5);

    m_BBTCorrection = new wxSpinCtrl( m_BBTPanel, wxID_ANY, wxT("25"), wxDefaultPosition, wxSize(100, -1), wxSP_ARROW_KEYS, 10, 100, 25 );
    itemFlexGridSizer351->Add(m_BBTCorrection, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxLEFT|wxRIGHT|wxBOTTOM, 5);

    m_labBBTPer = new wxStaticText( m_BBTPanel, wxID_ANY, _("%"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer351->Add(m_labBBTPer, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxRIGHT|wxBOTTOM, 5);

    itemFlexGridSizer351->AddGrowableCol(1);

    wxArrayString m_BBTKeyStrings;
    m_BBTKeyStrings.Add(_("&Block"));
    m_BBTKeyStrings.Add(_("&Fromblock"));
    m_BBTKeyStrings.Add(_("&Route"));
    m_BBTKeyStrings.Add(_("&Speed"));
    m_BBTKey = new wxRadioBox( m_BBTPanel, wxID_ANY, _("Key"), wxDefaultPosition, wxDefaultSize, m_BBTKeyStrings, 1, wxRA_SPECIFY_COLS );
    m_BBTKey->SetSelection(0);
    itemBoxSizer350->Add(m_BBTKey, 0, wxALIGN_TOP|wxALL, 5);

    wxStaticLine* itemStaticLine365 = new wxStaticLine( m_BBTPanel, wxID_STATIC, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
    itemBoxSizer349->Add(itemStaticLine365, 0, wxGROW|wxALL, 5);

    m_labBBTCalculation = new wxStaticText( m_BBTPanel, wxID_ANY, _("Calculation"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer349->Add(m_labBBTCalculation, 0, wxALIGN_CENTER_HORIZONTAL|wxLEFT|wxRIGHT|wxTOP, 5);

    m_BBTList2 = new wxListCtrl( m_BBTPanel, ID_LOC_BBTLIST2, wxDefaultPosition, wxSize(100, 100), wxLC_REPORT|wxLC_HRULES );
    itemBoxSizer349->Add(m_BBTList2, 1, wxGROW|wxALL, 5);

    wxFlexGridSizer* itemFlexGridSizer368 = new wxFlexGridSizer(0, 8, 0, 0);
    itemBoxSizer349->Add(itemFlexGridSizer368, 0, wxGROW, 5);
    m_labBBTFromBlock = new wxStaticText( m_BBTPanel, wxID_ANY, _("From block"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer368->Add(m_labBBTFromBlock, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxLEFT|wxTOP|wxBOTTOM, 5);

    wxArrayString m_BBTFromBlockStrings;
    m_BBTFromBlock = new wxComboBox( m_BBTPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, m_BBTFromBlockStrings, wxCB_DROPDOWN );
    itemFlexGridSizer368->Add(m_BBTFromBlock, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxLEFT|wxRIGHT, 5);

    m_labBBTBlock = new wxStaticText( m_BBTPanel, wxID_ANY, _("Block"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer368->Add(m_labBBTBlock, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxLEFT|wxTOP|wxBOTTOM, 5);

    wxArrayString m_BBTBlockStrings;
    m_BBTBlock = new wxComboBox( m_BBTPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, m_BBTBlockStrings, wxCB_DROPDOWN );
    itemFlexGridSizer368->Add(m_BBTBlock, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxLEFT|wxRIGHT, 5);

    m_labBBTInterval = new wxStaticText( m_BBTPanel, wxID_ANY, _("Interval"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer368->Add(m_labBBTInterval, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxLEFT|wxTOP|wxBOTTOM, 5);

    m_BBTInterval = new wxSpinCtrl( m_BBTPanel, wxID_ANY, wxT("0"), wxDefaultPosition, wxSize(100, -1), wxSP_ARROW_KEYS, 0, 65535, 0 );
    itemFlexGridSizer368->Add(m_BBTInterval, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxLEFT|wxRIGHT, 5);

    m_labBBTRoute = new wxStaticText( m_BBTPanel, wxID_ANY, _("Route"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer368->Add(m_labBBTRoute, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxLEFT|wxTOP|wxBOTTOM, 5);

    wxArrayString m_BBTRouteStrings;
    m_BBTRoute = new wxComboBox( m_BBTPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, m_BBTRouteStrings, wxCB_DROPDOWN );
    itemFlexGridSizer368->Add(m_BBTRoute, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxLEFT|wxRIGHT, 5);

    m_labBBTSpeed = new wxStaticText( m_BBTPanel, wxID_ANY, _("Speed"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer368->Add(m_labBBTSpeed, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxLEFT|wxTOP|wxBOTTOM, 5);

    m_BBTSpeed = new wxSpinCtrl( m_BBTPanel, wxID_ANY, wxT("0"), wxDefaultPosition, wxSize(80, -1), wxSP_ARROW_KEYS, 0, 1000, 0 );
    itemFlexGridSizer368->Add(m_BBTSpeed, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxLEFT|wxRIGHT, 5);

    m_labBBTDelay = new wxStaticText( m_BBTPanel, wxID_ANY, _("Delay"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer368->Add(m_labBBTDelay, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxLEFT|wxTOP|wxBOTTOM, 5);

    m_BBTDelay = new wxSpinCtrl( m_BBTPanel, wxID_ANY, wxT("0"), wxDefaultPosition, wxSize(65, -1), wxSP_ARROW_KEYS, 0, 1000, 0 );
    itemFlexGridSizer368->Add(m_BBTDelay, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxLEFT|wxRIGHT, 5);

    itemFlexGridSizer368->AddGrowableCol(1);
    itemFlexGridSizer368->AddGrowableCol(3);
    itemFlexGridSizer368->AddGrowableCol(7);

    wxBoxSizer* itemBoxSizer381 = new wxBoxSizer(wxHORIZONTAL);
    itemBoxSizer349->Add(itemBoxSizer381, 0, wxALIGN_LEFT|wxALL, 5);
    m_BBTAdd = new wxButton( m_BBTPanel, ID_BBT_ADD, _("Add"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer381->Add(m_BBTAdd, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_BBTDelete = new wxButton( m_BBTPanel, ID_BUTTON_BBT_DELETE, _("Delete"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer381->Add(m_BBTDelete, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_BBTCopy = new wxButton( m_BBTPanel, ID_BBT_COPY, _("Copy"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer381->Add(m_BBTCopy, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_BBTDeleteAll = new wxButton( m_BBTPanel, ID_BUTTON_BBT_DELETEALL, _("Delete all"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer381->Add(m_BBTDeleteAll, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_BBTModify = new wxButton( m_BBTPanel, ID_BBT_MODIFY, _("Modify"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer381->Add(m_BBTModify, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_BBTExport = new wxButton( m_BBTPanel, ID_BBT_EXPORT, _("Export"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer381->Add(m_BBTExport, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_BBTImport = new wxButton( m_BBTPanel, ID_BBT_IMPORT, _("Import"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer381->Add(m_BBTImport, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_BBTFixAll = new wxButton( m_BBTPanel, ID_BBT_FIXALL, _("Fix all"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer381->Add(m_BBTFixAll, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_BBTFixed = new wxCheckBox( m_BBTPanel, wxID_ANY, _("Fixed"), wxDefaultPosition, wxDefaultSize, 0 );
    m_BBTFixed->SetValue(false);
    itemBoxSizer381->Add(m_BBTFixed, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_BBTGenerateIn = new wxCheckBox( m_BBTPanel, ID_BBT_GENATE_IN, _("Generate IN"), wxDefaultPosition, wxDefaultSize, 0 );
    m_BBTGenerateIn->SetValue(false);
    itemBoxSizer381->Add(m_BBTGenerateIn, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_Notebook->AddPage(m_BBTPanel, _("BBT"));

    m_SBTPanel = new wxPanel( m_Notebook, ID_PANEL_LOC_SBT, wxDefaultPosition, wxDefaultSize, wxSUNKEN_BORDER|wxTAB_TRAVERSAL );
    wxBoxSizer* itemBoxSizer393 = new wxBoxSizer(wxVERTICAL);
    m_SBTPanel->SetSizer(itemBoxSizer393);

    m_SBTDefaultBox = new wxStaticBox(m_SBTPanel, wxID_ANY, _("Default"));
    wxStaticBoxSizer* itemStaticBoxSizer394 = new wxStaticBoxSizer(m_SBTDefaultBox, wxVERTICAL);
    itemBoxSizer393->Add(itemStaticBoxSizer394, 0, wxALIGN_LEFT|wxALL, 5);
    wxFlexGridSizer* itemFlexGridSizer395 = new wxFlexGridSizer(0, 2, 0, 0);
    itemStaticBoxSizer394->Add(itemFlexGridSizer395, 0, wxGROW, 5);
    m_labDecelerate = new wxStaticText( m_SBTPanel, wxID_ANY, _("Decelerate"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer395->Add(m_labDecelerate, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_Decelerate = new wxSpinCtrl( m_SBTPanel, wxID_ANY, wxT("0"), wxDefaultPosition, wxSize(80, -1), wxSP_ARROW_KEYS, 0, 50, 0 );
    itemFlexGridSizer395->Add(m_Decelerate, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_LabelV_step = new wxStaticText( m_SBTPanel, wxID_STATIC_LOC_V_STEP, _("V_step:"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer395->Add(m_LabelV_step, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL|wxADJUST_MINSIZE, 2);

    wxFlexGridSizer* itemFlexGridSizer399 = new wxFlexGridSizer(0, 2, 0, 0);
    itemFlexGridSizer395->Add(itemFlexGridSizer399, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    m_Accel = new wxSpinCtrl( m_SBTPanel, wxID_ANY, wxT("0"), wxDefaultPosition, wxSize(80, -1), wxSP_ARROW_KEYS, 0, 10, 0 );
    itemFlexGridSizer399->Add(m_Accel, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticText* itemStaticText401 = new wxStaticText( m_SBTPanel, wxID_ANY, _("* 100ms"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer399->Add(itemStaticText401, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxRIGHT|wxTOP|wxBOTTOM, 5);

    wxStaticText* itemStaticText402 = new wxStaticText( m_SBTPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer395->Add(itemStaticText402, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_Regulated = new wxCheckBox( m_SBTPanel, ID_LOC_REGULATED, _("regulated"), wxDefaultPosition, wxDefaultSize, 0 );
    m_Regulated->SetValue(false);
    itemFlexGridSizer395->Add(m_Regulated, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 2);

    itemFlexGridSizer395->AddGrowableCol(1);

    m_SBTList2 = new wxListCtrl( m_SBTPanel, ID_SBT_LIST, wxDefaultPosition, wxSize(100, 100), wxLC_REPORT|wxLC_SINGLE_SEL|wxLC_HRULES );
    itemBoxSizer393->Add(m_SBTList2, 1, wxGROW|wxALL, 5);

    wxFlexGridSizer* itemFlexGridSizer405 = new wxFlexGridSizer(0, 8, 0, 0);
    itemBoxSizer393->Add(itemFlexGridSizer405, 0, wxGROW|wxALL, 5);
    m_labSBTBlock = new wxStaticText( m_SBTPanel, wxID_ANY, _("Block"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer405->Add(m_labSBTBlock, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxLEFT|wxTOP|wxBOTTOM, 5);

    wxArrayString m_SBTBlockStrings;
    m_SBTBlock = new wxComboBox( m_SBTPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, m_SBTBlockStrings, wxCB_DROPDOWN );
    itemFlexGridSizer405->Add(m_SBTBlock, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_labSBTTrain = new wxStaticText( m_SBTPanel, wxID_ANY, _("Train"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer405->Add(m_labSBTTrain, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxLEFT|wxTOP|wxBOTTOM, 5);

    wxArrayString m_SBTTrainStrings;
    m_SBTTrain = new wxComboBox( m_SBTPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, m_SBTTrainStrings, wxCB_DROPDOWN );
    itemFlexGridSizer405->Add(m_SBTTrain, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_labSBTInterval = new wxStaticText( m_SBTPanel, wxID_ANY, _("Interval"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer405->Add(m_labSBTInterval, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxLEFT|wxTOP|wxBOTTOM, 5);

    m_SBTInterval = new wxSpinCtrl( m_SBTPanel, wxID_ANY, wxT("0"), wxDefaultPosition, wxSize(80, -1), wxSP_ARROW_KEYS, 0, 10, 0 );
    itemFlexGridSizer405->Add(m_SBTInterval, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxLEFT|wxRIGHT, 5);

    m_labSBTDecelerate = new wxStaticText( m_SBTPanel, wxID_ANY, _("Decelerate"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer405->Add(m_labSBTDecelerate, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxLEFT|wxTOP|wxBOTTOM, 5);

    m_SBTDecelerate = new wxSpinCtrl( m_SBTPanel, wxID_ANY, wxT("0"), wxDefaultPosition, wxSize(80, -1), wxSP_ARROW_KEYS, 0, 50, 0 );
    itemFlexGridSizer405->Add(m_SBTDecelerate, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxLEFT|wxRIGHT, 5);

    itemFlexGridSizer405->AddGrowableCol(1);
    itemFlexGridSizer405->AddGrowableCol(3);

    wxBoxSizer* itemBoxSizer414 = new wxBoxSizer(wxHORIZONTAL);
    itemBoxSizer393->Add(itemBoxSizer414, 0, wxALIGN_LEFT|wxALL, 5);
    m_SBTAdd = new wxButton( m_SBTPanel, ID_SBT_ADD, _("Add"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer414->Add(m_SBTAdd, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_SBTDelete = new wxButton( m_SBTPanel, ID_SBT_DELETE, _("Delete"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer414->Add(m_SBTDelete, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_SBTModify = new wxButton( m_SBTPanel, ID_SBT_MODIFY, _("Modify"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer414->Add(m_SBTModify, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_Notebook->AddPage(m_SBTPanel, _("SBT"));

    itemBoxSizer2->Add(m_Notebook, 1, wxGROW|wxALL, 5);

    wxStdDialogButtonSizer* itemStdDialogButtonSizer418 = new wxStdDialogButtonSizer;

    itemBoxSizer2->Add(itemStdDialogButtonSizer418, 0, wxGROW|wxALL, 5);
    m_Cancel = new wxButton( itemDialog1, wxID_CANCEL, _("&Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
    itemStdDialogButtonSizer418->AddButton(m_Cancel);

    m_Apply = new wxButton( itemDialog1, wxID_APPLY, _("&Apply"), wxDefaultPosition, wxDefaultSize, 0 );
    itemStdDialogButtonSizer418->AddButton(m_Apply);

    m_OK = new wxButton( itemDialog1, wxID_OK, _("&OK"), wxDefaultPosition, wxDefaultSize, 0 );
    m_OK->SetDefault();
    itemStdDialogButtonSizer418->AddButton(m_OK);

    wxButton* itemButton422 = new wxButton( itemDialog1, wxID_HELP, _("&Help"), wxDefaultPosition, wxDefaultSize, 0 );
    itemStdDialogButtonSizer418->AddButton(itemButton422);

    itemStdDialogButtonSizer418->Realize();

    // Connect events and objects
    m_label_ID->Connect(ID_ABOX_ID, wxEVT_LEFT_UP, wxMouseEventHandler(LocDialog::OnAboxID), NULL, this);
    m_labIdent->Connect(ID_ABOX_IDENT, wxEVT_LEFT_UP, wxMouseEventHandler(LocDialog::OnAboxIdent), NULL, this);
    m_labRoadname->Connect(ID_ABOX_ROADNAME, wxEVT_LEFT_UP, wxMouseEventHandler(LocDialog::OnAboxRoadname), NULL, this);
    m_Label_CatalogNr->Connect(ID_ABOX_CATNR, wxEVT_LEFT_UP, wxMouseEventHandler(LocDialog::OnAboxCatnr), NULL, this);
    m_labDecType->Connect(ID_ABOX_DECODERTYPE, wxEVT_LEFT_UP, wxMouseEventHandler(LocDialog::onABoxDecoderType), NULL, this);
    m_F0Icon->Connect(ID_LOC_ICONF0, wxEVT_LEFT_DCLICK, wxMouseEventHandler(LocDialog::OnLocIconf0), NULL, this);
    m_Sound1->Connect(ID_LOC_SOUND1, wxEVT_LEFT_DCLICK, wxMouseEventHandler(LocDialog::OnLocSound1), NULL, this);
    m_Icon_f1->Connect(ID_LOC_ICONF1, wxEVT_LEFT_DCLICK, wxMouseEventHandler(LocDialog::OnLocIconf1), NULL, this);
    m_Sound2->Connect(ID_LOC_SOUND2, wxEVT_LEFT_DCLICK, wxMouseEventHandler(LocDialog::OnLocSound2), NULL, this);
    m_Icon_f2->Connect(ID_LOC_ICONF2, wxEVT_LEFT_DCLICK, wxMouseEventHandler(LocDialog::OnLocIconf2), NULL, this);
    m_Sound3->Connect(ID_LOC_SOUND3, wxEVT_LEFT_DCLICK, wxMouseEventHandler(LocDialog::OnLocSound3), NULL, this);
    m_Icon_f3->Connect(ID_LOC_ICONF3, wxEVT_LEFT_DCLICK, wxMouseEventHandler(LocDialog::OnLocIconf3), NULL, this);
    m_Sound4->Connect(ID_LOC_SOUND4, wxEVT_LEFT_DCLICK, wxMouseEventHandler(LocDialog::OnLocSound4), NULL, this);
    m_Icon_f4->Connect(ID_LOC_ICONF4, wxEVT_LEFT_DCLICK, wxMouseEventHandler(LocDialog::OnLocIconf4), NULL, this);
////@end LocDialog content construction
}

/*!
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_CANCEL
 */

void LocDialog::OnCancelClick( wxCommandEvent& event )
{
  if( m_BBTList != NULL ) {
    ListOp.base.del(m_BBTList);
  }
  EndModal( 0 );
}

/*!
 * Should we show tooltips?
 */

bool LocDialog::ShowToolTips()
{
    return true;
}

/*!
 * Get bitmap resources
 */

/*!
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BUTTON_F1
 */

void LocDialog::OnButtonF1Click( wxCommandEvent& event )
{
  if( m_Props == NULL )
    return;

  FunctionDialog*  funDlg = new FunctionDialog(this, m_Props, 1 + m_iFunGroup*4 );
  funDlg->ShowModal();
}


/*!
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BUTTON_F2
 */

void LocDialog::OnButtonF2Click( wxCommandEvent& event )
{
  if( m_Props == NULL )
    return;

  FunctionDialog*  funDlg = new FunctionDialog(this, m_Props, 2 + m_iFunGroup*4 );
  funDlg->ShowModal();
}


/*!
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BUTTON_F3
 */

void LocDialog::OnButtonF3Click( wxCommandEvent& event )
{
  if( m_Props == NULL )
    return;

  FunctionDialog*  funDlg = new FunctionDialog(this, m_Props, 3 + m_iFunGroup*4 );
  funDlg->ShowModal();
}


/*!
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BUTTON_F4
 */

void LocDialog::OnButtonF4Click( wxCommandEvent& event )
{
  if( m_Props == NULL )
    return;

  FunctionDialog*  funDlg = new FunctionDialog(this, m_Props, 4 + m_iFunGroup*4 );
  funDlg->ShowModal();
}


/*!
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for wxID_APPLY
 */

bool LocDialog::OnApply()
{
  if( m_Props == NULL )
    return false;

  TraceOp.trc( "locdlg", TRCLEVEL_INFO, __LINE__, 9999, "apply" );

  wxCommandEvent event;
  OnBbtModifyClick(event);

  if( !Evaluate() )
    return false;

  InitIndex();
  return true;
}


void LocDialog::OnApplyClick( wxCommandEvent& event )
{
  if( m_bSave && OnApply() ) {
    if( !wxGetApp().isStayOffline() ) {
      /* Notify RocRail. */
      iONode cmd = NodeOp.inst( wModelCmd.name(), NULL, ELEMENT_NODE );
      wModelCmd.setcmd( cmd, wModelCmd.modify );
      NodeOp.addChild( cmd, (iONode)m_Props->base.clone( m_Props ) );
      wxGetApp().sendToRocrail( cmd );
      cmd->base.del(cmd);
    }
    else {
      wxGetApp().setLocalModelModified(true);
    }
  }
}


/*!
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BUTTON3
 */

void LocDialog::OnButtonF0Click( wxCommandEvent& event )
{
  if( m_Props == NULL )
    return;

  FunctionDialog*  funDlg = new FunctionDialog(this, m_Props, 0 );
  funDlg->ShowModal();
}


/*!
 * wxEVT_COMMAND_LISTBOX_SELECTED event handler for ID_LISTBOX
 */

void LocDialog::OnOkClick( wxCommandEvent& event )
{
  if( m_bSave && OnApply() ) {
    if( !wxGetApp().isStayOffline() ) {
      /* Notify RocRail. */
      iONode cmd = NodeOp.inst( wModelCmd.name(), NULL, ELEMENT_NODE );
      wModelCmd.setcmd( cmd, wModelCmd.modify );
      NodeOp.addChild( cmd, (iONode)m_Props->base.clone( m_Props ) );
      wxGetApp().sendToRocrail( cmd );
      cmd->base.del(cmd);
    }
    else {
      wxGetApp().setLocalModelModified(true);
    }
  }
  if( m_BBTList != NULL ) {
    ListOp.base.del(m_BBTList);
  }
  EndModal( wxID_OK );
}


/*!
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BUTTON_LOC_NEW
 */

void LocDialog::OnButtonLocNewClick( wxCommandEvent& event )
{
  int i = findID("NEW");
  if( i == wxNOT_FOUND ) {
    iONode model = wxGetApp().getModel();
    if( model != NULL ) {
      iONode lclist = wPlan.getlclist( model );
      if( lclist == NULL ) {
        lclist = NodeOp.inst( wLocList.name(), model, ELEMENT_NODE );
        NodeOp.addChild( model, lclist );
      }
      if( lclist != NULL ) {
        iONode lc = NodeOp.inst( wLoc.name(), lclist, ELEMENT_NODE );
        NodeOp.addChild( lclist, lc );
        wLoc.setid( lc, "NEW" );
        appendItem(lc);
        setIDSelection(wItem.getid(lc));
        m_Props = lc;
        InitValues();
      }
    }
  }
}

/*!
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BUTTON_DELETE
 */

void LocDialog::OnButtonDeleteClick( wxCommandEvent& event )
{
  if( m_Props == NULL )
    return;

  int action = wxMessageDialog( this, wxGetApp().getMsg("removewarning"), _T("Rocrail"), wxYES_NO | wxICON_EXCLAMATION ).ShowModal();
  if( action == wxID_NO )
    return;

  wxGetApp().pushUndoItem( (iONode)NodeOp.base.clone( m_Props ) );
  /* Notify RocRail. */
  iONode cmd = NodeOp.inst( wModelCmd.name(), NULL, ELEMENT_NODE );
  wModelCmd.setcmd( cmd, wModelCmd.remove );
  NodeOp.addChild( cmd, (iONode)m_Props->base.clone( m_Props ) );
  wxGetApp().sendToRocrail( cmd );
  cmd->base.del(cmd);

  iONode model = wxGetApp().getModel();
  if( model != NULL ) {
    iONode lclist = wPlan.getlclist( model );
    if( lclist != NULL ) {
      NodeOp.removeChild( lclist, m_Props );
      m_Props = selectPrev();
    }
  }

  InitIndex();
}


/*!
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BITMAPBUTTON
 */

void LocDialog::OnBitmapbuttonClick( wxCommandEvent& event )
{
  const char* imagepath = wGui.getimagepath( wxGetApp().getIni() );
  TraceOp.trc( "locdlg", TRCLEVEL_INFO, __LINE__, 9999, "imagepath = [%s]", imagepath );
  wxFileDialog* fdlg = new wxFileDialog(this, _T("Search loco image"),
      wxString(imagepath,wxConvUTF8), _T(""),
      _T("PNG files (*.png)|*.png|GIF files (*.gif)|*.gif|XPM files (*.xpm)|*.xpm"), wxFD_OPEN);
  if( fdlg->ShowModal() == wxID_OK ) {
    TraceOp.trc( "locdlg", TRCLEVEL_INFO, __LINE__, 9999, "Loading %s...", (const char*)fdlg->GetPath().mb_str(wxConvUTF8) );
    wxBitmapType bmptype = wxBITMAP_TYPE_XPM;
    if( StrOp.endsWithi( fdlg->GetPath().mb_str(wxConvUTF8), ".gif" ) )
      bmptype = wxBITMAP_TYPE_GIF;
    else if( StrOp.endsWithi( fdlg->GetPath().mb_str(wxConvUTF8), ".png" ) )
      bmptype = wxBITMAP_TYPE_PNG;
    else {
      TraceOp.trc( "locdlg", TRCLEVEL_WARNING, __LINE__, 9999, "unsupported image format %s", (const char*)fdlg->GetPath().mb_str(wxConvUTF8) );
      return;
    }
    m_LocImage->SetBitmapLabel( wxBitmap( fdlg->GetPath(), bmptype ) );
    m_LocImage->Refresh();
    wLoc.setimage( m_Props, FileOp.ripPath(fdlg->GetPath().mb_str(wxConvUTF8)) );
    m_ImageName->SetValue( wxString( FileOp.ripPath(wLoc.getimage(m_Props)), wxConvUTF8) );
  }
}



/*!
 * Get bitmap resources
 */

wxBitmap LocDialog::GetBitmapResource( const wxString& name )
{
    // Bitmap retrieval
////@begin LocDialog bitmap retrieval
    wxUnusedVar(name);
    return wxNullBitmap;
////@end LocDialog bitmap retrieval
}

/*!
 * Get icon resources
 */

wxIcon LocDialog::GetIconResource( const wxString& name )
{
    // Icon retrieval
////@begin LocDialog icon retrieval
    wxUnusedVar(name);
    return wxNullIcon;
////@end LocDialog icon retrieval
}
/*!
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BITMAPBUTTON_LC_INDEX
 */

void LocDialog::EditFunction( int nr, wxString txt ) {
  TraceOp.trc( "locdlg", TRCLEVEL_INFO, __LINE__, 9999, "EditFunction [%d]", nr );
  Boolean funfound = False;
  iONode fundef = wLoc.getfundef( m_Props );
  while( fundef != NULL ) {
    if( wFunDef.getfn( fundef ) == nr ) {
      wFunDef.settext( fundef, txt.mb_str(wxConvUTF8) );
      funfound = True;
      break;
    }
    fundef = wLoc.nextfundef( m_Props, fundef );
  }
  if( !funfound ) {
    fundef = NodeOp.inst( wFunDef.name(), m_Props, ELEMENT_NODE );
    wFunDef.setfn( fundef, nr );
    wFunDef.settext( fundef, txt.mb_str(wxConvUTF8) );
    NodeOp.addChild( m_Props, fundef );
  }
}



/*!
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BUTTON_LOC_CONSIST_DELETE
 */

void LocDialog::OnButtonLocConsistDeleteClick( wxCommandEvent& event )
{
  int sel = m_ConsistList->GetSelection();
  if( sel != wxNOT_FOUND )
    m_ConsistList->Delete(sel);

}


/*!
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BUTTON_LOC_CONSIST_ADD
 */

void LocDialog::OnButtonLocConsistAddClick( wxCommandEvent& event )
{
  char* id = StrOp.dup(m_ConsistLocID->GetStringSelection().mb_str(wxConvUTF8));
  if( !StrOp.equals( wLoc.getid(m_Props), id ) )
    m_ConsistList->Append( m_ConsistLocID->GetStringSelection() );
  StrOp.free(id);
}

void LocDialog::initCVDesc() {
  for( int i = 0; i < 256; i++ )
    m_CVDesc[i] = "";

  m_CVDesc[  1]  = "Primary Address";
  m_CVDesc[  2]  = "Vstart";
  m_CVDesc[  3]  = "Acceleration Rate";
  m_CVDesc[  4]  = "Deceleration Rate";
  m_CVDesc[  5]  = "Vhigh";
  m_CVDesc[  6]  = "Vmid";
  m_CVDesc[  7]  = "Manufacturer Version No.";
  m_CVDesc[  8]  = "Manufactured ID";
  m_CVDesc[  9]  = "Total PWM Period";
  m_CVDesc[ 10]  = "EMF Feedback Cutout";
  m_CVDesc[ 11]  = "Packet Time-Out Value";
  m_CVDesc[ 12]  = "Power Source Conversion";
  m_CVDesc[ 13]  = "Alternate Mode Function Status F1-F8";
  m_CVDesc[ 14]  = "Alternate Mode Fnc. Status FL,F9-F12";
  m_CVDesc[ 15]  = "Decoder Lock";
  m_CVDesc[ 16]  = "Decoder Lock";
  m_CVDesc[ 17]  = "Extended Address";
  m_CVDesc[ 18]  = "Extended Address";
  m_CVDesc[ 19]  = "Consist Address";
  m_CVDesc[ 20]  = "Reserved by NMRA for future use";
  m_CVDesc[ 21]  = "Consist Addr Active for F1-F8";
  m_CVDesc[ 22]  = "Consist Addr Active for FL-F9-F12";
  m_CVDesc[ 23]  = "Acceleration Adjustment";
  m_CVDesc[ 24]  = "Deceleration Adjustment";
  m_CVDesc[ 25]  = "Speed Table/Mid-range Cab Speed Step";
  m_CVDesc[ 26]  = "Reserved by NMRA for future use";
  m_CVDesc[ 27]  = "Decoder Automatic Stopping Configuration";
  m_CVDesc[ 28]  = "Bi-Directional Communication Configuration";
  m_CVDesc[ 29]  = "Configuration Data #1";
  m_CVDesc[ 30]  = "Error Information";
  m_CVDesc[ 31]  = "Index High Byte";
  m_CVDesc[ 32]  = "Index Low Byte";

}


/*!
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BUTTON_LC_CV_DESC
 */

void LocDialog::OnButtonLcCvDescClick( wxCommandEvent& event )
{
  if( m_iSelectedCV == -1 )
    return;

  wxString str = m_CVList->GetCellValue(m_iSelectedCV, 0 );
  long cvnr = 0;
  str.ToLong(&cvnr);
  if( cvnr < 256 ) {
    iONode cv = m_CVNodes[cvnr];
    wCVByte.setdesc( cv, m_CVDescription->GetValue().mb_str(wxConvUTF8) );
    m_CVList->SetCellValue(m_iSelectedCV, 2, m_CVDescription->GetValue() );
  }
}


/*!
 * wxEVT_GRID_CELL_LEFT_CLICK event handler for ID_GRID_LOC_CV
 */

void LocDialog::OnCVCellLeftClick( wxGridEvent& event )
{
  m_iSelectedCV = event.GetRow();
  if( m_iSelectedCV == -1 )
    return;

  wxString str = m_CVList->GetCellValue( m_iSelectedCV, 2 );
  m_CVDescription->SetValue(str);
  m_CVDescription->Enable(true);
  m_CVDescModify->Enable(true);
  event.Skip();
}




/*!
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BUTTON_F8
 */

void LocDialog::OnButtonLocoDocClick( wxCommandEvent& event )
{
  doDoc( event, "locos" );
}


/*!
 * wxEVT_COMMAND_CHECKBOX_CLICKED event handler for ID_LOC_REGULATED
 */

void LocDialog::OnLocRegulatedClick( wxCommandEvent& event )
{
  int val = atoi( m_SpeedSteps->GetValue().mb_str(wxConvUTF8) );
/*
  if( m_Regulated->IsChecked() ) {
    m_Accel->Enable( false );
  }
  else {
    m_Accel->Enable( true );
  }
  */
}


/*!
 * wxEVT_COMMAND_TEXT_UPDATED event handler for ID_TEXTCTRL_SPEEDSTEPS
 */

void LocDialog::OnTextctrlSpeedstepsTextUpdated( wxCommandEvent& event )
{
  OnLocRegulatedClick(event);
}


/*!
 * wxEVT_COMMAND_TEXT_ENTER event handler for ID_TEXTCTRL_SPEEDSTEPS
 */

void LocDialog::OnTextctrlSpeedstepsEnter( wxCommandEvent& event )
{
  OnLocRegulatedClick(event);
}


/*!
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BUTTON_F12
 */

/*!
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_LC_SERVICED
 */

void LocDialog::OnLcServicedClick( wxCommandEvent& event )
{
  m_MTime->SetValue(m_RunTime->GetValue());
  wLoc.setmtime( m_Props, wLoc.getruntime( m_Props ) );
  wLoc.setmdate( m_Props, time(NULL) );
  m_Serviced->SetBackgroundColour( Base::getGreen() );
  InitValues();
}





/*!
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BUTTON_IMPORTLOCOS
 */

void LocDialog::OnButtonImportlocosClick( wxCommandEvent& event )
{
  wxString ms_FileExt = wxGetApp().getMsg("planfiles");
  Boolean guest = m_GuestImport->IsChecked()?True:False;
  const char* l_openpath = wGui.getopenpath( wxGetApp().getIni() );
  wxFileDialog* fdlg = new wxFileDialog(this, wxGetApp().getMenu("openplanfile"), wxString(l_openpath,wxConvUTF8) , _T(""), ms_FileExt, wxFD_OPEN);
  if( fdlg->ShowModal() == wxID_OK ) {

    wGui.setopenpath( wxGetApp().getIni(), fdlg->GetPath().mb_str(wxConvUTF8) );
    // strip filename:
    wGui.setopenpath( wxGetApp().getIni(), FileOp.getPath(wGui.getopenpath( wxGetApp().getIni() ) ) );

    if( fdlg->GetPath().Len() > 0 && FileOp.exist(fdlg->GetPath().mb_str(wxConvUTF8)) ) {
      iOFile f = FileOp.inst( fdlg->GetPath().mb_str(wxConvUTF8), OPEN_READONLY );
      char* buffer = (char*)allocMem( FileOp.size( f ) +1 );
      FileOp.read( f, buffer, FileOp.size( f ) );
      FileOp.base.del( f );
      iODoc doc = DocOp.parse( buffer );
      if( doc != NULL ) {
        iONode plan = DocOp.getRootNode( doc );
        DocOp.base.del( doc );
        TraceOp.trc( "frame", TRCLEVEL_INFO, __LINE__, 9999, "Plan [%s] is successfully parsed!", (const char*)fdlg->GetPath().mb_str(wxConvUTF8) );

        /* TODO: read all loco's and add them to the list */
        iONode list = NodeOp.findNode( plan, wLocList.name() );

        iONode model = wxGetApp().getModel();
        iONode lclist = NULL;
        if( model != NULL ) {
          lclist = wPlan.getlclist( model );
          if( lclist == NULL ) {
            lclist = NodeOp.inst( wLocList.name(), model, ELEMENT_NODE );
            NodeOp.addChild( model, lclist );
          }
        }

        if( list != NULL ) {
          int i = 0;
          int cnt = NodeOp.getChildCnt( list );
          for( i = 0; i < cnt; i++ ) {
            m_Props = (iONode)NodeOp.base.clone( NodeOp.getChild( list, i ) );
            wItem.setgenerated(m_Props, guest );

            if( model != NULL ) {
              TraceOp.trc( "frame", TRCLEVEL_EXCEPTION, __LINE__, 9999, "adding loco %s", wLoc.getid(m_Props));
              NodeOp.addChild( lclist, m_Props );
              InitValues();
              OnApplyClick(event);
            }
          }
        }


        NodeOp.base.del( plan );
      }
      else {
        TraceOp.trc( "frame", TRCLEVEL_EXCEPTION, __LINE__, 9999, "Plan [%s] is not parseable!", (const char*)fdlg->GetPath().mb_str(wxConvUTF8) );
      }
    }

  }
  fdlg->Destroy();
  m_GuestImport->SetValue(false);
}


/*!
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_LOC_FN_GROUP
 */

void LocDialog::OnLocFnGroupClick( wxCommandEvent& event )
{
  evaluateFunctions();
  m_iFunGroup++;
  if( m_iFunGroup > 6 )
    m_iFunGroup = 0;

  initFunctions();
}


/*!
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_LOC_FN_GROUP_PREV
 */

void LocDialog::OnLocFnGroupPrevClick( wxCommandEvent& event )
{
  evaluateFunctions();
  if( m_iFunGroup > 0 )
    m_iFunGroup--;

  initFunctions();
}


/*!
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_LOC_COPY
 */

void LocDialog::OnLocCopyClick( wxCommandEvent& event )
{
  if( m_Props != NULL ) {
    iONode model = wxGetApp().getModel();
    if( model != NULL ) {
      iONode lclist = wPlan.getlclist( model );
      if( lclist == NULL ) {
        lclist = NodeOp.inst( wLocList.name(), model, ELEMENT_NODE );
        NodeOp.addChild( model, lclist );
      }

      if( lclist != NULL ) {
        iONode lccopy = (iONode)NodeOp.base.clone( m_Props );
        char* id = StrOp.fmt( "%s (copy)", wLoc.getid(lccopy));
        wLoc.setid(lccopy, id);
        wLoc.setruntime(lccopy, 0 );
        wLoc.setmtime(lccopy, 0 );
        wLoc.setmdate(lccopy, 0 );
        StrOp.free(id);
        NodeOp.addChild( lclist, lccopy );
        InitIndex();
      }

    }
  }
}


/*!
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_LOC_ACTIONS
 */

void LocDialog::OnLocActionsClick( wxCommandEvent& event )
{
  if( m_Props == NULL )
    return;

  ActionsCtrlDlg*  dlg = new ActionsCtrlDlg(this, m_Props,
      "run,stop,stall,min,mid,max,cruise,dirchange,lights,eventtimeout,f1,f2,f3,f4,f5,f6,f7,f8,f9,f10,f11,f12,f13,f14,f15,f16,f17,f18,f19,f20,f21,f22,f23,f24,f25,f26,f27,f28" );

  if( wxID_OK == dlg->ShowModal() ) {
    // TODO: inform
  }

  dlg->Destroy();
}


/*!
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BUTTON_SHOWDOC
 */

void LocDialog::OnButtonShowdocClick( wxCommandEvent& event )
{
  wxLaunchDefaultBrowser(m_Documentation->GetValue(), wxBROWSER_NEW_WINDOW );
}


/*!
 * wxEVT_COMMAND_CHECKBOX_CLICKED event handler for wxID_ANY
 */

void LocDialog::OnShowClick( wxCommandEvent& event )
{
  if( m_Props == NULL )
    return;

  TraceOp.trc( "locdlg", TRCLEVEL_INFO, __LINE__, 9999, "show" );

  if( !Evaluate() )
    return;

  if( !wxGetApp().isStayOffline() ) {
    /* Notify RocRail. */
    iONode cmd = NodeOp.inst( wModelCmd.name(), NULL, ELEMENT_NODE );
    wModelCmd.setcmd( cmd, wModelCmd.modify );
    NodeOp.addChild( cmd, (iONode)m_Props->base.clone( m_Props ) );
    wxGetApp().sendToRocrail( cmd );
    cmd->base.del(cmd);
  }
  else {
    wxGetApp().setLocalModelModified(true);
  }
}


/*!
 * wxEVT_COMMAND_CHECKBOX_CLICKED event handler for wxID_ANY
 */

void LocDialog::OnRestoreSpeedClick( wxCommandEvent& event )
{
  OnShowClick(event);
}


/*!
 * wxEVT_COMMAND_CHECKBOX_CLICKED event handler for wxID_ANY
 */

void LocDialog::OnRestoreFxClick( wxCommandEvent& event )
{
  OnShowClick(event);
}


/*!
 * wxEVT_COMMAND_LIST_ITEM_SELECTED event handler for ID_LISTCTRLINDEX
 */

void LocDialog::OnListctrlindexLcSelected( wxListEvent& event )
{
  m_Props = getSelection(event.GetIndex());
  InitValues();
}


/*!
 * wxEVT_COMMAND_LIST_COL_CLICK event handler for ID_LISTCTRLINDEX
 */

void LocDialog::OnListctrlindexLcColLeftClick( wxListEvent& event )
{
  sortOnColumn(event.GetColumn());
}


/*!
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BUTTON_BBT_DELETE
 */

void LocDialog::OnButtonBbtDeleteClick( wxCommandEvent& event )
{
  if( m_Props != NULL) {
    // re-init the list to update the bbt pointers
    sortBBT();
    if(  m_iBBTSel != wxNOT_FOUND ) {
      iONode l_BBTSel = (iONode)ListOp.get(m_BBTList, m_iBBTSel);

      if( l_BBTSel != NULL ) {
        NodeOp.removeChild( m_Props, l_BBTSel );
        l_BBTSel = NULL;
        initBBT();

        if( NodeOp.getChildCnt(m_Props) == 0 ) {
          // ToDo: Work aroud for forcing the loco objects to remove all child nodes...
          iONode node = NodeOp.inst( wCVByte.name(), m_Props, ELEMENT_NODE);
          NodeOp.addChild( m_Props, node );
        }

        if( m_BBTList2->GetItemCount() == 0 ) {
          m_BBTDelete->Enable(false);
          m_BBTDeleteAll->Enable(false);
        }
      }
    }
  }
}


/*!
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BUTTON_BBT_DELETEALL
 */

void LocDialog::OnButtonBbtDeleteallClick( wxCommandEvent& event )
{
  if( m_Props != NULL ) {
    iONode bbt = wLoc.getbbt( m_Props );
    while( bbt != NULL ) {
      NodeOp.removeChild( m_Props, bbt );
      NodeOp.base.del(bbt);
      bbt = wLoc.getbbt( m_Props );
    };

    if( NodeOp.getChildCnt(m_Props) == 0 ) {
      // ToDo: Work aroud for forcing the loco objects to remove all child nodes...
      iONode node = NodeOp.inst( wCVByte.name(), m_Props, ELEMENT_NODE);
      NodeOp.addChild( m_Props, node );
    }
    initBBT();
    m_BBTDelete->Enable(false);
    m_BBTDeleteAll->Enable(false);
  }
}


/*!
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BBT_MODIFY
 */

void LocDialog::OnBbtModifyClick( wxCommandEvent& event )
{
  if( m_Props != NULL && m_iBBTSel != wxNOT_FOUND) {
    // re-init the list to update the bbt pointers
    sortBBT();
    iONode l_BBTSel = (iONode)ListOp.get(m_BBTList, m_iBBTSel);

    TraceOp.trc( "locdlg", TRCLEVEL_INFO, __LINE__, 9999, "l_BBTSel=%lx", l_BBTSel );
    wBBT.setinterval(l_BBTSel, m_BBTInterval->GetValue());
    TraceOp.trc( "locdlg", TRCLEVEL_INFO, __LINE__, 9999, "l_BBTSel=%lx", l_BBTSel );
    wBBT.setfixed(l_BBTSel, m_BBTFixed->IsChecked()?True:False);
    wBBT.setgeneratein(l_BBTSel, m_BBTGenerateIn->IsChecked()?True:False);
    wBBT.setfrombk(l_BBTSel, m_BBTFromBlock->GetValue().mb_str(wxConvUTF8));
    wBBT.setroute(l_BBTSel, m_BBTRoute->GetValue().mb_str(wxConvUTF8));
    wBBT.setbk(l_BBTSel, m_BBTBlock->GetValue().mb_str(wxConvUTF8));
    wBBT.setspeed(l_BBTSel, m_BBTSpeed->GetValue());
    wBBT.setdelay(l_BBTSel, m_BBTDelay->GetValue());

    int sel = m_iBBTSel;
    initBBT();
    m_iBBTSel = sel;
    m_BBTList2->SetItemState(m_iBBTSel, wxLIST_STATE_SELECTED, wxLIST_STATE_SELECTED);
  }
}


/*!
 * wxEVT_COMMAND_LIST_ITEM_SELECTED event handler for ID_LOC_BBTLIST2
 */

void LocDialog::OnLocBbtlist2Selected( wxListEvent& event )
{
  if( m_Props != NULL ) {
    m_iBBTSel = event.GetIndex();
    if( m_iBBTSel != wxNOT_FOUND) {
      sortBBT();
      iONode l_BBTSel = (iONode)ListOp.get(m_BBTList, m_iBBTSel);
      TraceOp.trc( "locdlg", TRCLEVEL_INFO, __LINE__, 9999, "selected bbt=%d node=%lx", m_iBBTSel, l_BBTSel );
      m_BBTDelete->Enable(true);
      m_BBTCopy->Enable(true);
      m_BBTBlock->SetValue( wxString(wBBT.getbk(l_BBTSel),wxConvUTF8));
      m_BBTFromBlock->SetValue( wxString(wBBT.getfrombk(l_BBTSel),wxConvUTF8));
      m_BBTRoute->SetValue( wxString(wBBT.getroute(l_BBTSel),wxConvUTF8));
      m_BBTInterval->SetValue(wBBT.getinterval(l_BBTSel));
      m_BBTGenerateIn->SetValue(wBBT.isgeneratein(l_BBTSel)?true:false);
      m_BBTFixed->SetValue(wBBT.isfixed(l_BBTSel)?true:false);
      m_BBTFixed->Enable(!m_BBTGenerateIn->IsChecked());
      m_BBTSpeed->SetValue(wBBT.getspeed(l_BBTSel));
      m_BBTDelay->SetValue(wBBT.getdelay(l_BBTSel));
    }
  }
}


static int __sortSBTBlock(obj* _a, obj* _b)
{
    iONode a = (iONode)*_a;
    iONode b = (iONode)*_b;
    const char* idA = wSBT.getbk( a );
    const char* idB = wSBT.getbk( b );
    return ms_SBTSort ? strcmp( idA, idB ):strcmp( idB, idA );
}


static int __sortSBTTrain(obj* _a, obj* _b)
{
    iONode a = (iONode)*_a;
    iONode b = (iONode)*_b;
    const char* idA = wSBT.gettrain( a );
    const char* idB = wSBT.gettrain( b );
    return ms_SBTSort ? strcmp( idA, idB ):strcmp( idB, idA );
}


static int __sortSBTInterval(obj* _a, obj* _b)
{
    iONode a = (iONode)*_a;
    iONode b = (iONode)*_b;
    if( wSBT.getinterval(a) > wSBT.getinterval(b) )
      return ms_SBTSort ? 1:-1;
    if( wSBT.getinterval(a) < wSBT.getinterval(b) )
      return ms_SBTSort ? -1:1;
    return 0;
}


static int __sortSBTDecelerate(obj* _a, obj* _b)
{
    iONode a = (iONode)*_a;
    iONode b = (iONode)*_b;
    if( wSBT.getinterval(a) > wSBT.getdecelerate(b) )
      return ms_SBTSort ? 1:-1;
    if( wSBT.getinterval(a) < wSBT.getdecelerate(b) )
      return ms_SBTSort ? -1:1;
    return 0;
}


static int __sortBBTFromBlock(obj* _a, obj* _b)
{
    iONode a = (iONode)*_a;
    iONode b = (iONode)*_b;
    const char* idA = wBBT.getfrombk( a );
    const char* idB = wBBT.getfrombk( b );
    return ms_BBTSort ? strcmp( idA, idB ):strcmp( idB, idA );
}


static int __sortBBTRoute(obj* _a, obj* _b)
{
    iONode a = (iONode)*_a;
    iONode b = (iONode)*_b;
    const char* idA = wBBT.getroute( a );
    const char* idB = wBBT.getroute( b );
    return ms_BBTSort ? strcmp( idA, idB ):strcmp( idB, idA );
}


static int __sortBBTBlock(obj* _a, obj* _b)
{
    iONode a = (iONode)*_a;
    iONode b = (iONode)*_b;
    const char* idA = wBBT.getbk( a );
    const char* idB = wBBT.getbk( b );
    return ms_BBTSort ? strcmp( idA, idB ):strcmp( idB, idA );
}


static int __sortBBTInterval(obj* _a, obj* _b)
{
    iONode a = (iONode)*_a;
    iONode b = (iONode)*_b;
    if( wBBT.getinterval(a) > wBBT.getinterval(b) )
      return ms_BBTSort ? 1:-1;
    if( wBBT.getinterval(a) < wBBT.getinterval(b) )
      return ms_BBTSort ? -1:1;
    return 0;
}


static int __sortBBTSteps(obj* _a, obj* _b)
{
    iONode a = (iONode)*_a;
    iONode b = (iONode)*_b;
    if( wBBT.getsteps(a) > wBBT.getsteps(b) )
      return ms_BBTSort ? 1:-1;
    if( wBBT.getsteps(a) < wBBT.getsteps(b) )
      return ms_BBTSort ? -1:1;
    return 0;
}


static int __sortBBTSpeed(obj* _a, obj* _b)
{
    iONode a = (iONode)*_a;
    iONode b = (iONode)*_b;
    if( wBBT.getsteps(a) > wBBT.getspeed(b) )
      return ms_BBTSort ? 1:-1;
    if( wBBT.getsteps(a) < wBBT.getspeed(b) )
      return ms_BBTSort ? -1:1;
    return 0;
}


static int __sortBBTCount(obj* _a, obj* _b)
{
    iONode a = (iONode)*_a;
    iONode b = (iONode)*_b;
    if( wBBT.getcount(a) > wBBT.getcount(b) )
      return ms_BBTSort ? 1:-1;
    if( wBBT.getcount(a) < wBBT.getcount(b) )
      return ms_BBTSort ? -1:1;
    return 0;
}


static int __sortBBTFixed(obj* _a, obj* _b)
{
    iONode a = (iONode)*_a;
    iONode b = (iONode)*_b;
    if( wBBT.isfixed(a) > wBBT.isfixed(b) )
      return ms_BBTSort ? 1:-1;
    if( wBBT.isfixed(a) < wBBT.isfixed(b) )
      return ms_BBTSort ? -1:1;
    return 0;
}


iOList LocDialog::sortSBT() {
  if( m_Props == NULL ) {
    return NULL;
  }

  iOList list = ListOp.inst();
  iONode sbt = wLoc.getsbt( m_Props );

  while( sbt != NULL ) {
    ListOp.add(list, (obj)sbt);
    sbt = wLoc.nextsbt( m_Props, sbt );
  };

  if( m_SBTSortCol == 1 ) {
    ListOp.sort(list, &__sortSBTTrain);
  }
  else if( m_SBTSortCol == 2 ) {
    ListOp.sort(list, &__sortSBTInterval);
  }
  else if( m_SBTSortCol == 3 ) {
    ListOp.sort(list, &__sortSBTDecelerate);
  }
  else {
    ListOp.sort(list, &__sortSBTBlock);
  }

  if( m_SBTList != NULL ) {
    ListOp.base.del(m_SBTList);
  }
  m_SBTList = list;
  return m_SBTList;
}


iOList LocDialog::sortBBT() {
  if( m_Props == NULL ) {
    return NULL;
  }

  iOList list = ListOp.inst();
  iONode bbt = wLoc.getbbt( m_Props );

  while( bbt != NULL ) {
    ListOp.add(list, (obj)bbt);
    bbt = wLoc.nextbbt( m_Props, bbt );
  };

  if( m_BBTSortCol == 1 ) {
    ListOp.sort(list, &__sortBBTBlock);
  }
  else if( m_BBTSortCol == 2 ) {
    ListOp.sort(list, &__sortBBTInterval);
  }
  else if( m_BBTSortCol == 3 ) {
    ListOp.sort(list, &__sortBBTSteps);
  }
  else if( m_BBTSortCol == 4 ) {
    ListOp.sort(list, &__sortBBTCount);
  }
  else if( m_BBTSortCol == 5 ) {
    ListOp.sort(list, &__sortBBTFixed);
  }
  else if( m_BBTSortCol == 6 ) {
    ListOp.sort(list, &__sortBBTRoute);
  }
  else if( m_BBTSortCol == 7 ) {
    ListOp.sort(list, &__sortBBTSpeed);
  }
  else {
    ListOp.sort(list, &__sortBBTFromBlock);
  }

  if( m_BBTList != NULL ) {
    ListOp.base.del(m_BBTList);
  }
  m_BBTList = list;
  return m_BBTList;
}


void LocDialog::initSBT() {
  m_SBTList2->DeleteAllItems();

  if( m_Props == NULL )
    return;

  m_iSBTSel = wxNOT_FOUND;
  m_SBTBlock->SetValue( wxT(""));
  m_SBTInterval->SetValue(0);
  m_SBTDecelerate->SetValue(0);

  iOList list = sortSBT();

  int cnt = ListOp.size(list);
  for( int i = 0; i < cnt; i++ ) {
    iONode sbt = (iONode)ListOp.get(list, i);
    m_SBTList2->InsertItem( i, wxString(wSBT.getbk(sbt),wxConvUTF8) );
    m_SBTList2->SetItem( i, 1, wxString(wSBT.gettrain(sbt),wxConvUTF8) );
    m_SBTList2->SetItem( i, 2, wxString::Format(wxT("%d"), wSBT.getinterval(sbt)) );
    m_SBTList2->SetItem( i, 3, wxString::Format(wxT("%d"), wSBT.getdecelerate(sbt)) );
    TraceOp.trc( "locdlg", TRCLEVEL_INFO, __LINE__, 9999, "sbt[%d]=%lx", i, sbt );
  }
  // resize
  for( int n = 0; n < 4; n++ ) {
    m_SBTList2->SetColumnWidth(n, wxLIST_AUTOSIZE_USEHEADER);
    int autoheadersize = m_SBTList2->GetColumnWidth(n);
    m_SBTList2->SetColumnWidth(n, wxLIST_AUTOSIZE);
    int autosize = m_SBTList2->GetColumnWidth(n);
    if(autoheadersize > autosize )
      m_SBTList2->SetColumnWidth(n, wxLIST_AUTOSIZE_USEHEADER);
  }
}

void LocDialog::initBBT() {
  m_BBTList2->DeleteAllItems();

  if( m_Props == NULL )
    return;

  m_iBBTSel = wxNOT_FOUND;
  m_BBTBlock->SetValue( wxT(""));
  m_BBTFromBlock->SetValue( wxT(""));
  m_BBTRoute->SetValue( wxT(""));
  m_BBTInterval->SetValue(0);
  m_BBTSpeed->SetValue(0);

  iOList list = sortBBT();

  int cnt = ListOp.size(list);
  for( int i = 0; i < cnt; i++ ) {
    iONode bbt = (iONode)ListOp.get(list, i);
    m_BBTList2->InsertItem( i, wxString(wBBT.getfrombk(bbt),wxConvUTF8) );
    m_BBTList2->SetItem( i, 1, wxString(wBBT.getbk(bbt), wxConvUTF8) );
    m_BBTList2->SetItem( i, 2, wxString::Format(wxT("%d"), wBBT.getinterval(bbt)) );
    m_BBTList2->SetItem( i, 3, wxString::Format(wxT("%d"), wBBT.getsteps(bbt)) );
    m_BBTList2->SetItem( i, 4, wxString::Format(wxT("%d"), wBBT.getcount(bbt)) );
    m_BBTList2->SetItem( i, 5, wBBT.isfixed(bbt) ? wxGetApp().getMsg("yes"):wxGetApp().getMsg("no") );
    m_BBTList2->SetItem( i, 6, wxString(wBBT.getroute(bbt), wxConvUTF8) );
    m_BBTList2->SetItem( i, 7, wxString::Format(wxT("%d"), wBBT.getspeed(bbt)) );
    m_BBTList2->SetItem( i, 8, wBBT.isgeneratein(bbt) ? wxGetApp().getMsg("yes"):wxGetApp().getMsg("no") );
    m_BBTList2->SetItem( i, 9, wxString::Format(wxT("%d"),wBBT.getdelay(bbt)) );
    //m_BBTList2->SetItemPtrData(i, (wxUIntPtr)bbt);
    TraceOp.trc( "locdlg", TRCLEVEL_INFO, __LINE__, 9999, "bbt[%d]=%lx", i, bbt );
  }

  // resize
  for( int n = 0; n < 9; n++ ) {
    m_BBTList2->SetColumnWidth(n, wxLIST_AUTOSIZE_USEHEADER);
    int autoheadersize = m_BBTList2->GetColumnWidth(n);
    m_BBTList2->SetColumnWidth(n, wxLIST_AUTOSIZE);
    int autosize = m_BBTList2->GetColumnWidth(n);
    if(autoheadersize > autosize )
      m_BBTList2->SetColumnWidth(n, wxLIST_AUTOSIZE_USEHEADER);
  }
}



/*!
 * wxEVT_COMMAND_CHECKBOX_CLICKED event handler for ID_CONSIST_LIGHTSOFF
 */

void LocDialog::OnConsistLightsoffClick( wxCommandEvent& event )
{
  m_SyncLights->Enable(!m_LightsOff->IsChecked());
}


/*!
 * wxEVT_LEFT_DCLICK event handler for ID_LOC_ICONF1
 */

void LocDialog::OnLocIconf1( wxMouseEvent& event )
{
  const char* imagepath = wGui.getimagepath( wxGetApp().getIni() );
  TraceOp.trc( "locdlg", TRCLEVEL_INFO, __LINE__, 9999, "imagepath = [%s]", imagepath );
  wxFileDialog* fdlg = new wxFileDialog(this, _T("Search icon image"),  wxString(imagepath,wxConvUTF8), _T(""),
      _T("PNG files (*.png)|*.png"), wxFD_OPEN);
  if( fdlg->ShowModal() == wxID_OK ) {
    m_Icon_f1->SetValue( fdlg->GetFilename() );
  }
}


/*!
 * wxEVT_LEFT_DCLICK event handler for ID_LOC_ICONF2
 */

void LocDialog::OnLocIconf2( wxMouseEvent& event )
{
  const char* imagepath = wGui.getimagepath( wxGetApp().getIni() );
  TraceOp.trc( "locdlg", TRCLEVEL_INFO, __LINE__, 9999, "imagepath = [%s]", imagepath );
  wxFileDialog* fdlg = new wxFileDialog(this, _T("Search icon image"),  wxString(imagepath,wxConvUTF8), _T(""),
      _T("PNG files (*.png)|*.png"), wxFD_OPEN);
  if( fdlg->ShowModal() == wxID_OK ) {
    m_Icon_f2->SetValue( fdlg->GetFilename() );
  }
}


/*!
 * wxEVT_LEFT_DCLICK event handler for ID_LOC_ICONF3
 */

void LocDialog::OnLocIconf3( wxMouseEvent& event )
{
  const char* imagepath = wGui.getimagepath( wxGetApp().getIni() );
  TraceOp.trc( "locdlg", TRCLEVEL_INFO, __LINE__, 9999, "imagepath = [%s]", imagepath );
  wxFileDialog* fdlg = new wxFileDialog(this, _T("Search icon image"),  wxString(imagepath,wxConvUTF8), _T(""),
      _T("PNG files (*.png)|*.png"), wxFD_OPEN);
  if( fdlg->ShowModal() == wxID_OK ) {
    m_Icon_f3->SetValue( fdlg->GetFilename() );
  }
}


/*!
 * wxEVT_LEFT_DCLICK event handler for ID_LOC_ICONF4
 */

void LocDialog::OnLocIconf4( wxMouseEvent& event )
{
  const char* imagepath = wGui.getimagepath( wxGetApp().getIni() );
  TraceOp.trc( "locdlg", TRCLEVEL_INFO, __LINE__, 9999, "imagepath = [%s]", imagepath );
  wxFileDialog* fdlg = new wxFileDialog(this, _T("Search icon image"),  wxString(imagepath,wxConvUTF8), _T(""),
      _T("PNG files (*.png)|*.png"), wxFD_OPEN);
  if( fdlg->ShowModal() == wxID_OK ) {
    m_Icon_f4->SetValue( fdlg->GetFilename() );
  }
}


/*!
 * wxEVT_LEFT_DCLICK event handler for ID_LOC_ICONF0
 */

void LocDialog::OnLocIconf0( wxMouseEvent& event )
{
  const char* imagepath = wGui.getimagepath( wxGetApp().getIni() );
  TraceOp.trc( "locdlg", TRCLEVEL_INFO, __LINE__, 9999, "imagepath = [%s]", imagepath );
  wxFileDialog* fdlg = new wxFileDialog(this, _T("Search icon image"),  wxString(imagepath,wxConvUTF8), _T(""),
      _T("PNG files (*.png)|*.png"), wxFD_OPEN);
  if( fdlg->ShowModal() == wxID_OK ) {
    m_F0Icon->SetValue( fdlg->GetFilename() );
  }
}


/*!
 * wxEVT_LEFT_DCLICK event handler for ID_LOC_SOUND1
 */

void LocDialog::OnLocSound1( wxMouseEvent& event )
{
  wxFileDialog* fdlg = new wxFileDialog(this, _T("Search sound"),  wxString(wxT("."),wxConvUTF8), _T(""),
      _T("MP3 files (*.mp3)|*.mp3|Wave files (*.wav)|*.wav"), wxFD_OPEN);
  if( fdlg->ShowModal() == wxID_OK ) {
    m_Sound1->SetValue( fdlg->GetFilename() );
  }
}


/*!
 * wxEVT_LEFT_DCLICK event handler for ID_LOC_SOUND2
 */

void LocDialog::OnLocSound2( wxMouseEvent& event )
{
  wxFileDialog* fdlg = new wxFileDialog(this, _T("Search sound"),  wxString(wxT("."),wxConvUTF8), _T(""),
      _T("MP3 files (*.mp3)|*.mp3|Wave files (*.wav)|*.wav"), wxFD_OPEN);
  if( fdlg->ShowModal() == wxID_OK ) {
    m_Sound2->SetValue( fdlg->GetFilename() );
  }
}


/*!
 * wxEVT_LEFT_DCLICK event handler for ID_LOC_SOUND3
 */

void LocDialog::OnLocSound3( wxMouseEvent& event )
{
  wxFileDialog* fdlg = new wxFileDialog(this, _T("Search sound"),  wxString(wxT("."),wxConvUTF8), _T(""),
      _T("MP3 files (*.mp3)|*.mp3|Wave files (*.wav)|*.wav"), wxFD_OPEN);
  if( fdlg->ShowModal() == wxID_OK ) {
    m_Sound3->SetValue( fdlg->GetFilename() );
  }
}


/*!
 * wxEVT_LEFT_DCLICK event handler for ID_LOC_SOUND4
 */

void LocDialog::OnLocSound4( wxMouseEvent& event )
{
  wxFileDialog* fdlg = new wxFileDialog(this, _T("Search sound"),  wxString(wxT("."),wxConvUTF8), _T(""),
      _T("MP3 files (*.mp3)|*.mp3|Wave files (*.wav)|*.wav"), wxFD_OPEN);
  if( fdlg->ShowModal() == wxID_OK ) {
    m_Sound4->SetValue( fdlg->GetFilename() );
  }
}


/*!
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for wxID_HELP
 */

void LocDialog::OnHelpClick( wxCommandEvent& event )
{
  switch( m_Notebook->GetSelection() ) {
  case 0: wxGetApp().openLink( "loc-index" ); break;
  case 1: wxGetApp().openLink( "loc-gen" ); break;
  case 2: wxGetApp().openLink( "loc-int" ); break;
  case 3: wxGetApp().openLink( "loc-details" ); break;
  case 4: wxGetApp().openLink( "loc-fun" ); break;
  case 5: wxGetApp().openLink( "loc-consist" ); break;
  case 6: wxGetApp().openLink( "loc-cv" ); break;
  case 7: wxGetApp().openLink( "loc-bbt" ); break;
  default: wxGetApp().openLink( "loc-index" ); break;
  }
}


/*!
 * wxEVT_COMMAND_CHECKBOX_CLICKED event handler for ID_LOC_MANUALLY
 */

void LocDialog::OnLocManuallyClick( wxCommandEvent& event )
{
  if( m_Props == NULL )
    return;

  TraceOp.trc( "locdlg", TRCLEVEL_INFO, __LINE__, 9999, "manually" );

  if( !Evaluate() )
    return;

  if( !wxGetApp().isStayOffline() ) {
    /* Notify RocRail. */
    iONode cmd = NodeOp.inst( wModelCmd.name(), NULL, ELEMENT_NODE );
    wModelCmd.setcmd( cmd, wModelCmd.modify );
    NodeOp.addChild( cmd, (iONode)m_Props->base.clone( m_Props ) );
    wxGetApp().sendToRocrail( cmd );
    cmd->base.del(cmd);
  }
  else {
    wxGetApp().setLocalModelModified(true);
  }
}


/*!
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_SELECT_LOCOIMAGE
 */

void LocDialog::OnSelectLocoimage( wxCommandEvent& event )
{
  OnBitmapbuttonClick(event);
}


/*!
 * wxEVT_COMMAND_LIST_COL_CLICK event handler for ID_LOC_BBTLIST2
 */

void LocDialog::OnLocBbtlist2ColLeftClick( wxListEvent& event )
{
  if(m_BBTSortCol == event.GetColumn())
    ms_BBTSort = !ms_BBTSort;
  else
    ms_BBTSort = true;

  m_BBTSortCol = event.GetColumn();
  initBBT();
}


/*!
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BBT_COPY
 */

void LocDialog::OnBbtCopyClick( wxCommandEvent& event ) {
  if( m_Props != NULL) {
    // re-init the list to update the bbt pointers
    sortBBT();
    if( m_iBBTSel != wxNOT_FOUND ) {
      iONode l_BBTSel = (iONode)ListOp.get(m_BBTList, m_iBBTSel);

      if( l_BBTSel != NULL ) {
        iONode bbtrec = (iONode)NodeOp.base.clone(l_BBTSel);
        char* s = StrOp.fmt("copy of %s", wBBT.getfrombk(bbtrec));
        wBBT.setfrombk(bbtrec, s);
        StrOp.free(s);
        s = StrOp.fmt("copy of %s", wBBT.getbk(bbtrec));
        wBBT.setbk(bbtrec, s);
        StrOp.free(s);
        NodeOp.addChild( m_Props, bbtrec );
        initBBT();
      }
    }
  }
}


/*!
 * wxEVT_COMMAND_CHECKBOX_CLICKED event handler for ID_BBT_GENATE_IN
 */

void LocDialog::OnBbtGenateInClick( wxCommandEvent& event ) {
  if( m_BBTGenerateIn->IsChecked() )
    m_BBTFixed->SetValue(true);
  m_BBTFixed->Enable(!m_BBTGenerateIn->IsChecked());
}


/*!
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BBT_ADD
 */

void LocDialog::OnBbtAddClick( wxCommandEvent& event ) {
  if( m_Props != NULL) {
    // re-init the list to update the bbt pointers
    //initBBT();
    iONode bbtrec = NodeOp.inst(wBBT.name(), m_Props, ELEMENT_NODE);
    NodeOp.addChild( m_Props, bbtrec );
    initBBT();
  }
}


/*!
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BBT_EXPORT
 */

void LocDialog::OnBbtExportClick( wxCommandEvent& event ) {
  wxFileDialog* fdlg = new wxFileDialog(this, _T("BBT"), wxString(".",wxConvUTF8), _T(""),
      _T("XML files (*.xml)|*.xml"), wxFD_SAVE);
  if( fdlg->ShowModal() == wxID_OK ) {
    wxString path = fdlg->GetPath();

    if( !path.Contains( _T(".xml") ) )
      path.Append( _T(".xml") );

    iOFile f = FileOp.inst( path.mb_str(wxConvUTF8), OPEN_WRITE );
    if( f != NULL ) {
      iONode lc = NodeOp.inst(wLoc.name(), NULL, ELEMENT_NODE);
      iONode bbt = wLoc.getbbt( m_Props );
      while( bbt != NULL ) {
        NodeOp.addChild(lc, (iONode)NodeOp.base.clone(bbt));
        bbt = wLoc.nextbbt( m_Props, bbt );
      };
      char* s = NodeOp.toEscString(lc);
      FileOp.write( f, s, StrOp.len(s));
      FileOp.base.del( f );
    }
  }
  fdlg->Destroy();
}


/*!
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BBT_IMPORT
 */

void LocDialog::OnBbtImportClick( wxCommandEvent& event ) {
  wxFileDialog* fdlg = new wxFileDialog(this, _T("BBT"), wxString(".",wxConvUTF8), _T(""),
      _T("XML files (*.xml)|*.xml"), wxFD_OPEN);
  if( fdlg->ShowModal() == wxID_OK ) {
    if( FileOp.exist(fdlg->GetPath().mb_str(wxConvUTF8)) ) {
      iOFile f = FileOp.inst( fdlg->GetPath().mb_str(wxConvUTF8), OPEN_READONLY );
      char* buffer = (char*)allocMem( FileOp.size( f ) +1 );
      FileOp.read( f, buffer, FileOp.size( f ));
      iODoc doc = DocOp.parse(buffer);
      if( doc != NULL ) {
        iONode lc = DocOp.getRootNode(doc);
        if( lc != NULL ) {
          iONode bbt = wLoc.getbbt( lc );
          while( bbt != NULL ) {
            NodeOp.addChild(m_Props, (iONode)NodeOp.base.clone(bbt));
            bbt = wLoc.nextbbt( lc, bbt );
          };
          initBBT();
        }
      }

      freeMem(buffer);
      FileOp.base.del( f );
    }
  }
  fdlg->Destroy();
}


/*!
 * wxEVT_COMMAND_LIST_ITEM_SELECTED event handler for ID_SBT_LIST
 */

void LocDialog::OnSbtListSelected( wxListEvent& event )
{
  if( m_Props != NULL ) {
    m_iSBTSel = event.GetIndex();
    if( m_iSBTSel != wxNOT_FOUND) {
      sortSBT();
      iONode l_SBTSel = (iONode)ListOp.get(m_SBTList, m_iSBTSel);
      TraceOp.trc( "locdlg", TRCLEVEL_INFO, __LINE__, 9999, "selected sbt=%d node=%lx", m_iSBTSel, l_SBTSel );
      m_SBTDelete->Enable(true);
      m_SBTBlock->SetValue( wxString(wSBT.getbk(l_SBTSel),wxConvUTF8));
      m_SBTTrain->SetValue( wxString(wSBT.gettrain(l_SBTSel),wxConvUTF8));
      m_SBTInterval->SetValue(wSBT.getinterval(l_SBTSel));
      m_SBTDecelerate->SetValue(wSBT.getdecelerate(l_SBTSel));
    }
  }
}


/*!
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_SBT_ADD
 */

void LocDialog::OnSbtAddClick( wxCommandEvent& event )
{
  if( m_Props != NULL) {
    iONode sbtrec = NodeOp.inst(wSBT.name(), m_Props, ELEMENT_NODE);
    wSBT.setinterval(sbtrec, m_SBTInterval->GetValue());
    wSBT.setbk(sbtrec, m_SBTBlock->GetValue().mb_str(wxConvUTF8));
    wSBT.settrain(sbtrec, m_SBTTrain->GetValue().mb_str(wxConvUTF8));
    wSBT.setdecelerate(sbtrec, m_SBTDecelerate->GetValue());

    NodeOp.addChild( m_Props, sbtrec );
    initSBT();
  }
}


/*!
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_SBT_DELETE
 */

void LocDialog::OnSbtDeleteClick( wxCommandEvent& event )
{
  if( m_Props != NULL) {
    // re-init the list to update the bbt pointers
    sortSBT();
    if(  m_iSBTSel != wxNOT_FOUND ) {
      iONode l_SBTSel = (iONode)ListOp.get(m_SBTList, m_iSBTSel);

      if( l_SBTSel != NULL ) {
        NodeOp.removeChild( m_Props, l_SBTSel );
        l_SBTSel = NULL;
        initSBT();

        if( NodeOp.getChildCnt(m_Props) == 0 ) {
          // ToDo: Work aroud for forcing the loco objects to remove all child nodes...
          iONode node = NodeOp.inst( wCVByte.name(), m_Props, ELEMENT_NODE);
          NodeOp.addChild( m_Props, node );
        }

        if( m_SBTList2->GetItemCount() == 0 ) {
          m_SBTDelete->Enable(false);
        }
      }
    }
  }
}


/*!
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_SBT_MODIFY
 */

void LocDialog::OnSbtModifyClick( wxCommandEvent& event )
{
  if( m_Props != NULL && m_iSBTSel != wxNOT_FOUND) {
    // re-init the list to update the bbt pointers
    sortSBT();
    iONode l_SBTSel = (iONode)ListOp.get(m_SBTList, m_iSBTSel);

    wSBT.setinterval(l_SBTSel, m_SBTInterval->GetValue());
    wSBT.setbk(l_SBTSel, m_SBTBlock->GetValue().mb_str(wxConvUTF8));
    wSBT.settrain(l_SBTSel, m_SBTTrain->GetValue().mb_str(wxConvUTF8));
    wSBT.setdecelerate(l_SBTSel, m_SBTDecelerate->GetValue());

    int sel = m_iSBTSel;
    initSBT();
    m_iSBTSel = sel;
    m_SBTList2->SetItemState(m_iSBTSel, wxLIST_STATE_SELECTED, wxLIST_STATE_SELECTED);
  }
}


/*!
 * wxEVT_COMMAND_LIST_COL_CLICK event handler for ID_SBT_LIST
 */

void LocDialog::OnSbtListColLeftClick( wxListEvent& event )
{
  if(m_SBTSortCol == event.GetColumn())
    ms_SBTSort = !ms_SBTSort;
  else
    ms_SBTSort = true;

  m_SBTSortCol = event.GetColumn();
  initSBT();
}


void LocDialog::OnBbtFixallClick( wxCommandEvent& event )
{
  if( m_Props == NULL )
    return;

  if( m_BBTList2->GetSelectedItemCount() > 0 ) {
    iOList list = sortBBT();
    for( int i = 0; i < m_BBTList2->GetItemCount(); i++ ) {
      TraceOp.trc( "locdlg", TRCLEVEL_INFO, __LINE__, 9999, "Item state = %X", m_BBTList2->GetItemState(i, wxLIST_STATE_SELECTED) );
      if( m_BBTList2->GetItemState(i, wxLIST_STATE_SELECTED) & wxLIST_STATE_SELECTED ) {
        iONode bbt = (iONode)ListOp.get(list, i);
        wBBT.setfixed(bbt, wBBT.isfixed(bbt) ? False:True);
      }
    }
  }

  initBBT();
}


void LocDialog::OnAboxID( wxMouseEvent& event )
{
  ABox(m_ID, wxGetApp().getCMsg( "id" ) );
}


void LocDialog::OnAboxRoadname( wxMouseEvent& event )
{
  ABox(m_Roadname, wxGetApp().getCMsg( "roadname" ));
}


void LocDialog::OnAboxCatnr( wxMouseEvent& event )
{
  ABox(m_CatNr, wxGetApp().getCMsg( "catnr" ));
}


void LocDialog::onABoxDecoderType( wxMouseEvent& event )
{
  ABox(m_DecoderType, wxGetApp().getCMsg( "decodertype" ));
}


void LocDialog::OnAboxIdent( wxMouseEvent& event )
{
  ABox(m_Ident, wxGetApp().getCMsg( "identifier" ));
}

