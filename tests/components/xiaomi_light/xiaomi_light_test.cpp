#include <gtest/gtest.h>
#include "esphome/components/xiaomi_light/xiaomi_light.h"

namespace esphome::xiaomi_light::testing {

class XiaomiLightMapTest : public ::testing::Test {
 protected:
  XiaomiLight light_;
};

TEST_F(XiaomiLightMapTest, MapZeroInput) {
  // At brightness=0, output is mapped to ostart=0.06 (minimum level)
  EXPECT_NEAR(light_.map(0.0f, 0.0f, 100.0f, 0.06f, 100.0f), 0.06f, 0.001f);
}

TEST_F(XiaomiLightMapTest, MapFullInput) {
  // At brightness=100, output reaches oend=100.0
  EXPECT_NEAR(light_.map(100.0f, 0.0f, 100.0f, 0.06f, 100.0f), 100.0f, 0.001f);
}

TEST_F(XiaomiLightMapTest, MapMidpoint) {
  // At brightness=50, output is near the midpoint of [0.06, 100.0]
  float result = light_.map(50.0f, 0.0f, 100.0f, 0.06f, 100.0f);
  EXPECT_NEAR(result, 50.03f, 0.05f);
}

TEST_F(XiaomiLightMapTest, MapLinearIdentity) {
  // Linear identity mapping: [0, 100] -> [0, 100]
  EXPECT_NEAR(light_.map(0.0f, 0.0f, 100.0f, 0.0f, 100.0f), 0.0f, 0.001f);
  EXPECT_NEAR(light_.map(50.0f, 0.0f, 100.0f, 0.0f, 100.0f), 50.0f, 0.001f);
  EXPECT_NEAR(light_.map(100.0f, 0.0f, 100.0f, 0.0f, 100.0f), 100.0f, 0.001f);
}

TEST_F(XiaomiLightMapTest, GetTraitsMinMireds) {
  // Default CW color temperature is 175 mireds (cold white)
  auto traits = light_.get_traits();
  EXPECT_FLOAT_EQ(traits.get_min_mireds(), 175.0f);
}

TEST_F(XiaomiLightMapTest, GetTraitsMaxMireds) {
  // Default WW color temperature is 333 mireds (warm white)
  auto traits = light_.get_traits();
  EXPECT_FLOAT_EQ(traits.get_max_mireds(), 333.0f);
}

}  // namespace esphome::xiaomi_light::testing
