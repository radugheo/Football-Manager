# OOP Template

### Tema 0

- [X] Nume proiect (îl puteți schimba ulterior)
- [X] Scurtă descriere a temei alese, ce v-ați propus să implementați

## Tema 1

#### Cerințe
- [X] definirea a minim 3-4 clase folosind compunere
- [X] constructori de inițializare
- [X] pentru o clasă: constructor de copiere, `operator=` de copiere, destructor
<!-- - [ ] pentru o altă clasă: constructor de mutare, `operator=` de mutare, destructor -->
<!-- - [ ] pentru o altă clasă: toate cele 5 funcții membru speciale -->
- [X] `operator<<` pentru toate clasele
- [X] cât mai multe `const`
- [X] implementarea a minim 3 funcții membru publice pentru funcționalități specifice temei alese
- [X] scenariu de utilizare a claselor definite (crearea de obiecte și apelarea funcțiilor membru publice în main)
- [X] tag de `git`: de exemplu `v0.1`
- [X] serviciu de integrare continuă (CI); exemplu: GitHub Actions

## Tema 2

#### Cerințe
- [X] separarea codului din clase în `.h` (sau `.hpp`) și `.cpp`
- [X] moșteniri
  - [X] funcții virtuale (pure), constructori virtuali (clone)
  - [X] apelarea constructorului din clasa de bază 
  - [X] smart pointers
  - [ ] `dynamic_cast`
- [X] suprascris cc/op= pentru copieri/atribuiri corecte, copy and swap
- [X] excepții
  - [X] ierarhie proprie (cu baza `std::exception` sau derivată din `std::exception`)
  - [X] utilizare cu sens: de exemplu, `throw` în constructor, `try`/`catch` în `main`
- [X] funcții și atribute `static`
- [X] STL
- [X] cât mai multe `const`
- [X] tag de `git`: de exemplu `v0.2`

## Tema 3

#### Cerințe
- [X] 2 șabloane de proiectare (design patterns)
- [ ] o funcție șablon (template) cu sens; minim 2 instanțieri
- [ ] o clasă șablon cu sens; minim 2 instanțieri
- [ ] o specializare pe funcție/clasă șablon
- [ ] tag de `git`: de exemplu `v0.3` sau `v1.0`

##Football Manager

<h3>How to play</h3>
<p>After you choose your team, you can adjust the squad and the desired tactics for the next game, sell or buy players from the transfer market, and of course, simulate the next match.</p>
<p>If you are in top 6 when the regular season ends, you qualify for the Play-Offs. Else, it's the Play-Outs.</p>
<h3>About</h3>
<p>The results of the matches are not entire randomly generated. They depend on the squad and tactics chosen for every match. I tried to get as close as I could to get realistic scores. </p>
<p>Players'value is calculated based on their OVR and age. The younger the player, the higher the price. Of course, the OVR matters too.</p>
<h3>Resources</h3>
<ul>
  <li><a href="https://github.com/effolkronium/random/">Effolkronium Random</a> - Random for modern C++ with convenient API</li>
  <li><a href="https://www.fifacm.com/">FifaCM</a> - for player stats</li>
  <li>Google Pictures for backgrounds and team logos.</li>
</ul>
