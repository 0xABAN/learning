# C++ → NVIDIA Roadmap

Small native projects that stack: C++ fundamentals → vision → concurrency → CUDA → inference.

Start on a laptop. Add CUDA when Project 1 is solid.

## Sequence

| # | Project | Role |
| --- | --------- | ------ |
| 1 | Image-processing library | Learning foundation |
| 2 | Camera calibration + marker pose | Learning / geometry |
| 3 | Multithreaded video pipeline | Resume-grade systems |
| 4 | CPU vs CUDA convolution | Resume-grade CUDA |
| 5 | TensorRT inference wrapper | Resume-grade inference |

**Robotics alternative for #2:** 2D occupancy-grid mapper from simulated LIDAR (toward ROS2 / Isaac / localization).

**Do not** start with YOLO + ROS2 + TensorRT + Isaac all at once. CPU first, understand data flow, then accelerate one stage.

---

## 1. Image-processing library (C++)

CLI tool only — no GUI, no web.

- Load/save PGM/PPM
- Grayscale
- Blur, Sobel edges, threshold, resize
- Unit tests + benchmarks
- C++17/20 + stdlib only at first

**You learn:** `std::vector`, memory layout, RAII, file I/O, APIs, CMake, testing, basic vision.

---

## 2. Camera calibration and marker pose

OpenCV (C++):

- Chessboard webcam calibration
- Undistort frames
- Detect ArUco markers
- Estimate 3D marker pose
- Show reprojection error + pose stability

**Vocabulary:** intrinsics/extrinsics, coordinate transforms, projection, reprojection error, pose estimation.

Teaches real geometry — not just calling a network.

---

## 3. Multithreaded real-time video pipeline

```text
video input → capture thread → bounded queue → processing workers → output
```

C++ + OpenCV. Measure:

- FPS
- p50 / p95 frame latency
- Dropped frames
- Queue depth
- CPU utilization

**Tools:** `std::thread` / `std::jthread`, `std::mutex`, `std::condition_variable`, atomics, bounded queue.

Connects vision to systems engineering, concurrency, and real-time constraints.

---

## 4. CPU vs CUDA image convolution

One op from Project 1 (blur or Sobel), two implementations:

1. CPU C++
2. CUDA kernel

Compare:

- Correctness
- Kernel time
- Host ↔ device transfer time
- End-to-end latency
- Image sizes + block dimensions

Profile with Nsight when you have an NVIDIA GPU.

**You learn:** grids/blocks, device memory, thread indexing, sync, transfer cost, basic GPU optimization.

One kernel you can verify mathematically > giant neural-net CUDA project.

---

## 5. Small TensorRT inference wrapper

*After* 1–4, not before.

- Export pretrained vision model: PyTorch → ONNX
- Load with TensorRT
- C++ inference wrapper
- Pre/post-processing
- Compare PyTorch vs ONNX Runtime vs TensorRT
- Benchmark FP32 vs FP16 (if supported)

Report: latency, throughput, memory, accuracy deltas.

Maps to NCG postings that emphasize C++, Python, CUDA, TensorRT, performance analysis.

---

## Resume bar (every project)

- [ ] CMake
- [ ] Clear C++ interfaces
- [ ] Unit tests
- [ ] Sanitizers
- [ ] `-Wall -Wextra -Wpedantic`
- [ ] Reproducible benchmark
- [ ] Short architecture diagram
- [ ] Failure cases + limitations
- [ ] Measured performance results

The win is not “used CUDA.” It is explaining **why** one path was faster, **where** the bottleneck was, and **what** tradeoff you made.

---

## Target story

> C++ real-time perception pipeline — camera geometry, multithreading, and a CUDA/TensorRT-accelerated stage.

Fits NVIDIA computer-vision and robotics roles; builds on Amazon robotics background.

---

## Current workspace

Parallel track while building projects:

- `cpp/basics/` — language drills
- `leetcode/` — Python problem practice (existing C++ exercises retained)
- nvim setup (lazy, treesitter, fzf-lua, blink.cmp)

**Next project step when ready:** scaffold Project 1 under something like `cpp/projects/imgproc/`.
