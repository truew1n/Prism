import os

def count_lines_of_code(directory):
    total_lines = 0
    
    # Loop through all files and subdirectories in the current directory
    for root, _, files in os.walk(directory):
        for file in files:
            # Check if the file has one of the desired extensions
            if file.endswith(('.cpp', '.hpp', '.h', '.c')):
                file_path = os.path.join(root, file)
                with open(file_path, 'r', encoding='utf-8', errors='ignore') as f:
                    lines = f.readlines()
                    line_count = len(lines)
                    total_lines += line_count
                    print(f"{file_path}: {line_count} lines")
    
    return total_lines

if __name__ == "__main__":
    directory = os.getcwd()  # Current directory
    total_lines = count_lines_of_code(directory)
    print(f"\nTotal lines of code in .cpp, .hpp, .h, .c files: {total_lines}")
