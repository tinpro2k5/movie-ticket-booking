cmake_minimum_required(VERSION 3.10)
project(MovieTicketBooking)

set(CMAKE_CXX_STANDARD 17)

# Include directories
include_directories(include)

# Source files
file(GLOB_RECURSE SRC_FILES
    src/models/*.cpp
    src/repositories/*.cpp
    src/services/*.cpp
    src/utils/*.cpp
    src/app/*.cpp
)

# Main executable
add_executable(movie_ticket_booking ${SRC_FILES} src/main.cpp)
target_link_libraries(movie_ticket_booking mysqlclient)

# Test files
file(GLOB TEST_SRC_FILES
    test/user_service/test_user_service.cpp
)

add_executable(test_user_service ${TEST_SRC_FILES} ${SRC_FILES})
target_link_libraries(test_user_service mysqlclient)


# cách dùng để build
# rm -rf *
# cmake ..
# make
