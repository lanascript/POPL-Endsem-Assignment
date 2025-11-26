# Member B – Contribution Summary

## Overview

Once Member A finished the storage + container overhaul, I was responsible for everything that lives “above” the list abstraction: functional utilities, keyword-driven analytics, an interactive CLI, and the documentation/reporting trail. I spent the first session reading the PoPL brief, replaying Member A’s demos, and deciding how to expose the WHAT-first workflows their code enabled. The rest of my time went into `core/FunctionalOps.hpp`, the menu interface, the augmented demo/tests, and the supporting docs/logs so our submission covers design, execution, and evidence end-to-end.

## Code Deliverables

1. **Functional Programming Layer (`core/FunctionalOps.hpp`)**
   - Started by mapping Member A’s Aggregation helpers into a richer toolkit: `map`, `filter`, `fold_left`, `take`, `drop`, `distinct`, and `sorted`.
   - Added a `Pipeline<T>` wrapper so we can express “WHAT-first” flows like `tokens → filter(len>3) → map(uppercase) → take(10)` without mutating the original list (clones preserve storage invariants).
   - Built `KeywordFrequency` structs and the `keyword_frequencies(...)` routine to satisfy the assignment’s keyword-counting scenario using the new pipeline primitives.

2. **User-Facing Interface (`interface/Menu.hpp`)**
   - Once the functional blocks were in place, I layered a menu-driven CLI that stitches together FileReader, Search, Sort, Aggregation, and the new FunctionalOps utilities.
   - The CLI mirrors the brief’s use case: load data, preview tokens, run case-insensitive search, sort them, build a keyword frequency table, and showcase a transformation pipeline.
   - To respect Member A’s scripted demo, the main binary now offers both modes: `./demo` replays the automatic showcase, while `./demo --menu` hands control to evaluators.

3. **Demo & Tests**
   - Updated `main.cpp` so the default run still reads `tests/sample.txt`, but now shows the keyword frequency table and points to the CLI via `--menu`.
   - Added `tests/pipeline_test.cpp` (plus `tests/keywords.txt`) to assert the map/filter chains and keyword aggregation don’t regress; registered the target in the Makefile.

4. **Documentation & Logs**
   - Reworked `README_unfinished.md` with the new build/run/test instructions and pointers to the CLI/pipeline sections.
   - Documented my process in `MemberB_Log.md` and wrapped it up here so the division of work is explicit.
   - Sketched the functional/UI slice in Mermaid and mirrored it in Lucidchart, ready to export as PNG alongside Member A’s diagram.

## Constraints & Agreements

- No changes were made to storage backends, container implementations, or Member A’s documentation/tests; all extensions compose via `List<T>`.
