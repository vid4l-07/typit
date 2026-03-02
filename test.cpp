#include <iostream>
#include <unistd.h>
#include <termios.h>
#include <sys/ioctl.h>

void obtenerTamano(int &filas, int &columnas) {
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    filas = w.ws_row;
    columnas = w.ws_col;
}

void moverCursor(int fila, int columna) {
    std::cout << "\033[" << fila << ";" << columna << "H";
}

void limpiarLinea() {
    std::cout << "\033[2K";
}

int main() {
    termios original, raw;
    tcgetattr(STDIN_FILENO, &original);
    raw = original;
    raw.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &raw);

    int filas, columnas;
    obtenerTamano(filas, columnas);

    int centroFila = filas / 2;
    int centroCol  = columnas / 2;

    std::string buffer;
    char c;

    while (true) {
        read(STDIN_FILENO, &c, 1);
		if (c < 32) continue;
        if (c == 'q') break;

        buffer += c;

        obtenerTamano(filas, columnas);
        centroFila = filas / 2;
        centroCol  = columnas / 2;

        // Determinar cuántos caracteres caben a la izquierda
        int maxVisible = centroCol - 1;

        std::string visible;
        if ((int)buffer.size() > maxVisible)
            visible = buffer.substr(buffer.size() - maxVisible);
        else
            visible = buffer;

        moverCursor(centroFila, 1);
        limpiarLinea();
        moverCursor(centroFila, centroCol - visible.size());
        std::cout << visible;

        moverCursor(centroFila, centroCol);
        std::cout.flush();
    }

    tcsetattr(STDIN_FILENO, TCSANOW, &original);
    std::cout << "\033[0m\n";
    return 0;
}
