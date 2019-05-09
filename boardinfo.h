#ifndef BOARDINFO_H
#define BOARDINFO_H
#include <QLabel>
namespace  binfo{

typedef enum ID{
    none,pawn,rook,knight,bishop,queen,king
}piece_id;

typedef enum Special_key_{
    nothing,pawn_queen,pawn_pass,king_leftrook,king_rightrook
}special_key;

typedef struct Chess_pieces{
    QLabel *img;//for img
    piece_id id;
    bool group;
    bool special_skill=false;
    bool first=true;
    bool alive=true;
    int x;
    int y;
}pieces;

typedef struct Board_information{
    QLabel *color;//for route
    piece_id id;
    short group;
    short index;
    int xindex;
    int yindex;
    bool legal;
}board_info;

typedef struct Position_information{
    int x;
    int y;
    bool legal;
}position_info;

typedef struct Record_information{
    board_info from;
    board_info to;
    special_key key;
    bool is_first;
    short second_group;
    short second_index;
    int second_xindex;
    int second_yindex;
}record_info;

}

#endif // BINFO_H
