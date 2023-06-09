include Makefile.inc

LIBSMUMPS = -L$(libdir) -lsmumps$(PLAT) -lmumps_common$(PLAT)
LIBDMUMPS = -L$(libdir) -ldmumps$(PLAT) -lmumps_common$(PLAT)
LIBCMUMPS = -L$(libdir) -lcmumps$(PLAT) -lmumps_common$(PLAT)
LIBZMUMPS = -L$(libdir) -lzmumps$(PLAT) -lmumps_common$(PLAT)
PROGRAMS = mumps_test smumps_test

all : $(PROGRAMS)
.SECONDEXPANSION:

# matrix_poisson: $$@.o
# 	$(FL) -o $@ $(OPTL) $@.o $(LIBDMUMPS) $(LORDERINGS) $(LIBS) $(LIBBLAS) $(LIBOTHERS)

# .SUFFIXES: .c .F .o
# .F.o:
# 	$(FC) $(OPTF) -I. -I$(topdir)/include -I$(topdir)/src $(INCS) -c $*.F $(OUTF)$*.o
# .c.o:
# 	$(CC) $(OPTC) $(CDEFS) -I. -I$(topdir)/include -I$(topdir)/src $(INCS) -c $*.c $(OUTC)$*.o


mumps_test: mumps_test.o matrix_loader.o mumps_check.o
	$(CC) -o $@ $(OPTL)  mumps_test.o matrix_loader.o mumps_check.o $(LIBDMUMPS) $(LORDERINGS) $(LIBS) $(LIBBLAS) $(LIBOTHERS)

smumps_test: smumps_test.o matrix_loader.o mumps_check.o
	$(CC) -o $@ $(OPTL)  smumps_test.o matrix_loader.o mumps_check.o $(LIBSMUMPS) $(LORDERINGS) $(LIBS) $(LIBBLAS) $(LIBOTHERS)

# c_example: $$@.o
	# $(CC) -o $@ $(OPTL) $@.o $(LIBDMUMPS) $(LORDERINGS) $(LIBS) $(LIBBLAS) $(LIBOTHERS)


mumps_test.o : 
	$(CC) $(OPTC) $(CDEFS) -I. -I$(topdir)/include -I$(topdir)/src $(INCS) -c $*.c $(OUTC)$*.o
	
smumps_test.o : 
	$(CC) $(OPTC) $(CDEFS) -I. -I$(topdir)/include -I$(topdir)/src $(INCS) -c $*.c $(OUTC)$*.o

matrix_loader.o : 
	$(CC) $(OPTC) $(CDEFS) -I. -I$(topdir)/include -I$(topdir)/src $(INCS) -c $*.c $(OUTC)$*.o
	
mumps_check.o : 
	$(CC) $(OPTC) $(CDEFS) -I. -I$(topdir)/include -I$(topdir)/src $(INCS) -c $*.c $(OUTC)$*.o

# c_example.o : 
	# $(CC) $(OPTC) $(CDEFS) -I. -I$(topdir)/include -I$(topdir)/src $(INCS) -c $*.c $(OUTC)$*.o


clean : 
	$(RM) *.o $(PROGRAMS)
