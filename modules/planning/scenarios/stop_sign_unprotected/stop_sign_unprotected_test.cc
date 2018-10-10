/******************************************************************************
 * Copyright 2018 The Apollo Authors. All Rights Reserved.
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

/**
 * @file
 **/

#define protected public
#define private public
#include "modules/planning/scenarios/stop_sign_unprotected/stop_sign_unprotected.h"  // NOINT

#include <memory>

#include "gtest/gtest.h"

#include "cybertron/common/log.h"
#include "modules/common/util/file.h"
#include "modules/planning/common/planning_gflags.h"

namespace apollo {
namespace planning {

class StopSignUnprotectedScenarioTest : public ::testing::Test {
 public:
  virtual void SetUp() {}

 protected:
  std::unique_ptr<StopSignUnprotectedScenario> scenario_;
};

TEST_F(StopSignUnprotectedScenarioTest, VerifyConf) {
  FLAGS_scenario_stop_sign_unprotected_config_file =
      "//apollo/modules/planning/conf/"
      "scenario_stop_sign_unprotected_config.pb.txt";

  ScenarioConfig config;
  EXPECT_TRUE(apollo::common::util::GetProtoFromFile(
      FLAGS_scenario_side_pass_config_file, &config));
}

TEST_F(StopSignUnprotectedScenarioTest, InitTasks) {
  FLAGS_scenario_stop_sign_unprotected_config_file =
      "//apollo/modules/planning/testdata/conf/"
      "scenario_stop_sign_unprotected_config.pb.txt";

  scenario_.reset(new StopSignUnprotectedScenario());
  EXPECT_EQ(scenario_->scenario_type(),
            ScenarioConfig::STOP_SIGN_UNPROTECTED);

  ScenarioConfig config;
  EXPECT_TRUE(apollo::common::util::GetProtoFromFile(
      FLAGS_scenario_stop_sign_unprotected_config_file, &config));

  EXPECT_TRUE(scenario_->Init());

  std::vector<std::unique_ptr<Task>> tasks;
  // stage stop
  scenario_->InitTasks(config, 0, &tasks);
  EXPECT_EQ(tasks.size(), 0);

  // stage creep
  scenario_->InitTasks(config, 1, &tasks);
  EXPECT_EQ(tasks.size(), 0);

  // stage intersection_cruise
  scenario_->InitTasks(config, 2, &tasks);
  EXPECT_EQ(tasks.size(), 5);
}

}  // namespace planning
}  // namespace apollo
