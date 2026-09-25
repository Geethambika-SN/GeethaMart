cmake_minimum_required(VERSION 3.25)

project(GeethaMart)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(PostgreSQL_ROOT "C:/Program Files/PostgreSQL/18")

# PostgreSQL
include_directories(
    "C:/Program Files/PostgreSQL/18/include"
)

link_directories(
    "C:/Program Files/PostgreSQL/18/lib"
)

# vcpkg libraries
include_directories(
    "${CMAKE_SOURCE_DIR}/../vcpkg_installed/x64-windows/include"
)

link_directories(
    "${CMAKE_SOURCE_DIR}/../vcpkg_installed/x64-windows/lib"
)

add_executable(GeethaMart

    src/main.cpp

    # Utilities
    src/util/DatabaseConnection.cpp
    src/util/PasswordUtils.cpp

    # Models
    src/model/Product.h
    src/model/User.h
    src/model/CartItem.h
    src/model/Order.h
    src/model/OrderItem.h
    src/model/Review.h

    # Product
    src/repository/ProductRepository.cpp
    src/service/ProductService.cpp
    src/controller/ProductController.cpp

    # User
    src/repository/UserRepository.cpp
    src/service/UserService.cpp
    src/controller/UserController.cpp

    # Cart
    src/repository/CartRepository.cpp
    src/service/CartService.cpp
    src/controller/CartController.cpp

    # Order
    src/repository/OrderRepository.cpp
    src/service/OrderService.cpp
    src/controller/OrderController.cpp

    # Review
    src/repository/ReviewRepository.cpp
    src/service/ReviewService.cpp
    src/controller/ReviewController.cpp
)

target_link_libraries(
    GeethaMart
    libpq
    libsodium
)