# CC Lab - Compiler Construction Learning Repository

A comprehensive collection of compiler construction (CC) labs and a mini-compiler project. This repository contains practical implementations of compiler concepts including lexical analysis, parsing, symbol tables, and a complete MicroJava mini-compiler.

---

## 📁 Repository Structure

```
CC Lab/
├── Lab 1/              # Expression Evaluation
├── lab 2/              # File Processing Basics
├── lab 3/              # Multi-threaded Buffer Management
├── lab 4/              # Lexical Analyzer with Tokenization
├── Lab 5/              # NFA Design (JFLAP)
├── Lab 6/              # Symbol Table Implementation
├── Mini Compiler/      # Complete MicroJava Compiler Project
└── README.md          # This file
```

---

## 🔬 Lab Descriptions

### Lab 1: Prefix Expression Evaluation
**Location:** [Lab 1/](Lab%201/)

**Overview:**
Implements evaluation of prefix (Polish notation) mathematical expressions using a stack-based approach.

**Files:**
- `Prefix-eval.cpp` - C++ implementation of prefix expression evaluator

**Key Concepts:**
- Stack data structure
- Operator precedence
- Mathematical expression parsing
- Support for operators: `+`, `-`, `*`, `/`, `^`

**Features:**
- Evaluates prefix expressions correctly
- Pretty-prints floating-point results
- Input validation and error handling

---

### Lab 2: File Processing Basics
**Location:** [lab 2/](lab%202/)

**Overview:**
Introduces basic file I/O operations and data processing from files.

**Files:**
- `Task1.cpp` - File reading and display implementation
- `Task2.cpp` - Additional file processing tasks
- `Random.txt` - Sample input data
- `report.csv` - Generated output/report
- `sample_files/` - Directory containing test data
  - `File1.txt`
  - `File2.txt`
  - `File3.txt`

**Key Concepts:**
- File input/output operations
- Data parsing and processing
- CSV file generation
- Error handling for file operations

---

### Lab 3: Multi-threaded Buffer Management
**Location:** [lab 3/](lab%203/)

**Overview:**
Implements producer-consumer pattern with double buffering using threading. Demonstrates synchronization techniques for concurrent programming.

**Files:**
- `Task1.py` - Producer-consumer with double-buffer implementation

**Key Concepts:**
- Threading in Python
- Buffer management and synchronization
- Condition variables and locks
- Producer-consumer pattern
- Double buffering technique

**Features:**
- Two alternating buffers (Buffer A and Buffer B)
- Producer thread fills buffers with user input
- Consumer thread processes buffered data
- Thread synchronization using locks and conditions
- Graceful program termination

---

### Lab 4: Lexical Analyzer with Tokenization
**Location:** [lab 4/](lab%204/)

**Overview:**
Implements lexical analysis (tokenization) for MicroJava source code. Converts raw source code into meaningful tokens.

**Files:**
- `Lexical_Analyzer.py` - Main Python lexical analyzer implementation
- `Lexical_Analyzer.cpp` - C++ version of lexical analyzer
- `source.mj` - Sample MicroJava source code for testing
- `tokens.txt` - Generated token output
- `tokens2.txt` - Additional token output

**Key Concepts:**
- Regular expressions for pattern matching
- Token classification
- Lexeme and token relationships
- Symbol recognition

**Token Types Recognized:**
- Keywords: `if`, `else`, `int`, `float`, `bool`, `return`, `while`, `for`, `class`, `program`, `void`, `print`, `read`, `final`, `new`
- Identifiers: Variable and function names
- Numbers: Integers and floating-point numbers
- Operators: Arithmetic and logical operators
- Delimiters: Parentheses, braces, semicolons

**Features:**
- Multi-threaded buffer processing
- Token generation with line/column information
- Error detection and reporting
- Support for both single and multi-line comments

---

### Lab 5: NFA Design (JFLAP)
**Location:** [Lab 5/](Lab%205/)

**Overview:**
Designs Non-Deterministic Finite Automata (NFA) for various lexical elements using JFLAP (Java Formal Languages and Automata Package).

**Files:**
- `charConst.jff` - NFA for character constants
- `comments.jff` - NFA for comment handling
- `identifier.jff` & `identifier (1).jff` - NFA for identifiers
- `Keywords.jff` - NFA for keyword recognition
- `number.jff` - NFA for number patterns
- `operators.jff` - NFA for operator recognition
- `symbols.jff` - NFA for special symbols
- `MicroJava Lexical Analyzer NFA.jff` - Complete lexical analyzer NFA
- `MicorJava Stateless NFA.jff` - Stateless NFA variant
- `Part 1.jff` & `Part 3 Statelessapproach.jff` - Lab assignment parts
- `NFA.jff` - General NFA example
- `test.txt` - Test cases

**Key Concepts:**
- Finite State Machines
- Non-deterministic automata
- State transitions
- Acceptance conditions
- Visual automata design

**Usage:**
Open `.jff` files with JFLAP software to visualize and test the automata.

---

### Lab 6: Symbol Table Implementation
**Location:** [Lab 6/](Lab%206/)

**Overview:**
Implements symbol table data structures using AVL Trees for efficient symbol management in compiler phases.

**Files:**
- `Symbol_table.py` - AVL Tree-based symbol table implementation

**Key Concepts:**
- Symbol table design and management
- AVL Tree self-balancing binary search tree
- Tree rotations (left and right)
- Symbol insertion, lookup, and deletion
- Balance factor maintenance

**Features:**
- Self-balancing AVL tree structure
- Efficient insertion and search operations (O(log n))
- Symbol key-value storage
- Automatic height balancing
- Support for scope management

**Data Structure:**
```
AVLNode:
  - key: Symbol identifier
  - value: Associated information (type, scope, etc.)
  - left/right: Child nodes
  - height: Node height for balancing
```

---

## 🔧 Mini Compiler Project
**Location:** [Mini Compiler/](Mini%20Compiler/)

**Overview:**
A complete MicroJava mini-compiler with both desktop (Tkinter GUI) and web (FastAPI) interfaces. Provides compilation of simplified Java-like programs.

### Project Structure
```
Mini Compiler/
├── mini-compiler.py          # Desktop GUI application (Tkinter)
├── mini_compiler.py          # Core compiler logic
├── mini-compiler.py          # Alternative version
├── requirements.txt          # Python dependencies
├── Dockerfile               # Docker containerization
├── README.md                # Project documentation
├── webapp/
│   ├── main.py             # FastAPI backend
│   ├── interpreter.py      # Interpreter module
│   ├── __pycache__/
│   └── static/
│       └── index.html      # Web UI frontend
└── __pycache__/
```

### Features

#### Desktop Application
- **Technology:** Python Tkinter GUI
- **Functionality:** Local compilation of MicroJava programs
- **Launch:** `python mini-compiler.py`

#### Web Application
- **Backend:** FastAPI (Python web framework)
- **Frontend:** Static HTML interface
- **Server:** Uvicorn ASGI server

### Dependencies
```
fastapi==0.115.6
uvicorn[standard]==0.34.0
pydantic==2.10.4
```

### Installation & Running

#### Web Application (Recommended)
```bash
# Install dependencies
python -m pip install -r requirements.txt

# Run the server
python -m uvicorn webapp.main:app --host 127.0.0.1 --port 8000
```

Access in browser: `http://127.0.0.1:8000`

**API Endpoint:**
- `POST /api/compile`
- Request body: `{"source":"program P { void main() { } }"}`

#### Desktop Application
```bash
python mini-compiler.py
```
*Note:* Tkinter may not be available on Linux servers. Use web app instead.

### Docker Deployment (Render)

1. Push repository to GitHub
2. Create Web Service on Render
3. Connect your GitHub repository
4. Select **Docker** environment
5. Render auto-detects `Dockerfile`
6. Deploy and share your Render URL

---

## 📋 Compiler Construction Progression

The labs follow a logical progression in compiler design:

1. **Lab 1-2** → Foundation (expression evaluation, file I/O)
2. **Lab 3** → Concurrency (buffer management for input processing)
3. **Lab 4** → Lexical Analysis (tokenization)
4. **Lab 5** → Formal Languages (automata design for lexical rules)
5. **Lab 6** → Symbol Management (efficient data structures)
6. **Mini Project** → Integration (complete compiler pipeline)

---

## 🚀 Getting Started

### Prerequisites
- **C++**: GCC or Clang compiler for Lab 1-4 C++ files
- **Python**: Python 3.7+ for Labs 3-6 and Mini Compiler
- **JFLAP**: Download from [jflap.org](http://www.jflap.org/) for Lab 5
- **Git**: For version control

### Quick Start

1. **Clone the repository:**
   ```bash
   git clone <repository-url>
   cd "CC Lab"
   ```

2. **Run a specific lab:**
   ```bash
   # Lab 1 (C++)
   cd "Lab 1"
   g++ -o prefix-eval Prefix-eval.cpp
   ./prefix-eval

   # Lab 3 (Python)
   cd "lab 3"
   python Task1.py

   # Lab 4 (Python)
   cd "lab 4"
   python Lexical_Analyzer.py
   ```

3. **Run Mini Compiler:**
   ```bash
   cd "Mini Compiler"
   python -m pip install -r requirements.txt
   python -m uvicorn webapp.main:app --host 127.0.0.1 --port 8000
   ```

---

## 📊 Key Technologies & Concepts

| Lab | Technology | Key Concept |
|-----|-----------|------------|
| Lab 1 | C++ | Data Structures (Stack) |
| Lab 2 | C++ | File I/O |
| Lab 3 | Python | Threading & Synchronization |
| Lab 4 | Python/C++ | Lexical Analysis & Regex |
| Lab 5 | JFLAP | Formal Languages (NFA) |
| Lab 6 | Python | Advanced Data Structures (AVL Tree) |
| Mini Compiler | Python | Full Compiler Pipeline |

---

## 📝 Notes for Students

- **Labs 1-6** are educational exercises covering fundamental compiler concepts
- **Mini Compiler** is the capstone project integrating all learned concepts
- All code includes comments explaining key operations
- Test files are provided for hands-on practice
- JFLAP files (Lab 5) are best viewed with JFLAP visualization tool

---

## 🔗 Useful Resources

- **JFLAP Download:** [http://www.jflap.org/](http://www.jflap.org/)
- **FastAPI Documentation:** [https://fastapi.tiangolo.com/](https://fastapi.tiangolo.com/)
- **Compiler Design Concepts:** Standard compiler construction textbooks
- **Python Threading:** [Python Documentation](https://docs.python.org/3/library/threading.html)
- **Regular Expressions:** [Regex101.com](https://regex101.com/)

---

## 📄 License

This project is for educational purposes as part of compiler construction coursework.

---

## ✅ Checklist for Review

- [ ] All labs completed and tested
- [ ] Mini Compiler web interface deployed
- [ ] Documentation updated
- [ ] Code comments added
- [ ] Test cases verified
- [ ] README reviewed

---

**Last Updated:** January 2026

**Status:** Complete with all labs and mini-compiler project
