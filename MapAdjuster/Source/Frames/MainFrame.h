#pragma once
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include "PointWindow.h"
#include <wx/notebook.h>

class MainFrame: public wxFrame
{
  public:
	MainFrame(const wxString& title, const wxPoint& pos, const wxSize& size);

	void initFrame();

  private:
	void OnExit(wxCommandEvent& event);
	void OnAbout(wxCommandEvent& event);
	void OnSupportUs(wxCommandEvent& event);
	PointWindow* pointWindow = nullptr;
	wxNotebook* notebook = nullptr;
	wxFlexGridSizer* vbox = nullptr;
	
	void onResize(wxSizeEvent& evt);
};
