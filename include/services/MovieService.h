#ifndef MOVIESERVICE_H
#define MOVIESERVICE_H

#include "../../include/repositories/MovieRepository.h"
#include "../../include/app/RepositoryRegistry.h"


class MovieService{
    std::shared_ptr<MovieRepository> movie_repos;
    public:
    MovieService(RepositoryRegistry& repoRegistry){
        movie_repos = std::dynamic_pointer_cast<MovieRepository>(repoRegistry.movie_repos);
        if (!movie_repos) {
        Logger::getInstance()->log("Failed to cast to UserRepository", Logger::Level::ERROR);
        std::cerr << "Failed to cast to UserRepository" << std::endl;
        }
    }
    void getListMovie(){
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
    void filterMovies(){
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
    void manageMovies(User user){
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
};

#endif


