### Usage

```make``` and execute any of binaries.

### Benchmarking

Installing tools:
1. ```uname -r``` to get \<Kernel-Version\>
2. ```apt install linux-tools-<Kernel-Version>```
3. ```perf list``` to list all possible hardware counter based events. We require the task-clock and floating point counters.

To benchmark the code for GFLOPS (the FP counter names may differ, refer to `perf list`)
* For unoptimized code: ```perf stat -e task-clock,fp_arith_inst_retired.scalar_single,fp_arith_inst_retired.scalar_double ./unoptimized``` 
* For any other binary: ```perf stat -e task-clock,fp_arith_inst_retired.scalar_single,fp_arith_inst_retired.256b_packed_double ./blocking```
* You may also try ```perf stat -M GFLOPS ./binary``` but all counters may not be monitored.
* L1/2/3 hit/miss rates, and a lot of other events can be monitored.
