#!/bin/bash
set -e

# Chạy MySQL thực sự
echo "Starting MySQL server normally..."
exec sudo mysqld_safe
