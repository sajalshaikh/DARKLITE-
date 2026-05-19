# CyberCore-CLI: A Modular Cybersecurity Simulation Toolkit

**CyberCore-CLI** is an interactive, lightweight command-line interface (CLI) cybersecurity simulation engine built natively in C++. Developed as an educational sandbox application, it translates abstract security vectors and threat methodologies into a controlled, tangible local software terminal. 

The framework demonstrates core programming architectures—including procedural modular design, fixed-size contiguous data matrix tracking, input buffer stream protection, and persistent file I/O operations—to accurately model real-world defensive and offensive logic blocks.

---

## 🛠️ System Architecture & Core Modules

The toolkit features an entry-point orchestrator that guides users through a clean, menu-driven command interface across six isolated execution layers:

1. **Entropy-Driven Password Generator**
   * Dynamically aggregates user-configured character pools (uppercase, lowercase, base-10 digits, and special ASCII characters).
   * Generates unpredictable string sequences using current system clock indices (`srand(time(0))`) to prevent token predictability.
   * Directs structural credential generations permanently onto disk storage inside `passwords.txt`.

2. **Stateful Intrusion Access Portal (Brute Force)**
   * Simulates a secure administrative authentication gateway interface.
   * Tracks user interaction states across an explicit loop threshold, locking down the terminal window after three consecutive failed attempts.
   * Records unauthorized intrusion attempt alerts cleanly to `brute_force_results.txt`.

3. **Heuristic Phishing Vector Scanner**
   * Implements a swift pattern-matching loop using standard string library diagnostics (`std::string::find`).
   * Audits user-provided domain URLs against a static string array mapping out high-probability target keywords (`login`, `verify`, `bank`, `secure`, etc.).
   * Warns the console user upon threat identification and appends intercepted metrics to `phishing_results.txt`.

4. **Network Port Scan Monitor**
   * Maps out simulated local network socket sweeps across an administrative range ($1 \le n \le 100$).
   * Explicitly flags common accessible ports (SSH `22`, HTTP `80`, HTTPS `443`) to show exposure risks.
   * Monitors telemetry activity thresholds, logging bulk scans that exceed acceptable baselines to `port_scan_results.txt`.

5. **Signature-Based Traffic Firewall**
   * Evaluates plain-text packet simulation input strings via conditional branching pipelines.
   * Drops adversarial payloads matching malicious traffic patterns (`malware`, `exploit`, `hack`).
   * Commits filtered networking decision logs directly to `firewall_results.txt`.

6. **Centralized Runtime Metrics Dashboard**
   * Consolidates diagnostic application metrics tracking overall session runtime actions.
   * Pulls and prints human-readable structural alert events gathered inside an in-memory array data matrix (`struct Alert`).

---

## 💻 Core Technical Concepts Demonstrated

* **Data Modeling (`struct`):** Bundles complex threat telemetry properties heterogeneously to standardize alert history reporting.
* **Persistent I/O Operations (`<fstream>`):** Implements transaction-safe local database logging by piping strings into append-mode (`ios::app`) streams.
* **Stream Buffer Sanitization (`<limits>`):** Protects the processing loop against toxic input format exploits by programmatically clearing stream error flags (`cin.clear()`) and flushing hardware buffers.
* **Randomness Seeding (`<cstdlib>`, `<ctime>`):** Minimizes generation predictability by mapping pseudorandom calculations relative to real-time Unix Epoch calendar values.

---

## 🚀 How to Run the Project Locally

### Technical Requirements
* A standard-compliant C++ compiler (GCC `g++`, Clang, or MSVC) or any integrated compiler environment (e.g., JDoodle).

### Compilation & Build
Compile the application binary image directly from your terminal container using the strict standard execution flag:

```bash
g++ -std=c++11 ProgrammingFundamentalsProject.cpp -o cybercore_toolkit
