#include "PointWindow.h"

PointWindow::PointWindow(wxWindow* parent): wxWindow(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize)
{
	theGrid = new wxGrid(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxFULL_REPAINT_ON_RESIZE);
	theGrid->CreateGrid(0, 1, wxGrid::wxGridSelectCells);
	theGrid->HideCellEditControl();
	theGrid->HideRowLabels();
	theGrid->SetColLabelValue(0, "Point");
	theGrid->SetColLabelAlignment(wxLEFT, wxCENTER);
	theGrid->SetScrollRate(0, 20);
	theGrid->SetColLabelSize(20);

	/*
	for (auto i = 0; i< 100; i++)
	{
		theGrid->AppendRows(1, false);
		theGrid->SetRowSize(i, 20);
		theGrid->SetCellValue(i, 0, std::to_string(i));
		theGrid->SetReadOnly(i, 0);
	}*/
	theGrid->AutoSize();
	GetParent()->Layout();

	wxBoxSizer* logBox = new wxBoxSizer(wxVERTICAL);
	logBox->Add(theGrid, wxSizerFlags(1).Expand());
	SetSizer(logBox);
	logBox->Fit(this);
}
