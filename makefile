CXXFLAGS=-DOS_CPP -fno-exceptions -fno-rtti
CXX=g++

# make CH=1 will use ccache
ifdef CH
CXX=ccache g++
endif

AR=ar
ss: ss.o libss.a
	$(CXX) -o $@ $^

ss.o: ss.cpp
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
