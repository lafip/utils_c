cmake_minimum_required(VERSION 3.26)
project(utils_c LANGUAGES C)

# enable_testing()

add_executable(primelist primelist.c)

add_executable(invert2exp invert2exp.c)
target_link_libraries(invert2exp gmp)

add_executable(chinesremainder chinesremainder.c)
target_link_libraries(chinesremainder gmp)
# add_test(chinesremainder chinesremainder)
