# Probeklausur 02 – Kfz-Werkstatt

*Im Stil der Probeklausur „Flottenmanagementsystem“ von Prof. Braunagel und der Probeklausur 01*

**Bearbeitungszeit:** 2 h  **Typ:** Einzelarbeit  **Hilfsmittel:** Visual Studio, C++-Dokumentation

---

## 1. Problemstellung

Eine Kfz-Werkstatt möchte ihre Werkstattaufträge digital verwalten. Dafür soll ein
objektorientiertes Softwaresystem in C++ entwickelt werden.

Die Werkstatt nimmt unterschiedliche Auftragsarten an:
- Inspektionen
- Reparaturen

Alle Aufträge besitzen gemeinsame Eigenschaften:
- eine eindeutige Auftragsnummer, die automatisch vergeben wird (beginnend bei 500)
- das Kennzeichen des Fahrzeugs (darf nicht leer sein)
- die geschätzte Arbeitszeit in Stunden
- den Auftragsstatus („offen“, „in Bearbeitung“ oder „abgeschlossen“)
- den zuständigen Mechaniker
- die benötigte Qualifikation, die ein Mechaniker haben muss, um den Auftrag zu bearbeiten
- den Preis, der **nicht gespeichert**, sondern immer aus den anderen Daten berechnet wird

Der Stundensatz der Werkstatt beträgt 65,00 €.

Bei einer **Inspektion** wird zusätzlich gespeichert, ob eine Hauptuntersuchung (HU) mit
durchgeführt wird. Eine Inspektion kostet eine Grundgebühr von 49,00 € plus den Stundensatz
pro Arbeitsstunde. Mit Hauptuntersuchung kommen 119,00 € dazu. Für jede Inspektion wird
immer die Qualifikation `"Maintenance"` benötigt.

Bei einer **Reparatur** werden zusätzlich die benötigte Qualifikation (z.B. `"Engine"`,
`"Electrics"`, `"Body"`) und die Materialkosten in € gespeichert. Eine Reparatur kostet den
Stundensatz pro Arbeitsstunde (Arbeitslohn) plus die Materialkosten. Dauert eine Reparatur
**mehr als 8 Stunden**, gewährt die Werkstatt 10 % Rabatt auf den Arbeitslohn (nicht auf das
Material).

Neu angelegte Aufträge sind offen und haben noch keinen Mechaniker. Die Arbeitszeit muss
größer als 0 und darf höchstens 40 Stunden sein. Materialkosten dürfen nicht negativ sein.

Zu jedem Auftrag lassen sich mit der Funktion `printInfo()` alle Attribute in einer Tabelle mit
zwei senkrecht ausgerichteten Spalten auf dem Terminal ausgeben. Zwei Ausgabebeispiele:

```
Type                Inspection
Order No            500
License Plate       RV-AB 123
Work Hours          1.5 h
Qualification       Maintenance
Main Inspection     Yes
Price               265.50 EUR
Status              Open
Mechanic            None
--------------------------------------------------
Type                Repair
Order No            501
License Plate       FN-XY 42
Work Hours          10 h
Qualification       Engine
Parts Cost          350.00 EUR
Price               935.00 EUR
Status              In Progress
Mechanic            Lena Vogt
--------------------------------------------------
```

Auch die **Mechaniker** werden über die Software verwaltet. Ein Mechaniker hat eine ID, einen
Namen, eine maximale Arbeitszeit in Stunden (muss größer als 0 sein) und eine Liste seiner
Qualifikationen. Die ID soll nur einmalig gesetzt werden können und muss über alle Mechaniker
hinweg eindeutig sein. Da Mechaniker Weiterbildungen machen, soll für die Qualifikationen ein
passender Container aus der Standardbibliothek verwendet werden, in dem man suchen kann und der
keine doppelten Einträge enthält. Es sollen Methoden vorhanden sein, um Qualifikationen
hinzuzufügen, zu entfernen und abzufragen.

Einem Mechaniker können **mehrere** Aufträge zugewiesen werden, aber nur, wenn
- der Auftrag offen ist,
- der Mechaniker die benötigte Qualifikation des Auftrags besitzt und
- seine aktuelle Auslastung zusammen mit dem neuen Auftrag seine maximale Arbeitszeit nicht überschreitet.

Die aktuelle Auslastung wird aus den Arbeitszeiten der zugewiesenen Aufträge berechnet. Bei der
Zuweisung wechselt der Auftrag in den Status „in Bearbeitung“. Mit einer weiteren Methode
schließt der Mechaniker **einen** seiner Aufträge über die Auftragsnummer ab. Der Auftrag erhält
dann den Status „abgeschlossen“ und zählt nicht mehr zur Auslastung des Mechanikers. Der Auftrag
merkt sich aber weiterhin, welcher Mechaniker ihn bearbeitet hat. Gehört der Auftrag nicht zu
diesem Mechaniker, wird das über den Rückgabewert gemeldet.

Alle Aufträge werden in einer **Werkstatt** verwaltet. Eine Werkstatt hat einen Namen. Wird eine
Werkstatt aufgelöst, werden auch alle ihre Aufträge aus dem System gelöscht. Ein Auftrag kann in
der Werkstatt über seine Auftragsnummer gesucht werden. Außerdem kann ein Auftrag über seine
Auftragsnummer aus der Werkstatt entfernt (gelöscht) werden, aber **nur, wenn er abgeschlossen
ist**. Andernfalls soll eine Exception geworfen werden. Die Werkstatt kann ihren Umsatz
berechnen: die Summe der Preise aller abgeschlossenen Aufträge.

**Weitere Requirements:**
- Verwenden Sie mindestens eine abstrakte Klasse und ein statisches Attribut.
- Verwenden Sie für den Auftragsstatus einen geeigneten, typsicheren Datentyp.
- Orientieren Sie sich am Prinzip der Datenkapselung und implementieren Sie die nötigen Getter- und Setter-Methoden.
- Stellen Sie sicher, dass Ihr Code wiederverwendbar und erweiterbar ist.
- Ungültige Werte (z.B. eine Arbeitszeit von 0 h) sollen mit einer Exception abgelehnt werden.

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
- eine Werkstatt mit mindestens zwei Aufträgen jeder Art (insgesamt mindestens 4 Aufträge),
- zwei Mechaniker mit unterschiedlichen Qualifikationen, die in einem Vector-Container gespeichert werden.

Weisen Sie den Mechanikern Aufträge zu. Zeigen Sie dabei, dass **jede der drei Bedingungen**
einzeln zu einer Ablehnung führen kann, und einen Fall, in dem ein ungültiger Auftrag eine
Exception auslöst, die abgefangen wird. Geben Sie anschließend in einer Schleife die Daten aller
Aufträge über einen Basisklassenzeiger aus. Lassen Sie danach die Mechaniker Aufträge abschließen,
geben Sie den Umsatz der Werkstatt aus und zeigen Sie, dass ein nicht abgeschlossener Auftrag
nicht entfernt werden kann, ein abgeschlossener aber schon. Geben Sie die Aufträge zum Schluss
erneut aus.

**d)** Das Programm muss erfolgreich und fehlerfrei auf Ihrer Prüfungsmaschine kompilierbar sein.

**e)** Beantworten Sie die folgenden Fragen direkt in Ihrem Code:
1. Warum sollten Kopierkonstruktor und Zuweisungsoperator Ihrer Auftragsklasse verboten werden? Was würde bei einer Kopie passieren?
2. Erklären Sie den Unterschied zwischen einer virtuellen und einer rein virtuellen Methode und wozu das Schlüsselwort `override` dient. Warum kann man kein Objekt Ihrer Auftrags-Basisklasse anlegen?
3. Warum darf die Werkstatt nur abgeschlossene Aufträge löschen? Was würde sonst passieren?
