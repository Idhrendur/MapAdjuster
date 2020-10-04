#include "MainFrame.h"
#include "wx/splitter.h"
#include "ImageTab.h"

MainFrame::MainFrame(const wxString& title, const wxPoint& pos, const wxSize& size): wxFrame(nullptr, wxID_ANY, title, pos, size)
{
	Bind(wxEVT_MENU, &MainFrame::OnExit, this, wxID_EXIT);
	Bind(wxEVT_MENU, &MainFrame::OnAbout, this, wxID_ABOUT);
	Bind(wxEVT_MENU, &MainFrame::OnSupportUs, this, wxID_NETWORK);
	//Bind(wxEVT_SIZE, &MainFrame::onResize, this);
}

void MainFrame::initFrame()
{
	vbox = new wxFlexGridSizer(1, 2, 0, 0);
	notebook = new wxNotebook(this, wxID_ANY);

	ImageTab* imageFrom = new ImageTab(notebook, 1);
	notebook->AddPage(imageFrom, "Source");
	ImageTab* imageTo = new ImageTab(notebook, 2);
	notebook->AddPage(imageTo, "Target");

	pointWindow = new PointWindow(this);
	pointWindow->SetMinSize(wxSize(200, 1000));

	vbox->Add(pointWindow, wxSizerFlags(0).Expand());
	vbox->Add(notebook, wxSizerFlags(1).Expand());

	notebook->SetMinSize(wxSize(9000, 5000));

	this->SetSizer(vbox);
	this->Centre();
}

void MainFrame::onResize(wxSizeEvent& event)
{
	// layout everything in the dialog
	event.Skip();
}

void MainFrame::OnExit(wxCommandEvent& event)
{
	Close(true);
}

void MainFrame::OnAbout(wxCommandEvent& event)
{
	wxMessageBox("Copyright (c) 2020 The Paradox Game Converters Group\n\nThis tool, as all others, is free and available at our Github repository.\n\nGithub. Forums. Wiki pages. Steam. If you need to find us, report bugs, offer suggestions or wish to participate, we're there.", "Paradox Game Converters Group - Map Adjuster", wxOK | wxICON_INFORMATION);
}

void MainFrame::OnSupportUs(wxCommandEvent& event)
{
	wxLaunchDefaultBrowser("https://www.patreon.com/ParadoxGameConverters");
}

