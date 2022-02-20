
#include <stdio.h>
#include <stdlib.h>
#include "LoadCSV.h"

int main()
{
	Data_Pts Pts[NumATT], NewP;
	Table_T Train, Test;

	Train.n = N;
	Test.n = NumATT - N;
	CreateTablePts(&Train);
	CreateTablePts(&Test);

	int k, kmax = 15;
	double acc, OldAcc = 0;

	char Classe[3][20] = {
		"setosa",
		"versicolor",
		"virginica"};

	LoadCSV("Iris.csv", Pts);

	Split_TrainTest(Pts, &Train, &Test);
	// PrintDPData(&(Test.Pts[0]));
	// PrintDPData(&(Train.Pts[0]));

	// best K: 3
	for (int i = 1; i < kmax + 1; ++i)
	{
		acc = Accuracy(&Train, &Test, i);
		printf("accuracy (K=%d): %10f\n", i, acc);
		if (acc > OldAcc)
		{
			k = i;
			OldAcc = acc;
		}
	}

	printf("Best K: %d\n", k);

	system("pause");


	printf("Entrez la longueur du sepale (SL):  ");
	scanf("%lf", &(NewP.SL));
	puts("");

	printf("Entrez la largeur du sepale (SW):  ");
	scanf("%lf", &(NewP.SW));
	puts("");

	printf("Entrez la longueur du petale (PL):  ");
	scanf("%lf", &(NewP.PL));
	puts("");

	printf("Entrez la largeur du petale (PW):  ");
	scanf("%lf", &(NewP.PW));
	puts("");

	KNN(&Train, &NewP, k);

	printf("Prediction: %s\n", Classe[NewP.y_hat]);

	puts("");

	system("pause");
	return 0;
}