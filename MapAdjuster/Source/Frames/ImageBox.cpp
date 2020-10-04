#include "ImageBox.h"
#include "wx/image.h"

ImageBox::ImageBox(wxWindow* parent, const wxImage& theImage): wxWindow(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize)
{
	Bind(wxEVT_PAINT, &ImageBox::paintEvent, this);
	Bind(wxEVT_SIZE, &ImageBox::OnSize, this);

	image = theImage;
}

void ImageBox::paintEvent(wxPaintEvent& evt)
{
	wxPaintDC dc(this);
	render(dc);
}
void ImageBox::paintNow()
{
	wxClientDC dc(this);
	render(dc);
}
void ImageBox::render(wxDC& dc)
{
	dc.DrawBitmap(image, 0, 0, false);
	SetMinSize(image.GetSize());
}
void ImageBox::OnSize(wxSizeEvent& event)
{
	Refresh();
	// skip the event.
	event.Skip();
}
