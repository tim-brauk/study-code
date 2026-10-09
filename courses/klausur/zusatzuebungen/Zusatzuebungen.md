# Zusatzübungen C++ (Lab-Stoff außerhalb des Probeklausur-Formats)

Die echte Probeklausur (Flottenmanagement) prüft vor allem **UML + OOP + Polymorphie**. Die
folgenden Themen aus den Labs kamen dort nicht vor. Sie sind aber Vorlesungsstoff und eignen
sich gut als Training. Die Lösungen liegen in `loesung/`, zusammengefasst in `loesung/Loesungen.md`.

| Übung | Thema | ca. Zeit |
|---|---|---|
| 1 | Templates & STL | 25 min |
| 2 | Bug Hunt | 25 min |
| 3 | SOLID & Adapter Pattern | 20 min |
| 4 | Graphen & Dijkstra | 15 min |

## Übung 1: Templates & STL

Schreibe die Lösung in `templates.hpp` und teste sie in `main3.cpp`.

**a) (5 P)** `template <typename T> T clamp_value(const T& value, const T& low, const T& high)`
Begrenzt `value` auf `[low, high]`. Ist `low > high`, wirft die Funktion `std::invalid_argument`. Teste mit `int`, `double` und `std::string`.

**b) (5 P)** `template <typename Container> double average(const Container& values)`
Liefert den Mittelwert. Sie muss mit `std::vector<int>`, `std::array<double, 4>` und `std::list<float>` funktionieren. Ist der Container leer, wirft sie `std::domain_error`.

**c) (10 P)** Klassentemplate `RingBuffer<T, std::size_t N>`, intern ein `std::array<T, N>`:
- `void push(const T& value)`: Wenn der Puffer voll ist, wird der **älteste** Wert überschrieben.
- `const T& at(std::size_t index) const`: Index 0 ist der älteste gespeicherte Wert. Ist `index >= size()`, wird `std::out_of_range` geworfen.
- `std::size_t size() const`, `bool is_full() const`

Test: `RingBuffer<int, 3>`, push 1, 2, 3, 4 → Inhalt in Reihenfolge `2 3 4`.

**d) (5 P)** Funktionstemplate `template <typename T> std::string describe(const T& value)`
Liefert `"Wert: <value>"`. Schreibe eine **explizite Spezialisierung** für `bool`, die `"Wert: ja"` bzw. `"Wert: nein"` liefert.

---

## Übung 2: Bug Hunt

Die Datei `bughunt/bughunt.cpp` enthält **11 Fehler**: Compilerfehler, Laufzeitfehler, Logikfehler und Speicher- bzw. Designfehler.

1. Lege eine Tabelle `fehlerliste.md` an mit den Spalten **Zeile | Fehlerart | Beschreibung | Korrektur** (je Fehler 1 P).
2. Korrigiere die Datei so, dass sie ohne Warnungen kompiliert und sich wie in den Kommentaren beschrieben verhält (14 P).

---

## Übung 3: Design

**a) SOLID (8 P)**
Analysiere `design/label_service.cpp`. Benenne **drei** verletzte SOLID-Prinzipien. Gib für jedes an, wo genau es verletzt ist und wie man es beheben würde. Text genügt, du musst nicht refactoren.

**b) Adapter Pattern (9 P)**
In `design/old_scale.hpp` liegt eine alte Waagen-Klasse, die du **nicht verändern** darfst. Das neue System erwartet aber dieses Interface:
```cpp
class WeightSensor
{
public:
    virtual ~WeightSensor() = default;
    virtual double weight_kg() const = 0;
};
```
Schreibe einen **Objekt-Adapter** `ScaleAdapter`. Er rechnet Gramm in kg um und wirft `std::runtime_error`, wenn die Waage nicht kalibriert ist. Schreibe dazu eine Funktion `void weigh(const WeightSensor& sensor)`, die das Gewicht ausgibt, und teste beides in `main`. Skizziere auch kurz das UML des Adapters mit `WeightSensor`, `ScaleAdapter` und `OldScale`.

---

## Übung 4: Routenplanung mit Graphen

Die Depots sind über Straßen verbunden. Die Straßen sind ungerichtet und nach Entfernung in km gewichtet:

| von | nach | km |
|---|---|---|
| Stuttgart (0) | Esslingen (1) | 15 |
| Stuttgart (0) | Ludwigsburg (2) | 20 |
| Esslingen (1) | Ludwigsburg (2) | 30 |
| Esslingen (1) | Göppingen (3) | 30 |
| Ludwigsburg (2) | Heilbronn (4) | 35 |
| Göppingen (3) | Heilbronn (4) | 80 |
| Esslingen (1) | Heilbronn (4) | 70 |

Implementiere eine Klasse `RouteNetwork` mit einer **Adjazenzliste**. Sie braucht:
- `add_road(int from, int to, double km)`, ungültige Knoten → `std::out_of_range`
- `std::vector<double> shortest_distances(int start) const` mit **Dijkstra** und `std::priority_queue`

Gib die kürzesten Entfernungen von Stuttgart zu allen Depots aus.
