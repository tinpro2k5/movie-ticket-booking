#include <wx/wx.h>
#include <wx/statbmp.h>
#include <wx/artprov.h>
#include <wx/gbsizer.h>
#include "../../include/app/App.h"

class MainFrame : public wxFrame {
    App app;
public:
    MainFrame(const wxString& title)
        : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(1000, 700),
                  wxDEFAULT_FRAME_STYLE & ~(wxRESIZE_BORDER | wxMAXIMIZE_BOX)), app() {
        SetBackgroundColour(wxColour(240, 244, 255)); // Nhẹ nhàng, hiện đại

        Centre();
        SetMinSize(wxSize(1200, 700));
        SetMaxSize(wxSize(1200, 700));
        SetSize(wxSize(1200, 700));

        const std::string INIT_DB_SCRIPT = "release/init_db.sql";
        ServerInfo serverInfo("127.0.0.1", "root", "rootpassword", 3306);
        Logger::getInstance()->log("Connecting to database: " + serverInfo.getHost(), Logger::Level::INFO);
        DatabaseManager::getInstance()->connect(serverInfo);
        DatabaseManager::getInstance()->setupDatabase(INIT_DB_SCRIPT);

        wxPanel* panel = new wxPanel(this, wxID_ANY);
        panel->SetBackgroundColour(wxColour(240, 244, 255));

        wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

        mainSizer->AddStretchSpacer(1);
        // Title
        wxStaticText* titleText = new wxStaticText(panel, wxID_ANY, "Cinema Booking System");
        wxFont titleFont(wxFontInfo(32).Bold().FaceName("Arial"));
        titleText->SetFont(titleFont);
        titleText->SetForegroundColour(wxColour(44, 62, 80));
        mainSizer->Add(titleText, 0, wxALIGN_CENTER | wxTOP | wxBOTTOM, 12);

        // Subtitle
        wxStaticText* subtitle = new wxStaticText(panel, wxID_ANY, "Book your favorite movies easily and quickly!");
        wxFont subFont(wxFontInfo(16).Italic().FaceName("Arial"));
        subtitle->SetFont(subFont);
        subtitle->SetForegroundColour(wxColour(52, 152, 219));
        mainSizer->Add(subtitle, 0, wxALIGN_CENTER | wxBOTTOM, 30);

        // Button panel (centered, with spacing)
        wxBoxSizer* btnSizer = new wxBoxSizer(wxVERTICAL);

        wxButton* btnRegister = new wxButton(panel, wxID_ANY, "Register");
        wxButton* btnLogin = new wxButton(panel, wxID_ANY, "Login");
        wxButton* btnExit = new wxButton(panel, wxID_EXIT, "Exit");

        wxFont btnFont(wxFontInfo(18).Bold().FaceName("Arial"));
        btnRegister->SetFont(btnFont);
        btnLogin->SetFont(btnFont);
        btnExit->SetFont(btnFont);

        btnRegister->SetBackgroundColour(wxColour(46, 204, 113));
        btnRegister->SetForegroundColour(*wxWHITE);
        btnLogin->SetBackgroundColour(wxColour(52, 152, 219));
        btnLogin->SetForegroundColour(*wxWHITE);
        btnExit->SetBackgroundColour(wxColour(231, 76, 60));
        btnExit->SetForegroundColour(*wxWHITE);

        btnRegister->SetMinSize(wxSize(400, 54));
        btnLogin->SetMinSize(wxSize(400, 54));
        btnExit->SetMinSize(wxSize(400, 54));

        btnRegister->SetWindowStyleFlag(wxBORDER_NONE);
        btnLogin->SetWindowStyleFlag(wxBORDER_NONE);
        btnExit->SetWindowStyleFlag(wxBORDER_NONE);

        btnSizer->Add(btnRegister, 0, wxALIGN_CENTER | wxBOTTOM, 18);
        btnSizer->Add(btnLogin, 0, wxALIGN_CENTER | wxBOTTOM, 18);
        btnSizer->Add(btnExit, 0, wxALIGN_CENTER | wxBOTTOM, 18);

        mainSizer->Add(btnSizer, 0, wxALIGN_CENTER | wxBOTTOM, 30);

        // Footer
        wxStaticText* footer = new wxStaticText(panel, wxID_ANY, "© 2025 Movie Ticket Booking | Designed by You");
        footer->SetForegroundColour(wxColour(160, 160, 160));
        wxFont footerFont(wxFontInfo(11).FaceName("Arial"));
        footer->SetFont(footerFont);
        mainSizer->Add(footer, 0, wxALIGN_CENTER | wxBOTTOM, 18);
        
        mainSizer->AddStretchSpacer(2);

        panel->SetSizer(mainSizer);

        btnRegister->Bind(wxEVT_BUTTON, &MainFrame::OnRegister, this);
        btnLogin->Bind(wxEVT_BUTTON, &MainFrame::OnLogin, this);
        btnExit->Bind(wxEVT_BUTTON, &MainFrame::OnExit, this);
    }

    void OnRegister(wxCommandEvent&);
    void OnLogin(wxCommandEvent&);
    void OnExit(wxCommandEvent&) {
        Close(true);
    }
};

void MainFrame::OnRegister(wxCommandEvent&) {
    wxDialog dlg(this, wxID_ANY, "Register");
    wxBoxSizer* vbox = new wxBoxSizer(wxVERTICAL);

    wxTextCtrl* usernameCtrl = new wxTextCtrl(&dlg, wxID_ANY);
    wxTextCtrl* passwordCtrl = new wxTextCtrl(&dlg, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxTE_PASSWORD);
    wxTextCtrl* phoneCtrl = new wxTextCtrl(&dlg, wxID_ANY);
    wxTextCtrl* emailCtrl = new wxTextCtrl(&dlg, wxID_ANY);

    vbox->Add(new wxStaticText(&dlg, wxID_ANY, "Username:"), 0, wxALL, 5);
    vbox->Add(usernameCtrl, 0, wxEXPAND | wxALL, 5);
    vbox->Add(new wxStaticText(&dlg, wxID_ANY, "Password:"), 0, wxALL, 5);
    vbox->Add(passwordCtrl, 0, wxEXPAND | wxALL, 5);
    vbox->Add(new wxStaticText(&dlg, wxID_ANY, "Phone:"), 0, wxALL, 5);
    vbox->Add(phoneCtrl, 0, wxEXPAND | wxALL, 5);
    vbox->Add(new wxStaticText(&dlg, wxID_ANY, "Email:"), 0, wxALL, 5);
    vbox->Add(emailCtrl, 0, wxEXPAND | wxALL, 5);

    vbox->Add(new wxButton(&dlg, wxID_OK, "Register"), 0, wxALIGN_CENTER | wxALL, 10);

    dlg.SetSizerAndFit(vbox);

    if (dlg.ShowModal() == wxID_OK) {
        User user;
        user.setUsername(usernameCtrl->GetValue().ToStdString());
        user.setPassword(passwordCtrl->GetValue().ToStdString());
        user.setPhone(phoneCtrl->GetValue().ToStdString());
        user.setEmail(emailCtrl->GetValue().ToStdString());

        app.handleRegisterUI(user, this);
    }
}
void MainFrame::OnLogin(wxCommandEvent&) {
    wxDialog dlg(this, wxID_ANY, "Login");
    wxBoxSizer* vbox = new wxBoxSizer(wxVERTICAL);

    wxTextCtrl* usernameCtrl = new wxTextCtrl(&dlg, wxID_ANY);
    wxTextCtrl* passwordCtrl = new wxTextCtrl(&dlg, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxTE_PASSWORD);

    vbox->Add(new wxStaticText(&dlg, wxID_ANY, "Username:"), 0, wxALL, 5);
    vbox->Add(usernameCtrl, 0, wxEXPAND | wxALL, 5);
    vbox->Add(new wxStaticText(&dlg, wxID_ANY, "Password:"), 0, wxALL, 5);
    vbox->Add(passwordCtrl, 0, wxEXPAND | wxALL, 5);

    vbox->Add(new wxButton(&dlg, wxID_OK, "Login"), 0, wxALIGN_CENTER | wxALL, 10);

    dlg.SetSizerAndFit(vbox);

    if (dlg.ShowModal() == wxID_OK) {
        std::string username = usernameCtrl->GetValue().ToStdString();
        std::string password = passwordCtrl->GetValue().ToStdString();
        
        app.handleLoginUI(username, password, this);
    }
}
class MyApp : public wxApp {
public:
    virtual bool OnInit() {
        MainFrame* frame = new MainFrame("Cinema Booking System");
        frame->Show(true);
        return true;
    }
};

wxIMPLEMENT_APP(MyApp);