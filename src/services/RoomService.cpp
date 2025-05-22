#include "../../include/services/RoomService.h"
RoomService::RoomService(RepositoryRegistry& repoRegistry){
    room_repos = std::dynamic_pointer_cast<RoomRepository>(repoRegistry.room_repos);
    movie_theater_repos = std::dynamic_pointer_cast<MovieTheaterRepository>(repoRegistry.movie_theater_repos);
    if (!room_repos) {
        Logger::getInstance()->log("Failed to cast to RoomRepository", Logger::Level::ERROR);
        std::cerr << "Failed to cast to RoomRepository" << std::endl;
    }
    if (!movie_theater_repos) {
        Logger::getInstance()->log("Failed to cast to MovieTheaterRepository", Logger::Level::ERROR);
        std::cerr << "Failed to cast to MovieTheaterRepository" << std::endl;
    }
}

void RoomService::manageRoom(User user){
    cout << "===== QUẢN LÝ PHÒNG =====\n";
    cout << "1. Thêm phòng\n";
    cout << "2. Xem danh sách phòng\n";
    cout << "0. Thoát\n";
    cout << "=========================\n";
    int choice;
    cout << "Nhập lựa chọn của bạn: ";
    std::cin >> choice;
    switch (choice) {
        case 1: {
            Result<vector<Room>> list_room = room_repos->findAll();
            if (!list_room.success) {
                std::cout << list_room.error_message << "\n";
                return;
            }
            printRoomsTable(list_room.data);
            Room room;
            int room_id;
            cout << "Nhập ID phòng: \n";
            std::cin >> room_id;
            while(room_id < 1){
                cout << "Id không hợp lệ! Nhập lại id > 1\n";
                std::cin >> room_id;
            }
            room.setRoomId(room_id);
            int theater_id;
            cout << "Nhập ID rạp: \n";
            std::cin >> theater_id;
            while(theater_id < 1){
                cout << "Id không hợp lệ! Nhập lại id > 1\n";
                std::cin >> theater_id;
            }
            room.setTheaterId(theater_id);
            int capacity;
            cout << "Nhập sức chứa phòng: \n";
            std::cin >> capacity;
            while(capacity < 1){
                cout << "Sức chứa không hợp lệ! Nhập lại sức chứa > 1\n";
                std::cin >> capacity;
            }
            room.setRoomCapacity(capacity);
            string input = "";
            std::cin.ignore();
            cout << "Nhập tên phòng: \n";
            getline(std::cin, input);
            room.setRoomName(input);
            Result<int> result = room_repos->create(room);
            if(!result.success){
                cout << result.error_message << "\n";
                return;
            }else{
                cout << "Thêm phòng thành công \n";
            }
            break;
        }
        case 2: {
            vector<Room> rooms;
            Result<vector<Room>> result = room_repos->findAll();
            if (!result.success) {
                std::cout << result.error_message << "\n";
                return;
        }
            printRoomsTable(result.data);
            break;
        }
        default:
            return;
        }
    }
void RoomService::manageRoomUI(wxWindow* parent, User user) {
    wxDialog dlg(parent, wxID_ANY, "Room Management", wxDefaultPosition, wxSize(500, 350));
    wxBoxSizer* vbox = new wxBoxSizer(wxVERTICAL);

    wxButton* btnAdd = new wxButton(&dlg, wxID_ANY, "Add Room");
    wxButton* btnList = new wxButton(&dlg, wxID_ANY, "View Room List");
    wxButton* btnExit = new wxButton(&dlg, wxID_EXIT, "Exit");

    vbox->Add(btnAdd, 0, wxEXPAND | wxALL, 10);
    vbox->Add(btnList, 0, wxEXPAND | wxALL, 10);
    vbox->Add(btnExit, 0, wxEXPAND | wxALL, 10);

    dlg.SetSizerAndFit(vbox);

    // Add Room
    btnAdd->Bind(wxEVT_BUTTON, [&](wxCommandEvent&) {
        // Lấy danh sách rạp
        Result<std::vector<MovieTheater>> theaters = movie_theater_repos->findAll();
        if (!theaters.success || theaters.data.empty()) {
            wxMessageBox("No theaters found! Please add a theater first.", "Error", wxOK | wxICON_ERROR, &dlg);
            return;
        }

        wxDialog addDlg(&dlg, wxID_ANY, "Add Room", wxDefaultPosition, wxSize(400, 320));
        wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
        wxFlexGridSizer* grid = new wxFlexGridSizer(2, 10, 10);
        grid->AddGrowableCol(1, 1);


        wxStaticText* lblTheater = new wxStaticText(&addDlg, wxID_ANY, "Theater:");
        wxArrayString theaterChoices;
        std::vector<int> theaterIds;
        for (const auto& t : theaters.data) {
            theaterChoices.Add(wxString::Format("%d - %s", t.getTheaterId(), t.getTheaterName()));
            theaterIds.push_back(t.getTheaterId());
        }
        wxChoice* choiceTheater = new wxChoice(&addDlg, wxID_ANY, wxDefaultPosition, wxDefaultSize, theaterChoices);
        choiceTheater->SetSelection(0);

        wxStaticText* lblCapacity = new wxStaticText(&addDlg, wxID_ANY, "Capacity:");
        wxTextCtrl* txtCapacity = new wxTextCtrl(&addDlg, wxID_ANY);

        wxStaticText* lblName = new wxStaticText(&addDlg, wxID_ANY, "Room Name:");
        wxTextCtrl* txtName = new wxTextCtrl(&addDlg, wxID_ANY);


        grid->Add(lblTheater, 0, wxALIGN_CENTER_VERTICAL);
        grid->Add(choiceTheater, 1, wxEXPAND);
        grid->Add(lblCapacity, 0, wxALIGN_CENTER_VERTICAL);
        grid->Add(txtCapacity, 1, wxEXPAND);
        grid->Add(lblName, 0, wxALIGN_CENTER_VERTICAL);
        grid->Add(txtName, 1, wxEXPAND);

        mainSizer->Add(grid, 1, wxALL | wxEXPAND, 15);

        wxBoxSizer* btnSizer = new wxBoxSizer(wxHORIZONTAL);
        wxButton* btnOK = new wxButton(&addDlg, wxID_OK, "Add");
        wxButton* btnCancel = new wxButton(&addDlg, wxID_CANCEL, "Cancel");
        btnSizer->Add(btnOK, 0, wxRIGHT, 10);
        btnSizer->Add(btnCancel, 0);
        mainSizer->Add(btnSizer, 0, wxALIGN_CENTER | wxBOTTOM, 10);

        addDlg.SetSizerAndFit(mainSizer);

        if (addDlg.ShowModal() == wxID_OK) {
            long capacity = 0;
            std::string name = txtName->GetValue().ToStdString();
            bool ok2 = txtCapacity->GetValue().ToLong(&capacity);
            int theaterSel = choiceTheater->GetSelection();
            int theater_id = (theaterSel >= 0 && theaterSel < (int)theaterIds.size()) ? theaterIds[theaterSel] : -1;

            if (theater_id < 1 || !ok2 || capacity < 1 || name.empty()) {
                wxMessageBox("Please enter valid information for all fields!", "Input Error", wxOK | wxICON_ERROR, &addDlg);
                return;
            }
            Room room;
            // Không set room_id, để DB tự sinh
            room.setTheaterId(theater_id);
            room.setRoomCapacity(capacity);
            room.setRoomName(name);

            Result<int> result = room_repos->create(room);
            if (!result.success) {
                wxMessageBox(wxString::FromUTF8(result.error_message.c_str()), "Error", wxOK | wxICON_ERROR, &addDlg);
            } else {
                wxMessageBox("Room added successfully!", "Success", wxOK | wxICON_INFORMATION, &addDlg);
            }
        }
    });
    // View Room List
    btnList->Bind(wxEVT_BUTTON, [&](wxCommandEvent&) {
        Result<std::vector<Room>> result = room_repos->findAll();
        if (!result.success || result.data.empty()) {
            wxMessageBox("No rooms found!", "Info", wxOK | wxICON_INFORMATION, &dlg);
            return;
        }
        wxDialog listDlg(&dlg, wxID_ANY, "Room List", wxDefaultPosition, wxSize(600, 350));
        wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);

        wxListCtrl* listCtrl = new wxListCtrl(&listDlg, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_REPORT);
        listCtrl->InsertColumn(0, "ID", wxLIST_FORMAT_LEFT, 50);
        listCtrl->InsertColumn(1, "Theater ID", wxLIST_FORMAT_LEFT, 100);
        listCtrl->InsertColumn(2, "Name", wxLIST_FORMAT_LEFT, 200);
        listCtrl->InsertColumn(3, "Capacity", wxLIST_FORMAT_LEFT, 100);

        long idx = 0;
        for (const auto& r : result.data) {
            long item = listCtrl->InsertItem(idx, wxString::Format("%d", r.getRoomId()));
            listCtrl->SetItem(item, 1, wxString::Format("%d", r.getTheaterId()));
            listCtrl->SetItem(item, 2, wxString::FromUTF8(r.getRoomName().c_str()));
            listCtrl->SetItem(item, 3, wxString::Format("%d", r.getRoomCapacity()));
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