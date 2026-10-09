# Probeklausur 01 – Paketzustelldienst

*Im Stil der Probeklausur „Flottenmanagementsystem“ von Prof. Braunagel*

**Bearbeitungszeit:** 2 h  **Typ:** Einzelarbeit  **Hilfsmittel:** Visual Studio, C++-Dokumentation

---

## 1. Problemstellung

Ein regionaler Paketdienst möchte die Zustellung seiner Pakete digital verwalten. Dafür soll
ein objektorientiertes Softwaresystem in C++ entwickelt werden.

Der Paketdienst verschickt unterschiedliche Paketarten:
- Standardpakete
- Expresspakete

Alle Pakete besitzen gemeinsame Eigenschaften:
- eine eindeutige Sendungsnummer, die automatisch vergeben wird (beginnend bei 1000)
- das Gewicht in kg
- die Postleitzahl des Empfängers
- den Zustellstatus („im Depot“, „in Zustellung“ oder „zugestellt“)
- den momentan zuständigen Zusteller
- den Versandpreis, der **nicht gespeichert**, sondern immer aus den anderen Daten berechnet wird

Bei einem Standardpaket wird zusätzlich gespeichert, ob es sich um Sperrgut handelt.
Ein Standardpaket kostet 4,99 € + 0,50 € pro kg, bei Sperrgut kommen 10,00 € dazu.
Bei einem Expresspaket ist die garantierte Zustellzeit in Stunden wichtig. Ein Expresspaket
kostet das Doppelte eines (normalen) Standardpakets gleichen Gewichts. Ist die
garantierte Zustellzeit 12 Stunden oder kürzer, kommen weitere 5,00 € dazu.

Neu erstellte Pakete befinden sich im Depot und haben noch keinen Zusteller. Ein Paket darf
nicht schwerer als 31,5 kg sein.

Zu jedem Paket lassen sich mit der Funktion `printInfo()` alle Attribute in einer Tabelle mit
zwei senkrecht ausgerichteten Spalten auf dem Terminal ausgeben. Zwei Ausgabebeispiele:

```
Type                Standard
Tracking No         1000
Weight              4 kg
Postal Code         88212
Bulky Goods         No
Price               6.99 EUR
Status              In Depot
Courier             None
--------------------------------------------------
Type                Express
Tracking No         1001
Weight              2.5 kg
Postal Code         88214
Delivery Time       8 h
Price               17.48 EUR
Status              In Delivery
Courier             Anna Berger
--------------------------------------------------
```

Auch die **Zusteller** werden über die Software verwaltet. Ein Zusteller hat eine ID, einen Namen,
eine maximale Zuladung in kg und eine Liste der Postleitzahlen, die er beliefert. Die ID soll
nur einmalig gesetzt werden können und muss über alle Zusteller hinweg eindeutig sein. Da sich
die Liefergebiete ändern können, soll für die Postleitzahlen ein passender Container aus der
Standardbibliothek verwendet werden, in dem man suchen kann. Es sollen Methoden vorhanden sein,
um Postleitzahlen hinzuzufügen und zu entfernen.

Ein Zusteller kann **mehrere** Pakete in sein Fahrzeug laden, aber nur, wenn
- das Paket sich im Depot befindet,
- die Postleitzahl des Pakets zu seinen Liefergebieten gehört und
- die aktuelle Zuladung zusammen mit dem neuen Paket seine maximale Zuladung nicht überschreitet.

Die aktuelle Zuladung wird aus den geladenen Paketen berechnet. Beim Laden wechselt das Paket in
den Status „in Zustellung“. Mit einer weiteren Methode stellt der Zusteller alle geladenen Pakete
zu. Sie erhalten dann den Status „zugestellt“, und das Fahrzeug ist anschließend leer.

Alle Pakete werden in einem **Depot** verwaltet. Ein Depot hat einen Namen. Wird ein Depot
aufgelöst, werden auch alle seine Pakete aus dem System gelöscht. Ein Paket kann im Depot über
seine Sendungsnummer gesucht werden.

**Weitere Requirements:**
- Verwenden Sie mindestens eine abstrakte Klasse und ein statisches Attribut.
- Verwenden Sie für den Zustellstatus einen geeigneten, typsicheren Datentyp.
- Orientieren Sie sich am Prinzip der Datenkapselung und implementieren Sie die nötigen Getter- und Setter-Methoden.
- Stellen Sie sicher, dass Ihr Code wiederverwendbar und erweiterbar ist.
- Ungültige Werte (z.B. ein Gewicht von 40 kg) sollen mit einer Exception abgelehnt werden.

---

## 2. Abgabeumfang

**a)** Erstellen Sie ein UML-Klassendiagramm, das als Basis für das geplante Softwaresystem dient
und die oben beschriebenen Anforderungen erfüllt. Darzustellen sind:
- alle Attribute und Methoden
- Sichtbarkeiten
- Datentypen
- zusätzliche Eigenschaften bei konstanten, statischen, abgeleiteten, eindeutigen, virtuellen usw. Methoden, Attributen und Parametern
- Parameterrichtungen
- Klassenbeziehungen mit Navigierbarkeit, Multiplizität und Beziehungsnamen

*Hinweis: Um Zeit zu sparen, genügt es, pro Klasse jeweils nur eine Getter- und eine Setter-Methode darzustellen.*

**b)** Implementieren Sie nun das Softwaresystem in C++. Folgen Sie dabei der Coding Convention
für C++ aus der Vorlesung. Orientieren Sie sich an Ihrem Klassendiagramm, d.h. der Code soll alle
Spezifikationen Ihres Diagramms erfüllen. Ergänzen Sie den Code um alle technischen Details, die
typischerweise nicht im Klassendiagramm stehen, aber für die korrekte Umsetzung nötig sind.

*Hinweis 1: Alle relevanten Getter- und Setter-Methoden müssen implementiert werden.*
*Hinweis 2: Funktions-Header müssen NICHT dokumentiert werden.*

**c)** Erzeugen Sie in Ihrer `main`-Funktion:
- ein Depot mit mindestens einem Paket jeder Art (insgesamt mindestens 3 Pakete),
- zwei Zusteller, die in einem Vector-Container gespeichert werden.

Laden Sie Pakete in die Fahrzeuge der Zusteller. Zeigen Sie dabei mindestens einen Fall, in dem
das Laden abgelehnt wird, und einen Fall, in dem ein ungültiges Paket eine Exception auslöst, die
abgefangen wird. Geben Sie anschließend in einer Schleife die Daten aller Pakete über einen
Basisklassenzeiger aus. Lassen Sie danach einen Zusteller seine Pakete zustellen und geben Sie
die Pakete erneut aus.

**d)** Das Programm muss erfolgreich und fehlerfrei auf Ihrer Prüfungsmaschine kompilierbar sein.

**e)** Beantworten Sie die folgenden Fragen direkt in Ihrem Code:
1. Warum benötigt eine polymorphe Basisklasse einen virtuellen Destruktor? Was passiert ohne ihn?
2. Die Beziehung zwischen Depot und Paket ist eine andere als die zwischen Zusteller und Paket.
   Benennen Sie beide Beziehungsarten und zeigen Sie, woran man den Unterschied in Ihrem Code erkennt.
