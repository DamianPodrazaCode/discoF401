#

# Żyroskop L3GD20 wbudowany w discovery f401

Pliki:
- HWPort -> portowanie sprzętu
- LibL3GD20 -> obsługa L3GD20

# 

Do uruchomienia biblioteki na innym sprzęcie wystarczy dopasować metody do swojego sprzętu zawarte w klasie WHPort, w obecnym stanie są dopasowane do płytki discoveryF401.

Następnie należy stworzyć obiekt L3GD20 z parametrem jako wskaźnik na funkcję która będzie się uruchamiała za każdym razem jak pojawią się nowe dane żyroskopu.

Przed przystąpieniem do konfiguracji i uruchomienia żyroskopu dobrze jest sprawdzić poprawność działania komunikacji poprzez wywołanie metody whoAmI(), która powinna zwrócić właściwość zawartą w id obiektu.

Można od razu uruchomić metodę on() biblioteki bez ustawień ale żyroskop będzie działał na najniższych możliwych ustawieniach.

W celu poprawnej konfiguracji należy uruchomić kolejno metody:

- resetSoft() -> zerowanie rejestrów wewnętrznych w gyro,
- fullScaleSelect_set() ->  ustawienie zakresu działania żyroskopu w jednostkach dps,
- hpfFreq_set() -> ustawienie częstotliwość filtra górnoprzepustowego, ale to tylko konfiguracja filtra a nie włączenie,
- outFilterSelect() -> włączenie lub wyłączenie filtrów górnoprzepustowych i filtra dolnoprzepustowego2, filtr dolnoprzepustowy1 jest włączany automatycznie przy metodzie on(), wyjaśnienie połączeń wewnętrznych filtrów jest dostępne w DS żyroskopu,

Teraz dopiero powinno się użyć metody on(), która ustawia częstotliwość pracy, częstotliwości filtrów dolnoprzepustowych i uruchamia żyroskop.

Odczyt wartości żyroskopu powinno się skorelować z funkcją potwierdzającą gotowość danych, która została podana przy tworzeniu obiektu.

Przykład dla discovery F401 - pobieranie danych i wysyłanie na USBCDC w main.cpp.
Poprawny wariant dla płytki discovery F401 dla PlatformIO jest dostępny w moim repozytorium "PlatformIO-STM32duino-extra-board-variant", wraz z opisem konfiguracji.
