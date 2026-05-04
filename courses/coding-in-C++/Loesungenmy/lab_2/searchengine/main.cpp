/*
 * ============================================================
 *  Search Engine System – C++ Implementation
 *  Basierend auf dem UML-Klassendiagramm (Part I)
 * ============================================================
 */

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>   // std::sort, std::transform
#include <cctype>      // std::tolower

// ============================================================
//  Hilfs-Funktion: String in Kleinbuchstaben umwandeln
//  (für die Suche ohne Groß-/Kleinschreibung)
// ============================================================
std::string toLower(const std::string& s) {
    std::string result = s;
    std::transform(result.begin(), result.end(), result.begin(),
                   [](unsigned char c) { return std::tolower(c); });
    return result;
}


// ============================================================
//  Klasse: WebResource
//  Entspricht der UML-Klasse "WebResource"
// ============================================================
class WebResource {
private:
    // --- Attribute (alle private → Encapsulation) ---
    std::string url;         // - url : String
    std::string content;     // - content : String
    double      rankScore;   // - rankScore : Double

    // static-Attribut: wird von ALLEN Instanzen geteilt
    // Entspricht "- static indexCount : Int" im UML
    static int indexCount;

public:
    // ----------------------------------------------------------
    //  Konstruktor
    //  Erhöht bei jeder neuen Ressource den Zähler
    // ----------------------------------------------------------
    WebResource(const std::string& url,
                const std::string& content,
                double rankScore)
        : url(url), content(content), rankScore(rankScore)
    {
        indexCount++;   // statischer Zähler hochzählen
    }

    // ----------------------------------------------------------
    //  Destruktor: Zähler wieder verringern
    //  Nur verringern wenn kein Kopier-Konstruktor-Aufruf
    // ----------------------------------------------------------
    ~WebResource() {
        // Nicht verringern - der Zähler zählt erstellte Instanzen
    }

    // ----------------------------------------------------------
    //  Derived Attribute: isPopular
    //  Entspricht "/ isPopular : Boolean {derived}" im UML
    //  → wird BERECHNET, nicht gespeichert
    //  {query} = ändert keinen Zustand (const)
    // ----------------------------------------------------------
    bool isPopular() const {
        return rankScore > 0.7;
    }

    // ----------------------------------------------------------
    //  Getter-Methoden {query} = const

    
    // ----------------------------------------------------------
    std::string getUrl() const {          // + getUrl() : String {query}
        return url;
    }

    double getRankScore() const {         // + getRankScore() : Double {query}
        return rankScore;
    }

    std::string getContent() const {      // Zusatz für die Suchlogik
        return content;
    }

    static int getIndexCount() {          // Zugriff auf statischen Zähler
        return indexCount;
    }

    // ----------------------------------------------------------
    //  display() – gibt den internen Zustand lesbar aus
    //  + display() : void
    // ----------------------------------------------------------
    void display() const {
        std::cout << "  URL      : " << url          << "\n"
                  << "  Content  : " << content      << "\n"
                  << "  Rank     : " << rankScore     << "\n"
                  << "  Popular  : " << (isPopular() ? "ja" : "nein") << "\n";
    }

    // ----------------------------------------------------------
    //  checkPopularity() – gibt Popularität zurück {query}
    // ----------------------------------------------------------
    bool checkPopularity() const {        // + checkPopularity() : Boolean {query}
        return isPopular();
    }
};

// Statisches Attribut muss außerhalb der Klasse definiert werden
int WebResource::indexCount = 0;


// ============================================================
//  Klasse: SearchQuery
//  Entspricht der UML-Klasse "SearchQuery"
// ============================================================
class SearchQuery {
private:
    // --- Attribute ---
    std::string queryText;    // - queryText : String
    int         maxResults;   // - maxResults : Int
    std::string createdAt;    // - createdAt : DateTime (hier als String)

public:
    // ----------------------------------------------------------
    //  Konstruktor
    //  maxResults hat Standardwert 10 (wie im UML vermerkt)
    // ----------------------------------------------------------
    SearchQuery(const std::string& queryText,
                int maxResults = 10,
                const std::string& createdAt = "2026-04-30")
        : queryText(queryText), maxResults(maxResults), createdAt(createdAt)
    {}

    // ----------------------------------------------------------
    //  isValid() – prüft ob die Anfrage gültig ist
    //  + isValid() : Boolean {query}
    //  Bedingung: queryText darf nicht leer sein
    // ----------------------------------------------------------
    bool isValid() const {
        return !queryText.empty();
    }

    // ----------------------------------------------------------
    //  Getter {query} = const
    // ----------------------------------------------------------
    std::string getQueryText() const {
        return queryText;
    }

    int getMaxResults() const {
        return maxResults;
    }

    // ----------------------------------------------------------
    //  setMaxResults() – einzige Methode, die Zustand ändert
    //  + setMaxResults(in n : Int) : void
    // ----------------------------------------------------------
    void setMaxResults(int n) {
        maxResults = n;
    }

    // ----------------------------------------------------------
    //  display() – gibt den internen Zustand lesbar aus
    // ----------------------------------------------------------
    void display() const {
        std::cout << "  Query     : \"" << queryText    << "\"\n"
                  << "  MaxResult : " << maxResults   << "\n"
                  << "  Erstellt  : " << createdAt    << "\n"
                  << "  Gültig    : " << (isValid() ? "ja" : "nein") << "\n";
    }
};


// ============================================================
//  Klasse: SearchEngine
//  Entspricht der UML-Klasse "SearchEngine"
// ============================================================
class SearchEngine {
private:
    // --- Attribute ---
    std::string engineName;                    // - engineName : String
    int         maxIndexSize;                  // - maxIndexSize : Int
    std::vector<WebResource> index;            // interne Ressourcen-Liste

    // static-Attribut: Gesamtzahl aller ausgeführten Queries
    // Entspricht "- static totalQueryCount : Int {default=0}" im UML
    static int totalQueryCount;

    // ----------------------------------------------------------
    //  indexResource() – fügt eine Ressource zum Index hinzu
    //  private, weil nur intern genutzt
    //  - indexResource(in r : WebResource) : void
    // ----------------------------------------------------------
    void indexResource(const WebResource& r) {
        if ((int)index.size() < maxIndexSize) {
            index.push_back(r);
        } else {
            std::cout << "[Warnung] Index voll! Ressource nicht hinzugefügt.\n";
        }
    }

public:
    // ----------------------------------------------------------
    //  Konstruktor
    // ----------------------------------------------------------
    SearchEngine(const std::string& name, int maxIndexSize = 1000000)
        : engineName(name), maxIndexSize(maxIndexSize)
    {}

    // ----------------------------------------------------------
    //  addResource() – öffentliche Schnittstelle zum Hinzufügen
    //  Ruft intern indexResource() auf
    // ----------------------------------------------------------
    void addResource(const WebResource& r) {
        indexResource(r);
    }

    // ----------------------------------------------------------
    //  executeQuery() – die eigentliche Suchlogik
    //  + executeQuery(in q : SearchQuery) : List<WebResource>
    //
    //  Ablauf:
    //  1. Validierung der Anfrage
    //  2. Suche: queryText im content jeder Ressource prüfen
    //     (case-insensitive mit toLower)
    //  3. Sortierung: nach rankScore absteigend
    //  4. Rückgabe: nur die ersten maxResults Treffer
    // ----------------------------------------------------------
    std::vector<WebResource> executeQuery(const SearchQuery& q) {
        // 1. Validierung
        if (!q.isValid()) {
            std::cout << "[Fehler] Ungültige Suchanfrage!\n";
            return {};
        }

        totalQueryCount++;   // statischen Zähler erhöhen

        std::string needle = toLower(q.getQueryText());

        // 2. Suche – alle Ressourcen durchsuchen
        std::vector<WebResource> matches;
        for (const WebResource& res : index) {
            std::string haystack = toLower(res.getContent());
            // Prüfen ob der Suchbegriff im Inhalt vorkommt
            if (haystack.find(needle) != std::string::npos) {
                matches.push_back(res);
            }
        }

        // 3. Sortierung nach rankScore (absteigend)
        std::sort(matches.begin(), matches.end(),
                  [](const WebResource& a, const WebResource& b) {
                      return a.getRankScore() > b.getRankScore();
                  });

        // 4. Auf maxResults begrenzen
        int limit = q.getMaxResults();
        if ((int)matches.size() > limit) {
            matches.erase(matches.begin() + limit, matches.end());
        }

        return matches;
    }

    // ----------------------------------------------------------
    //  getQueryCount() – gibt Anzahl ausgeführter Queries zurück
    //  + getQueryCount() : Int {query}
    // ----------------------------------------------------------
    static int getQueryCount() {
        return totalQueryCount;
    }

    // ----------------------------------------------------------
    //  resetStats() – setzt Statistik zurück
    //  + resetStats() : void
    // ----------------------------------------------------------
    static void resetStats() {
        totalQueryCount = 0;
    }

    // ----------------------------------------------------------
    //  displayInfo() – gibt Systeminfo aus
    //  + displayInfo() : void
    // ----------------------------------------------------------
    void displayInfo() const {
        std::cout << "  Engine    : " << engineName           << "\n"
                  << "  Im Index  : " << index.size()         << " Ressourcen\n"
                  << "  Max Index : " << maxIndexSize          << "\n"
                  << "  Queries   : " << totalQueryCount       << "\n";
    }
};

// Statisches Attribut definieren
int SearchEngine::totalQueryCount = 0;


// ============================================================
//  Hilfsfunktion: Suchergebnisse formatiert ausgeben
// ============================================================
void printResults(const std::vector<WebResource>& results,
                  const SearchQuery& q)
{
    std::cout << "\n╔══════════════════════════════════════════════╗\n";
    std::cout << "  Suchanfrage: \"" << q.getQueryText()
              << "\"  (max. " << q.getMaxResults() << " Treffer)\n";
    std::cout << "╚══════════════════════════════════════════════╝\n";

    if (results.empty()) {
        std::cout << "  → Keine Treffer gefunden.\n";
        return;
    }

    std::cout << "  → " << results.size() << " Treffer:\n\n";
    int rank = 1;
    for (const WebResource& res : results) {
        std::cout << "  [" << rank++ << "] ";
        res.display();
        std::cout << "\n";
    }
}


// ============================================================
//  main() – Demonstration der Funktionalität
// ============================================================
int main() {

    std::cout << "========================================\n";
    std::cout << "  Search Engine System – Demonstration \n";
    std::cout << "========================================\n\n";

    // --------------------------------------------------------
    //  1. Search Engine erstellen
    // --------------------------------------------------------
    SearchEngine engine("ClaudeSearch v1");

    std::cout << "[1] Engine-Info (vor dem Befüllen):\n";
    engine.displayInfo();

    // --------------------------------------------------------
    //  2. Web-Ressourcen erstellen und in den Index laden
    // --------------------------------------------------------
    std::cout << "\n[2] Ressourcen werden indexiert...\n\n";

    engine.addResource(WebResource(
        "wikipedia.org/machine_learning",
        "Machine learning is a subset of artificial intelligence. "
        "It enables systems to learn from data automatically.",
        0.92
    ));

    engine.addResource(WebResource(
        "britannica.com/ai",
        "Artificial intelligence (AI) refers to simulation of human "
        "intelligence in machines programmed to think like humans.",
        0.85
    ));

    engine.addResource(WebResource(
        "arxiv.org/deep-learning",
        "Deep learning uses neural networks with many layers. "
        "It is a machine learning technique for pattern recognition.",
        0.78
    ));

    engine.addResource(WebResource(
        "medium.com/python-tutorial",
        "Python is a versatile programming language. "
        "It is widely used in data science and machine learning projects.",
        0.65
    ));

    engine.addResource(WebResource(
        "stackoverflow.com/cpp-basics",
        "C++ is a general-purpose programming language. "
        "It supports object-oriented, procedural and generic programming.",
        0.55
    ));

    engine.addResource(WebResource(
        "geeksforgeeks.org/oop",
        "Object-oriented programming (OOP) uses objects and classes. "
        "Key principles are encapsulation, inheritance and polymorphism.",
        0.72
    ));

    engine.addResource(WebResource(
        "towardsdatascience.com/neural-nets",
        "Neural networks are inspired by the human brain. "
        "They are a core component of deep learning and machine learning.",
        0.88
    ));

    engine.addResource(WebResource(
        "openai.com/gpt",
        "GPT is a large language model based on the Transformer architecture. "
        "It is trained on large datasets using machine learning techniques.",
        0.95
    ));

    std::cout << "  → " << WebResource::getIndexCount()
              << " Ressourcen im Speicher.\n";
    std::cout << "\n[3] Engine-Info (nach dem Befüllen):\n";
    engine.displayInfo();


    // --------------------------------------------------------
    //  3. Suchanfrage 1: "machine learning"
    // --------------------------------------------------------
    std::cout << "\n\n========================================\n";
    std::cout << "  SUCHE 1\n";
    std::cout << "========================================\n";

    SearchQuery q1("machine learning", 3);
    std::cout << "\nAnfrage-Details:\n";
    q1.display();

    auto results1 = engine.executeQuery(q1);
    printResults(results1, q1);


    // --------------------------------------------------------
    //  4. Suchanfrage 2: "programming"
    // --------------------------------------------------------
    std::cout << "\n========================================\n";
    std::cout << "  SUCHE 2\n";
    std::cout << "========================================\n";

    SearchQuery q2("programming", 5);
    std::cout << "\nAnfrage-Details:\n";
    q2.display();

    auto results2 = engine.executeQuery(q2);
    printResults(results2, q2);


    // --------------------------------------------------------
    //  5. Suchanfrage 3: Begriff der nicht existiert
    // --------------------------------------------------------
    std::cout << "\n========================================\n";
    std::cout << "  SUCHE 3 (kein Treffer erwartet)\n";
    std::cout << "========================================\n";

    SearchQuery q3("quantum computing", 5);
    std::cout << "\nAnfrage-Details:\n";
    q3.display();

    auto results3 = engine.executeQuery(q3);
    printResults(results3, q3);


    // --------------------------------------------------------
    //  6. Ungültige Anfrage (leerer String)
    // --------------------------------------------------------
    std::cout << "\n========================================\n";
    std::cout << "  SUCHE 4 (ungültige Anfrage)\n";
    std::cout << "========================================\n";

    SearchQuery q4("");
    std::cout << "\nAnfrage-Details:\n";
    q4.display();

    auto results4 = engine.executeQuery(q4);


    // --------------------------------------------------------
    //  7. Abschluss-Statistik
    // --------------------------------------------------------
    std::cout << "\n========================================\n";
    std::cout << "  STATISTIK\n";
    std::cout << "========================================\n\n";
    engine.displayInfo();

    std::cout << "\n[OK] Programm beendet.\n";
    return 0;
}