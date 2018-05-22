// Boot up even if unable to connect to the cloud
SYSTEM_MODE(SEMI_AUTOMATIC);
SYSTEM_THREAD(ENABLED);
int retryCount = 0;

void setup()
{
  pinMode(D7, OUTPUT);
  digitalWrite(D7, HIGH); // Turn power on

  // Attempt to connect to the cloud on boot up
  Particle.connect();
  waitFor(Particle.connected, 15000);
}

void loop()
{
    // Check for cloud connection
    if(Particle.connected() == false) {
        if(retryCount == 0) {
           delay(240000); // Delay 4 minutes the first time without reset for good measure
        } else {
            digitalWrite(D7, LOW); // Turn power off
            delay(4000); // Wait for 4 seconds
            digitalWrite(D7, HIGH); // Turn power on

            if (retryCount < 2) {
                delay(1000*60*5); // Delay 5 minutes the first two tries
            } else if (retryCount < 4) {
                delay(1000*60*30); // Delay 30 minutes the second two tries
            } else if (retryCount < 12) {
                delay(1000*60*60*2); // Delay 2 hours the final eight tries
            } else {
                // Give up
            }
        }
        // Increase the retry count by one
        retryCount = retryCount + 1;
    } else {
        // We're connected, reset the retryCount to zero
        retryCount = 0;
    }
    delay(30000); // Wait 30 seconds
}
