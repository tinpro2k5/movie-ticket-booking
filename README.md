# movie-ticket-booking

# ĐỒ ÁN OOP: HỆ THỐNG ĐẶT VÉ XEM PHIM 
- Dự án gốc: https://www.codewithc.com/movie-ticket-booking-system-in-c-with-mysql

# Tính năng

- **Quản lý phim, khách hàng, phòng chiếu, đặt vé, ghế ngồi**
- **Đăng nhập/Đăng ký người dùng**: Lưu thông tin user, xác thực OTP
- **Tìm kiếm phim**: Theo tên, thể loại, ngày chiếu
- **Đặt vé**: 
  - Chọn phim → rạp → suất chiếu → ghế
- **Kiểm tra chỗ ngồi**
- **In vé**: Dưới dạng file PDF
- **Quản lý lịch chiếu**: Cho từng phim / phòng / rạp
- **CRUD và hiển thị danh sách phim**
- **Giao diện người dùng**: Console (có thể mở rộng lên GUI sau)

# Thông tin kỹ thuật

- **Language**: C++
- **Database**: MySQL (localhost)
- **Môi trường**: GitHub Codespaces
- **Kiến trúc phần mềm**: Mô hình 3 lớp (3-Layer Architecture)

## 1. UI Layer (Giao diện người dùng)
- **Trách nhiệm**: Giao tiếp với người dùng qua console (có thể mở rộng lên GUI sau)
- **Chức năng**: 
  - Xử lý menu chính
  - Lựa chọn người dùng
  - Nhập đầu vào

## 2. Business Logic Layer (Lớp xử lý nghiệp vụ)
- **Trách nhiệm**: Xử lý các chức năng chính
- **Chức năng**: 
  - Đặt vé, kiểm tra ghế
  - Kiểm tra dữ liệu đầu vào, tính toán

## 3. Data Access Layer (Lớp truy cập dữ liệu)
- **Trách nhiệm**: Giao tiếp trực tiếp với MySQL
- **Chức năng**: 
  - Truy vấn dữ liệu từ các bảng

# Design Pattern

- **Singleton**: Quản lý kết nối MySQL (DatabaseManager) để đảm bảo chỉ tạo 1 kết nối duy nhất
- **Repository**: Tách riêng truy vấn dữ liệu ra khỏi lớp xử lý nghiệp vụ
- **MVC (đơn giản)**: 
  - UI (main)
  - Controller (service)
  - Model (dữ liệu: phim, vé)
- **Builder**: Tạo các truy vấn SQL
- **Factory (optional)**: Có thể dùng nếu tạo các đối tượng phim, vé có đặc điểm khác nhau (ví dụ: vé thường, vé VIP)
- **Observer**: Khi vé được đặt → gửi thông báo (email), cập nhật trạng thái ghế
- **Strategy**: Chọn thuật toán tính giá vé khác nhau theo ngày/giờ/loại ghế

# Dependency Injection
- **Mục tiêu**: Tách riêng phần phụ thuộc giữa các lớp để dễ test và mở rộng

# Deployment
- **Hướng dẫn**: 
  - File hướng dẫn cài đặt Database, cấu hình, compile và chạy chương trình (Linux)
- **GitHub Codespaces**: 
  - Tạo codespace trên Repository chứa cấu hình sẵn môi trường bằng `.devcontainer`
- **Docker (optional)**: 
  - Có thể container hóa MySQL và chương trình chính nếu cần

# CÁCH ĐẢM BẢO CHẤT LƯỢNG
  
## Unit Testing (Kiểm thử đơn vị)
- Sử dụng Google Test để viết unit test cho các module xử lý logic quan trọng:

- Đặt vé, kiểm tra ghế trống

- Tính giá vé (kết hợp với Strategy Pattern)

-  Tìm kiếm phim, xác thực thông tin người dùng

##  Kiểm thử các luồng nghiệp vụ chính:

- Người dùng đăng ký → đăng nhập → đặt vé → in vé

- Admin tạo phim → thêm suất chiếu → kiểm tra lịch chiếu

## Cài đặt hệ thống ghi log lỗi (log ra file):

- Lỗi kết nối CSDL, Lỗi nhập sai dữ liệu, Exception không mong muốn
- Ghi chi tiết thời gian, loại lỗi, mô-đun gây lỗi để dễ truy vết.
