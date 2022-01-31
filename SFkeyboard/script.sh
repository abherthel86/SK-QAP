#!/bin/bash

dirInstancias='Instances'
#runs=10

for fator in 4 # se voce precisar variar algum argumento do codigo
do
	for arquivo in `ls ${dirInstancias}` #lista todos os arquivos na pasta que contem as instancias que vc quer rodar
	do
		#echo $arquivo
		idioma=`echo ${arquivo} | cut -d "_" -f 1 | cut -d "." -f 1` 
		
		#echo ${idioma}

		for iter in {1..10} #se for heuristica vc vai querer rodar mais de uma vez
		do
			echo "Solving: " ${arquivo} ":" #output pra saber que instancia ta sendo rodada
			./exeSFkey ${dirInstancias}/${arquivo} charlists/Char${idioma}.txt KeybLayout/b_matrix.txt BestSol/BestEnglish.txt
		done
	done
done
