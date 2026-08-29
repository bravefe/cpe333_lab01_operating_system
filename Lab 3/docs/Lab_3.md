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
```c
auto int x = 3;
```
`auto` gives x automatic storage duration. The variable is initialized to 3 when `main()` begins. During each loop iteration, x is decremented by 1. Its values are 3, 2, and 1 during the three iterations, after which it becomes 0 and the condition `x > 0` becomes false. Therefore, the loop executes exactly three times.

The variable y is declared with `static` This means that y is created once and exists for the entire lifetime of the program. That is why y went from 6 to 7 and 8. However, the address may be different when the program is executed again because the program's memory layout can change between executions when PIE and ASLR are enabled.

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
Without static, y becomes an automatic local variable. is executed each time the program enters the block containing the declaration. Therefore, each loop iteration starts with 5 and y++ to 6, but when the next iteration begins, a new y is initialized.

The result show that all the y even in diffrent program has the same adresss. The compiler can reuse the same stack location for a local variable because the previous y is no longer needed. The important difference is the lifetime/value, not simply the printed address.

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

Using `-no-pie` disables Position Independent Executable (PIE), so the static variable is placed at a fixed address. Therefore, the address is 0x404018 in every execution instead of changing between runs.

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

Its address stays the same within each program because the same stack location can be reused. However, the address changes between program because y is stored on the stack, and `-no-pie` does not disable ASLR for stack addresses.

Therefore, `-no-pie` makes the static variable's address fixed, but it does not make the stack address of an automatic variable fixed.


---
