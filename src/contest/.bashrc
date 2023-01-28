alias c++='g++ -std=c++2a -fmax-errors=5 -DLOCAL -Wall -Wextra -O2 -s'

#Stress-testing
function test {
	SOL=$1
	CHECKER=$2
	for i in {1..100};
		do
			./gen.out > in && $CHECKER < in > ans && $SOL < in > out && diff -Zb out ans && echo "Test $i passed!!" || break;
		done
}
