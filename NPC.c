#include <stdio.h>
#include <stdbool.h>

#define MAX_VARS 100

// Función para verificar si la asignación satisface la fórmula booleana


//
bool isSatisfied(int assignment[], int clauses[][3], int numClauses) {
    int i;
	for (i = 0; i < numClauses; i++) {
        int var1 = clauses[i][0];
        int var2 = clauses[i][1];
        int var3 = clauses[i][2];

        // Verificar si al menos una variable en la cláusula es verdadera
        if (!(assignment[abs(var1)] == (var1 > 0) || assignment[abs(var2)] == (var2 > 0) ||
              assignment[abs(var3)] == (var3 > 0))) {
            return false;
        }
    }

    return true;
}

// Función recursiva de backtracking para encontrar una asignación que satisfaga la fórmula
bool solveSAT(int assignment[], int clauses[][3], int numVars, int numClauses, int currentVar) {
    if (currentVar > numVars) {
        // Se alcanzó una asignación completa, verificar si satisface la fórmula
        return isSatisfied(assignment, clauses, numClauses);
    }

    // Asignar valor verdadero y continuar con la siguiente variable
    assignment[currentVar] = true;
    if (solveSAT(assignment, clauses, numVars, numClauses, currentVar + 1)) {
        return true;
    }

    // Asignar valor falso y continuar con la siguiente variable
    assignment[currentVar] = false;
    if (solveSAT(assignment, clauses, numVars, numClauses, currentVar + 1)) {
        return true;
    }

    return false;
}

int main() {
	
/*Número de variables: 4
Número de cláusulas: 3
Cláusula 1: 1 2 -3
Cláusula 2: -1 -2 3
Cláusula 3: 2 -3 4
*/
    int numVars, numClauses;
    int assignment[MAX_VARS] = {0};
    int clauses[MAX_VARS][3];

    printf("Ingrese el número de variables: ");
    scanf("%d", &numVars);

    printf("Ingrese el número de cláusulas: ");
    scanf("%d", &numClauses);
	int i,j;
    printf("Ingrese las cláusulas (cada cláusula debe tener tres variables):\n");
    for (i = 0; i < numClauses; i++) {
        printf("Cláusula %d: ", i + 1);
        
        for (j = 0; j < 3; j++) {
            scanf("%d", &clauses[i][j]);
        }
    }

    if (solveSAT(assignment, clauses, numVars, numClauses, 1)) {
        printf("La fórmula es satisfacible. Asignación encontrada:\n");

        for (i = 1; i <= numVars; i++) {
            printf("Variable %d: %s\n", i, assignment[i] ? "Verdadero" : "Falso");
        }
    } else {
        printf("La fórmula no es satisfacible.\n");
    }

    return 0;
}

