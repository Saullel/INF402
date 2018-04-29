#!/bin/bash

./jeu $1 

./minisat_static dimacs.out res_minisat.out

./resultat $1 res_minisat.out


if [ `diff res_minisat.out unsat` -ne 0 ]
then
	./resultat $1 res_minisat.out
fi