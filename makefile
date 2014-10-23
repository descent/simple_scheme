s_eval: s_eval.o cell.o token_container.o
	g++ -o $@ $^

s_eval.o: s_eval.cpp cell.h
	g++ -g -c $<


#cell: cell.o
#	g++ -o $@ $<
#
cell.o: cell.cpp cell.h
	g++ -g -c $<

token_container.o: token_container.cpp token_container.h
	g++ -g -c $<
clean:
	rm -rf *.o s_eval
