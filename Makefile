PATH = /mnt/c/Program Files (x86)/Microsoft Visual Studio/2019/Community/VC/Tools/MSVC/14.22.27905/bin/Hostx64/x64

CC   = "$(PATH)/cl.exe"
LINK = "$(PATH)/link.exe"

DBG = "/mnt/c/Program Files (x86)/Windows Kits/10/Debuggers/x64/windbg.exe"

INC_PATH  = /I "C:/Program Files (x86)/Windows Kits/10/Include/10.0.18362.0/ucrt"
INC_PATH += /I "C:/Program Files (x86)/Microsoft Visual Studio/2019/Community/VC/Tools/MSVC/14.22.27905/include"

LIB_PATH  = /LIBPATH:"C:/Program Files (x86)/Microsoft Visual Studio/2019/Community/VC/Tools/MSVC/14.22.27905/lib/x64"
LIB_PATH += /LIBPATH:"C:/Program Files (x86)/Windows Kits/10/Lib/10.0.18362.0/um/x64"
LIB_PATH += /LIBPATH:"C:/Program Files (x86)/Windows Kits/10/Lib/10.0.18362.0/ucrt/x64"

BIN = ./bin
SRC = ./src

PDB = VM64.pdb
EXE = VM64.exe

CC_OPTIONS   = /Zi /D_HAS_EXCEPTIONS=0 /Fd:$(BIN)/$(PDB)
DBG_OPTIONS  = -y "C:/Users/Jas/Documents/VM64/bin/" -srcpath "C:/Users/Jas/Documents/VM64/src"
LINK_OPTIONS = /DEBUG /PDB:$(BIN)/$(PDB)

OBJECTS = $(patsubst $(SRC)/%.cpp, $(BIN)/%.o, $(wildcard $(SRC)/*.cpp))

$(BIN)/%.o: $(SRC)/%.cpp
	$(CC) $(CC_OPTIONS) $(INC_PATH) /Fo:$@ /c $^

$(EXE): $(OBJECTS)
	$(LINK) $(LINK_OPTIONS) $(LIB_PATH) $^ /OUT:$(BIN)/$@

debug:
	$(DBG) $(DBG_OPTIONS) $(BIN)/$(EXE)

.PHONY: clean
clean:
	/bin/rm -f $(BIN)/*.o
	/bin/rm -f $(BIN)/$(EXE)
	/bin/rm -f $(BIN)/$(PDB)
	/bin/rm -f $(BIN)/*.ilk
