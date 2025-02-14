/** Group One
 * 
 * Matric No.	Fullname
 * U22CS1001	Abdulganiyu Lateefah
 * U22CS1002	Abdullah Abdullah
 * U22CS1102	Otuaga Eseoghene Christine
 * U22CS1060	Hassan Abubakar Abdulkadir
 * U22CS1014	Ahmad Al-Amin
 * U22CS1112	Stephen Victor Ibukun
 * U22CS1010	Adefisan Praise Adedokun
 * U22CS1015	Ahmad Hafsah Yahaya
 * U22CS1009	Adefisan Peace Folashade
 * U22CS1031	Ayegh Anadoo Jessica
 * 
 * Title: C++ Implementation of the Simplex Algorithm for solving LPPs
 * Brief Description: 
 * This program implements the Simplex algorithm to solve Linear Programming Problems (LPPs)
 * that feature only ‘less than or equal to’ constraints with nonnegative right-hand sides.
 * It supports both maximization and minimization problems by appropriately setting the objective
 * function. The program constructs a tableau, adds slack variables, and iteratively performs 
 * pivot operations while updating basic variables to approach an optimal solution. Detailed 
 * tableau displays are provided at each iteration to facilitate educational understanding and 
 * debugging. Its design is robust for moderate‐size LPPs, though it does not yet support 
 * constraints with negative right-hand sides or other inequality types.
 * 
 */

#include <iostream>
#include <vector>
#include <iomanip>
#include <limits>

using namespace std;

class Simplex {
private:
    // Variables below rep. decision varables and constraints respectively
    int numVars, numConstraints;
    // Vector below reps. the tableau at each iteration
    vector<vector<double>> tableau;
    // We will use numbers to rep. our basic variables
    vector<int> basicVars;

public:
    // Constructor to set up the Simplex tableau
    Simplex(int variables, int constraints, vector<vector<double>> &A, vector<double> &b, vector<double> &c, bool isMaximization) {
        numVars = variables;
        numConstraints = constraints;
        // Initialize tableau with constraints and slack variables
        /**
         * (numVars + numConstraints + 1, 0) -> This creates (numVars + numConstraints + 1) columns
         * in each row and sets each of them to 0
         */
        tableau.resize(numConstraints + 2, vector<double>(numVars + numConstraints + 1, 0));

        // Add constraints to tableau
        for (int i = 0; i < numConstraints; i++) {
            for (int j = 0; j < numVars; j++) {
                tableau[i][j] = A[i][j]; // Constraint coefficients
            }
            tableau[i][numVars + i] = 1;  // Add slack variable
            tableau[i].back() = b[i];     // Right-hand side values
            basicVars.push_back(numVars + i); // Keep track of basic variables
        }

        // Add objective function to tableau
        for (int j = 0; j < numVars; j++) {
            tableau[numConstraints][j] = isMaximization ? c[j] : -c[j]; // Flip sign for minimization
        }
    }

    // Display the Simplex tableau with borders
    void printTableau(int iteration = -1) {
        int width = 10; // Width of columns
        int totalWidth = (numVars + numConstraints + 2) * width + (numVars + numConstraints + 3);

        // Show iteration number
        if (iteration == -1) {
            cout << "\n** Starting Tableau **\n";
        } else if (iteration == 0) {
            cout << "\n** Final Tableau **\n";
        } else {
            cout << "\n** Iteration " << iteration << " **\n";
        }

        // Top border
        cout << "+" << string(totalWidth - 2, '-') << "+\n";

        // Column headers
        cout << "|" << setw(width) << " Basis " << "|";
        for (int j = 0; j < numVars + numConstraints; j++) {
            cout << setw(width) << "x" + to_string(j + 1) << "|";
        }
        cout << setw(width) << " RHS " << "|\n";

        // Middle border
        cout << "+" << string(totalWidth - 2, '-') << "+\n";

        // Print rows of tableau
        for (int i = 0; i < numConstraints + 2; i++) {
            if (i < numConstraints) {
                cout << "|" << setw(width) << "x" + to_string(basicVars[i] + 1) << "|";
            } else if (i == numConstraints) {
                cout << "|" << setw(width) << " Z " << "|";
            } else {
                cout << "|" << setw(width) << " Cj - Zj " << "|";
            }
            for (int j = 0; j <= numVars + numConstraints; j++) {
                cout << setw(width) << fixed << setprecision(2) << tableau[i][j] << "|";
            }
            cout << "\n";
        }

        // Bottom border
        cout << "+" << string(totalWidth - 2, '-') << "+\n\n";
    }
    
    // Compute Cj - Zj values and store them in the last row
    void computeCjMinusZj() {
        /**
         * numVars + numConstraints reps. the number of columns in the tableau
         */
        for (int j = 0; j < numVars + numConstraints; j++) {
            double zj = 0;
            for (int i = 0; i < numConstraints; i++) {
                zj += tableau[i][j] * tableau[numConstraints][basicVars[i]]; // Compute Zj
            }
            // cout<<zj<<endl;
            tableau[numConstraints + 1][j] = tableau[numConstraints][j] - zj; // Compute Cj - Zj
            // cout<<"cj-zj: "<<tableau[numConstraints + 1][j]<<endl;
        }
        // To compute the objective function value
        double zj = 0;
        for (int i = 0; i < numConstraints; i++) {
            zj += tableau[i].back() * tableau[numConstraints][basicVars[i]]; // Compute Zj
        }
        tableau[numConstraints+1].back() = tableau[numConstraints].back() = zj;
    }

    // Find pivot column (entering variable)
    int getPivotColumn() {
        int pivotCol = -1;
        double maxPositive = 0; // Track the most positive Cj - Zj
        
        computeCjMinusZj();
        /**
         * numVars + numConstraints reps. the number of columns in the tableau
         */
        for (int j = 0; j < numVars + numConstraints; j++) {
            // Find the most positive Cj - Zj value
            if (tableau[numConstraints + 1][j] > maxPositive) {
                maxPositive = tableau[numConstraints + 1][j];
                pivotCol = j;
            }
        }
    
        return (pivotCol == -1 || maxPositive <= 0) ? -1 : pivotCol; // If no positive Cj - Zj, optimal reached
    }

    // Find pivot row (leaving variable)
    int getPivotRow(int pivotCol) {
        int pivotRow = -1;
        /**
         * The variable minRatio is assigned to the largest possible value a double can store to
         * ensure any subsequent value will be less than it 
         * */  
        double minRatio = numeric_limits<double>::max();

        for (int i = 0; i < numConstraints; i++) {
            if (tableau[i][pivotCol] > 0) {
                double ratio = tableau[i].back() / tableau[i][pivotCol];
                if (ratio < minRatio) {
                    minRatio = ratio;
                    pivotRow = i;
                }
            }
        }
        return pivotRow;
    }

    // Perform pivot operation to lead to the updated tableau
    void pivot(int pivotRow, int pivotCol) {
        double pivotElement = tableau[pivotRow][pivotCol];

        // Scale the pivot row
        /**
         * For every entry in pivot row, divide by pivot element
         */
        for (double &val : tableau[pivotRow]) {
            val /= pivotElement;
        }

        // Set other rows to zero in pivot column
        for (int i = 0; i < numConstraints; i++) {
            if (i != pivotRow) {
                double factor = tableau[i][pivotCol];
                for (int j = 0; j <= numVars + numConstraints; j++) {
                    tableau[i][j] -= factor * tableau[pivotRow][j];
                }
            }
        }

        // Update basic variables list
        basicVars[pivotRow] = pivotCol;
    }

    // Run the Simplex algorithm
    void solve(bool isMaximization) {

        cout << "\nRunning Simplex Algorithm...\n";

        int iteration = 0;
        while (true) {
            int pivotCol = getPivotColumn();
            // Show starting tableau only once at the beginning
            if (iteration == 0)  printTableau(-1);
            
            if (pivotCol == -1) break;
    
            int pivotRow = getPivotRow(pivotCol);
            if (pivotRow == -1) {
                cout << "The problem is **Unbounded**.\n";
                return;
            }
    
            pivot(pivotRow, pivotCol);
            computeCjMinusZj();
    
            iteration++;
    
            // Check if the next pivot column is invalid to determine if this is the final iteration
            int nextPivotCol = getPivotColumn();
            if (nextPivotCol == -1) {
                printTableau(0); // Print as final tableau and exit
                break;
            } else {
                printTableau(iteration); // Print next iteration
            }
        }
    
        // If no iterations occurred (initial tableau is optimal), print final tableau
        if (iteration == 0) {
            printTableau(0);
        }
    
        // Show the best solution
        cout << "Found Optimal Solution!\n";
        vector<double> solution(numVars, 0);
        for (int i = 0; i < numConstraints; i++) {
            if (basicVars[i] < numVars) {
                solution[basicVars[i]] = tableau[i].back();
            }
        }
    
        for (int i = 0; i < numVars; i++) {
            cout << "x" << i + 1 << " = " << fixed << setprecision(2) << solution[i] << endl;
        }
        cout << (isMaximization ? "Maximum" : "Minimum") << " Value (Z) = " << fixed << setprecision(2) << (isMaximization ? tableau[numConstraints].back() : -tableau[numConstraints].back()) << endl;
    }
};

// **MAIN FUNCTION**
int main() {
    int variables, constraints;
    char problemType;

    // Notify the user of the program's limitation
    cout << "Note: \nThis Simplex Algorithm only works for LPPs with <= constraints\nIt can't deal with constraints with negative RHS values yet" << endl;    

    // Get user input for number of variables and constraints
    cout << "Enter the number of decision variables: ";
    cin >> variables;
    cout << "Enter the number of constraints: ";
    cin >> constraints;

    vector<vector<double>> A(constraints, vector<double>(variables));
    vector<double> b(constraints);
    vector<double> c(variables);

    // Get user input for the coefficients of the constraints
    cout << "Enter the coefficients of the constraints (row by row):\n";
    for (int i = 0; i < constraints; i++) {
        for (int j = 0; j < variables; j++) {
            cout << "a" << i + 1 << j + 1 << ": ";
            cin >> A[i][j];
        }
    }

    // Get user input for the right-hand side values of the constraints
    cout << "Enter the right-hand side values of the constraints:\n";
    for (int i = 0; i < constraints; i++) {
        cout << "b" << i + 1 << ": ";
        cin >> b[i];
    }

    // Get user input for the coefficients of the objective function
    cout << "Enter the coefficients of the objective function:\n";
    for (int i = 0; i < variables; i++) {
        cout << "c" << i + 1 << ": ";
        cin >> c[i];
    }

    // Ask if the problem is maximization or minimization
    cout << "Is this a maximization (M) or minimization (m) problem? (M/m): ";
    cin >> problemType;
    bool isMaximization = (problemType == 'M' || problemType == 'm') ? (problemType == 'M') : true;

    // Create an object of the Simplex class and solve the problem
    Simplex simplex(variables, constraints, A, b, c, isMaximization);
    simplex.solve(isMaximization);

    // The code below is there to stop the program from exiting until the user presses any key
    cout << "\nPress the enter key to exit...\n";
    cin.ignore(); // Clears the input buffer in case of leftover inputs thus letting line 333 work
    cin.get(); 

    return 0;
}
