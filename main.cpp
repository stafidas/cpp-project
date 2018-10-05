#include <iostream>
#include <cstdlib>
#include <ctime>
#include <windows.h>
#include <conio.h>

#define BLACK 0
#define BLUE 1
#define GREEN 2
#define CYAN 3
#define RED 4
#define MAGENTA 5
#define BROWN 6
#define LIGHTGREY 7
#define DARKGREY 8
#define LIGHTBLUE 9
#define LIGHTGREEN 10
#define LIGHTCYAN 11
#define LIGHTRED 12
#define LIGHTMAGENTA 13
#define YELLOW 14
#define WHITE 15
#define BLINK 128

#define PROB_NEW_FIRE               5
#define MAX_XWR_AEROS             200
#define MAX_XWR_EDAFOUS           300
#define MAX_VEL_AEROS               5
#define MAX_VEL_EDAFOUS	            2
#define SPACE_X                    30
#define SPACE_Y                    60
#define MAX_XWR_AEROS_KAUSIMA     250
#define MAX_XWR_EDAFOUS_KAUSIMA   310
#define OXIMA_ENERGO              true
#define OXIMA_SE_BLABI	          false
#define MIN_ILIKIA                500
#define MAX_ILIKIA                800
#define PROB_NEW_OXIMA             20
#define PROB_NEW_AEROS             30
#define MAX_OXIMATA                25
#define PROB_OXIMA_SE_BLABI         1
#define TIME_DELAY                100

using namespace std;

int get_rand(int, int);
void sleep_for(int msec);
int get_keyboard_character();
void print_with_color(int, char *);
void print_with_color(int, char);
void print_with_color(int, int);

class oxima{
	protected:
		int thesi_x, thesi_y;             //trexouses syntetagmenes oximatos
		int base_x, base_y;               //thesi bashs
		bool katastasi;                   //katastasi leitourgias
		int ilikia;                       //ilikia oximatos
		int posotita_nerou;               //trexousa posotita nerou oximatos
		int posotita_kausimou;            //trexousa posotita kausimou oximatos
		int xwritikotita_nerou;
		int xwritikotita_kausimou;

		int velocity;                     //taxutita kinishs oximatos
        char type;                        //typos oximatos

	public:
		void get_thesi(int*,int*);
		void set_base(int, int);
		char get_type();
	    bool in_base();
		bool running_status(){return katastasi;}; //epistrefei thn katastasi tou oximatos
		bool beyond_repair();
		void oxima_play();

		// TODO: Orizei to oxima se katastasi blabis
		void make_corrupted(){katastasi= OXIMA_SE_BLABI;};

		void print_oxima();
		virtual void move () = 0;
		virtual void move (int, int) = 0;

		oxima();
};

oxima::oxima() {
  thesi_x = get_rand(0, SPACE_X);
  thesi_y = get_rand(0, SPACE_Y);
  katastasi = OXIMA_ENERGO;
  ilikia = get_rand(MIN_ILIKIA, MAX_ILIKIA);
  type = '?';
}
//synarthsh apothikeyei thn thesi tou oximatos se deiktes
void oxima::get_thesi(int* x, int* y){
	*x=thesi_x;
	*y=thesi_y;
}
//synarthsh pou epistrefei ton typo tou oximatos
char oxima::get_type(){
	return type;
}
//synarthsh poy thetei tis syntetagmenes bashs
void oxima::set_base(int x, int y) {
	base_x = x;
	base_y = y;
}
//synarthsh pou epistrefei an ena oxima einai sthn bash
bool oxima::in_base() {
	if(thesi_x == base_x && thesi_y == base_y) {
		return true;
	}
	return false;
}
//synarthsh pou epistrefei an ena oxima einai se katastasi na episkeyastei h oxi analoga me thn ilikia tou
bool oxima::beyond_repair(){
	if(ilikia <= 0){
		return true;
    }
	return false;
}
//ektupwnei ola ta stoixeia toiu oximatos se mia grammh
void oxima::print_oxima(){
    char t[1000];
 //   sprintf(t, "%c %d X|Y %d|%d\n", type, katastasi, thesi_x, thesi_y);

   cout << type << " " << katastasi << " X|Y:" << thesi_x << "|" << thesi_y << "\tI-" << ilikia << "\tV-" << velocity << "\tPN-" << posotita_nerou << "\tPK-" << posotita_kausimou << "\tXN-" << xwritikotita_nerou << "\tXK-" << xwritikotita_kausimou << "\n";






}

class aeros: public oxima {
      public:
             aeros(int base_x, int base_y);
             void move();
		     void move (int, int);
};

aeros::aeros(int base_x, int base_y)
{
	xwritikotita_nerou = get_rand(MAX_XWR_AEROS/2, MAX_XWR_AEROS);
	xwritikotita_kausimou = get_rand(MAX_XWR_AEROS_KAUSIMA/2, MAX_XWR_AEROS_KAUSIMA);

    posotita_nerou = get_rand(xwritikotita_nerou/2, xwritikotita_nerou);
    posotita_kausimou = get_rand(xwritikotita_kausimou/2, xwritikotita_kausimou);

	velocity = get_rand(MAX_VEL_AEROS / 2, MAX_VEL_AEROS);

	type = 'A';
	set_base(base_x, base_y);
}
//synarthsh tyxaias kinisis twn oximatwn aeros
void aeros::move(){
	int new_x, new_y;

	new_x = get_rand(thesi_x - velocity, thesi_x + velocity);//tyxaia kinisi tou oximatos ston aksona x
	new_y = get_rand(thesi_y - velocity, thesi_y + velocity);//tyxaia kinisi tou oximatos ston aksona y
//elegxos oriwn gia thn kinisi
	if (new_x < 0)
		new_x = 0;
	if (new_y < 0)
		new_y = 0;
	if (new_x >= SPACE_X)
		new_x = SPACE_X - 1;
	if (new_y >= SPACE_Y)
		new_y = SPACE_Y - 1;

	posotita_kausimou -= abs(thesi_x - new_x) + abs(thesi_y - new_y);

	thesi_x = new_x;
	thesi_y = new_y;
}
//synarthsh stoxeumenhs kinisis twn oximatwn aeros
void aeros::move(int goal_x, int goal_y){
	if (thesi_x == goal_x && thesi_y == goal_y)
	   return;

	if (goal_x != thesi_x) {
       if (goal_x > thesi_x) {
          if (thesi_x + velocity >= goal_x) {
             posotita_kausimou -= abs(thesi_x - goal_x);
             thesi_x = goal_x;
          }
          else {
             posotita_kausimou -= velocity;
             thesi_x += velocity;
          }
       }
       else {
          if (thesi_x - velocity <= goal_x) {
             posotita_kausimou -= abs(thesi_x - goal_x);
             thesi_x = goal_x;
          }
          else {
             posotita_kausimou -= velocity;
             thesi_x -= velocity;
          }
       }
    }

   if (goal_y != thesi_y) {
       if (goal_y > thesi_y) {
          if (thesi_y + velocity >= goal_y) {
             posotita_kausimou -= abs(thesi_y - goal_y);
             thesi_y = goal_y;
          }
          else {
             posotita_kausimou -= velocity;
             thesi_y += velocity;
          }
       }
       else {
          if (thesi_y - velocity <= goal_y) {
             posotita_kausimou -= abs(thesi_y - goal_y);
             thesi_y = goal_y;
          }
          else {
             posotita_kausimou -= velocity;
             thesi_y -= velocity;
          }
       }
   }
}


class edafous: public oxima {
      public:
             edafous(int base_x, int base_y);
             void move();
             void move (int, int);
};

edafous::edafous(int base_x, int base_y)
{
	xwritikotita_nerou = get_rand(MAX_XWR_EDAFOUS/2, MAX_XWR_EDAFOUS);
	xwritikotita_kausimou = get_rand(MAX_XWR_EDAFOUS_KAUSIMA/2, MAX_XWR_EDAFOUS_KAUSIMA);

  posotita_nerou = get_rand(xwritikotita_nerou/2, xwritikotita_nerou);
  posotita_kausimou = get_rand(xwritikotita_kausimou/2, xwritikotita_kausimou);

	velocity = get_rand(MAX_VEL_EDAFOUS / 2, MAX_VEL_EDAFOUS);

	type = 'E';
	set_base(base_x, base_y);
}
//synarthsh tyxaias kinisis twn oximatwn efafous
void edafous:: move(){
	// Ta edafous DEN mporoun na pane diagwnia
	int new_x, new_y;

	if (get_rand(0, 100) > 50) {
		new_x = get_rand(thesi_x - velocity, thesi_x + velocity);
	}
	else {
		new_y = get_rand(thesi_y - velocity, thesi_y + velocity);
	}
//elegxos oriwn
	if (new_x < 0)
		new_x = 0;
	if (new_y < 0)
		new_y = 0;
	if (new_x >= SPACE_X)
		new_x = SPACE_X - 1;
	if (new_y >= SPACE_Y)
		new_y = SPACE_Y - 1;

	posotita_kausimou -= abs(thesi_x - new_x) + abs(thesi_y - new_y);

	thesi_x = new_x;
	thesi_y = new_y;
}
//synarthsh stoxeymenhs kinisis twn oximatwn edafous
void edafous::move(int goal_x, int goal_y){
	// Ta edafous DEN mporoun na pane diagwnia

	if (thesi_x == goal_x && thesi_y == goal_y)
	   return;

	if (goal_x != thesi_x) {
       if (goal_x > thesi_x) {
          if (thesi_x + velocity >= goal_x) {
             posotita_kausimou -= abs(thesi_x - goal_x);
             thesi_x = goal_x;
          }
          else {
             posotita_kausimou -= velocity;
             thesi_x += velocity;
          }
       }
       else {
          if (thesi_x - velocity <= goal_x) {
             posotita_kausimou -= abs(thesi_x - goal_x);
             thesi_x = goal_x;
          }
          else {
             posotita_kausimou -= velocity;
             thesi_x -= velocity;
          }
       }
       return;
    }

   if (goal_y != thesi_y) {
       if (goal_y > thesi_y) {
          if (thesi_y + velocity >= goal_y) {
             posotita_kausimou -= abs(thesi_y - goal_y);
             thesi_y = goal_y;
          }
          else {
             posotita_kausimou -= velocity;
             thesi_y += velocity;
          }
       }
       else {
          if (thesi_y - velocity <= goal_y) {
             posotita_kausimou -= abs(thesi_y - goal_y);
             thesi_y = goal_y;
          }
          else {
             posotita_kausimou -= velocity;
             thesi_y -= velocity;
          }
       }
   }
}

class xwros {
	private:
		int has_fire[SPACE_X][SPACE_Y];
		int spreaded_fire[SPACE_X][SPACE_Y];
		int fire_delay[SPACE_X][SPACE_Y];

		int base_x, base_y; 			// Tixaia arxikopoiisi
		oxima * oximata[MAX_OXIMATA];   //Pinakas deiktwn oximatwn
	public:
		void spread_fire(void);
		void create_fire(void);
		int cell_has_fire(int, int);
		void where_is_base(int *, int *);
		void add_fire(int, int, int);
		void clear_fire(int, int, int);

		bool fire_everywhere(void);
		void get_vehicle_and_make_corrupted(void);

		void dhmiourgia_oximatos(void);
		void possible_dhmiourgia_oximatos(void);
        void get_points_info_and_print_data(void);
		void print_space(void);
		xwros();
		~xwros();
		void play();
};

xwros::xwros() {
  int x,y;
   for (x=0; x<SPACE_X; x++){
    for (y=0; y<SPACE_Y; y++){
	 has_fire[x][y] = 0;
	 fire_delay[x][y] = 0;
    }
   }

   base_x = get_rand(0, SPACE_X);
   base_y = get_rand(0, SPACE_Y);

   int i;
   for(i = 0; i < MAX_OXIMATA; i++)
         oximata[i] = 0;

   cout << "Space inited!\n";
}

xwros::~xwros() {
   int i;
   for(i = 0; i < MAX_OXIMATA; i++)
         if (oximata[i]) {
            delete oximata[i];
            oximata[i] = 0;
         }

}
//synarthsh h opoia epitelei pollaples leitourgies poy perigrafontai se parakatw sxolia
void xwros::play() {
   int i;
   for(i = 0; i < MAX_OXIMATA; i++)
         if (oximata[i]) {
            oximata[i]->oxima_play();//kaleitai h synarthsh play() gia kathe oxima
         }

   for(i = 0; i < MAX_OXIMATA; i++)
         if (oximata[i]) {
            if (oximata[i]->beyond_repair() && oximata[i]->in_base()) {
                delete oximata[i];
                oximata[i] = 0;//katastrefetai ena oxima poy einai pera apo to orio episkeyhs opws oristike sthn antistoixh synarthsh
            }
         }
}
//synarthsh gia pithani dhmiourgia oximatos
void xwros::possible_dhmiourgia_oximatos(void){
 //anatrexoume ton pinaka wste na broume mia kenh thesi,pernoume mia pithanotita dhmioyrgias oximatos kai analoga dhmiourgoumne neo oxima
   if (get_rand(0,100)<PROB_NEW_OXIMA) {
      dhmiourgia_oximatos();
   }
 }

//synarthsh gia RHTH dhmiourgia oximatos
void xwros::dhmiourgia_oximatos(void){
   int new_thesi = -1, i;
   for(i = 0; i < MAX_OXIMATA; i++) {
         if (oximata[i] == NULL) {
            new_thesi = i;
            break;
            }
         }

   if (new_thesi == -1)
      return;
   //brogxos if gia kathorismo typou toy dhmiourgithentos oximatos
   if (get_rand(0,100)<PROB_NEW_AEROS ){
      oximata[i] = new aeros(base_x, base_y);
   }
   else {
      oximata[i] = new edafous(base_x, base_y);
   }
 }

//synarthsh diaxeirhshs fwtias ston kosmo
void xwros::spread_fire (void) {
   int x, y, d;

   // Anaptisoume iparxouses fwties
   for (x=0; x<SPACE_X; x++){
    for (y=0; y<SPACE_Y; y++){
			if (fire_delay[x][y] > 0)
			  fire_delay[x][y]--;

     if (cell_has_fire(x,y)){
      add_fire(x, y, 1);
	  }
   }
  }

    // Eksaplwnoume fwties
    for (x=0; x<SPACE_X; x++){
     for (y=0; y<SPACE_Y; y++){
				spreaded_fire[x][y] = has_fire[x][y];
			}
		}

    for (x=0; x<SPACE_X; x++){
     for (y=0; y<SPACE_Y; y++){
       if (spreaded_fire[x][y]){
	        if (get_rand(0, 100) < 5) add_fire(x+1, y, 1);
			    if (get_rand(0, 100) < 5) add_fire(x-1,y,1);
		    	if (get_rand(0, 100) < 5) add_fire(x,y+1,1);
  			  if (get_rand(0, 100) < 5) add_fire(x,y-1,1);
       }
     }
    }

	 // Dimiourgoume, pithanws, mia nea fwtia
	 if (get_rand(0,100) < PROB_NEW_FIRE) {
        create_fire();
     }
}
//synarthsh gia RHTH dhmioyrgia fwtias tyxaia mesa ston kosmo
void xwros::create_fire (void) {
   int x, y, rand_x, rand_y, nx , ny;

	rand_x = get_rand(0, SPACE_X);
	rand_y = get_rand(0, SPACE_Y);
	 // Dimiourgoume, pithanws, mia nea fwtia
   for (x=0; x<SPACE_X; x++){
    for (y=0; y<SPACE_Y; y++){
			nx = (x + rand_x) % SPACE_X;
			ny = (y + rand_y) % SPACE_Y;
     	if (!cell_has_fire(nx, ny) && fire_delay[nx][ny] <= 0){
				cout << "A new fire has been created: [" << nx << ", " << ny << "]-[" << rand_x << ", " << rand_y << "]\n";
      	add_fire(nx, ny, 1);
      	return;
   		}
    }
   }
}

int xwros::cell_has_fire(int x , int y){
	return this->has_fire[x][y];
}

//synarthsh pou apothikeyei thn thesi ths bashs
void xwros::where_is_base (int *x, int *y){
 *x = this->base_x;
 *y = this->base_y;
}
//synarthsh pou prosthetei ena megethos amount fwtias se ena keli
void xwros::add_fire(int x,int y,int amount){
 if (x<0 || y<0 || x>=SPACE_X || y>=SPACE_Y)
   return;

 if (fire_delay[x][y] > 0)
 	return;

 has_fire[x][y] +=amount;
 if(has_fire[x][y] > 100){
  has_fire[x][y] = 100;
 }
}

//synarthsh pou sbhnei kata ena megethos amount thn fwtia se ena keli
void xwros::clear_fire(int x,int y,int amount){
 if (x<0 || y<0 || x>=SPACE_X || y>=SPACE_Y)
   return;

 has_fire[x][y] -= amount;
 if(has_fire[x][y] <= 0){
   has_fire[x][y] = 0;
   fire_delay[x][y] = 10;
  }
}

// I sigkekrimeni sinartisi elegxei an iparxei pantou fwtia kai epistrefei True i False antistoixa
bool xwros::fire_everywhere(void) {
 int x,y;
 for( x=0;x<SPACE_X;x++){
  for(y=0;y<SPACE_Y;y++){
   if( cell_has_fire(x,y)==0){
    return false;
   }
  }
 }

 return true;
}
//synarthsh pou diabazei apo ton xrhsth enan kwdiko kia analoga kalei thn make_corrupted()
void xwros::get_vehicle_and_make_corrupted(){
    int a;

    cout << "Dwse kwdiko oximatos metaksi [0, " << MAX_OXIMATA << "):";
    cin >> a;
    if (a < 0 || a >= MAX_OXIMATA || !oximata[a]) {
        cout << "Den iparxei oxima me ton sigkekrimeno kwdiko!\n";
        return;
    }

    if (oximata[a]->running_status() == OXIMA_SE_BLABI) {
        cout << "Hello! Afto to oxima, einai idi se blabi!\n";
    }
    else {
        oximata[a]->make_corrupted();
    }
}

//synarthsh pou ektypwnei ta stoixeia enos shmeiou toy xarth pou epilegei o xrhsths
void xwros::get_points_info_and_print_data(){
     int x, y, i, tx, ty;
     cout << "Dwse syntetagmens shmeiou X[1, " << SPACE_X << "), Y[1, " << SPACE_Y << ")\n";
     cin >> x >> y;
     if(x >= SPACE_X || y >= SPACE_Y || x < 0 || y < 0) {
           cout << "Oi sintetagmenes pou dwstae einai ektos oriwn\n";
           return;
     }

     if (cell_has_fire(x,y)>0) {
        cout << "To megethos ths fwtias einai:" << cell_has_fire(x,y) << "\n";
     }
     else {
        cout << "To sigkekrimeno simeio den exei fwtia\n";
     }
     if (fire_delay[x][y] > 0){
        cout << "To shmeio exei katasbestei prin apo ligo apo ton stolo ths pyrosbestikhs\n";
     }
     if (x == base_x && y == base_y){
         cout << "To shmeio pou epileksate einai h bash\n";
     }

      for(i = 0; i < MAX_OXIMATA; i++)
           if (oximata[i]) {
                oximata[i]->get_thesi(&tx, &ty);
                if (tx == x && ty == y) {
                  cout << i << "\t";
                  oximata[i]->print_oxima();
                }
           }

}
//Synarthsh pou ektypwnei tom xwro thw fvties kai ta oximata
void xwros::print_space(void) {
    int x,y, nx, ny;
    int i;
    char oxima;

    system ("cls");
 for( x=0;x<SPACE_X;x++){
  for(y=0;y<SPACE_Y;y++){
		oxima = 0;
	  for(i = 0; i < MAX_OXIMATA; i++) {
	       if (oximata[i]) {
	          oximata[i]->get_thesi(&nx, &ny);
	          if (nx == x && ny == y) {
							oxima = oximata[i]->get_type();
							break;
						}

	       }
		}

   if (oxima) {
   	    print_with_color(MAGENTA, oxima);
    }
   else if (cell_has_fire(x,y) > 0)
     print_with_color(RED, "*");
   else if (fire_delay[x][y] > 0)
     cout << "-";
   else if (x == base_x && y == base_y) {
     print_with_color(GREEN, "B");
   }
   else
     cout << " ";
  }

  cout << "| ";
  switch(x) {
    case 0:
        print_with_color(YELLOW, "5343: Xaris Mallios");
        break;
    case 1:
        print_with_color(YELLOW, "5228: Lefteris Mantas");
        break;
    case 2:
        print_with_color(YELLOW, "5431: Dimitris Stafidas");
        break;
    case 4:
        cout << "MENU:";
        break;
    case 5:
        cout << "E: Exit";
        break;
    case 6:
        cout << "C: Create vehicle";
        break;
    case 7:
        cout << "F: Create fire";
        break;
    case 8:
        cout << "S: Print statistics";
        break;
    case 9:
        cout << "P: Pause";
        break;
    case 10:
        cout << "G: Corrupt vehicle";
        break;
    case 11:
        cout << "Base:" << base_x << "-" << base_y;
        break;
    case 12:
        cout << "Press choice";
        break;
    }
  cout << "\n";
 }

  for(i = 0; i < MAX_OXIMATA; i++)
       if (oximata[i]) {
          cout << i << "\t";
          oximata[i]->print_oxima();
       }
}

xwros * space;
int main()
{
    srand(time(NULL));

    int kb;

    const char* green = "\033[1m ";
    const char* white = "\033[0;37m " ;
    const char* red   = "\033[0;31m  ";

    cout << "System is ready!" << "\n";

    space = new xwros();//dhmiourgia enos neou xwrou space apo ton constructor tou xwrou

    if (!space) {
       cout << "Space is broke!\n";
       system("pause");
       return 0;
    }
    cout << "Space is up!" << "\n";
    //arxikopoihsh me 1 fwtia kai 3 oximata stonm kosmo gia logous emfanishs kai leitoyrgikothtas
    space->create_fire();
    space->dhmiourgia_oximatos();
    space->dhmiourgia_oximatos();
    space->dhmiourgia_oximatos();

    while (space->fire_everywhere() == false ) {
          space->possible_dhmiourgia_oximatos();
          space->spread_fire();

          space->play();
          space->print_space();//ektupwsi tou dhmiourghmenou xwrou
  //        cout << green << "Prasino?" << white << "\n";

          // system("pause");

          //brogxos if-else pou diaxeirizetai tis epiloges tou xrhsth sthn allhlepidrash toy me to programma
          kb = get_keyboard_character();
          if (kb == 'E' || kb == 'e') {
                 break;//to programma termatizetai
          }
          else if (kb == 'C' || kb == 'c') {
                 space->dhmiourgia_oximatos();
                 cout << "A new vehicle just created just for you!\n";
          }
          else if (kb == 'F' || kb == 'f') {
                 space->create_fire();
                 cout << "A new fire just created just for you!\n";
          }
          else if (kb == 'P' || kb == 'p') {
               cout << "System paused!\n";
                 system("pause");
          }
          else if (kb == 'S' || kb == 's') {
                space->get_points_info_and_print_data();
               system("pause");
          }
          else if (kb == 'G' || kb == 'g') {
               space->get_vehicle_and_make_corrupted();
               system("pause");
          }
          // Alles idees
          sleep_for(TIME_DELAY);
    }

    delete space;
    system("pause");
}

// Sinartisi pou dexetai enan xarakthra apo ton xrhsth kai ton epistrefei wste na diaxeiristei apo to parapanw block if-else
int get_keyboard_character() {
    int t;
    if (kbhit()) {
       t = getch();
       while(kbhit()) {
          getch();
       }
       return t;
    }
    else
        return 0;
}
//synarthsh xronokathisterishs pou metra se millisecond ton xrono
void sleep_for(int msec) {
	Sleep(msec);
}
//synarthsh paragvghs tyxaiwn arithmvn
int get_rand(int min, int max) {
	return (rand() % (max - min)) + min;
}
//synarthsh pou ypoligizei thn apoluth timh enos arithmou
int absolute(int x)
{

    if (x>= 0)
    {
        return x;
    }
    else
    {
        return -x;
    }
}
//synarthsh pou ektelei pollaples leitourgies opws perigrafontai parakatw
void oxima::oxima_play(){
	int temp;

//an synthiki true to oxima mpainei se blabh
	if (ilikia < 0) {
		katastasi = OXIMA_SE_BLABI;
	}
	else {
        ilikia -= 1;
    }

    //to oxima omws mporei na mpei & tyxaia se katastasi blabis
    if (get_rand(0,100) <= PROB_OXIMA_SE_BLABI && !in_base() && katastasi == OXIMA_ENERGO) {
        katastasi = OXIMA_SE_BLABI ;
    }

    //an to oxima einai se blabi kai einai sthn basi episkeyazetai,alliws paei sthn basi
	if (katastasi == OXIMA_SE_BLABI) {
		if (in_base()){
			if (ilikia <= 0) {
				return;
			}
             katastasi = OXIMA_ENERGO;
             return;
         }
         else {
              move(base_x, base_y);
		      return;
            }
        }

	// Edw thewrw oti to oxima DEN exei BLABI
	if (posotita_kausimou <= 0) {
		if (in_base()) {
			posotita_kausimou = xwritikotita_kausimou;
			return;
		}
		else {
             //den exw kausima
			// Den eimai sti basi
			// Prepei na paw sti basi

			move(base_x, base_y);
			return;
		}
	}

	// Edw thewrw oti to oxima DEN exei BLABI KAI EXEI kafsima
	if (posotita_nerou <= 0) {
		if (in_base()) {
			posotita_nerou = xwritikotita_nerou;
			return;
		}
		else {
             //Den exw nero
			// Den eimai sti basi
			// Prepei na paw sti basi

			move(base_x, base_y);
			return;
		}
	}

	// Edw thewrw oti to oxima
	//	DEN EXEI BLABI
	//	EXEI KAFSIMA
	// 	EXEI NERO


	if (space->cell_has_fire(thesi_x, thesi_y)) {
		if (space->cell_has_fire(thesi_x, thesi_y) > posotita_nerou) {
			temp = posotita_nerou;
		}
		else {
			temp = space->cell_has_fire(thesi_x, thesi_y);
		}

		space->clear_fire(thesi_x, thesi_y, temp);
		posotita_nerou -= temp;
		return;
	}

	// Edw thewrw oti to oxima
	//	DEN EXEI BLABI
	//	EXEI KAFSIMA
	// 	EXEI NERO
	//  KAI DEN EXEI FWTIA EKEI POU BRISKETAI

    int x, y, l;
    l = 0;
    for(x = 0; x < SPACE_X; x++) {
      for(y = 0; y < SPACE_Y; y++) {
        if(space->cell_has_fire(x, y)) {
          l--;
          if (l < 0) {
            move(x, y);
            return;
          }
        }
      }
    }

	move();
}

void print_with_color(int col, char * t) {
    static HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, col);
    cout << t;
    SetConsoleTextAttribute(hConsole, WHITE);
}
void print_with_color(int col, char t) {
    static HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, col);
    cout << t;
    SetConsoleTextAttribute(hConsole, WHITE);
}
void print_with_color(int col, int t) {
    static HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, col);
    cout << t;
    SetConsoleTextAttribute(hConsole, WHITE);
}
