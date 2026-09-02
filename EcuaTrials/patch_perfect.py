from PIL import Image

img = Image.open('gfx/bg_bottom.png').convert('RGB')

# The inner clean wood is between x=28 and x=80.
clean_wood = img.crop((28, 40, 78, 102)) # width 50, height 62

# The inner area to cover is from x=24 to x=232. Width = 208.
# Create a patch of width 208 and height 62.
patch = Image.new('RGB', (208, 62))
for x in range(0, 208, 50):
    patch.paste(clean_wood, (x, 0))

# Now paste the patch into the image
img.paste(patch, (24, 106))

img.save('gfx/bg_bottom.png')
