add_executable(pretty_tests
    "main.cpp"
)

target_include_directories(pretty_tests PRIVATE
    ../Impl
)

target_link_libraries(pretty_tests PRIVATE
    pretty
)