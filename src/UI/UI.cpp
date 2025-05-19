#include <wx/wx.h>
#include "../../include/app/App.h"

class MainFrame : public wxFrame {
    App app; // Tạo instance App
public:
    MainFrame(const wxString& title)
        : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(400, 300)), app() {
        const std::string INIT_DB_SCRIPT = "release/init_db.sql";
        ServerInfo serverInfo("127.0.0.1", "root", "rootpassword", 3306);
        cout << "------------------------------------------\n";
        Logger::getInstance()->log("Connecting to database: " + serverInfo.getHost(), Logger::Level::INFO); 
        cout << "------------------------------------------\n";
        DatabaseManager::getInstance()->connect(serverInfo);
        cout << "------------------------------------------\n";
        DatabaseManager::getInstance()->setupDatabase(INIT_DB_SCRIPT);
        cout << "------------------------------------------\n";
        wxPanel* panel = new wxPanel(this, wxID_ANY);

        wxBoxSizer* vbox = new wxBoxSizer(wxVERTICAL);

        wxStaticText* titleText = new wxStaticText(panel, wxID_ANY, "===== CINEMA BOOKING SYSTEM =====");
        vbox->Add(titleText, 0, wxALIGN_CENTER | wxTOP | wxBOTTOM, 20);

        wxButton* btnRegister = new wxButton(panel, wxID_ANY, "Register");
        wxButton* btnLogin = new wxButton(panel, wxID_ANY, "Login");
        wxButton* btnExit = new wxButton(panel, wxID_EXIT, "Exit");

        vbox->Add(btnRegister, 0, wxEXPAND | wxALL, 10);
        vbox->Add(btnLogin, 0, wxEXPAND | wxALL, 10);
        vbox->Add(btnExit, 0, wxEXPAND | wxALL, 10);

        panel->SetSizer(vbox);

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