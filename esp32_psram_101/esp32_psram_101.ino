
void logMemory() {
  log_d("Used PSRAM: %d", ESP.getPsramSize() - ESP.getFreePsram());
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  //PSRAM Initialisation
  if (psramInit()) {
    Serial.println("\nThe PSRAM is correctly initialized");
  } else {
    Serial.println("\nPSRAM does not work");
  }
  log_d("Total heap: %d", ESP.getHeapSize());
  log_d("Free heap: %d", ESP.getFreeHeap());
  log_d("Total PSRAM: %d", ESP.getPsramSize());
  log_d("Free PSRAM: %d", ESP.getFreePsram());
  delay(1000);
  Serial.print("sizeof int = ");
  Serial.println(sizeof(int));
  //Create an integer
  int *var_int = (int *) ps_malloc(sizeof(int));
  *var_int = 42;
  Serial.println((String)"var_int = " + *var_int);
  log_d("var_int Total PSRAM: %d", ESP.getPsramSize());
  log_d("var_int Free PSRAM: %d", ESP.getFreePsram());
  free(var_int); //The allocated memory is freed.

  delay(1000);
  Serial.print("sizeof char = ");
  Serial.println(sizeof(char));

  //Create an uint8_t
  char *var_uint8_t = (char *) ps_malloc(sizeof(char));
  *var_uint8_t = 0xF2;
  Serial.println((String)"var_uint8_t = " + *var_uint8_t);
  log_d("var_uint8_t Total PSRAM: %d", ESP.getPsramSize());
  log_d("var_uint8_t Free PSRAM: %d", ESP.getFreePsram());
  free(var_uint8_t); //The allocated memory is freed.

  delay(1000);

  Serial.print("sizeof uint8_t = ");
  Serial.println(sizeof(uint8_t));
  //Create an uint8_t
  uint8_t *var_uint8 = (uint8_t *) ps_malloc(20000 * sizeof(uint8_t));
  *var_uint8 = 0xF2;
  Serial.println((String)"var_uint8 = " + *var_uint8);
  log_d("var_uint8 Total PSRAM: %d", ESP.getPsramSize());
  log_d("var_uint8 Free PSRAM: %d", ESP.getFreePsram());
  free(var_uint8); //The allocated memory is freed.

  //Create a float
  float *var_float = (float *) ps_malloc(sizeof(float));
  *var_float = 42.42;
  Serial.print("var_float = "); Serial.println(*var_float);
  log_d("var_float Total PSRAM: %d", ESP.getPsramSize());
  log_d("var_float Free PSRAM: %d", ESP.getFreePsram());
  free(var_float); //The allocated memory is freed.

  delay(1000);
  Serial.println("Create an array of 1000 integers");
  //Create an array of 1000 integers
  int n_elements = 1000;
  int *int_array = (int *) ps_calloc(n_elements, sizeof(int));
  //We access array values like a classic array
  int_array[0] = 42;
  int_array[42] = 42;
  int_array[999] = 42;
  Serial.println("dump arrays");
  for (int i = 0; i < n_elements; i++) {
    Serial.print(i);
    Serial.print("->");
    Serial.println(int_array[i]);
  }
  Serial.println("Done");
  log_d("var_float Total PSRAM: %d", ESP.getPsramSize());
  log_d("var_float Free PSRAM: %d", ESP.getFreePsram());
  logMemory();
  free(var_float); //The allocated memory is freed.
  logMemory();
  //Create an array of n_elements
  int available_PSRAM_size = ESP.getFreePsram();
  Serial.println((String)"PSRAM Size available (bytes): " + available_PSRAM_size);

  int *array_int = (int *) ps_malloc(n_elements * sizeof(int)); //Create an integer array of n_elements
  array_int[0] = 42;
  array_int[999] = 42; //We access array values like classic array

  int available_PSRAM_size_after = ESP.getFreePsram();
  Serial.println((String)"PSRAM Size available (bytes): " + available_PSRAM_size_after); // Free memory space has decreased
  int array_size = available_PSRAM_size - available_PSRAM_size_after;
  Serial.println((String)"Array size in PSRAM in bytes: " + array_size);

  //Delete array
  free(array_int); //The allocated memory is freed.
  Serial.println((String)"PSRAM Size available (bytes): " + ESP.getFreePsram());

}

void loop() {
  // put your main code here, to run repeatedly:

}
