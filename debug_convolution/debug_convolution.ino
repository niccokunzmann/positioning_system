
const int sample_frequency       = 8000; //Hz max 8000Hz
const int samples_per_wave_cycle = 20;  // determines the frequency
const int number_of_samples      = 300; // used to determine the volume

const int wave_frequency         = sample_frequency / samples_per_wave_cycle;  //Hz

long sum_sinus = 0;
long sum_cosinus = 0;

int sinus_wave[samples_per_wave_cycle];
int cosinus_wave[samples_per_wave_cycle];

// for interrupt sampling
int sample_index = 0;
volatile boolean recording_samples = false;

int samples[] = // volume: 2380849

{1023, 1023, 1023, 1023, 1023, 1023, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 
1, 1, 1, 1, 1, 1, 1, 1, 1, 989, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 2, 1, 1, 1, 1, 1, 
1, 1, 1, 1, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1, 1, 1, 1, 1, 1, 1, 1, 1, 756, 1023, 1023, 
1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 
1023, 2, 1, 1, 2, 2, 1, 1, 1, 1, 1, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1, 1, 1, 2, 
2, 1, 1, 1, 1, 1, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1023, 
1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1023, 1023, 1023, 1023, 1023, 1023, 
1023, 1023, 1023, 1023, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 0, 2, 
1, 2, 1, 1, 1, 1, 1, 1, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1, 1, 1, 1, 1, 1, 1, 1, 
1, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1023, 1023, 1023, 1023, 
1023, 1023, 1023, 1023, 1023, 1023, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 806, 
1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1023, 1023, 1023, 1023}


;

void setup_waves() {
  for (int i = 0; i < samples_per_wave_cycle; ++i) {
    sinus_wave[i]   = int(sin(i * PI * 2 / samples_per_wave_cycle) * 127);
    cosinus_wave[i] = int(cos(i * PI * 2 / samples_per_wave_cycle) * 127);
  }
}

void convolve_wave() {
  sum_sinus   = 0;
  sum_cosinus = 0;
  long sum_of_samples = 0;
  for (int sample_index = 0; sample_index < number_of_samples; sample_index++) {
    sum_of_samples += samples[sample_index];
  }
  int average_sample = sum_of_samples / number_of_samples;
  Serial.print("sum_of_samples ");
  Serial.println(sum_of_samples);
  Serial.print("average_sample ");
  Serial.println(average_sample);
  Serial.print("sizeof(int)");
  Serial.println(sizeof(int));
  Serial.print("sizeof(long)");
  Serial.println(sizeof(long));
  
  for (int sample_index = 0;
       sample_index < number_of_samples;
       sample_index++) 
  {
    int wave_index = sample_index % samples_per_wave_cycle;

    //Serial.print("sin: ");                      // equal
    //Serial.println(sinus_wave[wave_index]);     // equal
    //Serial.print("cos: ");                      // equal
    //Serial.println(cosinus_wave[wave_index]);   // equal

    sum_sinus   += long(samples[sample_index] - average_sample) * sinus_wave[wave_index];
    //Serial.println(sum_sinus);
    sum_cosinus += long(samples[sample_index] - average_sample) * cosinus_wave[wave_index];
  }
}

long compute_squared_volume() {
  // 8 bit sine_wave
  // 10 bit analogRead
  // 9 bit number_of_samples
  // == 27 bit sum_sinus
  // => shift by 12 bit to get 15 bit sum_sinus
  // => 30 bit sum_sinus squared
  // => 31 bit sum_sinus squared + sum_cosinus squared
  long sin_value = sum_sinus / 512;
  Serial.print("sin_value ");
  Serial.println(sin_value);
  Serial.print("sin_value*sin_value ");
  Serial.println(sin_value*sin_value);
  long cos_value = sum_cosinus / 512;
  Serial.print("cos_value ");
  Serial.println(cos_value);
  Serial.print("cos_value*cos_value ");
  Serial.println(cos_value*cos_value);
  return sin_value * sin_value + cos_value * cos_value;
}


void setup() {
  setup_waves();
  Serial.begin(9600);
  while (!Serial) {};
  convolve_wave();
  Serial.print("sum_sinus ");
  Serial.println(sum_sinus);
  Serial.print("sum_cosinus ");
  Serial.println(sum_cosinus);
  long sqv = compute_squared_volume();
  Serial.print("squared value: ");
  Serial.println(sqv);
  
}

void loop () {

};


