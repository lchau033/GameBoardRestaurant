//Lia Chauvel 6770728 & Simone Gaudreault 6590548
#include"tileFactory.h"
#include<time.h>

int TileFactory::point=0;
Tile** TileFactory::tff;

TileFactory * TileFactory::get(int _nTiles) { // retourne null si _nTiles<14
        if(_nTiles<14){
            return NULL;
        }
      TileFactory tf(_nTiles);//Nous n'avons pas mis la tilefactory static car nous voulions avoir la capacité de créer une nouvelle partie après qu'une partie a été gagnée

      return &tf;

    }
//retourne la prochaine tuile et incrémente point pour être à la prochaine tuile
    Tile * TileFactory::next(){
        return tff[point++];
    }
//Constructeur qui crée toutes les tuiles
    TileFactory::TileFactory(int _nTiles){
        point=0;
        tff=new Tile*[_nTiles];
        int maxTuile=_nTiles/14;
        int maxDesert=_nTiles%14+maxTuile;
        int compteur=14;
        //crée les différents type de tuile
        tff[0]=new Tile();
        tff[1]=new Restaurant();
        tff[2]=new MarchandEpices();
        tff[3]=new MarchandTissus();
        tff[4]=new Bijoutier();
        tff[5]=new FabricantCharrette();
        tff[6]=new PetitMarche();
        tff[7]=new MarcheAuxEpices();
        tff[8]=new MarcheAuxBijoux();
        tff[9]=new MarcheTissus();
        tff[10]=new MarcheNoir();
        tff[11]=new Casino();
        tff[12]=new MarchandGemmes();
        tff[13]=new Palais();
        //clone les tuiles
        for(int i=1;i<14;i++){
            for(int j=compteur;j<(maxTuile-1)+compteur;j++){
                tff[j]=tff[i]->clone();
            }
            compteur+=maxTuile-1;
        }
        for(int i=compteur;i<(maxDesert-1)+compteur;i++){
            tff[i]=tff[0]->clone();
        }
        //Afin que nos tuiles soient en désordre, nous les faisons s'échanger de place entre elle de façon aléatoire pour une nombre d'échange aléatoire selon le nombre de tuiles
        srand(time(NULL));
        int rand1=rand()%(100*_nTiles)+_nTiles*_nTiles;
        int rand3=0;
        int rand2=0;
        for(int i=0;i<rand1;i++){
            rand3=rand()%_nTiles;
            rand2=rand()%_nTiles;
            std::swap(tff[rand3],tff[rand2]);
        }

    }

