"""
Generate cheatset from the engine Wren library.

usage: generate_cheatset.py [path_to_files] [output_file.md]
"""

HEADER = """# Potetre2d Cheatset
This list every documented classes, methods and constants of the engine.
You don't need to import any module to use them and they are available
everywhere.

Please note that this cheatset is generated from the engine source code
and may change in the future. If you find any error, please report it
on the Potetre2d repository.

This document is licensed under the CC-BY-SA 4.0 license.
"""

import os, sys

if len(sys.argv) < 3:
    print("usage: generate_cheatset.py [path_to_files] [output_file.md]")
    sys.exit(1)

path = sys.argv[1]
output = sys.argv[2]

files = os.listdir(path)
files.sort()
# Filter out non .wren files
files = [f for f in files if f.endswith(".wren")]

print("Generating cheatset from {} files!".format(len(files)))
print("- From path: {}".format(path))
print("- Output file: {}".format(output))

#### Utility functions ####

def remove_prefix(text, prefix):
    """
    Remove @prefix from @text

    Example: "@thisis a test: A text" -> "A text"
    """
    # Find the :
    index = text.find(":")
    if index == -1:
        # Find last space before
        index = text.rfind(" ", 0, index)
        return text[index + 1:].strip()
    # Split after :
    return text.split(":")[1].strip()

#### Main ####
output_file = open(output, "w")
output_file.write(HEADER)
for file in files:
    file_path = os.path.join(path, file)
    print("   ** Parsing {} ...".format(file_path))
    with open(file_path, "r") as f:
        output_file.write("\n## {}\n".format(file.split(".")[0].capitalize()))
        # Get lines
        lines = f.readlines()
        # Everything but comments
        lines = [l.strip() for l in lines if l.strip().startswith("//")]

        current_class = ""

        for line in lines:
            # Remove comment prefix
            line = line.replace("//", "").strip()

            if line.startswith("@class-desc"):
                output_file.write("**{}**\n\n".format(remove_prefix(line, "@class-desc")))
            elif line.startswith("@class"):
                output_file.write("### {}\n".format(remove_prefix(line, "@class")))
                current_class = remove_prefix(line, "@class")
            elif line.startswith("@method"):
                output_file.write("#### {}\n".format(remove_prefix(line, "@method")))
            elif line.startswith("@const"):
                output_file.write("#### Constant: {}.{}\n".format(current_class, remove_prefix(line, "@const")))
            elif line.startswith("@ctor"):
                output_file.write("#### Constructor: {}.{}\n".format(current_class, remove_prefix(line, "@ctor")))
            elif line.startswith("@function"):
                output_file.write("#### {}.{}\n".format(current_class, remove_prefix(line, "@function")))
            elif line.startswith("@desc"):
                output_file.write("{}\n\n".format(remove_prefix(line, "@desc")))
            elif line.startswith("@param"):
                output_file.write(" * {}\n".format(remove_prefix(line, "@param")))
            elif not line.startswith("@") or len(line) == 0:
                continue
            else:
                output_file.write(" * {}\n".format(line))

        f.close()

print("- Done!")
output_file.close()