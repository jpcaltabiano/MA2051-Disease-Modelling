all: model

model: test-model-script.o
	g++ -g test-model-script.o -o model

test-model-script.o: test-model-script.cpp
	g++ -c -g test-model-script.cpp

clean:
	rm -f *.o model output.csv