

void setup(void)
{
	Serial.begin(115200);
	Serial1.begin(115200);
	Serial.println("Monitor is online...");
}


void loop(void)
{
	uint8_t buffer[256];
	uint16_t len=0;
	while(Serial.available()){
		buffer[len] = Serial.read();
		len++;
	}
	if(len){
		Serial1.write(buffer,len);
	}
	len=0;
	while(Serial1.available()){
		buffer[len] = Serial1.read();
		len++;
	}
	if(len){
		Serial.write(buffer,len);
	}
}
