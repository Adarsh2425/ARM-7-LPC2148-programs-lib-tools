void pinWrite(int pinNum,int pinValue); // 0-31,0/1- challenge - identififign the port 
void portWrite(int portNum,int portValue); //0/1, hexadecimal value-32bit or 8bit
int pinRead(int pinNum);
int portRead(int portNum);
void pinSelect(int pinNum, int funcvalue);// funcvalue=0/1/2/3
