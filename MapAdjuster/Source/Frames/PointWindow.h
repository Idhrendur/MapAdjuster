#pragma once
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
#include <wx/grid.h>

class PointWindow: public wxWindow
{
  public:
	PointWindow(wxWindow* parent);

  private:
	wxGrid* theGrid = nullptr;
	std::vector<wxStaticText*> logArray;
};
