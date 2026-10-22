"""Schema structure tests for xiaomi_light ESPHome component modules."""

from pathlib import Path
import sys

sys.path.insert(0, str(Path(__file__).parent.parent))

import components.xiaomi_light as hub  # noqa: E402


class TestHubConstants:
    def test_hub_class_defined(self):
        assert hub.XiaomiLight is not None
