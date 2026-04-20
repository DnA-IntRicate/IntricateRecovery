from raptor.core.process import run
from raptor.hooks.registry import register_hook

from typing import List, Optional


@register_hook("post_merge")
def post_merge_hook(args: Optional[List[str]]):
    run(["raptor", "clean", "workspace"])
    run(["raptor", "premake", "default"])
