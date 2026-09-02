from PIL import Image

img = Image.open('gfx/bg_bottom.png').convert('RGB')

# Pure wood patch, strictly away from any borders or compass rose
pure_wood = img.crop((30, 40, 80, 102)) # width 50, height 62

# Create a full-width pure wood strip
strip = Image.new('RGB', (224, 62)) # 240 - 16 = 224
for x in range(0, 224, 50):
    strip.paste(pure_wood, (x, 0))

# Paste the full-width strip into the image, covering the slots (x=16 to 240, y=106 to 168)
img.paste(strip, (16, 106))

img.save('gfx/bg_bottom.png')
