/*
 Rocrail - Model Railroad Software

 Copyright (C) 2002-2012 Rob Versluis, Rocrail.net

 Without an official permission commercial use is not permitted.
 Forking this project is not permitted.

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 2
 of the License, or (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
*/
#ifndef __rocprodlg__
#define __rocprodlg__

/**
@file
Subclass of RocProDlgGen, which is generated by wxFormBuilder.
*/

#include "rocprodlggen.h"
#include "wx/timer.h"

#include "rocs/public/node.h"
#include "rocs/public/map.h"

//// end generated include
/** Implementing RocProDlgGen */
class RocProDlg : public RocProDlgGen
{
  char* m_DecFilename;
  iONode m_DecNode;
  iONode m_LocoProps;
  iONode m_CVConf;
  iOMap m_CVMap;
  iOMap m_CVNrMap;
  iOMap m_CatMap;
  iONode m_SelectedCV;
  bool m_bSpeedCurve;
  int m_CVoperation;
  int m_PendingCV;
  int m_Curve[28];
  bool m_bLongAddress;
  int m_CV17;
  int m_CV18;
  iONode m_CVconf;
  int m_CVidx;
  int m_CVall[1024];
  int m_CVcountAll;
  int m_CVidxAll;
  bool m_UseDecSpec4All;;
  bool m_Save;
  iONode mCVDip;
  iOMap m_DIPMap;

  bool parseDecFile();
  void initLocMap(const char* locid=NULL);
  iONode getLocoCV(int nr);
  void setCVVal(int val, bool updateval=true);
  void importJMRI(iONode decoder);
  void loadDecFile();
	protected:
		// Handlers for RocProDlgGen events.
		void onTreeSelChanged( wxTreeEvent& event );
		void onOpen( wxCommandEvent& event );
		void onOK( wxCommandEvent& event );
    void onClose( wxCloseEvent& event );
    void onLocoList( wxCommandEvent& event );
    void onConfig( wxCommandEvent& event );
    void onVCurve( wxCommandEvent& event );
    void onVCurve();
    void onValueSlider( wxScrollEvent& event );
    void onValue( wxSpinEvent& event );
    void onValueText( wxCommandEvent& event );
    void onBit( wxCommandEvent& event );
    void onSaveAs( wxCommandEvent& event );
    void onRead( wxCommandEvent& event );
    void onWrite( wxCommandEvent& event );
    void onSaveCV( wxCommandEvent& event );
    void onTreeItemPopup( wxTreeEvent& event );
    void onMenu( wxCommandEvent& event );
    void onNr( wxSpinEvent& event );
    void onNrText( wxCommandEvent& event );
    void onExtAddrRead( wxCommandEvent& event );
    void onExtAddrWrite( wxCommandEvent& event );
    void onPTON( wxCommandEvent& event );
    void onPTOFF( wxCommandEvent& event );
    void onImgOpen( wxCommandEvent& event );
    void onReadAllCV( wxCommandEvent& event );
    void onCVInfoEnter( wxCommandEvent& event );
    void onHexValue( wxCommandEvent& event );
    void onDIP( wxCommandEvent& event );
    void onTreeDIP( wxTreeEvent& event );
	public:
		/** Constructor */
		RocProDlg( wxWindow* parent );
		~RocProDlg();
    void event(iONode node);
    void doCV(int command, int nr, int value);

};

#endif // __rocprodlg__
