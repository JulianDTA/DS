from PIL import Image

img = Image.open('gfx/bg_bottom_orig.png').convert('RGBA')

# The inner board is roughly from x=24 to x=232, y=32 to y=144
# The compass is centered horizontally, so roughly x=100 to x=156
# Let's just clone from the left side (x=32 to x=88) to cover the compass!

# Compass bounding box (estimated):
box_to_cover = (100, 45, 160, 105)
width = box_to_cover[2] - box_to_cover[0]
height = box_to_cover[3] - box_to_cover[1]

# Source box (left side of the board):
source_box = (40, 45, 40 + width, 45 + height)

patch = img.crop(source_box)
img.paste(patch, (box_to_cover[0], box_to_cover[1]))

# Wait, the board has a slight horizontal gradient or lighting difference?
# Let's also blend the edges if possible, or just paste it directly and see how it looks.
# We will convert back to P using original palette.

orig_p = Image.open('gfx/bg_bottom_orig.png')
img_p = img.quantize(palette=orig_p, dither=0)
img_p.save('gfx/bg_bottom.png')
