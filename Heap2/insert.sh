echo "#THIS IS THE DATA FOR THE OPERATION INSERT" >"INSERT"		#creates the file INSERT and writes the data. > implies writing the data
echo "#inputs		average_time ">>"INSERT"			#appends the data . >> is to append
for i in 100 200 300 500 700 1000 2000 3000 5000 10000 20000 30000 50000 100000
do
	avg=0.0
	for j in {1..10}
	do 	
		./p $i						#after g++ -o p random.cpp
		./q 1 infile infile2				#after g++ -o q leftistheaps.cpp
		time=`tail -1 "outputfile"`			#gets the time from the output file
		avg=`echo "scale=7 ; $avg + $time" | bc`	#adds this time to avg
	done
avg=`echo "scale=7 ; $avg/10" | bc`				#divides the whole sum by 10
echo $i $avg							#prints the no. of inputs and avg time..
echo $i"		"$avg >> "INSERT"			#append the data >> implies append
done		
