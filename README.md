## V.04 failo generavimas, skirstymas bei išvedimas su 10 pažymių kiekvienam studentui užtruko: 
- `0,001s su 10 studentų
- `0,004s su 100 studentų
- `0,029s su 1000 studentų
- `0,281s su 10000 studentų
- `2,781s su 100000 studentų

## V.05 Studentų išskirstymas su 10 pažymių kiekvienam studentui užtruko: 

# std::vector

| Studentų skaičius | Trukmė  | 
| ----------------  | ------- | 
| 100               | 0.001s  |
| 1000              | 0.009s  |
| 10000             | 0.092s  |
| 100000            | 0.913s  |
| 1000000           | 8.998s  | 

# std::deque

| Studentų skaičius | Trukmė  | 
| ----------------  | ------- | 
| 100               | 0.001s  |
| 1000              | 0.009s  |
| 10000             | 0.086s  |
| 100000            | 0.865s  |
| 1000000           | 8.458s  |

# std::list

| Studentų skaičius | Trukmė  | 
| ----------------  | ------- | 
| 100               | 0.001s  |
| 1000              | 0.009s  |
| 10000             | 0.091s  |
| 100000            | 0.889s  |
| 1000000           | 8.869s  |

Tokiai paprastai užduočiai, kaip duomenų nuskaitymas ir dėjimas į naujus struktūrų masyvus, pagal atliktus matavimus labiausiai tinka deque konteineris, kuris net puse sekundės sparčiau atlieka darbą už vektorių dirbant su 1000000 dydžio masyvu. List konteineris beveik tiksliai užima vidurį tarp deque ir vector, nuo vieno atsilikdamas panašiai kiek lenkdamas kitą. Programoje nėra manipuliuojama duomenimis jau esančiais masyvuose, todėl išmatuotas yra tik duomenų pridėjimo į skirtingą konteinerį efektyvumas.
