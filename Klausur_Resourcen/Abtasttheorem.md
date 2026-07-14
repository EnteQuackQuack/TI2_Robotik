# Abtasttheorem

---
## Problem
Mikrocontroller arbeiten diskret und können die **kontinuierliche Entwicklung physikalischer Größen** (z. B. Sensorwerte) nur in endlichen Zeitintervallen erfassen.

### Frage
Wie oft muss ein Signal abgetastet werden, um es korrekt zu rekonstruieren und keine Informationen (z. B. Maxima/Minima) zu verlieren?

---

## Nyquist-Shannon-Abtasttheorem

### Aussage
Um ein Signal mit der höchsten Frequenz **$f$** fehlerfrei zu rekonstruieren, muss die Abtastrate **$f_{\text{abtast}}$** streng größer als das Doppelte von **$f$** sein:

$$
f_{\text{abtast}} > 2 \cdot f
$$

> **Wichtig:**
> - **$f$** ist die höchste **relevante** Frequenz im Signal.
> - Beispiel: Maximale Tasterfrequenz = 10 Hz → **$f_{\text{abtast}} > 20$ Hz** (Intervall ≤ 50 ms).

---

### Begründung
- Jedes Signal lässt sich als Summe von Sinusschwingungen darstellen (**Fouriertransformation**).
- Ohne ausreichend hohe Abtastrate können **Oberschwingungen** nicht erfasst werden → **Alias-Effekt**: Falsche Rekonstruktion des Signals.

#### Fouriertransformation
Mathematisches Verfahren zur Zerlegung eines Signals in seine Frequenzkomponenten.

#### Alias-Effekt
Fehlerhafte Interpretation eines Signals aufgrund zu niedriger Abtastrate.

### Beispiel
Audio-CDs: Abtastrate von **44,1 kHz** für hörbare Frequenzen bis 20 kHz (44,1 kHz > 2 × 20 kHz).

---

## Lösung des Problems

### 1. Bestimmung der höchsten relevanten Frequenz **$f$**
- Bei bekanntem Signal: Fourieranalyse durchführen.
- Bei unbekanntem Signal: Physik des Systems analysieren (z. B. Tasterfrequenz = 10 Hz → $f_{\text{abtast}} > 20$ Hz).

### 2. Wahl der Abtastrate
Beispiel Taster: Maximale Betätigung = 10 Hz → **Abtastrate ≥ 20 Hz** (Intervall ≤ 50 ms).

### 3. Filterung (optional, nicht Teil des Theorems)
Höhere Frequenzen (Rauschen/Oberschwingungen) mit **Tiefpassfiltern** entfernen, um Alias-Effekte zu vermeiden.

### 4. Praktische Umsetzung
- Bei komplexen Signalen: **Mehrfach abtasten** (z. B. 4–8 Mal pro Schwingung für bessere Amplitudenauflösung).
- **Mittelwertbildung** bei Sensorfehlern (z. B. 4 Messwerte → Mittelwert).

#### Mehrfach abtasten – Beispiel
- Theoretisch: $f = 100$ Hz → $f_{\text{abtast}} > 200$ Hz.
- Praktisch: 4–8 Abtastpunkte pro Schwingung (400–800 Hz) für bessere Auflösung.

---
## Zusammenhang mit Echtzeitsystemen
- **Echtzeitanforderung**: Die Abtastrate muss so gewählt werden, dass:
  - Zu niedrige Raten zu **Datenverlust** führen.
  - Zu hohe Raten **Prell-Effekte** (z. B. bei Tastern) oder unnötige Rechenlast verursachen.
- **Kompromiss**: So hoch wie nötig, so niedrig wie möglich.

---
## Code Beispiel:
```cpp
// Platzhalter für Code-Beispiel
