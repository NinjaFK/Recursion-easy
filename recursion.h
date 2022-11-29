/*
	Name: Brian Nieh, 5008139573, 1005, 7
	Description: Recursion
	Input: Implementing four recursive function
	Output: Result of recursive functions
*/
#ifndef RECURSION_H
#define RECURSION_H
#include <iostream>
#include <string>
using namespace std;
const int WIDTH = 4;
const int HEIGHT = 5;
// Doll class for the findCenter function. This represents a Matryoshka doll with another Doll inside it
// A doll containing no other Dolls will have an innerDoll of nullptr
class Doll
{
	string name;
	unsigned int id;
	static unsigned int count;
	Doll *innerDoll;

public:
	Doll *getInnerDoll() const { return innerDoll; }
	void printDoll() { cout << "Doll: " << id << " " << name << endl; }

	Doll(string name, Doll *inside)
	{
		this->name = name;
		innerDoll = inside;
		id = count;
		count++;
	}
};
//---------------------------- Recursive function implementations ----------------------------
int power(const int &base, int pow)
{
	// Check for the base case; anything to the 0th is trivial to solve
	// Otherwise, recursively take the power of a base with a lower pow
	if (pow == 0)
	{
		return 1;
	}
	return base * power(base, pow - 1);
}
int findBiggestNumber(int arr[], int index)
{
	// Try to find the biggest number in the array. If a base case is hit where the biggest value is trivial,
	// return the result without recursing. Else, try to find the biggest number in the array ending at the index
	// to the left of the current one. Then return the biggest value between that value and the one at the current index.
	// Try not to do more than one recursive call here.
	//(HINT Try using a variable to store the result of your recursive case)
	int result;
	if (index == 0)
	{
		return arr[0];
	}
	// this is my recursive call
	result = findBiggestNumber(arr, index - 1);
	if (arr[index] > result)
	{
		result = arr[index];
	}
	return result;
}
void findTheX(char grid[HEIGHT][WIDTH], const int &x, const int &y)
{
	// If the char at the current spot is an X, then we solved it
	// Print the message andmark the spot as a O now to make sure we don't find it twice
	// Else if the char is an 'O', it is either a wall or has been verified
	// to not contain the X
	if (grid[y][x] == 'X')
	{
		cout << "Found the X at (" << x << "," << y << ")\n";
		grid[y][x] = 'O';
		return;
	}
	// i dont use else if can clang
	if (grid[y][x] != 'O')
	{
		// If this is not the X or an O, mark this spot as a O then recursively try the right, left, above
		// and below spots only if each ear in bounds of the array
		// down
		grid[y][x] = 'O';
		if (x < WIDTH - 1)
		{
			findTheX(grid, x + 1, y);
		}
		// right
		if (y < HEIGHT - 1)
		{
			findTheX(grid, x, y + 1);
		}
		// up
		if (x > 0)
		{
			findTheX(grid, x - 1, y);
		}
		// left
		if (y > 0)
		{
			findTheX(grid, x, y - 1);
		}
	}
	// You can assume the grid always has dimensions of the consts HEIGHT and WIDTH
	// by the parameter declaration above and that the X is always findable. Consider
	// that with row major arrays, y should come before x when accessing, as well
}
void findCenter(Doll *doll)
{
	// Try to find the center most Doll in a stack of Matryoshka dolls.
	// Print the doll we are currently opening using it's printDoll function and then open the next one
	// If this is the inner most Doll, don't recurse.
	// prints
	doll->printDoll();
	// the if statment uses null as false
	if (doll->getInnerDoll())
	{
		// sets the next
		findCenter(doll->getInnerDoll());
	}
}
#endif