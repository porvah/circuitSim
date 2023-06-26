#pragma once
#define MAX_CONNECTIONS 20
#define UNKNOWN -999.0
#define NONE -1
#define RES 1
#define VCC 2
#define GND 0
struct Component {
	int type;
	double value;
	int marked;
	int T1;
	int T2;
	double current;
};

struct Node {
	int number;
	double volt;
	struct Component connections[MAX_CONNECTIONS];
	int compNo;
	int marked;
};
