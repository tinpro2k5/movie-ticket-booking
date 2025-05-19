#include "../../include/services/MovieService.h"

MovieService::MovieService(RepositoryRegistry& repoRegistry){
        movie_repos = std::dynamic_pointer_cast<MovieRepository>(repoRegistry.movie_repos);
        if (!movie_repos) {
        Logger::getInstance()->log("Failed to cast to UserRepository", Logger::Level::ERROR);
        std::cerr << "Failed to cast to UserRepository" << std::endl;
        }
    }
void MovieService::getListMovie(){
    Result<vector<Movie>> result = movie_repos->findAll();
    if(!result.success){
        cout << result.error_message << "\n";
        return;
    }
    const vector<Movie>& movies = result.data;
    if(movies.empty()){
        cout << "Phim không tồn tại\n";
        return;
    }
    printMoviesTable(movies);
}
void MovieService::filterMovies(){
    cout << "==========Lọc Phim==========\n";
    cout << "1. ID \n";
    cout << "2. Thể loại\n";
    cout << "3. Tên \n"; 
    cout << "0. Thoát\n";
    cout << "============================\n";
    int choice;
    cout << "Chọn phương thức lọc: \n";
    std::cin >> choice;
        switch (choice){
            case 1:{
            getListMovie();
            int id;
            cout << "Nhap id: \n";
            std::cin >> id;
            while(id < 1){
                cout << "ID không hợp lệ. Nhập lại ID > 1\n";
                std::cin >> id;
            }
            Result<Movie> result = movie_repos->findById(id);
            if(!result.success){
                cout << result.error_message << "\n";
                return;
            }
            const Movie& movie = result.data;
            vector<Movie> movies;
            movies.push_back(movie);
            printMoviesTable(movies);
            break;
        }
            case 2:{
            string input = "";
            std::cin.ignore();
            cout << "Nhập thể loại: \n";
            getline(std::cin, input);
            Result<std::vector<Movie>> result = movie_repos->findByGenre(input);
            if(!result.success){
                cout << result.error_message << "\n";
                return;
            }
            printMoviesTable(result.data);
            break;  
        }
            case 3:{
            string input = "";
            std::cin.ignore();
            cout << "Nhập tên: \n";
            getline(std::cin, input);
            Result<std::vector<Movie>> result = movie_repos->findByName(input);
            if(!result.success){
                cout << result.error_message << "\n";
                return;
            }
            printMoviesTable(result.data);
            break;
        }
            default:{
                return;
            break;
        }
    }
}
void MovieService::manageMovies(User user){
    std::cout << "===== QUẢN LÝ PHIM =====\n";
    std::cout << "1. Thêm phim\n";
    std::cout << "2. Xóa phim\n";
    std::cout << "3. Cập nhật phim\n";
    std::cout << "4. Xem danh sách phim\n";
    std::cout << "0. Thoát\n";
    std::cout << "=============================\n";
    int choice;
    cout << "Nhập lựa chọn của bạn: ";
    std::cin >> choice;
        switch (choice){
            case 1:{
                Movie movie;
                movie.setMovieId(0);
                string input = "";
                std::cin.ignore();
                cout << "Nhập tên phim: \n";
                getline(std::cin, input);
                movie.setMovieTitle(input);
                cout << "Nhập thể loại: \n";
                getline(std::cin, input);
                movie.setMovieGenre(input);
                cout << "Nhap mô tả: \n";
                getline(std::cin, input);
                movie.setMovieDescription(input);
                cout << "Nhập thời gian: \n";
                int duration;
                std::cin >> duration;
                movie.setMovieDuration(duration);
                cout << "Nhập xếp hạng: \n";
                double rating;
                std::cin >> rating;
                movie.setMovieRating(rating);
                string path = "";
                std::cin.ignore();
                cout << "Nhập đường dẫn đến hình ảnh: \n";
                getline(std::cin, path);
                movie.setMoviePosterPath(path);
                cout << "Nhập giá vé: \n";
                int price;
                std::cin >> price;
                if(price <= 0){
                    cout << "Giá vé không hợp lệ. Nhập lại giá vé > 0\n";
                    std::cin >> price;
                }
                movie.setPrice(price);
                Result<int> result = movie_repos->create(movie);
                if(!result.success){
                    cout << result.error_message << "\n";
                    return;
                }else{
                    cout << "Thêm phim thành công \n";
                }
                break;
            }
            case 2:{
                Result<vector<Movie>> list_movie = movie_repos->findAll();
                printMoviesTable(list_movie.data);
                cout << "Nhập ID phim cần xóa: \n";
                int id;
                std::cin >> id;
                while(id < 1){
                    cout << "ID không hợp lệ. Nhập lại ID > 1\n";
                    std::cin >> id;
                }
                Result<bool> result = movie_repos->remove(id);
                if(!result.success){
                    cout << result.error_message << "\n";
                    return;
                }else{
                    cout << "Xóa phim thành công \n";
                }
                break;
            }
            case 3:{
                Result<vector<Movie>> list_movie = movie_repos->findAll();
                printMoviesTable(list_movie.data);
                cout << "Nhap id phim can cap nhat: \n";
                int id;
                std::cin >> id;
                while(id < 1){
                    cout << "ID không hợp lệ. Nhập lại ID > 1\n";
                    std::cin >> id;
                }
                Result<Movie> result = movie_repos->findById(id);
                if(!result.success){
                    cout << result.error_message << "\n";
                    return;
                }
                Movie movie = result.data;     
                string input = "";
                std::cin.ignore();
                cout << "Nhập tên phim: \n";
                getline(std::cin, input);
                if(input.empty()){
                    input = movie.getMovieTitle();
                }
                movie.setMovieTitle(input);
                cout << "Nhập thể loại: \n";
                getline(std::cin, input);
                if(input.empty()){
                    input = movie.getMovieGenre();
                }
                movie.setMovieGenre(input);
                cout << "Nhập mô tả: \n";
                getline(std::cin, input);
                if (input.empty()){
                    input = movie.getMovieDescription();
                }
                movie.setMovieDescription(input);
                cout << "Nhập thời gian: \n";
                int duration;
                std::cin >> duration;
                if(duration == 0){
                    duration = movie.getMovieDuration();
                }
                movie.setMovieDuration(duration);
                cout << "Nhap xep hang: \n";
                double rating;
                std::cin >> rating;
                if(rating == 0){
                    rating = movie.getMovieRating();
                }
                movie.setMovieRating(rating);
                string path = "";
                std::cin.ignore();
                cout << "Nhập đường dẫn hình ảnh: \n";
                getline(std::cin, path);
                if(path.empty()){
                    path = movie.getMoviePosterPath();
                }
                movie.setMoviePosterPath(path);
                cout << "Nhập giá vé: \n";
                int price;
                std::cin >> price;
                if(price == 0){
                    price = movie.getPrice();
                }
                movie.setPrice(price);
                Result<bool> result1 = movie_repos->update(movie);
                if(!result1.success){
                    cout << result1.error_message << "\n";
                    return;
                }else{
                    cout << "Cập nhật phim thành công \n";
                }
                break;
            }
            case 4:
                getListMovie();
                break;
            default:
                cout << "Không có chức năng này\n";
                break;
        }
}

void MovieService::manageMoviesUI(wxWindow* parent, User user) {
    wxDialog dlg(parent, wxID_ANY, "Manage Movies", wxDefaultPosition, wxSize(400, 400));
    wxBoxSizer* vbox = new wxBoxSizer(wxVERTICAL);

    vbox->Add(new wxStaticText(&dlg, wxID_ANY, "===== MANAGE MOVIES ====="), 0, wxALIGN_CENTER | wxTOP | wxBOTTOM, 15);

    wxButton* btnAdd    = new wxButton(&dlg, wxID_ANY, "Add Movie");
    wxButton* btnDelete = new wxButton(&dlg, wxID_ANY, "Delete Movie");
    wxButton* btnUpdate = new wxButton(&dlg, wxID_ANY, "Update Movie");
    wxButton* btnList   = new wxButton(&dlg, wxID_ANY, "List Movies");
    wxButton* btnExit   = new wxButton(&dlg, wxID_EXIT, "Exit");

    vbox->Add(btnAdd,    0, wxEXPAND | wxALL, 8);
    vbox->Add(btnDelete, 0, wxEXPAND | wxALL, 8);
    vbox->Add(btnUpdate, 0, wxEXPAND | wxALL, 8);
    vbox->Add(btnList,   0, wxEXPAND | wxALL, 8);
    vbox->Add(btnExit,   0, wxEXPAND | wxALL, 8);

    dlg.SetSizerAndFit(vbox);

    // Add Movie
    btnAdd->Bind(wxEVT_BUTTON, [&](wxCommandEvent&) {
        wxDialog addDlg(&dlg, wxID_ANY, "Add Movie", wxDefaultPosition, wxSize(400, 450));
        wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

        wxFlexGridSizer* grid = new wxFlexGridSizer(2, 10, 10);
        grid->AddGrowableCol(1, 1);

        wxStaticText* lblName = new wxStaticText(&addDlg, wxID_ANY, "Name:");
        wxTextCtrl* txtName = new wxTextCtrl(&addDlg, wxID_ANY);

        wxStaticText* lblGenre = new wxStaticText(&addDlg, wxID_ANY, "Genre:");
        wxTextCtrl* txtGenre = new wxTextCtrl(&addDlg, wxID_ANY);

        wxStaticText* lblDesc = new wxStaticText(&addDlg, wxID_ANY, "Description:");
        wxTextCtrl* txtDesc = new wxTextCtrl(&addDlg, wxID_ANY, "", wxDefaultPosition, wxSize(200, 60), wxTE_MULTILINE);

        wxStaticText* lblDuration = new wxStaticText(&addDlg, wxID_ANY, "Duration (min):");
        wxTextCtrl* txtDuration = new wxTextCtrl(&addDlg, wxID_ANY);

        wxStaticText* lblRating = new wxStaticText(&addDlg, wxID_ANY, "Rating:");
        wxTextCtrl* txtRating = new wxTextCtrl(&addDlg, wxID_ANY);

        wxStaticText* lblPoster = new wxStaticText(&addDlg, wxID_ANY, "Poster Path:");
        wxTextCtrl* txtPoster = new wxTextCtrl(&addDlg, wxID_ANY);

        wxStaticText* lblPrice = new wxStaticText(&addDlg, wxID_ANY, "Ticket Price:");
        wxTextCtrl* txtPrice = new wxTextCtrl(&addDlg, wxID_ANY);

        grid->Add(lblName, 0, wxALIGN_CENTER_VERTICAL);
        grid->Add(txtName, 1, wxEXPAND);
        grid->Add(lblGenre, 0, wxALIGN_CENTER_VERTICAL);
        grid->Add(txtGenre, 1, wxEXPAND);
        grid->Add(lblDesc, 0, wxALIGN_CENTER_VERTICAL);
        grid->Add(txtDesc, 1, wxEXPAND);
        grid->Add(lblDuration, 0, wxALIGN_CENTER_VERTICAL);
        grid->Add(txtDuration, 1, wxEXPAND);
        grid->Add(lblRating, 0, wxALIGN_CENTER_VERTICAL);
        grid->Add(txtRating, 1, wxEXPAND);
        grid->Add(lblPoster, 0, wxALIGN_CENTER_VERTICAL);
        grid->Add(txtPoster, 1, wxEXPAND);
        grid->Add(lblPrice, 0, wxALIGN_CENTER_VERTICAL);
        grid->Add(txtPrice, 1, wxEXPAND);

        mainSizer->Add(grid, 1, wxALL | wxEXPAND, 15);

        wxBoxSizer* btnSizer = new wxBoxSizer(wxHORIZONTAL);
        wxButton* btnOK = new wxButton(&addDlg, wxID_OK, "Add");
        wxButton* btnCancel = new wxButton(&addDlg, wxID_CANCEL, "Cancel");
        btnSizer->Add(btnOK, 0, wxRIGHT, 10);
        btnSizer->Add(btnCancel, 0);

        mainSizer->Add(btnSizer, 0, wxALIGN_CENTER | wxBOTTOM, 10);

        addDlg.SetSizerAndFit(mainSizer);

        if (addDlg.ShowModal() == wxID_OK) {
            Movie movie;
            movie.setMovieId(0);
            movie.setMovieTitle(txtName->GetValue().ToStdString());
            movie.setMovieGenre(txtGenre->GetValue().ToStdString());
            movie.setMovieDescription(txtDesc->GetValue().ToStdString());
            movie.setMoviePosterPath(txtPoster->GetValue().ToStdString());

            // Validate and convert duration, rating, price
            long duration = 0;
            double rating = 0.0;
            long price = 0;
            bool ok1 = txtDuration->GetValue().ToLong(&duration);
            bool ok2 = txtRating->GetValue().ToDouble(&rating);
            bool ok3 = txtPrice->GetValue().ToLong(&price);

            // Simple validation
            if (movie.getMovieTitle().empty() || movie.getMovieGenre().empty() ||
                !ok1 || duration <= 0 ||
                !ok2 || rating < 0.0 ||
                !ok3 || price <= 0) {
                wxMessageBox("Please enter valid information for all required fields!", "Input Error", wxOK | wxICON_ERROR, &addDlg);
                return;
            }

            movie.setMovieDuration(duration);
            movie.setMovieRating(rating);
            movie.setPrice(price);

            Result<int> result = movie_repos->create(movie);
            if (!result.success) {
                wxMessageBox(wxString::FromUTF8(result.error_message.c_str()), "Error", wxOK | wxICON_ERROR, &addDlg);
            } else {
                wxMessageBox("Movie added successfully!", "Success", wxOK | wxICON_INFORMATION, &addDlg);
            }
        }
    });

    // Delete Movie
    btnDelete->Bind(wxEVT_BUTTON, [&](wxCommandEvent&) {
        Result<vector<Movie>> list_movie = movie_repos->findAll();
        if (!list_movie.success || list_movie.data.empty()) {
            wxMessageBox("No movies found!", "Error", wxOK | wxICON_ERROR, &dlg);
            return;
        }

        wxDialog delDlg(&dlg, wxID_ANY, "Delete Movies", wxDefaultPosition, wxSize(900, 400));
        wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);

        // Cho phép chọn nhiều dòng
        wxListCtrl* listCtrl = new wxListCtrl(&delDlg, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_REPORT);
        
        // Add columns
        listCtrl->InsertColumn(0, "ID", wxLIST_FORMAT_LEFT, 40);
        listCtrl->InsertColumn(1, "Name", wxLIST_FORMAT_LEFT, 150);
        listCtrl->InsertColumn(2, "Genre", wxLIST_FORMAT_LEFT, 80);
        listCtrl->InsertColumn(3, "Description", wxLIST_FORMAT_LEFT, 300);
        listCtrl->InsertColumn(4, "Duration", wxLIST_FORMAT_LEFT, 70);
        listCtrl->InsertColumn(5, "Rating", wxLIST_FORMAT_LEFT, 60);
        listCtrl->InsertColumn(6, "Poster Path", wxLIST_FORMAT_LEFT, 120);
        listCtrl->InsertColumn(7, "Price", wxLIST_FORMAT_LEFT, 80);

        // Add data
        long idx = 0;
        for (const auto& m : list_movie.data) {
            long item = listCtrl->InsertItem(idx, wxString::Format("%d", m.getMovieId()));
            listCtrl->SetItem(item, 1, m.getMovieTitle());
            listCtrl->SetItem(item, 2, m.getMovieGenre());
            listCtrl->SetItem(item, 3, m.getMovieDescription());
            listCtrl->SetItem(item, 4, wxString::Format("%d", m.getMovieDuration()));
            listCtrl->SetItem(item, 5, wxString::Format("%.1f", m.getMovieRating()));
            listCtrl->SetItem(item, 6, m.getMoviePosterPath());
            listCtrl->SetItem(item, 7, wxString::Format("%d", m.getPrice()));
            listCtrl->SetItemData(item, idx);
            ++idx;
        }

        sizer->Add(listCtrl, 1, wxEXPAND | wxALL, 10);

        wxBoxSizer* btnSizer = new wxBoxSizer(wxHORIZONTAL);
        wxButton* btnDeleteSelected = new wxButton(&delDlg, wxID_OK, "Delete Selected");
        wxButton* btnCancel = new wxButton(&delDlg, wxID_CANCEL, "Cancel");
        btnSizer->Add(btnDeleteSelected, 0, wxRIGHT, 10);
        btnSizer->Add(btnCancel, 0);

        sizer->Add(btnSizer, 0, wxALIGN_CENTER | wxBOTTOM, 10);

        delDlg.SetSizerAndFit(sizer);

        btnDeleteSelected->Bind(wxEVT_BUTTON, [&](wxCommandEvent&) {
            // Lấy các dòng được chọn
            long item = -1;
            std::vector<int> idsToDelete;
            for (;;) {
                item = listCtrl->GetNextItem(item, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
                if (item == -1) break;
                int id = wxAtoi(listCtrl->GetItemText(item, 0));
                idsToDelete.push_back(id);
            }
            if (idsToDelete.empty()) {
                wxMessageBox("Please select at least one movie to delete.", "Warning", wxOK | wxICON_WARNING, &delDlg);
                return;
            }
            int deletedCount = 0;
            wxString errorMsg;
            for (int id : idsToDelete) {
                Result<bool> result = movie_repos->remove(id);
                if (!result.success) {
                    errorMsg += wxString::Format("ID %d: %s\n", id, result.error_message);
                } else {
                    deletedCount++;
                }
            }
            if (deletedCount > 0)
                wxMessageBox(wxString::Format("%d movie(s) deleted successfully!", deletedCount), "Success", wxOK | wxICON_INFORMATION, &delDlg);
            if (!errorMsg.IsEmpty())
                wxMessageBox("Some movies could not be deleted:\n" + errorMsg, "Warning", wxOK | wxICON_WARNING, &delDlg);

            delDlg.EndModal(wxID_OK);
        });

        btnCancel->Bind(wxEVT_BUTTON, [&](wxCommandEvent&) {
            delDlg.EndModal(wxID_CANCEL);
        });

        delDlg.ShowModal();
    });

    // Update Movie
    btnUpdate->Bind(wxEVT_BUTTON, [&](wxCommandEvent&) {
        Result<vector<Movie>> list_movie = movie_repos->findAll();
        if (!list_movie.success || list_movie.data.empty()) {
            wxMessageBox("No movies found!", "Error", wxOK | wxICON_ERROR, &dlg);
            return;
        }

        wxDialog editDlg(&dlg, wxID_ANY, "Edit Movies", wxDefaultPosition, wxSize(1000, 400));
        wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);

        wxListCtrl* listCtrl = new wxListCtrl(&editDlg, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_REPORT | wxLC_SINGLE_SEL | wxLC_EDIT_LABELS);

        // Add columns
        listCtrl->InsertColumn(0, "ID", wxLIST_FORMAT_LEFT, 40);
        listCtrl->InsertColumn(1, "Name", wxLIST_FORMAT_LEFT, 150);
        listCtrl->InsertColumn(2, "Genre", wxLIST_FORMAT_LEFT, 80);
        listCtrl->InsertColumn(3, "Description", wxLIST_FORMAT_LEFT, 400);
        listCtrl->InsertColumn(4, "Duration", wxLIST_FORMAT_LEFT, 70);
        listCtrl->InsertColumn(5, "Rating", wxLIST_FORMAT_LEFT, 60);
        listCtrl->InsertColumn(6, "Poster Path", wxLIST_FORMAT_LEFT, 120);
        listCtrl->InsertColumn(7, "Price", wxLIST_FORMAT_LEFT, 80);

        // Add data
        long idx = 0;
        for (const auto& m : list_movie.data) {
            long item = listCtrl->InsertItem(idx, wxString::Format("%d", m.getMovieId()));
            listCtrl->SetItem(item, 1, m.getMovieTitle());
            listCtrl->SetItem(item, 2, m.getMovieGenre());
            listCtrl->SetItem(item, 3, m.getMovieDescription());
            listCtrl->SetItem(item, 4, wxString::Format("%d", m.getMovieDuration()));
            listCtrl->SetItem(item, 5, wxString::Format("%.1f", m.getMovieRating()));
            listCtrl->SetItem(item, 6, m.getMoviePosterPath());
            listCtrl->SetItem(item, 7, wxString::Format("%d", m.getPrice()));
            listCtrl->SetItemData(item, idx);
            ++idx;
        }

        sizer->Add(listCtrl, 1, wxEXPAND | wxALL, 10);

        wxBoxSizer* btnSizer = new wxBoxSizer(wxHORIZONTAL);
        wxButton* btnSave = new wxButton(&editDlg, wxID_OK, "Save Changes");
        wxButton* btnCancel = new wxButton(&editDlg, wxID_CANCEL, "Cancel");
        btnSizer->Add(btnSave, 0, wxRIGHT, 10);
        btnSizer->Add(btnCancel, 0);

        sizer->Add(btnSizer, 0, wxALIGN_CENTER | wxBOTTOM, 10);

        editDlg.SetSizerAndFit(sizer);

        // Cho phép sửa các trường (trừ ID)
        // Cho phép sửa khi double-click vào dòng
        listCtrl->Bind(wxEVT_LIST_ITEM_ACTIVATED, [&](wxListEvent& event) {
            long item = event.GetIndex();
            int id = wxAtoi(listCtrl->GetItemText(item, 0));
            wxString name = listCtrl->GetItemText(item, 1);
            wxString genre = listCtrl->GetItemText(item, 2);
            wxString desc = listCtrl->GetItemText(item, 3);
            wxString duration = listCtrl->GetItemText(item, 4);
            wxString rating = listCtrl->GetItemText(item, 5);
            wxString poster = listCtrl->GetItemText(item, 6);
            wxString price = listCtrl->GetItemText(item, 7);

            wxDialog editRowDlg(&editDlg, wxID_ANY, "Edit Movie", wxDefaultPosition, wxSize(400, 450));
            wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
            wxFlexGridSizer* grid = new wxFlexGridSizer(2, 10, 10);
            grid->AddGrowableCol(1, 1);

            grid->Add(new wxStaticText(&editRowDlg, wxID_ANY, "Name:"), 0, wxALIGN_CENTER_VERTICAL);
            wxTextCtrl* txtName = new wxTextCtrl(&editRowDlg, wxID_ANY, name);
            grid->Add(txtName, 1, wxEXPAND);

            grid->Add(new wxStaticText(&editRowDlg, wxID_ANY, "Genre:"), 0, wxALIGN_CENTER_VERTICAL);
            wxTextCtrl* txtGenre = new wxTextCtrl(&editRowDlg, wxID_ANY, genre);
            grid->Add(txtGenre, 1, wxEXPAND);

            grid->Add(new wxStaticText(&editRowDlg, wxID_ANY, "Description:"), 0, wxALIGN_CENTER_VERTICAL);
            wxTextCtrl* txtDesc = new wxTextCtrl(&editRowDlg, wxID_ANY, desc, wxDefaultPosition, wxSize(200, 60), wxTE_MULTILINE);
            grid->Add(txtDesc, 1, wxEXPAND);

            grid->Add(new wxStaticText(&editRowDlg, wxID_ANY, "Duration (min):"), 0, wxALIGN_CENTER_VERTICAL);
            wxTextCtrl* txtDuration = new wxTextCtrl(&editRowDlg, wxID_ANY, duration);
            grid->Add(txtDuration, 1, wxEXPAND);

            grid->Add(new wxStaticText(&editRowDlg, wxID_ANY, "Rating:"), 0, wxALIGN_CENTER_VERTICAL);
            wxTextCtrl* txtRating = new wxTextCtrl(&editRowDlg, wxID_ANY, rating);
            grid->Add(txtRating, 1, wxEXPAND);

            grid->Add(new wxStaticText(&editRowDlg, wxID_ANY, "Poster Path:"), 0, wxALIGN_CENTER_VERTICAL);
            wxTextCtrl* txtPoster = new wxTextCtrl(&editRowDlg, wxID_ANY, poster);
            grid->Add(txtPoster, 1, wxEXPAND);

            grid->Add(new wxStaticText(&editRowDlg, wxID_ANY, "Ticket Price:"), 0, wxALIGN_CENTER_VERTICAL);
            wxTextCtrl* txtPrice = new wxTextCtrl(&editRowDlg, wxID_ANY, price);
            grid->Add(txtPrice, 1, wxEXPAND);

            mainSizer->Add(grid, 1, wxALL | wxEXPAND, 15);

            wxBoxSizer* btnSizer = new wxBoxSizer(wxHORIZONTAL);
            wxButton* btnOK = new wxButton(&editRowDlg, wxID_OK, "Save");
            wxButton* btnCancel = new wxButton(&editRowDlg, wxID_CANCEL, "Cancel");
            btnSizer->Add(btnOK, 0, wxRIGHT, 10);
            btnSizer->Add(btnCancel, 0);
            mainSizer->Add(btnSizer, 0, wxALIGN_CENTER | wxBOTTOM, 10);

            editRowDlg.SetSizerAndFit(mainSizer);

            if (editRowDlg.ShowModal() == wxID_OK) {
                listCtrl->SetItem(item, 1, txtName->GetValue());
                listCtrl->SetItem(item, 2, txtGenre->GetValue());
                listCtrl->SetItem(item, 3, txtDesc->GetValue());
                listCtrl->SetItem(item, 4, txtDuration->GetValue());
                listCtrl->SetItem(item, 5, txtRating->GetValue());
                listCtrl->SetItem(item, 6, txtPoster->GetValue());
                listCtrl->SetItem(item, 7, txtPrice->GetValue());
            }
        });

    btnSave->Bind(wxEVT_BUTTON, [&](wxCommandEvent&) {
        int updatedCount = 0;
        wxString errorMsg;
        for (long i = 0; i < listCtrl->GetItemCount(); ++i) {
            int id = wxAtoi(listCtrl->GetItemText(i, 0));
            std::string name = listCtrl->GetItemText(i, 1).ToStdString();
            std::string genre = listCtrl->GetItemText(i, 2).ToStdString();
            std::string desc = listCtrl->GetItemText(i, 3).ToStdString();
            long duration = 0;
            double rating = 0.0;
            std::string poster = listCtrl->GetItemText(i, 6).ToStdString();
            long price = 0;

            bool ok1 = listCtrl->GetItemText(i, 4).ToLong(&duration);
            bool ok2 = listCtrl->GetItemText(i, 5).ToDouble(&rating);
            bool ok3 = listCtrl->GetItemText(i, 7).ToLong(&price);

            if (name.empty() || genre.empty() || !ok1 || duration <= 0 || !ok2 || rating < 0.0 || !ok3 || price <= 0) {
                errorMsg += wxString::Format("Row %ld: Invalid data\n", i+1);
                continue;
            }

            Movie movie;
            movie.setMovieId(id);
            movie.setMovieTitle(name);
            movie.setMovieGenre(genre);
            movie.setMovieDescription(desc);
            movie.setMovieDuration(duration);
            movie.setMovieRating(rating);
            movie.setMoviePosterPath(poster);
            movie.setPrice(price);

            Result<bool> result = movie_repos->update(movie);
            if (!result.success) {
                errorMsg += wxString::Format("Row %ld: %s\n", i+1, result.error_message);
            } else {
                updatedCount++;
            }
        }
        if (updatedCount > 0)
            wxMessageBox("Movies updated successfully!", "Success", wxOK | wxICON_INFORMATION, &editDlg);
        else
            wxMessageBox("No movies were updated:\n" + errorMsg, "Warning", wxOK | wxICON_WARNING, &editDlg);

        editDlg.EndModal(wxID_OK);
    });

        btnCancel->Bind(wxEVT_BUTTON, [&](wxCommandEvent&) {
            editDlg.EndModal(wxID_CANCEL);
        });

        editDlg.ShowModal();
    });

    // List Movies
    btnList->Bind(wxEVT_BUTTON, [&](wxCommandEvent&) {
        Result<vector<Movie>> result = movie_repos->findAll();
        if (!result.success || result.data.empty()) {
            wxMessageBox("No movies found!", "Info", wxOK | wxICON_INFORMATION, &dlg);
            return;
        }

        wxDialog listDlg(&dlg, wxID_ANY, "Movie List", wxDefaultPosition, wxSize(1000, 400)); 
        wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);

        wxListCtrl* listCtrl = new wxListCtrl(&listDlg, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_REPORT | wxLC_SINGLE_SEL);

        // Add columns
        listCtrl->InsertColumn(0, "ID", wxLIST_FORMAT_LEFT, 40);
        listCtrl->InsertColumn(1, "Name", wxLIST_FORMAT_LEFT, 150);
        listCtrl->InsertColumn(2, "Genre", wxLIST_FORMAT_LEFT, 80);
        listCtrl->InsertColumn(3, "Description", wxLIST_FORMAT_LEFT, 400);
        listCtrl->InsertColumn(4, "Duration", wxLIST_FORMAT_LEFT, 70);
        listCtrl->InsertColumn(5, "Rating", wxLIST_FORMAT_LEFT, 60);
        listCtrl->InsertColumn(6, "Price", wxLIST_FORMAT_LEFT, 80);

        // Add data
        long idx = 0;
        for (const auto& m : result.data) {
            long item = listCtrl->InsertItem(idx, wxString::Format("%d", m.getMovieId()));
            listCtrl->SetItem(item, 1, m.getMovieTitle());
            listCtrl->SetItem(item, 2, m.getMovieGenre());
            listCtrl->SetItem(item, 3, m.getMovieDescription());
            listCtrl->SetItem(item, 4, wxString::Format("%d", m.getMovieDuration()));
            listCtrl->SetItem(item, 5, wxString::Format("%.1f", m.getMovieRating()));
            listCtrl->SetItem(item, 6, wxString::Format("%d", m.getPrice()));
            listCtrl->SetItemData(item, idx);
            ++idx;
        }

        // Hiện chi tiết khi double-click (đề phòng trường hợp description dài)
        listCtrl->Bind(wxEVT_LIST_ITEM_ACTIVATED, [&](wxListEvent& event) {
            long item = event.GetIndex();
            wxString desc = listCtrl->GetItemText(item, 3);
            wxMessageBox(desc, "Movie Description", wxOK | wxICON_INFORMATION, &listDlg);
        });

        sizer->Add(listCtrl, 1, wxEXPAND | wxALL, 10);

        wxButton* btnClose = new wxButton(&listDlg, wxID_OK, "Close");
        sizer->Add(btnClose, 0, wxALIGN_CENTER | wxBOTTOM, 10);

        listDlg.SetSizerAndFit(sizer);

        btnClose->Bind(wxEVT_BUTTON, [&](wxCommandEvent&) {
            listDlg.EndModal(wxID_OK);
        });

        listDlg.ShowModal();
    });

    // Exit
    btnExit->Bind(wxEVT_BUTTON, [&](wxCommandEvent&) {
        dlg.EndModal(wxID_EXIT);
    });

    dlg.ShowModal();
}