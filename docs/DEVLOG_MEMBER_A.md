# **Member A – Development Log**

Member A: ASHMITA DUTTA (2022B1A71372G)

> Template: `YYYY-MM-DD HH:MM (IST) – Action – Notes / Insights / Follow-up`

1. **2025-11-24 08:45 – Specification interpretation**
   - Re-read the POPL brief plus Member B expectations to ensure my work unblocked their functional extensions.
   - Interpreted the mandatory goals as: (a) storage abstraction that can hot-swap implementations, (b) functional algorithms over a unified `List<T>`, (c) clean documentation for handoff.
   - Grey area: the brief never clarified whether cross-file persistence was required. I scoped to in-memory storage only and went ahead with CONTAIN-AND-DELEGATE implementation. 

2. **2025-11-24 09:30 – GenAI architecture sounding board (Cursor GPT-5.1)**
   - Prompt: `"Need to redesign a C++ container suite so Stack/Queue/etc. can swap storage at runtime. Prefer composition over inheritance and must stay move-only. How should I structure interfaces?"`
   - Response (abridged): suggested creating an `IStorage<T>` interface with `clone`, `push`, `pop`, `peek` primitives, then wrapping it in `std::unique_ptr` inside each container; additionally warned about copy-cost when cloning storages.
   - Interpretation: validated my contain-and-delegate instinct while spotlighting ownership semantics. Grey area: the AI skipped exception-safety guidance for `clone`, so I noted to audit destructors manually.
   - Incorporation: implemented `IStorage<T>` with a virtual destructor and pure virtual `clone()` returning `std::unique_ptr<IStorage<T>>`; every container now holds `std::unique_ptr<IStorage<T>> storage`.
   - Fallout: first compile crashed due to missing virtual destructor leading to double-delete; once added, the pattern stabilized and has remained intact.
   - Final insight: composition gave the required flexibility, and the AI suggestion was successfully adopted with added safety auditing.

3. **2025-11-24 11:10 – Storage backend implementation**
   - Authored `VectorStorage`, `LinkedListStorage`, and `HeapStorage` against `IStorage<T>`; each gained move-only semantics plus defensive bounds checks.
   - Manual driver confirmed parity across push/pop/peek operations for mixed data types.
   - Insight: keeping `clone` cheap by leveraging corresponding STL containers avoided premature optimization.
   - Follow-up: documented runtime trade-offs (`VectorStorage` fastest iteration, `HeapStorage` best for priority queue) inside `Contributions_MemberA.md`.

4. **2025-11-24 13:00 – GenAI assist for functional pipeline (OpenAI ChatGPT web)**
   - Prompt: `"Given a templated List<T> over interchangeable storage, outline map/filter/reduce signatures that keep the List move-only but still enable chaining."`
   - Response: recommended returning new `List<T>` values for `map`/`filter`, keeping callables templated, and optionally exposing iterator adaptors to minimize copies.
   - Interpretation: insight aligned with my plan but raised doubts about copying performance; ChatGPT left allocator reuse unexplored (grey area). I treated the copy cost as acceptable for clarity.
   - Incorporation: implemented `map`, `filter`, `reduce`, `inversion_count`, and `average` by converting storage into `std::vector`, performing the operation, then writing back through `storage->clear()` + `storage->push`.
   - Fallout: first `map` draft let lambdas capture dangling references; resolved by emphasizing value captures in docstrings and tests. The feature set has held steady.
   - Final insight: explicit copying plus documentation is better than clever aliasing; the AI input was adopted with caution and succeeded long term.

5. **2025-11-24 15:20 – File reader + search utilities**
   - Built `read_lines`, `read_tokens`, `read_all` to emit `List<std::string>`, then layered linear search, case-sensitive/insensitive substring search, `contains`, and `find_all`.
   - Insight: keeping readers free of algorithm dependencies prevented circular includes.
   - Tests: exercised the pipeline through a temporary CLI harness and later via `tests/aggregation_test.cpp`.

6. **2025-11-24 17:00 – Sorting + aggregation verification**
   - Added extract–sort–write-back helpers with optional comparator plus numeric `average`.
   - Ran `make all` to compile demo/tests, fixing a signed/unsigned comparison warning in the sorting loop.
   - Outcome: confirmed every container/backend combo behaves consistently, giving Member B a stable API surface.

7. **2025-11-24 18:10 – Documentation & UML**
   - Updated README, authored `MemberB_Contribution` handoff notes, produced UML showing `List<T>` delegating to `IStorage<T>`, and finalized this log.
   - Logged manual verification steps and reiterated the in-memory-only assumption for graders.

_End of log._

