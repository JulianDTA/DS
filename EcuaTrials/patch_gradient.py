from PIL import Image

img = Image.open('gfx/bg_bottom.png').convert('RGB')
pixels = img.load()

# Interpolate vertically for the slot area
for x in range(16, 240):
    top_color = pixels[x, 105]
    bottom_color = pixels[x, 169]
    
    # Calculate gradient
    for y in range(106, 169):
        ratio = (y - 105) / (169 - 105)
        r = int(top_color[0] * (1 - ratio) + bottom_color[0] * ratio)
        g = int(top_color[1] * (1 - ratio) + bottom_color[1] * ratio)
        b = int(top_color[2] * (1 - ratio) + bottom_color[2] * ratio)
        
        # Add a tiny bit of noise to simulate wood grain?
        # Actually just a smooth gradient is fine for a flat board.
        pixels[x, y] = (r, g, b)

img.save('gfx/bg_bottom.png')
