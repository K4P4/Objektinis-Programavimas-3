## Naudojimosi instrukcijos:

Versijoms iki v0.4 yra sukurtas makefile esantis pagrindiniame aplanke, naudojantis g++ kompiliatoriumi, linux sistemoje, reikia:
- Konsolėje atsidaryti aplanką
- make
- ./main

## V0.4 failo generavimas, skirstymas bei išvedimas su 10 pažymių kiekvienam studentui užtruko: 
- `0,001s su 10 studentų
- `0,004s su 100 studentų
- `0,029s su 1000 studentų
- `0,281s su 10000 studentų
- `2,781s su 100000 studentų

Kad išbandyti šį generavimą, programos meniu lange reikia pasirinkti 4 variantą

## V0.5 Studentų išskirstymas su 10 pažymių kiekvienam studentui užtruko: 

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

Naudoti cpp failai pateikti konteineriams atitinkamo pavadinimo aplankuose

## V1.0 Studentų išskirstymas su 10 pažymių kiekvienam studentui užtruko: 

# std::vector

| Studentų skaičius | 1 Strategija | 2 Strategija |
| ----------------  | ------------ | ------------ |
| 100               | 0.001s       | 0.002s       |
| 1000              | 0.009s       | 0.088s       |
| 10000             | 0.092s       | 7.829s       |
| 100000            | 0.913s       | 788.002s     |
| 1000000           | 8.998s       | *Per ilgai*  |

Labai greitai ižvelgiamas didelis vector konteinerio minusas - elementų trynimas. Kadangi ištrynus elementą visi po jo esantys elementai turi būti perkopijuojami per vieną vietą, gauname jog esant dideliam elementų, o tai reiškia ir trynimų skaičiui, programos veikimo laikas pailgėja net iki 863 kartų (su 100000 duomenų). Nors naudojamos atminties kiekis sumažėja dvigubai (vietoje trijų konteinerių, kuriuose yra kiekvienas elementas du kartus, turime du konteinerius, kuriuose jie nesikartoja) tai, mano manymu, neatperka tokio milžininško veikimo laiko pailgėjimo, o jei atmintis tampa didele problema, tuomet reiktų naudoti vector konteinerio alternatyvas.

# std::deque

| Studentų skaičius | 1 Strategija | 2 Strategija |
| ----------------  | ------------ | ------------ |
| 100               | 0.001s       | 0.002s       |
| 1000              | 0.009s       | 0.042s       |
| 10000             | 0.086s       | 3.294s       |
| 100000            | 0.865s       | 324.294s     |
| 1000000           | 8.458s       | *Per ilgai*  |

Deque konteinerio situacija panaši kaip ir vector, veikimo laikas lyginant su 1 strategija didėja eksponentiškai. Tačiau lyginant su vector, veikimo laikas yra du kartus trumpesnis, tai yra todėl, kad deque pasižymi savybe išsiskirstyti duomenis į daugiau nei vieną blokus. Rezultatas tas, kad, ištrynus tam tikrą elementą reikia perkopijuoti ne visus elementus, o tik tuos esančius tame pačiame atminties bloke. Nors tai šiek tiek ir pagerina situaciją, bet vis dėlto, tikrai nėra efektyvus sprendimas.

# std::list

| Studentų skaičius | 1 Strategija | 2 Strategija |
| ----------------  | ------------ | ------------ |
| 100               | 0.001s       | 0.001s       |
| 1000              | 0.009s       | 0.008s       |
| 10000             | 0.091s       | 0.082s       |
| 100000            | 0.889s       | 0.811s       |
| 1000000           | 8.869s       | 8.038s       |

Priešingai nei kiti du konteineriai, list tampa netgi efektyvesnis naudojantis antra strategija, kadangi elementai yra išdėstyti ne vienas šalia kito blokuose, o sujungti vienas su kitu double linked list pagrindu. Tai reiškia, jog nors ir priėjimas prie konkretaus elemento yra lėtesnis, bet kai jis prieitas trynimas tėra rodyklės nukreipimas, kas yra labai pigus veiksmas laiko atžvilgiu. Mūsų atveju, kuomet vistiek turi būti iteruoti visi elementai, list konteinerio lėtesnis priėjimas prie elemento tampa nesvarbus ir naudojantis antra strategija tai yra pats sparčiausias užduoties atlikimo būdas.

Naudoti cpp failai pateikti konteineriams atitinkamo pavadinimo aplankuose



