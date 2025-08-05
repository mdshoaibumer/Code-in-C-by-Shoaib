# 🧠 Memory Layout in C — Deep Dive

This folder is part of my system programming journey to understand how memory is organized for C programs at a low level.

## 📌 Topics Covered
- Stack vs Heap (with diagrams & code)
- BSS, Data, and Text Segments
- Function & variable address tracing
- Common mistakes in memory usage
- GDB inspection of memory segments

## 🧪 Example Files
- `stack_vs_heap.c`: Demo of local vs dynamically allocated memory
- `memory_map_notes.md`: Text explanation and visuals
- `gdb_output.txt`: Memory layout from debugging sessions

## 🔧 Commands Used
```bash
gcc -g stack_vs_heap.c -o demo
gdb ./demo
info proc mappings

