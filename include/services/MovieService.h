#ifndef MOVIESERVICE_H
#define MOVIESERVICE_H

#include "repositories/MovieRepositories.h"

class MovieService {
private:
    MovieRepositories movie_repos;  // Đối tượng MovieRepositories để làm việc với cơ sở dữ liệu
public:
    // Phương thức khởi tạo, huy
    MovieService();
    ~MovieService();    
    // Phương thức quản lý phim
    void manageMovieMenu(); 

    // Các phương thức khác nếu cần, ví dụ như thêm phim, sửa phim, xóa phim, v.v.
    void addMovie();
    void editMovie();
    void deleteMovie();
    void listMovies();
};

#endif // MOVIESERVICE_H

