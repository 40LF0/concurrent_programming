#include "bwtree.h"
#include "bwtree_test_util.h"
#include "multithread_test_util.h"
#include "worker_pool.h"

#include <gtest/gtest.h>

#include <algorithm>
#include <random>
#include <vector>
#include <string>
#include <cmath>


class BwtreeTest_density_with_exist_db : public ::testing::Test {
  protected:
    /*
     * NOTE: You can also use constructor/destructor instead of SetUp() and
     * TearDown(). The official document says that the former is actually
     * perferred due to some reasons. Checkout the document for the difference.
     */
    BwtreeTest_density_with_exist_db() {
    }

    ~BwtreeTest_density_with_exist_db() {
    }
    
    const uint32_t num_threads_ =
      test::MultiThreadTestUtil::HardwareConcurrency() + (test::MultiThreadTestUtil::HardwareConcurrency() % 2);

    void template_test(int k){
      const uint32_t key_num = 1024 * 1024;
      std::atomic<size_t> insert_success_counter = 0;

      common::WorkerPool thread_pool(num_threads_, {});
      thread_pool.Startup();
      

      // Inserts in a 1M key space randomly until all keys has been inserted
      auto workload = [&](uint32_t id) {
        const uint32_t gcid = id + 1;
        tree->AssignGCID(gcid);
        std::default_random_engine thread_generator(id);
        std::uniform_int_distribution<int> uniform_dist(0, key_num - 1);

        while (insert_success_counter.load() < key_num) {
          int key = uniform_dist(thread_generator);

          if (tree->Insert(key, key)) insert_success_counter.fetch_add(1);
        }
        tree->UnregisterThread(gcid);
      };

      tree->UpdateThreadLocal(num_threads_ + 1);
      test::MultiThreadTestUtil::RunThreadsUntilFinish(&thread_pool, num_threads_, workload);
      tree->UpdateThreadLocal(1);

      // Verifies whether random insert is correct
      for (uint32_t i = 0; i < key_num; i++) {
        auto s = tree->GetValue(i);

        EXPECT_EQ(s.size(), 1);
        EXPECT_EQ(*s.begin(), i);
      }
      
      auto workload1 = [&](uint32_t id) {
        const uint32_t gcid = id + 1;
        tree->AssignGCID(gcid);
        std::default_random_engine thread_generator(id);
        std::uniform_int_distribution<int> uniform_dist(0, static_cast<int>(pow(2,k)) -1);


        for (uint32_t i = 0; i < key_num/2; i++) {
            int key = uniform_dist(thread_generator);  // NOLINT
            tree->Delete(key, key);
            tree->Insert(key, key);
        }
        tree->UnregisterThread(gcid);
       };

       tree->UpdateThreadLocal(num_threads_ + 1);
       test::MultiThreadTestUtil::RunThreadsUntilFinish(&thread_pool, num_threads_, workload1);
       tree->UpdateThreadLocal(1);

       delete tree;

    }
    test::BwTreeTestUtil::TreeType *const tree = test::BwTreeTestUtil::GetEmptyTree();

};



TEST_F(BwtreeTest_density_with_exist_db, pow_2_1) {
    template_test(1);
}
TEST_F(BwtreeTest_density_with_exist_db, pow_2_2) {
    template_test(2);
}
TEST_F(BwtreeTest_density_with_exist_db, pow_2_3) {
    template_test(3);
}
TEST_F(BwtreeTest_density_with_exist_db, pow_2_4) {
    template_test(4);
}
TEST_F(BwtreeTest_density_with_exist_db, pow_2_5) {
    template_test(5);
}
TEST_F(BwtreeTest_density_with_exist_db, pow_2_6) {
    template_test(6);
}
TEST_F(BwtreeTest_density_with_exist_db, pow_2_7) {
    template_test(7);
}
TEST_F(BwtreeTest_density_with_exist_db, pow_2_8) {
    template_test(8);
}
TEST_F(BwtreeTest_density_with_exist_db, pow_2_9) {
    template_test(9);
}
TEST_F(BwtreeTest_density_with_exist_db, pow_2_10) {
    template_test(10);
}
TEST_F(BwtreeTest_density_with_exist_db, pow_2_11) {
    template_test(11);
}
TEST_F(BwtreeTest_density_with_exist_db, pow_2_12) {
    template_test(12);
}
TEST_F(BwtreeTest_density_with_exist_db, pow_2_13) {
    template_test(13);
}
TEST_F(BwtreeTest_density_with_exist_db, pow_2_14) {
    template_test(14);
}
TEST_F(BwtreeTest_density_with_exist_db, pow_2_15) {
    template_test(15);
}
TEST_F(BwtreeTest_density_with_exist_db, pow_2_16) {
    template_test(16);
}
TEST_F(BwtreeTest_density_with_exist_db, pow_2_17) {
    template_test(17);
}
TEST_F(BwtreeTest_density_with_exist_db, pow_2_18) {
    template_test(18);
}
TEST_F(BwtreeTest_density_with_exist_db, pow_2_19) {
    template_test(19);
}
TEST_F(BwtreeTest_density_with_exist_db, pow_2_20) {
    template_test(20);
}
