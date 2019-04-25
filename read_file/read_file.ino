
void serialEvent()
{
   while(Serial.available()) 
   {
      char ch = Serial.read();
      Serial.write(ch);
      if(index &lt; MaxChars &amp;&amp; isDigit(ch))              {                               
            strValue[index++] = ch;                     
      }else{                               
            strValue[index] = 0;                               
            newAngle = atoi(strValue);                               
            if(newAngle &gt; 0 &amp;&amp; newAngle &lt; 180){
               if(newAngle &lt; angle)                                                
                   for(; angle &gt; newAngle; angle -= 1) {
                   myservo.write(angle);
               }  
            else 
               for(; angle &lt; newAngle; angle += 1){
                   myservo.write(angle);
                } 
         }
         index = 0;
         angle = newAngle;
      }  
   }
}
