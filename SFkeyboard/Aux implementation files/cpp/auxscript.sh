#!/bin/bash

dirInstancias='RealInstances'
#runs=10

for fator in 4 # se voce precisar variar algum argumento do codigo
do
	for arquivo in `ls ${dirInstancias}` #lista todos os arquivos na pasta que contem as instancias que vc quer rodar
	do
		MEDIA=0
		for iter in {1..10} #se for heuristica vc vai querer rodar mais de uma vez...
		do
			echo "Solving: " ${arquivo} ":" #output pra saber que instancia ta sendo rodada
			./exeSFkey ${dirInstancias}/${arquivo} charlists/Char_${arquivo} KeybInstances/b_matrix.txt
			MELHORCUSTO=`./exeSFkey ${dirInstancias}/${arquivo} charlists/Char_${arquivo} KeybInstances/b_matrix.txt | grep "Best Global Solution Cost" | cut -d " " -f 5` 
			MEDIA=$(($MEDIA + $MELHORCUSTO))
		done
		MEDIAFINAL=$(($MEDIA / 10))
		echo "Media Final Instancia $arquivo : $MEDIAFINAL"
	done
done
