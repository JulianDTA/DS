import os
from PIL import Image

def process_sprite(input_name, output_name, size=(64, 64)):
    try:
        img = Image.open(f"/artifacts/{input_name}")
        img = img.convert("RGBA")
        img = img.resize(size, Image.NEAREST)
        
        pixels = img.load()
        for y in range(img.height):
            for x in range(img.width):
                r, g, b, a = pixels[x, y]
                # If white or nearly white (background of generation), make it MAGENTA
                if r > 240 and g > 240 and b > 240:
                    pixels[x, y] = (255, 0, 255, 255)
                    
        img.save(f"/gfx/{output_name}.png")
        print(f"Saved {output_name}.png with Magenta background")
    except Exception as e:
        print(f"Error processing {input_name}: {e}")

files = os.listdir("/artifacts")
for f in files:
    if f.startswith("cantuna_pixelart") and f.endswith(".jpg"):
        process_sprite(f, "cantuna_sprite")
    elif f.startswith("tintin_pixelart") and f.endswith(".jpg"):
        process_sprite(f, "tintin_sprite")
    elif f.startswith("latunda_pixelart") and f.endswith(".jpg"):
        process_sprite(f, "latunda_sprite")
