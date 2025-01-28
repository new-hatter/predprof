void setup() {
   pinMode(11, OUTPUT); // объявляем пин 10 как выход
   Serial.begin (9600); // подключаем монитор порта
  pinMode(9, OUTPUT); // назначаем trigPin, как выход
  pinMode(8, INPUT); // назначаем echoPin, как вход
}
void loop() {
  int duration, cm; // назначаем переменную "cm" и "duration" для показаний датчика
  digitalWrite(9, LOW); // изначально датчик не посылает сигнал
  delayMicroseconds(2); // ставим задержку в 2 ммикросекунд

  digitalWrite(9, HIGH); // посылаем сигнал
  delayMicroseconds(10); // ставим задержку в 10 микросекунд
  digitalWrite(9, LOW); // выключаем сигнал
  duration = pulseIn(8, HIGH); // включаем прием сигнала
  cm = duration / 58; // вычисляем расстояние в сантиметрах

  Serial.print(cm); // выводим расстояние в сантиметрах
  Serial.println("cm");

  delay(1000); // ставим паузу в 1 секунду

  if (cm = 3 ){
    tone (10, 600); // включаем на пьезодинамик 600 Гц
    delay(1000); // ждем 1 секунду
    tone(10, 900); // включаем на пьезодинамик 900 Гц
    delay(1000); // ждем 1 секунду
    noTone(10); // отключаем пьезодинамик на пин 11
    delay(1000); // ждем 1 секунду
  }
}

