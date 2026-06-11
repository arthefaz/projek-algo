# Edit File Feature Documentation

## Overview
The **Edit File** feature allows you to modify the contents of existing files and automatically recalculate their sizes.

## Features

### Edit File Menu Option
- **Menu Number**: 10
- **Label**: Edit File

### How to Use

1. **Select Option 10** from the main menu
2. **Enter Folder Name** - Where the file is located
3. **Enter File Name** - The name of the file you want to edit
4. **View Old Content** - The system displays the current file content
5. **Enter New Content** - Type the new content line by line
6. **Finish Input** - Type just a dot (`.`) on a line by itself to complete
7. **Automatic Size Update** - The file size recalculates automatically

### Example

```
Select: 10
Nama Folder : src
Nama file : main.cpp

Konten lama:
---
int main() { return 0; }
---

Masukkan konten baru (gunakan . di awal baris untuk selesai):
#include <iostream>
int main() {
    std::cout << "Hello World" << std::endl;
    return 0;
}
.

File berhasil di-edit (Ukuran baru: 1 KB)
```

## Key Characteristics

### Automatic Size Calculation
- File size is **automatically recalculated** after editing
- Size = content length / 1024 bytes
- Minimum 1 KB (very small files are shown as 1 KB)

### Snapshot Integration
- **Automatically creates a snapshot** after editing
- Full undo support using the **Undo feature (Option 4)**
- You can restore to the previous version anytime

### User Feedback
- Shows the old content before editing
- Displays new size after editing completes
- Provides success/error messages

## Size Calculation Examples

| Content | Approx Size | Shown As |
|---------|------------|----------|
| "hello" (5 bytes) | 5/1024 | 1 KB |
| ~5KB of text | 5120 bytes | 5 KB |
| ~10KB of text | 10240 bytes | 10 KB |

## Integration with Undo System

### Before Edit
```
Menu → File Contents: "old content"
File Size: 1 KB
```

### After Edit
```
Menu → File Contents: "new content"
File Size: 5 KB (auto-updated)
Snapshot Created
```

### After Undo
```
Menu → File Contents: "old content" (restored)
File Size: 1 KB (restored)
```

## Technical Implementation

### Function Signature
```cpp
void editFile()
```

### Process Flow
1. Get folder name from user
2. Get file name from user
3. Find the folder in BST
4. Find the file in the folder's linked list
5. Display current file content
6. Read new content from input (until ".")
7. Update file's isiFile
8. Recalculate ukuranFile using `hitungUkuranFile()`
9. Create snapshot for undo
10. Display confirmation with new size

### Memory Management
- No new memory allocation (reuses existing FileNode)
- Old content string is replaced by new content
- String resources are properly managed by C++ std::string

## Error Handling

- **Folder tidak ditemukan** - Entered folder doesn't exist
- **File tidak ditemukan** - Entered file name doesn't exist

## Related Features

- **Option 1**: Tambah File - Create new files with content
- **Option 3**: Rename File - Change file names
- **Option 4**: Undo Aktivitas - Revert changes
- **Option 6**: Cari File - View file contents
- **Option 7**: Tampilkan File di Folder - List files with sizes

## Notes

- Edit operations create snapshots automatically
- You can edit multiple times before using undo
- Each edit creates a new snapshot state
- File ID remains the same after editing
- Only content and size change
