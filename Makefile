
BIN = cc
OBJ = \
	cg.o \
	ct.o \
	pp.o \
	st.o \
	ps.o \
	tk.o \
	er.o \
	cc.o

$(BIN): $(OBJ)
	$(CC) -o $@ $(OBJ)

st.o: st.c
	$(CC) -DIMPLEMENT -c -o $@ st.c

clean:
	rm $(BIN) $(OBJ)

