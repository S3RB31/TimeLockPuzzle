#/usr/bin/python
# This code was taken from: 
# http://de.scribd.com/doc/32307363/Anti-Emulation-through-TimeLock-puzzles / Appendix A (at the very end)
# All rights to their respective owners
# Requires Python Cryptography Toolkit
# http://www.amk.ca/python/code/crypto.html 

from Crypto.Util import randpool
from Crypto.Util import number
import math
import sys

def makepuzzle(t):
	# Init PyCrypto RNG
	rnd = randpool.RandomPool()
	
	# Generate 512-bit primes
	
	p = number.getPrime(512, rnd.get_bytes)
	q = number.getPrime(512, rnd.get_bytes)
	
	n = p * q
	phi = (p - 1) * (q - 1)
	
	# AES key --- this is what we will encode into the puzzle solution
	key = number.getRandomNumber(128, rnd.get_bytes)
	
	# Need a random starting value for the puzzle, between 1 and n
	a = number.getRandomNumber(4096, rnd.get_bytes)
	a = a % n
	
	# *** puzzle shortcut ***
	# fast way to compute (a^2)^t (if you know phi)
	e = pow(2, t, phi)
	b = pow(a, e, n)
	
	# So b = (a^2)^t, and we encode the key into this solution
	ck = (key + b) % n
	
	return (key, (n, a, t, ck))
	
def solvepuzzle((n, a, t, ck)):
	tmp = a
	sys.stdout.write("Working")
	for i in range(t):
		tmp = pow(tmp, 2, n)
		if i % 100000 == 0:
			sys.stdout.write(".")
	print ""
	return (ck - tmp) % n

def main():
	# Generate a new puzzle requiting 100000 modular squarings to solve
	(key, puzzle) = makepuzzle(1000000)
	
	# Use this key to encrypt a payload
	print "key = " + str(key)
	
	print ""
	print "puzzle = " + str(puzzle)
	print ""
	
	# Recover the key
	solution = solvepuzzle(puzzle)
	print "solution = " + str(solution)
	
if __name__ == "__main__":
	main()