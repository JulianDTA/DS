import os
from PIL import Image

files = os.listdir("/artifacts")
for f in files:
    if f.startswith("touch_ui_board_clean") and f.endswith(".jpg"):
        img = Image.open("/artifacts/" + f).convert("RGB")
        img = img.resize((256, 192), Image.NEAREST)
        img.save("/gfx/touch_bg.png")
        print("Clean touch bg saved!")
