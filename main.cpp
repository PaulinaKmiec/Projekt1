// import klas
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

// wczytywanie danych z pliku do tablicy dynamicznej
vector<int> loadData(const char *path) {
    fstream myfile;
    myfile.open(path, std::ios::in);
    vector<int> numbers; //inicjalizacja wektora o nazwie numbers typu calkowitego
    cout << "Wczytywanie danych: " << endl;
    int a;
    while (myfile >> a) { // odczytywanie liczb z pliku
        numbers.push_back(a); //dodawanie elementów na koniec tablicy
        cout << "Wczytano " << a << endl; // wypisanie wczytanej liczby
    }
    myfile.close(); // zamkniecie strumienia po wczytaniu
    return numbers; //zwrócenie wektora
}

// funkcja wyszukujaca podciagi
vector<vector<int> > findAllSubseries(vector<int> numbers) {
    vector<vector<int> > substrings;
// Od tego miejsca funkcje zaczynaja sprawdzac podane dane z pliku
    vector<int> substring;
    for (unsigned i = 0; i < numbers.size(); i++) {  // Petla "for" sprawdza nastepujace po sobie elementy
        for (unsigned j = i; j < numbers.size(); j++) {
            if (substring.empty()) {
                substring.push_back(numbers[j]); //dodanie elementu na koniec zapisanego wektora
                continue;
            }
            if (substring.back() > numbers[j]) { //warunek sprawdza czy ostatni element wektora "substring" jest wiekszy od poprzedniej liczby
                substring.push_back(numbers[j]);
                if (substring.size() > 1) {
                    substrings.push_back(substring);
                }
            } else { //jezeli nastepny element jest wiekszy lub równy numbers[j] program zamyka wektor
                substring.clear();
                break;
            }
        }
    }
    return substrings;
}

//wypisanie elementów wektora w konsoli a
void printSubstring(vector<int> substring) {
    for (unsigned i = 0; i < substring.size(); i++) {
        cout << substring[i] << " ";
    }
    cout << endl;
}

//funkcja wypisujaca wszystkie podciagi w konsoli
void printAllSubstrings(vector<vector<int> > substrings) {
    vector<int> s; //stworzenie pomocniczego wektora "s"
    for (unsigned i = 0; i < substrings.size(); i++) {
        s = substrings[i];
        printSubstring(s); //wypisanie danych za pomoca tej funkcji.
    }
}

// funkcja zapisujaca wektor w pliku tekstowym
void writeToFile(vector<vector<int> > substrings) {
    ofstream myfile;
    myfile.open("scores.txt", std::ios::out);
    vector<int> s;
    if (myfile.is_open()) {
        for (unsigned j = 0; j < substrings.size(); j++) {
            s = substrings[j];
            for (unsigned i = 0; i < s.size(); i++) {
                myfile << s[i] << " ";
            }
            myfile << "\n";
        }
        myfile.close();
    }
}
// funkcja wypisujaca wiadomosc o pustym pliku
void printEmptyVectorMessage(){
    cout << "Wektor liczb jest pusty." << endl; // wypisanie informacji o pustym pliku
}

int main() {
    vector<int> numbers = loadData("numbers.txt"); //odczyt danych do wektora numbers
    if (numbers.empty()) { // sprawdzanie czy wektor nie jest pusty
        printEmptyVectorMessage();
        return 0;
    }
    vector<vector<int> > substrings = findAllSubseries(numbers);
    printAllSubstrings(substrings);
    writeToFile(substrings);
    return 0;
}
