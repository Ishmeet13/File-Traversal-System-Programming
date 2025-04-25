# 🗂️ FileTraversal Commander 🖥️

A powerful C-based file system utility for efficiently managing and manipulating files and directories through a simple command-line interface.

## 📋 Description

FileTraversal Commander is a lightweight system utility that leverages the `ftw.h` library for traversing file hierarchies. It provides essential file management operations including listing, counting, size calculation, selective deletion, and directory operations—all through an intuitive menu-driven interface.

## ✨ Features

- **List all files and directories** - Recursively display all paths in a directory
- **Count files** - Get the total number of files in a directory tree
- **Count directories** - Get the total number of directories in a directory tree
- **Calculate total size** - Determine the combined size of all files in a directory
- **Delete by extension** - Remove files with a specific extension
- **Copy directory** - Copy directories with optional extension exclusion
- **Move directory** - Relocate directories from source to destination

## 🛠️ Technical Details

- Written in C using the POSIX file tree walker (`ftw.h`)
- Uses system commands for copy and move operations
- Minimal dependencies, requiring only standard C libraries
- Compatible with Unix-like operating systems

## 📦 Installation

### Prerequisites
- GCC compiler
- POSIX-compliant operating system (Linux, macOS, etc.)

### Compilation
```bash
gcc -o filetraversal_commander main.c -Wall
```

## 🚀 Usage

1. Run the compiled program:
```bash
./filetraversal_commander
```

2. Select an option from the menu by entering the corresponding number:
```
Select an option:
1. List all files and directories (-ls)
2. Count all files (-fc)
3. Count all directories (-dc)
4. Calculate total size (-fs)
5. Delete files of specific extension (-del)
6. Copy directory (-cp)
7. Move directory (-mv)
8. Exit
Enter your choice:
```

3. Follow the prompts to provide necessary paths or parameters.

## 📝 Examples

### Listing all files in a directory:
```
Enter your choice: 1
Enter directory: /home/user/documents
/home/user/documents
/home/user/documents/file1.txt
/home/user/documents/file2.pdf
/home/user/documents/subfolder
/home/user/documents/subfolder/file3.docx
```

### Counting files:
```
Enter your choice: 2
Enter directory: /home/user/documents
Total files: 3
```

### Deleting files by extension:
```
Enter your choice: 5
Enter directory: /home/user/documents
Enter file extension: .tmp
Deleted: /home/user/documents/temp1.tmp
Deleted: /home/user/documents/temp2.tmp
```

## ⚠️ Caution

- The delete operation is permanent and cannot be undone
- Always verify the directory paths before performing copy, move or delete operations
- The program uses system commands which might not work identically across all platforms

## 👨‍💻 Development

### Code Structure
- `main.c` - Contains all functionality including the menu system and file operations
- Function callbacks for the `nftw()` function handle different file operations
- Global variables track counts and sizes during traversal

### Future Improvements
- Error handling for invalid paths and operations
- Support for Windows operating systems
- Pattern matching for more flexible file selection
- Progress indicators for operations on large directories

## 📄 License

This project is available under the MIT License - allowing for free use, modification, and distribution.

---

Created with ❤️ for efficient file system management.
