#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LoadCsv.h"
#include "KNN.h"

#define MaxLineLen 200

void LoadCSV(char FName[20], Data_Pts *Pts)
{
	FILE *in_file = fopen(FName, "r");
	char line[MaxLineLen];
	if (in_file == NULL)
	{
		puts("Error! Could not open file");
		exit(-1);
	}
	char *tocken;
	fgets(line, MaxLineLen, in_file);
	/*tocken = strtok(line, ",");
	//columns
	while( tocken != NULL ) {
		printf("%-15s",tocken );
		tocken = strtok(NULL, ",");
	}*/
	// printf("Data: \n");
	int i = 0;
	char *c;
	while (fgets(line, MaxLineLen, in_file))
	{
		int j = 0;
		tocken = strtok(line, ","); // extraire, un à un, tous les élèments syntaxiques d'une chaine de caractère
		while (tocken != NULL)
		{
			// printf("%-15s",tocken );
			switch (j)
			{
			case 0:
				Pts[i].ID = strtod(tocken, &c); // transformer une chaine de caractères, contenant la représentation textuelle d'un nombre flottant en une donnée typée double
				break;
			case 1:
				Pts[i].SL = strtod(tocken, &c);
				break;
			case 2:
				Pts[i].SW = strtod(tocken, &c);
				break;
			case 3:
				Pts[i].PL = strtod(tocken, &c);
				break;
			case 4:
				Pts[i].PW = strtod(tocken, &c);
				break;
			case 5:

				if (strstr(tocken, "setosa")) // recherche la 1ère occurance d'une chaine de caractères
					Pts[i].y = setosa;
				else if (strstr(tocken, "versicolor"))
					Pts[i].y = versicolor;
				else if (strstr(tocken, "virginica"))
					Pts[i].y = virginica;

				break;
			}
			tocken = strtok(NULL, ",");
			j++;
		}
		i++;
	}
	fclose(in_file);
}
