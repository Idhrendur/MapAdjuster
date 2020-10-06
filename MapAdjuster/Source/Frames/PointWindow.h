#pragma once
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
#include <wx/grid.h>
#include "../PointMapper/CoPoint.h"
#include "ImageBox.h"

wxDECLARE_EVENT(wxEVT_UPDATE_POINT, wxCommandEvent);

class PointWindow: public wxWindow
{
  public:
	PointWindow(wxWindow* parent);
	void loadCoPoints(const std::shared_ptr<std::vector<std::shared_ptr<CoPoint>>>& theCoPoints) { coPoints = theCoPoints; }
	void registerPoint(const Point& point, ImageTabSelector theSelector);
	void redrawGrid() const;

  private:
	wxGrid* theGrid = nullptr;
	std::shared_ptr<std::vector<std::shared_ptr<CoPoint>>> coPoints;
	std::shared_ptr<CoPoint> workingPoint;

	void createCoPoint(const Point& point, ImageTabSelector selector);
	void updateWorkingPoint(const Point& point, ImageTabSelector selector) const;

  protected:
	wxEvtHandler* eventListener = nullptr;
};
