#include <LedControl.h>

// DIN, CLK, CS(LOAD), cantidad de MAX7219
LedControl lc = LedControl(13, 11, 12, 1);

const int MAS_LOCAL   = 2;
const int MENOS_LOCAL = 3;
const int MAS_VIS     = 4;
const int MENOS_VIS   = 5;

int local = 0;
int visitante = 0;

bool estadoML_ant  = HIGH;
bool estadoMEL_ant = HIGH;
bool estadoMV_ant  = HIGH;
bool estadoMEV_ant = HIGH;
void mostrarMarcador()
{
  lc.setDigit(0, 0, local / 10, false);
  lc.setDigit(0, 1, local % 10, false);

  lc.setDigit(0, 2, visitante / 10, false);
  lc.setDigit(0, 3, visitante % 10, false);
}

void setup()
{
  pinMode(MAS_LOCAL, INPUT_PULLUP);
  pinMode(MENOS_LOCAL, INPUT_PULLUP);
  pinMode(MAS_VIS, INPUT_PULLUP);
  pinMode(MENOS_VIS, INPUT_PULLUP);

  lc.shutdown(0, false);
  lc.setIntensity(0, 8);
  lc.clearDisplay(0);

  mostrarMarcador();
}

void loop()
{
  bool ML  = digitalRead(MAS_LOCAL);
  bool MEL = digitalRead(MENOS_LOCAL);
  bool MV  = digitalRead(MAS_VIS);
  bool MEV = digitalRead(MENOS_VIS);

  // Local +
  if (estadoML_ant == HIGH && ML == LOW)
  {
    if (local < 99)
      local++;

    mostrarMarcador();
  }

  // Local -
  if (estadoMEL_ant == HIGH && MEL == LOW)
  {
    if (local > 0)
      local--;

    mostrarMarcador();
  }

  // Visitante +
  if (estadoMV_ant == HIGH && MV == LOW)
  {
    if (visitante < 99)
      visitante++;

    mostrarMarcador();
  }

  // Visitante -
  if (estadoMEV_ant == HIGH && MEV == LOW)
  {
    if (visitante > 0)
      visitante--;

    mostrarMarcador();
  }

  estadoML_ant  = ML;
  estadoMEL_ant = MEL;
  estadoMV_ant  = MV;
  estadoMEV_ant = MEV;

  delay(20); // antirrebote básico
}
