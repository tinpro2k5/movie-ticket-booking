
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

## 3. Cấu hình môi trường

### 3.1. Cấu hình SMTP (Gửi email)

Tạo file `.msmtprc` trong thư mục `~` với nội dung sau:

```
account default
host smtp.gmail.com
port 587
auth on
user your-email@gmail.com
password your-email-password
tls on
tls_starttls on
```

Đặt quyền bảo mật cho file:

```bash
chmod 600 /home/devuser/.msmtprc
```

## 4. Biên dịch chương trình

```bash
g++ src/models/*.cpp src/repositories/*.cpp src/services/*.cpp src/utils/*.cpp src/app/*.cpp src/main.cpp -o movie_ticket_booking -lmysqlclient
```

## 5. Cấu hình Docker (Tùy chọn)

```bash
docker build -t movie-ticket-booking -f .devcontainer/deploy/Dockerfile.deploy .
docker run -it -p 3306:3306 movie-ticket-booking
```

## 6. Ghi chú

* Đảm bảo MySQL đang chạy trước khi chạy ứng dụng.

```


