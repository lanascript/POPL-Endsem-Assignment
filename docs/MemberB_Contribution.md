# Member B – Contribution Summary

## Overview

Member B focused on the “WHAT-first” functional workflows, application-level orchestration, and evaluator-facing assets demanded by the [assignment brief](file:///Users/apple/POPL-Endsem-Assignment/PoPL2025EndSemAssignment.pdf). The work complements Member A’s storage/container foundation without modifying their codepaths.

## Code Deliverables

1. **Functional Programming Layer (`core/FunctionalOps.hpp`)**
   - Introduced generic higher-order helpers (`map`, `filter`, `fold_left`, `take`, `drop`, `distinct`, `sorted`).
   - Added a composable `Pipeline<T>` abstraction with fluent APIs for map/filter/sort/take/drop/tap/fold chains.
   - Delivered `KeywordFrequency` data objects plus `keyword_frequencies` analytics required by the “keyword count” use-case.

2. **User-Facing Interface (`interface/Menu.hpp`)**
   - Menu-driven CLI that loads tokens/keywords, runs searches, sorts, frequency tables, and transformation demos.
   - Dual-mode entry point: default scripted showcase (`./demo`) vs. interactive menu (`./demo --menu`).

3. **Demo & Tests**
   - Upgraded `main.cpp` to showcase both scripted pipelines and the new CLI.
   - Added `tests/pipeline_test.cpp` plus `tests/keywords.txt` to verify keyword analytics and pipeline behavior.

4. **Documentation**
   - Updated `README_unfinished.md` with instructions for the new interfaces/tests.
   - Authored this contribution summary, `MemberB_Log.md`, and a Mermaid-based UML slice (`UML_MemberB.md`).

## Constraints & Agreements

- Member B did **not** alter storage backends, container implementations, or Member A’s logs/tests, honoring the agreed team split.
- All new functionality layers purely on top of the existing `List<T>` abstraction via composition.

## Next Steps

- Extend the CLI with scripted batch modes for auto-grading if needed.
- Export `UML_MemberB.md` into a PNG to keep visual artifacts consistent with Member A’s assets.

