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
        Movie movie;
        movie.setMovieId(0);

        wxTextEntryDialog nameDlg(&dlg, "Enter movie name:", "Add Movie");
        if (nameDlg.ShowModal() != wxID_OK) return;
        movie.setMovieTitle(nameDlg.GetValue().ToStdString());

        wxTextEntryDialog genreDlg(&dlg, "Enter genre:", "Add Movie");
        if (genreDlg.ShowModal() != wxID_OK) return;
        movie.setMovieGenre(genreDlg.GetValue().ToStdString());

        wxTextEntryDialog descDlg(&dlg, "Enter description:", "Add Movie");
        if (descDlg.ShowModal() != wxID_OK) return;
        movie.setMovieDescription(descDlg.GetValue().ToStdString());

        wxTextEntryDialog durationDlg(&dlg, "Enter duration (minutes):", "Add Movie");
        if (durationDlg.ShowModal() != wxID_OK) return;
        movie.setMovieDuration(std::stoi(durationDlg.GetValue().ToStdString()));

        wxTextEntryDialog ratingDlg(&dlg, "Enter rating:", "Add Movie");
        if (ratingDlg.ShowModal() != wxID_OK) return;
        movie.setMovieRating(std::stod(ratingDlg.GetValue().ToStdString()));

        wxTextEntryDialog posterDlg(&dlg, "Enter poster path:", "Add Movie");
        if (posterDlg.ShowModal() != wxID_OK) return;
        movie.setMoviePosterPath(posterDlg.GetValue().ToStdString());

        wxTextEntryDialog priceDlg(&dlg, "Enter ticket price:", "Add Movie");
        if (priceDlg.ShowModal() != wxID_OK) return;
        movie.setPrice(std::stoi(priceDlg.GetValue().ToStdString()));

        Result<int> result = movie_repos->create(movie);
        if (!result.success) {
            wxMessageBox(wxString::FromUTF8(result.error_message.c_str()), "Error", wxOK | wxICON_ERROR, &dlg);
        } else {
            wxMessageBox("Movie added successfully!", "Success", wxOK | wxICON_INFORMATION, &dlg);
        }
    });

    // Delete Movie
    btnDelete->Bind(wxEVT_BUTTON, [&](wxCommandEvent&) {
        Result<vector<Movie>> list_movie = movie_repos->findAll();
        if (!list_movie.success || list_movie.data.empty()) {
            wxMessageBox("No movies found!", "Error", wxOK | wxICON_ERROR, &dlg);
            return;
        }
        wxArrayString choices;
        for (const auto& m : list_movie.data) {
            choices.Add(wxString::Format("%d - %s", m.getMovieId(), m.getMovieTitle()));
        }
        wxSingleChoiceDialog delDlg(&dlg, "Select movie to delete:", "Delete Movie", choices);
        if (delDlg.ShowModal() == wxID_OK) {
            int idx = delDlg.GetSelection();
            int id = list_movie.data[idx].getMovieId();
            Result<bool> result = movie_repos->remove(id);
            if (!result.success) {
                wxMessageBox(wxString::FromUTF8(result.error_message.c_str()), "Error", wxOK | wxICON_ERROR, &dlg);
            } else {
                wxMessageBox("Movie deleted successfully!", "Success", wxOK | wxICON_INFORMATION, &dlg);
            }
        }
    });

    // Update Movie
    btnUpdate->Bind(wxEVT_BUTTON, [&](wxCommandEvent&) {
        Result<vector<Movie>> list_movie = movie_repos->findAll();
        if (!list_movie.success || list_movie.data.empty()) {
            wxMessageBox("No movies found!", "Error", wxOK | wxICON_ERROR, &dlg);
            return;
        }
        wxArrayString choices;
        for (const auto& m : list_movie.data) {
            choices.Add(wxString::Format("%d - %s", m.getMovieId(), m.getMovieTitle()));
        }
        wxSingleChoiceDialog updDlg(&dlg, "Select movie to update:", "Update Movie", choices);
        if (updDlg.ShowModal() == wxID_OK) {
            int idx = updDlg.GetSelection();
            Movie movie = list_movie.data[idx];

            wxTextEntryDialog nameDlg(&dlg, "Enter movie name (leave blank to keep current):", "Update Movie", movie.getMovieTitle());
            if (nameDlg.ShowModal() == wxID_OK && !nameDlg.GetValue().IsEmpty())
                movie.setMovieTitle(nameDlg.GetValue().ToStdString());

            wxTextEntryDialog genreDlg(&dlg, "Enter genre (leave blank to keep current):", "Update Movie", movie.getMovieGenre());
            if (genreDlg.ShowModal() == wxID_OK && !genreDlg.GetValue().IsEmpty())
                movie.setMovieGenre(genreDlg.GetValue().ToStdString());

            wxTextEntryDialog descDlg(&dlg, "Enter description (leave blank to keep current):", "Update Movie", movie.getMovieDescription());
            if (descDlg.ShowModal() == wxID_OK && !descDlg.GetValue().IsEmpty())
                movie.setMovieDescription(descDlg.GetValue().ToStdString());

            wxTextEntryDialog durationDlg(&dlg, "Enter duration (leave blank to keep current):", "Update Movie", wxString::Format("%d", movie.getMovieDuration()));
            if (durationDlg.ShowModal() == wxID_OK && !durationDlg.GetValue().IsEmpty())
                movie.setMovieDuration(std::stoi(durationDlg.GetValue().ToStdString()));

            wxTextEntryDialog ratingDlg(&dlg, "Enter rating (leave blank to keep current):", "Update Movie", wxString::Format("%.1f", movie.getMovieRating()));
            if (ratingDlg.ShowModal() == wxID_OK && !ratingDlg.GetValue().IsEmpty())
                movie.setMovieRating(std::stod(ratingDlg.GetValue().ToStdString()));

            wxTextEntryDialog posterDlg(&dlg, "Enter poster path (leave blank to keep current):", "Update Movie", movie.getMoviePosterPath());
            if (posterDlg.ShowModal() == wxID_OK && !posterDlg.GetValue().IsEmpty())
                movie.setMoviePosterPath(posterDlg.GetValue().ToStdString());

            wxTextEntryDialog priceDlg(&dlg, "Enter ticket price (leave blank to keep current):", "Update Movie", wxString::Format("%d", movie.getPrice()));
            if (priceDlg.ShowModal() == wxID_OK && !priceDlg.GetValue().IsEmpty())
                movie.setPrice(std::stoi(priceDlg.GetValue().ToStdString()));

            Result<bool> result1 = movie_repos->update(movie);
            if (!result1.success) {
                wxMessageBox(wxString::FromUTF8(result1.error_message.c_str()), "Error", wxOK | wxICON_ERROR, &dlg);
            } else {
                wxMessageBox("Movie updated successfully!", "Success", wxOK | wxICON_INFORMATION, &dlg);
            }
        }
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

        // Hiện chi tiết khi double-click
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