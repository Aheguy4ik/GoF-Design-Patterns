cmake_minimum_required(VERSION 3.10)
project(AdapterPattern)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)  # Включаем заголовки из include

# Компилируем реальные cpp файлы в библиотеки
add_library(monster STATIC src/Monster.cpp)
add_library(pet STATIC src/Pet.cpp)
add_library(pet_adapter_dynamic STATIC src/PetAdapterDynamic.cpp)

# Собираем основной исполняемый файл
add_executable(adapter src/main.cpp)
target_link_libraries(adapter monster pet pet_adapter_dynamic)

# Настройка GoogleTest
enable_testing()

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Тесты
add_executable(tests Structural/Adapter/tests/test_adapters.cpp)
target_link_libraries(tests monster pet pet_adapter_dynamic ${GTEST_LIBRARIES} pthread)

add_test(NAME AdapterTest COMMAND tests)
