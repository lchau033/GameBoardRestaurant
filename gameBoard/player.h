//Lia Chauvel 6770728 & Simone Gaudreault 6590548
#ifndef PLAYER_H
#define PLAYER_H

#include <string>
class Player{
    private:
        int gold ; //le nombre de pièces d’or.
        int ruby ;// le nombre de rubis.
        int spice ; // le nombre de sacs d’épices.
        int fabric ;// le nombre de rouleaux de tissus.
        int jewel ;  //le nombre de bijoux.
        int cart ; // la capacité du joueur.
        int food ; // le nombre de nourritures.
        std::string nom;
        int countMarchandGemmes;
        int row;
        int col;
public:
    Player(std::string &playerName){
        this->nom=playerName;
        gold=5;
        ruby=0;
        spice=1;
        fabric=1;
        jewel=1;
        this->food=10;
        cart=9;
        this->countMarchandGemmes=0;//variable permettant de suivre le nombre de fois qu'on a acheté un rubis d'un marchand de Gemmes
    }
    Player(){};
    bool canAct() const{ // retourne vrai si food > 0
        return this->food>0;
    }
    bool pay( Player& player ){ // donne une pièce d’or à un autre joueur
        bool payed=false;
        if(this->gold-1>=0){
            this->gold-=1;
            player.setGold(player.getGold()+1);
            payed=true;
        }
        return payed;
    }
    void eat(){// reduit le nombre de nourritures de 1 si food > 0
        if(this->canAct()){
            this->food-=1;
        }
    }
    void setCoordinates(int row, int col){
        this->col=col;
        this->row=row;
    }
    int getCol()const{
        return this->col;
    }
    int getRow()const{
        return this->row;
    }
    int getGold()const{
        return gold;
    }
    void setGold(int value){
        this->gold=value;
    }
    int getRuby()const{
        return ruby;
    }
    void setRuby(int value){
        this->ruby=value;
    }
    int getSpice()const{
        return spice;
    }
    void setSpice(int value){
        spice=value;
    }
    int getFabric()const{
        return fabric;
    }
    void setFabric(int value){
        fabric=value;
    }
    int getJewel()const{
        return jewel;
    }
    void setJewel(int value){
        jewel=value;
    }
    int getCart()const{
        return cart;
    }
    void setCart(int value){
        cart=value;
    }
    int getFood()const{
        return food;
    }
    void setFood(int value){
        food=value;
    }
    int getCountMarchandGemmes()const{
        return countMarchandGemmes;
    }
    void setCountMarchandGemmes(int value){
        countMarchandGemmes=value;
    }
    std::string getNom()const{
        return nom;
    }
    friend inline std::ostream& operator<<(std::ostream&t,const Player& p){
        t<<p.getRow()<<" "<<p.getCol()<<" "<<std::endl<<p.getNom()<<std::endl<<p.getGold()<<" "<<p.getRuby()<<" "<<p.getSpice()<<" "<<p.getFabric()<<" "<<p.getJewel()<<" "<<p.getCart()<<" "<<p.getFood()<<" "<<p.getCountMarchandGemmes();
        return t;
    }


};
#endif // PLAYER_H
