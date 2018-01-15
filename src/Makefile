GXX=g++
CFLAGS=-fPIC -fpermissive -c -w -std=c++11 -ISDK/ -Ilibjson/
BFLAGS=-fshort-wchar -shared
FLAGS=-DLINUX -D__LINUX__ -DNDEBUG -v -g0 -m32 -O2
BUILDDIR=build
BUILDFILE=SAMPSON.so

all:
	@echo '====================== Build started ======================='
	mkdir -p $(BUILDDIR)
	cd libjson; make SHARED=0
	@echo '====================== Compiling SDK ======================='
	$(GXX) $(FLAGS) $(CFLAGS) SDK/*.cpp
	@echo '===================== Compiling plugin ====================='
	$(GXX) $(FLAGS) $(CFLAGS) *.cpp
	@echo '====================== Building plugin ====================='
	$(GXX) $(FLAGS) $(BFLAGS) -o $(BUILDDIR)/$(BUILDFILE) *.o -Wl,--whole-archive libjson/libjson.a -Wl,--no-whole-archive
	@echo '====================== Build finished ======================'
	rm *.o
	@echo '====================== Clean finished ======================'

clean:
	@echo '====================== Clean started ======================='
	cd libjson; make clean
	rm *.o
	@echo '====================== Clean finished ======================'
