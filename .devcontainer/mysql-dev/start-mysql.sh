#!/bin/bash
set -e

# Sửa config để MySQL dễ chạy trong Codespace
sed -i 's/^bind-address/#bind-address/' /etc/mysql/mysql.conf.d/mysqld.cnf

# Khởi động MySQL
echo "Starting MySQL..."
service mysql start

# Đặt lại password cho root nếu lần đầu
if [ ! -f /var/lib/mysql/.mysql_password_set ]; then
  echo "Setting root password..."
  mysql -u root <<-EOSQL
    ALTER USER 'root'@'localhost' IDENTIFIED WITH mysql_native_password BY 'rootpassword';
    FLUSH PRIVILEGES;
EOSQL
  touch /var/lib/mysql/.mysql_password_set
fi

# Giữ container sống
echo "MySQL is running. Container is alive..."
tail -f /dev/null
