

struct DHT_result
{
  float tempF;
  float tempC;
  float humidity;
};

struct BME_result
{
  float temp;
  float humid;
  float pressure;
  
};

DHT_result read_DHT();
BME_result read_BME();
