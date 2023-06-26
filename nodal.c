#include "structures.h"
#include "solver.h"
#include <stdio.h>
#include <stdlib.h>



void setupNodes(struct Node nodes[], int nodeNo, int gndNode, struct Component components[], int noComponents) {
	for (int i = 0; i < nodeNo; i++) {
		nodes[i].number = i;
		if (i == gndNode) {
			nodes[i].volt = 0.0;
			
		}
		else {
			nodes[i].volt = UNKNOWN;
		}
		nodes[i].marked = 0;
		nodes[i].compNo = 0;
	}
	for (int i = 0; i < noComponents; i++) {
		if (components[i].T1 == components[i].T2 && components[i].type == RES) {
			components[i].current = 0.0;
		}
		components[i].marked = 0;
		int t1 = components[i].T1;
		int t2 = components[i].T2;
		nodes[t1].connections[nodes[t1].compNo++] = components[i];
		nodes[t2].connections[nodes[t2].compNo++] = components[i];
	}
}

double** makeMatrix(int nodeNo) {
	double** matrix = (double**)malloc(nodeNo * sizeof(double*));
	for (int i = 0; i < nodeNo; i++) {
		matrix[i] = (double*)malloc(((nodeNo) + 1) * sizeof(double));
	}

	return matrix;
}

double** solveCircuit(int nodeNo, int compNo, struct Component components[], int gndNode, int vProbe, int iProbe) {
	struct Node* nodes = (struct Node*)malloc(nodeNo * sizeof(struct Node));
	setupNodes(nodes, nodeNo, gndNode, components, compNo);


	double** equations = makeMatrix(nodeNo);
	int eqNo = 0;

	//gnd set up
	for (int i = 0; i < nodes[gndNode].compNo; i++) {
		if (nodes[gndNode].connections[i].type == VCC) {
			nodes[gndNode].connections[i].marked = 1;
			if (nodes[gndNode].number == nodes[gndNode].connections[i].T1) {
				nodes[nodes[gndNode].connections[i].T2].volt = nodes[gndNode].connections[i].value;
			}
			else {
				nodes[nodes[gndNode].connections[i].T1].volt = -1 * nodes[gndNode].connections[i].value;
			}
		}
	}

	//analysis
	int eqnNo = 0;
	for (int i = 0; i < nodeNo; i++) {
		double* eqn = (double*)malloc((nodeNo + 1) * sizeof(double));
		for (int j = 0; j <= nodeNo; j++) {
			eqn[j] = 0.0;
		}
		struct Node* curr = &nodes[i];
		int superNode = 1;
		if (!(*curr).marked) {
			while (superNode) {
				superNode = 0;
				if ((*curr).marked == 0) {
					(*curr).marked = 1;
					if ((*curr).volt != UNKNOWN) {
						for (int j = 0; j < nodeNo; j++) {
							eqn[j] = 0.0;
						}
						eqn[i] = 1;
						eqn[nodeNo] = (*curr).volt;
					}
					else {
						struct Node* nextNode = NULL;
						for (int j = 0; j < (*curr).compNo; j++) {
							struct Component* comp = &(*curr).connections[j];
							struct Node* t1 = &nodes[(*curr).connections[j].T1];
							struct Node* t2 = &nodes[(*curr).connections[j].T2];
							struct Node* otherEnd;
							if ((*t1).number == (*curr).number) {
								otherEnd = t2;
							}
							else {
								otherEnd = t1;
							}
							if ((*comp).type == RES) {
								eqn[(*curr).number] += (1 / (*comp).value);
								eqn[(*otherEnd).number] -= (1 / (*comp).value);
							}
							else if ((*comp).type == VCC) {
								if ((*comp).marked == 0) {
									(*comp).marked = 1;
									double* vccEqn = (double*)malloc((nodeNo + 1) * sizeof(double));
									for (int k = 0; k <= nodeNo; k++) {
										vccEqn[k] = 0.0;
									}
									vccEqn[(*t2).number] = 1;
									vccEqn[(*t1).number] = -1;
									vccEqn[nodeNo] = (*comp).value;
									equations[eqnNo++] = vccEqn;
									superNode = 1;
									nextNode = otherEnd;
									for (int k = 0; k < (*nextNode).compNo; k++) {
										if ((*nextNode).connections[k].type == VCC && (*nextNode).connections[k].T1 == (*curr).connections[j].T1 && (*nextNode).connections[k].T2 == (*curr).connections[j].T2) {
											(*nextNode).connections[k].marked = 1;
										}
									}
								}
							}
						}
						if (superNode)
							curr = nextNode;
					}
				}

			}
			equations[eqnNo++] = eqn;
		}
		

	}
	free(nodes);
	return equations;

}

