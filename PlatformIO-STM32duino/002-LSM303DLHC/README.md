#

# Akcelerometr i magnetometr LSM303DLHC wbudowany w discovery f401

Pliki:
- HWPort -> portowanie sprzętu
- LibLSM303DLHC -> obsługa LSM303DLHC

# 

Do uruchomienia biblioteki na innym sprzęcie wystarczy dopasować metody do swojego sprzętu zawarte w klasie WHPort, w obecnym stanie są dopasowane do płytki discoveryF401.

## Akcelerometr

Następnie należy stworzyć obiekt LSM303DLHC_ACC z parametrem jako wskaźnik na funkcję która będzie się uruchamiała za każdym razem jak pojawią się nowe dane akcelerometru.

Przed przystąpieniem do konfiguracji i uruchomienia akcelerometru dobrze jest sprawdzić poprawność działania komunikacji poprzez wywołanie metody whoAmI(), która powinna zwrócić właściwość zawartą w id obiektu.

Można od razu uruchomić metodę on() biblioteki bez ustawień ale akcelerometr będzie działał na najniższych możliwych ustawieniach.

W celu poprawnej konfiguracji należy uruchomić kolejno metody:

- resetSoft() -> zerowanie rejestrów wewnętrznych w akcelerometru,
- fullScaleSelect_set() ->  ustawienie zakresu działania akcelerometru w jednostkach g,
- hpfFreq_set() -> ustawienie częstotliwość filtra górnoprzepustowego, ale to tylko konfiguracja filtra a nie włączenie,
- hpfOn_set() -> włączenie lub wyłączenie filtrów górnoprzepustowych.

Teraz dopiero powinno się użyć metody on(), która ustawia częstotliwość pracy, i włącza akcelerometr.
Odczyt wartości akcelerometru powinno się skorelować z funkcją potwierdzającą gotowość danych, która została podana przy tworzeniu obiektu.
#

## Magnetomert


#
Przykład dla discovery F401 - pobieranie danych i wysyłanie na USBCDC w main.cpp.
Poprawny wariant dla płytki discovery F401 dla PlatformIO jest dostępny w moim repozytorium "PlatformIO-STM32duino-extra-board-variant", wraz z opisem konfiguracji.


