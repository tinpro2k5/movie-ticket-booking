
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
g++ src/models/*.cpp src/repositories/*.cpp src/services/*.cpp src/utils/*.cpp src/app/*.cpp src/main.cpp -o release/movie_ticket_booking `wx-config --cxxflags --libs` -lmysqlclient
```

hoặc lệnh này nếu bị lỗi:
```bash
g++ $(wx-config --cxxflags) src/models/*.cpp src/repositories/*.cpp src/services/*.cpp src/utils/*.cpp src/app/*.cpp src/main.cpp -o release/movie_ticket_booking $(wx-config --libs) -lmysqlclient
```

## 5. Cấu hình Docker (Tùy chọn)

```bash
docker build -t movie-ticket-booking -f .devcontainer/deploy/Dockerfile.deploy .
docker run -it -p 3306:3306 movie-ticket-booking
```

## 6. Ghi chú

* Đảm bảo MySQL đang chạy trước khi chạy ứng dụng.

```
Để chạy được UI ở máy local thì cần cài đặt và cấu hình XLaunch (VcXsrv) để hiển thị giao diện:

1. Tải và cài đặt VcXsrv (XLaunch) từ: https://sourceforge.net/projects/vcxsrv/

2. Khởi động XLaunch và cấu hình như sau:
   - Chọn "Multiple windows" ở màn hình đầu tiên
   - Ở màn hình "Display settings", chọn "Start no client"
   - Ở màn hình "Extra settings":
     + Chọn "Clipboard"
     + Chọn "Primary Selection"
     + Chọn "Native opengl"
     + Bỏ chọn "Disable access control"
   - Nhấn "Finish" để lưu cấu hình và khởi động XLaunch

3. Thêm biến môi trường DISPLAY trong terminal Linux:
```bash
export DISPLAY=$(cat /etc/resolv.conf | grep nameserver | awk '{print $2}'):0
```

4. Kiểm tra kết nối X11:
```bash
xeyes  # Nếu hiện cửa sổ con mắt là đã thành công
```

5. Sau đó có thể chạy ứng dụng UI:
```bash
./release/movie_ticket_booking_ui
```

Lưu ý:
- Cần khởi động lại XLaunch mỗi khi khởi động lại máy tính
- Nếu gặp lỗi kết nối, hãy kiểm tra:
  + XLaunch đang chạy
  + Biến DISPLAY đã được set đúng
  + Firewall Windows cho phép kết nối VcXsrv


