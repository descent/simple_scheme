CXXFLAGS=-DOS_CPP -fno-exceptions -fno-rtti -std=c++11
CXX=g++

# make CH=1 will use ccache
ifdef CH
CXX=ccache g++
endif

ifdef RL # ReadLine
CXXFLAGS=-DRL -DOS_CPP -fno-exceptions -fno-rtti
CXXLDFLAGS=-lreadline
endif

AR=ar
ss: ss.o libss.a
	$(CXX) -o $@ $^ $(CXXLDFLAGS)

ss.o: ss.cpp s_eval.h cell.h token_container.h
	$(CXX) $(CXXFLAGS) -g -c $<

libss.a: s_eval.o cell.o token_container.o
	$(AR) rcs $@ $^

s_eval.o: s_eval.cpp cell.h
	$(CXX) $(CXXFLAGS) -g -c $<


#cell: cell.o
#	$(CXX) -o $@ $<
#
cell.o: cell.cpp cell.h
	$(CXX) $(CXXFLAGS) -g -c $<

token_container.o: token_container.cpp token_container.h
	$(CXX) $(CXXFLAGS) -g -c $<
clean:
	rm -rf *.o s_eval
