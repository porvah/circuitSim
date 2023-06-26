#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "structures.h"
#include "nodal.h"
#include "solver.h"
#include <stdlib.h>
int main() {


	printf("CircuitSim V1.0\n");
	int nNodes;
	printf("Enter the number of nodes:\n");
	scanf("%d", &nNodes);
	int nComp;
	printf("\nEnter the number of components:\n");
	scanf("%d", &nComp);
	printf("Enter each component in the form (type value terminal1Node terminal2Node)\n");
	printf("Note 1 : for types (1 for resistance , 2 for VCC)\n");
	printf("Note 2 : all voltages are in volts and all resistances in kohms\n");
	printf("Note 2 : in voltage sources terminal 1 is the -ve pole, terminal 2 is the +ve pole\n");
	
	struct Component* mycomp = (struct Component*)malloc(nComp * sizeof(struct Component));
	for (int i = 0; i < nComp; i++) {
		printf("%d- ", i + 1);
		scanf("%d %lf %d %d", &mycomp[i].type, &mycomp[i].value, &mycomp[i].T1, &mycomp[i].T2);
		printf("\n");
		
	}
	int nGnd;
	printf("Choose the ground Node (reference node): \n");
	scanf("%d", &nGnd);
	

	double** eqnMatrix = solveCircuit(nNodes, nComp, mycomp, nGnd, 0, 0);
	double* results = solver(nNodes, eqnMatrix);
	
	for (int i = 0; i < nNodes; i++) {
		printf("N%d= %f Volts\n", i, results[i]);
	}
	return 0;
}