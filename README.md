# NetSMT: Guided-SMT solving
This project is a prototype implementation of the guided-SMT solving part of [NetSMT]():
> Xing Fang, Feiyan Ding, Bang Huang, Ziyi Wang, Gao Han, Rulan Yang, Lizhao You, Qiao Xiang, 
Linghe Kong, Yutong Liu, Jiwu Shu. "Network Can Help Check Itself: Accelerating SMT-based Network 
Configuration Verification Using Network Domain Knowledge", INFOCOM'24

The SMT formula simplification part of NetSMT can be found [here]().

## Introduction
This project builds upon the [Z3 Theorem Prover](https://github.com/Z3Prover/z3) v4.12.2. 
Our modifications aim to use network domain knowledge to guide the variable and assignment exploration
order of the SMT solving process.
### Variable Exploration Order Guidelines
1. All branching variables are prior to other variables.
2. Branching variables whose residing router is closer to the destination are explored first.
3. For branching variables residing in the same router, we order them based on their corresponding route announcement type.

### Assignment Exploration Order Guidelines
1. For branching variables, we prefer the value assignment that is consistent with operating intent.
2. For branching variables that reside in the suspicious error routers, we prefer the assignment that is contrary to operating intent.


## Setup
### Compile
 please refer to the [Z3 build instructions](./README-Z3.md).

### Run & Debug
We use Visual Studio for both development and debugging. For detailed instructions
on setting up and configuring the environment, please refer to
[Z3's CMake build system](./README-CMake.md).

Once you have finished setting up Visual Studio.
you can use the following steps to start debugging:  

1. Open the solution and locate the `shell` project.
2. Right-click and `Set as StartUp Project`.
3. Set parameters in `Debug` -> `Shell Properties` -> `Debugging` -> `Command Arguments`. For example,
`guided="false" dst="barcelona" dst_port="GigabitEthernet0/0" prop_type=0 network_type=0 topology="path\topology"
smt.arith.solver=2 -st path\file.smt2`. Below are the detailed descriptions of each parameter used in the command arguments:
    - **guided:** whether to enable exploration order guidelines. If false, the solver will behave like the original Z3.
    - **dst:** sepcify the prefix origination node.
    - **dst_port:** sepcify the prefix origination port.
    - **prop_type:** 0: reachability; 1:isolation; 2:forwarding
    - **network_type:**  0: wan; 1:fattree
    - **topology:** path to network topology file 
    - **smt.arith.solver:** we use 2 because the old arithmetic core is faster for network verification problems.
   Discussion can be found [here](https://github.com/Z3Prover/z3/issues/6740).
    - **-st**: show detail output
    - **path\file.smt2:** path to SMT2 file

4. Start running or debugging with `Local Windows Debugger`.


## Code Modification
All codes that we have modified are encapsulated within `ADD_BEGIN` and `ADD_END` markers.
Below, we provide an overview of the functionalities introduced by these modifications.
- **util/graph.cpp/.h:** store topology and compute the distance from nodes to the destination.
- **util/gparams.cpp:** reset topology data when solving different topologies at one time.
- **util/env_params.cpp:** register command arguments.
- **smt/smt_internalizer.h:** initialize the variabe and assignment order.
- **smt/smt_case_split_queue.cpp:** determine the next variable to explore.
- **smt/smt_context.cpp:** determine the next assignment to explore.
- **smt/smt_context.h:** functions used to initialize and determine exploration order.


## Contact

- Xing Fang (xing.fang.xmu@outlook.com)
- Feiyan Ding (feiyan.ding.xmu@gmail.com)
- Bang Huang (bang.huang.xmu@outlook.com)
