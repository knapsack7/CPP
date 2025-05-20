cmake_minimum_required(VERSION 3.10)
project(TradingSystemTests)

find_package(GTest REQUIRED)
find_package(Protobuf 5.29.3 REQUIRED)
find_package(Boost REQUIRED COMPONENTS system thread)
find_package(absl REQUIRED)

include_directories(${CMAKE_SOURCE_DIR}/include ${CMAKE_SOURCE_DIR}/src ${CMAKE_SOURCE_DIR}/proto)

add_executable(connection_test ConnectionTest.cpp)
target_link_libraries(connection_test 
    trading_system_lib 
    protobuf::libprotobuf
    GTest::GTest 
    GTest::Main 
    ${Boost_LIBRARIES}
    absl::base 
    absl::synchronization 
    absl::strings 
    absl::status 
    absl::statusor 
    absl::log 
    absl::log_internal_check_op 
    absl::log_internal_conditions 
    absl::log_internal_format 
    absl::log_internal_globals 
    absl::log_internal_log_sink_set 
    absl::log_internal_message 
    absl::log_internal_nullguard 
    absl::log_internal_proto 
    absl::log_severity 
    absl::log_sink 
    pthread
)

add_executable(trading_cases_test TradingCasesTest.cpp)
target_link_libraries(trading_cases_test 
    trading_system_lib 
    protobuf::libprotobuf
    GTest::GTest 
    GTest::Main 
    ${Boost_LIBRARIES}
    absl::base 
    absl::synchronization 
    absl::strings 
    absl::status 
    absl::statusor 
    absl::log 
    absl::log_internal_check_op 
    absl::log_internal_conditions 
    absl::log_internal_format 
    absl::log_internal_globals 
    absl::log_internal_log_sink_set 
    absl::log_internal_message 
    absl::log_internal_nullguard 
    absl::log_internal_proto 
    absl::log_severity 
    absl::log_sink 
    pthread
)

add_test(NAME ConnectionTest COMMAND connection_test)
add_test(NAME TradingCasesTest COMMAND trading_cases_test)

enable_testing() 