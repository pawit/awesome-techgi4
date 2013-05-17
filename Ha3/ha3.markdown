## TechGI 4 Hausaufgabe 3 - Tom Nick

### Aufgabe 1
Das Synchronisieren der Uhrzeiten ist essentiell wichtig in jedem Software-System, dass in irgendeiner Weise die Zeit benutzt.
Seien es Timestamps auf logs, der Zeitpunkt an dem ein UDP-Packet eintrifft oder das Änderungsdatum einer Datei auf dem Dateisystem.
Ohne eine Synchronisierung der Zeit wären jeglichen Zeitdaten eines Computers nur auf diesem selber nützlich, jede Kommunikation mit einem anderen System würde zwangsweise irgendwann zu Fehlern führen. Bei verteilten Systemen gewinnt dieses Thema umso mehr an Wichtigkeit, da hier dauerhaft zeitbehaftete Informationen ausgetauscht werden, somit muss beim Design dieser darauf geachtet werden, dass die Uhrzeiten nur minimale Abweichungen haben dürfen bzw. oft synchronisiert werden.

### Aufgabe 2
    t_1 = absolut synchron
    rho = maximale Drift
    delta = tolerierbare Abweichungen
Intuitiv würde man zuerst sagen der Zeitpunkt müsste `delta/rho` sein. Da aber die Uhren in verschieden Richtungen driften können, müssene sie zum Zeitpunkt `delta/2*rho` wieder synchronisiert werden, damit ihre gegenseitige Abweichung kleiner als `delta` ist.

### Aufgabe 4
    A ist am langsamsten
    B ist weder am schnellsten noch am langsamsten
    C ist am schnellsten
    t_0 : A=B=C
1. Falls die Dauer die Nachricht zu verschicken kleiner als `C - B` bzw. `B - A` zum Zeitpunkt der Ankunnft ist, würde die Nachricht scheinbar vor ihrem Sendezeitpunkt ankommen.
2. Falls die Systeme zum Sendezeitpunkt synchronisiert waren, ist es sehr unwahrscheinlich das dies passieren kann, wären sie nicht synchronsiert ist es durchaus möglich. Möglichkeiten diese Situationen zu korrigieren wären das System von vornerein zu synchronisieren, man könnte auch den Zeitstempel der Ankunft anpassen mit `lokale Zeit + dauer des sendes`. Das Empfängersystem könnte auch seine Uhr so lange verlangsamen bis der Ankunftszeitpunkt korrekt ist.
3. Der Lamport Algorhitmus würde einen Middleware-layer einfügen, der die lokale Uhrzeit und Timestamp-Nachricht beim Senden verändern würde, beim Empfangen die lokale Uhrzeit.

### Aufgabe 5
    Genauigkeit = 100ms
    Sendezeit = 50ms
1. Falls `T' - 50ms > T`, dann wäre die Nachricht die ankommt älter als die schon in der Tabelle vermerkte, unabhängig von der Reisezeit.
2. Falls `lok.zeit. - 150ms > 175000ms`
3. Ja extern sollte auch hin und wieder synchronisiert werden, falls diese Systeme externe Schnittstellen haben, da die Uhren mitunter in die gleiche Richtung driften.

### Aufgabe 6
Die Differenz des Sende und Ankommenszeitpunkt sind jeweils:

    A = 16:34:23.480 - 16:34:13.430 = 1050ms
    B = 16:34:15.725 - 16:34:25.700 = -1025ms
    C = (1050ms - 1025ms)/2 = 12.5ms
Die Dauer der Nachricht würde also in etwa `12.5ms` dauern, somit würde ich die Differenz der Uhren auf `1037.5ms` beziffern.
Das Fehlerintervall liegt bei `1025 - 1050`.



