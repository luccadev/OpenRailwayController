/*
 Rocrail - Model Railroad Software

 Copyright (C) 2002-2014 Rob Versluis, Rocrail.net

 


 This program is free software; you can redistribute it and/or
 as published by the Free Software Foundation; either version 2
 modify it under the terms of the GNU General Public License
 of the License, or (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
*/

#ifndef __bidibidentdlg__
#define __bidibidentdlg__

/**
@file
Subclass of BidibIdentDlgGen, which is generated by wxFormBuilder.
*/

#include "bidibidendlggen.h"

#include "rocs/public/node.h"
#include "rocs/public/list.h"
#include "rocs/public/map.h"
#include "rocs/public/mutex.h"

//// end generated include

/** Implementing BidibIdentDlgGen */
class BidibIdentDlg : public BidibIdentDlgGen
{
  iONode node;
  iONode bidibnode;
  iOList nodeList;
  iOMap nodeMap;
  iOMap nodePathMap;
  iONode m_SelectedBidibNode;
  iONode m_ProductsNode;
  iOMap  m_ProductsMap;
  int macro;
  int macroline;
  int macrosize;
  int macrolevel;
  int macroparam;
  bool macrosave;
  bool macroapply;
  int configL;
  int configR;
  int configV;
  int configS;
  int uid;
  char* www;
  iOMutex servoSetMutex;
  bool eventUpdate;
  wxTreeItemId findTreeItem( const wxTreeItemId& root, const wxString& text);
  int getLevel(const char* path, int* n, int* o, int* p, char** key, char** parentkey);
  wxTreeItemId addTreeChild( const wxTreeItemId& root, iONode bidibnode);
  void handleFeature(iONode node);
  void clearFeatureList();
  void handleMacro(iONode node);
  void handleAccessory(iONode node);


  protected:
		// Handlers for BidibIdentDlgGen events.
		void onCancel( wxCommandEvent& event );
		void onOK( wxCommandEvent& event );
    void onTreeSelChanged( wxTreeEvent& event );
    void onBeginDrag( wxTreeEvent& event );
    void onItemActivated( wxTreeEvent& event );
    void onItemRightClick( wxTreeEvent& event );
    void onMenu( wxCommandEvent& event );
    void onFeatureSelect( wxCommandEvent& event );
    void onFeaturesGet( wxCommandEvent& event );
    void onFeatureSet( wxCommandEvent& event );
    void onServoLeft( wxScrollEvent& event );
    void onServoRight( wxScrollEvent& event );
    void onServoSpeed( wxScrollEvent& event );
    void onServoPort( wxSpinEvent& event );
    void onServoLeftTest( wxCommandEvent& event );
    void onServoRightTest( wxCommandEvent& event );
    void onServoGet( wxCommandEvent& event );
    void onPortSet( wxCommandEvent& event );
    void onConfigL( wxSpinEvent& event );
    void onConfigR( wxSpinEvent& event );
    void onConfigV( wxSpinEvent& event );
    void onConfigS( wxSpinEvent& event );
    void onServoReserved( wxScrollEvent& event );
    void onPortType( wxCommandEvent& event );
    void onConfigLtxt( wxCommandEvent& event );
    void onConfigRtxt( wxCommandEvent& event );
    void onConfigVtxt( wxCommandEvent& event );
    void onConfigStxt( wxCommandEvent& event );
    void onSelectUpdateFile( wxCommandEvent& event );
    void onUpdateStart( wxCommandEvent& event );

    void onServoSet(bool overwrite=false);
    void onPageChanged( wxNotebookEvent& event );
    void onMacroList( wxCommandEvent& event );
    void onMacroLineSelected( wxGridEvent& event );
    void onMacroApply( wxCommandEvent& event );
    void onMacroReload( wxCommandEvent& event );
    void onMacroSave( wxCommandEvent& event );
    void onMacroEveryMinute( wxCommandEvent& event );
    void onMacroExport( wxCommandEvent& event );
    void onMacroImport( wxCommandEvent& event );
    void onMacroSaveMacro( wxCommandEvent& event );
    void onMacroDeleteMacro( wxCommandEvent& event );
    void onMacroRestoreMacro( wxCommandEvent& event );
    void onMacroTest( wxCommandEvent& event );

    void onVendorCVEnable( wxCommandEvent& event );
    void onVendorCVDisable( wxCommandEvent& event );
    void onVendorCVGet( wxCommandEvent& event );
    void onVendorCVSet( wxCommandEvent& event );

    void onAccessoryOnTest( wxCommandEvent& event );
    void onAccessoryOffTest( wxCommandEvent& event );
    void onAccessoryReadOptions( wxCommandEvent& event );
    void onAccessoryWriteOptions( wxCommandEvent& event );
    void onAccessoryReadMacroMap( wxCommandEvent& event );
    void onAccessoryWriteMacroMap( wxCommandEvent& event );
    void onLeftLogo( wxMouseEvent& event );
    void onFBLogo( wxMouseEvent& event );
    void onProductName( wxMouseEvent& event );
    int getProductID(int uid);
    void onReport( wxCommandEvent& event );
    void onUsernameSet( wxCommandEvent& event );

	public:
		/** Constructor */
		BidibIdentDlg( wxWindow* parent );
	//// end generated class members
    BidibIdentDlg( wxWindow* parent, iONode node );
    ~BidibIdentDlg();
    void event(iONode node);
    void initLabels();
    void initValues();
    void initProducts();
    const char* GetProductName(int vid, int pid, char** www);

	
};

#endif // __bidibidentdlg__
