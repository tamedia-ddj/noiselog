# Tonpegel aufzeichnen mit einem Arduino

Wann ists still? Und wann gibts besonders viel Lärm? Dieses Skript zeichnet die Werte auf, die ein Mikrofon liefert, das an ein einfaches Entwicklerboard angeschlossen wird. Die Werte werden übers WLAN an einen Server übermittelt. Achtung: Dieses Skript misst lediglich die Stromstärke. Als Dezibel-Messgerät eignet es sich nicht. 

## Setup

- Die PHP-Datei wird in einem Unterverzeichnis auf einem Webserver abgelegt. 
- Die Ino-Datei wird in der Arduino-IDE geöffnet. Die Variablen werden richtig gesetzt. Anschliessend wird das Skript auf den Mikrokontroller übertragen. 
