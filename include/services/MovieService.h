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
            cout << "Khong co phim trong CSDL \n";
            return;
        }
        cout << "Danh sach phim: \n";
        for(const Movie& movie : movies){
            std::cout << "Movie ID: " << movie.getMovieId() << std::endl;
            std::cout << "Movie Title: " << movie.getMovieTitle() << std::endl;
            std::cout << "Movie Genre: " << movie.getMovieGenre() << std::endl;
            std::cout << "Movie Description: " << movie.getMovieDescription() << std::endl;
            std::cout << "Movie Duration: " << movie.getMovieDuration() << std::endl;
            std::cout << "Movie Rating: " << movie.getMovieRating() << std::endl;
            std::cout << "Movie Poster Path: " << movie.getMoviePosterPath() << std::endl;
            std::cout << "Movie Price: " << movie.getPrice() << std::endl;
        }
    }
    void filterMovies(){
        cout << "--------------------------------\n";
        cout << "Cac phuong thuc loc phim \n";
        cout << "0. Out khoi loc\n";
        cout << "1. ID \n";
        cout << "2. The Loai\n";
        cout << "3. Ten \n"; 
        cout << "--------------------------------\n";
        int choice;
        cout << "Chon cach loc: \n";
        std::cin >> choice;
            switch (choice){
                case 1:{
                int id;
                cout << "Nhap id: \n";
                std::cin >> id;
                while(id < 1){
                    cout << "Id khong hop le! Nhap lai id > 1\n";
                    std::cin >> id;
                }
                Result<Movie> result = movie_repos->findById(id);
                if(!result.success){
                    cout << result.error_message << "\n";
                    return;
                }
                const Movie& movie = result.data;
                cout << "Phim ban can tim la: \n";
                std::cout << "Movie ID: " << movie.getMovieId() << std::endl;
                std::cout << "Movie Title: " << movie.getMovieTitle() << std::endl;
                std::cout << "Movie Genre: " << movie.getMovieGenre() << std::endl;
                std::cout << "Movie Description: " << movie.getMovieDescription() << std::endl;
                std::cout << "Movie Duration: " << movie.getMovieDuration() << std::endl;
                std::cout << "Movie Rating: " << movie.getMovieRating() << std::endl;
                std::cout << "Movie Poster Path: " << movie.getMoviePosterPath() << std::endl;
                std::cout << "Movie Price: " << movie.getPrice() << std::endl;
                break;
            }
                case 2:{
                string input = "";
                std::cin.ignore();
                cout << "Nhap the loai \n";
                getline(std::cin, input);
                Result<std::vector<Movie>> result = movie_repos->findByGenre(input);
                if(!result.success){
                    cout << result.error_message << "\n";
                    return;
                }
                for(int i = 0; i < result.data.size(); i++){
                    std::cout << "Movie ID: " << result.data[i].getMovieId() << std::endl;
                    std::cout << "Movie Title: " << result.data[i].getMovieTitle() << std::endl;
                    std::cout << "Movie Genre: " << result.data[i].getMovieGenre() << std::endl;
                    std::cout << "Movie Description: " << result.data[i].getMovieDescription() << std::endl;
                    std::cout << "Movie Duration: " << result.data[i].getMovieDuration() << std::endl;
                    std::cout << "Movie Rating: " << result.data[i].getMovieRating() << std::endl;
                    std::cout << "Movie Poster Path: " << result.data[i].getMoviePosterPath() << std::endl;
                    std::cout << "Movie Price: " << result.data[i].getPrice() << std::endl;
                }
                break;  
            }
                case 3:{
                string input = "";
                std::cin.ignore();
                cout << "Nhap ten \n";
                getline(std::cin, input);
                Result<std::vector<Movie>> result = movie_repos->findByName(input);
                if(!result.success){
                    cout << result.error_message << "\n";
                    return;
                }
                for(int i = 0; i < result.data.size(); i++){
                    std::cout << "Movie ID: " << result.data[i].getMovieId() << std::endl;
                    std::cout << "Movie Title: " << result.data[i].getMovieTitle() << std::endl;
                    std::cout << "Movie Genre: " << result.data[i].getMovieGenre() << std::endl;
                    std::cout << "Movie Description: " << result.data[i].getMovieDescription() << std::endl;
                    std::cout << "Movie Duration: " << result.data[i].getMovieDuration() << std::endl;
                    std::cout << "Movie Rating: " << result.data[i].getMovieRating() << std::endl;
                    std::cout << "Movie Poster Path: " << result.data[i].getMoviePosterPath() << std::endl;
                    std::cout << "Movie Price: " << result.data[i].getPrice() << std::endl;
                }
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
        std::cin >> choice;
            switch (choice){
                case 1:{
                    Movie movie;
                    movie.setMovieId(0);
                    string input = "";
                    std::cin.ignore();
                    cout << "Nhap ten phim: \n";
                    getline(std::cin, input);
                    movie.setMovieTitle(input);
                    cout << "Nhap the loai: \n";
                    getline(std::cin, input);
                    movie.setMovieGenre(input);
                    cout << "Nhap mo ta: \n";
                    getline(std::cin, input);
                    movie.setMovieDescription(input);
                    cout << "Nhap thoi gian: \n";
                    int duration;
                    std::cin >> duration;
                    movie.setMovieDuration(duration);
                    cout << "Nhap xep hang: \n";
                    double rating;
                    std::cin >> rating;
                    movie.setMovieRating(rating);
                    string path = "";
                    std::cin.ignore();
                    cout << "Nhap duong dan hinh anh: \n";
                    getline(std::cin, path);
                    movie.setMoviePosterPath(path);
                    cout << "Nhap gia ve: \n";
                    int price;
                    std::cin >> price;
                    if(price <= 0){
                        cout << "Gia ve khong hop le! Nhap lai gia ve > 0\n";
                        std::cin >> price;
                    }
                    movie.setPrice(price);
                    Result<int> result = movie_repos->create(movie);
                    if(!result.success){
                        cout << result.error_message << "\n";
                        return;
                    }else{
                        cout << "Them phim thanh cong \n";
                    }
                    break;
                }
                case 2:{
                    cout << "Nhap id phim can xoa: \n";
                    int id;
                    std::cin >> id;
                    while(id < 1){
                        cout << "Id khong hop le! Nhap lai id > 1\n";
                        std::cin >> id;
                    }
                    Result<bool> result = movie_repos->remove(id);
                    if(!result.success){
                        cout << result.error_message << "\n";
                        return;
                    }else{
                        cout << "Xoa phim thanh cong \n";
                    }
                    break;
                }
                case 3:{
                    cout << "Nhap id phim can cap nhat: \n";
                    int id;
                    std::cin >> id;
                    while(id < 1){
                        cout << "Id khong hop le! Nhap lai id > 1\n";
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
                    cout << "Nhap ten phim: \n";
                    getline(std::cin, input);
                    if(input.empty()){
                        input = movie.getMovieTitle();
                    }
                    movie.setMovieTitle(input);
                    cout << "Nhap the loai: \n";
                    getline(std::cin, input);
                    if(input.empty()){
                        input = movie.getMovieGenre();
                    }
                    movie.setMovieGenre(input);
                    cout << "Nhap mo ta: \n";
                    getline(std::cin, input);
                    if (input.empty()){
                        input = movie.getMovieDescription();
                    }
                    movie.setMovieDescription(input);
                    cout << "Nhap thoi gian: \n";
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
                    cout << "Nhap duong dan hinh anh: \n";
                    getline(std::cin, path);
                    if(path.empty()){
                        path = movie.getMoviePosterPath();
                    }
                    movie.setMoviePosterPath(path);
                    cout << "Nhap gia ve: \n";
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
                        cout << "Cap nhat phim thanh cong \n";
                    }
                    break;
                }
                case 4:
                    getListMovie();
                    break;
                default:
                    cout << "Khong co chuc nang nay \n";
                    break;
            }
        }
};
#endif


