"""
Remove comments from a Wren source file.
usage: python remove_comments.py <path/to/file> <output_file>
"""
import sys,os

def main():
    if len(sys.argv) < 3:
        print("usage: python remove_comments.py <path/to/file> <output_file>")
        return
    file_path = sys.argv[1]
    output_path = sys.argv[2]
    if not os.path.exists(file_path):
        print("file not found")
        return

    with open(file_path, "r") as f:
        lines = f.readlines()
    with open(output_path, "w") as f:
        for line in lines:
            if line.strip().startswith("//"):
                continue
            if line[0] == "\n":
                continue
            f.write(line.strip() + "\n")

if __name__ == "__main__":
    main()
