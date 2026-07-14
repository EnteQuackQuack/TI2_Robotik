# 📡 **Abtasttheorem**
*Wie oft muss ich ein Signal abtasten, um es korrekt digital zu verarbeiten?*

---

---

## ❓ **Problem**
Mikrocontroller arbeiten **diskret** und können die **kontinuierliche Entwicklung physikalischer Größen** (z. B. Sensorwerte) **nur in endlichen Zeitintervallen** erfassen.

> **🔍 Frage:**
> Wie oft muss ein Signal abgetastet werden, um es **korrekt zu rekonstruieren** und keine Informationen (z. B. Maxima/Minima) zu verlieren?

---

---

## 📜 **Nyquist-Shannon-Abtasttheorem**

### 🎯 **Aussage**
Um ein Signal mit der höchsten Frequenz **`f`** fehlerfrei zu rekonstruieren, muss die Abtastrate **`f_abtast`** **streng größer als das Doppelte von `f`** sein:

$$
\boxed{f_{\text{abtast}} > 2 \cdot f}
$$

> **⚠️ Wichtig:**
> - **`f`** = höchste **relevante** Frequenz im Signal (nicht zwingend die physikalisch höchste!).
> - **Beispiel Taster:** Maximale Betätigungsfrequenz = 10 Hz → **`f_abtast > 20 Hz`** (Intervall ≤ 50 ms).

---

### 🧠 **Begründung**
1. **Fouriertransformation**
   Jedes Signal lässt sich als **Summe von Sinusschwingungen** darstellen.
   → Mathematisches Verfahren zur Zerlegung eines Signals in seine **Frequenzkomponenten**.

2. **Alias-Effekt** 🚨
   - **Problem:** Zu niedrige Abtastrate → **falsche Rekonstruktion** des Signals.
   - **Folge:** Höhere Frequenzen (Oberschwingungen) werden als niedrigere Frequenzen **falsch interpretiert**.
   - **Beispiel:**
     ```plaintext
     Signal-Frequenz: 30 Hz
     Abtastrate: 40 Hz (< 2×30 Hz) → Alias-Effekt: Das Signal erscheint als 10 Hz!
     ```

3. **Praktisches Beispiel**
   - **Audio-CDs:** Abtastrate = **44,1 kHz** (hörbarer Bereich: 20 Hz–20 kHz).
     → 44,1 kHz > 2 × 20 kHz ✅

---

---

## ✅ **Lösung des Problems**
   Schritt | Maßnahme | Beispiel |
 |---------|----------|----------|
 | **1️⃣** | **Höchste relevante Frequenz `f` bestimmen** | Taster: 10 Hz → `f = 10 Hz` |
 | **2️⃣** | **Abtastrate `f_abtast > 2·f` wählen** | `f_abtast > 20 Hz` (z. B. 25 Hz) |
 | **3️⃣** | **Filterung (optional, aber empfehlenswert)** | Tiefpassfilter, um Rauschen/Oberschwingungen zu entfernen |
 | **4️⃣** | **Mehrfachabtastung für Präzision** | 4–8 Abtastpunkte pro Schwingung (z. B. 400–800 Hz für `f = 100 Hz`) |

> **💡 Warum Mehrfachabtastung?**
> - Theoretisch reicht `f_abtast > 2·f`, aber für eine **bessere Annäherung der Signalform** (z. B. Sinuskurve) sind **mehr Punkte pro Schwingung** sinnvoll.
> - **Beispiel:**
>   - `f = 100 Hz` → Theoretisch: `f_abtast > 200 Hz`.
>   - Praktisch (für gute Auflösung): **400–800 Hz**.

---
---
## ⚙️ **Zusammenhang mit Echtzeitsystemen**
 | **Problem** | **Folge** | **Lösung** |
 |-------------|-----------|------------|
 | **Zu niedrige Abtastrate** | Datenverlust, Alias-Effekt | `f_abtast > 2·f` einhalten |
 | **Zu hohe Abtastrate** | Prell-Effekte (z. B. Taster), hohe Rechenlast | **Filterung**, Kompromiss finden |
 | **Prell-Effekte** | Falsche Detektion (z. B. Taster "gedrückt" → "nicht gedrückt" → "gedrückt") | **Entprell-Algorithmen** oder Hardware-Filter |

> **🔥 Merksatz:**
> **"So hoch wie nötig, so niedrig wie möglich!"**
> - **Niedrigere Abtastrate** → Sparsam mit Ressourcen (Strom, CPU).
> - **Höhere Abtastrate** → Genauere Daten, aber mehr Aufwand.

---
---
## 📌 **Zusammenfassung für die Klausur**
```diff
+ ✅ Abtastrate muss > 2× höchste relevante Frequenz sein.
+ ✅ Fouriertransformation zerlegt Signale in Sinusschwingungen.
+ ✅ Alias-Effekt vermeiden: Sonst falsche Signalrekonstruktion!
+ ✅ Mehrfachabtastung für bessere Signalform-Abbildung.
+ ✅ Filterung (Tiefpass) gegen Rauschen/Oberschwingungen.
- ❌ Prell-Effekte sind keine relevanten Frequenzen (außer, man will sie messen)!
- ❌ Zu hohe Abtastrate → unnötige Rechenlast.
---

## Code Beispiel:
