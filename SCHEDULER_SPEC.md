# SCHEDULER_SPEC.md

Version: 1.0

Status: Core Standard

---

# Goals

Low latency.

High throughput.

Fairness.

Realtime support.

Accelerator awareness.

---

# Scheduling Classes

Interactive

Realtime

Batch

Background

Accelerator

---

# Interactive

Target:

Desktop workloads

Latency:

< 5ms

---

# Realtime

Policy:

EDF + Priority Enforcement

Guarantee:

Deterministic execution

---

# Batch

Policy:

Throughput optimized

Use Cases:

Compilation

Rendering

Training

---

# Background

Lowest priority.

Never starve higher classes.

---

# Accelerator Scheduler

Resources:

GPU

NPU

DSP

FPGA

---

# Load Balancing

NUMA aware.

Core topology aware.

Cache aware.

---

# Fairness

Weighted fair scheduling.

Starvation prevention mandatory.

---

# Metrics

Context Switch Rate

Latency

Queue Length

CPU Utilization

GPU Utilization

NPU Utilization

All exposed through telemetry.

---

# Future Extensions

Energy-aware scheduling.

Thermal-aware scheduling.

Cluster-aware scheduling.
