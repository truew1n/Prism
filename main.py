import os

def count_lines_of_code(directory):
    total_lines = 0
    total_classes = 0
    
    # Loop through all files and subdirectories in the specified directories
    for root, _, files in os.walk(directory):
        # Skip directories that are not Engine or Game
        if os.path.basename(root) not in ['Engine', 'Game']:
            continue
        
        for file in files:
            # Check if the file has one of the desired extensions
            if file.endswith(('.cpp', '.hpp', '.h', '.c', '.frag', '.vert')):
                if file == "stb_image.h" or file == "stb_image.cpp":
                    continue
                if file.endswith(('.hpp', '.h')):
                    total_classes += 1
                file_path = os.path.join(root, file)
                with open(file_path, 'r', encoding='utf-8', errors='ignore') as f:
                    lines = f.readlines()
                    line_count = len(lines)
                    total_lines += line_count
                    print(f"{file_path}: {line_count} lines")
    
    return [total_lines, total_classes]

if __name__ == "__main__":
    current_directory = os.getcwd()  # Current directory
    total_lines = 0
    total_classes = 0
    
    # Process Engine and Game folders
    for folder in ['Engine', 'Game']:
        folder_path = os.path.join(current_directory, folder)
        if os.path.isdir(folder_path):
            data = count_lines_of_code(folder_path)
            total_lines += data[0]
            total_classes += data[1]
    
    print("\n")
    print(f"Total lines of code in .cpp, .hpp, .h, .c, .frag, .vert files: {total_lines}")
    print(f"Total Class Count: {total_classes}")
