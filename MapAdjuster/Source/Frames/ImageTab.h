#pragma once
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

class ImageTab: public wxScrolledWindow
{
  public:
	ImageTab(wxWindow* parent, int test);

  private:
	void OnSize(wxSizeEvent& event);
};
