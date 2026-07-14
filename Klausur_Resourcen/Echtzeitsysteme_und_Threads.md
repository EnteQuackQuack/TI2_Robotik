# Echtzeitsysteme und Threads

---
## **Echtzeitanforderungen**
Echtzeitsysteme müssen **Zeitbedingungen** einhalten, um korrekt zu funktionieren.\

### Arten von Echtzeitsystemen
- **Harte Echtzeitsysteme**:
  - **Deadline muss immer eingehalten werden**, sonst entsteht ein **Schaden**.
  - Muessen **deterministisch** (vorhersehbar) sein.
  - **Beispiel**: Airbag-Steuerung (Verzögerung → lebensgefährlich).

- **Weiche Echtzeitsysteme**:
  - **Deadline sollte eingehalten werden**, aber bei Nichteinhaltung nimmt der Nutzen ab.
  - Muessen nicht **deterministisch** sein, sollten aber meistens die Deadline einhalte
  - **Beispiel**: Geschwindigkeitsanzeige im Auto (leicht verzögerte Anzeige ist tolerierbar).

> [!NOTE]
> **Deadline einer Funktion**
> - **Definition**: Spätester Zeitpunkt, bis zu dem eine Funktion ihr Ergebnis liefern **muss**.
> - Wird **relativ zur Aktivierung** angegeben (z. B. "innerhalb von 10 ms nach Start").
> - **Reaktionszeit** = Zeit von der Aktivierung bis zum Vorliegen des Ergebnisses.
>   - **Formel**: `Reaktionszeit ≤ Deadline`
> - **Ausführungszeit** = Zeit, die die Funktion zur Berechnung benötigt (z. B. 8 ms für Funktion C).

---

---
## **Konflikte bei der Echtzeitverarbeitung**
Konflikte entstehen, wenn:
1. **Funktionen längere Berechnungszeiten** benötigen als das geforderte **Abtastintervall**.
2. **Mehrere Aufgaben** auf einem Prozessor parallel laufen müssen.

### Beispielsystem
Drei Software-Funktionen auf einem Steuergerät:
   Funktion | Ausführungszeit | Aufrufintervall | Erwartete Reaktionszeit |
 |----------|-----------------|-----------------|-------------------------|
 | A (Cockpit-Display) | 30 ms | alle 400 ms | 400 ms |
 | B (Daten an Motormanagement) | 45 ms | alle 200 ms | 100 ms |
 | C (Airbag-Ansteuerung) | 8 ms | einmalig | 10 ms |

> **Kritisch**: Funktion C muss **spätestens nach 10 ms** reagieren, sonst versagt das System.

---
> [!IMPORTANT]
> **Worst-Case-Analyse für Funktion C**
> - **Problem**: Funktion C muss den Sensor **regelmäßig abfragen**, um einen Crash zu erkennen.
> - **Lösung**:
>   - Maximales **Abtastintervall** ($T_{\text{poll}}$) berechnen, damit die Deadline eingehalten wird:
>     $$
>     T_{\text{poll}} \leq D_C - C_C = 10\,\text{ms} - 8\,\text{ms} = 2\,\text{ms}
>     $$
>   - **$T_{\text{poll}}$**: Maximales Intervall zwischen Sensorabfragen.
>   - **$D_C$**: **Deadline** von Funktion C (10 ms).
>   - **$C_C$**: **Ausführungszeit** von Funktion C (8 ms).
> - **Interpretation**:
>   - Funktion C darf **maximal alle 2 ms** den Sensor abfragen, um sicherzustellen, dass sie **innerhalb von 10 ms** reagieren kann (8 ms Berechnung + 2 ms Puffer).

---
---
## **Lösungsansätze für Konflikte**

### 1. **Monolithische Implementierung (naiv)**
**Was ist das?**
- **Ansatz**: Alle Funktionen (A, B, C) werden in **einer einzigen Endlosschleife** in `main()` implementiert.
- **Beispielcode**:
  ```c
  int main() {
    while(1) {
      // Funktion A aufrufen
      CockpitDisplay_Update();
      // Funktion B aufrufen
      SendDataToEngine();
      // Funktion C manuell einbauen: Sensor alle 2 ms abfragen
      if (getTime() % 2 == 0) { CheckAirbagSensor(); }
    }
  }
  ```
- **Problem**:
  - Manuelles Einfügen von Aufrufpunkten für Funktionen.
  - **Nachteile**:
    - Sehr komplex und fehleranfällig.
    - Nicht skalierbar (z. B. bei Schleifen oder Compileroptimierungen).
    - Die vorgegebenen Reaktionszeiten (siehe Beispielsystem) koennen nicht eingehalten werden
    - andere Seiteneffekte möglich.
> [!CAUTION]
> Monolitische Implementierung ist fuer quasi kein Problem eine Loesung

### 2. **Prozesse/Threads (professioneler Ansatz)**
- **Lösung**: Aufgaben als **unabhängige Threads** (oder Prozesse) implementieren.
- **Vorteile**:
  - Keine manuelle Aufrufpunkt-Verwaltung.
  - Besser skalierbar und wartbar.
- **Nachteil**: Benötigt einen **Scheduler** zur Verwaltung.

> [!TIP] 
> #### **Multithreading**
> - **Definition**: (Quasi-)parallele Ausführung mehrerer Funktionen.
> - **Steuerung durch Betriebssystem**:
>   - Startet, stoppt und unterbricht Threads nach einer **Strategie** (z. B. Priorisierung).
> - **Wichtige Zeitbedingungen**:
>   - **Deadline**: Bis wann muss die Funktion fertig sein?
>   - **Aktivierung**: Wann muss die Funktion gestartet werden?
>   - **Priorisierung**: Gibt es Threads mit Vorrang?
>
> #### **Thread-Zustände**
> Jeder Thread befindet sich in einem von drei Zuständen:
> 1. **ready**: Thread möchte Rechenzeit erhalten.
> 2. **running**: Thread nutzt gerade die CPU.
> 3. **blocked**: Thread wartet (z. B. auf eine Nachricht oder Ressource).

> [!WARNING]
> #### **Kritische Bereiche**
> **Problem:**
> Mehrere Tasks greifen **gleichzeitig** auf dieselbe Ressource zu (z. B. globale Variablen, Motor, Sensoren).
> - **Beispiel mit NNXT.h**:
>   - Task A liest den Wert eines **globalen Sensors** (z. B. `SensorValue`).
>   - Task B schreibt in denselben Sensor, während Task A liest → **Dateninkonsistenz** (z. B. halb aktualisierter Wert).
> **Lösung für NNXT (FreeRTOS):**
> 1. **Kritische Bereiche identifizieren**:
>    - Codeabschnitte, in denen auf **geteilte Ressourcen** (z. B. Sensoren, Motoren, globale Variablen) zugegriffen wird.
>
> 2. **Schutzmechanismen in NNXT.h**:
>    - **`taskENTER_CRITICAL()`** und **`taskEXIT_CRITICAL`**:
>      - Sperrt/entsperrt den Zugriff auf kritische Bereiche.
>      - **Beispiel**:
>        ```c
>        taskENTER_CRITICAL();  // Sperre setzen
>        // Kritischer Bereich: z. B. Sensorwert lesen/schreiben
>        int sensorValue = ReadSensor(Port_0);
>        ProcessSensorValue(sensorValue);
>        taskEXIT_CRITICAL();   // Sperre aufheben
>        ```
>    - **Hinweis**:
>      - **Keine automatische Erkennung** durch Compiler → **manuelle Implementierung nötig!**
>      - **Dokumentation**: Siehe [NNXT-Tutorial](https://nnxt.io/docs) für Details.
> **Warum ist das wichtig?**
> - Ohne Schutz: **Race Conditions** → Unvorhersehbares Verhalten (z. B. Abstürze, falsche Sensorwerte).
> - Mit Schutz: **Deterministisches Verhalten** (wichtig für harte Echtzeitsysteme).
---
---
## **Threadverwaltung auf dem NNXT**
> [!NOTE]
> Das **FreeRTOS** des NNXT verwendet einen **Zeitscheiben-Scheduler** (keine Priorisierung!):
> - Jeder Thread bekommt für **~1 ms Rechenzeit** zugewiesen, dann wird gewechselt.
> - **Tasks** (NNXT-spezifische Threads) werden als spezielle Funktionen geschrieben.

### **NNXT-Funktionen für Tasks**
 | Funktion | Beschreibung |
 |----------|--------------|
 | `CreateTask(t)` | Erzeugt einen Task aus Funktion `t`. |
 | `StartTask(t)` | Startet Task `t`. |
 | `CreateAndStartTask(t)` | Erzeugt und startet Task `t` sofort. |
 | `StartScheduler()` | Startet das Betriebssystem (keine Rückkehr!). |
 | `Delay(ms)` | Task schlafen lassen für `ms` Millisekunden. |

---
### **Grundsätzliche Struktur eines NNXT-Programms**
```c
void AppTask1() {
  while(1) {
    // Endlosschleife für Task 1
    Delay(50); // Task schlafen lassen
  }
}

void AppTask2() {
  // Code für Task 2
}

int main() {
  /* Initialisierung (z. B. Sensoren) */
  SensorConfig(Port_0, SensorTouch);

  /* Tasks erzeugen und starten */
  CreateAndStartTask(AppTask1);
  CreateAndStartTask(AppTask2);

  /* Betriebssystem starten */
  StartScheduler();

  return 0; // Wird nie erreicht
}
```

### **Konkrets Code Beispiel**
```c
// Einfuegen
```

---
---
## Zusammenfassung fuer die Klausur
+ ✅ Harte Echtzeitsysteme: Deadline muss immer eingehalten werden (z. B. Airbag).
+ ✅ Weiche Echtzeitsysteme: Deadline sollte eingehalten werden (z. B. Geschwindigkeitsanzeige).
+ ✅ Konflikte entstehen durch zu lange Ausführungszeiten oder parallele Aufgaben.
+ ✅ Lösung: Threads + Scheduler (z. B. FreeRTOS auf NNXT).
+ ✅ NNXT: Tasks mit CreateAndStartTask() erstellen, StartScheduler() starten.
+ ✅ Kritische Bereiche manuell schützen (keine automatische Erkennung durch Compiler!).
- ❌ Monolithische Implementierung ist fehleranfällig und nicht skalierbar.
- ❌ Ohne Scheduler keine faire Verteilung der Rechenzeit.
