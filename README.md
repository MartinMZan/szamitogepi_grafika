# szamitogepi_grafika

Data jegyzék linkje: https://drive.google.com/file/d/1XGZBsEkHPAvlpfFhqRw96VigA0A8hOcR/view?usp=sharing

Féléves feladatom egy ügyességi játékot foglal magában.
A játék lényege, hogy ahogy a játékos elindította a labda szimulációt (játékot) a program aktivizálja egy labda mozgását.
A játékos akkor nyeri meg a játékot, hogyha több mint 60 másodpercen át ki tudja kerülni azt, hogy egy labda nekiütközzön.
A játékos veszít, hogyha egy labda belecsapódik a játékosba.
A játék nehezítése érdekében a program időközönként újabb labdákat indít útjának. 
A labdák véletlen irányba mozognak (a nehézség növelése érdekében megfelelő véletlen értékekkel), ütköznek a fallal, a többi labdával és a játékossal is.


A minimális elvárások közül teljesíti:

-Kamerakezelés: alapból benne volt a Cube példában

-Objektumok: több modellt is használ, melyet külön fájlokból be lehet tölteni

-Animáció, mozgatás: a benne lévő labda modell "mozgatható" (később kifejtem), illetve fényerő állítható

-Textúrák: minden modell kapott textúrát, illetve több textúra is töltődik a játék megnyerése/elvesztése esetén

-Fények: állíthatóak a leírásnak megfelelően, + és - gombokkal

-Használati útmutató: implementálva, U (User's guide) gomb lenyomására jelenik meg

-Strukturáltság, könnyen kezelés: A 3 többlet funkcióból 2-nek saját header és c állományokathoztam létre a strukturáltság érdekében, próbáltam sokat mondó változóneveket adni, illetve a gombokat és a hozzátartozó funkciókat beszédesen próbáltam kiosztani.

A többlet funkciók közül teljesíti:

	1) Fizika: Több pattogó labda szimulációját készítettem el programomban.

	Felhasználói szemszögből:
A szimuláció (játék) B (Bounce vagy Ball) gombnyomásra indul. A labdák ütközés után a megfelelő irányba mennek tovább. Amint a játék befejeződött, a labda újra a kezdeti pozíciójára kerül és a felhasználó ha szeretné szintén a kétszeri B gomb lenyomásával új szimulációt indíthat.

	Programozói szemszögből:
A labda ütközésének eseményére (mely egy későbbi pontban van kifejtve) irányvektort kellett számolni a két ütközött labda között. Ehhez lett igazítva az ütközés utáni labdák iránya és X, Y, valamint Z iránybeli sebessége.
A labda mozgásához több eseményt is figyelembe kellett venni, sebességet számolni.

	2) Átlátszóság: Átlátszó textúrákat alkalmaztam a feladatban.
	
	Felhasználói szemszögből:
A játékos amint elindítja a programot rögtön láthatja azt, hogy a fal egy része, egy sávban átlátszó. Ezen sáv mögött egy festményt talál. Ha közelebb megy az ablakhoz láthatja azt is, hogy az átlátszó textúra valójában kissé "homályos" is.

	Programozói szemszögből:
Jó textúrát sem volt könnyű találni, hogy legyen megfelelő mértékben átlátszó is, és esztétikus is. Mindemellett a kiterjesztésre is kifejezetten figyelni kellett, volt olyan hogy transzparens képként volt hírdetve egy kép és valójában jpg kiterjesztésű volt, melyről tudni kellett hogy nem támogatja az átltászóságot.
Amire még kifejezetten figyelni kellett, hogy a háttér (ez esetben a festmény) hamarabb legyen renderelve mint maga az átlátszó objektum.

	3) Ütközésvizsgálat: A program érzékeli a következő ütközéseket: játékos-pálya, játékos-labda, labda-pálya, labda-labda

	Felhasználói szemszögből:
A játékos nem tud átmenni a falon.

A játékosnak, ha labda ütközik elveszíti a játékot.

A labda, ha nekimegy a pálya szélének visszapattan.

A labda, ha nekiütközik egy másik labdának elmozdul mindkét labda.


	Programozói szemszögből:
Külön header állományt hoztam létre a jobban átláthatóság és a kezelhetőség végett.
A játékos-labda, illetve a labda-labda ütközés volt érdekesebb. Előbbinél a labda középpontjának és a kamera pozíciójának távolságát kellett kiszámolni.
A labda-labda ütközéskor a két labda középpontjának távolságágát kellett viszonyítani a labda méretéhez, figyelembevéve azt is, hogy a labdák széleinek ütközését vizsgáljuk.
A dolog általam legnehezebbnek része az ütközés detektálása volt, a feltételeket átlátni utólag is kissé kusza.

	Használati útmutató:

	Billentyűk:
W 	- előre sétálás
	
S 	- hátra sétálás
	
A	- balra sétálás
	
D	- jobbra sétálás
	
"+"	- fényerő fel
	
"-"	- fényerő le
	
t	- textúra előnézet
	
u	- felhasználói útmutató
	
b	- labda szimuláció indítása
	
ESC	- kilépés

	Egér:
Bármelyik egérgomb lenyomása után az egeret húzva lehet körbenézni.
