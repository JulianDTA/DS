from PIL import Image

img = Image.open('gfx/bg_bottom.png').convert('RGB')

# Take a clean horizontal strip from y=82 to y=94, full width
clean_strip = img.crop((0, 82, 256, 94))

# Create a patch of 256x60 to cover the slots (y=108 to y=168)
patch = Image.new('RGB', (256, 60))
for y in range(0, 60, 12):
    patch.paste(clean_strip, (0, y))

# Paste the patch over the slots
img.paste(patch, (0, 108))

img.save('gfx/bg_bottom.png')
