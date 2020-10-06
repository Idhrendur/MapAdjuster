#include "MapAdjuster.h"
#include "Frames/MainFrame.h"

wxIMPLEMENT_APP(MapAdjuster);

bool MapAdjuster::OnInit()
{
	wxInitAllImageHandlers();
	MainFrame* frame = new MainFrame("MapAdjuster", wxPoint(50, 50), wxSize(1200, 600));
	frame->initFrame();
	frame->SetIcon(wxIcon(wxT("converter.ico"), wxBITMAP_TYPE_ICO, 16, 16));

	wxMenu* menuFile = new wxMenu;
	menuFile->Append(wxID_FILE1, "Export Points");
	menuFile->Append(wxID_FILE2, "Export Adjusted Map");
	menuFile->Append(wxID_EXIT, "Exit");
	wxMenu* menuHelp = new wxMenu;
	menuHelp->Append(wxID_ABOUT, "About");
	menuHelp->Append(wxID_NETWORK, "Support Us");
	wxMenuBar* menuBar = new wxMenuBar;
	menuBar->Append(menuFile, "&Menu");
	menuBar->Append(menuHelp, "&PGCG");

	frame->SetMenuBar(menuBar);
	frame->CreateStatusBar();
	frame->SetStatusText("Paradox Game Converters Group");

	frame->Show(true);
	return true;
}
