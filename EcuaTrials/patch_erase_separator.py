from PIL import Image

img = Image.open('gfx/bg_bottom.png').convert('RGB')

# Take a clean horizontal strip from y=82 to y=94, full width
clean_strip = img.crop((0, 82, 256, 94))

# Create a patch of 256x74 to cover the separator (y=104) and the slots (y=108 to y=168)
# From y=94 to y=168 is exactly 74 pixels height.
patch = Image.new('RGB', (256, 74))
for y in range(0, 84, 12):
    patch.paste(clean_strip, (0, y))

# Crop the patch exactly to 74 pixels height just to be clean
patch = patch.crop((0, 0, 256, 74))

# Paste the patch starting from y=94, covering everything down to y=168
img.paste(patch, (0, 94))

img.save('gfx/bg_bottom.png')
