cmake_minimum_required(VERSION 3.17)
project(gsl)
# set(SRC "test/test_matrix.cpp" "test/main.cpp" "test/test_vector.cpp" "test/test_matrix_view.cpp" "test/test_opr.cpp" "test/test_vector_view.cpp") 
# set(SRC "test/test_vector.cpp" "test/test_opr.cpp" "test/test_matrix_view.cpp")
 # set(SRC "regression/regor.cpp")
# set(SRC  "test.cpp")
set(SRC "classification/logistic_reg.cpp")
find_package(GSL REQUIRED)
find_package(Threads REQUIRED)
find_package(Python3 COMPONENTS Development NumPy)
add_executable(gsl ${SRC})
target_compile_features(gsl PUBLIC cxx_std_20)
target_compile_options(gsl PRIVATE -ggdb -Wall -pedantic -Wextra)
target_include_directories(gsl PUBLIC $<BUILD_INTERFACE:${GSL_INCLUDE_DIR} 
                                ${CMAKE_SOURCE_DIR}/src 
                                ${CMAKE_SOURCE_DIR}/Catch2/single_include/ 
                                ${CMAKE_SOURCE_DIR}/rapidcsv/src/ 
                                PRIVATE ${Python3_INCLUDE_DIRS} ${Python3_NumPy_INCLUDE_DIRS})
  target_link_libraries(gsl PUBLIC GSL::gsl Python3::Python Python3::NumPy)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
