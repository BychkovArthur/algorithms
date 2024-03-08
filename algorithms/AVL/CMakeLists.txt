cmake_minimum_required(VERSION 3.10)
project(AVL)

# Задание стандарта C++
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Установка флагов для компиляции
add_compile_options(-g -rdynamic)

# Настройка переменных для папок
set(INCLUDE_DIR include)
set(SOURCE_DIR src)
set(TEST_DIR test)

# Подключение директории с заголовочными файлами
include_directories(${INCLUDE_DIR})

# Переменные с исходными файлами
file(GLOB_RECURSE SOURCES LIST_DIRECTORIES false ${SOURCE_DIR}/*.cpp)
file(GLOB_RECURSE TEST_SOURCES LIST_DIRECTORIES false ${TEST_DIR}/*.cpp)

# Добавляем CMakeLists.txt для gtest, чтобы собрать библиотеку gtest
add_subdirectory(libs/googletest)

# Делаем библиотеку из наших исходников
add_library(${CMAKE_PROJECT_NAME}_lib ${SOURCES})


#---------------main.cpp------------------

# Делаем исполняемый файл, в котором просто будем спрашивать пользователя входные данные
add_executable(${CMAKE_PROJECT_NAME}_exe main.cpp)
# "Привязываем" (линкуем) бинарник main.cpp с библиотекой, в которой расположена функция
target_link_libraries(${CMAKE_PROJECT_NAME}_exe PRIVATE ${CMAKE_PROJECT_NAME}_lib)


#---------------tests--------------------

# Добавляем бинарный файл с тестами
add_executable(${CMAKE_PROJECT_NAME}_test ${TEST_SOURCES})
# Линкуем к тестам библиотеку с функциями, а так же, сам gtest. 3 строки ниже делают одно и то же!
target_link_libraries(${CMAKE_PROJECT_NAME}_test PRIVATE ${CMAKE_PROJECT_NAME}_lib GTest::gtest_main)
# target_link_libraries(${CMAKE_PROJECT_NAME}_test PRIVATE ${CMAKE_PROJECT_NAME}_lib gtest gtest_main)
# target_link_libraries(${CMAKE_PROJECT_NAME}_test PRIVATE ${CMAKE_PROJECT_NAME}_lib gtest_main)

# Подключение к тестам заголовочных фалов. Но зачем, если я подключаю саму библиотеку с тестами (работает и без этой строки)?
target_include_directories(${CMAKE_PROJECT_NAME}_test PRIVATE ${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})