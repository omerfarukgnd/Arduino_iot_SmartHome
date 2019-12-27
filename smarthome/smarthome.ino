//hareket sensörü başlangıç

    int pirPin = 3; // PIR pin
    int ledPin = 4; // LED pin
    int deger = 0;

//hareket sensörü bitiş

//ısı-nem sensörü başlangıç

    #include <dht11.h> // dht11 kütüphanesini ekliyoruz.
    #define DHT11PIN 2 // DHT11PIN olarak Dijital 2"yi belirliyoruz.
    dht11 DHT11;

//ısı-nem sensörü bitiş

//mesafe-olcum sensörü başlangıc

    byte trigger = 10; // Sensörün Trigger bacağının bağlı olduğu pin
    byte echo = 11; // Sensörün Echo bacağının bağlı olduğu pin
    unsigned long sure; // Echo bacağının kac mikro saniyede aktif olduğunu saklayacak olan değişken
    double toplamYol;
    int aradakiMesafe;

//mesafe-olcum sensörü bitiş

//yakınlık sensörü bşlangıç

    int LED = 12; // Use the onboard Uno LED
    int isObstaclePin = 7; // This is our input pin
    int isObstacle = HIGH; // HIGH MEANS NO OBSTACLE

//yakınlık sensörü bitiş

//gaz ölçüm sensörü başlangıç

    int redLed = 15;
    int greenLed = 14;
    int buzzer = 13;
    int smokeA0 = A5;
    int sensorThres = 400;// Your threshold value

//gaz ölçüm sensörü bitiş

//alev sensörü başlangıç

    int buzzer = 8;
    int LED = 7;
    int flame_sensor = 1;//4 tü 1 yaptım
    int flame_detected;

//alev sensörü bitiş



void setup() {

      Serial.begin(9600); //Serial Porttan veri göndermek için baundrate ayarlanıyor.

  //hareket sensörü başlangıç

      pinMode(pirPin, INPUT); // PIR Pin'i giriş yapılıyor
      pinMode(ledPin, OUTPUT); // LED Pin'i çıkış yapılıyor

  //hareket sensörü bitiş

  //ısı-nem sensörü başlangıç

      Serial.println("Arduinoturkiye.com DHT11 Test Programi");

  //ısı-nem sensörü bitiş

  //mesafe-olcum sensörü başlangıç

      pinMode(trigger, OUTPUT); // Sensörün Trigger bacağına gerilim uygulayabilmemiz için OUTPUT yapıyoruz.
      pinMode(echo, INPUT); // Sensörün Echo bacağındaki gerilimi okuyabilmemiz için INPUT yapıyoruz.

  //mesafe-olcum sensörü bitiş

  //yakınlık sensörü başlangıc

      pinMode(LED, OUTPUT);
      pinMode(isObstaclePin, INPUT);

  //yakınlık sensörü bitiş

  //gaz ölçüm sensörü başlangıç

      pinMode(redLed, OUTPUT);
      pinMode(greenLed, OUTPUT);
      pinMode(buzzer, OUTPUT);
      pinMode(smokeA0, INPUT);

  //gaz ölçüm sensörü bitiş

  //alev sensörü başlangıç

      pinMode(buzzer, OUTPUT);
      pinMode(LED, OUTPUT);
      pinMode(flame_sensor, INPUT);

  //alev sensörü bitiş

}



void loop() {

  //hareket sensörü başlangıç

      deger = digitalRead(pirPin); // Dijital pin okunuyor
      Serial.println(deger); // Okunan değer seri porttan okunuyor.
      if (deger == HIGH)
        {digitalWrite(ledPin, HIGH); // Eğer okunan değer 1 ise LED yakılıyor.}
      else{digitalWrite(ledPin,LOW); // Eğer okunan değer 0 ise LED söndürülüyor.}

  //hareket sensörü bitiş

  //ısı-nem sensörü başlangıç

      Serial.println();// Bir satır boşluk bırakıyoruz serial monitörde.
      int chk = DHT11.read(DHT11PIN);
      // Sensörün okunup okunmadığını konrol ediyoruz.
      // chk 0 ise sorunsuz okunuyor demektir. Sorun yaşarsanız
      // chk değerini serial monitörde yazdırıp kontrol edebilirsiniz.

      // Sensörden gelen verileri serial monitörde yazdırıyoruz.
      Serial.print("Nem (%): ");
      Serial.println((float)DHT11.humidity, 2);

      Serial.print("Sicaklik (Celcius): ");
      Serial.println((float)DHT11.temperature, 2);

      Serial.print("Sicaklik (Fahrenheit): ");
      Serial.println(DHT11.fahrenheit(), 2);

      Serial.print("Sicaklik (Kelvin): ");
      Serial.println(DHT11.kelvin(), 2);

      // Çiğ Oluşma Noktası, Dew Point
      Serial.print("Cig Olusma Noktasi: ");
      Serial.println(DHT11.dewPoint(), 2);

  //ısı-nem sensörü bitiş

  //mesafe-olcum sensörü başlangıç

      /* Başlangıçta LOW durumda olan trigger bacağına gerilim uygulayıp ardından gerilimi keserek bir ses dalgası
      oluşturmuş oluyoruz. Bu işlem arasında 10 mikro saniye beklenmenin sebebi HC-SR04'ün en az 10 mikro saniyelik
      dalgalar ile çalışmasıdır. */
      digitalWrite(trigger, HIGH);
      delayMicroseconds(10);
      digitalWrite(trigger, LOW);

      // Dalga üretildikten sonra geri yansıyıp Echo bacağının HIGH duruma geçireceği süreyi pulseIn fonksiyonu ile kaydediyoruz.
      sure = pulseIn(echo, HIGH);

      // Aşağıda yapılan süre-mesafe dönüşüm işlemleri yazımızda açıklanmıştır.
      toplamYol = (double)sure*0.034;
      aradakiMesafe = toplamYol / 2;

      Serial.print("Ses dalgasinin geri donus suresi :");
      Serial.print(sure);
      Serial.println("mikro saniye");

      Serial.print("Ses dalgasinin toplam kat ettigi yol :");
      Serial.print(toplamYol);
      Serial.println("cm.");

      Serial.print("HC-SR04 ile karsisindaki yuzey arasindaki mesafe :");
      Serial.print(aradakiMesafe);
      Serial.println("cm.\n\n");

  //mesafe-olcum sensörü bitiş

  //yakınlık sensörü başlangıç

      isObstacle = digitalRead(isObstaclePin);
      if (isObstacle == LOW) {
          Serial.println("OBSTACLE!!, OBSTACLE!!");
          digitalWrite(LED, HIGH);
      }
      else {
          Serial.println("clear");
          digitalWrite(LED, LOW);
      }

  //yakınlık sensörü bitiş


  //gaz ölçüm sensör başlangıc

      int analogSensor = analogRead(smokeA0);
      Serial.print("Pin A0: ");
      Serial.println(analogSensor);
      // Checks if it has reached the threshold value
      if (analogSensor > sensorThres){
        digitalWrite(redLed, HIGH);
        digitalWrite(greenLed, LOW);
        tone(buzzer, 1000, 200);
      }
      else{
        digitalWrite(redLed, LOW);
        digitalWrite(greenLed, HIGH);
        noTone(buzzer);
      }

  //gaz ölçüm sensör bitiş

  //alev sensörü başlangıç

      flame_detected = digitalRead(flame_sensor);
      if (flame_detected == 1){
        Serial.println("Flame detected...! take action immediately.");
        digitalWrite(buzzer, HIGH);
        digitalWrite(LED, HIGH);
        delay(200);
        digitalWrite(LED, LOW);
        delay(200);
      }
      else{
        Serial.println("No flame detected. stay cool");
        digitalWrite(buzzer, LOW);
        digitalWrite(LED, LOW);
      }

  //alev sensörü bitiş

}
