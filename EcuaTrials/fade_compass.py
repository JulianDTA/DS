from PIL import Image

# Open original and convert to RGBA for blending
img = Image.open('gfx/bg_bottom.png').convert('RGBA')

# Bounding box of the compass
box = (100, 45, 160, 105)

# Pick a base wood color from a clear area
base_color = img.getpixel((50, 50))

# Create a solid block of the base wood color
wood_block = Image.new('RGBA', img.size, base_color)

# Create a mask that is only white in the compass area, with some fading edges
mask = Image.new('L', img.size, 0)
for y in range(box[1], box[3]):
    for x in range(box[0], box[2]):
        # Distance to center for a soft circular mask
        cx = (box[0] + box[2]) / 2
        cy = (box[1] + box[3]) / 2
        dist = ((x - cx)**2 + (y - cy)**2)**0.5
        max_dist = (box[2] - box[0]) / 2
        
        if dist < max_dist:
            # Opacity of the wood covering the compass (higher = fainter compass)
            # Let's make it 75% covered by wood
            mask.putpixel((x, y), 190)

# Composite the solid wood over the image using the mask
faded_img = Image.composite(wood_block, img, mask)

# Convert back to Palette mode using the original palette!
orig_p = Image.open('gfx/bg_bottom.png')
final_img = faded_img.convert('RGB').quantize(palette=orig_p, dither=Image.Dither.NONE)
final_img.save('gfx/bg_bottom.png')
print('Faded compass successfully!')
