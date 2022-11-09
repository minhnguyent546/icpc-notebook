alias cpp='g++ -std=c++17 -fmax-errors=5 -DLOCAL -Wall -Wextra'

#Stress-testing
function test {
	SOL=$1
	CHECKER=$2
	for i in {1..100};
		do
			./gen.out > in && ./"$CHECKER.out" < in > ans && ./"$SOL.out" < in > out && diff -Z out ans && echo "Test $i passed!!" || break;
		done
}
