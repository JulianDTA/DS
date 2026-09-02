from PIL import Image

img = Image.open('gfx/bg_bottom.png').convert('RGB')
# Wood area without text or UI: x=14 to 242, y=36 to 98 (height 62)
strip = img.crop((14, 36, 242, 98))
img.paste(strip, (14, 108))

img.save('gfx/bg_bottom.png')
