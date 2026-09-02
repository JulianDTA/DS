from PIL import Image
img = Image.open('gfx/bg_bottom.png').convert('RGB')

# Let's find the inner borders of the panel at y=60
min_x = 0
max_x = 255

# Left border
for x in range(0, 50):
    p = img.getpixel((x, 60))
    if p[0] > 100: # Wood color starts
        print(f"Left inner wood starts at {x}")
        break

# Right border
for x in range(255, 200, -1):
    p = img.getpixel((x, 60))
    if p[0] > 100:
        print(f"Right inner wood starts at {x}")
        break

