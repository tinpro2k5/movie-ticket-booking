
# Hướng Dẫn Cài Đặt Movie Ticket Booking

## 1. Yêu cầu hệ thống

- Hệ điều hành: Linux (Ubuntu 22.04 hoặc tương đương)  
- Compiler: GCC hỗ trợ chuẩn C++17  
- CMake: Phiên bản 3.10 trở lên  
- MySQL Server: Đã cài đặt và chạy  
- Thư viện: libmysqlclient-dev để kết nối MySQL  
- Công cụ khác: build-essential, msmtp, msmtp-mta  

## 2. Cài đặt các dependencies

### 2.1. Cài đặt các gói cần thiết

```bash
sudo apt-get update && \
sudo apt-get install -y build-essential curl vim sudo cmake mysql-server libmysqlclient-dev msmtp msmtp-mta
````

### 2.2. Cấu hình MySQL

```bash
sudo service mysql start
sudo mysql -e "ALTER USER 'root'@'localhost' IDENTIFIED WITH mysql_native_password BY 'rootpassword'; FLUSH PRIVILEGES;"
```
### 2.3 Cài đặt wxWidgets 
```bash
sudo apt update
sudo apt install libwxgtk3.0-gtk3-dev
```

### 2.4 Cài đặt libharu 
```bash
sudo apt update
sudo apt install libhpdf-dev
```

## 3. Cấu hình môi trường

### 3.1. Cấu hình SMTP (Gửi email)

Tạo file `.msmtprc` trong thư mục `~` với nội dung sau:

```
account gmail
host smtp.gmail.com
port 587
auth on
tls on
tls_trust_file /etc/ssl/certs/ca-certificates.crt
user tinpro12052005@gmail.com
password hnosdncjeqdczunc
from tinpro12052005@gmail.com
account default : gmail
```

Đặt quyền bảo mật cho file:

```bash
chmod 600 ~/.msmtprc
```

## 4. Biên dịch chương trình

```bash
g++ src/models/*.cpp src/repositories/*.cpp src/services/*.cpp src/utils/*.cpp src/app/*.cpp src/main.cpp -o release/movie_ticket_booking `wx-config --cxxflags --libs` -lhpdf -lmysqlclient
```

hoặc lệnh này nếu bị lỗi:
```bash
g++ $(wx-config --cxxflags) src/models/*.cpp src/repositories/*.cpp src/services/*.cpp src/utils/*.cpp src/app/*.cpp src/main.cpp -o release/movie_ticket_booking $(wx-config --libs) -lhpdf -lmysqlclient
```

## 5. Cấu hình Docker (Tùy chọn)

```bash
docker build -t movie-ticket-booking -f .devcontainer/deploy/Dockerfile.deploy .
docker run -it -p 3306:3306 movie-ticket-booking
```

## 6. Ghi chú

* Đảm bảo MySQL đang chạy trước khi chạy ứng dụng.

```


