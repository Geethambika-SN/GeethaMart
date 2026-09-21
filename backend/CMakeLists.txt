cmake_minimum_required(VERSION 3.25)

project(GeethaMart)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# PostgreSQL
set(PostgreSQL_ROOT "C:/Program Files/PostgreSQL/18")

include_directories("${PostgreSQL_ROOT}/include")
link_directories("${PostgreSQL_ROOT}/lib")

# GeethaMart vcpkg dependencies
set(VCPKG_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/../vcpkg_installed/x64-windows")

include_directories("${VCPKG_ROOT}/include")
link_directories("${VCPKG_ROOT}/lib")

# Backend executable
add_executable(GeethaMart
    src/main.cpp

    # Repository layer
    src/repository/ProductRepository.cpp
    src/repository/UserRepository.cpp

    # Service layer
    src/service/ProductService.cpp
    src/service/UserService.cpp

    # Controller layer
    src/controller/ProductController.cpp
    src/controller/UserController.cpp

    # Utility layer
    src/util/DatabaseConnection.cpp
    src/util/PasswordUtils.cpp
)

# Link libraries
target_link_libraries(GeethaMart
    libpq
    libsodium
)