CC = gcc

# Includes
CFLAGS = -Iutil -Isrc -Isrc/engine -Isrc/assets/shaders

LIBS = -ld3d11 -ldxgi -ldxguid -lgdi32 -luser32 -lshell32 -lole32

SRC = src/main.c src/engine/renderer.c

null_engine: $(SRC)
	@$(CC) $(CFLAGS) $(SRC) -o null_engine $(LIBS)

run: null_engine
	@./null_engine

clean:
	@rm null_engine.exe