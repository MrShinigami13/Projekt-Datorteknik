# Projekt-Datorteknik
Projekt i kursen datorteknik

om pic32mx: http://www.microchip.com/wwwproducts/en/PIC32MX320F128H



bra hemsidor
http://www.rickard.gunee.com/projects/video/pic/howto.php

Ljud:
https://diyhacking.com/arduino-audio-player/


fungerande pong med vga: http://nathandumont.com/blog/pong-on-a-vga-monitor-with-the-chipkit-uno32


Nytt:
Basic I/O-manualen har all info om displayen i Appendix B.
I stort sett samma kod som finns i v�ra labbar. Beh�vs initaliseras och clearas p� r�tt s�tt om displayen inte ska paja.

Att g�ra:
F� koll p� smidiga s�tt att generera pixlar i OLEDen. �n s� l�nge har vi bara sett bmp-konvertering till pixelmatriser.
/M�jlig l�sning paddel: Skulle g� att rita paddlar med r�tt m�ngd pixlar i typ paint och sen konvertera och infoga p� samma s�t som icon och font hanteras.
/Kvarst�ende problem: Kolla hur pixelpekare hanteras p� OLEDen. s� vi kan peka p� r�tt pixel osv.