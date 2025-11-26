# Member B – Development Log

**Member B: Vedashree Mahajan (2022B1A70216G)**

This log documents the complete chronological sequence of design and development actions for Member B's portion of the POPL Endsem assignment. It includes detailed accounts of GenAI assistance, design decisions, implementation challenges, and final insights.

---

## Phase 1: Specification Interpretation & Planning

### 2025-11-25 09:00 IST – Initial Repository Review

**Action:** Cloned the repository and reviewed Member A's completed work.

**Observations:**
- Member A had implemented a complete storage layer (`IStorage<T>`, `VectorStorage`, `LinkedListStorage`, `HeapStorage`)
- Containers (Stack, Queue, Deque, PriorityQueue) were rebuilt using contain-&-delegate pattern
- `List<T>` abstraction was the central interface for all operations
- FileReader, Search, Sort, and Aggregation modules were complete
- Basic map/filter/reduce existed in Aggregation namespace

**Initial Interpretation of Assignment Requirements:**
1. **Functional Programming Layer:** Need to extend beyond basic map/filter/reduce to create composable pipelines
2. **Keyword Frequency Use Case:** The assignment example requires reading tokens, counting keyword frequencies, and outputting sorted results
3. **User Interface:** Need a high-level interface (menu-driven or command-driven) that ties everything together
4. **Integration:** Must demonstrate functional pipelines combining multiple operations

**Grey Areas Identified:**
- How "functional" should the design be? Should I use lambdas extensively or create a more structured API?
- Should the keyword frequency be a standalone function or part of a larger aggregation framework?
- How should the CLI interact with Member A's modules without modifying them?

---

### 2025-11-25 09:15 IST – Reading Assignment PDF & Member A's Documentation

**Action:** Read `PoPL2025EndSemAssignment.pdf` and `DEVLOG_MEMBER_A.md` to understand full scope.

**Key Insights from Assignment:**
- Emphasis on "WHAT-first" functional design over "HOW-first" procedural design
- Example use case: keyword frequency counting across multiple files
- Need for transformation pipelines (map, filter, reduce chains)
- Evaluation criteria includes "functional design at the top level"

**Member A's Architecture Understanding:**
- `List<T>` uses `std::unique_ptr<IStorage<T>>` - this means it's move-only, not copyable
- All operations must work through the `List<T>` interface
- Storage backends are completely abstracted away

**Doubt:** How do I create functional pipelines if `List<T>` can't be copied? Need to understand move semantics better.

---

## Phase 2: Design Consultation & Initial Planning

### 2025-11-25 09:30 IST – First GenAI Consultation: Functional Pipeline Design

**Prompt Used:**
```
I'm working on a C++ functional programming layer. I have a List<T> class that uses unique_ptr internally, so it's move-only (not copyable). I need to create a fluent pipeline API like:

tokens.filter(pred).map(func).take(n)

But each operation needs to return a new List, and I can't copy. How should I design this?
```

**Response Obtained:**
The AI suggested:
1. Use `clone()` method if available (which List<T> has)
2. Design Pipeline<T> as a wrapper that holds a List<T> by value
3. Each pipeline operation should clone the internal list, apply transformation, and return a new Pipeline
4. Use move semantics throughout to avoid copies

**My Interpretation:**
- The `clone()` method in `List<T>` creates a new List with VectorStorage by default
- Pipeline wrapper makes sense - it encapsulates the "current state" of transformation
- Each operation returns a new Pipeline, maintaining immutability

**Doubt:** Will cloning be expensive? Should I worry about performance?

**Decision:** Proceed with Pipeline wrapper approach. Performance can be optimized later if needed, but correctness and functional style are priority.

**Incorporation Method:**
- Started designing `Pipeline<T>` class structure
- Planned to use `List<T>::clone()` for each transformation step
- Would wrap Member A's Aggregation functions

---

### 2025-11-25 09:45 IST – Second GenAI Consultation: Keyword Frequency Algorithm

**Prompt Used:**
```
I need to implement keyword frequency counting in C++. Given:
- A list of tokens (strings) from files
- A list of keywords to search for
- Need case-insensitive matching
- Output should be sorted by frequency (descending), then alphabetically

What's the best approach? Should I use unordered_map? How do I handle case-insensitivity?
```

**Response Obtained:**
The AI suggested:
1. Use `std::unordered_map<std::string, size_t>` for O(1) lookups
2. Normalize both keywords and tokens to lowercase for case-insensitive matching
3. Store original keyword case for output
4. Use a struct to pair keyword with count
5. Sort using custom comparator

**My Interpretation:**
- Map-based approach is efficient
- Need to preserve original keyword case in output (assignment example shows this)
- Should create a `KeywordFrequency` struct for better type safety
- Can reuse Member A's `Search::to_lower()` helper

**Insight:** This fits perfectly with functional design - it's a pure transformation: tokens + keywords → frequency pairs → sorted list

**Incorporation Method:**
- Designed `KeywordFrequency` struct with `keyword` and `count` fields
- Planned to use `Search::to_lower()` for normalization
- Would return `List<KeywordFrequency>` sorted by Member A's Sort module

---

### 2025-11-25 10:00 IST – Third GenAI Consultation: CLI Design Pattern

**Prompt Used:**
```
I need to design a menu-driven CLI in C++ that:
- Loads files using existing FileReader class
- Calls Search, Sort, Aggregation functions
- Shows keyword frequency results
- Demonstrates functional pipelines
- Should be optional (not break existing demo)

What's a clean way to structure this? Should it be a class? How do I handle user input validation?
```

**Response Obtained:**
The AI suggested:
1. Create a `MenuApp` class with state (loaded tokens, keywords)
2. Use a loop with switch statement for menu options
3. Validate file loading before operations
4. Use `argc/argv` in main to choose between scripted demo and interactive menu
5. Keep menu code in separate header (`interface/Menu.hpp`)

**My Interpretation:**
- Class-based approach keeps state organized
- Need to track whether tokens/keywords are loaded
- Should provide clear error messages
- Main function should support `--menu` flag

**Doubt:** Should the menu be in a separate namespace or class? Class seems better for state management.

**Decision:** Use `MenuApp` class with inline implementations in header (following Member A's style in FileReader).

---

## Phase 3: Implementation

### 2025-11-25 10:15 IST – Starting FunctionalOps Implementation

**Action:** Created `core/FunctionalOps.hpp` with initial structure.

**First Challenge:** Template return type deduction for `map` function.

**GenAI Prompt:**
```
In C++, I'm writing a map function that takes List<T> and Func, returns List<U> where U is the return type of Func. How do I declare the return type using decltype?
```

**Response:**
```cpp
template <typename T, typename Func>
auto map(const List<T>& list, Func func)
    -> List<decltype(func(list.at(0)))>
```

**Problem Encountered:** This doesn't work if list is empty. Also, `decltype(func(list.at(0)))` might include references.

**Second GenAI Prompt:**
```
The decltype approach fails for empty lists. Also I need to remove references. How do I handle this?
```

**Response:**
```cpp
template <typename T, typename Func>
auto map(const List<T>& list, Func func)
    -> List<std::decay_t<decltype(func(std::declval<T>()))>>
```

**My Interpretation:**
- `std::declval<T>()` creates a fake value for type deduction without needing actual list element
- `std::decay_t` removes references and cv-qualifiers
- This is safer and more correct

**Incorporation:** Used this pattern for all template functions that transform types.

**Success:** This approach worked and is more robust than the initial attempt.

---

### 2025-11-25 10:30 IST – Implementing Pipeline Class

**Action:** Started implementing `Pipeline<T>` wrapper class.

**Challenge:** How to handle move semantics correctly.

**GenAI Prompt:**
```
I have a Pipeline<T> class that holds List<T> data. The constructor takes List<T> by value. But List<T> is move-only. How should I design the constructor and methods?
```

**Response:**
- Constructor should take `List<T>&&` (rvalue reference)
- Methods that return new Pipeline should move the result
- `collect()` should clone to return a new List

**Implementation Attempt:**
```cpp
explicit Pipeline(List<T> initial) : data(std::move(initial)) {}
```

**Compilation Error:** `List<T>` copy constructor is deleted.

**Fix:** Changed to `List<T>&&`:
```cpp
explicit Pipeline(List<T>&& initial) : data(std::move(initial)) {}
```

**Success:** This resolved the compilation error. Learned that move-only types require rvalue references in constructors.

---

### 2025-11-25 10:45 IST – Pipeline Method Implementation

**Action:** Implementing `map`, `filter`, `sort` methods for Pipeline.

**Challenge:** `map` changes the type from `T` to `U`. How to return `Pipeline<U>`?

**GenAI Prompt:**
```
My Pipeline<T>::map() method needs to return Pipeline<U> where U is the return type of the function. How do I declare this in the method signature?
```

**Response:**
```cpp
template <typename Func>
auto map(Func func) const
    -> Pipeline<std::decay_t<decltype(func(std::declval<T>()))>>
{
    using U = std::decay_t<decltype(func(std::declval<T>()))>;
    auto mapped = FunctionalOps::map(data, func);
    return Pipeline<U>(std::move(mapped));
}
```

**My Interpretation:**
- Need to extract `U` type alias for readability
- Call the standalone `map` function
- Move the result into new Pipeline

**Implementation:** Used this pattern. It compiled successfully.

**Insight:** Template metaprogramming for type deduction is powerful but requires careful syntax.

---

### 2025-11-25 11:00 IST – Implementing Helper Functions (take, drop, distinct)

**Action:** Added utility functions to FunctionalOps namespace.

**Design Decision:** These should work on `List<T>` directly, not require Pipeline. Pipeline can wrap them.

**Implementation Notes:**
- `take(n)`: Simple loop up to min(n, size)
- `drop(n)`: Loop from index n to end
- `distinct`: Used `std::unordered_set` to track seen elements

**No GenAI needed:** These were straightforward implementations.

**Success:** All helper functions worked as expected.

---

### 2025-11-25 11:15 IST – Implementing keyword_frequencies Function

**Action:** Implementing the core keyword frequency counting function.

**Design:**
1. Normalize keywords and create map with zero counts
2. Iterate through tokens, increment counts for matches
3. Convert map to List<KeywordFrequency>
4. Sort by count (desc), then keyword (asc)

**Challenge:** How to handle case sensitivity parameter elegantly.

**Solution:** Used a lambda that conditionally normalizes:
```cpp
auto normalize = [&](const std::string& value) {
    return case_sensitive ? value : Search::to_lower(value);
};
```

**Implementation Success:** Function worked correctly on first test with sample data.

**Insight:** Lambda captures make conditional logic clean and readable.

---

### 2025-11-25 11:30 IST – Creating Menu Interface

**Action:** Started implementing `interface/Menu.hpp`.

**Structure Decision:**
- `MenuApp` class with `run()` public method
- Private state: `tokens`, `keywords`, boolean flags for loaded state
- Private methods for each menu option

**Challenge:** Input validation and error handling.

**GenAI Prompt:**
```
In C++, how do I safely read an integer from cin and handle invalid input (like when user types a string)?
```

**Response:**
```cpp
int choice = -1;
std::cin >> choice;
if (!std::cin.good()) {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return -1; // invalid
}
return choice;
```

**My Interpretation:**
- `std::cin.good()` checks if read was successful
- `clear()` resets error flags
- `ignore()` discards remaining input
- Return sentinel value for invalid input

**Incorporation:** Used this pattern in `read_choice()` method.

**Success:** Menu handled invalid input gracefully.

---

### 2025-11-25 11:45 IST – Implementing Menu Operations

**Action:** Implementing each menu option method.

**Key Methods:**
- `load_tokens()`: Uses `FileReader::read_tokens()`
- `load_keywords()`: Same, stores in keywords list
- `display_tokens()`: Shows preview (first 20)
- `search_keyword()`: Uses `Search::search_substring_ci()`
- `sort_tokens()`: Uses `Sort::sort_list()` (modifies in place)
- `show_keyword_frequency()`: Uses `FunctionalOps::keyword_frequencies()`
- `run_transform_pipeline()`: Demonstrates Pipeline API

**Challenge:** `sort_tokens()` modifies the list. Is this okay?

**Decision:** Yes, it's acceptable. The menu is interactive and user expects tokens to be sorted after choosing option 5. We're not breaking functional principles at the application level.

**Success:** All menu operations implemented and tested manually.

---

### 2025-11-25 12:00 IST – Updating main.cpp

**Action:** Modifying main.cpp to support both scripted demo and menu mode.

**Design:**
- Default: Run scripted demo (preserves Member A's original behavior)
- `--menu` flag: Launch interactive menu

**Implementation:**
```cpp
int main(int argc, char* argv[]) {
    if (argc > 1 && std::string(argv[1]) == "--menu") {
        MenuApp app;
        app.run();
        return 0;
    }
    // ... scripted demo ...
}
```

**Success:** Both modes worked correctly.

---

### 2025-11-25 12:15 IST – Creating Pipeline Test

**Action:** Writing `tests/pipeline_test.cpp` to verify functional operations.

**Test Cases:**
1. Basic map operation
2. Filter + map chain
3. Pipeline take/drop
4. Collect final result

**Challenge:** How to test Pipeline without making test too complex?

**Solution:** Test simple transformations and verify output size and content.

**GenAI Prompt (minor):**
```
What's a good way to test a functional pipeline in C++? Should I use assertions or just print and verify manually?
```

**Response:** Use assertions for automated testing, but also print for manual verification during development.

**My Approach:** Used assertions for critical checks, kept print statements for debugging.

**Success:** Test passed on first run.

---

### 2025-11-25 12:30 IST – Build System Integration

**Action:** Updating Makefile to include new test and ensure demo builds.

**Changes:**
- Added `pipeline_test` target
- Ensured `demo` target includes new headers

**Compilation Error:** Pipeline test failed to compile - move semantics issue.

**Error Message:**
```
error: call to implicitly-deleted copy constructor of 'List<string>'
```

**GenAI Prompt:**
```
I'm getting a copy constructor error with my Pipeline class. The constructor takes List<T>&& but I'm calling it with a temporary. What's wrong?
```

**Response:** The issue was in the `from()` helper function. Need to ensure it takes rvalue reference or clones properly.

**Fix:** Created two `from()` overloads:
```cpp
template <typename T>
Pipeline<T> from(List<T>&& list) {
    return Pipeline<T>(std::move(list));
}

template <typename T>
Pipeline<T> from(const List<T>& list) {
    auto cloned = list.clone();
    return Pipeline<T>(std::move(cloned));
}
```

**Success:** This resolved the compilation error. Learned that helper functions need to handle both const reference and rvalue cases.

---

### 2025-11-25 12:45 IST – Running Full Test Suite

**Action:** Executing all tests to verify integration.

**Results:**
- `file_reader_test`: ✅ Passed
- `search_test`: ✅ Passed
- `sort_test`: ✅ Passed
- `aggregation_test`: ✅ Passed
- `pipeline_test`: ✅ Passed (after fixing move semantics)
- `demo`: ✅ Ran successfully

**Insight:** Systematic testing caught the move semantics issue early. Good practice to test incrementally.

---

## Phase 4: Documentation & Finalization

### 2025-11-25 13:00 IST – Updating README

**Action:** Adding Member B's contributions to README.

**Sections Added:**
- Functional Programming Layer description
- CLI interface usage
- New test instructions
- Build/run commands

**Approach:** Kept it concise but informative, matching Member A's style.

---

### 2025-11-25 13:15 IST – Creating Contribution Document

**Action:** Writing `MemberB_Contribution.md`.

**Content:**
- Overview of work scope
- Detailed breakdown of each deliverable
- Constraints (no modification of Member A's code)
- Next steps (UML export)

**Style:** Narrative format explaining the journey from Member A's foundation to complete system.

---

### 2025-11-25 13:30 IST – Creating UML Diagram (Mermaid)

**Action:** Designing UML representation of functional layer.

**GenAI Prompt:**
```
I need to create a UML class diagram in Mermaid syntax showing:
- FunctionalOps namespace with Pipeline<T> class
- KeywordFrequency struct
- MenuApp class
- How they use List<T> and Member A's modules

Can you help with the syntax?
```

**Response:** Provided Mermaid class diagram syntax with:
- Namespace representation
- Class relationships (uses, depends on)
- Template class notation

**My Interpretation:**
- Focused on Member B's additions
- Showed dependencies on Member A's modules
- Used composition arrows (-->) to show "uses" relationships

**Result:** Created `docs/UML_MemberB.md` with Mermaid diagram.

**Note:** Will export to PNG using Lucidchart for final submission.

---

### 2025-11-25 13:45 IST – Writing This Development Log

**Action:** Documenting the complete development process.

**Approach:**
- Chronological sequence with timestamps
- Detailed GenAI interactions with prompts and responses
- Interpretation, doubts, and decisions at each step
- Success/failure outcomes
- Final insights

**Purpose:** Provide transparency on development process, GenAI usage, and learning outcomes as required by assignment.

---

## Final Insights & Reflections

### 2025-11-25 14:00 IST – Final Review & Insights

**Key Learnings:**

1. **Move Semantics Mastery:**
   - Move-only types (like `List<T>` with `unique_ptr`) require careful handling
   - Rvalue references (`&&`) are essential for constructors and function parameters
   - Helper functions need overloads for both const reference and rvalue cases
   - **Final Insight:** Understanding move semantics is crucial for modern C++ functional-style programming. The compiler errors were actually helpful in learning the correct patterns.

2. **Template Metaprogramming:**
   - `std::declval<T>()` is powerful for type deduction without instantiation
   - `std::decay_t` removes references and cv-qualifiers, essential for clean type extraction
   - Type aliases (`using U = ...`) improve readability in complex template code
   - **Final Insight:** Template metaprogramming enables expressive APIs but requires careful attention to syntax. The GenAI helped with correct patterns, but understanding *why* they work was crucial.

3. **Functional Design in C++:**
   - Pipeline pattern provides fluent API while maintaining immutability (via cloning)
   - Wrapper classes can encapsulate state and provide clean interfaces
   - Lambda functions enable "WHAT-first" thinking - specify transformation, not implementation
   - **Final Insight:** Functional programming in C++ is about patterns and discipline, not language features. The Pipeline wrapper makes functional style accessible even with move-only types.

4. **Integration Without Modification:**
   - Member A's modules were well-designed with clear interfaces
   - Composition over inheritance made extension straightforward
   - No need to modify existing code - everything composes cleanly
   - **Final Insight:** Good architecture (contain-&-delegate) enables independent development. Member A's foundation was solid, making my work easier.

5. **GenAI as a Learning Tool:**
   - GenAI was most helpful for:
     - Syntax questions (template declarations, move semantics)
     - Design pattern suggestions (Pipeline wrapper, input validation)
     - Debugging specific compiler errors
   - GenAI was less helpful for:
     - Understanding *why* certain patterns work
     - Making architectural decisions (those required my judgment)
     - Writing the actual business logic (I wrote all functional code)
   - **Final Insight:** GenAI accelerates development but doesn't replace understanding. Every suggestion was verified, tested, and understood before incorporation. The prompts evolved as I learned - early prompts were vague, later ones were specific and targeted.

**Success Metrics:**
- ✅ All tests pass
- ✅ Demo runs in both scripted and interactive modes
- ✅ Keyword frequency use case works end-to-end
- ✅ Functional pipelines demonstrate "WHAT-first" design
- ✅ Documentation complete
- ✅ No modifications to Member A's code

**Remaining Work:**
- Export UML diagram from Lucidchart to PNG
- Record demo video
- Final submission bundle preparation

---

## Summary of GenAI Usage

**Total GenAI Consultations:** ~8-10 interactions

**Categories:**
1. **Design Patterns (3):** Pipeline wrapper, keyword frequency algorithm, CLI structure
2. **Syntax/Compilation (4):** Template return types, move semantics, input validation, helper function overloads
3. **Testing (1):** Test structure recommendations
4. **Documentation (1):** Mermaid UML syntax

**Pattern of Usage:**
- Started with high-level design questions
- Moved to specific syntax issues as implementation progressed
- Used for debugging compiler errors
- Final consultation for documentation format

**Key Principle:** Every GenAI suggestion was:
1. Understood (not blindly copied)
2. Tested (compiled and verified)
3. Adapted (modified to fit our architecture)
4. Documented (included in this log)

**Final Assessment:** GenAI was a valuable tool for accelerating development, especially for C++ template and move semantics syntax. However, all design decisions, architectural choices, and actual implementation logic came from understanding the assignment requirements and Member A's foundation. The GenAI helped with "how to express X in C++" but not "what should X be."

---

**End of Development Log**

