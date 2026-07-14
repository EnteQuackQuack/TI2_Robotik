# Echtzeitsysteme und Threads

---
## **Echtzeitanforderungen**
Echtzeitsysteme müssen **Zeitbedingungen** einhalten, um korrekt zu funktionieren.

### Arten von Echtzeitsystemen
- **Harte Echtzeitsysteme**:
  - **Deadline muss immer eingehalten werden**, sonst entsteht ein **Schaden**.
  - **Beispiel**: Airbag-Steuerung (Verzögerung → lebensgefährlich).

- **Weiche Echtzeitsysteme**:
  - **Deadline sollte eingehalten werden**, aber bei Nichteinhaltung nimmt der Nutzen ab.
  - **Beispiel**: Geschwindigkeitsanzeige im Auto (leicht verzögerte Anzeige ist tolerierbar).

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
### **Analyse des Systemverhaltens**
- **Worst-Case-Szenario** für Funktion C:
  - Sensorabfrage muss **mindestens alle 2 ms** erfolgen, um die Deadline einzuhalten:
    $$
    T_{\text{poll}} \leq D_C - C_C = 10\,\text{ms} - 8\,\text{ms} = 2\,\text{ms}
    $$
  - **$T_{\text{poll}}$**: Maximales Intervall zwischen Sensorabfragen.
  - **$D_C$**: Deadline von Funktion C (10 ms).
  - **$C_C$**: Ausführungszeit von Funktion C (8 ms).

---
---
## **Lösungsansätze für Konflikte**

### 1. **Monolithische Implementierung (naiv)**
- **Problem**:
  - Manuelles Einfügen von Aufrufpunkten für Funktion C in Funktion B.
  - **Nachteile**:
    - Sehr komplex und fehleranfällig.
    - Nicht skalierbar (z. B. bei Schleifen oder Compileroptimierungen).
    - Seiteneffekte möglich.

> **Fazit**: Nicht praktikabel für komplexe Systeme.

---
### 2. **Prozesse/Threads**
- **Lösung**: Aufgaben als **unabhängige Threads** (oder Prozesse) implementieren.
- **Vorteile**:
  - Keine manuelle Aufrufpunkt-Verwaltung.
  - Besser skalierbar und wartbar.
- **Nachteil**: Benötigt einen **Scheduler** zur Verwaltung.

#### **Multithreading**
- **Definition**: (Quasi-)parallele Ausführung mehrerer Funktionen.
- **Steuerung durch Betriebssystem**:
  - Startet, stoppt und unterbricht Threads nach einer **Strategie** (z. B. Priorisierung).
- **Wichtige Zeitbedingungen**:
  - **Deadline**: Bis wann muss die Funktion fertig sein?
  - **Aktivierung**: Wann muss die Funktion gestartet werden?
  - **Priorisierung**: Gibt es Threads mit Vorrang?

---
#### **Thread-Zustände**
Jeder Thread befindet sich in einem von drei Zuständen:
1. **ready**: Thread möchte Rechenzeit erhalten.
2. **running**: Thread nutzt gerade die CPU.
3. **blocked**: Thread wartet (z. B. auf eine Nachricht oder Ressource).

---
---
## **Threadverwaltung auf dem NNXT**
Das **FreeRTOS** des NNXT verwendet einen **Zeitscheiben-Scheduler** (keine Priorisierung!):
- Jeder Thread bekommt für **~1 ms Rechenzeit** zugewiesen, dann wird gewechselt.
- **Tasks** (NNXT-spezifische Threads) werden als spezielle Funktionen geschrieben.

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
  StartScheduler(); // Keine Rückkehr nach diesem Aufruf!

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
