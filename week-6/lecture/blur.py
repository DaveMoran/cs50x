from PIL import Image, ImageFilter

before = Image.open("before.bmp");
after = before.filter(ImageFilter.BoxBlur(10));
after.save("after.bmp")