import os
from PIL import Image

def process_sprite(input_name, output_name, size=(64, 64)):
    try:
        # Load image
        img = Image.open(f"/artifacts/{input_name}")
        img = img.convert("RGBA")
        
        # Resize
        img = img.resize(size, Image.NEAREST)
        
        # We need a magenta background for transparency
        pixels = img.load()
        for y in range(img.height):
            for x in range(img.width):
                r, g, b, a = pixels[x, y]
                # If white or nearly white (background of generation), make it magenta
                if r > 240 and g > 240 and b > 240:
                    pixels[x, y] = (255, 0, 255, 255)
                    
        # Save as PNG
        img.save(f"/gfx/{output_name}.png")
        print(f"Saved {output_name}.png")
    except Exception as e:
        print(f"Error processing {input_name}: {e}")

def process_bg(input_name, output_name, size=(256, 192)):
    try:
        img = Image.open(f"/artifacts/{input_name}")
        img = img.convert("RGB")
        img = img.resize(size, Image.NEAREST)
        img.save(f"/gfx/{output_name}.png")
        print(f"Saved {output_name}.png")
    except Exception as e:
        print(f"Error processing {input_name}: {e}")

# Find generated files by prefix
files = os.listdir("/artifacts")
for f in files:
    if f.startswith("cantuna_pixelart") and f.endswith(".jpg"):
        process_sprite(f, "cantuna_sprite")
    elif f.startswith("tintin_pixelart") and f.endswith(".jpg"):
        process_sprite(f, "tintin_sprite")
    elif f.startswith("latunda_pixelart") and f.endswith(".jpg"):
        process_sprite(f, "latunda_sprite")
    elif f.startswith("card_back") and f.endswith(".jpg"):
        process_sprite(f, "card_back", size=(32, 48))
    elif f.startswith("board_plaza") and f.endswith(".jpg"):
        process_bg(f, "board_bg")
    elif f.startswith("touch_ui") and f.endswith(".jpg"):
        process_bg(f, "touch_bg")
