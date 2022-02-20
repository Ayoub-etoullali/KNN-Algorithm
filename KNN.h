#ifndef _KNN
#define _KNN
#define NumATT 150
#define NumClasses 3
#define TestSetSize 0.4
#define N (int)(NumATT * (1 - TestSetSize))
//#define N 150
typedef struct Data_Pts
{
	int ID;
	double SL, SW, PL, PW, distance;
	int y;	   // type
	int y_hat; // il est vide (new type)
} Data_Pts;

typedef struct Table_T
{
	int n; // taille
	Data_Pts *Pts;
} Table_T;

enum Iris
{
	setosa,
	versicolor,
	virginica
};

typedef Data_Pts *Tab_Pts;
void CreateTablePts(Table_T *);
void PrintDPData(const Data_Pts *);
void EucDistance(Data_Pts *, const Data_Pts *);
void EucDistanceAll(Table_T *, const Data_Pts *);
void selectionSort(Table_T *);
void Split_TrainTest(Tab_Pts, Table_T *, Table_T *);
void KNN(Table_T *, Data_Pts *, int);
double Accuracy(Table_T *, Table_T *, int);

#endif