/*
	Course: CPSC 121	Thursday
	Project: No.11 Part 2
	Date: April 16 2015
	Professor: Ray Ahmadia
	Purpose: Use multiple kinds of sorting to sort months of the year
*/
#include <iostream>
#include <sstream>

using namespace std;

class SORT{
private:
	string blank[12];
public:
	template <class T>
	void BubbleSort(T *blank, int n){ // bubble sorting algorithm
		for (int i = 0; i < n-1; ++i)
		{
			for (int j = 0; j < n-1-i; ++j)
			{
				if ( blank[j] > blank[j+1] ){
					string temp = blank[j]; blank[j]= blank[j+1];
					blank[j+1] = temp;
				}
			}
		}
	}
	template <class T> 
	void SelectionSort(T blank[], int n){ //selection sort
		string min; int k;
		for (int i = 0; i < n-1; ++i)
		{
			k= i; min= blank[k];
			for (int j = i+1; j < n; ++j)
			if( blank[j] < min ){
					k=j; min = blank[k]; 
				}
				blank[k] = blank[i]; blank[i]=min;
			
		}
	}
	template <class T> 
	void HeapSort(T blank[], int n){ //heap sort
		string x;
		for(int k =n/2-1; k>=0; k--)
			shift(blank,k,n);
		while(--n>0){
			x = blank[0]; blank[0] = blank[n]; blank[n] = x;
			shift(blank,0,n);
		}
	}
	template <class T> 
	void shift(T blank[], int k, int n ){ //shift for heap sort
		int i, j;
		string x;
		i=k; x=blank[i];
		while( (j=2*i+1 )< n ){
			if(j<n-1 && blank[j] < blank[j+1] ) j++;
			if (x>= blank[j]) break;
			blank[i]=blank[j]; i=j;
		}
		blank[i]=x;
	}
	

	template <class T> 
	void Display(T blank[], int n){ //display function
		for (int i = 0; i < 12; ++i)
		{
			cout << blank[i] << " ";
		}
		cout << endl;
	}


};

int main(){ // run everything on three strings
	string one[12]={"JAN","FEB", "MAR", "APR", "MAY", "JUN", "JUL", "AUG", "SEPT", "NOV", "DEC"};
	string two[12]={"JAN","FEB", "MAR", "APR", "MAY", "JUN", "JUL", "AUG", "SEPT", "NOV", "DEC"};
	string three[12]={"JAN","FEB", "MAR", "APR", "MAY", "JUN", "JUL", "AUG", "SEPT", "NOV", "DEC"};
	

	SORT p;
	p.BubbleSort(one,12); p.SelectionSort(two,12); p.HeapSort(three,12); 
	p.Display(one, 12); p.Display(two,12); p.Display(three,12);
/*-------------------------output---------------------
 APR AUG DEC FEB JAN JUL JUN MAR MAY NOV SEPT 
 APR APR APR APR AUG AUG AUG AUG DEC NOV SEPT 
 APR AUG DEC FEB JAN JUL JUN MAR MAY NOV SEPT 
*/
