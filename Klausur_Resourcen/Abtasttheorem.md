# Abtasttheorem
*Wie oft muss ich ein Signal abtasten, um es korrekt digital zu verarbeiten?*

---

---
## Problem
Mikrocontroller arbeiten **diskret** und können die **kontinuierliche Entwicklung physikalischer Größen** (z. B. Sensorwerte) **nur in endlichen Zeitintervallen** erfassen.

> [!NOTE]
> **Frage:** ❓
> Wie oft muss ein Signal abgetastet werden, um es **korrekt zu rekonstruieren** und keine Informationen (z. B. Maxima/Minima) zu verlieren?

---

---
## Nyquist-Shannon-Abtasttheorem 📜

### Aussage 🎯
Um ein Signal mit der höchsten Frequenz **$f$** fehlerfrei zu rekonstruieren, muss die Abtastrate **$f_{\text{abtast}}$** streng größer als das Doppelte von **$f$** sein:

$$
f_{\text{abtast}} > 2 \cdot f
$$

> [!IMPORTANT]
> - **$f$** = höchste **relevante** Frequenz im Signal (nicht zwingend die physikalisch höchste!).
> - Beispiel Taster: Maximale Betätigungsfrequenz = 10 Hz → **$f_{\text{abtast}} > 20$ Hz** (Intervall ≤ 50 ms).

---
### Begründung 🧠
1. **Fouriertransformation**
   Jedes Signal lässt sich als **Summe von Sinusschwingungen** darstellen.
   → Mathematisches Verfahren zur Zerlegung eines Signals in seine **Frequenzkomponenten**.

2. **Alias-Effekt**
   - **Problem:** Zu niedrige Abtastrate → **falsche Rekonstruktion** des Signals.
   - **Folge:** Höhere Frequenzen (Oberschwingungen) werden als niedrigere Frequenzen **falsch interpretiert**.
   - **Beispiel:**
     ```
     Signal-Frequenz: 30 Hz
     Abtastrate: 40 Hz (< 2×30 Hz) → Alias-Effekt: Das Signal erscheint als 10 Hz!
     ```

3. **Praktisches Beispiel**
   - **Audio-CDs:** Abtastrate = **44,1 kHz** (hörbarer Bereich: 20 Hz–20 kHz).
     → 44,1 kHz > 2 × 20 kHz

---
---
## Lösung des Problems ✅

1. **Bestimmung der höchsten relevanten Frequenz $f$**
   - Bei bekanntem Signal: Fourieranalyse durchführen.
   - Bei unbekanntem Signal: Physik des Systems analysieren (z. B. Tasterfrequenz = 10 Hz → $f_{\text{abtast}} > 20$ Hz).

2. **Wahl der Abtastrate**
   Beispiel Taster: Maximale Betätigung = 10 Hz → **Abtastrate ≥ 20 Hz** (Intervall ≤ 50 ms).

3. **Filterung (optional, aber empfehlenswert)**
   Höhere Frequenzen (Rauschen/Oberschwingungen) mit **Tiefpassfiltern** entfernen, um Alias-Effekte zu vermeiden.

4. **Mehrfachabtastung für Präzision**
   - Theoretisch: $f = 100$ Hz → $f_{\text{abtast}} > 200$ Hz.
   - Praktisch: 4–8 Abtastpunkte pro Schwingung (400–800 Hz) für bessere Auflösung der Signalform (z. B. Sinuskurve).

---
---
## Zusammenhang mit Echtzeitsystemen
- **Zu niedrige Abtastrate** → Datenverlust, Alias-Effekt.
- **Zu hohe Abtastrate** → Prell-Effekte (z. B. bei Tastern) oder unnötige Rechenlast.
- **Prell-Effekte** → Falsche Detektion (z. B. Taster "gedrückt" → "nicht gedrückt" → "gedrückt").
  → **Lösung:** Entprell-Algorithmen oder Hardware-Filter.

> [!TIP]
> **"So hoch wie nötig, so niedrig wie möglich!"**
> - Niedrigere Abtastrate → Sparsam mit Ressourcen (Strom, CPU).
> - Höhere Abtastrate → Genauere Daten, aber mehr Aufwand.

---
---
## Zusammenfassung für die Klausur
```diff
+ ✅ Abtastrate muss > 2× höchste relevante Frequenz sein.
+ ✅ Fouriertransformation zerlegt Signale in Sinusschwingungen.
+ ✅ Alias-Effekt vermeiden: Sonst falsche Signalrekonstruktion!
+ ✅ Mehrfachabtastung für bessere Signalform-Abbildung.
+ ✅ Filterung (Tiefpass) gegen Rauschen/Oberschwingungen.
- ❌ Prell-Effekte sind keine relevanten Frequenzen (außer, man will sie messen)!
- ❌ Zu hohe Abtastrate → unnötige Rechenlast.
```

---
---
## Code Beispiel:
```cpp
// Platzhalter für Code-Beispiel
