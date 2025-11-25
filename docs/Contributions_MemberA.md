# 🧑‍💻 Member A Contribution Summary (Ashmita Dutta - lanascript)

I was responsible for the **entire architectural redesign** of the container framework and the implementation of all core functional modules, laying the foundation for the project's success.

---

## 1. 🏗️ Architectural Redesign: Contain-&-Delegate

My primary contribution was moving the system away from limiting inheritance-based storage to a **Contain-and-Delegate (Composition)** architecture.

* **Recognition:** Identified that inheritance coupled container behavior tightly to specific storage implementations, limiting flexibility.
* **Solution:** Rebuilt the system so that top-level containers (`List<T>`, `Stack<T>`, etc.) depend only on the **`IStorage<T>` abstraction**, enabling storage backends to be seamlessly interchanged.


---

## 2. 💾 Storage Layer Implementation

Implemented the entire storage foundation required by the new composition architecture:

* `IStorage<T>` (The pure virtual interface).
* `VectorStorage<T>` (Dynamic array backend).
* `LinkedListStorage<T>` (Doubly-linked list backend).
* `HeapStorage<T>` (Min/Max heap backend).

---

## 3. 📦 Container Layer Implementation

Implemented all required standard container types using the new `IStorage<T>` abstraction:

* `Stack<T>`
* `Queue<T>`
* `Deque<T>`
* `PriorityQueue<T>`

---

## 4. 🗃️ List Abstraction (`List<T>`)

* Implemented the **unified `List<T>` interface** over `IStorage<T>`, providing essential operations (`push/pop`, `front/back`, `at`, `clone`, `append`).
* This abstraction ensures all higher-level functional modules (Search, Sort, Aggregate) are **backend-independent**.

---

## 5. 📂 Functional Modules Implementation

Implemented the entire suite of high-level functional utility modules:

### File Reader Module
* `read_tokens(path)`
* `read_lines(path)`
* `read_all(path)`

### Searching Module
* `linear_search`
* `contains`
* `find_all` (indices)
* `substring_search` and Case-Insensitive (CI) substring search

### Sorting Module
* Default `std::sort`-based sort
* Custom comparator sort
* Stable sort

### Aggregation Module
* `inversion_count`
* `average` (for numeric lists)
* `map`
* `filter`
* `reduce`

---

## 6. 🧪 Testing, Build, and Documentation

* **Testing:** Created dedicated test files for every implemented module (File Reader, Search, Sort, Aggregation).
* **Makefile:** Constructed the primary `Makefile` for automated compilation, cleaning, and test execution.
* **Documentation:** Authored the Design Log, the main `README.md` with my half of the contributions, and updated the UML diagram to reflect the final architecture.