/******************************************************************************
 * Copyright 2017 The Apollo Authors. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *****************************************************************************/

#include <string>

#include "gtest/gtest.h"

#include "modules/common/configs/config_gflags.h"
#include "modules/planning/common/planning_gflags.h"
#include "modules/planning/integration_tests/planning_test_base.h"
#include "modules/planning/planning.h"

namespace apollo {
namespace planning {

/**
 * @class SunnyvaleLoopTest
 * @brief This is an integration test that uses the sunnyvale_loop map.
 */

class SunnyvaleLoopTest : public PlanningTestBase {
 public:
  virtual void SetUp() {
    FLAGS_map_dir = "modules/map/data/sunnyvale_loop";
    FLAGS_test_data_dir = "modules/planning/testdata/sunnyvale_loop_test";
    FLAGS_test_routing_response_file = "1_routing.pb.txt";
  }
};

/*
 * test stop for not-nudgable obstacle
 * A cruise test case
 */
TEST_F(SunnyvaleLoopTest, cruise) {
  std::string seq_num = "1";
  FLAGS_test_prediction_file = seq_num + "_prediction.pb.txt";
  FLAGS_test_localization_file = seq_num + "_localization.pb.txt";
  FLAGS_test_chassis_file = seq_num + "_chassis.pb.txt";
  PlanningTestBase::SetUp();
  RUN_GOLDEN_TEST;
}

/*
 * stop case to trigger QP ST failed to solve
 */
TEST_F(SunnyvaleLoopTest, stop) {
  // TODO: fix this test.
  std::string seq_num = "2";
  FLAGS_test_prediction_file = seq_num + "_prediction.pb.txt";
  FLAGS_test_localization_file = seq_num + "_localization.pb.txt";
  FLAGS_test_chassis_file = seq_num + "_chassis.pb.txt";
  FLAGS_test_routing_response_file = seq_num + "_routing.pb.txt";
  PlanningTestBase::SetUp();
  bool run_planning_success = RunPlanning("sunnyvale_stop", 0);
  EXPECT_FALSE(run_planning_success);
}

}  // namespace planning
}  // namespace apollo
