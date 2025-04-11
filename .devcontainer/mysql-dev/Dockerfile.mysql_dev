FROM ubuntu:22.04

# Cập nhật và cài đặt các gói cơ bản
RUN apt-get update && \
    DEBIAN_FRONTEND=noninteractive apt-get install -y \
    build-essential \
    git \
    curl \
    vim \
    sudo \
    npm \
    mysql-server \
    libmysqlclient-dev && \
    apt-get clean && rm -rf /var/lib/apt/lists/*

# Tạo user để không chạy bằng root
RUN useradd -m devuser && echo "devuser ALL=(ALL) NOPASSWD:ALL" >> /etc/sudoers


USER devuser
WORKDIR /home/devuser


# Cấu hình MySQL
USER root
RUN echo "[client]\\nport=3306\\nsocket=/var/run/mysqld/mysqld.sock\\n\\n[mysqld]\\nuser=mysql\\nport=3306\\ndatadir=/var/lib/mysql\\nsocket=/var/run/mysqld/mysqld.sock" > /etc/my.cnf



# Sửa quyền thư mục socket
RUN mkdir -p /var/run/mysqld && \
chmod 755 /var/run/mysqld && \
chown mysql:mysql /var/run/mysqld

USER devuser
# Expose cổng mysql
EXPOSE 3306

# Khởi động MySQL khi container start
CMD ["bash", "-c", "service mysql start && bash"]
