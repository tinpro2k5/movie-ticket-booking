#!/bin/bash

set -e  # Dừng nếu có lỗi

echo "🔧 Updating package list and installing required packages..."
sudo apt-get update
sudo DEBIAN_FRONTEND=noninteractive apt-get install -y \
    build-essential \
    git \
    curl \
    vim \
    sudo \
    npm \
    mysql-server \
    libmysqlclient-dev

echo "🧹 Cleaning up apt cache..."
sudo apt-get clean
sudo rm -rf /var/lib/apt/lists/*

# Optional: Add a user if needed (in Codespaces, user is usually 'codespace')
# echo "👤 Creating non-root user 'devuser'..."
# sudo useradd -m devuser
# echo "devuser ALL=(ALL) NOPASSWD:ALL" | sudo tee -a /etc/sudoers

echo "🛠️ Configuring MySQL..."
sudo mkdir -p /etc
cat <<EOF | sudo tee /etc/my.cnf
[client]
port=3306
socket=/var/run/mysqld/mysqld.sock

[mysqld]
user=mysql
port=3306
datadir=/var/lib/mysql
socket=/var/run/mysqld/mysqld.sock
EOF

echo "📁 Fixing MySQL socket directory permissions..."
sudo mkdir -p /var/run/mysqld
sudo chmod 755 /var/run/mysqld
sudo chown mysql:mysql /var/run/mysqld

echo "🚀 Starting MySQL service..."
sudo service mysql restart

echo "✅ MySQL Dev Environment setup complete!"
