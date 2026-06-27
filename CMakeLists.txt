cmake_minimum_required(VERSION 3.14)
project(Lab3 LANGUAGES CXX)

# Включаем вывод всех предупреждений компилятора, чтобы сразу видеть ошибки
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

# Включаем поддержку стандарта C++ 17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Указываем компилятору искать файлы в корне проекта, а также в папках src и sequence
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/sequence
)

# Создаем основной исполняемый файл проекта
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp")
    add_executable(main_app main.cpp)
endif()

# Создаем исполняемый файл для тестов (если файл test.cpp существует)
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/test.cpp")
    add_executable(test_app test.cpp)
endif()