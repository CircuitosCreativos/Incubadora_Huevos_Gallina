void mostrar_temp(uint8_t columna, uint8_t fila, float temp) {
  lcd.clear();
  lcd.setCursor(columna, fila);
  lcd.print("Temp=");
  lcd.print(temp);
  lcd.print((char)223);
  lcd.print("C");
}
//-----------------------------------------------------------------

void mostrar_hum(uint8_t columna, uint8_t fila, String hum) {
  lcd.setCursor(columna, fila);
  lcd.print("Hum=");
  lcd.print(hum);
  lcd.print("%RH");
}
//-------------------------------------------------------------------

void mostrar_error(uint8_t columna, uint8_t fila) {
  lcd.clear();
  lcd.setCursor(columna, fila);
  lcd.print("Error sensor");
  lcd.setCursor(columna, fila+1);
  lcd.print("desconectado");
}

