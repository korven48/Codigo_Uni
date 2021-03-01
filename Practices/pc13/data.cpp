#include <iostream>
#include <string>
using namespace std;

// Declare data structures here...
enum tCategory
{
	LowCost,
	Tourist,
	Businessor,
	FirstClass
};

struct tSeat
{
	int row;
	char letter;
	tCategory category;
	string passenger;
};

const int MAX_SEATS = 100;
typedef tSeat seatArr[MAX_SEATS];

struct tPlane
{
	string codeName;
	seatArr seats;
};

const int MAX_PLANES = 10;
typedef tPlane planeArr[MAX_PLANES];

struct tFleet
{
	string compName;
	planeArr planes;
};

enum tStatus
{
	Scheduled,
	Boarding,
	Departed,
	Delayedor,
	Canceled
};

struct tFlight
{
	string destination;
	string code;
	tStatus status;
};

const int MAX_FLIGHTS = 50;
typedef tFlight flightArr[MAX_FLIGHTS];

struct tAirport
{
	string name;
	flightArr flights;
};

int main()
{

	return 0;
}