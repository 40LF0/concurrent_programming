if(EXISTS "/home/seungyeon/CONCURRENT_PROGRAMING/2022_ite4065_2019082851/lab04/db_project/build/test/db_test[1]_tests.cmake")
  include("/home/seungyeon/CONCURRENT_PROGRAMING/2022_ite4065_2019082851/lab04/db_project/build/test/db_test[1]_tests.cmake")
else()
  add_test(db_test_NOT_BUILT db_test_NOT_BUILT)
endif()
