#include "ImageTab.h"
#include "ImageBox.h"
#include "OSCompatibilityLayer.h"
#include <wx/wrapsizer.h>

ImageTab::ImageTab(wxWindow* parent, int test): wxScrolledWindow(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize)
{
	wxWrapSizer* imageTabSizer = new wxWrapSizer(wxBOTH);
	SetScrollRate(16, 16);

	if (test == 1)
	{
		wxImage image;
		image.LoadFile("test-from/provinces.bmp", wxBITMAP_TYPE_BMP);
		ImageBox* imageFrom = new ImageBox(this, image);
		imageTabSizer->Add(imageFrom);
		imageFrom->SetMinSize(image.GetSize());
	}
	if (test == 2)
	{
		wxImage image;
		image.LoadFile("test-to/provinces.bmp", wxBITMAP_TYPE_BMP);
		ImageBox* imageTo = new ImageBox(this, image);
		imageTabSizer->Add(imageTo);
		imageTo->SetMinSize(image.GetSize());
	}

	SetSizer(imageTabSizer);
	GetParent()->Layout();
}
