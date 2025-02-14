# Group-One-Simplex-Program
**Name**: Abubakar Abdulkadir Hassan </br>
**Matric no.**: U22CS1060 </br>

# C++ Simplex Algorithm for Linear Programming

## Introduction
This repository hosts a C++ implementation of the **Simplex Algorithm**, designed to solve Linear Programming Problems (LPPs). This project demonstrates the Simplex Method's ability to optimize real-world decision-making scenarios, such as maximizing profits or minimizing costs under linear constraints. The code provides a modular, educational tool for understanding how the Simplex algorithm navigates high-dimensional feasible regions through iterative pivot operations.

---

## What It Does
This program **solves linear optimization problems** by:
- Converting constraints into equations using **slack variables**.
- Organizing problem data into a **Simplex tableau**.
- Iteratively selecting pivot elements to refine solutions until optimality is reached.
- Handling both **maximization** and **minimization** problems.

**Key Features**:
- Accepts user-defined objective functions, constraints, and resource limits.
- Displays the Simplex tableau at each iteration for transparency.
- Outputs optimal variable values and the objective function result.

---

## How It Works
### Algorithm Overview
1. **Standard Form Conversion**:
   - Constraints are converted to equations using slack variables (e.g., `2x + y <= 5` becomes `2x + y + s = 5`).
   - Minimization problems are converted to maximization by negating the objective function.

2. **Tableau Initialization**:
   - Constraints and objective function coefficients are structured into a matrix (tableau).
   - Slack variables form the initial basis (identity matrix).

3. **Iterative Pivot Operations**:
   - **Entering Variable**: Column with the largest positive `Cj - Zj` (net improvement per unit).
   - **Leaving Variable**: Row with the smallest non-negative ratio of RHS to pivot column value.
   - **Pivot**: Normalizes the pivot row and adjusts other rows to update the basis.

4. **Termination**:
   - Stops when all `Cj - Zj <= 0` (optimality) or if the problem is unbounded.

### Code Structure
- **`Simplex` Class**: Manages the tableau, constraints, and pivot logic.
- Key Methods:
  - `computeCjMinusZj()`: Calculates net improvement for variables.
  - `getPivotColumn()` / `getPivotRow()`: Identifies entering/leaving variables.
  - `pivot()`: Executes row operations to update the tableau.
  - `solve()`: Drives the iterative optimization loop.

---

## How to Use It
### Prerequisites
- A C++ compiler (e.g., `g++`).
- Basic understanding of LPP formulation.

### Steps

1. **Clone the Repository**:
```
	git clone https://github.com/your-username/simplex-cpp.git
	cd simplex-cpp
```
2. **Compile the Code**
```
	g++ simplex.cpp -o simplex
```
3. **Run the Program**
```
	./simplex
```  
4. **Input Your Linear Programming Problem (LPP)**
	- Enter the number of decision variables and constraints.
	- Provide coefficients for constraints (e.g., 1 1 <= 5 for x + y <= 5).
	- Specify the objective function coefficients (e.g., 3 2 for Z = 3x + 2y).
	- Choose maximization or minimization.

## Sample problem
### Baker's Problem
Maximize profit Z = 3x + 2y with constraints:
- x + y <= 10 (flour)
- 2x + y <= 15 (time)

and x,y >= 0

### Sample input 
    Note:
    This Simplex Algorithm only works for LPPs with <= constraints
    It can't deal with constraints with negative RHS values yet
    Enter the number of decision variables: 2
    Enter the number of constraints: 2
    Enter the coefficients of the constraints (row by row):
    a11: 1
    a12: 1
    a21: 2
    a22: 1
    Enter the right-hand side values of the constraints:
    b1: 10
    b2: 15
    Enter the coefficients of the objective function:
    c1: 3
    c2: 2
    Is this a maximization (M) or minimization (m) problem? (M/m): M

### Sample output
    Running Simplex Algorithm...
    
    ** Starting Tableau **
    +-----------------------------------------------------------------+
    |    Basis |        x1|        x2|        x3|        x4|      RHS |
    +-----------------------------------------------------------------+
    |        x3|      1.00|      1.00|      1.00|      0.00|     10.00|
    |        x4|      2.00|      1.00|      0.00|      1.00|     15.00|
    |        Z |      3.00|      2.00|      0.00|      0.00|      0.00|
    |  Cj - Zj |      3.00|      2.00|      0.00|      0.00|      0.00|
    +-----------------------------------------------------------------+
    
    
    ** Iteration 1 **
    +-----------------------------------------------------------------+
    |    Basis |        x1|        x2|        x3|        x4|      RHS |
    +-----------------------------------------------------------------+
    |        x3|      0.00|      0.50|      1.00|     -0.50|      2.50|
    |        x1|      1.00|      0.50|      0.00|      0.50|      7.50|
    |        Z |      3.00|      2.00|      0.00|      0.00|     22.50|
    |  Cj - Zj |      0.00|      0.50|      0.00|     -1.50|     22.50|
    +-----------------------------------------------------------------+
    
    
    ** Final Tableau **
    +-----------------------------------------------------------------+
    |    Basis |        x1|        x2|        x3|        x4|      RHS |
    +-----------------------------------------------------------------+
    |        x2|      0.00|      1.00|      2.00|     -1.00|      5.00|
    |        x1|      1.00|      0.00|     -1.00|      1.00|      5.00|
    |        Z |      3.00|      2.00|      0.00|      0.00|     25.00|
    |  Cj - Zj |      0.00|      0.00|     -1.00|     -1.00|     25.00|
    +-----------------------------------------------------------------+
    
    Found Optimal Solution!
    x1 = 5.00
    x2 = 5.00
    Maximum Value (Z) = 25.00
    
    Press the enter key to exit...
    --
    

## Group members

- [@U22cs1001](https://github.com/U22cs1001/Group-one-simplex-program "U22cs1001")
- [@Skidoo123](https://github.com/Skidoo123 "@Skidoo123")
- [@Eseoghene-ChristineOtuaga](https://github.com/Eseoghene-ChristineOtuaga/Group-One-Simplex-Program-.git "@Eseoghene-ChristineOtuaga")
- [@itzaeehassan](https://github.com/itzaeehassan/Group-One-Simplex-Program/ "@itzaeehassan")
- [@Mk30033](https://github.com/Mk30033/Group-One-Simplex-Program "@Mk30033")
- [@13Eris](https://github.com/13Eris/Group-one-simplex-program- "@13Eris")
- [@iampraiseeeeee](https://github.com/iampraiseeeeee/Group-one-simplex-program- "@iampraiseeeeee")
- [@hafsaahmad11](https://github.com/hafsaahmad11/Group-One-Simplex-Program "@hafsaahmad11")
- [@Shadepeace](https://github.com/Shadepeace/Group-One-Simplex-Program.git "@Shadepeace")
- [@Jessicaayegh](https://github.com/Jessicaayegh "@Jessicaayegh")
