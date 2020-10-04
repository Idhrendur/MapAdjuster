#pragma once
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

class ImageBox: public wxWindow
{
  public:
	ImageBox(wxWindow* parent, const wxImage& theImage);
	void paintEvent(wxPaintEvent& evt);
	void paintNow();
	void OnSize(wxSizeEvent& event);
	void render(wxDC& dc);
	
  private:
	wxImage image;
};
