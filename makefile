s_eval: s_eval.o
	g++ -o $@ $<

s_eval.o: s_eval.cpp
	g++ -c $<
clean:
	rm -rf *.o s_eval
