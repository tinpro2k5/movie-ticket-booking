#include <cassert>
#include <string>
#include "../../include/repositories/MovieRepository.h"  // Include header file
/*
Dong lenh sau de compile
g++ src/models/Movie.cpp src/repositories/MovieRepository.cpp src/utils/DatabaseManager.cpp test/user_repos/test_movie_repos.cpp -o test/user_repos/test_movie -lmysqlclient 
*/
// Giả lập đối tượng DatabaseManager
void testFindAll() {
    // Tạo MovieRepository
    MovieRepository movieRepo;

    // Giả lập tìm phim theo movieId
    Result<std::vector<Movie>> result = movieRepo.findAll();
    
    // Kiểm tra kết quả trả về
    assert(result.success == true);  // Kết quả thành công
    assert(result.data.size() > 0);  // Có ít nhất 1 movie được trả về
    assert(result.data[0].getMovieId() == 1);  // Kiểm tra movieId của movie trả về
    std::cout << "testFindMovieById passed!" << std::endl;

    for(int i = 0; i < result.data.size(); i++){
        std::cout << "Movie ID: " << result.data[i].getMovieId() << std::endl;
        std::cout << "Movie Title: " << result.data[i].getMovieTitle() << std::endl;
        std::cout << "Movie Genre: " << result.data[i].getMovieGenre() << std::endl;
        std::cout << "Movie Description: " << result.data[i].getMovieDescription() << std::endl;
        std::cout << "Movie Duration: " << result.data[i].getMovieDuration() << std::endl;
        std::cout << "Movie Rating: " << result.data[i].getMovieRating() << std::endl;
        std::cout << "Movie Poster Path: " << result.data[i].getMoviePosterPath() << std::endl;
    }
}
void testFindById(){
    // Tạo MovieRepository
    MovieRepository movieRepo;

    // Giả lập tìm phim theo movieId
    Result<Movie> result = movieRepo.findById(1);
    
    // Kiểm tra kết quả trả về
    assert(result.success == true);  // Kết quả thành công
    assert(result.data.getMovieId() == 1);  // Kiểm tra movieId của movie trả về
    std::cout << "testFindMovieById passed!" << std::endl;

    std::cout << "Movie ID: " << result.data.getMovieId() << std::endl;
    std::cout << "Movie Title: " << result.data.getMovieTitle() << std::endl;
    std::cout << "Movie Genre: " << result.data.getMovieGenre() << std::endl;
    std::cout << "Movie Description: " << result.data.getMovieDescription() << std::endl;
    std::cout << "Movie Duration: " << result.data.getMovieDuration() << std::endl;
    std::cout << "Movie Rating: " << result.data.getMovieRating() << std::endl;
    std::cout << "Movie Poster Path: " << result.data.getMoviePosterPath() << std::endl;
}
void testAdd(){
    // Tạo MovieRepository
    MovieRepository movieRepo;

    // Tạo movie mới
    Movie movie(3, "New Movie", "Action", "Description of new movie", 120, 8.5, "poster.jpg");

    // Giả lập thêm phim
    Result<bool> result = movieRepo.add(movie);
    
    // Kiểm tra kết quả trả về
    assert(result.success == true);  // Kết quả thành công
    std::cout << "testAdd passed!" << std::endl;
}
void testUpdate(){
    // Tạo MovieRepository
    MovieRepository movieRepo;

    // Tạo movie mới
    Movie movie(1, "Updated Title", "Updated Genre", "Updated Description", 120, 8.5, "updated_poster.jpg");

    // Giả lập cập nhật phim
    Result<bool> result = movieRepo.update(movie);
    
    // Kiểm tra kết quả trả về
    if (result.success) {
        std::cout << "testUpdate passed!" << std::endl;
    } else {
        std::cerr << "testUpdate failed! Reason: " << result.error_message << std::endl;
    }
    std::cout << "testUpdate passed!" << std::endl;
}
int main() {
    // Chạy các unit test
    DatabaseManager::getInstance()->connect(ServerInfo("127.0.0.1", "root", "rootpassword", 3306));
    DatabaseManager::getInstance()->setupDatabase();
    testFindAll();
    cout << "-------------------------" << endl;
    testAdd();
    cout << "-------------------------" << endl;
    testUpdate();
    cout << "-------------------------" << endl;
    testFindAll();
    cout << "-------------------------" << endl;
    std::cout << "All tests passed!" << std::endl;

    return 0;
}
