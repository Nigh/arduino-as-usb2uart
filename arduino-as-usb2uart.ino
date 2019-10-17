

void setup(void)
{
	Serial.begin(115200);
	Serial1.begin(460800);
	// Serial got a 127 bytes buffer for transmit
	// Serial.println(Serial.availableForWrite());
	// Serial.println(Serial1.availableForWrite());
}


void loop(void)
{
	uint8_t buffer[0x2000];
	uint8_t buffer2[0x2000];

	static uint16_t len=0;
	static uint16_t bp=0;
	static uint16_t len2=0;
	static uint16_t bp2=0;

	while(Serial.available()){
		buffer[(bp+len)&0x1FFF] = Serial.read();
		len++;
	}
	if(len > 0){
		uint16_t ava = Serial1.availableForWrite();
		if(ava > 0){
			if(len > ava){
				Serial1.write(buffer+bp,ava);
				len -= ava;
				bp = (bp + ava)&0x1FFF;
			}else{
				Serial1.write(buffer+bp,len);
				len = 0;
				bp = 0;
			}
		}
	}

	while(Serial1.available()){
		buffer2[(bp2+len2)&0x1FFF] = Serial1.read();
		len2++;
	}
	if(len2){
		uint16_t ava = Serial.availableForWrite();
		if(ava > 0){
			if(len2 > ava){
				Serial.write(buffer2+bp2,ava);
				len2 -= ava;
				bp2 = (bp2 + ava)&0x1FFF;
			}else{
				Serial.write(buffer2+bp2,len2);
				len2 = 0;
				bp2 = 0;
			}
		}
	}
}
