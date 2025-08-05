# Day 1 – Deep Dive into Memory Layout in C

## Topic: Memory Layout in C Programming

Today's learning focuses on understanding how memory is organized and utilized during C program execution. A clear grasp of memory layout is foundational for becoming a high-performance system-level programmer.

---

## 📂 Key Concepts Covered

### 🔹 Memory Segments:
- **Text Segment (Code Segment)**: Stores executable instructions.
- **Data Segment**:
  - `.data`: Stores initialized global and static variables.
  - `.bss`: Stores uninitialized global and static variables.
- **Heap**: Dynamically allocated memory (`malloc`, `calloc`, etc.)
- **Stack**: Stores local variables and function call frames.

### 🧪 Code Demonstrations:
- Print memory addresses of:
  - Functions (Text Segment)
  - Global/static variables (Data/BSS Segment)
  - Local variables (Stack)
  - Dynamically allocated variables (Heap)

### 🧰 Tools Used:
- `gcc` compiler
- `gdb` for memory inspection
- `objdump` and `nm` for segment analysis
