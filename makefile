CXXFLAGS=-DOS_CPP
CXX=g++
ss: ss.o libss.a
	g++ -o $@ $^

ss.o: ss.cpp
	g++ $(CXXFLAGS) -g -c $<

libss.a: s_eval.o cell.o token_container.o
	ar rcs $@ $^

s_eval.o: s_eval.cpp cell.h
	g++ $(CXXFLAGS) -g -c $<


#cell: cell.o
#	g++ -o $@ $<
#
cell.o: cell.cpp cell.h
	g++ $(CXXFLAGS) -g -c $<

token_container.o: token_container.cpp token_container.h
	g++ $(CXXFLAGS) -g -c $<
clean:
	rm -rf *.o s_eval
