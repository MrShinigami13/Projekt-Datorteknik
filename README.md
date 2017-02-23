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
I stort sett samma kod som finns i våra labbar. Behövs initaliseras och clearas på rätt sätt om displayen inte ska paja.

Att göra:
Få koll på smidiga sätt att generera pixlar i OLEDen. Än så länge har vi bara sett bmp-konvertering till pixelmatriser.
/Möjlig lösning paddel: Skulle gå att rita paddlar med rätt mängd pixlar i typ paint och sen konvertera och infoga på samma sät som icon och font hanteras.
/Kvarstående problem: Kolla hur pixelpekare hanteras på OLEDen. så vi kan peka på rätt pixel osv.