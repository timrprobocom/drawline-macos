#define wxUSE_LOG_DEBUG 1
#include <wx/wx.h>
#include <wx/panel.h>
#include <random>


class MainFrame : public wxFrame
{
public:
    explicit MainFrame( const wxString& title );

    void onOK( wxCommandEvent & event )
    {
        Close();
    }

    ~MainFrame()
    {
        wxLogDebug( __FUNCTION__ );
    }

    void onTimer( wxTimerEvent & event );

protected:
    std::mt19937        m_Random;
    wxPanel *           m_Panel;
    wxTimer             m_Timer;
};



MainFrame::MainFrame( const wxString& title )
    : wxFrame( nullptr, -1, title, wxPoint(-1,24), wxSize(800,450) )
{
    SetBackgroundColour( {240,240,240} );
    SetLabel( title );

    m_Random.seed( std::random_device()() );

    m_Panel = new wxPanel( this, -1 );

    Bind( wxEVT_TIMER, &MainFrame::onTimer, this );
    m_Timer.SetOwner( this );
    m_Timer.Start( 1000 );
}


void MainFrame::onTimer( wxTimerEvent& event )
{
    wxClientDC dc( m_Panel );
    wxSize rct = m_Panel->GetClientSize();
    static int color = 0;

    // Clear background.

    int w = rct.GetWidth();
    int h = rct.GetHeight();
    int square = std::min(w,h);

    dc.SetClippingRegion( 0, 0, w, h );
    dc.SetPen( *wxBLACK_PEN );
    dc.SetBrush( *wxBLACK_BRUSH );
    dc.DrawRectangle( 0, 0, w, h );

    // Draw grid.

    std::vector<wxPoint> pts;
    dc.SetPen( color ? *wxBLUE_PEN : *wxGREEN_PEN );
    color = !color;

    // Build 6,000 semi-random lines.

    std::uniform_int_distribution<int> distribution(0,square);

    for( int i = 0; i < 6000; i++ )
        pts.emplace_back( distribution(m_Random), distribution(m_Random) );

    int64_t tBefore = __rdtsc();
    dc.DrawLines( pts.size(), pts.data() );
    int64_t tAfter = __rdtsc();
    wxDO_LOG(Debug)("Elapsed: %lld", tAfter-tBefore);
}

//
// This is the main application.
//

class Example: public wxApp
{
public:
    virtual bool OnInit()
    {
        wxApp::OnInit();
        wxInitAllImageHandlers();

        // Create the main window.

        MainFrame * gui = new MainFrame( "Line-Drawing Example" );
        SetTopWindow( gui );
        gui->Show(true);
        return true;
    }
};

wxDECLARE_APP(Example);

wxIMPLEMENT_APP(Example);
