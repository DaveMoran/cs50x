# Importt rules
from cs50 import get_int


# Step 1: Get height
height = get_int("Height: ")

# Step 2: Make sure height is in valid range
while height < 1 or height > 8:
    height = get_int("Height: ")

final_string = ""

# Step 3: Begin printing out pyramid
for i in range(1, height + 1):

    # First loop, print out space, then hash
    for j in range(height):
        if height - j > i:
            final_string += " "
        else:
            final_string += "#"

    # Add gutter
    final_string += "  "

    # Second loop, add hashes, then new line
    for k in range(height):
        if i > k:
            final_string += "#"

    final_string += "\n"

print(final_string, end="")