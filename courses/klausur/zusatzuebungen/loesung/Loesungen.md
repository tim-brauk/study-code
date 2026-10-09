# Lösungen zu den Zusatzübungen

Der ganze Code wurde mit `g++ -std=c++17 -Wall -Wextra -pedantic` ohne Warnungen gebaut.

## Übung 1: Templates & STL

Siehe `templates/templates.hpp`. Wichtige Punkte:
- Templates stehen **komplett im Header**. Eine Trennung in .hpp/.cpp führt zu Linkerfehlern.
- `clamp_value` vergleicht nur mit `<`. Dann funktioniert sie für alle Typen mit `operator<`, z.B. auch `std::string`.
- Bei `clamp_value("m", "a", "k")` ohne `<std::string>` würde `T` als `char[2]` bzw. `const char*` abgeleitet. Deshalb muss der Typ explizit angegeben oder `std::string` übergeben werden.
- RingBuffer: Den Index rechnet man modulo `N` und merkt sich `start` und `count`. Bei `push` auf einen vollen Puffer wird `data[start]` überschrieben und `start` weitergeschoben.
- Die Spezialisierung `template <> inline std::string describe<bool>(const bool&)` braucht `inline`, wenn sie im Header steht.

| Teil | Punkte |
|---|---|
| a) | 5 (Logik 3, Exception 1, Tests 1) |
| b) | 5 (generisch über Range-for 3, `domain_error` 1, drei Container getestet 1) |
| c) | 10 (Überschreiben des ältesten Werts 4, `at` mit richtigem Index 3, Exception 1, `size`/`is_full` 2) |
| d) | 5 (Template 2, korrekte Spezialisierungssyntax 3) |

---

## Übung 2: Bug Hunt

| # | Zeile | Art | Beschreibung | Korrektur |
|---|---|---|---|---|
| 1 | 23 | Compiler | `get_location()` ist nicht `const`, wird aber in `print() const` und `main` auf `const TrackingEvent&` aufgerufen | `const std::string& get_location() const` |
| 2 | 45 | Speicher/Design | Der Destruktor von `Shipment` ist nicht `virtual`. Wird über einen Basiszeiger gelöscht (`unique_ptr<Shipment>`), läuft der Destruktor von `InternationalShipment` nicht (undefiniertes Verhalten, Leck). | `virtual ~Shipment()` |
| 3 | 64 | Laufzeit | `events[events.size()]` liest ein Element hinter dem Ende (Off-by-one), und es gibt keine Prüfung auf eine leere Liste | `events.back()` + `empty()`-Prüfung |
| 4 | 75 | Logik | Ganzzahldivision: Das Ergebnis ist 12 statt 12.67 | `static_cast<double>(sum) / events.size()` |
| 5 | 101 | Logik/UB | Der Member `customs_rate` wird nie initialisiert, der Parameter wird ignoriert | `customs_rate(customs_rate)` in die Initialisierungsliste |
| 6 | 108 | Speicher | `new[]` wird mit `delete` statt `delete[]` freigegeben. Außerdem ist die Rule of Three verletzt (Kopie führt zu doppeltem `delete`). | `delete[]`, besser `std::vector<std::string>` |
| 7 | 113 | Logik | `fee()` ist nicht `const` und **überschreibt daher nicht**, sondern verdeckt. Polymorph kommt 5 € statt 7 € bzw. 10 € heraus. | `double fee() const override` |
| 8 | 131 | Laufzeit (UB) | Die Funktion gibt eine Referenz auf die lokale Variable `label` zurück (dangling reference) | Rückgabe per Wert: `std::string make_label(...)` |
| 9 | 139 | Design/Logik | `std::vector<Shipment>` führt zu **Object Slicing**: `InternationalShipment` wird zum `Shipment`, die Polymorphie geht verloren | `std::vector<std::unique_ptr<Shipment>>` |
| 10 | 144 | Laufzeit | `index <= shipments.size()` greift außerhalb der Grenzen zu | `<` |
| 11 | 160 | Compiler | Ein `unique_ptr` lässt sich nicht kopieren | `std::move(p_shipment)` |

Bewertung: 1 P je gefundenem Fehler mit sinnvoller Erklärung (11 P), 14 P für die lauffähige korrigierte Datei. Korrekte Ausgabe: S1 = 7 EUR, S2 = 5 EUR, Durchschnitt 12.6667, Gebühr S3 = 10 EUR, und beim Programmende werden **beide** Destruktoren ausgegeben.

---

## Übung 3: Design

### a) SOLID (8 P), mindestens drei davon

| Prinzip | Wo | Problem | Lösung |
|---|---|---|---|
| **S**ingle Responsibility | `LabelService::create_label` | Eine Klasse rechnet Preise, formatiert, gibt auf der Konsole aus, speichert in eine Datei und verschickt E-Mails. Sie hat 5 Gründe, sich zu ändern. | Aufteilen in `PriceCalculator`, `LabelFormatter`, `LabelRepository` und `Notifier` |
| **O**pen/Closed | `calculate_price` mit `if/else` auf einen String | Jeder neue Pakettyp erfordert eine Änderung dieser Methode. Bei Tippfehlern wird stillschweigend 0.0 zurückgegeben. | Polymorphie: Jeder Pakettyp hat sein eigenes `price()` (wie in der Probeklausur), und neue Typen kommen als neue Klasse dazu |
| **L**iskov Substitution | `LabelPrinter::scan_barcode/weigh` | Der Drucker kann nicht überall eingesetzt werden, wo ein `DepotDevice` erwartet wird, weil er Exceptions wirft | Interfaces aufteilen (siehe I) |
| **I**nterface Segregation | `DepotDevice` | Ein „fettes“ Interface zwingt den Drucker, Methoden zu implementieren, die er nicht braucht | `LabelPrintable`, `BarcodeScannable` und `Weighable` als eigene, kleine Interfaces |
| **D**ependency Inversion | `Smtp smtp;` in `create_label` | Die High-Level-Logik hängt direkt an einer konkreten Low-Level-Klasse und ist dadurch weder testbar noch austauschbar (z.B. gegen SMS) | Ein Interface `Notifier` wird per Konstruktor injiziert (`Notifier&` oder `unique_ptr<Notifier>`) |

Bewertung: je Prinzip 1 P für die Benennung mit Stelle und 1 P für einen sinnvollen Lösungsvorschlag, maximal 8 P.

### b) Adapter (9 P)

Siehe `design/scale_adapter.cpp`.

```
┌─────────────────────────┐
│ <<interface>>           │
│ WeightSensor            │
├─────────────────────────┤
│ + weight_kg() : double  │  (abstrakt)
└────────────▲────────────┘
             │ (Realisierung, gestrichelt)
┌────────────┴────────────┐  - scale    ┌──────────────────────────┐
│ ScaleAdapter            │────────────▶│ OldScale                 │
├─────────────────────────┤ 1         1 ├──────────────────────────┤
│ - scale : OldScale&     │             │ + read_grams() : int     │
│ + weight_kg() : double  │             │ + is_calibrated() : bool │
└─────────────────────────┘             └──────────────────────────┘
```

Bewertung: erbt von `WeightSensor` (1), hält `OldScale` per Komposition bzw. Referenz und erbt **nicht** davon (2), Umrechnung g → kg mit `double`-Division (2), Exception (1), `weigh` + `main` (1), UML (2).

---

## Übung 4: Dijkstra

Erwartete Ausgabe ab Stuttgart:

| Depot | km | Weg |
|---|---|---|
| Stuttgart | 0 | – |
| Esslingen | 15 | S → E |
| Ludwigsburg | 20 | S → L (nicht S → E → L = 45) |
| Göppingen | 45 | S → E → G |
| Heilbronn | 55 | S → L → H (nicht S → E → H = 85) |

Bewertung: Adjazenzliste und ungerichtetes `add_road` (3), Exception (1), `priority_queue` als Min-Heap mit `std::greater` (2), Relaxation und Überspringen veralteter Einträge (3), Ausgabe (1).

---

