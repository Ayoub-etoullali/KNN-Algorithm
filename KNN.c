#include <stdio.h>
#include <stdlib.h>
#include "KNN.h"
#include <math.h>
#define max(a, b) \
	({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a > _b ? _a : _b; })

void CreateTablePts(Table_T *PtrTab)
{
	PtrTab->Pts = (Data_Pts *)malloc(PtrTab->n * sizeof(Data_Pts));
}

void PrintDPData(const Data_Pts *P)
{
	printf("ID: %d\n", P->ID);
	printf("SL: %f\n", P->SL);
	printf("SW: %f\n", P->SW);
	printf("PL: %f\n", P->PL);
	printf("PW: %f\n", P->PW);
	printf("y: %d\n", P->y);
}
void EucDistance(Data_Pts *P, const Data_Pts *NewP)
{
	P->distance = sqrt(pow(P->SL - NewP->SL, 2) + pow(P->SW - NewP->SW, 2) + pow(P->PL - NewP->PL, 2) + pow(P->PW - NewP->PW, 2));
}
void EucDistanceAll(Table_T *P, const Data_Pts *NewP)
{
	for (int i = 0; i < P->n; ++i)
		EucDistance(&(P->Pts[i]), NewP);
}

void swap(Data_Pts *xp, Data_Pts *yp)
{
	Data_Pts temp = *xp;
	*xp = *yp;
	*yp = temp;
}

void selectionSort(Table_T *arr)
{
	int i, j, min_idx;
	for (i = 0; i < arr->n - 1; i++)
	{
		min_idx = i;
		for (j = i + 1; j < arr->n; j++)
			if (arr->Pts[j].distance < arr->Pts[min_idx].distance)
				min_idx = j;
		swap(&arr->Pts[min_idx], &arr->Pts[i]);
	}
}

void Split_TrainTest(Tab_Pts Pts, Table_T *Train, Table_T *Test)
{
	int i, j, k, l1 = 0, l2 = 0;

	for (j = 0; j < NumATT; j += (NumATT / NumClasses))
	{
		for (i = 0; i < (NumATT / NumClasses) * (1 - TestSetSize); ++i, ++l1)
			Train->Pts[l1] = Pts[j + i];

		for (k = 0; k < (NumATT / NumClasses) * TestSetSize; ++k, ++l2)
			Test->Pts[l2] = Pts[j + i + k];
	}
}

void KNN(Table_T *Data, Data_Pts *NewP, int k)
{
	int a = 0, b = 0, c = 0, i;
	EucDistanceAll(Data, NewP);
	selectionSort(Data);
	for (i = 0; i < k; ++i)
	{
		// printf("Distance with point %d: %f | Label: %d\n",Pts[i].ID,Pts[i].distance,Pts[i].y );
		a += Data->Pts[i].y == 0;
		b += Data->Pts[i].y == 1;
		c += Data->Pts[i].y == 2;
	}
	if (max(max(a, b), c) == a)
		NewP->y_hat = setosa;
	else if (max(max(a, b), c) == b)
		NewP->y_hat = versicolor;
	else if (max(max(a, b), c) == c)
		NewP->y_hat = virginica;
}

double Accuracy(Table_T *Train, Table_T *Test, int k)
{

	double acc = 0;

	for (int i = 0; i < Test->n; ++i)
	{
		KNN(Train, &(Test->Pts[i]), k);
		if (Test->Pts[i].y_hat == Test->Pts[i].y)
			acc++;
	}
	return acc / Test->n;
}