CFLAGS=/nologo /W4 /EHsc /Za /I.  

all: tema1.exe

build: tema1.exe

tema1.exe: tema1.obj bucket_interface.obj hashtable_interface.obj
	link /nologo /out:tema1.exe tema1.obj bucket_interface.obj hashtable_interface.obj hash.lib

tema1.obj: tema1.c
	cl $(CFLAGS) /c /Fe$@ $**

bucket_interface.obj: bucket_interface.c
	cl $(CFLAGS) /c /Fe$@ $**

hashtable_interface.obj: hashtable_interface.c
	cl $(CFLAGS) /c /Fe$@ $**

clean:
	del *.obj *.exe
