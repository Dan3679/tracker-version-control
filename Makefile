# Compiler und Flags für modernes C++
CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -Isrc

# Ordnerstruktur
SRC_DIR = src
OBJ_DIR = obj

# Name des fertigen Programms (unter Linux ohne .exe)
TARGET = tracker-version-control 

# Alle Quelldateien im src-Ordner (main.cpp und taschenrechner.cpp)
SRCS = $(SRC_DIR)/main.cpp # $(SRC_DIR)/taschenrechner.cpp

# Generiert die Pfade für die Objektdateien im obj-Ordner automatisch:
# Aus 'src/main.cpp' wird 'obj/main.o'
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))

# Das Standard-Ziel, wenn du einfach nur "make" tippst
all: $(TARGET)

# Linken: Verbindet die .o Dateien zum fertigen Programm
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Kompilieren: Erstellt aus jeder .cpp Datei eine .o Datei
# Das '| $(OBJ_DIR)' sorgt dafür, dass der obj-Ordner zuerst erstellt wird, falls er fehlt
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Erstellt den obj-Ordner, falls er noch nicht existiert
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Aufräumen: Löscht das Programm und den obj-Ordner restlos
clean:
	rm -rf $(OBJ_DIR) $(TARGET)

# Verhindert Konflikte, falls es Dateien namens 'all' oder 'clean' geben sollte
.PHONY: all clean
