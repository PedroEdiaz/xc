BIN = cc
BKND = irxc
OBJ = \
	backend/$(BKND).o \
	op.o \
	ct.o \
	st.o \
	ps.o \
	tk.o \
	er.o \
	pp.o \
	cc.o

$(BIN): $(OBJ)
	$(CC) -o $@ $(OBJ)

st.o: st.c
	$(CC) -DIMPLEMENT -c -o $@ st.c

clean:
	rm $(BIN) $(OBJ)

