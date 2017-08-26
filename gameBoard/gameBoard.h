//Lia Chauvel 6770728 & Simone Gaudreault 6590548
#ifndef GAMEBOARD_H
#define GAMEBOARD_H
#include<time.h>
#include<string.h>
#include<vector>
#include<fstream>
#include <iostream>
#include"tile.h"
#include<tr1/array>
#include<list>

enum Move{GAUCHE,DROITE,HAUT,BAS};
template<class T=Tile,class J=Player,int COLONNE=6,int LIGNE=6>
class GameBoard {
    T ***grille;
    std::vector<J> players;
    static int nombreDeRestaurant;
    static std::vector<std::tr1::array<int,2> > endroitsRestaurants;
public:
    GameBoard(){//Nous avons appelé cette classe GameBoard, mais elle représente la classe BoardGame dans le projet.
        grille=new T**[LIGNE];
        for(int i=0;i<LIGNE;i++){
            grille[i]=new T*[COLONNE];
        }
    }
    //ajoute une tuile au gameboard
    void add(const T& tile, int row, int col){
        grille[row][col]=tile.clone();
    }
    //ajoute un joueur sur une tuile donnée et dans le vecteur
    void addPlayer(J player, int row, int col){
        player.setCoordinates(row,col);
        grille[row][col]->addPlayer(player);
        players.push_back(player);
    }
    //va chercher une tuile selon sa ligne et sa colonne
    const T& getTile(int row, int col) const{
        return grille[row][col];
    }
    //obtient les coordonnées d'une tuile et change la valeur des pointeurs
    void getCoordinate(const T &tile, int *row, int *col) const{
        int i=0,j=0,pointI=0,pointJ=0;
        bool found=false;
        while(i<COLONNE && !found){
            j=0;
            while(j<LIGNE && !found){
                if(grille[i][j]==tile){
                    pointI=i;
                    pointJ=j;
                    found=true;
                }
                j++;
            }
            i++;
        }
        if(found){
            *row=pointI;
            *col=pointJ;
        }
    }
    //mettre à jour les attributs des joueurs
    void setPlayer(J player){
        bool found=false;
        typename std::vector<J>::iterator it=players.begin();
        while(it!=players.end() && !found){
            if((*it).getNom().compare(player.getNom())==0){
                found=true;
                (*it).setGold(player.getGold());
                (*it).setRuby(player.getRuby());
                (*it).setSpice(player.getSpice());
                (*it).setFabric(player.getFabric());
                (*it).setJewel(player.getJewel());
                (*it).setCart(player.getCart());
                (*it).setFood(player.getFood());
                (*it).setCoordinates(player.getRow(),player.getCol());

            }
            it++;
        }


    }
    //Trouver un joueur et le retourner selon son nom
    J getPlayer(const std::string& playerName)const{
        typename std::vector<J>::const_iterator it=players.begin();
        bool found=false;
        J thePlayer;
        while(it!=players.end() && !found){
            if((*it).getNom().compare(playerName)==0){
                found=true;
                thePlayer=*it;
            }
            it++;
        }
        return thePlayer;

    }
    //Chercher une tuile et la retourner selon le nom du joueur qui s'y trouve
    const T& getTile(const std::string& playerName) const{
        J thePlayer=this->getPlayer(playerName);
        return *grille[thePlayer.getRow()][thePlayer.getCol()];
    }
    //Retourne un vecteur contenant les joueurs sur une tuile particulière
    std::vector<J> getPlayers(const T &tile){
        std::list<J> listOfPlayers=grille[tile.getLigne()][tile.getColonne()]->getList();
        std::vector<J> vectorOfPlayers;
        typename std::list<J>::iterator it;
        for(it=listOfPlayers.begin();it!=listOfPlayers.end();it++){
            vectorOfPlayers.push_back(*it);
        }
        return vectorOfPlayers;
    }
//Méthode qui fait bouger un joueur sur une case selon le move choisi.
    const T& move(Move move, const std::string& playerName ){
        T* currentGrid=this->getTile(playerName).clone();
        J p=this->getPlayer(playerName);
        grille[currentGrid->getLigne()][currentGrid->getColonne()]->removePlayer(p);//Le joueur est enlevé de la position précedente
        if(move==GAUCHE){
            currentGrid=grille[currentGrid->getLigne()][currentGrid->getColonne()-1];
        }
        else if(move==DROITE){
            currentGrid=grille[currentGrid->getLigne()][currentGrid->getColonne()+1];
        }
        else if(move==HAUT){
            currentGrid=grille[currentGrid->getLigne()-1][currentGrid->getColonne()];
        }
        else if(move==BAS){
            currentGrid=grille[currentGrid->getLigne()+1][currentGrid->getColonne()];

        }
        p.setCoordinates(currentGrid->getLigne(),currentGrid->getColonne());
        grille[currentGrid->getLigne()][currentGrid->getColonne()]->addPlayer(p);//Le joueur est ajouté à sa nouvelle position
        return (*currentGrid);
    }
    //Vérifie si le joueur a gagné.
    bool win(std::string &pName){
        bool win=false;
        typename std::vector<J>::iterator it=players.begin();
        bool found=false;
        while(it!=players.end() && !found){
            if((*it).getNom().compare(pName)==0){
                found=true;
                if((*it).getRuby()==5){//condition pour gagner
                    win=true;
                }
            }
            it++;
        }
        return win;
    }
    //Choisi une tuile au hasard parmi les tuiles restaurant et positionne le joueur sur cette tuile (au début du jeu)
    const T& startTile(J& p){
        int grid=rand()%nombreDeRestaurant;
        p.setCoordinates(endroitsRestaurants.at(grid)[0],endroitsRestaurants.at(grid)[1]);
        return *grille[p.getRow()][p.getCol()];
    }
    //ajuste les lignes et les colonnes de chaque case de la grille et trouve les cases restaurant
    void startGame(){
        std::tr1::array<int,2> tempTab;
        for(int i=0;i<LIGNE;i++){
            for(int j=0;j<COLONNE;j++){
                grille[i][j]->setLigne(i);
                grille[i][j]->setCol(j);
            }
        }
        for(int i=0; i<LIGNE;i++){
            for(int j=0;j<COLONNE;j++){
                if(grille[i][j]->getAction().compare("Restaurant")==0){
                        tempTab[0]=i;
                        tempTab[1]=j;
                    endroitsRestaurants.push_back(tempTab);
                    nombreDeRestaurant++;
                }
            }
        }
    }
    //enregistrer les données importantes afin de recréer le jeu plus tard
    void saveGame()
    {
          std::ofstream myfile; // création du fichier
    myfile.open("fichierSauvegarde.txt");
        myfile << *this;
        myfile.close();
    }
         friend inline std::ostream& operator<<(std::ostream&out, const GameBoard&bg)
{
    out<<LIGNE<<" "<<COLONNE<<std::endl;
   for(int i=0;i<LIGNE;i++){
    for(int j=0;j<COLONNE;j++){
        out<<bg.grille[i][j]->getAction()<<std::endl;//Commence par écrire dans le fichier toutes l' action de chaque tuile en ordre
    }
   }
   //écrit le nombre de joueur puis le joueur
   out<<bg.players.size()<<std::endl;
   for(typename std::vector<J>::const_iterator it=bg.players.begin();it!=bg.players.end();it++){
            out<<*it<<std::endl;
        }
   return out;

}
//Supprime les joueurs lorsqu'on crée une nouvelle partie
void deletePlayers()
{

    players.erase(players.begin(),players.end());
}


};
template<class T,class J,int COLONNE,int LIGNE>
int GameBoard<T,J,COLONNE,LIGNE>::nombreDeRestaurant=0;
template<class T,class J,int COLONNE,int LIGNE>
std::vector<std::tr1::array<int,2> > GameBoard<T,J,COLONNE,LIGNE>::endroitsRestaurants;


#endif // GAMEBOARD_H
