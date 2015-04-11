#include <windows.h>
#include "Crypt.h"

Miracl precision = PRECISION; // MIRACLs precision

int main(int argc, char **argv)
{
	// Create structs for ease of use
	
	time_lock lock1(LOCK1_T, LOCK1_N, LOCK1_A, LOCK1_Ck); 	// 333375479997064832815324426714270780197
	time_lock lock2(LOCK2_T, LOCK2_N, LOCK2_A, LOCK2_Ck); 	// 223542132748929563812418364444413115531

	// Solve LOCK1
	
	CreateThread(0, 0, &SolveTimeLock, &lock1, 0, 0);

	while (lock1.key == 0) 		
		Sleep(1000);
		
	std::cout << "key: " << BigToString(lock1.key).c_str() << std::endl << std::endl;

	// Solve LOCK2
	
	CreateThread(0, 0, &SolveTimeLock, &lock2, 0, 0);

	while (lock2.key == 0)
		Sleep(1000);
		
	std::cout << "key: " << BigToString(lock2.key).c_str() << std::endl << std::endl;
	
	return 0;
}