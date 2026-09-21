cmake_minimum_required(VERSION 3.25)

project(GeethaMart)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# PostgreSQL
set(PostgreSQL_ROOT "C:/Program Files/PostgreSQL/18")

include_directories("${PostgreSQL_ROOT}/include")
link_directories("${PostgreSQL_ROOT}/lib")

# Backend executable
add_executable(GeethaMart
    src/main.cpp
    src/repository/ProductRepository.cpp
    src/service/ProductService.cpp
    src/controller/ProductController.cpp
    src/util/DatabaseConnection.cpp
)

# Link PostgreSQL library
target_link_libraries(GeethaMart
    libpq
)