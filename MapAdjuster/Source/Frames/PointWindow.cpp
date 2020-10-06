#include "PointWindow.h"

wxDEFINE_EVENT(wxEVT_UPDATE_POINT, wxCommandEvent);

PointWindow::PointWindow(wxWindow* parent): wxWindow(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize)
{
	eventListener = parent;
	
	// Pointwindow displays the points we get from PointMapper.
	
	theGrid = new wxGrid(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxFULL_REPAINT_ON_RESIZE);
	theGrid->CreateGrid(0, 3, wxGrid::wxGridSelectCells);
	theGrid->HideCellEditControl();
	theGrid->HideRowLabels();
	theGrid->SetColLabelValue(0, "Point");
	theGrid->SetColLabelValue(1, "Source");
	theGrid->SetColLabelValue(2, "Target");
	theGrid->SetColLabelAlignment(wxLEFT, wxCENTER);
	theGrid->SetScrollRate(0, 20);
	theGrid->SetColLabelSize(20);

	theGrid->AutoSize();
	GetParent()->Layout();

	wxBoxSizer* logBox = new wxBoxSizer(wxVERTICAL);
	logBox->Add(theGrid, wxSizerFlags(1).Expand());
	SetSizer(logBox);
	logBox->Fit(this);
}

void PointWindow::redrawGrid() const
{
	auto rowCounter = 0;
	theGrid->BeginBatch();
	theGrid->DeleteRows(0, static_cast<int>(coPoints->size()));
	auto bgcolor = wxColour(200, 200, 200);

	for (const auto& coPoint: *coPoints)
	{
		std::string name;
		if (coPoint->getName().empty())
			name = "(No Name)";
		else
			name = coPoint->getName();
		std::string source;
		if (coPoint->getSource())
			source = std::to_string(coPoint->getSource()->x) + "x" + std::to_string(coPoint->getSource()->y);
		std::string target;
		if (coPoint->getTarget())
			target = std::to_string(coPoint->getTarget()->x) + "x" + std::to_string(coPoint->getTarget()->y);

		if (workingPoint && *coPoint == *workingPoint)
			bgcolor = wxColour(200, 255, 200);

		theGrid->AppendRows(1, false);
		theGrid->SetRowSize(rowCounter, 20);
		theGrid->SetCellValue(rowCounter, 0, name);
		theGrid->SetCellAlignment(rowCounter, 0, wxCENTER, wxCENTER);
		theGrid->SetReadOnly(rowCounter, 0);
		theGrid->SetCellValue(rowCounter, 1, source);
		theGrid->SetCellBackgroundColour(rowCounter, 1, bgcolor);
		theGrid->SetCellAlignment(rowCounter, 1, wxCENTER, wxCENTER);
		theGrid->SetReadOnly(rowCounter, 1);
		theGrid->SetCellValue(rowCounter, 2, target);
		theGrid->SetCellBackgroundColour(rowCounter, 2, bgcolor);
		theGrid->SetCellAlignment(rowCounter, 1, wxLEFT, wxCENTER);
		theGrid->SetReadOnly(rowCounter, 2);
		rowCounter++;
	}
	theGrid->EndBatch();
	theGrid->AutoSize();
	GetParent()->Layout();
	theGrid->Scroll(0, rowCounter - 1);
}

void PointWindow::registerPoint(const Point& point, ImageTabSelector theSelector)
{
	if (workingPoint)
		updateWorkingPoint(point, theSelector);
	else
		createCoPoint(point, theSelector);

	// Whatever we did, we want to update the table.
	redrawGrid();
}

void PointWindow::createCoPoint(const Point& point, ImageTabSelector selector)
{
	// Make a new point
	auto newPoint = std::make_shared<CoPoint>();
	if (selector == ImageTabSelector::SOURCE)
		newPoint->setSource(point);
	else
		newPoint->setTarget(point);
	coPoints->emplace_back(newPoint);
	// and mark it as working point!
	workingPoint = newPoint;
	
	// we must tell the map to update the point
	wxCommandEvent evt(wxEVT_UPDATE_POINT);
	evt.SetClientData(new PointData(point, selector));
	eventListener->QueueEvent(evt.Clone());
}

void PointWindow::updateWorkingPoint(const Point& point, ImageTabSelector selector) const
{
	wxCommandEvent evt(wxEVT_UPDATE_POINT);
	// We have a point selected so we're operating on some existing point.
	switch (selector)
	{
		case ImageTabSelector::SOURCE:
			if (workingPoint->getSource())
			{
				// we must tell the map to update the point
				evt.SetClientData(new PointData(*workingPoint->getSource(), point, selector));
			}
			else
			{
				evt.SetClientData(new PointData(point, selector));
			}
			workingPoint->setSource(point);
			break;
		case ImageTabSelector::TARGET:
			if (workingPoint->getTarget())
			{
				// we must tell the map to update the point
				evt.SetClientData(new PointData(*workingPoint->getTarget(), point, selector));
			}
			else
			{
				evt.SetClientData(new PointData(point, selector));
			}
			workingPoint->setTarget(point);
			break;
	}
	eventListener->QueueEvent(evt.Clone());
}
