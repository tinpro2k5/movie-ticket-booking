#include "../../include/services/TheaterService.h"

TheaterService::TheaterService(RepositoryRegistry& repoRegistry) {
    movie_theater_repos = std::dynamic_pointer_cast<MovieTheaterRepository>(repoRegistry.movie_theater_repos);
    if (!movie_theater_repos) {
        Logger::getInstance()->log("Failed to cast to MovieTheaterRepository", Logger::Level::ERROR);
        std::cerr << "Failed to cast to MovieTheaterRepository" << std::endl;
    }
}

void TheaterService::manageTheater(User user) {
    std::cout << "===== QUẢN LÝ RẠP =====\n";
    std::cout << "1. Thêm rạp\n";
    std::cout << "2. Xem danh sách rạp\n";
    std::cout << "0. Thoát\n";
    std::cout << "========================\n";
    int choice;
    cout << "Nhập lựa chọn của bạn: ";
    std::cin >> choice;
    switch (choice) {
        case 1: {
            MovieTheater theater;
            std::cin.ignore();
            std::cout << "Nhập tên rạp: ";
            std::string name;
            std::getline(std::cin, name);
            theater.setTheaterName(name);
            std::cout << "Nhập địa chỉ rạp: ";
            std::string location;
            std::getline(std::cin, location);
            theater.setTheaterLocation(location);
            Result<int> result = movie_theater_repos->create(theater);
            if (!result.success) {
                std::cout << result.error_message << "\n";
                return;
            } else {
                std::cout << "Thêm rạp thành công \n";
            }
            break;
        }
        case 2: {
            vector<MovieTheater> theaters = movie_theater_repos->findAll().data;
            printTheaterTable(theaters);
            break;
        }
        default:
            return;
    }
}
void TheaterService::manageTheaterUI(wxWindow* parent, User user) {
    wxDialog dlg(parent, wxID_ANY, "Theater Management", wxDefaultPosition, wxSize(480, 370));
    dlg.SetBackgroundColour(wxColour(245, 247, 250));
    dlg.Centre();

    wxBoxSizer* vbox = new wxBoxSizer(wxVERTICAL);

    // Title
    wxStaticText* title = new wxStaticText(&dlg, wxID_ANY, "Theater Management");
    wxFont titleFont(wxFontInfo(22).Bold().FaceName("Arial"));
    title->SetFont(titleFont);
    title->SetForegroundColour(wxColour(41, 128, 185));
    vbox->Add(title, 0, wxALIGN_CENTER | wxTOP | wxBOTTOM, 22);

    // Subtitle
    wxStaticText* subtitle = new wxStaticText(&dlg, wxID_ANY, "Choose an action below:");
    wxFont subFont(wxFontInfo(13).Italic().FaceName("Arial"));
    subtitle->SetFont(subFont);
    subtitle->SetForegroundColour(wxColour(52, 152, 219));
    vbox->Add(subtitle, 0, wxALIGN_CENTER | wxBOTTOM, 18);

    // Buttons
    wxButton* btnAdd = new wxButton(&dlg, wxID_ANY, "Add Theater");
    wxButton* btnList = new wxButton(&dlg, wxID_ANY, "View Theater List");
    wxButton* btnExit = new wxButton(&dlg, wxID_EXIT, "Exit");

    wxFont btnFont(wxFontInfo(15).Bold().FaceName("Arial"));
    const int BTN_HEIGHT = 48;
    const int BTN_WIDTH = 320;

    auto styleBtn = [&](wxButton* btn, wxColour bg, wxColour fg) {
        btn->SetFont(btnFont);
        btn->SetBackgroundColour(bg);
        btn->SetForegroundColour(fg);
        btn->SetMinSize(wxSize(BTN_WIDTH, BTN_HEIGHT));
        btn->SetWindowStyleFlag(wxBORDER_NONE);
    };

    styleBtn(btnAdd,  wxColour(52, 152, 219),  *wxWHITE); // Blue
    styleBtn(btnList, wxColour(46, 204, 113),  *wxWHITE); // Green
    styleBtn(btnExit, wxColour(149, 165, 166), *wxWHITE); // Gray

    vbox->Add(btnAdd,  0, wxALIGN_CENTER | wxTOP | wxBOTTOM, 10);
    vbox->Add(btnList, 0, wxALIGN_CENTER | wxBOTTOM, 10);
    vbox->Add(btnExit, 0, wxALIGN_CENTER | wxTOP | wxBOTTOM, 18);

    // Footer
    wxStaticText* footer = new wxStaticText(&dlg, wxID_ANY, "© 2025 Movie Ticket Booking");
    footer->SetForegroundColour(wxColour(160, 160, 160));
    wxFont footerFont(wxFontInfo(10).FaceName("Arial"));
    footer->SetFont(footerFont);
    vbox->Add(footer, 0, wxALIGN_CENTER | wxBOTTOM, 8);

    dlg.SetSizerAndFit(vbox);

    // Add Theater
    btnAdd->Bind(wxEVT_BUTTON, [&](wxCommandEvent&) {
        wxDialog addDlg(&dlg, wxID_ANY, "Add Theater", wxDefaultPosition, wxSize(400, 220));
        wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
        wxFlexGridSizer* grid = new wxFlexGridSizer(2, 10, 10);
        grid->AddGrowableCol(1, 1);

        wxStaticText* lblName = new wxStaticText(&addDlg, wxID_ANY, "Name:");
        wxTextCtrl* txtName = new wxTextCtrl(&addDlg, wxID_ANY);

        wxStaticText* lblLocation = new wxStaticText(&addDlg, wxID_ANY, "Location:");
        wxTextCtrl* txtLocation = new wxTextCtrl(&addDlg, wxID_ANY);

        grid->Add(lblName, 0, wxALIGN_CENTER_VERTICAL);
        grid->Add(txtName, 1, wxEXPAND);
        grid->Add(lblLocation, 0, wxALIGN_CENTER_VERTICAL);
        grid->Add(txtLocation, 1, wxEXPAND);

        mainSizer->Add(grid, 1, wxALL | wxEXPAND, 15);

        wxBoxSizer* btnSizer = new wxBoxSizer(wxHORIZONTAL);
        wxButton* btnOK = new wxButton(&addDlg, wxID_OK, "Add");
        wxButton* btnCancel = new wxButton(&addDlg, wxID_CANCEL, "Cancel");
        btnSizer->Add(btnOK, 0, wxRIGHT, 10);
        btnSizer->Add(btnCancel, 0);
        mainSizer->Add(btnSizer, 0, wxALIGN_CENTER | wxBOTTOM, 10);

        addDlg.SetSizerAndFit(mainSizer);

        if (addDlg.ShowModal() == wxID_OK) {
            std::string name = txtName->GetValue().ToStdString();
            std::string location = txtLocation->GetValue().ToStdString();
            if (name.empty() || location.empty()) {
                wxMessageBox("Please enter all required information!", "Error", wxOK | wxICON_ERROR, &addDlg);
                return;
            }
            MovieTheater theater;
            theater.setTheaterName(name);
            theater.setTheaterLocation(location);
            Result<int> result = movie_theater_repos->create(theater);
            if (!result.success) {
                wxMessageBox(wxString::FromUTF8(result.error_message.c_str()), "Error", wxOK | wxICON_ERROR, &addDlg);
            } else {
                wxMessageBox("Theater added successfully!", "Success", wxOK | wxICON_INFORMATION, &addDlg);
            }
        }
    });

    // View Theater List
    btnList->Bind(wxEVT_BUTTON, [&](wxCommandEvent&) {
        Result<std::vector<MovieTheater>> result = movie_theater_repos->findAll();
        if (!result.success || result.data.empty()) {
            wxMessageBox("No theaters found!", "Info", wxOK | wxICON_INFORMATION, &dlg);
            return;
        }
        wxDialog listDlg(&dlg, wxID_ANY, "Theater List", wxDefaultPosition, wxSize(600, 350));
        wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);

        wxListCtrl* listCtrl = new wxListCtrl(&listDlg, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_REPORT);
        listCtrl->InsertColumn(0, "ID", wxLIST_FORMAT_LEFT, 50);
        listCtrl->InsertColumn(1, "Name", wxLIST_FORMAT_LEFT, 200);
        listCtrl->InsertColumn(2, "Location", wxLIST_FORMAT_LEFT, 300);

        long idx = 0;
        for (const auto& t : result.data) {
            long item = listCtrl->InsertItem(idx, wxString::Format("%d", t.getTheaterId()));
            listCtrl->SetItem(item, 1, wxString::FromUTF8(t.getTheaterName().c_str()));
            listCtrl->SetItem(item, 2, wxString::FromUTF8(t.getTheaterLocation().c_str()));
            ++idx;
        }

        sizer->Add(listCtrl, 1, wxEXPAND | wxALL, 10);
        wxButton* btnClose = new wxButton(&listDlg, wxID_ANY, "Close");
        sizer->Add(btnClose, 0, wxALIGN_CENTER | wxBOTTOM, 10);

        btnClose->Bind(wxEVT_BUTTON, [&](wxCommandEvent&) {
            listDlg.EndModal(wxID_OK);
        });

        listDlg.SetSizerAndFit(sizer);
        listDlg.ShowModal();
    });

    btnExit->Bind(wxEVT_BUTTON, [&](wxCommandEvent&) {
        dlg.EndModal(wxID_EXIT);
    });

    dlg.ShowModal();
}