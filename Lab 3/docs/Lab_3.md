![Heading](Head.png)

### Static Storage Class 
**Step 1:** Compile and run this program 3 times, copy the output and put it in your report, explain why the result show up that way

**Output**
```text
The value of y is 6
The address of y is 0x5595aa281010

The value of y is 7
The address of y is 0x5595aa281010

The value of y is 8
The address of y is 0x5595aa281010

The value of y is 6
The address of y is 0x62b76f30f010

The value of y is 7
The address of y is 0x62b76f30f010

The value of y is 8
The address of y is 0x62b76f30f010

The value of y is 6
The address of y is 0x56a375d25010

The value of y is 7
The address of y is 0x56a375d25010

The value of y is 8
The address of y is 0x56a375d25010
```
**Explanation**
`auto` gives x automatic storage duration. The variable is initialized to 3 when `main()` begins. During each loop iteration, x is decremented by 1. Its values are 3, 2, and 1 during the three iterations, after which it becomes 0 and the condition `x > 0` becomes false. Therefore, the loop executes exactly three times.

The variable y is declared with `static` This means that y is created once and exists for the entire lifetime of the program. That is why y went from 6 to 7 and 8 because of y++ in each loop. However, the address may be different when the program is executed again because the program's memory layout can change between executions when PIE and ASLR are enabled.

Address Space Layout Randomization (ASLR): It randomize the memory of the Program evertime it start.

Position-Independent Executable (PIE) allows the main executable to be loaded at different virtual memory addresses. When PIE is combined with ASLR, the base address of the executable can change between executions.

---
**Step 2:** Modify the code by delete the `static` word, compile, and re-run the program.
**Step 3:** Copy the output and put it in your report, explain why the results show up that way, and discuss the difference between both outputs.

**Output**
```text
The value of y is 6
The address of y is 0x7ffecc8e85c0

The value of y is 6
The address of y is 0x7ffecc8e85c0

The value of y is 6
The address of y is 0x7ffecc8e85c0

The value of y is 6
The address of y is 0x7ffc16fe2260

The value of y is 6
The address of y is 0x7ffc16fe2260

The value of y is 6
The address of y is 0x7ffc16fe2260

The value of y is 6
The address of y is 0x7fff2e816410

The value of y is 6
The address of y is 0x7fff2e816410

The value of y is 6
The address of y is 0x7fff2e816410
```
**Explanation**
Without `static`, y has automatic storage duration. Each time the loop enters the block, y is initialized to 5. The statement y++ then changes it to 6. When the iteration ends, the lifetime of that automatic variable ends. On the next iteration, y is initialized to 5 again, so the printed value is always 6.

Although a new automatic y is created on each iteration, the compiler can reuse the same stack memory location because the previous y has reached the end of its lifetime. Therefore, the address can remain the same across iterations. However, the stack address can change between separate executions because of ASLR.

---

**Step 4:** Redo step 1-3, but this time compile the program using: 
 ```bash
“gcc -no-pie -o <your executable object name> <your c code name>” 
 ```
 Are they different? Why or why not 

**Step 4.1:** With `static`.

**Output**
```text
The value of y is 6
The address of y is 0x404018

The value of y is 7
The address of y is 0x404018

The value of y is 8
The address of y is 0x404018

The value of y is 6
The address of y is 0x404018

The value of y is 7
The address of y is 0x404018

The value of y is 8
The address of y is 0x404018

The value of y is 6
The address of y is 0x404018

The value of y is 7
The address of y is 0x404018

The value of y is 8
The address of y is 0x404018
```
**Explanation**
With static, y keeps its value between loop iterations, so the output is 6, 7, and 8. Its address remains the same because all iterations use the same variable.

When using `-no-pie`, PIE is disabled. This means the executable is loaded at a fixed memory address instead of being relocated to a different address between executions. Since the `static` variable y is stored in the executable's data section, its address is also fixed. Therefore, y has the address `0x404018` in every execution.

ASLR is still enabled, but it does not change the address of y because the executable was compiled without PIE. ASLR can still randomize other memory regions, such as the stack and heap.

---
**Step 4.2:** Without `static`.

**Output**
```text
The value of y is 6
The address of y is 0x7ffc878a8570

The value of y is 6
The address of y is 0x7ffc878a8570

The value of y is 6
The address of y is 0x7ffc878a8570

The value of y is 6
The address of y is 0x7ffe606424b0

The value of y is 6
The address of y is 0x7ffe606424b0

The value of y is 6
The address of y is 0x7ffe606424b0

The value of y is 6
The address of y is 0x7ffe8940b570

The value of y is 6
The address of y is 0x7ffe8940b570

The value of y is 6
The address of y is 0x7ffe8940b570
```
**Explanation**

Without `static`, y is an automatic variable that is recreated and initialized to 5 during each loop iteration. Therefore, its value is always 6 after `y++`.

Its address remains the same within each execution because the same stack location can be reused for y on each loop iteration. However, the address changes between separate executions because y is an automatic variable stored on the stack, and `-no-pie`does not disable ASLR. Therefore, the stack can be located at a different virtual address each time the program runs.

Therefore, `-no-pie` makes the static variable's address fixed in this environment, but it does not affect the stack address of the automatic variable. As a result, the non-static variable shows essentially the same address behavior with or without `-no-pie`.

---

**Comparison**
| Case | Value of `y` | Address within execution | Address between executions |
| - | - | - | - |
| `static`, normal compilation | 6  -> 7  -> 8 | Same | Change |
| non-`static`, normal compilation | 6  -> 6  -> 6 | Same in this experiment | Change |
| `static`, `-no-pie` | 6  -> 7  -> 8 | Same | Same in this environment |
| non-`static`, `-no-pie` | 6  -> 6  -> 6 | Same in this experiment | Change |

Overall, the main difference is the effect of `static` and `-no-pie` on the variable's lifetime and address. With static, y retains its value between loop iterations, producing 6 → 7 → 8. Without static, y is recreated and initialized to 5 on each iteration, so the output remains 6 → 6 → 6.

Without `-no-pie`, the address of the static variable changes between separate executions because PIE allows the executable to be relocated and ASLR randomizes the memory layout. When `-no-pie` is used, the main executable is not position-independent, so the static variable's address remains fixed in this environment at 0x404018.

The address of the non-static variable remains the same within an execution because the compiler can reuse the same stack location. However, its address changes between executions because it is stored on the stack, and ASLR can randomize the stack location. Therefore, using `-no-pie` does not make the address of the automatic variable fixed.

--- 

## Extern Storage Class
**Step 1:** Compile and run this program 3 times, copy the output and put it in your report, explain why the result show up that way

**Output**
```text
 Print value of x: 20
 Adress of x (in main function): 0x6096408c2010

 Display value of x: 20
 Adress of x (in display function): 0x6096408c2010

 Print value of x: 20
 Adress of x (in main function): 0x5e1a18ca0010

 Display value of x: 20
 Adress of x (in display function): 0x5e1a18ca0010

 Print value of x: 20
 Adress of x (in main function): 0x5cc33dfb4010

 Display value of x: 20
 Adress of x (in display function): 0x5cc33dfb4010
```
**Explanation**

---
**Step 2:** Modify the code by delete the `extern` word, compile, and re-run the program.
**Step 3:** Copy the output and put it in your report, explain why the results show up that way, and discuss the difference between both outputs.

**Output**
```text
 Print value of x: 0
 Adress of x (in main function): 0x7fff82c07e54

 Display value of x: 0
 Adress of x (in display function): 0x7fff82c07e34

 Print value of x: 0
 Adress of x (in main function): 0x7ffe0b6ab584

 Display value of x: 0
 Adress of x (in display function): 0x7ffe0b6ab564

 Print value of x: 0
 Adress of x (in main function): 0x7fff1070bd64

 Display value of x: 0
 Adress of x (in display function): 0x7fff1070bd44
```
**Explanation**


---

**Step 4:** Redo step 1-3, but this time compile the program using: 
 ```bash
“gcc -no-pie -o <your executable object name> <your c code name>” 
 ```
 Are they different? Why or why not 

**Step 4.1:** With `extern`.

**Output**
```text
 Print value of x: 20
 Adress of x (in main function): 0x404018

 Display value of x: 20
 Adress of x (in display function): 0x404018

 Print value of x: 20
 Adress of x (in main function): 0x404018

 Display value of x: 20
 Adress of x (in display function): 0x404018

 Print value of x: 20
 Adress of x (in main function): 0x404018

 Display value of x: 20
 Adress of x (in display function): 0x404018
```
**Explanation**


---
**Step 4.2:** Without `extern`.

**Output**
```text
 Print value of x: 0
 Adress of x (in main function): 0x7fffc1a84ba4

 Display value of x: 0
 Adress of x (in display function): 0x7fffc1a84b84

 Print value of x: 0
 Adress of x (in main function): 0x7ffcb85d5c74

 Display value of x: 0
 Adress of x (in display function): 0x7ffcb85d5c54

 Print value of x: 0
 Adress of x (in main function): 0x7ffcfbecac14

 Display value of x: 0
 Adress of x (in display function): 0x7ffcfbecabf4

```
**Explanation**


---

**Comparison**
| Case | Value of `x` | Address of `x` in main function | Address of `x` in display function  |
| - | - | - | - |
| `static`, normal compilation | 6  -> 7  -> 8 | Same | Change |
| non-`static`, normal compilation | 6  -> 6  -> 6 | Same in this experiment | Change |
| `static`, `-no-pie` | 6  -> 7  -> 8 | Same | Same in this environment |
| non-`static`, `-no-pie` | 6  -> 6  -> 6 | Same in this experiment | Change |

Overall,

--- 