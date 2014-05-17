/*
 Copyright (C) 2002-2014 Rob Versluis, Rocrail.net

 

 */
#ifndef __speedcurvedlg__
#define __speedcurvedlg__

/**
@file
Subclass of speedcurvedlggen, which is generated by wxFormBuilder.
*/

#include "speedcurvedlggen.h"

/** Implementing speedcurvedlggen */
class SpeedCurveDlg : public speedcurvedlggen
{
  wxTextCtrl* m_Step[28];
  wxSlider* m_SliderStep[28];
  int m_Curve[28];

  void onStep( wxCommandEvent& event );
  void onSlider( wxScrollEvent& event );
  void onLinearize( wxCommandEvent& event );
  void onLogarithmize( wxCommandEvent& event );
  void onCancel( wxCommandEvent& event );
  void onOK( wxCommandEvent& event );
  void onHelp( wxCommandEvent& event );

public:
	/** Constructor */
	SpeedCurveDlg( wxWindow* parent, int* curve );
	int* getCurve();
};

#endif // __speedcurvedlg__
