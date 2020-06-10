# transferJSON2WioTerminal
Video Demo : https://twitter.com/Nicho810/status/1270609454984163328



1. upgrade the wifi firmware of Wio Terminal

2. upload the Arduino code（remember to change ssid/pwd/ip address）

3. install flask via pip(python3 must)

4. run run.py on python3

5. open your browser: yourIP:5000 to check if it work

6. change color by entering yourIP:5000/color/blue or yourIP:5000/color/green

7. The serial monitor of Arduino should output message like below:

   ```
   14:58:48.331 -> HTTP/1.0 200 OK
   14:58:48.331 -> Content-Type: text/html; charset=utf-8
   14:58:48.331 -> Content-Length: 20
   14:58:48.331 -> Server: xxxxxxxxxxxxx
   14:58:48.331 -> xxxxxxxxxxxxxxx
   14:58:48.331 -> 
   14:58:48.331 -> json{"color":"blue"}start json processing...
   14:58:48.365 -> {"color":"blue"}
   14:58:48.365 -> color:blue
   14:58:48.500 -> change color to blue...
   14:58:48.500 -> Closing connection.
   14:58:48.500 -> Waiting 2 seconds before restarting...
   ```
   
   

