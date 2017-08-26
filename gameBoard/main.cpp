//Lia Chauvel 6770728 & Simone Gaudreault 6590548
#include <iostream>
#include<sstream>
#include <vector>
#include "gameBoard.h"
#include "tileFactory.cpp"
#include<stdexcept>
#include<algorithm>
#define n 8
using namespace std;
bool takeTurn(const std::string &pName );
void ouvrirLeFichier(ifstream &myfile);
void newGame();
void playGame( std::vector<string> noms);
bool pause=false;
GameBoard<Tile,Player,n,n> bg;
//Cet operateur permet de transformer notre input en un mouvement valide
istream& operator>>(istream& in,Move& m){
    int val;
    if(in>>val){
        switch(val){
        case GAUCHE: case DROITE: case HAUT: case BAS:
            m=Move(val);
            break;
        case 9:
            pause=true;
            break;
        default:
            throw out_of_range("Invalid value for type Move");
        }
    }
    //return in;
}
int main()
{
    string makeAction;
    std::vector<string>::iterator it;//Iterateur permettant de parcourir le vecteur de noms
    std::vector<string> noms;//Vecteurs des noms des joueurs dans la partie
    ifstream myfile("fichierSauvegarde.txt",ifstream::in);//fichier contenant la partie sauvegardée
    //Vérifie si une partie a été enregistrée auparavant
    if(myfile.is_open()){
            std::cout<<"Voulez-vous jouer la partie sauvegarder? La partie sauvegardee sera supprimee sinon.\n Veuillez repondre par oui ou non"<<endl;//Si on veut faire une nouvelle partie, on supprime l'autre partie
            cin>>makeAction;
          std::transform(makeAction.begin(),makeAction.end(),makeAction.begin(),::tolower);//change l'entree en minuscule
          while(makeAction.compare("oui")!=0 && makeAction.compare("non")!=0){//tant qu'on n'écrit pas une entrée valide

              std::cout<<makeAction<<" Veuillez repondre par oui ou non"<<std::endl;
              cin>>makeAction;
              std::transform(makeAction.begin(),makeAction.end(),makeAction.begin(),::tolower);

          }
          if(makeAction.compare("oui")==0){
            ouvrirLeFichier(myfile);//cas ou on veut jouer la partie enregistree
          }
          else{
             myfile.close();
            remove("fichierSauvegarde.txt");
            newGame();
          }

    }
    else{
        newGame();
}
}
//fonction pour jouer chacun des tours
bool takeTurn(const std::string &pName ) {

try {

     Move m;

     //cin.exceptions(std::istream::failbit);
     cout<<" Veuillez rentrer la direction du mouvement de votre joueur soit \n 0 pour GAUCHE, 1 pour DROITE, 2 pour HAUT ou 3 pour BAS"<<endl;

     cin>> m;
     Tile *t=bg.getTile(pName).clone();//Aller chercher la tuile correspondant  au joueur
     //Verifier si le mouvement est possible
     if((m==GAUCHE && t->getColonne()==0) || (m==DROITE && t->getColonne()==n-1) || (m==HAUT && t->getLigne()==0) || (m==BAS && t->getLigne()==n-1)){
        while((m==GAUCHE && t->getColonne()==0) || (m==DROITE && t->getColonne()==n-1) || (m==HAUT && t->getLigne()==0) || (m==BAS && t->getLigne()==n-1)){
        cout<<"Vous ne pouvez pas bouger dans cette direction veuillez reesseyez"<<std::endl;
        cin>>m;
        }
     }

     t=bg.move( m, pName ).clone();//Bouger le joueur
     Player p = bg.getPlayer( pName );//Aller chercher le joueur pour pouvoir modifier ses attributs
     p.setCoordinates(t->getLigne(),t->getColonne());
     bg.setPlayer(p);//Pour modifier l'emplacement du joueur
     if(pause){
        std::cout<<"Vous avez mis le jeu en pause"<<endl;//Cas où l'on appuie sur 9, le code pour mettre le jeu en pause
        return false;
     }
     cout<<"Vous possedez:"<<endl<<p.getGold()<<" pieces dor"<<endl<<p.getRuby()<<" rubis"<<endl<<p.getSpice()<<" sacs depices"<<endl<<p.getFabric()<<" rouleaux de tissu"<<endl<<p.getJewel()<<" bijoux"<<endl<<p.getFood()<<" nourritures"<<endl<<"et votre capacite est de "<<p.getCart()<<endl;



    //Verifie si c'est un désert puisqu'il ne peut pas faire d'action
     if(t->getAction().compare("Desert")==0)
     {
      cout<<"Mouhaha! Vous avez atteri sur un desert. \n "<<endl;
      return true;
     }

//Si le joueur a assez de nourriture, il pourra effectuer l'action s'il le désire
     if (p.canAct()) {

          string makeAction;
          string temp="";
          std::locale c;
          cout<<"Desirez-vous effectuer laction "<<t->getAction()<<"? Veuillez repondre par oui ou non: "<<endl;

          cin>>makeAction;
          std::transform(makeAction.begin(),makeAction.end(),makeAction.begin(),::tolower);
          while(makeAction.compare("oui")!=0 && makeAction.compare("non")!=0){

              std::cout<<makeAction<<" Veuillez repondre par oui ou non"<<std::endl;
              cin>>makeAction;
              std::transform(makeAction.begin(),makeAction.end(),makeAction.begin(),::tolower);

          }

          if ( makeAction.compare("oui")==0){
std::vector<Player> opL = bg.getPlayers( *t );
std::vector<Player>::iterator it;


if (p.getGold()>= opL.size()-1) {

     // consommer une nourriture

                    p.eat();

// payer les joueurs presents

// sur la meme tuile

for (it=opL.begin();it!=opL.end();it++) {
        if((*it).getNom().compare(p.getNom())!=0)
                         p.pay(*it);

                            bg.setPlayer(*it);

                    }

                     // effectuer l’action

                    t->action( p );

                    bg.setPlayer( p );
                    cout<<"Vous possedez maintenant:"<<endl<<p.getGold()<<" pieces dor"<<endl<<p.getRuby()<<" rubis"<<endl<<p.getSpice()<<" sacs depices"<<endl<<p.getFabric()<<" rouleaux de tissu"<<endl<<p.getJewel()<<" bijoux"<<endl<<p.getFood()<<" nourritures"<<endl<<"et votre capacite est de "<<p.getCart()<<endl;

}

          }
          else if (makeAction.compare("non")==0){
            return true;
          }

      }

      return true;

} catch ( std::istream::failure e ) {

cout<<"Incorrect key pressed"; cin.clear();
}catch ( std::out_of_range e ) {
  std::cout<<"Veuillez reessayer"<<std::endl;
}


}
//Methode pour ouvrir le fichier de sauvegarde et faire le setup pour continuer la partie
void ouvrirLeFichier(ifstream &myfile){
     std::vector<string>::iterator it;
    std::vector<string> noms;
    string tempName="";
    //action possible est un tableau de toutes les différents tuiles facilitant la comparaison avec le fichier
    string actionPossible[14]={"Desert","Restaurant", "MarchandEpices", "MarchandTissus","Bijoutier","FabricantCharrette","PetitMarche","MarcheAuxEpices","MarcheAuxBijoux","MarcheTissus","MarcheNoir","Casino","MarchandGemmes","Palais"};
    //tableau de pointeur à tous les types de tuile facilitant la reproduction du jeu
    Tile * tuilePossible[14]={new Tile(),new Restaurant(),new MarchandEpices(),new MarchandTissus(),new Bijoutier(),new FabricantCharrette(),new  PetitMarche(),new MarchandEpices(),new MarcheAuxBijoux(),new MarchandTissus(),new MarcheNoir(),new Casino(),new MarchandGemmes(),new Palais()};
    int n1[2];
    int nombreDeJoueurs;
    int attribut;
    int y;
    string line;
    stringstream strm(stringstream::out | stringstream::in);
        stringstream strm1(stringstream::out | stringstream::in);
        //Tant que le fichier a encore une ligne
    while(!myfile.eof()){
            getline(myfile, line);
            strm<<line;
            for(int i=0;i<2;i++){
                strm>>n1[i];
            }
            //on cherche l'action correcpondante pour crer la bonne tuile
            for (int i=0;i<n1[0]; i++){
                 for (int j=0; j<n1[1]; j++){
                     getline(myfile,line);
                     y=0;
                     bool found=false;
                     int p=0;
                     while(!found && p<14){
                     if(line.compare(actionPossible[p])==0)
                     {
                       bg.add(*tuilePossible[p]->clone(),i,j);

                       found=true;
                     }


                       p++;
                      }
                     }
            }
            //Ensuite, on prend le nombre de joueur
            getline(myfile,line);
            stringstream strm3(stringstream::out | stringstream::in);
            strm3<<line;
            for(int i=0;i<1;i++){
                strm3>>nombreDeJoueurs;
              }
              //on prend les coordonnées du joueur
            for(int i=0;i<nombreDeJoueurs;i++){
                getline(myfile,line);
            strm1<<line;
            int n2[2];
                for(int j=0;j<2;j++){
                    strm1>>n2[j];
                }
                //On prend le nom du joueur
                getline(myfile,line);
                istringstream iss(line);
                if(iss>>tempName){
                    noms.push_back(tempName);
                    Player pl(tempName);
                    pl.setCoordinates(n2[0],n2[1]);
                    bg.addPlayer(pl,n2[0],n2[1]);
                    stringstream strm2(stringstream::out | stringstream::in);
                    getline(myfile,line);
                    strm2<<line;
                    //ajuste les attributs selon le fichier
                    for(int k=0;k<8;k++){
                        strm2>>attribut;
                        switch(k){
                        case 0:
                            pl.setGold(attribut);
                            break;
                        case 1:
                            pl.setRuby(attribut);
                            break;
                        case 2:
                            pl.setSpice(attribut);
                            break;
                        case 3:
                            pl.setFabric(attribut);
                            break;
                        case 4:
                            pl.setJewel(attribut);
                            break;
                        case 5:
                            pl.setCart(attribut);
                            break;
                        case 6:
                            pl.setFood(attribut);
                            break;
                        case 7:
                            pl.setCountMarchandGemmes(attribut);
                            break;
                        }
                }
                bg.setPlayer(pl);
                }
            }
            bg.startGame();//Fait en sorte que les tuiles ont le sbonnes coordonnées
            myfile.close();//ferme le fichier


       }
       playGame(noms);
}
//gere la partie
void playGame( std::vector<string> noms){
    std::vector<string>::iterator it;
    string tempName="";


    bool hasWon=false;
    while(!hasWon && !pause){
    it=noms.begin();
         while(it!=noms.end() && !hasWon && !pause) {

             do {

                  cout<<*it;

             } while (!takeTurn(*it) && !pause);
            if(pause){
                bg.saveGame();
            }
             if ( bg.win(*it) ){
                std::cout<<"Vous avez gagner :)"<<std::endl;
                remove("fichierSauvegarde.txt");//Puisque le joueur a gagné, il n'a plus besoin du fichier!
                std::cout<<"Voulez-vous jouer une nouvelle partie? Veuillez repondre par oui ou non"<<endl;
                string makeAction;
                cin>>makeAction;
                  std::transform(makeAction.begin(),makeAction.end(),makeAction.begin(),::tolower);
                  while(makeAction.compare("oui")!=0 && makeAction.compare("non")!=0){

                      std::cout<<makeAction<<" Veuillez repondre par oui ou non"<<std::endl;
                      cin>>makeAction;
                      std::transform(makeAction.begin(),makeAction.end(),makeAction.begin(),::tolower);

                  }
                  if(makeAction.compare("oui")==0){
                        bg.deletePlayers();
                        newGame();
                        hasWon=true;
                  }
                  else{
                    hasWon=true;
                  }
             }
            it++;
        }
    }
}
//Crée un nouveau jeu
void newGame(){
    std::vector<string>::iterator it;
    std::vector<string> noms;
    string tempName="";
    int nombreDeJoueurs;
     TileFactory *tf= TileFactory::get(n*n);    //aller créer les tuiles

    cout<<"Veuillez entrer le nombre de joueurs: "<<endl;
    cin>>nombreDeJoueurs;
    cout<<"Veuillez entrer le nom de chaque joueur: "<<endl;
    for(int i=0;i<nombreDeJoueurs;i++){
        cin>>tempName;
        noms.push_back(tempName);//ajouter les noms à notre vecteur de noms
        tempName="";
    }
    cout<<"Vous pouvez mettre le jeu en pause en appuyant sur 9 losquon vous demande la direction de votre mouvement."<<endl;
    for (int i=0;i<n; i++){
         for (int j=0; j<n; j++){
              bg.add(*tf->next(),i,j);//ajoute les tuiles au boardgame
         }
    }
    bg.startGame();
    for(it=noms.begin();it!=noms.end();it++){
         Player jp(*it);
        Tile t=bg.startTile(jp);
        bg.addPlayer(jp,t.getLigne(),t.getColonne());
    }
    playGame(noms);
    }







