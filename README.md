# szamitogepi_grafika

Data jegyzék linkje: https://drive.google.com/file/d/1XGZBsEkHPAvlpfFhqRw96VigA0A8hOcR/view?usp=sharing

Féléves feladatom különböző OpenGL-hez kötődő és nem kötődő funkciók implementálását valósítja meg. Egy amolyan bemutató jellegű program.

A minimális elvárások közül teljesíti:

-Kamerakezelés: alapból benne volt a Cube példában

-Objektumok: több modellt is használ, melyet külön fájlokból be lehet tölteni

-Animáció, mozgatás: a benne lévő labda modell "mozgatható" (később kifejtem), illetve fényerő állítható

-Textúrák: minden modell kapott textúrát, a szükségesnél talán több félét is használtam

-Fények: állíthatóak a leírásnak megfelelően, + és - gombokkal

-Használati útmutató: implementálva, U (User's guide) gomb lenyomására jelenik meg

-Strukturáltság, könnyen kezelés: A 3 többlet funkcióból 2-nek saját header és c állományokathoztam létre a strukturáltság érdekében, próbáltam sokat mondó változóneveket adni, illetve a gombokat és a hozzátartozó funkciókat beszédesen próbáltam kiosztani.

A többlet funkciók közül teljesíti:

	1) Fizika: Egy pattogó labda szimulációját készítettem el programomban.

	Felhasználói szemszögből:
A szimuláció B (Bounce vagy Ball) gombnyomásra indul. Ekkor a felhasználó azt látja, hogy a labda leesik, majd visszapattan. Ekkor már nem ugyanolyan magasra pattan fel és ezt egészen addig folytatja, amíg meg nem áll. Amint a pattogás befejeződött és eltelt egy megadott mennyiségű idő a labda újra a kezdeti pozíciójára kerül és a felhasználó ha szeretné szintén a B gomb lenyomásával új szimulációt indíthat.

	Programozói szemszögből:
A labda visszapattanása utáni "energiája" valós életből vett számérték ez az alapból 0.8 értékű energy_loss_factor.
A labda mozgásához több eseményt és eltelt időt is figyelembe kellett venni, sebességet számolni.
Ha azt tapasztaljuk, hogy a labda mozgatása nem teljesen folytonos, esetleg a labda feljebb repül mint kellene annak oka az lehet, hogy a számítógép nem tudja elég gyorsan lefrissíteni a különböző állapotokat. Ekkor célszerű a bounce.c állományban az update_bounce_ball függvényben a speed_constant nevű változó értékét alacsonyabbra venni. Ekkor a labda mozgása lassabb lesz, viszont "könnyebb dolga" lesz a gépnek.

	2) Átlátszóság: Átlátszó textúrákat alkalmaztam a feladatban.
	
	Felhasználói szemszögből:
A játékos amint elindítja a programot rögtön láthatja azt, hogy a fal egy része, egy sávban átlátszó. Ezen sáv mögött egy festményt talál. Ha közelebb megy az ablakhoz láthatja azt is, hogy az átlátszó textúra valójában kissé "homályos" is.

	Programozói szemszögből:
Jó textúrát sem volt könnyű találni, hogy legyen megfelelő mértékben átlátszó is, és esztétikus is. Mindemellett a kiterjesztésre is kifejezetten figyelni kellett, volt olyan hogy transzparens képként volt hírdetve egy kép és valójában jpg kiterjesztésű volt, melyről tudni kellett hogy nem támogatja az átltászóságot.
Amire még kifejezetten figyelni kellett, hogy a háttér (ez esetben a festmény) hamarabb legyen renderelve mint maga az átlátszó objektum.

	3) Ütközésvizsgálat: A programba egy kocka alakú bounding-box implementáció készült.

	Felhasználói szemszögből:
A játékos hogyha odasétál a földből kiálló kockához azt tapasztalhatja, hogy a falán nem tud átsétálni semelyik irányból, körülötte viszont szabadon mozoghat.

	Programozói szemszögből:
Külön struktúrákat hoztam létre a jobban átláthatóság és a kezelhetőség végett.
Célszerűnek találtam kiszámolni a kocka összes pontját.
A dolog általam legnehezebbnek része az ütközés detektálása volt, a feltételeket átlátni utólag is kissé kusza.

Használati útmutató:
	Billentyűk:
	W 	- előre sétálás
	S 	- hátra sétálás
	A	- balra sétálás
	D	- jobbra sétálás
	+	- fényerő fel
	-	- fényerő le
	t	- textúra előnézet
	u	- felhasználói útmutató
	b	- labda szimuláció indítása
	ESC	- kilépés

	Egér:
Bármelyik egérgomb lenyomása után az egeret húzva lehet körbenézni.
