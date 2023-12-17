BIN = cc
OBJ = \
	cg.o \
	st.o \
	ps.o \
	tk.o \
	er.o \
	cc.o

$(BIN): $(OBJ)
	$(CC) -o $@ $(OBJ)

clean:
	rm $(BIN) $(OBJ)

.SUFFIXES: .c .h

.c.o:
	$(CC) -c -o $@ $<
.h.o:
	$(CC) -DIMPLEMENT -c -o $@ $<
