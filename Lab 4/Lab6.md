# Lab 6: Virtual Memory and VM Monitoring

## Objectives

1. Understand the concept of virtual memory.
2. Explain and compare how virtual memory is implemented in modern Linux and Microsoft Windows.
3. Show step-by-step how to increase or decrease swap space in Linux, including screenshots.
4. Understand Linux VM monitoring using the `free` and `vmstat` commands.
5. Understand Windows VM monitoring using Resource Monitor.

---

## 1. Concept of Virtual Memory

### 1.1 Definition
Explain what virtual memory is and why it is important in modern operating systems.

### 1.2 How It Works
Describe the role of:
- page tables
- swap space
- RAM
- paging and page faults

### 1.3 Comparison: Linux vs. Microsoft Windows
Compare how virtual memory is implemented in:
- Linux
- Microsoft Windows

You may discuss the following points:
- memory management model
- paging behavior
- swap usage
- virtual address space design
- monitoring tools

---

## 2. Increasing or Decreasing Swap Space in Linux

### 2.1 Purpose
Show how to manage swap space in Linux.

### 2.2 Step-by-Step Procedure
Provide a step-by-step guide to:
1. Check current swap status.
2. Create or resize swap space.
3. Enable or disable swap.
4. Verify the result.

### 2.3 Screenshots
Insert screenshots for each important step, such as:
- `free -h` output
- `swapon --show` output
- swap configuration file changes
- final verification output

### 2.4 Notes
Explain the difference between:
- increasing swap
- decreasing swap
- temporary swap file vs. permanent swap partition

---

## 3. Linux VM Monitoring with `free`

### 3.1 Run the Command
Run the following command in the Linux shell:

```bash
free
```

### 3.2 Capture and Explain the Output
Capture the output and explain each field shown by `free`, including:
- total
- used
- free
- shared
- buff/cache
- available
- swap information

### 3.3 Summary Paragraph
Write a paragraph summarizing all numerical values shown in the output.

### 3.4 Useful `free` Arguments
Use `free --help` and select 2 useful arguments.

For each argument:
- describe what it does
- show a sample command
- explain the output

Example arguments to consider:
- `-h` for human-readable output
- `-m` or `-g` for output in MB/GB
- `-t` for total line
- `-s` for periodic updates

---

## 4. Linux VM Monitoring with `vmstat`

### 4.1 Install `vmstat` if Needed
If `vmstat` is not installed, install it first.

### 4.2 Run the Command
Run the command in the Linux shell:

```bash
vmstat
```

### 4.3 Capture and Explain the Output
Capture the output and explain each column, including:
- procs
- memory
- swap
- io
- system
- cpu

### 4.4 Summary Paragraph
Write a paragraph summarizing all numerical values shown in the `vmstat` output.

### 4.5 Useful `vmstat` Arguments
Use `vmstat --help` and select 2 useful arguments.

For each argument:
- describe what it does
- show a sample command
- explain the output

Example arguments to consider:
- `-a`
- `-s`
- `-d`
- `-S` or `-m`
- `-n` for periodic output

---

## 5. Windows VM Monitoring

### 5.1 Open Resource Monitor
Open the Windows Resource Monitor and capture the memory-related interface.

### 5.2 Explain the Interface
Explain the information displayed in the Resource Monitor related to memory monitoring, such as:
- physical memory
- commit
- cached
- available
- hardware reserved

### 5.3 Summary Paragraph
Summarize all numerical values shown in the Physical Memory tab.

---

## 6. Submission Requirements

Submit the completed document file before the due date through LEB2.

> This is a problem session for a group of up to 6 students.

---

## 7. Report Checklist

Before submission, make sure your document includes:
- explanation of virtual memory
- comparison between Linux and Windows
- swap management steps with screenshots
- `free` command output and explanation
- `vmstat` command output and explanation
- Windows Resource Monitor analysis
- summarized paragraphs for numerical values
- final submission in LEB2
