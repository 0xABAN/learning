# Software Fundamentals: One-Year Roadmap

Build a connected understanding of software, from programming languages and
computer systems through networking, databases, and applied backend engineering.
Learn C++ throughout, practice interview-style data structures and algorithms,
and maintain a steady web development track.

## Time Commitment

Target at least **3 hours per day**, or **21 hours per week**. That is roughly
1,100 hours over a year. Plan the core curriculum around 900 hours, leaving room
for difficult topics, review, and interruptions.

| Track | Hours per week | Focus |
| --- | --- | --- |
| Systems and software fundamentals | 11 | The current phase, including its exercises, labs, and projects |
| C++ and DSA | 5 | Initially emphasize C++; gradually shift toward algorithmic problem-solving |
| Web development | 4 | Browser fundamentals, then an interface for backend projects |
| Review | 1 | Re-solve older problems and explain concepts without notes |

Use substantial, uninterrupted blocks. There is no need to touch every subject
every day. Project work belongs inside these allocations.

## Sequence

These are emphasis blocks, not strict prerequisites. Build a basic web app early
and revisit it as the underlying systems become clearer. Adjust the pace based
on demonstrated understanding.

| Period | Main focus | Evidence of understanding |
| --- | --- | --- |
| Months 1-2 | C++ foundations, compilation and linking, memory, debugging, basic data structures | Build a small program independently; diagnose memory and lifetime errors with a debugger and sanitizers |
| Months 3-5 | Computer architecture essentials, operating systems, concurrency, networking | Build a small network server; explain what happens from an incoming connection to a response |
| Months 6-8 | Databases and backend engineering | Build a database-backed service; investigate slow queries, concurrent updates, and failed requests |
| Months 9-10 | Programming language concepts and runtime behavior | Implement a small interpreter with a deliberately limited language |
| Months 11-12 | Distributed systems foundations and integration | Extend an existing project and test its behavior under failures and load |

## Months 1-2: C++ and Execution Fundamentals

- Learn the compile-and-link process and how to read compiler diagnostics.
- Understand values, references, pointers, object lifetimes, ownership, and RAII.
- Use standard containers, strings, functions, and classes comfortably.
- Practice debugging, unit testing, and using sanitizers.
- Connect memory layout and basic data structures to program behavior.

Start with small programs that can be explained and debugged independently. The
existing image-processing project can serve as a C++ exercise. Advanced template
techniques and obscure language details can wait.

## Months 3-5: Computer Systems and Networking

- Learn how machine instructions, CPU caches, and memory access affect execution.
- Study processes, threads, virtual memory, system calls, and file I/O.
- Practice synchronization and investigate races and deadlocks.
- Understand sockets, TCP and UDP, DNS, HTTP, and the role of TLS.
- Build a small network server and trace the path from connection to response.

Make the work experimental: predict behavior, run the program, inspect the
result, and investigate discrepancies. Include malformed input, disconnected
clients, and concurrent requests in server exercises.

## Months 6-8: Databases and Backend Engineering

- Learn SQL, relational modeling, indexes, and query plans.
- Understand transactions, isolation, and concurrent updates.
- Design APIs with explicit validation and error behavior.
- Implement authentication and authorization using established libraries.
- Practice integration testing, logging, metrics, and diagnosing failed requests.

Build a database-backed service and connect it to the web development track.
Use a practical backend stack such as Python, FastAPI, and PostgreSQL. Continue
using C++ for systems exercises without requiring every project to use it.

## Months 9-10: Programming Languages

- Study tokenization, parsing, and syntax trees.
- Understand scope, name resolution, types, and evaluation.
- Connect runtime behavior to memory management and execution.
- Implement a small interpreter with a deliberately limited language.

Aim to explain how source text becomes behavior and how language design choices
affect programmers. Keep the language small enough to finish and test thoroughly.

## Months 11-12: Distributed Systems and Integration

- Study replication, consistency, caching, and partial failure.
- Understand timeouts, retries, duplicate requests, and idempotency.
- Extend an existing service with a feature that exercises these concepts.
- Test failures and load; measure latency, throughput, and resource usage.
- Document observed bottlenecks, limitations, and design tradeoffs.

Use measurements and failure experiments to justify changes to the system.

## DSA Throughout the Year

Build a conceptual foundation in complexity, invariants, recursion, and
correctness. Cover arrays and hashing, linked lists, stacks and queues, binary
search, trees, heaps, graphs, greedy algorithms, backtracking, and dynamic
programming.

Study supporting discrete mathematics alongside the problems: logic, induction,
combinatorics, and basic probability. Include this work in the DSA allocation.

Measure progress by whether a solution can be explained, its correctness
justified, its complexity analyzed, and an unfamiliar variation solved. Return
to older problems after time away.

Follow `AGENTS.md` for exercises in this repository: new LeetCode scaffolds use
Python, and existing C++ exercises remain available. Develop C++ fluency through
language drills and systems projects alongside DSA practice.

## Web Development Throughout the Year

Start with HTML, CSS, JavaScript, the DOM, events, forms, HTTP, accessibility, and
browser security. Then add TypeScript and React. Build a basic app early and
gradually connect it to the backend work.

Understand browser behavior before investing heavily in framework-specific
features. Use the browser's developer tools to inspect requests, state, layout,
and errors.

## Learning With LLMs

Attempt the work and explain the core reasoning before asking for a solution.
Use LLMs for hints, counterexamples, quizzes, and critique. After receiving help,
close the conversation and reconstruct the solution later.

During weekly review, check whether the central concepts can be explained without
notes and whether a small related task can be completed independently. Use gaps
to choose the next review exercise.

## Starting Resources

- [LearnCpp](https://www.learncpp.com/): structured C++ study, including compilation, debugging, and language fundamentals.
- [CMU Introduction to Computer Systems](https://www.cs.cmu.edu/~213/): a model for connecting machine code, memory, performance, networking, and concurrency.
- [MIT Introduction to Algorithms](https://www.ocw.mit.edu/courses/6-006-introduction-to-algorithms-spring-2020/pages/syllabus/): algorithmic foundations; check the programming and discrete mathematics prerequisites before starting.
- [MDN Core Learning Modules](https://developer.mozilla.org/en-US/docs/Learn_web_development/Core): browser and web development fundamentals.

Use resources to support the current phase and its exercises. Completing every
listed course in full is not a requirement of this roadmap.

## Year-End Benchmark

Trace a request from the browser through the network, server, and database;
explain the major tradeoffs; and investigate where it goes wrong. Pair that
understanding with independent C++ programming and algorithmic problem-solving.

The goal is a strong, connected foundation across the stack, with practical
evidence of understanding at each layer.
