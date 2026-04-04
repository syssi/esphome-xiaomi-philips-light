"""Schema structure tests for xiaomi_light ESPHome component modules."""

import os
import sys

sys.path.insert(0, os.path.join(os.path.dirname(__file__), ".."))

import components.xiaomi_light as hub  # noqa: E402


class TestHubConstants:
    def test_hub_class_defined(self):
        assert hub.XiaomiLight is not None
