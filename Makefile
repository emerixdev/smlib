test:
	g++ -o app.out test.cpp  --std=c++23
ctest:
	g++ -o ctest.out complete_test.cpp  --std=c++23
particles:
	g++ -o examples/particles.out  examples/particles.cpp --std=c++23
