# Tonpegel aufzeichnen mit einem Arduino

Wann ists still? Und wann gibts besonders viel Lärm? Dieses Arduino-Skript zeichnet die Messwerte eines Mikrofons auf, das an einen Mikroprozessor angeschlossen wird. Gemessen werden nicht die Dezibel, sondern die elektrische Spannung). Die Messwerte werden mit dem Skript direkt auf einen Server übermittelt. Die Hintergründe zu diesem Projekt wurden in einem [Artikel in der Berner Zeitung](https://www.bernerzeitung.ch) beschrieben. Der Aufbau und die Skripte wurden lediglich für einen kurzen Test entwickelt. Es gibt keine Garantie, dass sie funktionieren. Für Hinweise zur Weiterentwicklung bin ich dankbar. 

## Aufbau

### Einkaufsliste: 

- Mikrocontroller, kompatibel mit der Arduino-Plattform. Wir verwedeten einen ESP8266 (siehe [Maker-Shop.ch](https://www.maker-shop.ch/nodemcu-esp8266-wifi-development-board) | [Aliexpress](https://de.aliexpress.com/item/32827135137.html?spm=a2g0s.9042311.0.0.1b684c4dhi9JIV).
- Ein einfaches Mikrofon (siehe z.B. [Maker-shop.ch]() | [Aliexpress](https://de.aliexpress.com/item/32866143647.html?spm=a2g0s.9042311.0.0.2df14c4dFuiPl6)).
- Verbindungskabel

Optional:

- USB-Stromadapter (siehe z.B. [Aliexpress](https://de.aliexpress.com/item/32783433931.html?spm=a2g0s.9042311.0.0.27424c4d9RrPWH))
- Mikro-USB-Kabel (siehe z.B. [Aliexpress](https://de.aliexpress.com/item/4000035824574.html?spm=a2g0o.productlist.0.0.6484678ck6vhhH&algo_pvid=9f7b3e63-f793-4396-9582-874a12510511&algo_expid=9f7b3e63-f793-4396-9582-874a12510511-1&btsid=dccaf817-81ca-4f7b-b9bf-fcf294d8d3c8&ws_ab_test=searchweb0_0,searchweb201602_7,searchweb201603_53))
- Akku: Entweder behilft man sich mit einem Akkupack. Oder man wählt einen etwas teureren Mikrocontroller, der gleich mit einem Anschluss für einen LiPo-Akku bestückt ist. 
- SD-Karten-Modul (siehe z.B. [Aliexpress](https://de.aliexpress.com/item/32984052110.html?spm=a2g0o.productlist.0.0.4c2b241bAmQ79S&algo_pvid=2ce03cd4-e655-49ea-9d54-c14ce3fb8493&algo_expid=2ce03cd4-e655-49ea-9d54-c14ce3fb8493-0&btsid=2177fb89-90e5-413e-aded-22278c3739c7&ws_ab_test=searchweb0_0,searchweb201602_7,searchweb201603_53)) mit SD-Karte (siehe z.B. [Aliexpress](https://de.aliexpress.com/item/33015019191.html?spm=a2g0s.9042311.0.0.2df14c4dFuiPl6))
- Windschutz (siehe z.B. [Aliexpress](https://de.aliexpress.com/item/4000022870715.html?spm=a2g0s.9042311.0.0.65984c4dM6S3yM))
- Kleine Verteilerbox (siehe z.B. [Aliexpress](https://de.aliexpress.com/item/33028235901.html) | Bauhaus(https://www.bauhaus.ch/de/search?query=63192511)).
