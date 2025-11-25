# Member B – Development Log

> Template: `YYYY-MM-DD HH:MM (IST) – Action – Notes / Insights / Follow-up`

1. **2025-11-25 09:05 – Repository intake**
   - Synced with `main`, read PoPL brief plus Member A docs (`DEVLOG_MEMBER_A.md`, UML).
   - Captured scope: functional workflows, keyword analytics, CLI, documentation.

2. **2025-11-25 09:35 – Functional design consultation (Cursor GPT-5.1)**
   - Prompted for ways to wrap existing `List<T>` in fluent pipelines without touching storage backends.
   - Adopted idea of a `Pipeline<T>` wrapper returning clones to respect unique storage ownership.

3. **2025-11-25 10:10 – Implemented `core/FunctionalOps.hpp`**
   - Added HOF helpers, pipeline abstraction, keyword frequency aggregator, and printable DTOs.
   - Insight: `List<T>` is move-only; clones are mandatory when sharing data across stages.

4. **2025-11-25 11:00 – Built CLI (`interface/Menu.hpp`)**
   - Designed menu flow, input guards, and transformation demos highlighting the pipeline API.
   - Ensured CLI is optional (`./demo --menu`) so scripted demo still works for graders.

5. **2025-11-25 11:45 – Demo + tests + docs**
   - Extended `main.cpp`, created `tests/pipeline_test.cpp`, wired new target into `Makefile`.
   - Authored README updates, contribution summary, Mermaid UML stub.

6. **2025-11-25 12:15 – Verification & cleanup**
   - Ran `make` (tests, demo) locally, documented manual test steps.
   - Prepared deliverables (`MemberB_Contribution.md`, this log) for submission bundle.

_End of log._

