//Lia Chauvel 6770728 & Simone Gaudreault 6590548
#ifndef TILE_H
#define TILE_H
#include <iostream>
#include<list>
#include "player.h"
#include<string>
#include<stdlib.h>
#include<sstream>
#include<algorithm>
class Tile{
    int colonne;
    int ligne;
    std::list<Player> joueurs;
public:
    Tile(){
        this->colonne=0;
        this->ligne=0;
    }

    int getColonne()const{
        return this->colonne;
    }
    int getLigne()const{
        return this->ligne;
    }
// retourne vrai si la tuile comparée est au même endroit
    bool operator==(const Tile &t){
        bool egal=false;
        if(t.colonne==this->colonne && t.ligne==this->ligne){
            egal=true;
        }
        return egal;
    }

    virtual bool action( Player& player ){
        return true;
    }

    virtual Tile* clone()const{
        return new Tile(*this);
    }
    //imprime la ligne et la colonne
    friend inline std::ostream& operator<<(std::ostream &out,const Tile& tile){
        out<<tile.getLigne()<<", "<<tile.getColonne();
        return out;
    }
    //obtient la liste des joueurs qui sont sur la tuile
    std::list<Player> getList()const{
        return this->joueurs;
    }
    //ajoute un joueur sur la tuile
    void addPlayer(const Player &p){
        joueurs.push_back(p);
    }
    //retire une joueur de la tuile
    void removePlayer(Player &p){
        std::list<Player> newList;
        std::list<Player>::iterator it;
        for(it=joueurs.begin();it!=joueurs.end();it++){//copie tous les joueurs n'ayant pas le nom de p
            if((*it).getNom().compare(p.getNom())!=0){
                newList.push_back(*it);
            }
        }
        joueurs=newList; //change la valeur de la liste
    }
    //retourne l'action de la tuile
    virtual std::string getAction()const{
        return "Desert";
    }
    void setLigne(int ligne){
        this->ligne=ligne;
    }
    void setCol(int col){
        this->colonne=col;
    }
};
//La tuile Restaurant met la nourriture à 10
class Restaurant: public Tile{
public:
    Restaurant():Tile(){

    }
    virtual bool action(Player &player){
        bool canPerform=false;
        player.setFood(10);
        canPerform=true;
        return canPerform;
    }
    virtual Restaurant* clone()const{
        return new Restaurant(*this);
    }
    virtual std::string getAction()const
    {
        return "Restaurant";
    }

};
//La tuile MarchandEpices, donne 3 sac d'épices en échange de 2 pièces d'or (moins si la capacité ne le permet pas)
class MarchandEpices:public Tile{
    public:
    MarchandEpices():Tile(){
    }
    virtual bool action(Player &player){
        bool canPerform=false;
        if(player.getGold()>=2){
            canPerform=true;
            player.setGold(player.getGold()-2);
            int j=0;
            while(player.getCart()>0 && j<3){
                player.setSpice(player.getSpice()+1);
                player.setCart(player.getCart()-1);
                j++;
            }
        }
        return canPerform;
    }
    virtual MarchandEpices* clone()const{
        return new MarchandEpices(*this);
    }
    virtual std::string getAction()const{
        return "MarchandEpices";
    }

};
//La tuile MarchandTissus, donne 3 sac de tissus en échange de 2 pièces d'or (moins si la capacité ne le permet pas)
class MarchandTissus:public Tile{
    public:
    MarchandTissus():Tile(){
    }
    virtual bool action(Player &player){
        bool canPerform=false;
        if(player.getGold()>=2){
            canPerform=true;
            player.setGold(player.getGold()-2);
            int j=0;
            while(player.getCart()>0 && j<3){
                player.setFabric(player.getFabric()+1);
                player.setCart(player.getCart()-1);
                j++;
            }
        }
        return canPerform;
    }
    virtual MarchandTissus* clone() const{
        return new MarchandTissus(*this);
    }
    virtual std::string getAction()const
    {
        return "MarchandTissus";
    }
};
//La tuile Bijoutier, donne 3 sac de bijoux en échange de 2 pièces d'or (moins si la capacité ne le permet pas)
class Bijoutier:public Tile{
    public:
    Bijoutier():Tile(){
    }
    virtual bool action(Player &player){
        bool canPerform=false;
        if(player.getGold()>=2){
            canPerform=true;
            player.setGold(player.getGold()-2);
            int j=0;
            while(player.getCart()>0 && j<3){
                player.setJewel(player.getJewel()+1);
                player.setCart(player.getCart()-1);
                j++;
            }
        }
        return canPerform;
    }
    virtual Bijoutier* clone()const{
        return new Bijoutier(*this);
    }
    virtual std::string getAction()const
    {
        return "Bijoutier";
    }
};
//La tuile FabricantCharrette, la capacité du joueur est augmenté de trois unités en échange de 7 pièces d'or
class FabricantCharrette:public Tile{
    public:
    FabricantCharrette(){
    }
    virtual bool action(Player &player){
        bool canPerform=false;
        if(player.getGold()>=7){
            player.setGold(player.getGold()-7);
            canPerform=true;
            player.setCart(player.getCart()+3);
        }
        return canPerform;
    }
    virtual FabricantCharrette* clone() const{
        return new FabricantCharrette(*this);
    }
    virtual std::string getAction()const
    {
        return "FabricantCharrette";
    }
};
//La tuile PetitMarche, donne 8 pièces d'or sac de tissus en échange de 1 sac d'épice, 1 rouleau de tissu et d'un bijou
class PetitMarche:public Tile{
    public:
    PetitMarche():Tile(){
    }
    virtual bool action(Player &player){
        bool canPerform=false;
        if(player.getFabric()>=1 && player.getSpice()>=1 && player.getJewel()>=1){
            canPerform=true;
            player.setFabric(player.getFabric()-1);
            player.setSpice(player.getSpice()-1);
            player.setJewel(player.getJewel()-1);
            player.setGold(player.getGold()+8);
            player.setCart(player.getCart()+3);
        }
        return canPerform;
    }
    virtual PetitMarche* clone() const{
        return new PetitMarche(*this);
    }
    virtual std::string getAction()const
    {
        return "PetitMarche";
    }
};
//La tuile MarcheAuxEpices, donne 6 pièces d'or en échange de 3 sacs d'épices
class MarcheAuxEpices:public Tile{
    public:
    MarcheAuxEpices():Tile(){
    }
    virtual bool action(Player &player){
        bool canPerform=false;
        if(player.getSpice()>=3){
            canPerform=true;
            player.setSpice(player.getSpice()-3);
            player.setGold(player.getGold()+6);
            player.setCart(player.getCart()+3);
        }
        return canPerform;
    }
    virtual MarcheAuxEpices* clone() const{
        return new MarcheAuxEpices(*this);
    }
    virtual std::string getAction()const
    {
        return "MarcheAuxEpices";
    }
};
//La tuile MarcheAuxBijoux, donne 6 pièces d'or en échange de 3 bijoux
class MarcheAuxBijoux:public Tile{
    public:
    MarcheAuxBijoux():Tile(){
    }
    virtual bool action(Player &player){
        bool canPerform=false;
        if(player.getJewel()>=3){
            canPerform=true;
            player.setJewel(player.getJewel()-3);
            player.setGold(player.getGold()+6);
            player.setCart(player.getCart()+3);
        }
        return canPerform;
    }
    virtual MarcheAuxBijoux* clone() const{
        return new MarcheAuxBijoux(*this);
    }
    virtual std::string getAction()const
    {
        return "MarcheAuxBijoux";
    }
};
//La tuile MarcheTissus, donne 6 pièces d'or en échange de 3 rouleaux de tissus
class MarcheTissus: public Tile{
    public:
    MarcheTissus():Tile(){
    }
    virtual bool action(Player &player){
        bool canPerform=false;
        if(player.getFabric()>=3){
            canPerform=true;
            player.setFabric(player.getFabric()-3);
            player.setGold(player.getGold()+6);
            player.setCart(player.getCart()+3);
        }
        return canPerform;
    }
    virtual MarcheTissus* clone() const{
        return new MarcheTissus(*this);
    }
    virtual std::string getAction()const
    {
        return "MarcheTissus";
    }
};
//La tuile MarcheNoir, donne au hasard entre 0-5 ressources tissus, épices et ou bijoux en échange de 1 pièce d'or
class MarcheNoir: public Tile{
    public:
    MarcheNoir():Tile(){
    }
    virtual bool action(Player &player){
        bool canPerform=false;
        int ressource=0;
        int nombreDeRessource=0;
        int i=0;
        if(player.getGold()>=1){
            canPerform=true;
            player.setGold(player.getGold()-1);
            ressource=rand()%6;//Nombre au hasard entre 0-5 de ressources
            while(player.getCart()>0 && i<ressource){//pour chaque items, on choisit au hasard quelle sorte d'item le joueur obtient
                nombreDeRessource=rand()%3;
                if(nombreDeRessource==0){
                    player.setFabric(player.getFabric()+1);
                }
                else if(nombreDeRessource==1){
                    player.setSpice(player.getSpice()+1);
                }
                else{
                    player.setJewel(player.getJewel()+1);
                }
                player.setCart(player.getCart()-1);
                i++;
            }
        }
        return canPerform;
    }
    virtual MarcheNoir* clone() const{
        return new MarcheNoir(*this);
    }
    virtual std::string getAction()const
    {
        return "MarcheNoir";
    }
};
//La tuile Casino, donne au hasard entre 0 et 10 pièces d'or en échange de 1 pièce d'or
class Casino: public Tile{
    public:
    Casino():Tile(){
    }
    virtual bool action(Player &player){
        bool canPerform=false;
        int choix=0;
        if(player.getGold()>=1){
            canPerform=true;
            player.setGold(player.getGold()-1);
            choix=rand()%10;
            if(choix==4 || choix==5 || choix==6){
                player.setGold(player.getGold()+2);
            }
            else if(choix==7 || choix==8){
                player.setGold(player.getGold()+3);
            }
            else if(choix==9){
                player.setGold(player.getGold()+10);
            }
        }
        return canPerform;
    }
        virtual Casino* clone()const{
            return new Casino(*this);
        }
    virtual std::string getAction()const
    {
        return "Casino";
    }
    };
//La tuile MarchandGemmes, donne un ruby en échange de 12 pièces d'or pour le premier, puis 13, etc.
class MarchandGemmes:public Tile{
    public:
    MarchandGemmes():Tile(){
    }
    virtual bool action(Player &player){
        bool canPerform=false;
        if(player.getGold()>=(12 + player.getCountMarchandGemmes())){
            player.setGold(player.getGold()-12+player.getCountMarchandGemmes());
            canPerform=true;
        if(player.getCart()>0)
            {
            player.setRuby(player.getRuby()+1);
            player.setCart(player.getCart()-1);
            player.setCountMarchandGemmes(player.getCountMarchandGemmes()+1);
        }

        }
        return canPerform;
    }
    virtual MarchandGemmes* clone() const{
        return new MarchandGemmes(*this);
    }
    virtual std::string getAction()const
    {
        return "MarchandGemmes";
    }
};
//La tuile Palais, donne un ruby en échange de 5 rouleaux de tissus, 5 sacs d'épices et 5 bijoux
class Palais:public Tile{
    public:
    Palais():Tile(){
    }
    virtual bool action(Player &player){
        bool canPerform=false;
        if( player.getFabric()>=5 && player.getSpice()>=5 && player.getJewel()>=5){
            canPerform=true;
            player.setRuby(player.getRuby()+1);
            player.setCart(player.getCart()+14);
            player.setFabric(player.getFabric()-5);
            player.setSpice(player.getSpice()-5);
            player.setJewel(player.getJewel()-5);
        }
        return canPerform;
    }
    virtual Palais* clone() const{
        return new Palais(*this);
    }
    virtual std::string getAction()const
    {
        return "Palais";
    }
};











#endif // TILE_H
