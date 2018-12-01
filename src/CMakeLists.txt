file(GLOB md5_src "*.h" "*.cpp")

add_executable(md5 ${md5_src})

# Libraries to be linked
target_link_libraries(md5 ${OPENSSL_LIBRARIES})