#include "Crypt.h"

void printProgress(int i, int t)
{
	if (i % (t / 10) == 0)		
		std::cout << std::endl << i / (t / 10) << "X %   ";

	if (i % (t / 100) == 0)
		std::cout << ". ";
}

std::string BigToString(Big a)
{
	reinterpret_cast<miracl*>(&precision)->IOBASE = 10;

	char *out = new char[PRECISION + 1]();
	
	out << a;
	std::string str_out(out);
	
	delete[] out;
	
	return str_out;
}

unsigned long __stdcall SolveTimeLock(void *lpParam)
{
	time_lock *p_lock = reinterpret_cast<time_lock*>(lpParam);

#ifdef DBGPUZZLE
	Timer timer;

	std::cout << "n: " << BigToString(p_lock->n).c_str() << std::endl;
	std::cout << "a: " << BigToString(p_lock->a).c_str() << std::endl;
	std::cout << "ck: " << BigToString(p_lock->ck).c_str() << std::endl;
	std::cout << "t: " << p_lock->t << std::endl << std::endl;
	
	std::cout << "X  ->  0 1 2 3 4 5 6 7 8 9";
#endif

	Big tmp = p_lock->a;

	for (int i = 0; i < p_lock->t; i++)
	{
		tmp = (tmp * tmp) % p_lock->n;
#ifdef DBGPUZZLE
		printProgress(i, p_lock->t);
#endif
	}

	p_lock->key = (p_lock->ck - tmp) % p_lock->n;

#ifdef DBGPUZZLE
	std::cout << std::endl << "Final time: " << timer.elapsed() << std::endl;
#endif

	return 0;
}