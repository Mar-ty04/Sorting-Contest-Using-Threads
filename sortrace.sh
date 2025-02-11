############################################################
# this file should be called sortrace.sh
# it must have execute privilege set to run
# run it as a background task like this:
# $ rm sortrace.log # start with fresh log file
# $ sortrace.sh >> sortrace.log & # run in the background
############################################################
echo "=======Start======="
whoami
date
echo My machine has this many processors
nproc # this is for Windows machines
#sysctl -n hw. Ncpu # this is for Mac machines
echo Generating 1000000 random numbers
sleep 1
./generate 1000000 -1000000 1000000 # you have to write generate.cpp
sleep 1
echo Starting system sort
sleep 1
{ time sort -n numbers.dat > systemsort.out; } 2>> sortrace.log # this line is for Windows
#{ time sort -n numbers.dat > systemsort.out; } 2>&1>> sortrace.log # modification for Mac
sleep 1
echo Starting my sort
sleep 1
{ time ./mysort numbers.dat mysort.out; } 2>> sortrace.log # this line is for Windows
#{ time ./mysort numbers.dat mysort.out; } 2>&1>> sortrace.log # modification for Mac computers
sleep 1
ls -l systemsort.out
ls -l mysort.out
echo Comparing systemsort.out to mysort.out
diff systemsort.out mysort.out 2>> sortrace.log
echo All done with diff compare
echo "=======End======="
date