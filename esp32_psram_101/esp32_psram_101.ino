
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

  //Create an integer
  int *var_int = (int *) ps_malloc(sizeof(int));
  *var_int = 42;
  log_d("var_int Total PSRAM: %d", ESP.getPsramSize());
  log_d("var_int Free PSRAM: %d", ESP.getFreePsram());

  //Create a float
  float *var_float = (float *) ps_malloc(sizeof(float));
  *var_float = 42.42;

  log_d("var_float Total PSRAM: %d", ESP.getPsramSize());
  log_d("var_float Free PSRAM: %d", ESP.getFreePsram());

  Serial.println((String)"var_int = " + *var_int);
  Serial.print("var_float = ");
  Serial.println(*var_float);

  //Create an array of 1000 integers
  int n_elements = 1000;
  int *int_array = (int *) ps_malloc(n_elements * sizeof(int));
  //We access array values like a classic array
  int_array[0] = 42;
  int_array[42] = 42;
  int_array[999] = 42;

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
