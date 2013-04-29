
#pragma once

struct array{
	int nrWindows;
	int *A;
};

struct window{
	int windowID;
	int weightMin;
	int weightMax;
	int Q;
	int K;
	int packages; //numarul de pachete din stiva ghiseului
	int grams; //numarul de grame din stiva ghiseului
};

struct person{
	int ID;
	int packWeight;
};
