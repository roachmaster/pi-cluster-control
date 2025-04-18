Binary Log Update — The Birth of Forge

What is Forge, and how can I put it into my own words?

Forge started as a dream — a pipe dream of mine.
I wanted to create a portable cloud system using a cluster of Raspberry Pi 4s I collected during the COVID era.
At that time, silicon was rare — supply chains froze, and the world nearly shut down for two years.

I would stalk MicroCenter, waiting for shipments.
Every chance I got, I would buy a Pi 4 along with a matching PoE hat.
Eventually, I had enough to successfully deploy Docker containers and even Kubernetes (K3s) across the cluster.

Many of my early projects started with huge hopes… but the flames of my desire to write the software would die out.
If it weren’t for the AI revolution, Forge might have never been born.

AI changed everything.
It helped me accelerate what I already knew — stitching my understanding of algorithms and data structures together into real systems.
In the past, researching my crazy ideas was painfully slow:
•	Searching through endless links
•	Finding only academic, theoretical papers
•	No real-world examples, just abstract models

But with AI today, I can quickly gather information, cross-pollinate disciplines, and build.

When I started working on the Raspberry Pi cluster, I envisioned something like AWS, but tailored for home labs:
•	Simpler
•	More specialized
•	Faster (especially for low-powered Pis)

I decided to use C++ and Bash to achieve this vision.

However, as I began, I realized that managing CMake files manually was tedious and unsustainable.
I knew from my experience with Gradle and Maven that centralized project manifests were a good practice (like build.gradle or pom.xml).

Thus, I decided to create a consolidated metadata file — a manifest for the entire project.

I chose YAML as the format:
•	XML was too verbose.
•	JSON was less verbose but still heavy mentally.
•	YAML (like Docker, Kubernetes, Swagger) was clean and expressive.

At first, the modules.yaml file was simple: a list of modules I wanted to create.
But over time, the schema evolved:
•	Each module entry began tracking packages, test packages, dependencies, etc.
•	The list grew large — fast.
•	Manual work became unsustainable.

I knew I needed automation.

Thus, I wrote a bootstrap.sh script:
•	Detects system packages (C++, CMake, Mustache, etc.)
•	Verifies base tools are installed
•	Ensures every machine I work on (laptop, workstation, server) could quickly become Forge-ready.

Later, I realized each module might have its own packages too.
Thus, the modules.yaml evolved again — adding per-module package management.

With AI’s help, writing the bootstrap script was quick.
But maintainability was a problem:
•	Early AI-generated scripts were good for MVPs but terrible for long-term maintenance.

So I started modularizing even the scripts:
•	Environment detection functions
•	Download and install functions
•	Package verification separated cleanly

Once that was stable, I moved on to writing a scaffold script:
•	Creates modules automatically
•	Populates directories
•	Generates starter files from templates

Again, early versions worked… but weren’t built for long-term clarity.

Luckily, my experience at Raytheon’s Framework Modernization Team paid off:
•	I had worked on auto-generating API clients (from Swagger/OpenAPI specs).
•	I had learned how to cleanly separate templates, rendering, and generation logic.

That experience deeply influenced how I restructured Forge’s scaffolding system — and built it for maintainability, scalability, and clarity.
