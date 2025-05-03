#ifndef MOVIESERVICE_H
#define MOVIESERVICE_H

#include "../../include/repositories/MovieRepository.h"

class MovieService{
    MovieRepository movie_repos;
    public:
    void getListMovie(){
        Result<vector<Movie>> result = movie_repos.findAll();
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
                Result<Movie> result = movie_repos.findById(id);
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
                break;
            }
                case 2:{
                string input = "";
                std::cin.ignore();
                cout << "Nhap the loai \n";
                getline(std::cin, input);
                Result<std::vector<Movie>> result = movie_repos.findByGenre(input);
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
                }
                break;  
            }
                case 3:{
                string input = "";
                std::cin.ignore();
                cout << "Nhap ten \n";
                getline(std::cin, input);
                Result<std::vector<Movie>> result = movie_repos.findByName(input);
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
                }
                break;
            }
                default:{
                    return;
                break;
            }
            }
        }
};
#endif


