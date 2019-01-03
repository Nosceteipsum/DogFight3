////////////////////////////////////////////////////////////////////
//                                                                //
//	  	  DF 3: Map_H                                             //
//                                                                //
//	     Made By: Tommy Kobberø Andersen                          //
//                                                                //
////////////////////////////////////////////////////////////////////

#if!defined CMAP_H
#define CMAP_H

struct SData;

#define MAP_TYPE_GRASS      1
#define MAP_TYPE_FARM       2
#define MAP_TYPE_ICE        3
#define MAP_TYPE_WILD_GRASS 4
#define MAP_TYPE_ADV_GRASS  5

//--------------------------------------------------------//
//--			Struct/classes			--//
//--------------------------------------------------------//

class CMap
{
public:

CMap();
~CMap();

void Init();

void Draw(SData *Data);
void Draw_Tree(SData *Data);

char  m_cMapType;

bool  m_bTreeActivate[3];
float m_fTreeX[3];
char  m_cTreeType[3];

bool  m_baField_Destroyed[15];

protected:
private:

};

#endif
