BIN = cc
BKND = irxc
OBJ = \
	backend/$(BKND).o \
	op.o \
	ct.o \
	va.o \
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

