# **Member A Development Log**

Member A: ASHMITA DUTTA (2022B1A71372G)

This log captures how I approached and completed the Member A portion of the POPL Endsem assignment. It is written as a natural progression documenting the key development phases and design decisions. Limited use of an LLM was made for brainstorming design alternatives and generating boilerplate templates, but every implementation decision, debugging step, and architectural redesign was consciously verified and written by me.

---

## **Understanding the Problem & Architectural Redesign**

I revisited the assignment specification and compared it with my previous design using LISTS AND THE BASE CLASS USAGE. It became clear that the inheritance-based model I used earlier would not satisfy the Functional–OO goals or the flexibility expected.  
I switched to a contain-&-delegate (composition) architecture and defined `IStorage<T>` as the foundational abstraction for all storage backends. This redesign became the backbone of the entire project.

---

## **Implementing the Storage Layer**

I implemented three interchangeable storage backends:

* `VectorStorage<T>`  
* `LinkedListStorage<T>`  
* `HeapStorage<T>`

Each conforms to `IStorage<T>`, ensuring consistent behavior while retaining internal freedom. This layer provides the modularity the assignment emphasizes.

---

## **Rewriting the Containers (Contain-&-Delegate)**

I rebuilt all major containers—Stack, Queue, Deque, PriorityQueue—using:

`std::unique_ptr<IStorage<T>> storage;`

This removed the rigid inheritance from earlier implementations and allowed each container to work with any storage type. I manually tested each to confirm that delegation worked as expected.

---

## **Building the Unified List\<T\> Abstraction**

I implemented the `List<T>` abstraction to act as the functional interface.  
It provides push/pop/access operations while remaining independent of storage.  
This class became the basis for searching, sorting, mapping, filtering, and aggregation.

---

## **File Reader Module**

I implemented file-reading utilities (`read_lines`, `read_tokens`, `read_all`) to convert file data into `List<std::string>`.  
This enables all downstream functionality such as keyword search and token processing.

---

## **Searching Utilities**

I added the first set of higher-level list algorithms:

* linear search  
* contains  
* find\_all  
* substring search (case-sensitive and case-insensitive)

These form the “read → search → analyze” pipeline required by the assignment.

---

## 

## 

## **Sorting Module**

I implemented sorting using a simple extract–sort–write-back approach.  
Both default and custom comparator-based sorting were added.  
This ensured correctness and backend independence.

---

## **Aggregation Functions**

To support the functional programming requirements, I implemented:

* inversion count  
* average (for numeric lists)  
* map  
* filter  
* reduce

These are foundational building blocks for the functional layer Member B will extend.

---

## **Testing & Build System**

I created clean test files for each module and a Makefile to compile and run them with a single command.  
This improved demonstrability and aligns with the assignment’s emphasis on ease of evaluation.

---

## **Documentation & UML**

Finally, I wrote the Member A contribution document, prepared a UML diagram reflecting the redesigned architecture, and organized the repository for clarity.  
These steps ensure that the overall system is understandable, modular, and easy for instructors to examine.

---

**In summary, this log reflects the complete trajectory of my work—from architectural redesign to implementing each component, verifying them through tests, and documenting the final system.** 