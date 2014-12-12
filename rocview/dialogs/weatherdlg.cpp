/* Rocrail - Model Railroad Software Copyright (C) 2002-2014 Rob Versluis, Rocrail.net This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 3 of the License, or (at your option) any later version. This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details. You should have received a copy of the GNU General Public License along with this program; if not, write to the Free Software Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.*/#include "weatherdlg.h"#include "rocview/public/guiapp.h"#include "rocrail/wrapper/public/Weather.h"#include "rocrail/wrapper/public/Sunrise.h"#include "rocrail/wrapper/public/Sunset.h"#include "rocrail/wrapper/public/Night.h"#include "rocrail/wrapper/public/Output.h"#include "rocrail/wrapper/public/ModelCmd.h"WeatherDlg::WeatherDlg( wxWindow* parent, iONode props ):WeatherDlgGen( parent ){  m_Props = props;  initLabels();  GetSizer()->Fit(this);  GetSizer()->SetSizeHints(this);  GetSizer()->Layout();  initValues();}void WeatherDlg::onCancel( wxCommandEvent& event ){  EndModal(0);}void WeatherDlg::initLabels() {  SetTitle(wxGetApp().getMsg( "weather" ));  m_WeatherBook->SetPageText( 0, wxGetApp().getMsg( "day" ) );  m_WeatherBook->SetPageText( 1, wxGetApp().getMsg( "night" ) );  m_labOutputs->SetLabel( wxGetApp().getMsg( "outputs" ) );  m_labMaxBri->SetLabel( wxGetApp().getMsg( "maxbri" ) );  m_labSunrise->SetLabel( wxGetApp().getMsg( "sunrise" ) );  m_labSunset->SetLabel( wxGetApp().getMsg( "sunset" ) );  m_labOutputsNight->SetLabel( wxGetApp().getMsg( "outputs" ) );  m_labBrightnessNight->SetLabel( wxGetApp().getMsg( "brightness" ) );}void WeatherDlg::initValues() {  m_Outputs->SetValue( wxString(wWeather.getoutputs(m_Props),wxConvUTF8) );  m_MaxBri->SetValue( wWeather.getmaxbri(m_Props) );  iONode sunrise = wWeather.getsunrise(m_Props);  if( sunrise == NULL ) {    sunrise = NodeOp.inst(wSunrise.name(), m_Props, ELEMENT_NODE );    NodeOp.addChild(m_Props, sunrise);  }  char* str = StrOp.fmt( "%d", wSunrise.gethour( sunrise ) );  m_SunriseHour->SetValue( wxString(str,wxConvUTF8) ); StrOp.free( str );  str = StrOp.fmt( "%d", wSunrise.getminute( sunrise ) );  m_SunriseMin->SetValue( wxString(str,wxConvUTF8) ); StrOp.free( str );  iONode sunset = wWeather.getsunset(m_Props);  if( sunset == NULL ) {    sunset = NodeOp.inst(wSunset.name(), m_Props, ELEMENT_NODE );    NodeOp.addChild(m_Props, sunset);  }  str = StrOp.fmt( "%d", wSunset.gethour( sunset ) );  m_SunsetHour->SetValue( wxString(str,wxConvUTF8) ); StrOp.free( str );  str = StrOp.fmt( "%d", wSunset.getminute( sunset ) );  m_SunsetMin->SetValue( wxString(str,wxConvUTF8) ); StrOp.free( str );  iONode night = wWeather.getnight(m_Props);  if( night == NULL ) {    night = NodeOp.inst(wNight.name(), m_Props, ELEMENT_NODE );    NodeOp.addChild(m_Props, night);  }  m_OutputsNight->SetValue( wxString(wNight.getoutputs(night),wxConvUTF8) );  m_BrightnessNight->SetValue( wNight.getbri(night) );  m_RedNight->SetValue( wNight.getred(night) );  m_GreenNight->SetValue( wNight.getgreen(night) );  m_BlueNight->SetValue( wNight.getblue(night) );}bool WeatherDlg::evaluate() {  wWeather.setoutputs( m_Props, m_Outputs->GetValue().mb_str(wxConvUTF8) );  wWeather.setmaxbri(m_Props, m_MaxBri->GetValue() );  iONode sunrise = wWeather.getsunrise(m_Props);  wSunrise.sethour( sunrise, atoi( m_SunriseHour->GetValue().mb_str(wxConvUTF8) ) );  wSunrise.setminute( sunrise, atoi( m_SunriseMin->GetValue().mb_str(wxConvUTF8) ) );  iONode sunset = wWeather.getsunset(m_Props);  wSunset.sethour( sunset, atoi( m_SunsetHour->GetValue().mb_str(wxConvUTF8) ) );  wSunset.setminute( sunset, atoi( m_SunsetMin->GetValue().mb_str(wxConvUTF8) ) );  iONode night = wWeather.getnight(m_Props);  wNight.setoutputs( night, m_OutputsNight->GetValue().mb_str(wxConvUTF8) );  wNight.setbri(night, m_BrightnessNight->GetValue() );  wNight.setred(night, m_RedNight->GetValue() );  wNight.setgreen(night, m_GreenNight->GetValue() );  wNight.setblue(night, m_BlueNight->GetValue() );  return true;}void WeatherDlg::onOK( wxCommandEvent& event ){  evaluate();  if( !wxGetApp().isStayOffline() ) {    /* Notify RocRail. */    iONode cmd = NodeOp.inst( wModelCmd.name(), NULL, ELEMENT_NODE );    wModelCmd.setcmd( cmd, wModelCmd.modify );    NodeOp.addChild( cmd, (iONode)NodeOp.base.clone( m_Props ) );    wxGetApp().sendToRocrail( cmd );    cmd->base.del(cmd);  }  else {    wxGetApp().setLocalModelModified(true);  }  EndModal( wxID_OK );}void WeatherDlg::onHelp( wxCommandEvent& event ) {  wxGetApp().openLink( "weather" );}