# Quick Start Guide

## 🚀 Get Started in 30 Seconds

### Compile
```bash
g++ -std=c++11 -Wall -Wextra UAS.cpp -o UAS
```

### Run
```bash
./UAS
```

## 📋 Menu Overview

| # | Feature | Use Case |
|---|---------|----------|
| 1 | Tambah File | Add new file with content |
| 2 | Hapus File | Delete a file |
| 3 | Rename File | Rename a file |
| 4 | Undo | Undo last operation |
| 5 | Tampilkan Struktur Folder | View folder tree |
| 6 | Cari File | Search & view file |
| 7 | Tampilkan File di Folder | List files in folder |
| 8 | Tampilkan Semua File | View all files |
| 9 | Tambah Folder | Create new folder |
| 10 | Edit File | Edit file content ⭐ NEW |
| 0 | Keluar | Exit |

## ⚡ Quick Commands

### Create folder structure
```
9 → src (Enter)
9 → docs (Enter)
```

### Add a file
```
1 → src (folder)
  → 1 (ID)
  → main.cpp (name)
  → code lines...
  → . (finish)
```

### Edit file
```
10 → src (folder)
   → main.cpp (filename)
   → old content shown
   → new content...
   → . (finish)
```

### Search & view
```
6 → src (folder)
  → main.cpp (filename)
  → Shows: ID, name, size, content
```

### Undo last change
```
4 → Restores previous state
```

## 💡 Tips

- **Multiline input**: End with "." on its own line
- **File size**: Auto-calculated in KB (minimum 1 KB)
- **Undo works**: For add, delete, rename, AND edit
- **BST ordering**: Folders appear alphabetically
- **Full snapshots**: Undo restores entire system state

## 📊 Example Workflow

```bash
# Create structure
9 → project
9 → lib

# Add file
1 → project → 1 → app.cpp → code... → .

# View files
8

# Edit content
10 → project → app.cpp → new code... → .

# Undo edit
4

# View again
8
```

## ✅ Features at a Glance

- ✅ **Linked List**: Files in each folder
- ✅ **Binary Tree**: Folder hierarchy
- ✅ **Stack**: Undo with complete snapshots
- ✅ **Auto Size**: Calculated from content
- ✅ **Edit Files**: NEW feature
- ✅ **Full History**: Undo any operation

## 📝 File Input Format

### For file content:
```
line 1
line 2
line 3
.
```

(Press Enter after each line, type "." alone to end)

### For single inputs:
```
Just type and press Enter
```

## 🎯 Common Tasks

**Task: Update main.cpp**
```
Menu 10 → src → main.cpp → [shows old content] → 
type new code → . → Done!
```

**Task: Find what's in a file**
```
Menu 6 → src → main.cpp → Shows everything
```

**Task: Revert last change**
```
Menu 4 → Changes to previous state
```

## ⚙️ Technical Info

- **Language**: C++11
- **Lines**: 664
- **Compilation**: No warnings/errors
- **Memory**: Safe, no leaks
- **Status**: Production ready

## 📖 Full Documentation

See detailed guides:
- `README.md` - Overview
- `COMPLETE_FEATURES.md` - All features
- `EDIT_FEATURE.md` - Edit feature details
- `FINAL_SUMMARY.md` - Complete summary

---

**Ready to go!** Run `./UAS` and start managing your repository!
