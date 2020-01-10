
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>


void GreedyColoring();

typedef struct Interval { // each interval is a struct with 2 numbers //
	int low;
	int high;
}interval;

typedef struct Graph {
	int color;
	int deg;
}graph;

void main()
{
	GreedyColoring();
}

void GreedyColoring()
{
	int k, i, j;
	int color = 1;
	int countGedges = 0, countGcompedges = 0;
	printf("Please input k, which will be the number of your intervals:\n");
	scanf_s("%d", &k); // getting the interval's family size from the user //

	interval *arr; // arr-array for the intervals //
	arr = (interval*)calloc(k, sizeof(interval));
	assert(arr);

	graph *Garr; // Garr-array for the vertex of the graph //
	Garr = (graph*)calloc(k, sizeof(graph));
	assert(Garr);

	int* colorarray;
	colorarray = (int*)calloc(k + 1, sizeof(int));// colorarray - array for color availability-->setting all values to 0 //
	assert(colorarray);

	printf("You will be now asked to insert a family of %d intervals:\n", k);

	for (i = 0; i < k; i++) // enter your intervals //
	{
		printf("%dth Interval:\n", i + 1);
		scanf_s("%d", &(arr[i]).low); // enter your first number of your i-th interval //
		scanf_s("%d", &(arr[i]).high); // enter your second number of your i-th interval //
	}
	printf("The Intervals family is:\n");

	for (i = 0; i < k; i++) // prints the family in one row //
	{
		printf("[%d,%d]", arr[i].low, arr[i].high);
		if (i != k - 1)
			printf(","); // print "," between intervals only if it is not the last interval //
	}
	printf("\n");

	for (i = 0; i < k - 1; i++) // sorting the array, by the lowest first number of the interval to the highest first number of the interval , //
								// if they are equal, sort it by the second number of the interval ascending //
	{
		for (j = 0; j < k - 1; j++)
		{
			if (arr[j].low > arr[j + 1].low || (arr[j].low == arr[j + 1].low && arr[j].high > arr[j + 1].high)) // swap only if the first number of interval in arr[j] bigger than the first number of interval in arr[j+1] //
			{
				interval temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}

	for (i = 0; i < k - 1; i++) // checking how many edges there are in the graph //
	{
		for (j = i + 1; j < k; j++)
		{
			if (arr[i].low == arr[j].low || arr[i].high >= arr[j].low || (arr[i].high <= arr[j].high && arr[i].high >= arr[j].low))
			{
				countGedges++; // there is an edge between the intervals(vertex) //
				Garr[i].deg++; // "i" vertex has an edge //
				Garr[j].deg++; // "j" vertex has an edge //	
			}
		}
	}

	int maxdeg = Garr[0].deg; // variable for the maximum degree of G //
	int mindeg = Garr[0].deg; // variable for the minimum degree of G //

	for (i = 1; i < k; i++) // checking for the maximum degree and minimum degree in the graph //
	{
		if (Garr[i].deg >= maxdeg)
			maxdeg = Garr[i].deg;
		else if (Garr[i].deg <= mindeg)
			mindeg = Garr[i].deg;
	}


	for (i = 0; i < k; i++) // all vertex's color are set to '1' primarily //
	{
		Garr[i].color = color;
	}


	for (i = 1; i < k; i++) // graph coloring //
	{
		for (j = i - 1; j >= 0; j--)
		{
			if (arr[j].low == arr[i].low || arr[j].high >= arr[i].low || (arr[j].high <= arr[i].high && arr[j].high >= arr[i].low))
			{
				colorarray[Garr[j].color]++; // the color of vertex 'j' won't be available //
			}

			for (int t = 1; t < k + 1; t++) // searching for the proper and available color //
			{
				if (colorarray[t] == 0)
				{
					Garr[i].color = t; // assign the color for vertex 'i' only if it's available (value=0) //
					break;
				}
			}

		}
		for (int m = 1; m < k + 1; m++) // resetting all the color's values to 0 //
		{
			colorarray[m] = 0;
		}

	}

	for (i = 0; i < k; i++)
	{
		if (color < Garr[i].color) // searching for the biggest vertex's color number in the graph //
			color = Garr[i].color;
	}

	for (i = 0; i < k; i++)
	{
		colorarray[Garr[i].color]++; // count how many times we have each number of the coloring //
	}

	printf("G Edges = %d\n", countGedges);
	printf("Maximum Degree of G = %d\n", maxdeg); // print the max degree of G //
	printf("Minimum Degree of G = %d\n", mindeg); // print the min degree of G //
	printf("Chromatic Number of G = %d\n", color);
	countGcompedges = (k*(k - 1) / 2) - countGedges; // G's complement has the number of possible edges(k*(k-1)/2) minus the edges in G itself //
	printf("G's Complement Edges = %d\n", countGcompedges);

	if (countGcompedges != 0) // we will check the case of a "k family" GRAPH(all vertex connected to each others) //
	{
		printf("Maximum Degree of G's Complement = %d\n", k - 1 - mindeg);
		printf("Minimum Degree of G's Complement = %d\n", k - 1 - maxdeg);
	}
	else
	{
		printf("Maximum Degree of G's Complement = 0\n"); //this is the case of a "k family" graph 
		printf("Minimum Degree of G's Complement = 0\n"); //in which all vertex connected to each others//
	}

	int m = 1; // m will by whom we want to color the graph //
	printf("Optional Coloring: ");

	while (m <= color) // printing the optional coloring, from '1' until the highest color(chromatic number) //
	{
		printf("{");
		for (i = 0; i < k; i++)
		{
			if (Garr[i].color == m)
			{
				colorarray[m]--; // reduces the number of times the color has been shown //
				printf("[%d,%d]", arr[i].low, arr[i].high); // print all intervals with color 'm'
				if (colorarray[m] != 0)
					printf(","); // print ',' between the intervals, nut not after the last interval printed out //
			}
		}
		printf("} = %d", m);
		if (m != color)
		{
			printf(", ");
		}
		m++;
	}
	printf("\n");
	free(colorarray); // free the array //
	free(Garr); // free the array //
	free(arr); // free the array //

	system("pause");
}
