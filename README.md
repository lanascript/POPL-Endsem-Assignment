## 🚀 POPL End-Semester Assignment: Functional + OO Container Framework

This project implements a flexible, functional, and object-oriented list-processing framework in C++ as required for the CS F301 Principles of Programming Languages End-Semester Assignment.

-----

## 👥 Team Members

| Name | ID | GitHub Handle |
| :--- | :--- | :--- |
| **Ashmita Dutta** | (2022B1A71372G) | lanascript |
| **Vedashree Mahajan** | (2022B1A70216G) | VM1235 |

-----

## 💡 Project Overview: Decoupled Container System

The core objective was to create a modern container framework leveraging **contain-and-delegate composition** to separate **behavior (containers)** from **storage (backends)**.

### Key Architectural Features:

  * **Storage–Behavior Decoupling:** The `List<T>` and various Container classes delegate all storage operations to an `IStorage<T>` backend.
  * **Interchangeable Backends:** Users can instantiate `List` with `VectorStorage`, `LinkedListStorage`, or `HeapStorage` seamlessly.
  * **Functional Design:** High-level list-processing modules (Search, Sort, Aggregate) emphasize a "WHAT-first" approach, promoting clean, reusable code.

-----

## ✔️ Features Implemented

The project is structured into three main layers: Storage, Container, and List Abstraction, supplemented by powerful utility modules.

### 1\. Storage Layer (Contain-&-Delegate)

  * `IStorage<T>` (Pure virtual interface)
  * `VectorStorage<T>` (Standard dynamic array backend)
  * `LinkedListStorage<T>` (Double-ended list backend)
  * `HeapStorage<T>` (Priority queue/Heap structure backend)

### 2\. Container Layer

General-purpose containers implemented over the Storage Layer:

  * `Stack<T>`
  * `Queue<T>`
  * `Deque<T>`
  * `PriorityQueue<T>`

### 3\. List Abstraction (`List<T>`)

The central abstraction providing core list operations:

  * `push_back`, `push_front`, `pop_back`, `pop_front`
  * `front`, `back`, `at`, `size`, `empty`
  * `clone()` and `append()`

### 4\. Utility Modules (Functional)

| Module | Implemented Features |
| :--- | :--- |
| **File Reader** | `read_lines(path)`, `read_tokens(path)`, `read_all(path)` |
| **Searching** | Linear search, `contains`, `find_all_indices`, Substring search, Case-insensitive search |
| **Sorting** | Default sort, Custom comparator sort, Stable sort |
| **Aggregation** | `counting_inversions`, `average` (numeric), `map`, `filter`, `reduce` |

### 5\. Functional Programming Layer (Member B)

- `core/FunctionalOps.hpp` introduces higher-order helpers (`map`, `filter`, `fold_left`, `take`, `drop`, `distinct`, `sorted`) that reuse the existing `List<T>` abstraction without touching storage backends.
- `FunctionalOps::Pipeline<T>` wraps lists in a fluent API (e.g., `tokens → filter(len > 3) → map(uppercase) → take(10)`) while respecting move-only semantics through cloning.
- `FunctionalOps::keyword_frequencies` implements the assignment’s keyword analytics use case, returning sorted `keyword -> count` rows for any token/keyword inputs.
- Additional helpers (`FunctionalOps::from`, `keyword` DTOs) power the new tests (`tests/pipeline_test.cpp`, `tests/keywords.txt`) and demo flows.

### 6\. Interactive CLI Layer (Member B)

- `interface/Menu.hpp` defines a `MenuApp` UI that wires FileReader, Search, Sort, Aggregation, and the functional operations into an evaluator-friendly workflow (load → inspect → search → sort → analyze → transform).
- The main binary now supports dual entry points: `./demo` (scripted showcase using `tests/sample.txt`) and `./demo --menu` (interactive mode).
- Menu actions guard against missing files, print keyword frequency tables, and run transformation pipelines so the full WHAT-first design can be demonstrated live.

-----

## ⚙️ Build and Run Instructions

This project uses `g++` with C++17 standard features.

### Build

Compile all source files and generate executables:

```bash
make
```

### Clean

Remove all compiled object files and executables:

```bash
make clean
```

### Running the Demo

Execute the main demonstration of the framework's capabilities:

```bash
./demo          # scripted showcase using demo_data/*
./demo --menu   # interactive CLI with menu + pipelines
```

The scripted demo now mirrors the assignment’s keyword-frequency use case:

- Reads every `.txt` file inside `demo_data/articles/` and aggregates their tokens.
- Loads keywords from `demo_data/keywords.txt`.
- Prints keyword frequencies in descending order, alongside the search/sort/filter/pipeline walkthrough.

Feel free to drop additional `.txt` files into `demo_data/articles/` or tweak the keyword file—no code changes are required.

-----

## 🧪 Testing

Dedicated test files are available under the `/tests` directory to verify the correctness of each module.

### Running Tests

Run all tests individually to check module functionality:

```bash
# File I/O tests
./file_reader_test

# Search functionality tests
./search_test

# Sorting algorithms tests
./sort_test

# Aggregation functions tests
./aggregation_test

# Functional pipeline & keyword analytics tests
./pipeline_test
```

-----

## 📐 Documentation

The updated UML documentation is split so each member owns a slice:

  * **Member A UML Diagram:** `/docs/UML_MemberA.png`
  * **Member B Functional + UI Slice (Mermaid spec):** `/docs/UML_MemberB.md`
  * **Logs:** `/docs/DEVLOG_MEMBER_A.md`, `/docs/MemberB_Log.md`
  * **Contribution Summaries:** `/docs/Contributions_MemberA.md`, `/docs/MemberB_Contribution.md`

-----

## 🎬 Submission Bundle

The submission bundle includes the following components:

  * **Code:** The complete source code.
  * **README:** This file.
  * **UML:** The project's architecture diagram.
  * **Build Scripts:** The `Makefile`.
  * **Test Outputs:** Output logs demonstrating successful test execution.
  * **Video Demo:** A video demonstration of the project.