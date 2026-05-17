## Aufgabe 1
- Strecke ohne Ausgleich (jede Loop immer drauf rechnen)
- für Strecke ohne Ausgleich jeweils 
	- P-Regler
	- PI-Regler
		- P-Regler + I-Regler
	- PD-Regler
		- P-Regler + D-Regler
- Regler "exportierbar" coden für Aufgabe 2
## Aufgabe 2
- Strecke mit Ausgleich (Sockelwert/Sollwert 0)
- jeden Zeitabschnitt ausrechnen was grad Zielwert ist, dann für den Zeitabschnitt den Zielwert festlegen
- PID-Regler
# Funktionsweise
## Reglerarten
### P-Regler
- Proportional zu Regeldifferenz wird Stellgröße des Aktuators angepasst
	- $a(t) = K_P *\Delta_a(t)$
	- Konstante K bestimmt Stellgröße
- schnelle Sprungantworten
- kompensiert auf Strecke ohne Ausgleich die Regelabweichung vollständig
- lässt auf Strecken mit Ausgleich bleibende Regelabweichung zurück!
#### Implementierung
 $a(t) = K_P *\Delta_a(t)$
$\Delta = \text{soll-ist}; a = K_P*\Delta$
- $K_P$ trial and error zum Bestimmen
- jede Loop delta berechnen
- $a$ addieren zu Motorwert (?)
	- anschauen wie Motorwert genau funktioniert
### I-Regler
- Proportional zur bisher "angesammelten" Regeldifferenz wird Stellgröße angepasst
- $a(t)=K_I*\int_0^t\Delta_a(t)dt$
- Konstante K bestimmt wieder Stellgröße wie bei P-Regler, höhere Konstante -> schnellere Anpassung, aber größeres Überschwingen
- Sollwert wird erst nach längerer Zeit erreicht
- Kann nicht allein für Strecke ohne Ausgleich eingesetzt werden
#### Implementierung
$s += \Delta$
$a=K_I*T*s$
- Integral-Implementierung (?)
### D-Regler
- Proportional zur Änderung der Regeldifferenz wird Stellgröße angepasst
- $a(t)=K_D*\frac{d\Delta_a(t)}{dt}$
- sorgt für hohes Überschwingen
- kann nicht allein eingesetzt werden
#### Implementierung
$\Delta=soll - ist$
$a=K_D*(\Delta-\Delta_{alt}/T)$
$\Delta_{alt}=\Delta$
- Ableitung Implementierung (?)
- Startwert $\Delta$ (?)
### PD-Regler
- P-Regler + D-Regler
$a(t) = K_P*\Delta_a(t)+K_D*\frac{d\Delta_a(t)}{dt}$
- Reglerkonstanten separat, müssen einzeln angepasst werden
### PID-Regler
- P-Regler + I-Regler + D-Regler
$a(t) = K_P*\Delta_a(t)+K_D*\frac{d\Delta_a(t)}{dt}+K_I*\int_0^t\Delta_a(t)dt$
- Reglerkonstanten separat, müssen einzeln angepasst werden
## Streckenarten
### Strecke ohne Ausgleich (I-Glied)
- genannt I-Strecke
- Effekt durch Regler bleibt erhalten (zB Antrieb in Schwerelosigkeit)
#### Beispiel Wassertank
- bei konstantem Zufluss $m(t)$ wird die Wassermenge im Tank linear ansteigen
- bei variierendem Zufluss $m(t)$ und Startwassermenge gilt $m_T(t)=m_0 + \int_o^tm(t)dt$ 

### Strecke mit Ausgleich (P-Glied)
- genannt P-Strecke
- Effekt durch Regler wird verbraucht (zB Antrieb auf Boden; Reibung)
#### Beispiel Wassertank
- Menge des Wassers proportional zu 
	- Menge des einfließenden Wassers
	- Menge des ausfließenden Wassers
### Strecke mit Verzögerung (PTn-Glied)
- Reaktion auf Änderung an Eingang findet verzögert statt
#### Beispiel Heizung
- Erwärme Wasser (braucht Zeit zum aufheizen)
- Erwärme mit Wasser Luft (braucht auch Zeit zum aufheizen)
