
all:	t3Solver.cpp BoardState.cpp TreeNode.cpp
	g++ -std=c++11 -c BoardState.cpp
	g++ -std=c++11 -c TreeNode.cpp	
	g++ -std=c++11 -c t3Solver.cpp	
boardstate:	BoardState.cpp
	g++ -std=c++11 -c BoardState.cpp
treenode:	TreeNode.cpp	
	g++ -std=c++11 -c TreeNode.cpp
tester:	BoardState.cpp tester.cpp TreeNode.cpp t3Solver.cpp
	g++ -std=c++11 -o tester tester.cpp BoardState.cpp TreeNode.cpp t3Solver.cpp
run: tester
	./tester ${ARGS}	
